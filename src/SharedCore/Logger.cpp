// Copyright (C) 2016 by DVO Games

#include <cstdio>
#include <cstring>

#include <cstdarg>

#include <ctime>

#include "Debug/Debug.h"

#include "Logger.h"

#ifdef OS_WINDOWS
const char *EOL("\r\n");
#else
const char *EOL("\n");
#endif

/**
 * Log file handler.
 */
static FILE *g_logFile = nullptr;

/**
 * Default log file name.
 */
static const char *DEFAULT_LOG_FILENAME("engine.log");

/**
 * Log level.
 */
static LogLevel g_logLevel = LOG_LEVEL_Standard;

bool Logger::Initialize(const char *const logFileName, const LogLevel level)
{
	// In case this assert fails then you are probably trying to initialize the
	// logger twice. It is not allowed.
	ASSERT(!g_logFile);

	const size_t logFileNameLen = logFileName ? strlen(logFileName) : 0;
	ASSERT(logFileNameLen < 260);

	char finalFileName[260] = { 0 };

	const bool logFileNameValid = logFileName && (logFileNameLen > 0);
	if (!logFileNameValid) {
		strcpy(finalFileName, DEFAULT_LOG_FILENAME);
	}
	else {
		strcpy(finalFileName, logFileName);
	}

	g_logLevel = level;

	g_logFile = fopen(finalFileName, "w+");
	ASSERT(g_logFile);

	if (!g_logFile) {
		printf("[Logger] Unable to open log file. (%s)\n", finalFileName);
		return false;
	}

	time_t timer;
	time(&timer);
	struct tm *const timeinfo = localtime(&timer);

	static const size_t timeBufferData = 20;
	char timeData[timeBufferData] = { 0 };
	strftime(timeData, timeBufferData, "%d-%m-%Y %H:%M:%S", timeinfo);

	Msg("Logger started - %s", timeData, finalFileName);

	return true;
}

void Logger::Shutdown(void)
{
	if (g_logFile) {
		fclose(g_logFile);
		g_logFile = nullptr;
	}
}

// Print current timestamp.
static void PrintTimestamp(void)
{
	time_t timer;
	time(&timer);
	struct tm *const timeinfo = localtime(&timer);

	static const size_t timeBufferData = 20;
	char timeData[timeBufferData] = { 0 };
	strftime(timeData, timeBufferData, "%d-%m-%Y %H:%M:%S", timeinfo);

	fprintf(g_logFile, "[%s] ", timeData);
	printf("[%s] ", timeData);
}

/// Print severity into file and system console.
static void PrintSeverity(const char *const severity)
{
	fputs(severity, g_logFile);
	printf("%s", severity);
}

/// Print end of line into log file and system console.
static void PrintEol(void)
{
	// NOTE: On Windows fputs and other stdio methods are adding return of
	// the cariage byte automatically when LF is added.
	fputs("\n", g_logFile);

	printf("%s", EOL);

	fflush(g_logFile);
}

void Logger::Msg(const char *const message, ...)
{
	if (g_logLevel == LOG_LEVEL_Critical) {
		return;
	}

	ASSERT(g_logFile);

	PrintTimestamp();
	PrintSeverity("<MSG> ");

	va_list vaArgs;
	va_start(vaArgs, message);

	va_list consoleVaArgs;
	va_copy(consoleVaArgs, vaArgs);

	vfprintf(g_logFile, message, vaArgs);
	va_end(vaArgs);

	vprintf(message, consoleVaArgs);
	va_end(consoleVaArgs);

	PrintEol();
}

void Logger::Error(const char *const message, ...)
{
	ASSERT(g_logFile);

	PrintTimestamp();
	PrintSeverity("<ERROR> ");

	va_list vaArgs;
	va_start(vaArgs, message);

	va_list consoleVaArgs;
	va_copy(consoleVaArgs, vaArgs);

	vfprintf(g_logFile, message, vaArgs);
	va_end(vaArgs);

	vprintf(message, consoleVaArgs);
	va_end(consoleVaArgs);

	PrintEol();
}

void Logger::Warning(const char *const message, ...)
{
	ASSERT(g_logFile);
	
	PrintTimestamp();
	PrintSeverity("<WARN> ");

	va_list vaArgs;
	va_start(vaArgs, message);

	va_list consoleVaArgs;
	va_copy(consoleVaArgs, vaArgs);

	vfprintf(g_logFile, message, vaArgs);
	va_end(vaArgs);

	vprintf(message, consoleVaArgs);
	va_end(consoleVaArgs);

	PrintEol();
}

/* eof */
