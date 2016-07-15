// Copyright (C) 2016 by Rage MP Team

#include "Offsets.h"

#include "GameAllocator.h"

void _declspec(naked) *CGameAllocator::Alloc(const size_t size)
{
	_asm jmp Offsets::CGameAllocator::Alloc;
}

void _declspec(naked) *CGameAllocator::AllocAligned(const size_t size, const size_t alignment)
{
	_asm jmp Offsets::CGameAllocator::AllocAligned;
}

int _declspec(naked) CGameAllocator::Free(void *const memory)
{
	_asm jmp Offsets::CGameAllocator::Free;
}

/* eof */
