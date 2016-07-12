// Copyright (C) 2016 by DVO Games

#pragma once

#include <cstring>

/**
 * Copy memory.
 *
 * @warning You have to take care about the eventual buffer overflows
 *          or reading the garbage.
 *
 * @param[out] destination
 * @param[in] source
 * @param[in] count How much bytes to copy?
 * @return The @a destination.
 */
template <typename TYPE>
static TYPE* MemCpy(TYPE* const destination, const TYPE* const source, const size_t count)
{
	::memcpy(destination, source, count);
	return destination;
}

/**
 * Set memory.
 *
 * @warning You have to take care about the eventual buffer overflows
 *          or reading the garbage.
 *
 * @param[out] destination
 * @param[in] value
 * @param[in] count How much bytes to set?
 * @return The @a destination.
 */
template <typename TYPE>
static TYPE* MemSet(TYPE* const destination, const int value, const size_t count)
{
	::memset(destination, value, count);
	return destination;
}

/**
 * Move memory.
 *
 * @param[out] destination
 * @param[in] value
 * @param[in] count How much bytes to move?
 * @return The @a destination.
 */
template <typename TYPE>
static TYPE* MemMove(TYPE* const destination, const TYPE* const source, const size_t count)
{
	::memmove(destination, source, count);
	return destination;
}

/**
 * Delete function working with standard object.
 *
 * @note Causes compilation error in case we want to remove not complete object.
 * @post It is responsibility of the caller to set pointer to nullptr after removing it.
 *
 * @param[in] object The object to be removed.
 */
template <typename TYPE>
static void DeleteCompleteObject(TYPE* const ptr)
{
	static_assert(sizeof(TYPE) > 0, "Tried to remove incomplete type object");

	delete ptr;
}

/**
 * Delete function working with arrays.
 *
 * @note Causes compilation error in case we want to remove not complete object.
 * @post It is responsibility of the caller to set pointer to nullptr after removing it.
 *
 * @param[in] array The array to be removed.
 */
template <typename TYPE>
static void DeleteCompleteArray(TYPE* const array)
{
	static_assert(sizeof(TYPE) > 0, "Tried to remove incomplete type array");

	delete[] array;
}

/* eof */
