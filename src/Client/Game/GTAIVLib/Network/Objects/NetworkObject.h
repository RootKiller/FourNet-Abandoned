// Copyright (C) 2016 by Rage MP Team

#pragma once

#include "Entities/Entity.h"

class CNetworkObject
{
public:
	uint8				pad[4]; // 0000 - 0004
	CEntity				*m_gameEntity;
};

/* eof */
