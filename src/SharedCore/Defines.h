// Copyright (C) 2016 by DVO Games

#pragma once

#ifdef OS_WINDOWS
#	include "Config.Win.h"
#else
#	error "No system config found"
#endif

#include "PrintMacros.h"

/**
 * @def Stringize macro.
 *
 * Example:
 * @code
 * const int MAJOR_VERSION = 2;
 * const int MINOR_VERSION = 1;
 *
 * printf("Engine version: " STRINGIZE(MAJOR_VERSION) "." STRINGIZE(MINOR_VERSION));
 * @codeend
 */
#ifndef STRINGIZE
#	define _STRINGIZE_HELPER(a) #a
#	define STRINGIZE(a) _STRINGIZE_HELPER(a)
#endif

/**
 * @def OS independed function name macro.
 */
#ifndef FUNCTION_NAME
#	ifdef OS_WINDOWS
#		define FUNCTION_NAME __FUNCTION__
#	else
#		error "TODO : Implement FUNCTION_NAME macro in " __FILE__ "
#	endif
#endif

/**
 * @def Super class.
 */
#ifndef SUPER_CLASS
#  define SUPER_CLASS(className) private:\
	typedef className Super;

#endif

/**
 * @def Calculate length of the non-empty C array.
 */
#ifndef ARRAY_LENGTH
#	define ARRAY_LENGTH(arr) (sizeof(arr) / sizeof(arr[0]))
#endif

/**
 * @def Concats two symbols.
 */
#ifndef CONCAT
#	define HELPER___CONCAT(a, b) a##b
#	define CONCAT(a, b) HELPER___CONCAT(a, b)
#endif

/* eof */
