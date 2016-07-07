// Copyright (C) 2016 by DVO Games

#pragma once

#include "Strings.h"

enum SeekMode
{
	SEEK_MODE_BEGINNING = 0,
	SEEK_MODE_CURRENT   = 1,
	SEEK_MODE_END       = 2
};

enum FileOpenFlags
{
	FILE_OPEN_FLAG_read_only = 1,

	FILE_OPEN_FLAG_truncate   = 2,

	// Handled by file system.
	FILE_OPEN_FLAG_create    = 4
};

class File
{
protected:
	// File pointer.
	FILE				*m_file;

			File		(const PathString& filePath, const unsigned flags);
	virtual	~File		();
public:

	// Get total size of the file.
	virtual size_t GetSize(void) const;

	// Get current read/write position of the file.
	virtual size_t GetPos(void) const;

	/**
	 * Seek reading/writing position.
	 *
	 * @param[in] pos The new position (can be negative)
	 * @param[in] mode The seek mode.
	 * @return @c true in case seek success @c false otherwise.
	 */
	virtual bool Seek	(const long pos, const SeekMode mode);

	/**
	 * Reset read/write position.
	 *
	 * @return @c true in case seek success @c false otherwise.
	 */
	virtual bool ResetPos(void);

	// Is it an end of the file?
	virtual	bool IsEof	(void) const;

	// Is it not an end of the file?
	virtual bool NotEof	(void) const;

	// Is the file empty?
	virtual bool IsEmpty (void) const;

	// Does the file have any content?
	virtual bool NotEmpty (void) const;
};
/* eof */
