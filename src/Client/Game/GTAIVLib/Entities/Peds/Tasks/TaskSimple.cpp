// Copyright (C) 2016 by Rage MP Team

#include "Offsets.h"

#include "TaskSimple.h"

_declspec(naked) CTaskSimple::CTaskSimple()
{
	_asm jmp Offsets::CTaskSimple::Constructor;
}

/* eof */
