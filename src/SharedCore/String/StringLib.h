// Copyright (C) 2016 by DVO Games

// ----------------------------------------------------------
//
// Template-based string library.
//
// Wraps all the C string methods using the
// modern C++ coding methods.
//
// Supports char and wchar_t (char16 and char32 todo)
//
// If you decided to look at this you may be interested in String class
// which is stored inside Shared/String/String.h file.
//

#pragma once

#include <stdarg.h>
#include <string>

template <typename TYPE>
static unsigned StrLen(const TYPE *const str);

template <typename TYPE>
static unsigned StrNLen(const TYPE *const str, const unsigned limit);

template <typename TYPE>
static void StrCpy(TYPE *const dest, const TYPE *const source);

template <typename TYPE>
static void StrNCpy(TYPE *const dest, const TYPE *const source, const unsigned count);

template <typename TYPE>
static void StrCat(TYPE *const dest, const TYPE *const source);

template <typename TYPE>
static const TYPE *StrStr(const TYPE *const a, const TYPE *const b);

template <typename TYPE>
static const TYPE *StrChr(const TYPE *const a, const TYPE b);

template <typename TYPE>
static const TYPE *StrRChr(const TYPE *const a, const TYPE b);

template <typename TYPE>
static int StrCmp(const TYPE *const a, const TYPE *const b);

template <typename TYPE>
static int StrNCmp(const TYPE *const a, const TYPE *const b, const unsigned count);

template <typename TYPE>
static int VSCPrintF(const TYPE *const buffer, va_list argList);

template <typename TYPE>
static int SPrintF(TYPE *const dest, const TYPE *const buffer, va_list argList);

template <>
static unsigned StrLen<char>(const char *const str)
{
	return static_cast<unsigned>(strlen(str));
}

template <>
static unsigned StrLen<wchar_t>(const wchar_t *const str)
{
	return static_cast<unsigned>(wcslen(str));
}

template <>
static unsigned StrNLen<char>(const char *const str, const unsigned limit)
{
	return static_cast<unsigned>(strnlen(str, static_cast<size_t>(limit)));
}

template <>
static unsigned StrNLen<wchar_t>(const wchar_t *const str, const unsigned limit)
{
	return static_cast<unsigned>(wcsnlen(str, static_cast<size_t>(limit)));
}

template <>
static void StrCpy(char *const dest, const char *const source)
{
	strcpy(dest, source);
}

template <>
static void StrCpy(wchar_t *const dest, const wchar_t *const source)
{
	wcscpy(dest, source);
}

template <>
static void StrNCpy(char *const dest, const char *const source, const unsigned count)
{
	strncpy(dest, source, static_cast<size_t>(count));
}

template <>
static void StrNCpy(wchar_t *const dest, const wchar_t *const source, const unsigned count)
{
	wcsncpy(dest, source, static_cast<size_t>(count));
}

template <>
static void StrCat(char *const dest, const char *const source)
{
	strcat(dest, source);
}

template <>
static void StrCat(wchar_t *const dest, const wchar_t *const source)
{
	wcscat(dest, source);
}

template <>
static const char *StrStr(const char *const a, const char *const b)
{
	return strstr(a, b);
}

template <>
static const wchar_t *StrStr(const wchar_t *const a, const wchar_t *const b)
{
	return wcsstr(a, b);
}

template <>
static const char *StrChr(const char *const a, const char b)
{
	return strchr(a, static_cast<const int>(b));
}

template <>
static const wchar_t *StrChr(const wchar_t *const a, const wchar_t b)
{
	return wcschr(a, static_cast<const int>(b));
}

template <>
static const char *StrRChr(const char *const a, const char b)
{
	return strrchr(a, static_cast<const int>(b));
}

template <>
static const wchar_t *StrRChr(const wchar_t *const a, const wchar_t b)
{
	return wcsrchr(a, static_cast<const int>(b));
}

template <>
static int StrCmp(const char *const a, const char *const b)
{
	return strcmp(a, b);
}

template <>
static int StrCmp(const wchar_t *const a, const wchar_t *const b)
{
	return wcscmp(a, b);
}

template <>
static int StrNCmp(const char *const a, const char *const b, const unsigned length)
{
	return strncmp(a, b, static_cast<size_t>(length));
}

template <>
static int StrNCmp(const wchar_t *const a, const wchar_t *const b, const unsigned length)
{
	return wcsncmp(a, b, static_cast<size_t>(length));
}

template <>
static int VSCPrintF(const char *const buffer, va_list argList)
{
	return _vscprintf(buffer, argList);
}

template <>
static int VSCPrintF(const wchar_t *const buffer, va_list argList)
{
	return _vscwprintf(buffer, argList);
}

template <>
static int SPrintF(char *const dest, const char *const buffer, va_list argList)
{
	return vsprintf(dest, buffer, argList);
}

template <>
static int SPrintF(wchar_t *const dest, const wchar_t *const buffer, va_list argList)
{
	return vswprintf(dest, buffer, argList);
}

/** The length of the color code #RRGGBB */
const unsigned COLOR_CODE_LENGTH = 7;

/**
 * Check if given string is #RRGGBB color code.
 *
 * @param[in] buffer The buffer to check.
 * @return @c true in case given buffer is color code @c false otherwise.
 */
template <typename TYPE>
static bool IsColorCode(TYPE *const buffer)
{
	if (StrNLen(buffer, COLOR_CODE_LENGTH) < COLOR_CODE_LENGTH) {
		return false;
	}

	if (buffer[0] != '#') {
		return false;
	}

	for (size_t i = 1; i < COLOR_CODE_LENGTH; ++i) {
		const char currentChar = buffer[i];
		if (!isxdigit(currentChar)) {
			return false;
		}
	}
	return true;
}

/* EOF */
