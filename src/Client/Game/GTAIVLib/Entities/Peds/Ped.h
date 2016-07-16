// Copyright (C) 2016 by Rage MP Team

#pragma once

#include "PedIntelligenceNY.h"

#include "Entities/Physical.h"

#include "Tasks/TaskComplexPlayerOnFoot.h"

enum EPedCreator
{
	PED_CREATOR_SCRIPT = 2,
};

class CPedMoveBlendOnFoot
{
public:
	CTaskComplexPlayerOnFoot *CreatePlayerOnFootTask(void) const;
};

struct XLiveProtectedBuffer
{
	uint8 pad_XLiveProtectedBuffer0[4 + 4 + 4 * 2];
	uint8 data[4];
};

class CPed : public CPhysical
{
public:
	uint8							pad524[12];			// 0524 - 0548
	uint8							m_unknown536;		// 0536 - 0537
	uint8							m_unknown537;		// 0537 - 0538
	uint8							pad538[10];			// 0538 - 0548
	CPedIntelligenceNY				*m_intelligence;	// 0548 - 0552
	uint8							pad552[56];			// 0552 - 0608
	uint32							m_unknownFlags608;	// 0608 - 0612
	uint32							m_unknownFlags612;	// 0612 - 0616
	uint8							pad616[289];		// 0616 - 3756
	uint8							m_unknown905;		// 0905 - 0906
	uint8							pad906[1798];		// 0906 - 2704
	CPedMoveBlendOnFoot				*m_pedMoveBlendOnFoot; // 2704 - 2708
	uint8							pad2708[1048];		// 0906 - 3756
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
