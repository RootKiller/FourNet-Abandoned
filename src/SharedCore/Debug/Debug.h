// Copyright (C) 2016 by DVO Games

#pragma once

#include "Defines.h"

typedef bool(*CustomAssertHandler)(const char *const expression, const char *const message, const char *const fn, const char *const file, const size_t line);

/**
 * Set custom assert handler.
 *
 * @param[in] customAssertHandler The custom assert handler method pointer, \c NULL means unset.
 */
void SetCustomAssertHandler(CustomAssertHandler *const customAssertHandler);

namespace detail {
	void AssertHandler(const char *const expression, const char *const message, const char *const fn, const char *const file, const unsigned line);
} /* namespace detail */

#ifdef DEBUG_BUILD
#	define ASSERT(expr)				((!!(expr)) ? static_cast<void>(0) : detail::AssertHandler(STRINGIZE(expr), nullptr, FUNCTION_NAME, __FILE__, __LINE__))
#	define ASSERT_MSG(expr, message) ((!!(expr)) ? static_cast<void>(0) : detail::AssertHandler(STRINGIZE(expr), message, FUNCTION_NAME, __FILE__, __LINE__))
#else
#	define ASSERT(expr)
#	define ASSERT_MSG(expr, message)
#endif

/* EOF */
