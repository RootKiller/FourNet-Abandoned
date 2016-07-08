// Copyright (C) 2016 by DVO Games

#pragma once

#include "Strings.h"

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

/**
 * Get full path of the module. (with exe file name)
 *
 * @param[in] moduleName The name of the module. In case nullptr method returns path to the process.
 * @return Path to the module.
 */
PathString GetModuleFullPath(const char *const moduleName = nullptr);

/**
 * Get path of the module. (without exe file name)
 *
 * @param[in] moduleName The name of the module. In case nullptr method returns path to the process.
 * @return Path to the module.
 */
PathString GetModulePath(const char *const moduleName = nullptr);

} /* namespace OS */

/* EOF */
