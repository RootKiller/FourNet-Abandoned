// Copyright (C) 2016 by DVO Games

#include <Windows.h>
#include <stdio.h>

#include "Hooking.h"

#include "Strings.h"

#include "Memory/MemFunctions.h"

#include "OS/OS.h"

#include <list>

typedef AString8 SegmentName_t;

std::list<const uint8 *> trampolines;
std::list<SegmentName_t> segmentsToUnlock;

static bool IsSectionToUnlock(const char *const name)
{
	if (!strcmp(name, "text")) {
		return true;
	}

	if (!strcmp(name, "idata")) {
		return true;
	}

	if (!strcmp(name, "rdata")) {
		return true;
	}

	if (!strcmp(name, "data")) {
		return true;
	}

	if (!strcmp(name, "tls")) {
		return true;
	}
	return false;
}

uint32 UnprotectMemory(void *start, const size_t size)
{
	uint32 oldProtect = 0;
	VirtualProtect(start, size, PAGE_EXECUTE_READWRITE, reinterpret_cast<PDWORD>(&oldProtect));
	return oldProtect;
}

uint32 ReprotectMemory(void *start, const size_t size, uint32 oldProtect)
{
	VirtualProtect(start, size, oldProtect, reinterpret_cast<PDWORD>(&oldProtect));
	return oldProtect;
}

void Hooking::Init(void)
{
	const PBYTE imageBase = reinterpret_cast<PBYTE>(GetModuleHandle(NULL));
	const IMAGE_DOS_HEADER *const dosHeader = reinterpret_cast<IMAGE_DOS_HEADER *>(imageBase);
	const IMAGE_NT_HEADERS *const ntHeaders = reinterpret_cast<IMAGE_NT_HEADERS *>(imageBase + dosHeader->e_lfanew);
	const IMAGE_SECTION_HEADER *sectionHeader = IMAGE_FIRST_SECTION(ntHeaders);

	// Loop thought all sections
	for (unsigned sec = 0; sec < ntHeaders->FileHeader.NumberOfSections; sec++, sectionHeader++) {
		if (!sectionHeader->Name || *sectionHeader->Name == 0) {
			continue;
		}

		if (IsSectionToUnlock(reinterpret_cast<const char *>(sectionHeader->Name + 1))) {
			UnprotectMemory(static_cast<void *>(imageBase + sectionHeader->VirtualAddress), ((sectionHeader->Misc.VirtualSize + 4095)&~4095));
		}
	}
}

void Hooking::Shutdown(void)
{
	ASSERT_MSG(trampolines.empty(), "JMP HOOK MEMORY LEAK DETECTED");
}


const uint8 X86_JMP_OPCODE = 0xE9;
const uint8 X86_CALL_OPCODE = 0xE8;

const size_t JMP_HOOK_SIZE = 5; // OP AA BB CC DD
const size_t CALL_HOOK_SIZE = 5;

static_assert(JMP_HOOK_SIZE == CALL_HOOK_SIZE, "Hook sizes are not equal, correct that.");
const size_t HOOK_SIZE = 5;

static void Hook(const Address_t address, const Address_t hook, const uint8 opcode)
{
	*(uint8 *)address = opcode;
	*(uint32 *)(address + 1) = hook - (address + 5);
}

void Hooking::InstallPermJmpHook(const Address_t from, const Address_t to)
{
	const uint32 oldProtect = UnprotectMemory(reinterpret_cast<void *>(from), HOOK_SIZE);
		Hook(from, to, X86_JMP_OPCODE);
	ReprotectMemory(reinterpret_cast<void *>(from), HOOK_SIZE, oldProtect);
}

void Hooking::InstallPermCallHook(const Address_t where, const Address_t to)
{
	const uint32 oldProtect = UnprotectMemory(reinterpret_cast<void *>(where), HOOK_SIZE);
		Hook(where, to, X86_CALL_OPCODE);
	ReprotectMemory(reinterpret_cast<void *>(where), HOOK_SIZE, oldProtect);
}

const size_t TRAMPOLINE_CODE_SIZE = JMP_HOOK_SIZE * 2;
const size_t TRAMPOLINE_BUFFER_SIZE = TRAMPOLINE_CODE_SIZE;

const Address_t *Hooking::InstallJmpHook(const Address_t from, const Address_t to)
{
	uint8 *const trampoline = new uint8[TRAMPOLINE_BUFFER_SIZE];
	{
		const uint8 *const source = reinterpret_cast<uint8 *>(from);

		MemCpy(trampoline, source, JMP_HOOK_SIZE);

		Hook(reinterpret_cast<Address_t>(trampoline + JMP_HOOK_SIZE), from + JMP_HOOK_SIZE, X86_JMP_OPCODE);
		InstallPermJmpHook(from, to);
	}

	trampolines.push_back(trampoline);
	return reinterpret_cast<Address_t *>(trampoline);
}

void Hooking::UninstallJmpHook(const Address_t original, const Address_t *const addr)
{
	if (std::find(trampolines.begin(), trampolines.end(), reinterpret_cast<const uint8 *>(addr)) == trampolines.end()) {
		ASSERT_MSG(false, "Tried to uninstall hook that is not installed?");
		return;
	}

	const uint8 *const trampoline = reinterpret_cast<const uint8 *>(addr);

	void *const fromPtr = reinterpret_cast<void *>(original);
	const uint32 oldProtect = UnprotectMemory(fromPtr, JMP_HOOK_SIZE);
	{
		MemCpy(static_cast<uint8 *>(fromPtr), trampoline, JMP_HOOK_SIZE);
	}
	ReprotectMemory(fromPtr, JMP_HOOK_SIZE, oldProtect);

	trampolines.remove(trampoline);
	delete []trampoline;
}

/* eof */
