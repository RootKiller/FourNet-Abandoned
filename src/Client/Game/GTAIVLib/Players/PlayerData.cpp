// Copyright (C) 2016 by Rage MP Team

#include "Offsets.h"
#include "PlayerData.h"

#include "Allocators/GameAllocator.h"

_declspec(naked) CPlayerData::CPlayerData()
{
	_asm jmp Offsets::CPlayerData::Constructor;
}

void _declspec(naked) CPlayerData::SetPlayerPed(CPlayerPed *const ped)
{
	_asm jmp Offsets::CPlayerData::SetPlayerPed;
}

CPlayerData _declspec(naked) *GetPlayerDataByIndex(const unsigned index)
{
	_asm jmp Offsets::Global::GetPlayerDataByIndex;
}

/* eof */
