// Copyright (C) 2016 by DVO Games

#pragma once

class UTF8Decoder
{
public:
	static unsigned GetCodePoint	(const char* const string, unsigned& advance, const unsigned index = 0);
	static unsigned GetLength		(const char* const string);
};

/* eof */
