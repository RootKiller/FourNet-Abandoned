// Copyright (C) 2016 by Rage MP Team

#include "Offsets.h"
#include "Streaming.h"

bool _declspec(naked) CStreaming::RequestSpecialModel(const unsigned modelHash, const unsigned unknown0, const unsigned unknown1)
{
	_asm jmp Offsets::CStreaming::RequestSpecialModel;
}

int _declspec(naked) CStreaming::LoadAllRequestedModels(const bool priorityModelsOnly)
{
	_asm jmp Offsets::CStreaming::LoadAllRequestedModels;
}

void _declspec(naked) CStreaming::RequestModel(const unsigned modelHash, const unsigned unk)
{
	_asm jmp Offsets::CStreaming::RequestModel;
}

bool _declspec(naked) CStreaming::HasModelLoaded(const unsigned modelHash)
{
	_asm jmp Offsets::CStreaming::HasModelLoaded;
}

int _declspec(naked) ModelIndexByModelHash(const unsigned modelHash, int *const modelIndex)
{
	_asm jmp Offsets::Global::ModelIndexByModelHash;
}


/* eof */