// Copyright (C) 2016 by DVO Games
#pragma once

/**
 * Select smaller value.
 *
 * @param[in] a		First value to compare.
 * @param[in] b		Second value to compare.
 * @return @a a in case it's smaller then @a b, @a b otherwise
 */
template <typename TYPE>
static TYPE Min(const TYPE a, const TYPE b)
{
	if (a < b) return a;
	return b;
}

/**
 * Select bigger value.
 *
 * @param[in] a		First value to compare.
 * @param[in] b		Second value to compare.
 * @return @a a in case it's bigger then @a b, @a b otherwise
 */
template <typename TYPE>
static TYPE Max(const TYPE a, const TYPE b)
{
	if (a > b) return a;
	return b;
}

/**
 * Clamp @a value between @a min and @a max.
 *
 * Version used for clamping r-values.
 *
 * @param[in]		value	Value to be clamped.
 * @param[in]		min		Minimum value.
 * @param[in]		max		Maximum value.
 * @return @a min in case @a value is smaller than @a min
 *         @a max in case @a value is bigger than @a max
 *         @value if it first the range.
 */
template <typename TYPE>
static TYPE Clamp(const TYPE value, const TYPE min, const TYPE max)
{
	if (value < min) return min;
	if (value > max) return max;
	return value;
}

/**
 * Find biggest value from given set.
 *
 * @param[in] values The set of the values to lookup from.
 * @param[in] count The count of the values.
 * @param[in] start The start index for the lookup. (0 by default)
 * @return The biggest value.
 */
template <typename TYPE>
static float FindBiggestFromSet(const TYPE* set, const size_t count, const size_t start = 0)
{
	TYPE biggest(0);
	for (size_t i = start; i < count; ++i) {
		if (set[i] > biggest) {
			biggest = set[i];
		}
	}
	return biggest;
}
/* eof */
