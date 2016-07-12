// Copyright (C) 2016 by Rage MP Team

#pragma once

#include <Windows.h>

enum InjectResult
{
	INJECT_RESULT_OK,

	INJECT_RESULT_DLL_NOT_FOUND,
	INJECT_RESULT_ALLOCATION_FAILED,
	INJECT_RESULT_WRITE_MEMORY_FAILED,
	INJECT_RESULT_WRITE_MEMORY_CORRUPTED,
	INJECT_RESULT_KERNEL32_NOT_AVAILABLE,
	INJECT_RESULT_LOAD_LIBRARY_NOT_AVAILABLE,
	INJECT_RESULT_REMOTE_THREAD_CREATION_FAILED,
};

/** Convert result into string */
const char *InjectResultToString(const InjectResult result);

/**
 * Inject DLL into process.
 *
 * @param[in] process Process handle.
 * @param[in] dllPath DLL path.
 * @return @c INJECT_RESULT_OK on case of injection succeeds error code otherwise.
 */
InjectResult InjectDll(const HANDLE process, const char *const dllPath);

/* EOF */
