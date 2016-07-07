// Copyright (C) 2016 by DVO Games

#include "File.h"

#include "Nil.h"

#include "TextFile.h"

TextFile::TextFile(const PathString& filePath, const unsigned flags)
	: File(filePath, flags)
{
	AString8 mode;
	
	if (flags & FILE_OPEN_FLAG_read_only) {
		mode = "r";
	}
	else if (flags & FILE_OPEN_FLAG_truncate) {
		mode = "w+";
	}
	else {
		mode = "a+";
	}

	m_file = fopen(filePath, mode);
	ASSERT(m_file);
}

bool TextFile::Write(const char *const string)
{
	ASSERT(m_file);
	fwrite(string, sizeof(char), strlen(string), m_file);

	fflush(m_file);
	return true;
}

bool TextFile::Write(const wchar_t *const string)
{
	ASSERT(m_file);
	fwrite(string, sizeof(wchar_t), wcslen(string), m_file);

	fflush(m_file);
	return true;
}

bool TextFile::Read(char *const string, size_t& length) const
{
	ASSERT(m_file);
	if (!fgets(string, static_cast<int>(length), m_file)) {
		return false;
	}

	length = StrLen(string);
	return true;
}

bool TextFile::Read(wchar_t *const string, size_t& length) const
{
	ASSERT(m_file);
	if (!fgetws(string, static_cast<int>(length), m_file)) {
		return false;
	}

	length = StrLen(string);
	return true;
}

/* eof */
