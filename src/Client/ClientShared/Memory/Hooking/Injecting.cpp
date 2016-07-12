// Copyright (C) 2016 by Rage MP Team

#include "Injecting.h"

#include "OS/OSFileSystem.h"

const char *InjectResultToString(const InjectResult result)
{
#define MAKE_CASE(resultValue) case resultValue: return #resultValue;
	switch (result) {
	MAKE_CASE(INJECT_RESULT_OK)

	MAKE_CASE(INJECT_RESULT_DLL_NOT_FOUND)
	MAKE_CASE(INJECT_RESULT_ALLOCATION_FAILED)
	MAKE_CASE(INJECT_RESULT_WRITE_MEMORY_FAILED)
	MAKE_CASE(INJECT_RESULT_WRITE_MEMORY_CORRUPTED)
	MAKE_CASE(INJECT_RESULT_KERNEL32_NOT_AVAILABLE)
	MAKE_CASE(INJECT_RESULT_LOAD_LIBRARY_NOT_AVAILABLE)
	MAKE_CASE(INJECT_RESULT_REMOTE_THREAD_CREATION_FAILED)
	}
#undef MAKE_CASE
	return "INJECT_RESULT_UNDEFINED";
}


InjectResult InjectDll(const HANDLE process, const char *const dllPath)
{
	if (!OS::FileExists(dllPath)) {
		return INJECT_RESULT_DLL_NOT_FOUND;
	}

	const size_t libPathLen = strlen(dllPath) + 1;

	void *const remoteLibPath = VirtualAllocEx(process, NULL, libPathLen, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	if (!remoteLibPath) {
		return INJECT_RESULT_ALLOCATION_FAILED;
	}

	SIZE_T bytesWritten = 0;
	if (!WriteProcessMemory(process, remoteLibPath, dllPath, libPathLen, &bytesWritten)) {
		VirtualFreeEx(process, remoteLibPath, sizeof(remoteLibPath), MEM_RELEASE);
		return INJECT_RESULT_WRITE_MEMORY_FAILED;
	}

	if (bytesWritten != libPathLen) {
		VirtualFreeEx(process, remoteLibPath, sizeof(remoteLibPath), MEM_RELEASE);
		return INJECT_RESULT_WRITE_MEMORY_CORRUPTED;
	}

	const HMODULE kernel32dll = GetModuleHandle("Kernel32");
	if (!kernel32dll) {
		VirtualFreeEx(process, remoteLibPath, sizeof(remoteLibPath), MEM_RELEASE);
		return INJECT_RESULT_KERNEL32_NOT_AVAILABLE;
	}

	const FARPROC pfnLoadLibraryA = GetProcAddress(kernel32dll, "LoadLibraryA");
	if (!pfnLoadLibraryA) {
		FreeModule(kernel32dll);
		VirtualFreeEx(process, remoteLibPath, sizeof(remoteLibPath), MEM_RELEASE);
		return INJECT_RESULT_LOAD_LIBRARY_NOT_AVAILABLE;
	}

	const HANDLE hThread = CreateRemoteThread(process, NULL, 0, (LPTHREAD_START_ROUTINE)pfnLoadLibraryA, remoteLibPath, 0, NULL);
	if (!hThread) {
		FreeModule(kernel32dll);
		VirtualFreeEx(process, remoteLibPath, sizeof(remoteLibPath), MEM_RELEASE);
		return INJECT_RESULT_REMOTE_THREAD_CREATION_FAILED;
	}

	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);

	FreeModule(kernel32dll);
	VirtualFreeEx(process, remoteLibPath, sizeof(remoteLibPath), MEM_RELEASE);
	return INJECT_RESULT_OK;
}

/* EOF */
