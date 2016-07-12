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
};

/* eof */
