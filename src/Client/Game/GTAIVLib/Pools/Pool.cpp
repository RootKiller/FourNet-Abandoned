// Copyright (C) 2016 by Rage MP Team

#include "Offsets.h"
#include "Pool.h"

void _declspec(naked) *CPool::New_2(void)
{
	_asm jmp Offsets::CPool::New_2;
}

CPool *CPool::TaskPoolInstance(void)
{
	return *reinterpret_cast<CPool **>(Offsets::CPool::ms_taskPool);
}

/* eof */
