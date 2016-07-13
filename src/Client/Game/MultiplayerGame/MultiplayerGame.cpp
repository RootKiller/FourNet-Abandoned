// Copyright (C) 2016 by Rage MP Team

#include "MultiplayerGame.h"

#include <Windows.h>

#include "OS/OS.h"

#include "Offsets.h"

#include "Logger.h"

#include "Memory/Hooking/Hooking.h"

#include "Hooks/GameHooks.h"


inline void InitDevConsole(void)
{
#ifdef DEBUG_BUILD
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
	freopen("CONIN$", "r", stdin);
#endif
}

inline void ShutdownDevConsole(void)
{
#ifdef DEBUG_BUILD
	FreeConsole();
#endif
}

void MultiplayerGame::Init(void)
{
	InitDevConsole();

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
	ShutdownDevConsole();
}

/* eof */
