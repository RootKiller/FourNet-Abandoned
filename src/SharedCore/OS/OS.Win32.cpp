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

} /* namespace OS */

/* EOF */
