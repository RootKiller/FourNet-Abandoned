// Copyright (C) 2016 by DVO Games

#pragma once

#include "Memory/MemFunctions.h"

#include "Strings.h"
#include "Singleton.h"

#include "AutoPtr.h"

#include <list>
#include <type_traits>

#include "File.h"
#include "BinaryFile.h"
#include "TextFile.h"

/**
 * File system class.
 */
class FileSystem : public ESingleton<FileSystem>
{
private:
	struct Folder
	{
		PathString	folderPath;
		AString64	target;
		bool		isReadOnly;

		Folder()
			: isReadOnly(false)
		{
		}

		Folder(const Folder& folder)
		{
			folderPath = folder.folderPath;
			target = folder.target;
			isReadOnly = folder.isReadOnly;
		}
	};

	std::list<Folder>		m_folders;

	const Folder*	GetFolder(const PathString& fileName) const;
public:
			FileSystem		();
			~FileSystem		();

	/**
	 * Mount system-level folder to the file system to the target location.
	 *
	 * @param[in] folderPath	Path of the folder.
	 * @param[in] target		The target where the folder will be mount.
	 * @param[in] isReadOnly	Is the folder read only?
	 * @return @c true if mount success @c false otherwise.
	 */
	bool	MountFolder		(const PathString& folderPath, const AString64& target, const bool isReadOnly = true);

	/**
	 * Check if file exists in any of the mounted archive or folder.
	 *
	 * @param[in] fileName The name of the file to be checked.
	 * @return @c true if file is found @c false otherwise.
	 */
	bool	FileExists		(const PathString& fileName);

	/**
	 * Check if folder exists in any of the mounted archive or folder.
	 *
	 * @param[in] folderName The name of the folder to be checked.
	 * @return @c true if folder is found @c false otherwise.
	 */
	bool	FolderExists	(const PathString& folderName);

	/**
	 * Open file.
	 *
	 * @tparam FILE_TYPE The type of the file class.
	 * @param[in] fileName	The name of the file. (Either OS-absolute path or engine FS path)
	 * @return Auto pointer to the file if file is opened - empty auto pointer otherwise.
	 */
	template <typename FILE_TYPE>
	AutoPtr<FILE_TYPE> OpenFile(const PathString& fileName, const unsigned flags = 0);
};

template <typename FILE_TYPE>
AutoPtr<FILE_TYPE> FileSystem::OpenFile(const PathString& fileName, const unsigned flags/* = 0*/)
{
	static_assert(std::is_base_of<File, FILE_TYPE>::value, "FILE_TYPE class must inherit from File class.");

	// NOTE: We are looking for a folder two times once in FileExists() function
	// and secondly using the GetFolder() method directly. In case this method
	// will be bottleneck in some situation this can be optimized.

	if (!(flags & FILE_OPEN_FLAG_create) && !FileExists(fileName)) {
		return AutoPtr<FILE_TYPE>();
	}

	PathString finalFileName;
	const Folder* const folder = GetFolder(fileName);
	if (folder) {
		if (folder->isReadOnly && (flags & FILE_OPEN_FLAG_create)) {
			Logger::Error("[File System] Tried to create file in read only folder.");
			return AutoPtr<FILE_TYPE>();
		}

		fileName.Replace(finalFileName, folder->target, folder->folderPath);
	}
	else {
		finalFileName = fileName;
	}
	return AutoPtr<FILE_TYPE>(new FILE_TYPE(finalFileName, flags));
}

/* eof */
