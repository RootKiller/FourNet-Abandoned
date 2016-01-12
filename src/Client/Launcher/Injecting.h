/// Copyright (C) 2016 by EFLC MP Team

#pragma once

#include <Windows.h>

namespace launcher {

//! Inject DLL into process.
bool InjectDll(const HANDLE process, const char *const dllPath);

} /* namespace launcher */

/* EOF */
