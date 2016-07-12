// Copyright (C) 2016 by Rage MP Team

#include "GameHooks.h"

#include "Logger.h"

#include "Offsets.h"
#include "Memory/Hooking/Hooking.h"
#include "Memory/MemFunctions.h"

#ifdef DEBUG_VEH_CREATION
Address_t CVehicleFactoryNY__Create__retn = 0;
Address_t callAddress = 0;
void _declspec(naked) CVehicleFactoryNY__Create__hook(void)
{
	_asm {
		push eax
		mov eax, [esp + 4]
		mov callAddress, eax
		pop eax
		pushad
	}

	Logger::Msg("CVehicleFactoryNY__Create - called from: %X", Offsets::ResolveAddress(callAddress));

	_asm {
		popad
		push	ebp
		push	edi
		mov		edi, [esp + 0Ch]
		jmp		CVehicleFactoryNY__Create__retn
	}
}
#endif

void GameHooks::Install(void)
{
	// Disable traffic.
	// TODO: Can we do it better? NOOP'ing 51 bytes seems not the best solution
	// maybe changing jnz to jz would also work - once we will need to test it.
	MemSet((void *)Offsets::CalculateAddress(0x00841FB7), 0x90, 51);

#ifdef DEBUG_VEH_CREATION
	CVehicleFactoryNY__Create__retn = Offsets::CalculateAddress(0x00443D66);
	Hooking::InstallPermJmpHook(Offsets::CalculateAddress(0x00443D60), (Address_t)CVehicleFactoryNY__Create__hook);
#endif
}

/* eof */
