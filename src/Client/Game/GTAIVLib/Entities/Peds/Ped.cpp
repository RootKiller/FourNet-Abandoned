// Copyright (C) 2016 by Rage MP Team

#include "OFfsets.h"

#include "Ped.h"

bool _declspec(naked) CPed::SetCharCreatedBy(const EPedCreator a2)
{
	_asm jmp Offsets::CPed::SetCharCreatedBy;
}

/* eof */
