// Copyright (C) 2016 by Rage MP Team

#include "GameLauncherProxy.h"

#include "OS/OS.h"

#include <Windows.h>

#include "Strings.h"

#include "Memory/Hooking/Hooking.h"
#include "Memory/Hooking/Injecting.h"

#include "Logger.h"

#include "ErrorReporting.h"

#include "ClientConsts.h"

/**
 * The return value from ResumeThread when it fails.
 *
 * If we trust enough MSDN thats the value they return when resume thread failed - they do not
 * mention any specific variable defined inside win32 so I prefer to put it here this way.
 */
const DWORD RESUME_THREAD_FAILED_VALUE = static_cast<DWORD>(-1);

/** The CreateProcessW prototype */
typedef BOOL (WINAPI *CreateProcessW_t)(LPCWCH lpApplicationName, LPWSTR lpCommandLine, LPSECURITY_ATTRIBUTES lpProcessAttributes,
			LPSECURITY_ATTRIBUTES lpThreadAttributes, BOOL bInheritHandles, DWORD dwCreationFlags, LPVOID lpEnvironment,
			LPCWSTR lpCurrentDirectory, LPSTARTUPINFOW lpStartupInfo, LPPROCESS_INFORMATION lpProcessInformation);

/** Pointer to the CreateProcessW trampoline */
CreateProcessW_t OriginalCreateProcessW = nullptr;

/** Handle creation of GTAIV process */
BOOL WINAPI HandleCreateGTAIVProcess(LPCWSTR lpApplicationName, LPWSTR lpCommandLine, LPSECURITY_ATTRIBUTES lpProcessAttributes,
			LPSECURITY_ATTRIBUTES lpThreadAttributes, BOOL bInheritHandles, DWORD dwCreationFlags, LPVOID lpEnvironment,
			LPCWSTR lpCurrentDirectory, LPSTARTUPINFOW lpStartupInfo, LPPROCESS_INFORMATION lpProcessInformation)
{
	PathString gameDirectory = OS::GetModulePath();
	PathString exeDirectory(gameDirectory);
	exeDirectory.Append("\\");
	exeDirectory.Append(GAME_EXE_NAME);

	wchar_t gameExePath[MAX_PATH] = { 0 };
	wchar_t gamePath[MAX_PATH] = { 0 };

	Logger::Msg("Game path: %s", *exeDirectory);

	MultiByteToWideChar(CP_ACP, NULL, exeDirectory, exeDirectory.Length(), gameExePath, MAX_PATH);
	MultiByteToWideChar(CP_ACP, NULL, gameDirectory, gameDirectory.Length(), gamePath, MAX_PATH);

	const BOOL result = OriginalCreateProcessW(gameExePath, lpCommandLine, lpProcessAttributes,
		lpThreadAttributes, bInheritHandles, dwCreationFlags | CREATE_SUSPENDED, lpEnvironment, gamePath,
		lpStartupInfo, lpProcessInformation);
	if (! result) {
		AString512 errorMessage;
		errorMessage.Format("Failed to start game process.\nGame path: %s\nErrno: %u", *exeDirectory, GetLastError());
		HandleError(errorMessage);
		return result;
	}

	const HANDLE gameProcess = lpProcessInformation->hProcess;

	// Inject core dll again so it can start multiplayer game.
	const PathString &corePath = OS::GetModuleFullPath(CORE_DLL_NAME);
	const InjectResult injectResult = InjectDll(lpProcessInformation->hProcess, corePath);
	if (injectResult != INJECT_RESULT_OK) {
		AString256 errorMessage;
		errorMessage.Format("Could not inject dll into the game process. Please try launching the mod again.\n\nErrno: %u, Errstr: %s", GetLastError(), InjectResultToString(injectResult));
		HandleError(errorMessage);
		TerminateProcess(lpProcessInformation->hProcess, 0);
		return 0;
	}

	if (ResumeThread(lpProcessInformation->hThread) == RESUME_THREAD_FAILED_VALUE) {
		AString256 errorMessage;
		errorMessage.Format("Could not resume process main thread. Please try launching the mod again.\n\nErrno: %u", GetLastError());
		HandleError(errorMessage);
		TerminateProcess(lpProcessInformation->hProcess, 0);
		return 0;
	}
	return result;
}

