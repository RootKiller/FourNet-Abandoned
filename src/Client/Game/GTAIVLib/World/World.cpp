// Copyright (C) 2016 by Rage MP Team

#include "Offsets.h"
#include "World.h"

bool _declspec(naked) CWorld::SetLoadCollisionFlag(CDynamicEntity *const entity, const bool flag)
{
	_asm jmp Offsets::CWorld::SetLoadCollisionFlag;
}

void _declspec(naked) CWorld::sub_817350(CDynamicEntity *const entity, const bool a2)
{
	_asm jmp Offsets::Global::sub_817350;
}

void _declspec(naked) CWorld::sub_806D40(CDynamicEntity *const entity)
{
	_asm jmp Offsets::Global::sub_806D40;
}

/* eof */
