// Copyright (C) 2016 by Rage MP Team

#include <Windows.h>

void CoreMain(void);
void CoreShutdown(void);

/**
 * DLL low-level entry point.
 *
 * @see https://msdn.microsoft.com/en-us/library/windows/desktop/ms682583(v=vs.85).aspx
 */
BOOL __stdcall DllMain(const HMODULE hinstDLL, const DWORD reason, const LPVOID reserved)
{
	switch (reason) {
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hinstDLL);

		CoreMain();
		break;

	case DLL_PROCESS_DETACH:
		CoreShutdown();
		break;
	}
	return TRUE;
}

/* eof */
