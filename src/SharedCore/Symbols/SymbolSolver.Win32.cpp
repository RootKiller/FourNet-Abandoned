// Copyright (C) 2016 by DVO Games

#include <Windows.h>

#include "Debug/Debug.h"

#include "Logger.h"

#include "SymbolSolver.h"

SymbolSolver::SymbolSolver(const char *const dynLibName)
{
	ASSERT(dynLibName);

	m_handle = static_cast<void *>(LoadLibrary(dynLibName));
	if (!m_handle) {
		Logger::Error("SymbolSolver.Win32: Unable to open dynamic library %s", dynLibName);
	}
}

SymbolSolver::~SymbolSolver()
{
	if (m_handle) {
		FreeLibrary(static_cast<HMODULE>(m_handle));
		m_handle = nullptr;
	}
}

void* SymbolSolver::GetProcAddress(const char *const procName)
{
	ASSERT(IsValid());
	ASSERT(procName);

	return ::GetProcAddress(static_cast<HMODULE>(m_handle), procName);
}

/* eof */
