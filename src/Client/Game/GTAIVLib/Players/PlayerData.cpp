// Copyright (C) 2016 by Rage MP Team

#include "Offsets.h"
#include "PlayerData.h"

CPlayerData _declspec(naked) *GetPlayerDataByIndex(const unsigned index)
{
	_asm jmp Offsets::Global::GetPlayerDataByIndex;
}

/* eof */
