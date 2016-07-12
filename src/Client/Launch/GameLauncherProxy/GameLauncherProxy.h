// Copyright (C) 2016 by Rage MP Team

#pragma once

/**
 * The game launcher proxy class.
 *
 * Performs loading of the Core dynamic library
 * again when the game launcher starts game process.
 */
class GameLauncherProxy
{
public:
	/** Initializes game launcher proxy */
	static void			Init		(void);

	/** Shutdowns game launcher proxy */
	static void			Shutdown	(void);
};

/* eof */
