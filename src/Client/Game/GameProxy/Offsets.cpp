// Copyright (C) 2016 by Rage MP Team

#include <Windows.h>

#include "OS/OS.h"
#include "Logger.h"

#include "Offsets.h"

#define INSIDE_OFFSETS_CPP
#include "OffsetsSetup.h"
#undef INSIDE_OFFSETS_CPP

/** The 4-bytes at 0x008F0FF6 from the 1.0.7.0 version */
const uint32 VERSION_1070_VALUE = 0x555556B8; // B8 56 55 55

/** Currently supported patch stringized version */
#define CURRENTLY_SUPPORTED_PATCH "1.0.7.0"

/** The game image base address used for calculating addresses */
static Address_t baseAddress = 0;

/** Are offsets initialized? */
static bool isInitialized = false;


/**
 * Setup offsets for 1.0.7.0 patch.
 */
static void Init_1070_Offsets(void)
{
#include "OffsetHelpersBegin.h"

	SET_OFFSET_ADDRESS(Global,					ModelIndexByModelHash,			0x0098AAE0);
	SET_OFFSET_ADDRESS(Global,					sub_817350,						0x00817350);
	SET_OFFSET_ADDRESS(Global,					sub_806D40,						0x00806D40);
	SET_OFFSET_ADDRESS(Global,					GetPlayerDataByIndex,			0x00817F20);

	SET_OFFSET_ADDRESS(CPedFactoryNY,			CreatePed,						0x0043A000);

	SET_OFFSET_ADDRESS(CStreaming,				RequestSpecialModel,			0x00832C40);
	SET_OFFSET_ADDRESS(CStreaming,				LoadAllRequestedModels,			0x00832C20);
	SET_OFFSET_ADDRESS(CStreaming,				RequestModel,					0x00B6C3D0);
	SET_OFFSET_ADDRESS(CStreaming,				HasModelLoaded,					0x00B6C4A0);

	SET_OFFSET_ADDRESS(CEventGroup,				Add,							0x009E58B0);

	SET_OFFSET_ADDRESS(CPed,					SetCharCreatedBy,				0x0089EC20);

	SET_OFFSET_ADDRESS(CWorld,					SetLoadCollisionFlag,			0x00B95290);

	SET_OFFSET_ADDRESS(CTaskSimpleStandStill,	Constructor,					0x00A1D730);

	SET_OFFSET_ADDRESS(CPool,					New_2,							0x00439CB0);
	SET_OFFSET_ADDRESS(CPool,					ms_taskPool,					0x0164B01C);

	// Your offsets lands here.

#include "OffsetsHelpersEnd.h"
}

bool Offsets::Init(void)
{
	baseAddress = (unsigned)GetModuleHandle(NULL) - 0x400000;
	isInitialized = true;

	const uint32 versionCheckValue = ReadMemValue<uint32>(CalculateAddress(0x008F0FF6));
	if (versionCheckValue != VERSION_1070_VALUE) {
		OS::ShowMessageBox("Fatal error", "Incompatible game version detected. Supported game patch is " CURRENTLY_SUPPORTED_PATCH ".", OS::EMessageBoxType::MESSAGE_BOX_TYPE_error);
		return false;
	}

	Init_1070_Offsets();

	DEBUG_LOG("[GameProxy] Offsets initialized (Base: %p, Module: %s)", baseAddress, *OS::GetModuleFullPath());
	return true;
}

Address_t Offsets::CalculateAddress(const Address_t sourceAddress)
{
	ASSERT(isInitialized);
	return sourceAddress + baseAddress;
}

Address_t Offsets::ResolveAddress(const Address_t sourceAddress)
{
	ASSERT(isInitialized);
	return sourceAddress - baseAddress;
}

/* eof */
