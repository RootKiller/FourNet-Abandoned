// Copyright (C) 2016 by Rage MP Team

#pragma once

#include "Types.h"

typedef uint32 Address_t;

/**
 * Hooking utilities class.
 *
 * Works only under 32-bit operating system.
 */
class Hooking
{
public:
	static void		Init					(void);
	static void		Shutdown				(void);

	static void		InstallPermJmpHook		(const Address_t from, const Address_t to);
	static void		InstallPermCallHook		(const Address_t where, const Address_t to);

	static const Address_t *InstallJmpHook	(const Address_t from, const Address_t to);
	static void		UninstallJmpHook		(const Address_t original, const Address_t *const address);

	static uint32	UnprotectMemory(void *start, const size_t size);
	static uint32	ReprotectMemory(void *start, const size_t size, uint32 oldProtect);
};

template <typename TYPE>
TYPE ReadMemValue(const Address_t address)
{
	return *reinterpret_cast<TYPE*>(address);
}

template <typename TYPE>
void WriteMemValue(const Address_t address, const TYPE newValue)
{
	*reinterpret_cast<TYPE*>(address) = newValue;
}
/* eof */
