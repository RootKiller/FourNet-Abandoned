// Copyright (C) 2016 by DVO Games

#include "OSFileSystem.h"
#include "Windows.h"

namespace OS {

bool FileExists(const PathString& fileName)
{
	const DWORD fileAttributes = GetFileAttributesA(fileName);
	return fileAttributes != INVALID_FILE_ATTRIBUTES && fileAttributes != FILE_ATTRIBUTE_DIRECTORY;
}

bool FolderExists(const PathString& folderName)
{
	return GetFileAttributesA(folderName) == FILE_ATTRIBUTE_DIRECTORY;
}

} /* namespace OS */

/* eof */
