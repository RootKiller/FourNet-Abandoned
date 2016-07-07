// Copyright (C) 2016 by DVO Games

#pragma once

#include "Memory/MemFunctions.h"

/**
 * Fixed allocator allocating memory on heap.
 *
 * This allocator allocates only __SIZE__ amount of elements and it is not possible
 * to change it later.
 */
template <typename ELEMENT_TYPE, unsigned SIZE>
class FixedHeapAllocator : public BaseAllocator<ELEMENT_TYPE>
{
	SUPER_CLASS(BaseAllocator<ELEMENT_TYPE>)
private:
	ElementType			*m_data;

public:
	// Constructor.
						FixedHeapAllocator()
		: m_data(nullptr)
	{
	}

	// Destructor.
						~FixedHeapAllocator() override
	{
		if (m_data) {
			DeleteCompleteArray(m_data);
		}
		m_data = nullptr;
	}

	/**
	 * @see BaseAllocator::Alloc
	 */
	ElementType*		Alloc(const unsigned count = 1) override
	{
		ASSERT(count <= SIZE);
		if (!m_data) {
			m_data = new ElementType[SIZE];
		}
		return m_data;
	}

	/**
	 * @see BaseAllocator::Realloc
	 */
	ElementType*		Realloc(const unsigned count = 1) override
	{
		ASSERT(m_data);
		return Super::Realloc(count);
	}

	/**
	 * @see BaseAllocator::Free
	 */
	void				Free(void) override
	{
	}

	/**
	 * @see BaseAllocator::GetSize
	 */
	unsigned			GetSize(void) const override
	{
		return SIZE;
	}

	/**
	 * @see BaseAllocator::GetBytesSize
	 */
	unsigned			GetBytesSize(void) const override
	{
		return SIZE * sizeof(ElementType);
	}

	/**
	 * @see BaseAllocator::IsDynamic
	 */
	bool				IsDynamic(void) const override
	{
		return false;
	}

	FixedHeapAllocator(const FixedHeapAllocator& alloc) = delete;
	FixedHeapAllocator& operator=(const FixedHeapAllocator& alloc) = delete;

	FixedHeapAllocator(const FixedHeapAllocator&& alloc) = delete;
	FixedHeapAllocator& operator=(FixedHeapAllocator&& alloc)
	{
		Free();

		m_data = alloc.m_data;

		alloc.m_data = nullptr;
		return *this;
	}
};

/* EOF */
