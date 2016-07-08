// Copyright (C) 2016 by Rage MP Team

#include "GameLauncherProxy.h"

#include "OS/OS.h"

#include <Windows.h>

#include "Strings.h"

#include "Memory/Hooking/Hooking.h"
#include "Memory/Hooking/Injecting.h"

typedef BOOL
(WINAPI *CreateProcessW_t)(LPCWCH lpApplicationName, LPWSTR lpCommandLine, LPSECURITY_ATTRIBUTES lpProcessAttributes,
			LPSECURITY_ATTRIBUTES lpThreadAttributes, BOOL bInheritHandles, DWORD dwCreationFlags, LPVOID lpEnvironment,
			LPCWSTR lpCurrentDirectory, LPSTARTUPINFOW lpStartupInfo, LPPROCESS_INFORMATION lpProcessInformation
);

CreateProcessW_t OriginalCreateProcess = nullptr;

BOOL WINAPI MyCreateProcess(LPCWSTR lpApplicationName, LPWSTR lpCommandLine, LPSECURITY_ATTRIBUTES lpProcessAttributes,
			LPSECURITY_ATTRIBUTES lpThreadAttributes, BOOL bInheritHandles, DWORD dwCreationFlags, LPVOID lpEnvironment,
			LPCWSTR lpCurrentDirectory, LPSTARTUPINFOW lpStartupInfo, LPPROCESS_INFORMATION lpProcessInformation)
{
	if (wcscmp(lpApplicationName, L"GTAIV.exe")) {
		return OriginalCreateProcess(lpApplicationName, lpCommandLine, lpProcessAttributes,
					lpThreadAttributes, bInheritHandles, dwCreationFlags, lpEnvironment, lpCurrentDirectory,
					lpStartupInfo, lpProcessInformation);
	}

	PathString gameDirectory = OS::GetModulePath();
	PathString exeDirectory(gameDirectory);
	exeDirectory.Append("\\GTAIV.exe");

	wchar_t gameExePath[MAX_PATH] = { 0 };
	wchar_t gamePath[MAX_PATH] = { 0 };

	MultiByteToWideChar(CP_UTF8, NULL, exeDirectory, exeDirectory.Length(), gameExePath, MAX_PATH);
	MultiByteToWideChar(CP_UTF8, NULL, gameDirectory, gameDirectory.Length(), gamePath, MAX_PATH);

	const BOOL result = OriginalCreateProcess(gameExePath, lpCommandLine, lpProcessAttributes,
		lpThreadAttributes, bInheritHandles, dwCreationFlags | CREATE_SUSPENDED, lpEnvironment, gamePath,
		lpStartupInfo, lpProcessInformation);

	if (! result) {
		return result;
	}

	const HANDLE gameProcess = lpProcessInformation->hProcess;

	// Inject core dll again so it can start multiplayer game.
	if (! InjectDll(gameProcess, OS::GetModuleFullPath("Core.dll"))) {
		OS::ShowMessageBox("Error", "Failed to load multiplayer core into game process.", OS::EMessageBoxType::MESSAGE_BOX_TYPE_error);
		TerminateProcess(gameProcess, 0);
		return FALSE;
	}

	ResumeThread(lpProcessInformation->hThread);
	return result;
}

static FARPROC GetProcAddressEx(const HMODULE module, const char *const procName)
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

FARPROC CreateProcessKernel32 = nullptr;

void GameLauncherProxy::Init(void)
{
	const HMODULE kernel32 = GetModuleHandle("Kernel32.dll");
	CreateProcessKernel32 = GetProcAddressEx(kernel32, "CreateProcessW");

	OriginalCreateProcess = reinterpret_cast<CreateProcessW_t>(Hooking::InstallJmpHook(reinterpret_cast<Address_t>(CreateProcessKernel32), reinterpret_cast<Address_t>(MyCreateProcess)));
}

void GameLauncherProxy::Shutdown(void)
{
	Hooking::UninstallJmpHook(reinterpret_cast<Address_t>(CreateProcessKernel32), reinterpret_cast<const Address_t *>(OriginalCreateProcess));
	Hooking::Shutdown();
}

/* eof */
