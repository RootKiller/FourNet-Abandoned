// Copyright (C) 2016 by DVO Games

#pragma once

#include "Memory/MemFunctions.h"

/**
 * Fixed allocator allocating memory as member class of the allocator.
 *
 * This allocator allocates only __SIZE__ amount of elements and it is not possible
 * to change it later.
 */
template <typename ELEMENT_TYPE, unsigned SIZE>
class FixedAllocator : public BaseAllocator<ELEMENT_TYPE>
{
private:
	ElementType			m_data[SIZE];

	bool				m_allocated;

public:
	// Constructor.
						FixedAllocator()
		: m_allocated(false)
	{
	}

	// Destructor.
						~FixedAllocator() override
	{
	}

	/**
	 * @see BaseAllocator::Alloc
	 */
	ElementType*		Alloc(const unsigned count = 1) override
	{
		ASSERT(count <= SIZE);
		ASSERT(!m_allocated);

		if (m_allocated) {
			return nullptr;
		}
		m_allocated = true;
		return m_data;
	}

	/**
	 * @see BaseAllocator::Free
	 */
	void				Free(void) override
	{
		m_allocated = false;
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

	FixedAllocator(const FixedAllocator& alloc) = delete;
	FixedAllocator& operator=(const FixedAllocator& alloc) = delete;

	FixedAllocator(const FixedAllocator&& alloc) = delete;
	FixedAllocator& operator=(FixedAllocator&& alloc)
	{
		Free();

		MemMove(m_data, alloc.m_data, GetBytesSize());
		return *this;
	}
};

/* EOF */
