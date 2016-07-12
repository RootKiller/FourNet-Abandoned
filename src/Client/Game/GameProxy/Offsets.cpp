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

	SET_OFFSET_ADDRESS(Base, AllocateMemory, 0x004011D0);

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
