// Copyright (C) 2016 by DVO Games

#include "File.h"

File::File(const PathString& fileName, const unsigned flags)
	: m_file(nullptr)
{
}

File::~File()
{
	if (m_file) {
		fclose(m_file);
		m_file = nullptr;
	}
}

size_t File::GetSize(void) const
{
	ASSERT(m_file);
	fpos_t tmp;
	if (fgetpos(m_file, &tmp) != 0) {
		return 0;
	}
	fseek(m_file, 0, SEEK_END);
	const long size = ftell(m_file);
	fseek(m_file, static_cast<long>(tmp), SEEK_SET);
	return static_cast<size_t>(size);
}

size_t File::GetPos(void) const
{
	ASSERT(m_file);
	fpos_t pos;
	if (fgetpos(m_file, &pos) != 0) {
		return 0;
	}
	return static_cast<size_t>(pos);
}

bool File::Seek(const long pos, const SeekMode mode)
{
	ASSERT(m_file);
	return fseek(m_file, pos, static_cast<int>(mode)) != 0;
}

bool File::ResetPos(void)
{
	ASSERT(m_file);
	rewind(m_file);
	return true;
}

bool File::IsEof(void) const
{
	ASSERT(m_file);
	return feof(m_file) != 0;
}

bool File::NotEof(void) const
{
	ASSERT(m_file);
	return feof(m_file) == 0;
}

bool File::IsEmpty(void) const
{
	return GetSize() == 0;
}

bool File::NotEmpty(void) const
{
	return GetSize() > 0;
}

/* eof */
