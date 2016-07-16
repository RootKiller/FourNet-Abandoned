// Copyright (C) 2016 by Rage MP Team

#include "Offsets.h"
#include "PedFactoryNY.h"

CPed _declspec(naked) *CPedFactoryNY::CreatePed(const void *const unknown0, const unsigned modelIndex, const CMatrix *const matrix, const bool unknown1, const bool unknown2)
{
	_asm jmp Offsets::CPedFactoryNY::CreatePed;
}

CPlayerPed _declspec(naked) *CPedFactoryNY::CreatePlayerPed(const void *const creationFlags, const unsigned modelIndex, const unsigned playerId, const CMatrix *const matrix, const bool unknown1)
{
	_asm jmp Offsets::CPedFactoryNY::CreatePlayerPed;
}

CPedFactoryNY *CPedFactoryNY::Instance(void)
{
	return *reinterpret_cast<CPedFactoryNY **>(Offsets::CalculateAddress(0x015E35A0));
}

/* eof */
