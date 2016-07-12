// Copyright (C) 2016 by Rage MP Team

#pragma once

#include "Strings.h"
#include "Logger.h"
#include "OS/OS.h"

/**
 * Handle error.
 *
 * Method prints error into log and displays os dialog.
 *
 * @param[in] errorMessage The error message to display.
 */
static void HandleError(const String &errorMessage)
{
	Logger::Error(errorMessage);
	OS::ShowMessageBox("Fatal Error", errorMessage, OS::EMessageBoxType::MESSAGE_BOX_TYPE_error);
}

/* eof */
