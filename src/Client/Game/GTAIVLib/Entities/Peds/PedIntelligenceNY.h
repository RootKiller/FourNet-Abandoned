// Copyright (C) 2016 by Rage MP Team

#pragma once

#include "Types.h"

#include "PedIntelligence.h"
#include "Tasks/EventGroup.h"

class CPedIntelligenceNY : public CPedIntelligence
{
public:
	uint8					pad[64];		// 0000-0064
	class CPed				*m_ped;			// 0064-0068
	CEventGroup				m_eventGroup;	// 0068-...
};

/* eof */
