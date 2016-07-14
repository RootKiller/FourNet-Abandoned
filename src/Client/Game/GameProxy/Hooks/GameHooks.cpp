// Copyright (C) 2016 by Rage MP Team

#include "GameHooks.h"

#include "Logger.h"

#include "Offsets.h"
#include "Memory/Hooking/Hooking.h"
#include "Memory/MemFunctions.h"

#include "Streaming/Streaming.h"
#include "Factories/PedFactoryNY.h"

#include "Entities/Peds/Ped.h"

#include "Entities/Peds/Tasks/TaskSimpleStandStill.h"

#include "Pools/Pool.h"

#include "World/World.h"

#include "Players/PlayerData.h"

#include <string>
#include <new>
#include <Windows.h>

Address_t callAddress = 0;
#ifdef DEBUG_VEH_CREATION
Address_t CVehicleFactoryNY__Create__retn = 0;
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

//#define DEBUG_PED_CREATION
#ifdef DEBUG_PED_CREATION
Address_t CPedFactoryNY__CreatePed__retn = 0;
void _declspec(naked) CPedFactoryNY__CreatePed__hook(void)
{
	_asm {
		push eax
		mov eax, [esp + 4]
		mov callAddress, eax
		pop eax
		pushad
	}

	Logger::Msg("CPedFactoryNY__CreatePed - called from: %X", Offsets::ResolveAddress(callAddress));

	_asm {
		popad
		mov		eax, [esp + 4]
		cmp		byte ptr [eax + 1], 0
		jmp		CPedFactoryNY__CreatePed__retn
	}
}
#endif

bool modelRequested = false;
bool modelLoaded = false;

void DoCreatePedTest(void)
{
#if 1
	// 0x90442A67 = M_Y_HASID_01 (http://www.gtamodding.com/wiki/List_of_models_hashes#Peds)
	const unsigned modelHash = 0x90442A67;

	if (!modelRequested) {
		// Request model
		CStreaming::RequestModel(modelHash, *(unsigned *)(Offsets::CalculateAddress(0x1849AE0)));
		CStreaming::LoadAllRequestedModels(false);

		modelRequested = true;
	}
#else
	// Player model seems to not work on CPed's :-(

	// 0x6F0783F5 = PLAYER (http://www.gtamodding.com/wiki/List_of_models_hashes#Peds)
	const int modelHash = 0x6F0783F5;

	const unsigned requestUnknown = *(unsigned *)(Offsets::CalculateAddress(0x15F73A0));
	CStreaming::RequestSpecialModel(modelHash, requestUnknown, 26);
	CStreaming::LoadAllRequestedModels(true);
#endif
	//BA3CB4 we base this code on this part

	int modelIndex = 0;
	ModelIndexByModelHash(modelHash, &modelIndex);

	CMatrix spawnMatrix;
	CPlayerData *const data = GetPlayerDataByIndex(0);
	if (data) {
		CPed *const ped = data->m_ped;
		if (ped) {
			const unsigned pedPtrVal = (unsigned)ped;
			const CMatrix *const mat = *(CMatrix **)(pedPtrVal + 32);
			if (mat) {
				spawnMatrix = *mat;
				spawnMatrix(3, 1) += 1.0f;
			}
			else {
				Logger::Error("No mat defined");
			}
		}
		else {
			Logger::Error("No ped found.");
		}
	}
	else {
		Logger::Error("GetPlayerDataByIndex failed");
	}

	CPedFactoryNY *const factory = CPedFactoryNY::Instance();

	int unknown = 0;
	CPed *const ped = factory->CreatePed(&unknown, modelIndex, &spawnMatrix, 1, true);
	if (! ped) {
		Logger::Error("Failed to create ped.");
		return;
	}

	CTaskSimpleStandStill *const task = new (CPool::TaskPoolInstance()->New_2()) CTaskSimpleStandStill(999999, 1, 0, 8.0f);

	ped->m_intelligence->m_eventGroup.Add(task, 4, 0);

	ped->SetCharCreatedBy(PED_CREATOR_SCRIPT);

	ped->m_unknownFlags608 &= 0xFFDFFFFF;
	ped->m_unknownFlags612 |= 0x80u;
	CWorld::sub_806D40(ped);
	ped->m_unknownFlags36 |= 8u;
	CWorld::SetLoadCollisionFlag(ped, false);
	ped->m_unknownByte65 = 2;
	CWorld::sub_817350(ped, 0);
}

Address_t addr_TickScriptingThreads = 0;
bool _declspec(naked) TickScriptingThreads(signed int a1)
{
	_asm jmp addr_TickScriptingThreads
}

bool _cdecl MyLoopHook(signed int a1)
{
	//Logger::Msg("MyLoopHook");
	static bool wasPressed = false;
	if (GetAsyncKeyState(VK_F6)) {
		if (!wasPressed) {
			DoCreatePedTest();
			wasPressed = true;
		}
	}
	else {
		wasPressed = false;
	}
	return TickScriptingThreads(a1);
}

LONG WINAPI HandleException(EXCEPTION_POINTERS *ExceptionInfo)
{
	char crashInfo[512] = { 0 };
	sprintf(crashInfo, "Crash at %X (%X).", (Address_t)ExceptionInfo->ExceptionRecord->ExceptionAddress, (Address_t)ExceptionInfo->ExceptionRecord->ExceptionCode);
	MessageBox(NULL, crashInfo, "Game crashed", MB_ICONERROR);
	return EXCEPTION_EXECUTE_HANDLER;
}

void GameHooks::Install(void)
{
	SetUnhandledExceptionFilter(HandleException);

	// Disable traffic.
	// TODO: Can we do it better? NOOP'ing 51 bytes seems not the best solution
	// maybe changing jnz to jz would also work - once we will need to test it.
	MemSet((void *)Offsets::CalculateAddress(0x00841FB7), 0x90, 51);

	addr_TickScriptingThreads = Offsets::CalculateAddress(0x005A6010);
	Hooking::InstallPermCallHook(Offsets::CalculateAddress(0x0080A092), (Address_t)MyLoopHook);

	// Disable parked vehicles. (Has to be tested however on first sight works fine).
	Hooking::InstallPermJmpHook(Offsets::CalculateAddress(0x00B3E4D0), Offsets::CalculateAddress(0x00B3E50F));

	// Disable pedestrians.
	MemSet((void *)Offsets::CalculateAddress(0x004215D9), 0x90, 5);

#ifdef DEBUG_PED_CREATION
//	CPedFactoryNY__CreatePed__retn = Offsets::CalculateAddress(0x0043A008);
//	Hooking::InstallPermJmpHook(Offsets::CalculateAddress(0x0043A000), (Address_t)CPedFactoryNY__CreatePed__hook);
#endif

#ifdef DEBUG_VEH_CREATION
	CVehicleFactoryNY__Create__retn = Offsets::CalculateAddress(0x00443D66);
	Hooking::InstallPermJmpHook(Offsets::CalculateAddress(0x00443D60), (Address_t)CVehicleFactoryNY__Create__hook);
#endif
}

/* eof */
