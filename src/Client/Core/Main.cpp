// Copyright (C) 2016 by Rage MP Team

#include "GameLauncherProxy.h"

#include "Strings.h"

#include <Windows.h>

#include "OS/OS.h"

/**
 * Get the game executable file name.
 *
 * @return The executable file name.
 */
PathString GetGameExeFileName(void)
{
	PathString path(OS::GetModuleFullPath());

	size_t slashPos = path.FindLast('/');
	if (IsNil(slashPos)) {
		slashPos = path.FindLast('\\');
	}

	ASSERT(NotNil(slashPos));
	PathString finalPath;
	finalPath.SubStr(path, slashPos + 1);
	return finalPath;
}


const char *LAUNCHER_EXE_NAME	("LaunchGTAIV.exe");
const char *GAME_EXE_NAME		("GTAIV.exe");

static bool		isProcessLauncher	= false;
static bool		isInitialized		= false;
/**
 * Method called when Core.dll is attached to the process.
 */
void CoreMain(void)
{
	const PathString &exeName = GetGameExeFileName();

	if (exeName == LAUNCHER_EXE_NAME) {
		GameLauncherProxy::Init();
		isProcessLauncher = true;
		isInitialized = true;
	}
	else if (exeName == GAME_EXE_NAME) {
		OS::ShowMessageBox("Game", "Game");
		isProcessLauncher = false;
		isInitialized = true;
	}
}

/**
 * Method called when Core.dll is detached from the process.
 */
void CoreShutdown(void)
{
	if (!isInitialized) {
		return;
	}

	if (isProcessLauncher) {
		GameLauncherProxy::Shutdown();
	}
	else {

	}
}

/* eof */
