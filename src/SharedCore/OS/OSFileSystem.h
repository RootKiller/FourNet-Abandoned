// Copyright (C) 2016 by DVO Games

#pragma once

#include "Strings.h"

namespace OS 
{

/**
 * Check if file exists in system level file system.
 *
 * @param[in] fileName The path to be checked (can be relative to working directory)
 * @return @c true if file exists @c false otherwise.
 */
bool FileExists(const PathString& fileName);

/**
 * Check if folder exists in operating system level file system.
 *
 * @param[in] folderName The path to be checked (can be relative to working directory)
 * @return @c true if folder exists @c false otherwise.
 */
bool FolderExists(const PathString& folderName);

/**
 * Create folder if does not exists.
 *
 * @param[in] folderName The name of the folder to create.
 * @return @c true if folder was created or exists @c false otherwise.
 */
bool CreateFolder(const PathString& folderName);

} /* namespace OS */

/* eof */
