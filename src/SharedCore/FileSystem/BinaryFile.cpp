// Copyright (C) 2016 by DVO Games

#include "File.h"

#include "BinaryFile.h"

BinaryFile::BinaryFile(const PathString& filePath, const unsigned flags)
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

	mode.Append('b');

	m_file = fopen(filePath, mode);
	ASSERT(m_file);
}

size_t BinaryFile::WriteByteSequence(const byte* const bytes, const size_t count)
{
	ASSERT(m_file);
	return fwrite(bytes, 1, count, m_file);
}

size_t BinaryFile::ReadByteSequence(byte* const bytes, const size_t count)
{
	ASSERT(m_file);
	return fread(bytes, 1, static_cast<unsigned>(count), m_file);
}

/* eof */
