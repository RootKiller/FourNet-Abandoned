/// Copyright (C) 2016 by Rage MP Team

#include <Windows.h>
#include <stdio.h>

#include "Strings.h"
#include "OS/OS.h"

#include "Memory/Hooking/Injecting.h"

namespace launcher {

extern const char* GAME_NAME;
extern const char* GAME_EXE_RELATIVE_PATH;
extern const char* GAME_EXE_NAME;

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
	gameExePath.Format("%s\\%s%s", *gamePath, GAME_EXE_RELATIVE_PATH, GAME_EXE_NAME);

	STARTUPINFO startupInfo = { 0 };
	PROCESS_INFORMATION processInformation = { 0 };
	startupInfo.cb = sizeof(startupInfo);

	if (GetFileAttributesA(gameExePath) == INVALID_FILE_ATTRIBUTES) {
		OS::ShowMessageBox("Fatal Error", "Unable to find game .exe file.\n\nGame file: " + gameExePath, OS::EMessageBoxType::MESSAGE_BOX_TYPE_error);
		return 0;
	}

	const LPSTR cmdLine = GetCommandLine();
	if (!CreateProcessA(gameExePath, cmdLine, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, gamePath, &startupInfo, &processInformation)) {
		const unsigned lastError = GetLastError();
		AString1024 errorMessage;
		errorMessage.Format("Cannot create game process.\n\nGame file: %s\nDirectory: %s\n\n(Error code: %u)", *gameExePath, *gamePath, lastError);
		OS::ShowMessageBox("Fatal Error", errorMessage, OS::EMessageBoxType::MESSAGE_BOX_TYPE_error);
		return 0;
	}

	char cPath[MAX_PATH] = { 0 };
	GetModuleFileNameA(NULL, cPath, MAX_PATH);
	AFixedString<MAX_PATH> path(cPath);

	const unsigned lastPathSeparator = path.FindLast('\\');
	ASSERT(NotNil(lastPathSeparator));
	path.CutAt(lastPathSeparator);
	path += "\\Core.dll";

	if (GetFileAttributesA(path) == INVALID_FILE_ATTRIBUTES) {
		OS::ShowMessageBox("Fatal Error", "Cannot find Core.dll file. Please try reinstalling the mod.", OS::EMessageBoxType::MESSAGE_BOX_TYPE_error);
		TerminateProcess(processInformation.hProcess, 0);
		return 0;
	}

	if (!InjectDll(processInformation.hProcess, path)) {
		OS::ShowMessageBox("Fatal Error", "Could not inject dll into the game process. Please try launching the game again.", OS::EMessageBoxType::MESSAGE_BOX_TYPE_error);
		TerminateProcess(processInformation.hProcess, 0);
		return 0;
	}

	ResumeThread(processInformation.hThread);
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
	return launcher::AppMain(__argc, __argv);
}

/* EOF */
