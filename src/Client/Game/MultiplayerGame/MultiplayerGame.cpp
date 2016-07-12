// Copyright (C) 2016 by Rage MP Team

#include "MultiplayerGame.h"

#include <Windows.h>

#include "OS/OS.h"

#include "Offsets.h"

#include "Logger.h"

#include "Memory/Hooking/Hooking.h"

#include "Hooks/GameHooks.h"

void MultiplayerGame::Init(void)
{
	Hooking::Init();

	if (!Offsets::Init()) {
		TerminateProcess(GetCurrentProcess(), 0);
		return;
	}

	DEBUG_LOG("Installing game hooks..");
	GameHooks::Install();

	DEBUG_LOG("MultiplayerGame initialized");
}

void MultiplayerGame::Shutdown(void)
{
}

/* eof */
