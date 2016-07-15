// Copyright (C) 2016 by Rage MP Team

#ifndef INSIDE_OFFSETS_CPP
#error "This file can be included only inside offsets cpp"
#endif

#include "OffsetHelpersBegin.h"

SETUP_OFFSET(Global,				ModelIndexByModelHash);
SETUP_OFFSET(Global,				sub_817350);
SETUP_OFFSET(Global,				sub_806D40);
SETUP_OFFSET(Global,				GetPlayerDataByIndex);

SETUP_OFFSET(CGameAllocator,		Alloc);
SETUP_OFFSET(CGameAllocator,		AllocAligned);
SETUP_OFFSET(CGameAllocator,		Free);

SETUP_OFFSET(CPedFactoryNY,			CreatePed);

SETUP_OFFSET(CStreaming,			RequestSpecialModel);
SETUP_OFFSET(CStreaming,			LoadAllRequestedModels);
SETUP_OFFSET(CStreaming,			RequestModel);
SETUP_OFFSET(CStreaming,			HasModelLoaded);

SETUP_OFFSET(CEventGroup,			Add);

SETUP_OFFSET(CPed,					SetCharCreatedBy);

SETUP_OFFSET(CWorld,				SetLoadCollisionFlag);

SETUP_OFFSET(CTaskSimpleStandStill,	Constructor);

SETUP_OFFSET(CPool,					New_2);
SETUP_OFFSET(CPool,					ms_taskPool);

// Your offsets lands here.

#include "OffsetsHelpersEnd.h"

/* eof */
