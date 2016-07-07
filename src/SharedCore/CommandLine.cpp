// Copyright (C) 2016 by DVO Games

#include <cstdio>
#include <string.h>

#include "CommandLine.h"

#include "Logger.h"

#include "Debug/Debug.h"

const size_t INVALID_PARAM_INDEX(-1);

static const char *const *argumentsVector = nullptr;
static size_t argumentsCount = 0;

void CmdLine::Init(const int argc, const char *const *const argv)
{
	ASSERT(argc > 0);

	argumentsCount = static_cast<size_t>(argc);
	argumentsVector = argv;
}

static size_t GetParamIndex(const char *const paramName)
{
	ASSERT(paramName);
	const size_t paramLen = strlen(paramName);
	if (!paramLen) {
		return INVALID_PARAM_INDEX;
	}

	for (size_t i = 1; i < argumentsCount; ++i) {
		const char *const arg = argumentsVector[i];
		if (strlen(arg) < 2) {
			continue;
		}

		if (arg[0] != '-') {
			continue;
		}

		if (! strcmp(arg + 1, paramName)) {
			return i;
		}
	}
	return INVALID_PARAM_INDEX;
}

bool CmdLine::IsParamSet(const char *const paramName)
{
	return GetParamIndex(paramName) != INVALID_PARAM_INDEX;
}

const char *CmdLine::GetParamValue(const char *const paramName)
{
	const size_t parameterIndex = GetParamIndex(paramName);
	if (parameterIndex == INVALID_PARAM_INDEX) {
		return nullptr;
	}

	if (parameterIndex == (argumentsCount - 1)) {
		return nullptr;
	}
	return argumentsVector[parameterIndex + 1];
}

bool CmdLine::IsOptionEnabled(const char *const optionName)
{
	ASSERT(optionName);
	const size_t paramLen = strlen(optionName);
	if (!paramLen) {
		return false;
	}

	for (size_t i = 1; i < argumentsCount; ++i) {
		const char *const arg = argumentsVector[i];
		if (strlen(arg) < 3) {
			continue;
		}

		if (arg[0] != '-' || arg[1] != '-') {
			continue;
		}

		if (! strcmp(arg + 2, optionName)) {
			return true;
		}
	}
	return false;
}

/* eof */
