// Copyright (C) 2016 by DVO Games

#pragma once

/**
 * Log setup level.
 */
enum LogLevel
{
	LOG_LEVEL_Standard	= 0, //< Standard display errors, warnings and info messages.

	LOG_LEVEL_Critical	= 1 //< Display only errors.
};

/**
 * Logger class.
 */
class Logger
{
public:

	/**
	 * Initialize the logger.
	 *
	 * @param[in] logFileName The log file name. If @c nullptr logger will use default name.
	 * @param[in] level	The log level.
	 * @return @c true in case logger has been successfully initialized @c false otherwise.
	 */
	static bool Initialize(const char *const logFileName, const LogLevel level);

	/**
	 * Shutdown the logger.
	 */
	static void Shutdown(void);

	/**
	 * Print message into the console and log.
	 *
	 * @param[in] message The message to be printed into the console and log.
	 */
	static void Msg(const char *const message, ...);

	/**
	 * Print error into the console and log.
	 *
	 * @param[in] message The message to be printed into the console and log.
	 */
	static void Error(const char *const message, ...);

	/**
	 * Print warning into the console and log.
	 *
	 * @param[in] message The message to be printed into the console and log.
	 */
	static void Warning(const char *const message, ...);
};

/**
 * @def Debug log macro.
 *
 * @param[in] message The message to print.
 */
#ifdef DEBUG_BUILD
#	define DEBUG_LOG(message, ...) Logger::Msg(message, __VA_ARGS__)
#else
#	define DEBUG_LOG(message, ...) do {} while (false)
#endif

/* eof */
