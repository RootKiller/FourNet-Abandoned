/// Copyright (C) 2016 by EFLC MP Team

namespace launcher {

/**
 * Set of game and mod specific constants.
 */

extern const char*	GAME_NAME				("Grand Theft Auto: Episodes From Liberty City");

// Firstly we inject into launcher and we perform some "hacky" skipping of the
// social-club launcher - after that the Core.dll is injecting itself again into
// the proper game process (e.g. EFLC.exe).
extern const char*	GAME_EXE_NAME			("LaunchEFLC.exe");

extern const char*	GAME_EXE_RELATIVE_PATH	("EFLC\\");
extern unsigned		GAME_APPID				(12220);

extern const char*	MOD_NAME				("EFLC Multiplayer");

} /* namespace launcher */

/* EOF */
