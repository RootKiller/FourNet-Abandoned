// Copyright (C) 2016 by Rage MP Team

#include "MultiplayerGame.h"

#include <Windows.h>

#include "OS/OS.h"

#include "Offsets.h"

#include "Logger.h"

#include "Memory/Hooking/Hooking.h"

void MultiplayerGame::Init(void)
{
	Hooking::Init();

	if (!Offsets::Init()) {
		TerminateProcess(GetCurrentProcess(), 0);
		return;
	}

	Logger::Msg("Allocate memory: %p / %p", Offsets::Base::AllocateMemory, Offsets::ResolveAddress(Offsets::Base::AllocateMemory));

	char workingDir[MAX_PATH] = { 0 };
	GetCurrentDirectory(MAX_PATH, workingDir);
	Logger::Msg("[FS] Working dir: %s", workingDir);
}

void MultiplayerGame::Shutdown(void)
{
}

/* eof */
