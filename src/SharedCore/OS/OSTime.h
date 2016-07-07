// Copyright (C) 2016 by DVO Games

#pragma once

#include "Types.h"

namespace OS {

/**
 * Initialize OS-layer for handling the time.
 *
 * @return @c true in case initalization succeeds @c false otherwise.
 */
bool InitTime(void);

/**
 * Shutdown OS-layer handling the time.
 */
void ShutdownTime(void);

/**
 * Get current time value in micro-seconds (using OS-level high resolution timer).
 *
 * @return Time value in micro seconds or @c Nil in case time layer
 *         is not initialized by InitTime() call or querying time failed.
 */
time_value GetTime(void);

} /* namespace OS */

/* eof */
