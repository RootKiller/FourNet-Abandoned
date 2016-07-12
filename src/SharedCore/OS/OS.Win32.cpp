// Copyright (C) 2016 by DVO Games

#include "OS.h"
#include "Windows.h"

namespace OS {

// Show message box.
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

// OS-level debug breakpoint call implementation used by Debugging code.
void DebugBreakPoint_Impl(void)
{
	RaiseException(EXCEPTION_BREAKPOINT, EXCEPTION_NONCONTINUABLE, 0, nullptr);
}

PathString GetModuleFullPath(const char *const moduleName)
{
	char exeFileName[MAX_PATH] = { 0 };
	GetModuleFileName(GetModuleHandle(moduleName), exeFileName, MAX_PATH);
	return PathString(exeFileName);
}

PathString GetModulePath(const char *const moduleName)
{
	const PathString fullPath(GetModuleFullPath(moduleName));
	const unsigned separator = fullPath.FindLast('\\');
	ASSERT(NotNil(separator));
	PathString path;
	path.SubStr(fullPath, 0, separator);
	return path;
}

} /* namespace OS */

/* EOF */
