// Copyright (C) 2016 by Rage MP Team

#pragma once

#include "DynamicEntity.h"

class CPhysical : public CDynamicEntity
{
public:
	uint8						pad268[256]; // 0268 - 0524
};
static_assert(sizeof(CPhysical) == 524, "Incorrect CPhysical size");

/* eof */
