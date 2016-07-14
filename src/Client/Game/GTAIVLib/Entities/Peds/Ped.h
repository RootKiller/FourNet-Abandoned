// Copyright (C) 2016 by Rage MP Team

#pragma once

#include "PedIntelligenceNY.h"

#include "Entities/Physical.h"

enum EPedCreator
{
	PED_CREATOR_SCRIPT = 2,
};

/** @todo Move to separated file */
class CPortalTracker
{
};

class CPed : public CPhysical
{
public:
	uint8							pad0[36];			// 0000 - 0036
	uint32							m_unknownFlags36;	// 0036 - 0040 some flags?
	uint8							pad40[25];			// 0040 - 0065
	uint8							m_unknownByte65;	// 0065 - 0066 Set to 2 when creating ped.
	uint8							pad66[62];			// 0066 - 0128
	CPortalTracker					*m_portalTracker;	// 0128 - 0132
	uint8							pad132[416];		// 0132 - 0548
	CPedIntelligenceNY				*m_intelligence;	// 0548 - 0552
	uint8							pad552[482];		// 0552 - 0608
	uint32							m_unknownFlags608;	// 0608 - 0612
	uint32							m_unknownFlags612;	// 0612 - 0616

	bool		SetCharCreatedBy	(const EPedCreator creator);
};

/* eof */
