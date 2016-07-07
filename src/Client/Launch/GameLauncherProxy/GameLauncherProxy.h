// Copyright (C) 2016 by Rage MP Team

#pragma once

/**
 * The game launcher proxy class.
 *
 * Perfroms loading of the Core dynamic library
 * again when the game launcher starts game process.
 */
class GameLauncherProxy
{
public:
	static void			Init		(void);
	static void			Shutdown	(void);
};

/* eof */
