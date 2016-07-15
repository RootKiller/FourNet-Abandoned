// Copyright (C) 2016 by Rage MP Team

#pragma once

#include "PedIntelligenceNY.h"

#include "Entities/Physical.h"

enum EPedCreator
{
	PED_CREATOR_SCRIPT = 2,
};

struct XLiveProtectedBuffer
{
	uint8 pad_XLiveProtectedBuffer0[4 + 4 + 4 * 2];
	uint8 data[4];
};

class CPed : public CPhysical
{
public:
	uint8							pad524[24];			// 0524 - 0548
	CPedIntelligenceNY				*m_intelligence;	// 0548 - 0552
	uint8							pad552[56];			// 0552 - 0608
	uint32							m_unknownFlags608;	// 0608 - 0612
	uint32							m_unknownFlags612;	// 0612 - 0616
	uint8							pad616[3140];		// 0616 - 3756
	XLiveProtectedBuffer			*m_health;			// 3756 - 3760
	uint8							pad3760[80];		// 3760 - 3840

	bool		SetCharCreatedBy	(const EPedCreator creator);

	/** Sets health of ped */
	void		SetHealth			(const float health);

	/** Gets health of ped */
	float		GetHealth			(void) const;
};
static_assert(sizeof(CPed) == 3840, "Incorrect CPed size");

/* eof */
