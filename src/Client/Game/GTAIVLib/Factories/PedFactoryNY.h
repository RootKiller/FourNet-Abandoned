// Copyright (C) 2016 by Rage MP Team

#pragma once

#include "Math/Matrix.h"

#include "PedFactory.h"

class CPed;
class CPlayerPed;

class CPedFactoryNY : public CPedFactory
{
public:
	/**
	 * Create CPed.
	 *
	 * @param[in] creationFlags   ?
	 * @param[in] modelIndex The index of the ped model to use.
	 * @param[in] matrix     The matrix where to spawn ped (can be nullptr)
	 * @param[in] unknown1   ?
	 * @param[in] unknown2   ?
	 * @return Ped pointer in case there is enough space in pool and all params are collect @c nullptr otherwise.
	 */
	CPed *CreatePed(const void *const creationFlags, const unsigned modelIndex, const CMatrix *const matrix, const bool unknown1, const bool unknown2);

	/**
	 * Create CPlayerPed.
	 *
	 * @param[in] creationFlags (2 bytes - if first is 0 and second 1 it means we are creating local player)
	 * @param[in] modelIndex The index of the ped model to use.
	 * @param[in] playerId   The id of the owning player.
	 * @param[in] matrix     The matrix where to spawn ped (can be nullptr)
	 * @param[in] unknown1   Set to true when creating local player - no idea what is this.
	 * @return Ped pointer in case there is enough space in pool and all params are collect @c nullptr otherwise.
	 */
	CPlayerPed *CreatePlayerPed(const void *const creationFlags, const unsigned modelIndex, const unsigned playerId, const CMatrix *const matrix, const bool unknown1);

	/** Get instance of the factory. */
	static CPedFactoryNY *Instance(void);
};

/* eof */
