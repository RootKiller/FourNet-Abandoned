// Copyright (C) 2016 by Rage MP Team

#pragma once

#include "Math/Matrix.h"

#include "PedFactory.h"

class CPed;

class CPedFactoryNY : public CPedFactory
{
public:
	/**
	 * Create CPed.
	 *
	 * @param[in] unknown0   ?
	 * @param[in] modelIndex The index of the ped model to use.
	 * @param[in] matrix     The matrix where to spawn ped (can be nullptr)
	 * @param[in] unknown1   ?
	 * @param[in] unknown2   ?
	 * @return Ped pointer in case there is enough space in pool and all params are collect @c nullptr otherwise.
	 */
	CPed *CreatePed(const void *const unknown0, const unsigned modelIndex, const CMatrix *const matrix, const bool unknown1, const bool unknown2);

	/** Get instance of the factory. */
	static CPedFactoryNY *Instance(void);
};

/* eof */
