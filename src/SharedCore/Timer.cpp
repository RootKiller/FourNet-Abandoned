// Copyright (C) 2016 by DVO Games

#include "Timer.h"

#include "Compare.h"

#include "OS/OSTime.h"

#include "Logger.h"

static time_value lastFrameTime = 0;
static float frameDelta = 0.01f;

void Timer::BeginFrame(void)
{
	const time_value now = OS::GetTime();
	if (lastFrameTime > 0) {
		frameDelta = static_cast<float>(now - lastFrameTime) * TIMEVAL_TO_SECONDS;
	}
	lastFrameTime = now;
}

void Timer::EndFrame(void)
{
	// Noop.
}

float Timer::GetFrameDelta(void)
{
	return frameDelta;
}

time_value Timer::GetNow(void)
{
	return OS::GetTime();
}

float Timer::GetDiff(const time_value start)
{
	return static_cast<float>(GetNow() - start) * TIMEVAL_TO_SECONDS;
}

/* eof */
