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
	BEGIN_OFFSET_NAMESPACE(Global)
		DECLARE_OFFSET(ModelIndexByModelHash);

		DECLARE_OFFSET(sub_817350);
		DECLARE_OFFSET(sub_806D40);

		DECLARE_OFFSET(GetPlayerDataByIndex);

		// -- New offset that has no special namespace here --
	END_OFFSET_NAMESPACE()

	BEGIN_OFFSET_NAMESPACE(CGameAllocator)
		DECLARE_OFFSET(Alloc);
		DECLARE_OFFSET(AllocAligned);
		DECLARE_OFFSET(Free);
	END_OFFSET_NAMESPACE()

	BEGIN_OFFSET_NAMESPACE(CPedFactoryNY)
		DECLARE_OFFSET(CreatePed);
	END_OFFSET_NAMESPACE()

	BEGIN_OFFSET_NAMESPACE(CStreaming)
		DECLARE_OFFSET(RequestSpecialModel);
		DECLARE_OFFSET(LoadAllRequestedModels);
		DECLARE_OFFSET(RequestModel);
		DECLARE_OFFSET(HasModelLoaded);
	END_OFFSET_NAMESPACE()

	BEGIN_OFFSET_NAMESPACE(CEventGroup)
		DECLARE_OFFSET(Add);
	END_OFFSET_NAMESPACE()

	BEGIN_OFFSET_NAMESPACE(CPed)
		DECLARE_OFFSET(SetCharCreatedBy);
	END_OFFSET_NAMESPACE()

	BEGIN_OFFSET_NAMESPACE(CWorld)
		DECLARE_OFFSET(SetLoadCollisionFlag);
	END_OFFSET_NAMESPACE()

	BEGIN_OFFSET_NAMESPACE(CTaskSimpleStandStill)
		DECLARE_OFFSET(Constructor);
	END_OFFSET_NAMESPACE()

	BEGIN_OFFSET_NAMESPACE(CPool)
		DECLARE_OFFSET(New_2);

		DECLARE_OFFSET(ms_taskPool);
	END_OFFSET_NAMESPACE()

	// -- New offset and namespaces here --

#include "OffsetsHelpersEnd.h"
};

/* eof */
