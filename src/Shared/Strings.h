/// Copyright (C) 2016 by EFLC MP Team
#pragma once

#include "Allocators.h"

#include "Types.h"

#include "String/StringLib.h"
#include "String/String.h"

//! Path string.
typedef AFixedString<260>		PathString;

/**
 * Fixed string types.
 */
//@{
typedef AFixedString<1 + 1>		AString1;
typedef AFixedString<2 + 1>		AString2;
typedef AFixedString<4 + 1>		AString4;
typedef AFixedString<8 + 1>		AString8;
typedef AFixedString<16 + 1>	AString16;
typedef AFixedString<32 + 1>	AString32;
typedef AFixedString<64 + 1>	AString64;
typedef AFixedString<128 + 1>	AString128;
typedef AFixedString<256 + 1>	AString256;
typedef AFixedString<512 + 1>	AString512;
typedef AFixedString<1024 + 1>	AString1024;
typedef AFixedString<2048 + 1>	AString2048;
//@}

/* EOF */