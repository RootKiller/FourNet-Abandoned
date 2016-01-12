//
//         GTA EFLC Multiplayer
// Copyright (C) 2015 All rights reserved
//

#include <Windows.h>
#include <stdio.h>

#include "Strings.h"
#include "OS.h"

#include "Steam/SteamWrapper.h"
#include "Injecting.h"

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
	SteamWrapper steam;
	if (!steam.Init()) {
		return 0;
	}

	if (!steam.IsGameInstalled()) {
		AString128 errorMessage;
		errorMessage.Format("To run you need to have installed %s game.", GAME_NAME);
		os::ShowMessageBox("Fatal Error", errorMessage, os::EMessageBoxType::MESSAGE_BOX_TYPE_error);
		return 0;
	}

	PathString gamePath;
	steam.GetGameInstallPath(gamePath);
	if (gamePath.IsEmpty()) {
		os::ShowMessageBox("Fatal Error", "Unable to find game installation path.", os::EMessageBoxType::MESSAGE_BOX_TYPE_error);
		return 0;
	}

	PathString gameExePath;
	gameExePath.Format("%s\\%s%s", *gamePath, GAME_EXE_RELATIVE_PATH, GAME_EXE_NAME);

	STARTUPINFO startupInfo = { 0 };
	PROCESS_INFORMATION processInformation = { 0 };
	startupInfo.cb = sizeof(startupInfo);

	SetEnvironmentVariableA("SteamAppID", STRINGIZE(GAME_APPID));

	if (GetFileAttributesA(gameExePath) == INVALID_FILE_ATTRIBUTES) {
		os::ShowMessageBox("Fatal Error", "Unable to find game .exe file.\n\nGame file: " + gameExePath, os::EMessageBoxType::MESSAGE_BOX_TYPE_error);
		return 0;
	}

	if (!CreateProcessA(gameExePath, NULL, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, gamePath, &startupInfo, &processInformation)) {
		const unsigned lastError = GetLastError();
		os::ShowMessageBox("Fatal Error", "Cannot create game process.\n\nGame file: " + gameExePath + "\nDirectory: "+ gamePath +"\n\n(Error code: " + lastError + ")", os::EMessageBoxType::MESSAGE_BOX_TYPE_error);
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
		os::ShowMessageBox("Fatal Error", "Cannot find Core.dll file. Please try reinstalling the mod.", os::EMessageBoxType::MESSAGE_BOX_TYPE_error);
		TerminateProcess(processInformation.hProcess, 0);
		return 0;
	}

	if (!InjectDll(processInformation.hProcess, path)) {
		os::ShowMessageBox("Fatal Error", "Could not inject dll into the game process. Please try launching the game again.", os::EMessageBoxType::MESSAGE_BOX_TYPE_error);
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
