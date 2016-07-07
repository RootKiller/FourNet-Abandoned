// Copyright (C) 2016 by DVO Games

#pragma once

#include "Types.h"

const float TIMEVAL_TO_SECONDS = 1.0f / 1000000;

/**
 * Timer class used for calculating delta times between frames.
 */
class Timer
{
public:
	static void		BeginFrame	(void);
	static void		EndFrame	(void);

	static float	GetFrameDelta(void);

	static time_value GetNow	(void);
	static float	GetDiff		(const time_value start);
};

/* eof */
