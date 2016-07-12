// Copyright (C) 2016 by Rage MP Team

#pragma once

#include "Memory/Hooking/Hooking.h"


/**
 * Class storing all memory offsets used by multiplayer.
 *
 * Adding new offsets tutorial:
 * @li Add declaration of offset at the end of the Offsets class (you can setup new namespace if needed).
 * @li Add setup of new offset to OffsetsSetup.h file.
 * @li Add SET_OFFSET_ADDRESS for your new offset to all versions we support.
 * @li Ready to go!
 */
class Offsets
{
public:
	/**
	 * Initialize offsets.
	 *
	 * @return @c true if game version is matching and we setup offsets @c false otherwise.
	 */
	static bool		Init		(void);

	/**
	 * Calculate the address with the base.
	 *
	 * @param[in] sourceAddress The address without base.
	 * @return The address with base.
	 */
	static Address_t CalculateAddress(const Address_t sourceAddress);

	/**
	 * Calculate the address without the base.
	 *
	 * @param[in] sourceAddress The address with base.
	 * @return The address without base.
	 */
	static Address_t ResolveAddress(const Address_t sourceAddress);

#include "OffsetHelpersBegin.h"
	BEGIN_OFFSET_NAMESPACE(Base)
		DECLARE_OFFSET(AllocateMemory);

		// -- New offset that has no special namespace here --
	END_OFFSET_NAMESPACE()

	// -- New offset and namespaces here --

#include "OffsetsHelpersEnd.h"
};

/* eof */
