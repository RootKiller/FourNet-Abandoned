/// Copyright (C) 2016 by GTA IV MP Team
#pragma once

#include <Windows.h>

//! Inject DLL into process.
bool InjectDll(const HANDLE process, const char *const dllPath);

/* EOF */
