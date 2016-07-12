// Copyright (C) 2016 by Rage MP Team

#pragma once

/** Name of the core dynamic library */
static const char *const CORE_DLL_NAME("FourNet.dll");

static const char*	GAME_NAME				("Grand Theft Auto: IV");

// Firstly we inject into launcher and we perform some "hacky" skipping of the
// social-club launcher - after that the core dynamic library is injecting itself again into
// the proper game process (e.g. GTAIV.exe).
static const char*	GAME_LAUNCHER_EXE_NAME	("LaunchGTAIV.exe");

static const char*	GAME_EXE_NAME			("GTAIV.exe");
static const wchar_t* WC_GAME_EXE_NAME		(L"GTAIV.exe");

static const char*	GAME_EXE_RELATIVE_PATH	("GTAIV\\");
static unsigned		GAME_APPID				(12210);

static const char*	MOD_NAME				("FourNet");

/* eof */
