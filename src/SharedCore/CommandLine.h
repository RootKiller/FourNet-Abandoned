// Copyright (C) 2016 by DVO Games

#pragma once

/**
 * Command-line processor.
 */
class CmdLine
{
public:
	/**
	 * Initialize the command line.
	 *
	 * @param[in] argc The count of the parameters.
	 * @param[in] argv The parameters data.
	 */
	static void Init(const int argc, const char *const argv[]);

	/**
	 * Check if the parameter is set.
	 *
	 * @param[in] paramName The name of the parameter to be checked excluding the
	 *                      minus prefix.
	 * @return @c true if parameter is set @c false otherwise.
	 */
	static bool IsParamSet(const char *const paramName);

	/**
	 * Get parameter value.
	 *
	 * @param[in] paramName The name of the parameter.
	 * @return @c nullptr in case parameter is not set, char array containing the
	 *         parameter value otherwise - the returned string can be also empty.
	 */
	static const char *GetParamValue(const char *const paramName);

	/**
	 * Check if option is enabled. (Options are set to --name in command line)
	 *
	 * @param[in] optionName without -- prefix.
	 * @return @c false if option is not enabled @c true if it's enabled.
	 */
	static bool IsOptionEnabled(const char *const optionName);
};

/* eof */
