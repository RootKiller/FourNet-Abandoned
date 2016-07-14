// Copyright (C) 2016 by Rage MP Team

#pragma once

#include "Types.h"

class CPed;

class CPlayerData
{
public:
	uint8				pad0[1420];		// 0000-1420
	CPed				*m_ped;			// 1420-1424	CPlayerPed*
};

CPlayerData *GetPlayerDataByIndex(const unsigned index);

/* eof */