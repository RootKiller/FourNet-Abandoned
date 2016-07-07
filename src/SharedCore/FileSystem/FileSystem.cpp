// Copyright (C) 2016 by DVO Games

#include "FileSystem.h"

#include "Logger.h"

#include "OS/OSFileSystem.h"

FileSystem::FileSystem()
	: m_folders()
{
}

FileSystem::~FileSystem()
{
}

const FileSystem::Folder* FileSystem::GetFolder(const PathString& fileName) const
{
	for (const Folder& folder : m_folders) {
		if (!fileName.StartsWith(folder.target)) {
			continue;
		}

		return &folder;
	}
	return nullptr;
}

bool FileSystem::MountFolder(const PathString& folderPath, const AString64& target, const bool isReadOnly)
{
	// The target format must be /name/../../
	ASSERT(target.StartsWith("/") && target.EndsWith("/"));

	if (! OS::FolderExists(folderPath)) {
		return false;
	}

	Folder folder;
	folder.folderPath = folderPath;
	folder.target = target;
	folder.isReadOnly = isReadOnly;

	m_folders.push_back(std::move(folder));

	Logger::Msg("[FileSystem] Folder %s has been mount at %s.%s", *folderPath, *target, isReadOnly?" (read only)":"");
	return true;
}

bool FileSystem::FileExists(const PathString& fileName)
{
	const Folder *const folder = GetFolder(fileName);
	if (! folder) {
		return OS::FileExists(fileName);
	}

	PathString _fileName;
	fileName.Replace(_fileName, folder->target, folder->folderPath);
	return OS::FileExists(_fileName);
}

bool FileSystem::FolderExists(const PathString& folderName)
{
	const Folder *const folder = GetFolder(folderName);
	if (! folder) {
		return OS::FolderExists(folderName);
	}

	PathString _folderName;
	folderName.Replace(_folderName, folder->target, folder->folderPath);
	return OS::FolderExists(_folderName);
}

/* eof */
