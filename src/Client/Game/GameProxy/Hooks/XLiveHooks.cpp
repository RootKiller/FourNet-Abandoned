// Copyright (C) 2016 by Rage MP Team
// The parts of this file is based on XLiveLess project by Listener.

#include "Offsets.h"

#include "XLiveHooks.h"

#include "Memory/MemFunctions.h"
#include "Memory/Hooking/Hooking.h"

#include "Logger.h"
#include "Debug/Debug.h"

#include <Windows.h>

#define INSIDE_XLIVEHOOKS_CPP
#include "XLiveFakedMethods.h"
#undef INSIDE_XLIVEHOOKS_CPP

/** Do we want to override standard game save path? */
#define OVERRIDE_SAVEPATH 1

static void InstallXLiveDllHooks(void)
{
	DEBUG_LOG("BEGIN Install XLive.dll hooks.");
	const HMODULE xliveDll = GetModuleHandle("xlive.dll");
	if (!xliveDll) {
		Logger::Error("Unable to get handle of xlive.dll! Expect crashes!");
		return;
	}

	for (size_t i = 0; i < ARRAY_LENGTH(replacements); ++i) {
		const uint16 ordinal = replacements[i].ordinal;

		const Address_t originalAddress = reinterpret_cast<Address_t>(GetProcAddress(xliveDll, MAKEINTRESOURCE(ordinal)));
		if (! originalAddress) {
			break;
		}

		Hooking::InstallJmpHook(originalAddress, replacements[i].method);
	}
	DEBUG_LOG("END Install XLive.dll hooks.");
}

#ifdef OVERRIDE_SAVEPATH
const char *gameHomeDirectory = nullptr;

void _cdecl GetOverridenSavePath(const int unused, char *outPath, char *saveFileName)
{
	strcpy(outPath, gameHomeDirectory);
	strcat(outPath, "savegames");

	const DWORD attrs = GetFileAttributes (outPath);

	// Make sure the savegames path exists.
	if (attrs == INVALID_FILE_ATTRIBUTES) {
		CreateDirectory (outPath, NULL);
	}
	ASSERT(attrs & FILE_ATTRIBUTE_DIRECTORY);

	if (saveFileName) {
		strcat(outPath, "\\");
		strcat(outPath, saveFileName);
	}
}
#endif

static void PatchGameProcess(void)
{
	// Process patches.

	// Disable 5second sleep on game startup.
	MemSet((void *)Offsets::CalculateAddress(0x00401835), 0x90, 11);

	// Enable debugger in error menu (don't load WER.dll)
	WriteMemValue<uint8>(Offsets::CalculateAddress(0x00D356D0), 0xC3); // retn

	// Disable certificates check.
	WriteMemValue<uint32>(Offsets::CalculateAddress(0x00403F10), 0x900008C2); // retn 8

	WriteMemValue<uint32>(Offsets::CalculateAddress(0x0040262D), 0x4AE9C033); // xor eax, eax - address of the RGSC object

	// Skip RGSC connect and EFC checks.
	WriteMemValue<uint32>(Offsets::CalculateAddress(0x00402631), 0x90000002); // jmp 40289E
	WriteMemValue<uint32>(Offsets::CalculateAddress(0x00402883), 0xA390); // NOP; MOV [g_rgsc], eax
	MemSet ((void *)Offsets::CalculateAddress(0x004028ED), 0x90, 0x2A);
	WriteMemValue<uint32>(Offsets::CalculateAddress(0x0040291D), 0x90909090); // NOP*4- last RGSC init check
	WriteMemValue<uint16>(Offsets::CalculateAddress(0x00402921), 0x9090); // NOP*2- last RGSC init check 

	// skip missing tests...
	MemSet((void *)Offsets::CalculateAddress(0x00402B12), 0x90, 14);
	MemSet((void *)Offsets::CalculateAddress(0x00402D17), 0x90, 14);
	WriteMemValue<uint32>(Offsets::CalculateAddress(0x403870), 0x90C3C033);	// xor eax, eax; retn
	WriteMemValue<uint32>(Offsets::CalculateAddress(0x404250), 0x90C3C033);	// xor eax, eax; retn

#ifdef OVERRIDE_SAVEPATH
	// savegames
	WriteMemValue<uint16>(Offsets::CalculateAddress(0x005B06E5), 0x9090); 	// NOP; NOP - save file CRC32 check
	Hooking::InstallPermJmpHook(Offsets::CalculateAddress(0x005B0110), (Address_t)GetOverridenSavePath); // replace getSavefilePath
	gameHomeDirectory = reinterpret_cast<char *>(Offsets::CalculateAddress(0x10F1DA0));
#endif

	WriteMemValue<uint32>(Offsets::CalculateAddress(0x00BAC160), 0x90C301B0);	// mov al, 1; retn
	WriteMemValue<uint32>(Offsets::CalculateAddress(0x00BAC180), 0x90C301B0);
	WriteMemValue<uint32>(Offsets::CalculateAddress(0x00BAC190), 0x90C301B0);
	WriteMemValue<uint32>(Offsets::CalculateAddress(0x00BAC1C0), 0x90C301B0);
}

void XLiveHooks::Install(void)
{
	InstallXLiveDllHooks();
	PatchGameProcess();
}

/* eof */
