// Copyright (C) 2016 by Rage MP Team

#include "Offsets.h"
#include "TaskSimpleStandStill.h"

_declspec(naked) CTaskSimpleStandStill::CTaskSimpleStandStill(int a2, char a3, char a4, float a5)
{
	_asm jmp Offsets::CTaskSimpleStandStill::Constructor;
}

/* eof */
