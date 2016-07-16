// Copyright (C) 2016 by Rage MP Team

#include "Offsets.h"

#include "Ped.h"

CTaskComplexPlayerOnFoot _declspec(naked) *CPedMoveBlendOnFoot::CreatePlayerOnFootTask(void) const
{
	_asm jmp Offsets::CPedMoveBlendOnFoot::CreatePlayerOnFootTask;
}


bool _declspec(naked) CPed::SetCharCreatedBy(const EPedCreator a2)
{
	_asm jmp Offsets::CPed::SetCharCreatedBy;
}

void CPed::SetHealth(const float health)
{
	// As long as we do not use XLive we do not
	// need to worry about that this value will be
	// obfuscated somehow so just operate on it normally.
	*reinterpret_cast<float*>(m_health->data) = health;
}

float CPed::GetHealth(void) const
{
	// As long as we do not use XLive we do not
	// need to worry about that this value will be
	// obfuscated somehow so just operate on it normally.
	return *reinterpret_cast<float*>(m_health->data);
}

/* eof */
