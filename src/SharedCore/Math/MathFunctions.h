// Copyright (C) 2016 by DVO Games

#pragma once

#include "Debug/Debug.h"
#include "Compare.h"

/**
 * Helper method making constant speed step of the value to the target.
 *
 * @param[in/out] value  The value to be stepped.
 * @param[in]     target The target value to reach.
 * @param[in]     speed  The speed of the step (must be greater than zero)
 */
template <typename TYPE>
static void StepTo(TYPE &value, const TYPE target, const TYPE speed = TYPE(1))
{
	ASSERT(speed > 0);

	const TYPE delta = Clamp<TYPE>(target - value, static_cast<TYPE>(-speed), static_cast<TYPE>(speed));
	value = value + delta;
}

/* eof */
