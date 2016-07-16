// Copyright (C) 2016 by Rage MP Team

#pragma once

class CGameAllocator
{
public:
	/**
	 * Allocate memory with default alignment of 16 bytes.
	 *
	 * @param[in] size The count of the bytes to allocate.
	 * @return Pointer to the allocated memory if allocation sucess
	 *         and (likely - not tested) @c nullptr in case out of memory.
	 */
	static void *Alloc(const size_t size);

	/**
	 * Allocate memory with specified alignment.
	 *
	 * @param[in] size The count of the bytes to allocate.
	 * @param[in] alignment The alignment of the allocated memory.
	 * @return Pointer to the allocated memory if allocation sucess
	 *         and (likely - not tested) @c nullptr in case out of memory.
	 */
	static void *AllocAligned(const size_t size, const size_t alignment = 16);

	/**
	 * Free memory allocated by game allocator.
	 *
	 * @param[in] memory The memory to free. (can be @c nullptr)
	 * @return ?
	 */
	static int Free(void *const memory);
};

#define GAME_ALLOC_OBJECT\
	void *operator new(const size_t size) { return CGameAllocator::Alloc(size); }\
	void operator delete(void *ptr) { CGameAllocator::Free(ptr); }\
	void *operator new[](size_t count) = delete;\
	void operator delete[](void *ptr) = delete;



/* eof */
