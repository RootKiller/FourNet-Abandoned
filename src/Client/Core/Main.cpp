// Copyright (C) 2016 by Rage MP Team

#include "GameLauncherProxy.h"

#include "Strings.h"

#include <Windows.h>

#include "OS/OS.h"
#include "OS/OSFileSystem.h"

#include "Memory/Hooking/Hooking.h"
#include "Memory/MemFunctions.h"

#include "Logger.h"

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
	PathString logPath = OS::GetModulePath("FourNet.dll");
	logPath.AppendSafe("\\logs\\");

	if (!OS::CreateFolder(logPath)) {
		AString512 errorMessage;
		errorMessage.Format("Failed to create log folder. Try restarting mod if it does not help run mod as administrator.\n\n%s", *logPath);
		OS::ShowMessageBox("Fatal error", errorMessage, OS::EMessageBoxType::MESSAGE_BOX_TYPE_error);

		TerminateProcess(GetCurrentProcess(), 0);
		return;
	}

	const PathString &exeName = GetGameExeFileName();

	if (exeName == LAUNCHER_EXE_NAME) {
		logPath.AppendSafe("MultiplayerLaunch.log.txt");
		Logger::Initialize(logPath, LOG_LEVEL_Standard);

		GameLauncherProxy::Init();
		isProcessLauncher = true;
		isInitialized = true;
	}
	else if (exeName == GAME_EXE_NAME) {
		isProcessLauncher = false;
		isInitialized = true;

		const Address_t base = (unsigned)GetModuleHandle(NULL) - 0x400000;

		logPath.AppendSafe("MultiplayerGame.log.txt");
		Logger::Initialize(logPath, LOG_LEVEL_Standard);

		Logger::Msg("MultiplayerGame (Base: %p, Module: %s)", base, *OS::GetModuleFullPath());

		char workingDir[MAX_PATH] = { 0 };
		GetCurrentDirectory(MAX_PATH, workingDir);
		Logger::Msg("[FS] Working dir: %s", workingDir);

		Hooking::Init();
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
