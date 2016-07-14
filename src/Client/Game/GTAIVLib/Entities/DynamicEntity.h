// Copyright (C) 2016 by Rage MP Team

#pragma once

#include "Entities/Entity.h"

/** @todo Move to separated file */
class CPortalTracker
{
public:
	uint8							m_padPortalTracker0[71];
};
static_assert(sizeof(CPortalTracker) == 71, "Incorrect CPortalTracker size");

class CDynamicEntity : public CEntity
{
public:
	uint32							m_unknown112;		// 0112 - 0116
	uint32							m_unknown116;		// 0116 - 0120
	uint32							m_unknown120;		// 0120 - 0124
	uint32							m_unknown124;		// 0124 - 0128
	CPortalTracker					m_portalTracker;	// 0128 - 0199
	uint8							m_pad199[69];		// 0199 - 0268
};
static_assert(sizeof(CDynamicEntity) == 268, "Incorrect CDynamicEntity size");

/* eof */
