/// Copyright (C) 2016 by EFLC MP Team

#include "Debug.h"
#include "OS.h"

#include <stdio.h>

namespace debug {

/**
 * Custom assert handler pointer.
 */
CustomAssertHandler* g_customAssertHandler = NULL;

void SetCustomAssertHandler(CustomAssertHandler *const customAssertHandler)
{
	g_customAssertHandler = customAssertHandler;
}

namespace detail {
/**
 * Internal assert handler
 *
 * @param[in] expression The stringized expression.
 * @param[in] message The user defined message.
 * @param[in] fn The function name.
 * @param[in] file The file name.
 * @param[in] line The line number.
 */
void AssertHandler(const char *const expression, const char *const message, const char *const fn, const char *const file, const size_t line)
{
	if (g_customAssertHandler && (*g_customAssertHandler)(expression, message, fn, file, line)) {
		return;
	}

	char assertionMessage[512] = { 0 };

	if (message) {
		// Message variant

		sprintf(
			assertionMessage,
			"An assertion error has been occured.\n\n"
			"Expression:\n\t%s\n" /* expression */
			"Function:\n\t%s\n" /* fn */
			"File:\n\t%s\n" /* file */
			"Line:\n\t%u\n" /* line */
			"Message:\n\t%s\n" /* message */
			"", expression, fn, file, line, message
		);
	}
	else {
		// No message variant

		sprintf(
			assertionMessage,
			"An assertion error has been occured.\n\n"
			"Expression:\n\t%s\n" /* expression */
			"Function:\n\t%s\n" /* fn */
			"File:\n\t%s\n" /* file */
			"Line:\n\t%u\n" /* line */
			"", expression, fn, file, line
		);
	}

	os::ShowMessageBox("Assertion error", assertionMessage, os::EMessageBoxType::MESSAGE_BOX_TYPE_error);
	os::DebugBreakPoint_Impl();
}

} /* namespace detail */
} /* namespace debug */

/* EOF */
