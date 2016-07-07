// Copyright (C) 2016 by DVO Games

#include "Windows.h"

#include "Debug/Debug.h"

#include "OSTime.h"

#include "Nil.h"

namespace OS {

static double frequency = 0.0f; 

static bool isInitialized = false;

bool InitTime(void)
{
	ASSERT(!isInitialized);

	LARGE_INTEGER freq;
	if(!::QueryPerformanceFrequency(&freq)) {
		return false;
	}

	frequency = static_cast<double>(freq.QuadPart) / 1000000.0;

	isInitialized = true;
	return true;
}

void ShutdownTime(void)
{
	ASSERT(isInitialized);

	// No-op on windows.
}

time_value GetTime(void)
{
	if (!isInitialized) {
		return Nil();
	}

	LARGE_INTEGER counter;
	if (!::QueryPerformanceCounter(&counter)) {
		return Nil();
	}

	return static_cast<time_value>(static_cast<double>(counter.QuadPart) / frequency);
}

} /* namespace OS */

/* eof */
