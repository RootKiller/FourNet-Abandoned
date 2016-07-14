// Copyright (C) 2016 by Rage MP Team

#pragma once

#include "Entities/DynamicEntity.h"

class CWorld
{
public:
	static bool SetLoadCollisionFlag(CDynamicEntity *const entity, const bool flag);

	/**
	 * Unknown method doing some operation on the entity.
	 * Called form scripting methods which warp ped into the car.
	 *
	 * @Eryk: I have no idea what is this method for..
	 * @todo findout the meaning of this method.
	 */
	static void sub_817350(CDynamicEntity *const entity, const bool a2);

	/**
	 * Unknown method doing some operation on the entity.
	 * Called form scripting methods which warp ped into the car.
	 *
	 * @Eryk: I have no idea what is this method for..
	 * @todo findout the meaning of this method.
	 */
	static void sub_806D40(CDynamicEntity *const entity);
};

/* eof */