/**
 * The hook to the CreateProcessW.
 */
BOOL WINAPI MyCreateProcessW(LPCWSTR lpApplicationName, LPWSTR lpCommandLine, LPSECURITY_ATTRIBUTES lpProcessAttributes,
			LPSECURITY_ATTRIBUTES lpThreadAttributes, BOOL bInheritHandles, DWORD dwCreationFlags, LPVOID lpEnvironment,
			LPCWSTR lpCurrentDirectory, LPSTARTUPINFOW lpStartupInfo, LPPROCESS_INFORMATION lpProcessInformation)
{
	if (wcscmp(lpApplicationName, WC_GAME_EXE_NAME)) {
		return OriginalCreateProcessW(lpApplicationName, lpCommandLine, lpProcessAttributes,
					lpThreadAttributes, bInheritHandles, dwCreationFlags, lpEnvironment, lpCurrentDirectory,
					lpStartupInfo, lpProcessInformation);
	}

	return HandleCreateGTAIVProcess(lpApplicationName, lpCommandLine, lpProcessAttributes,
					lpThreadAttributes, bInheritHandles, dwCreationFlags, lpEnvironment, lpCurrentDirectory,
					lpStartupInfo, lpProcessInformation);
}

/**
 * Get procedure address reimplementation.
 *
 * Unfortunately on Windows10 sometimes default GetProcAddress is not
 * returning address from Kernel32 but instead returns methods from
 * the compatibility layer DLLs - this plain implementation of
 * get proc address helps with this so we can hook into right method.
 *
 * @param[in] module The module where to find procedure.
 * @param[in] procName The name of the procedure to get.
 * @return Address to the procedure or @c nullptr in case procedure is not found.
 */
inline FARPROC GetProcAddressEx(const HMODULE module, const char *const procName)
{
	const PBYTE imageBase = reinterpret_cast<PBYTE>(module);
	const IMAGE_DOS_HEADER *const dosHeader = reinterpret_cast<IMAGE_DOS_HEADER *>(imageBase);
	const IMAGE_NT_HEADERS *const ntHeaders = reinterpret_cast<IMAGE_NT_HEADERS *>(imageBase + dosHeader->e_lfanew);
	const IMAGE_EXPORT_DIRECTORY *const exportDirectory = reinterpret_cast<IMAGE_EXPORT_DIRECTORY *>(imageBase + ntHeaders->OptionalHeader.DataDirectory[0].VirtualAddress);

	const Address_t *const names = reinterpret_cast<const Address_t *>(imageBase + exportDirectory->AddressOfNames);
	const Address_t *const procs = reinterpret_cast<Address_t *>(imageBase + exportDirectory->AddressOfFunctions);
	const uint16 *const ords = reinterpret_cast<uint16 *>(imageBase + exportDirectory->AddressOfNameOrdinals);

	for (uint32 i = 0; i < exportDirectory->NumberOfFunctions; ++i) {
		const char *const name = reinterpret_cast<const char *>(imageBase + names[i]);
		if (!strcmp(name, procName)) {
			const uint16 ord = ords[i];
			return reinterpret_cast<FARPROC>(imageBase + procs[ord]);
		}
	}
	return nullptr;
}

/** Address to the CreateProcessW method inside Kernel32.dll */
FARPROC CreateProcessWKernel32 = nullptr;

void GameLauncherProxy::Init(void)
{
	Hooking::Init();

	const HMODULE kernel32 = GetModuleHandle("Kernel32.dll");
	CreateProcessWKernel32 = GetProcAddressEx(kernel32, "CreateProcessW");

	OriginalCreateProcessW = reinterpret_cast<CreateProcessW_t>(Hooking::InstallJmpHook(reinterpret_cast<Address_t>(CreateProcessWKernel32), reinterpret_cast<Address_t>(MyCreateProcessW)));
}

void GameLauncherProxy::Shutdown(void)
{
	Hooking::UninstallJmpHook(reinterpret_cast<Address_t>(CreateProcessWKernel32), reinterpret_cast<const Address_t *>(OriginalCreateProcessW));
	CreateProcessWKernel32 = nullptr;
	Hooking::Shutdown();
}

/* eof */
