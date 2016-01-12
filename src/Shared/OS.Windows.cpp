/// Copyright (C) 2016 by EFLC MP Team

/**
 * Mirosoft Windows system layer implementation.
 */

#include "OS.h"

#include <Windows.h>

namespace os {

//! Get current module path.
extern "C" IMAGE_DOS_HEADER __ImageBase;
PathString GetCurrentModulePath(void)
{
	const HINSTANCE moduleInstance = reinterpret_cast<HINSTANCE>(&__ImageBase);

	char currentPath[MAX_PATH] = { 0 };
	GetModuleFileName(moduleInstance, currentPath, MAX_PATH);
	PathString result(currentPath);
	const unsigned pathSepratorPos = result.FindLast('\\');
	ASSERT(NotNil(pathSepratorPos));
	result.CutAt(pathSepratorPos);
	return result;
}

//! Show message box.
void ShowMessageBox(const char *const title, const char *const message, const EMessageBoxType messageBoxType)
{
	UINT flags = 0;
	switch (messageBoxType) {
	case EMessageBoxType::MESSAGE_BOX_TYPE_error:
		{
			flags |= MB_ICONERROR;
		} break;
	case EMessageBoxType::MESSAGE_BOX_TYPE_message:
		{
			flags = 0;
		} break;
	}
	MessageBoxA(NULL, message, title, flags);
}

//! OS-level debug breakpoint call implementation used by Debugging code.
void DebugBreakPoint_Impl(void)
{
	RaiseException(EXCEPTION_BREAKPOINT, EXCEPTION_NONCONTINUABLE, 0, nullptr);
}

}

/* EOF */
