// Copyright (C) 2016 by Rage MP Team

#include "Offsets.h"

#include "TaskSimpleNetworkClone.h"

_declspec(naked) CTaskSimpleNetworkClone::CTaskSimpleNetworkClone()
	: CTaskSimple()
{
	_asm {
		push eax;
		mov eax, ecx;
		mov dword ptr [eax], offset Offsets::CTaskSimpleNetworkClone::Vtable;
		pop eax;
		retn;
	}
}

CTaskSimpleNetworkClone _declspec(naked) *CTaskSimpleNetworkClone::Create(void)
{
	_asm jmp Offsets::CTaskSimpleNetworkClone::Clone;
}

/* eof */
