// Copyright (C) 2016 by DVO Games

#pragma once

#include "AutoPtr.h"

#include "Types.h"
#include "Strings.h"

class File;

class BinaryFile : public File
{
private:
	friend class FileSystem;

			BinaryFile		(const PathString& filePath, const unsigned flags);
public:
	size_t	WriteByteSequence(const byte* const bytes, const size_t count);
	size_t	ReadByteSequence(byte* const bytes, const size_t count);
};

using BinaryFilePtr = AutoPtr<BinaryFile>;

/* eof */
