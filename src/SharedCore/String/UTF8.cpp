// Copyright (C) 2016 by DVO Games

#include "Types.h"

#include "Strings.h"
#include "UTF8.h"

unsigned UTF8Decoder::GetCodePoint(const char* const string, unsigned& advance, const unsigned index)
{
	const uint8 first = static_cast<uint8>(string[index]);
	if (first < 0x80) {
		advance = 1;
		return first;
	}

	// Two octets used for character.
	// Pattern: 110xxxxx 10xxxxxx
	// First code point:  U+0080
	// Second code point: U+07FF
	if ((first >> 5) == 6) {
		const uint8 second = static_cast<uint8>(string[index + 1]);

		if (((second >> 6) & 2) != 2) {
			return Nil();
		}

		advance = 2;
		return static_cast<unsigned>((first & 0x1F) << 6) + (second & 0x3F);
	}

	// Three octets used for character.
	// Pattern: 1110xxxx 10xxxxxx 10xxxxxx
	// First code point:  U+0800
	// Second code point: U+FFFF
	if ((first >> 4) == 14)  {
		const uint8 second = static_cast<uint8>(string[index + 1]);
		const uint8 third  = static_cast<uint8>(string[index + 2]);

		if (((second >> 6) & 2) != 2) {
			return Nil();
		}

		if (((third >> 6) & 2) != 2) {
			return Nil();
		}

		advance = 3;
		return static_cast<unsigned>((first & 0xF) << 12) + ((second & 0x3F) << 6) + (third & 0x3F);
	}

	// Four octets used for character.
	// Pattern: 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
	// First code point:  U+10000
	// Second code point: U+1FFFFF
	if ((first >> 3) == 30) {
		const uint8 second = static_cast<uint8>(string[index + 1]);
		const uint8 third  = static_cast<uint8>(string[index + 2]);
		const uint8 forth  = static_cast<uint8>(string[index + 3]);

		if (((second >> 6) & 2) != 2) {
			return Nil();
		}

		if (((third >> 6) & 2) != 2) {
			return Nil();
		}

		if (((forth >> 6) & 2) != 2) {
			return Nil();
		}

		advance = 4;
		return static_cast<unsigned>((first & 0x7) << 18) + ((second & 0x3F) << 12) + ((third & 0x3F) << 6) + (forth & 0x3F);
	}
	return Nil();
}

unsigned UTF8Decoder::GetLength(const char* const string)
{
	unsigned length = 0;
	unsigned advance = 1;
	for (unsigned i = 0; i < StrLen(string); i += advance) {
		if (IsNil(GetCodePoint(string, advance, i))) {
			break;
		}
		++ length;
	}
	return length;
}


/* eof */
