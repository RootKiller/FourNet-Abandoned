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
#include "Entities/Peds/Tasks/TaskSimpleNetworkClone.h"

#include "Pools/Pool.h"

#include "World/World.h"

#include "Players/PlayerData.h"

#include "XLiveHooks.h"

#include <string>
#include <new>
#include <Windows.h>

#include "AutoPtr.h"

#include "Network/Objects/NetObjPlayer.h"

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

Address_t CPedFactoryNY__CreateScenarioPed__retn = 0;
void _declspec(naked) CPedFactoryNY__CreateScenarioPed__hook(void)
{
	_asm {
		push eax
		mov eax, [esp + 4]
		mov callAddress, eax
		pop eax
		pushad
	}

	Logger::Msg("CPedFactoryNY__CreateScenarioPed - called from: %X", Offsets::ResolveAddress(callAddress));

	_asm {
		popad
		mov		eax, [esp + 4]
		push	esi
		push	eax
		jmp		CPedFactoryNY__CreateScenarioPed__retn
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
	CPed *localPed = nullptr;
	if (data && (localPed = data->m_ped)) {
		CMatrix *mat = nullptr;
		const CVector &pos = localPed->GetPosition();
		spawnMatrix = CMatrix(pos.x, pos.y, pos.z + 2.0f);
	}
	else {
		Logger::Error("No local ped found.");
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

static unsigned playerId = 0;

class CUnk__PlayerNames
{
public:
	void SetPedNetworkNameAndColor(CPed *const ped, const char *const name, const unsigned *const color);

	unsigned SetPlayerNameVisible	(const unsigned playerId, const bool visible);

	static CUnk__PlayerNames *Instance(void)
	{
		return (CUnk__PlayerNames *)Offsets::CalculateAddress(0x018EDB70);
	}
};

Address_t SetPlayerNameVisible_addr = 0;
unsigned _declspec(naked) CUnk__PlayerNames::SetPlayerNameVisible(const unsigned playerId, const bool visible)
{
	_asm jmp SetPlayerNameVisible_addr;
}

Address_t SetPedNetworkNameAndColor_addr = 0;
void _declspec(naked) CUnk__PlayerNames::SetPedNetworkNameAndColor(CPed *const ped, const char *const name, const unsigned *const color)
{
	_asm jmp SetPedNetworkNameAndColor_addr;
}

// CPlayersManager::SetupPlayerPed???
Address_t sub_817DF0_addr = 0;
bool _declspec(naked) sub_817DF0(CPlayerPed *const ped, const CVector &position)
{
	_asm jmp sub_817DF0_addr;
}

Address_t CreatePlayerNetObj_addr = 0;
CNetObjPlayer _declspec(naked) *CreatePlayerNetObj(CEntity *const a1 /** gameEntity? */, const bool a2, const int a3)
{
	_asm jmp CreatePlayerNetObj_addr;
}

Address_t sub_49DE00_addr = 0;
void _declspec(naked) sub_49DE00(CNetObjPlayer *const netObj)
{
	_asm jmp sub_49DE00_addr;
}
CPlayerPed *localPed = nullptr;

void DoCreatePlayerPedTest(void)
{
	if (playerId == 31) {
		Logger::Error("Not enough player slots to create new player ped.");
		return;
	}

	// 0x90442A67 = M_Y_HASID_01 (http://www.gtamodding.com/wiki/List_of_models_hashes#Peds)
	const unsigned modelHash = 0x90442A67;

	if (!modelRequested) {
		// Request model
		CStreaming::RequestModel(modelHash, *(unsigned *)(Offsets::CalculateAddress(0x1849AE0)));
		CStreaming::LoadAllRequestedModels(false);

		modelRequested = true;
	}

	int modelIndex = 0;
	ModelIndexByModelHash(modelHash, &modelIndex);

	CMatrix spawnMatrix;
	if (localPed) {
		CMatrix *mat = nullptr;
		const CVector &pos = localPed->GetPosition();
		spawnMatrix = CMatrix(pos.x, pos.y, pos.z + 2.0f);
	}
	else {
		Logger::Error("No local ped found.");
	}

	// Base on CPlayersManager::CreatePlayer

	CPlayerData *const playerData = new CPlayerData();
	ASSERT(playerData);

	CPlayerData **const playerDatas = (CPlayerData **)(Offsets::CalculateAddress(0x011A7008));
	playerDatas[playerId] = playerData;

	const Address_t unknownAddress = Offsets::CalculateAddress(0x11A7108);
	unsigned unknown = ReadMemValue<unsigned>(unknownAddress) + 1;
	WriteMemValue<unsigned>(unknownAddress, unknown);

	unsigned *playerIndexes = (unsigned *)(Offsets::CalculateAddress(0x011A7088));
	playerIndexes[playerId] = unknown;

	playerData->m_playerIndex = static_cast<uint8>(playerId);

	bool unknownParam = true; /** isLocalPlayer (???) */

	uint8 creationFlags[2] = { 0, 1 };
	unknownParam = true;
	//if (playerId == 0) {
	//	creationFlags[0] = 0;
	//	creationFlags[1] = 1;
	//	unknownParam = true;
	//}

	CPlayerPed *const ped = CPedFactoryNY::Instance()->CreatePlayerPed(&creationFlags, modelIndex, playerId, &spawnMatrix, unknownParam);
	ASSERT(ped);

	ped->m_unknown905 = 100;
	playerData->SetPlayerPed(ped);

	if (playerId == 0) {
		localPed = ped;
	}

	//CNetObjPlayer *netPlayer = nullptr;
	//if (playerId > 0) {
	//	netPlayer = CreatePlayerNetObj(ped, true, true);
	//	ped->m_networkObject = netPlayer;
	//}

	playerData->m_unknown1244 = 2;

	ped->SetCharCreatedBy(PED_CREATOR_SCRIPT);

	CWorld::sub_806D40(ped);
	CWorld::sub_817350(ped, 0);

	CTaskComplexPlayerOnFoot *const task = ped->m_pedMoveBlendOnFoot->CreatePlayerOnFootTask();
	ped->m_intelligence->m_eventGroup.Add(task, 4, 0);

	if (playerId > 0) {
		//CVector position(spawnMatrix(3, 0), spawnMatrix(3, 1), spawnMatrix(3, 2));
		//sub_817DF0(ped, position);
		//playerData->m_unknown1388->m_unknown32 = 5;

		//sub_49DE00(netPlayer);

		//CTaskSimpleStandStill *const task = new (CPool::TaskPoolInstance()->New_2()) CTaskSimpleStandStill(999999, 1, 0, 8.0f);
		//CTaskSimpleNetworkClone *const task = CTaskSimpleNetworkClone::Create();
		//CTaskComplexPlayerOnFoot *const task = ped->m_pedMoveBlendOnFoot->CreatePlayerOnFootTask();
		//ped->m_intelligence->m_eventGroup.Add(task, 4, 0);

		static const char rpNames[][32] = { "Antoni Macierewicz", "Jaroslaw Kaczynski", "Andrzej Duda", "Anna Grodzka" };

		Logger::Msg("536 = %u, 537 = %u", ped->m_unknown536, ped->m_unknown537);
		//CUnk__PlayerNames::Instance()->SetPlayerNameVisible(playerId, true);
		const unsigned color = 0xFFFF8000;
		CUnk__PlayerNames::Instance()->SetPedNetworkNameAndColor(ped, rpNames[playerId % ARRAY_LENGTH(rpNames)], &color);
	}

	++ playerId;

	// CPlayersManager::ms_localPlayerIndex = 0;
	WriteMemValue<unsigned>(Offsets::CalculateAddress(0x00F1CC68), 0);
}

Address_t addr_TickScriptingThreads = 0;
bool _declspec(naked) TickScriptingThreads(signed int a1)
{
	_asm jmp addr_TickScriptingThreads
}

static bool localPedCreated = false;
namespace rage {
struct scrThread
{
	uint32 vtable;
	uint32 active;
	uint32 field_8;
	uint32 field_12;
	uint32 field_16;
	uint32 field_20;
	uint32 field_24;
	uint32 field_28;
	uint32 field_32;
	uint32 field_36;
	uint32 field_40;
	uint32 field_44;
	uint32 field_48;
	uint32 field_52;
	uint32 field_56;
	uint32 field_60;
	uint32 field_64;
	uint32 field_68;
	uint32 field_72;
	uint32 field_76;
	uint32 field_80;
	uint32 field_84;
	uint32 field_88;
	uint32 field_92;
	uint32 protected_buffer_xlive__field_96;
	uint32 field_100;
	uint32 field_104;
	const char *last_error__field_108;
};
};

struct GtaThread : rage::scrThread
{
	uint8 field_108;
	uint8 field_109;
	uint8 field_110;
	uint8 field_111;
	uint32 field_112;
	uint32 field_116;
	uint32 field_120;
	uint32 field_124;
	uint32 field_128;
	uint32 field_132;
	uint32 field_136;
	uint32 field_140;
	uint8 field_144;
	uint8 field_145;
	uint8 field_146;
	uint8 field_147;
	uint8 field_148;
	uint8 field_149;
	uint8 field_150;
	uint8 field_151;
	uint8 field_152;
	uint8 field_153;
	uint8 field_154;
	uint8 field_155;
	uint32 field_156;
	uint8 field_160;
	uint8 field_161;
	uint8 field_162;
	uint8 field_163;
	uint32 field_164;
	uint32 field_168;
};

AutoPtr<GtaThread> gameScript;

GtaThread *GetCurrentScriptInstance(void)
{
	return gameScript;
}

Address_t CreateCamScriptFadeoutInstruction_addr = 0;
int _declspec(naked) _stdcall CreateCamScriptFadeoutInstruction(const int duration) // returns cam instruction
{
	_asm jmp CreateCamScriptFadeoutInstruction_addr;
}

Address_t CreateCamScriptFadeinInstruction_addr = 0;
int _declspec(naked) _stdcall CreateCamScriptFadeinInstruction(const int duration) // returns cam instruction
{
	_asm jmp CreateCamScriptFadeinInstruction_addr;
}

Address_t CCamManager__SetCurrentCamInstruction_addr = 0;
class CCamManager
{
public:
	int SetCurrentCamInstruction(int instruction);

	static CCamManager *Instance(void)
	{
		return (CCamManager *)Offsets::CalculateAddress(0x0168F910);
	}
};

int _declspec(naked) CCamManager::SetCurrentCamInstruction(int instruction)
{
	_asm jmp CCamManager__SetCurrentCamInstruction_addr;
}

unsigned fadeInTimer = Nil();


void _declspec(naked) SetRadarScale(const float scale)
{
	_asm jmp Offsets::Global::SetRadarScale;
}

bool _cdecl MyLoopHook(signed int a1)
{
	if (!localPedCreated) {
		/* Disable all threads.
		const uint16 scriptThreadsCount = ReadMemValue<uint16>(Offsets::CalculateAddress(0x01983314));
		Logger::Msg("%u", scriptThreadsCount);
		GtaThread **const threads = (GtaThread **)Offsets::CalculateAddress(0x01983310);

		for (uint16 i = 0; i < scriptThreadsCount; ++i) {
			if (threads[i]) {
				threads[i]->active = 0;
			}
		}*/

		DoCreatePlayerPedTest();

		fadeInTimer = 4;
		localPedCreated = true;
	}

	if (NotNil(fadeInTimer)) {
		if (--fadeInTimer == 0) {
			int instruction = CreateCamScriptFadeinInstruction(1);
			CCamManager::Instance()->SetCurrentCamInstruction(instruction);
			fadeInTimer = Nil();
		}
	}


	//Logger::Msg("MyLoopHook");
	static bool wasPressed = false;
	if (GetAsyncKeyState(VK_F6)) {
		if (!wasPressed) {
			DoCreatePlayerPedTest();
			wasPressed = true;
		}
	}
	else {
		wasPressed = false;
	}

	if(GetAsyncKeyState(VK_F7)) {
		CPlayerData *const data = GetPlayerDataByIndex(0);
		if (data) {
			CPed *const ped = data->m_ped;

			CVector newPosition = ped->GetPosition();
			newPosition.z += 2.0f;

			ped->SetPosition(newPosition, 0, 0);
		}
	}

	return 1;
	//return TickScriptingThreads(a1);
}

LONG WINAPI HandleException(EXCEPTION_POINTERS *ExceptionInfo)
{
	char crashInfo[512] = { 0 };
	sprintf(crashInfo, "Crash at %X (%X).", (Address_t)ExceptionInfo->ExceptionRecord->ExceptionAddress, (Address_t)ExceptionInfo->ExceptionRecord->ExceptionCode);
	MessageBox(NULL, crashInfo, "Game crashed", MB_ICONERROR);
	return EXCEPTION_CONTINUE_SEARCH;
}

GtaThread *CreateScriptThread(const char *const a1, int a2, int a3, int a4)
{
	return nullptr;
}

static bool _cdecl IsPedLocal(CPed *const ped)
{
	if (! localPed) {
		return true;
	}

	return ped == localPed;
}

Address_t CPed__Process_addr = 0;
Address_t CPlayerPed__Process_addr = 0;

class CPlayerPedHook
{
public:
	bool Process(void);
};

bool CPlayerPedHook::Process(void)
{
	bool result = false;
	//Address_t method = CPed__sub_8AADC0_addr;
	const bool isLocalPed = localPed == 0 || static_cast<CPlayerPed *>((void *)this) == localPed;
	//if (isLocalPed) {
		//method = CPlayerPed__sub_9C0B00_addr;
	//}

	CPed *const ped = static_cast<CPed *>((void *)this);

	if (!isLocalPed) {
		WriteMemValue<uint8>(Offsets::CalculateAddress(0x10D0170), 1);
		//ped->m_unknown536 = 1;
		//ped->m_unknown537 = 1;
	}

	_asm {
		mov ecx, this ; just to ensure that ecx == this
		call CPlayerPed__Process_addr
		mov result, al
	}

	if (!isLocalPed) {
		WriteMemValue<uint8>(Offsets::CalculateAddress(0x10D0170), 0);
		//ped->m_unknown536 = 0;
		//ped->m_unknown537 = 1;
	}

	return result;
}

void GameHooks::Install(void)
{
	XLiveHooks::Install();

	SetUnhandledExceptionFilter(HandleException);

	// Always start new game
	Hooking::InstallPermJmpHook(Offsets::CalculateAddress(0x005B0311), Offsets::CalculateAddress(0x005B03BF));
	////Skip main menu
	//Hooking::InstallPermJmpHook(Offsets::CalculateAddress(0x00402B3C), Offsets::CalculateAddress(0x00402C07));
	//Hooking::InstallPermJmpHook(Offsets::CalculateAddress(0x00420853), Offsets::CalculateAddress(0x004208ED));


	// Disable traffic.
	// TODO: Can we do it better? NOOP'ing 51 bytes seems not the best solution
	// maybe changing jnz to jz would also work - once we will need to test it.
	MemSet((void *)Offsets::CalculateAddress(0x00841FB7), 0x90, 51);

	CPed__Process_addr = Offsets::CalculateAddress(0x008AADC0);
	CPlayerPed__Process_addr = Offsets::CalculateAddress(0x009C0B00);

	//MemSet((void *)Offsets::CalculateAddress(0x009C0B29), 0x90, 42);

	//CPlayerPed__sub_9C0B00__retn = Offsets::CalculateAddress(0x009C0B06);
	//Hooking::InstallPermJmpHook(Offsets::CalculateAddress(0x009C0B00), (Address_t)CPlayerPed__sub_9C0B00__hook);

	bool (__thiscall CPlayerPedHook::*method)(void) = &CPlayerPedHook::Process;
	WriteMemValue<Address_t>(Offsets::CalculateAddress(0x00D81A38), (Address_t)((void *&)method));

	gameScript = new GtaThread();
	memset(gameScript, 0, sizeof(GtaThread));

	sub_817DF0_addr = Offsets::CalculateAddress(0x00817DF0);
	sub_49DE00_addr = Offsets::CalculateAddress(0x0049DE00);

	CreatePlayerNetObj_addr = Offsets::CalculateAddress(0x00474180);

	CreateCamScriptFadeoutInstruction_addr = Offsets::CalculateAddress(0x00AFD240);
	CreateCamScriptFadeinInstruction_addr = Offsets::CalculateAddress(0x00AFD1D0);

	SetPedNetworkNameAndColor_addr = Offsets::CalculateAddress(0x004789D0);
	SetPlayerNameVisible_addr = Offsets::CalculateAddress(0x00478B70);

	CCamManager__SetCurrentCamInstruction_addr = Offsets::CalculateAddress(0x00AFEA00);

	//WriteMemValue<Address_t>(Offsets::CalculateAddress(0x00FE78C4), (Address_t)CreateScriptThread);

	addr_TickScriptingThreads = Offsets::CalculateAddress(0x005A6010);
	Hooking::InstallPermCallHook(Offsets::CalculateAddress(0x0080A092), (Address_t)MyLoopHook);

	Hooking::InstallPermJmpHook(Offsets::CalculateAddress(0x005A4CA0), (Address_t)GetCurrentScriptInstance);

	// Disable parked vehicles. (Has to be tested however on first sight works fine).
	Hooking::InstallPermJmpHook(Offsets::CalculateAddress(0x00B3E4D0), Offsets::CalculateAddress(0x00B3E50F));

	// Disable pedestrians.
	MemSet((void *)Offsets::CalculateAddress(0x004215D9), 0x90, 5);

#ifdef DEBUG_PED_CREATION
	CPedFactoryNY__CreatePed__retn = Offsets::CalculateAddress(0x0043A008);
	Hooking::InstallPermJmpHook(Offsets::CalculateAddress(0x0043A000), (Address_t)CPedFactoryNY__CreatePed__hook);

	CPedFactoryNY__CreateScenarioPed__retn = Offsets::CalculateAddress(0x0043A176);
	Hooking::InstallPermJmpHook(Offsets::CalculateAddress(0x0043A170), (Address_t)CPedFactoryNY__CreateScenarioPed__hook);
#endif

#ifdef DEBUG_VEH_CREATION
	CVehicleFactoryNY__Create__retn = Offsets::CalculateAddress(0x00443D66);
	Hooking::InstallPermJmpHook(Offsets::CalculateAddress(0x00443D60), (Address_t)CVehicleFactoryNY__Create__hook);
#endif
}

/* eof */
