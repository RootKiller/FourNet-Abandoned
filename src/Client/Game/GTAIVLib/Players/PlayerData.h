// Copyright (C) 2016 by Rage MP Team

#pragma once

#include "Types.h"
#include "Entities/Peds/PlayerPed.h"

#include "Allocators/GameAllocator.h"

class CUnk_PlayerData
{
public:
	uint8			pad_CUnk_PlayerData[32];
	uint32			m_unknown32;
};

class CPlayerData
{
public:
	uint8				pad0[1242];		// 0000 - 1242
	uint8				m_playerIndex;	// 1242 - 1243
	uint8				pad1243;		// 1243 - 1244
	uint32				m_unknown1244;	// 1244 - 1248
	uint8				pad1248[140];	// 1248 - 1420
	CUnk_PlayerData		*m_unknown1388;	// 1388 - 1392
	uint8				pad1392[28];	// 1392 - 1420
	CPlayerPed			*m_ped;			// 1420 - 1424
	uint8				pad1424[48];	// 1424 - 1472

			CPlayerData	();

	void	SetPlayerPed(CPlayerPed *const ped);

	GAME_ALLOC_OBJECT;
};
static_assert(sizeof(CPlayerData) == 1472, "Incorrect CPlayerData size");

CPlayerData *GetPlayerDataByIndex(const unsigned index);

/* eof */