// Copyright (C) 2016 by Rage MP Team

#include "Offsets.h"
#include "EventGroup.h"

void _declspec(naked) CEventGroup::Add(CTask *const task, signed int a3, int a4)
{
	_asm jmp Offsets::CEventGroup::Add;
}

/* eof */
