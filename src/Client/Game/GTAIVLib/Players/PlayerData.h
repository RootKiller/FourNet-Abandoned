// Copyright (C) 2016 by Rage MP Team

#pragma once

#include "Types.h"
#include "Entities/Peds/PlayerPed.h"

class CPlayerData
{
public:
	uint8				pad0[1420];		// 0000-1420
	CPlayerPed			*m_ped;			// 1420-1424


};

CPlayerData *GetPlayerDataByIndex(const unsigned index);

/* eof */