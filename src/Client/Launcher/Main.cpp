/// Copyright (C) 2016 by Rage MP Team

#include <Windows.h>
#include <stdio.h>

#include "Strings.h"
#include "OS/OS.h"
#include "OS/OSFileSystem.h"

#include "Memory/Hooking/Injecting.h"

#include "Logger.h"

#include "ClientConsts.h"

namespace launcher {

/**
 * Handle error.
 *
 * Method prints error into log and displays os dialog.
 *
 * @param[in] errorMessage The error message to display.
 */
static void HandleError(const String &errorMessage)
{
	Logger::Error(errorMessage);
	OS::ShowMessageBox("Fatal Error", errorMessage, OS::EMessageBoxType::MESSAGE_BOX_TYPE_error);
}

/**
 * The return value from ResumeThread when it fails.
 *
 * If we trust enough MSDN thats the value they return when resume thread failed - they do not
 * mention any specific variable defined inside win32 so I prefer to put it here this way.
 */
const DWORD RESUME_THREAD_FAILED_VALUE = static_cast<DWORD>(-1);

/**
 * Launcher application main method.
 *
 * @param[in] argc Arguments count.
 * @param[in] argv Arguments value.
 */
int AppMain(int argc, char *argv[])
{
	// Patryk do: Get this path from registry (HKEY_LOCAL_MACHINE\SOFTWARE\WOW6432Node\Rockstar Games\Grand Theft Auto IV)
	// (WOW6432Node will likely not be there on 32bit os - better handle it explicitly so we will not put our hands into
	// cup of shit when microsoft changes something in registry handling)

	const PathString gamePath("E:\\Program Files (x86)\\Steam\\steamapps\\common\\Grand Theft Auto IV");

	PathString gameExePath;
	gameExePath.Format("%s\\%s%s", *gamePath, GAME_EXE_RELATIVE_PATH, GAME_LAUNCHER_EXE_NAME);

	Logger::Msg("Game executable: %s", *gameExePath);

	STARTUPINFO startupInfo = { 0 };
	PROCESS_INFORMATION processInformation = { 0 };
	startupInfo.cb = sizeof(startupInfo);

	if (GetFileAttributesA(gameExePath) == INVALID_FILE_ATTRIBUTES) {
		AString512 errorMessage;
		errorMessage.Format("Unable to find game .exe file.\n\nGame file: %s\nErrno: %u", *gameExePath, GetLastError());
		HandleError(errorMessage);
		return 0;
	}

	const LPSTR cmdLine = GetCommandLine();
	Logger::Msg("Command line: %s", cmdLine);

	if (!CreateProcessA(gameExePath, cmdLine, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, gamePath, &startupInfo, &processInformation)) {
		const unsigned lastError = GetLastError();
		AString1024 errorMessage;
		errorMessage.Format("Cannot create game process.\n\nGame file: %s\nDirectory: %s\n\n(Error code: %u)", *gameExePath, *gamePath, lastError);
		HandleError(errorMessage);
		return 0;
	}

	const PathString fourNetDllPath(OS::GetModulePath() + "\\" + CORE_DLL_NAME);

	if (GetFileAttributesA(fourNetDllPath) == INVALID_FILE_ATTRIBUTES) {
		AString512 errorMessage;
		errorMessage.Format("Cannot find %s file. Please try reinstalling the mod.\n\n%s\nErrno: %u", CORE_DLL_NAME, *fourNetDllPath, GetLastError());
		HandleError(errorMessage);
		TerminateProcess(processInformation.hProcess, 0);
		return 0;
	}

	const InjectResult injectResult = InjectDll(processInformation.hProcess, fourNetDllPath);
	if (injectResult != INJECT_RESULT_OK) {
		AString256 errorMessage;
		errorMessage.Format("Could not inject dll into the game process. Please try launching the mod again.\n\nErrno: %u, Errstr: %s", GetLastError(), InjectResultToString(injectResult));
		HandleError(errorMessage);
		TerminateProcess(processInformation.hProcess, 0);
		return 0;
	}

	if (ResumeThread(processInformation.hThread) == RESUME_THREAD_FAILED_VALUE) {
		AString256 errorMessage;
		errorMessage.Format("Could not resume process main thread. Please try launching the mod again.\n\nErrno: %u", GetLastError());
		HandleError(errorMessage);
		TerminateProcess(processInformation.hProcess, 0);
		return 0;
	}

	Logger::Msg("Everything went that smoth we will start party hard now.");
	return 1;
}

} /* namespace launcher */

/**
 * Launcher low-level entry point.
 *
 * @see https://msdn.microsoft.com/en-us/library/windows/desktop/ms633559(v=vs.85).aspx
 */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	PathString logPath(OS::GetModulePath() + "\\logs\\");

	if (!OS::CreateFolder(logPath)) {
		AString512 errorMessage;
		errorMessage.Format("Failed to create log folder. Try restarting mod if it does not help run mod as administrator.\n\n%s", *logPath);
		OS::ShowMessageBox("Fatal error", errorMessage, OS::EMessageBoxType::MESSAGE_BOX_TYPE_error);
		return 0;
	}

	logPath.AppendSafe("MultiplayerLauncher.log.txt");

	if (!Logger::Initialize(logPath, LogLevel::LOG_LEVEL_Standard)) {
		OS::ShowMessageBox("Fatal Error", "Failed to initialize logger.", OS::EMessageBoxType::MESSAGE_BOX_TYPE_error);
		return 0;
	}
	int appReturn = launcher::AppMain(__argc, __argv);
	Logger::Shutdown();
	return appReturn;
}

/* EOF */
