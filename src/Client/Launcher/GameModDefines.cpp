/// Copyright (C) 2016 by Rage MP Team

namespace launcher {

/**
 * Set of game and mod specific constants.
 */

extern const char*	GAME_NAME				("Grand Theft Auto: IV");

// Firstly we inject into launcher and we perform some "hacky" skipping of the
// social-club launcher - after that the Core.dll is injecting itself again into
// the proper game process (e.g. GTAIV.exe).
extern const char*	GAME_EXE_NAME			("LaunchGTAIV.exe");

extern const char*	GAME_EXE_RELATIVE_PATH	("GTAIV\\");
extern unsigned		GAME_APPID				(12210);

extern const char*	MOD_NAME				("GTA:IV Multiplayer");

} /* namespace launcher */

/* EOF */
