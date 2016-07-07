// Copyright (C) 2016 by DVO Games

#pragma once

namespace OS {

enum class EMessageBoxType
{
	MESSAGE_BOX_TYPE_message,
	MESSAGE_BOX_TYPE_error
};

/**
 * Shows message box.
 *
 * @param[in]	title	The title.
 * @param[in]	message	The message.
 * @param[in]	messageBoxType The message box type. (optional)
 *
 * @see EMessageBoxType
 */
void ShowMessageBox(const char *const title, const char *const message, const EMessageBoxType messageBoxType = EMessageBoxType::MESSAGE_BOX_TYPE_message);

/**
 * OS level debug breakpoint implementation.
 */
void DebugBreakPoint_Impl(void);

} /* namespace OS */

/* EOF */
