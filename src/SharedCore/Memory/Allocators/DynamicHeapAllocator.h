// Copyright (C) 2016 by DVO Games

#pragma once

/**
 * Dynamic allocator allocating memory on the heap.
 *
 * This allocator can allocate any amount of elements (up to platform memory limits of course)
 */
template <typename ELEMENT_TYPE>
class DynamicHeapAllocator : public BaseAllocator<ELEMENT_TYPE>
{
private:
	ElementType			*m_data;

	unsigned			m_dataSize;

public:
	// Constructor.
						DynamicHeapAllocator()
		: m_data(nullptr)
		, m_dataSize(0)
	{

	}

	// Destructor.
						~DynamicHeapAllocator() override
	{
		Free();
	}

	/**
	 * @see BaseAllocator::Alloc
	 */
	ElementType*		Alloc(const unsigned count = 1) override
	{
		ASSERT(! m_data);

		// In case the memory was already allocated in debug build return nullptr
		// and let the user take care about eventual allocation problems.
		if (m_data) {
			return nullptr;
		}

		m_dataSize = count * sizeof(ElementType);
		m_data = new ElementType[count];
		return m_data;
	}

	/**
	 * @see BaseAllocator::Free
	 */
	void				Free(void) override
	{
		if (m_data) {
			DeleteCompleteArray(m_data);
			m_data = nullptr;
		}
		m_dataSize = 0;
	}

	/**
	 * @see BaseAllocator::GetSize
	 */
	unsigned GetSize(void) const override
	{
		return m_dataSize;
	}

	/**
	 * @see BaseAllocator::GetBytesSize
	 */
	unsigned GetBytesSize(void) const override
	{
		return m_dataSize;
	}

	/**
	 * @see BaseAllocator::IsDynamic
	 */
	bool IsDynamic(void) const override
	{
		return true;
	}

	DynamicHeapAllocator(const DynamicHeapAllocator& alloc) = delete;
	DynamicHeapAllocator& operator=(const DynamicHeapAllocator& alloc) = delete;

	DynamicHeapAllocator(const DynamicHeapAllocator&& alloc) = delete;
	DynamicHeapAllocator& operator=(DynamicHeapAllocator&& alloc)
	{
		Free();

		m_data = alloc.m_data;
		m_dataSize = alloc.m_dataSize;

		alloc.m_data = nullptr;
		alloc.m_dataSize = 0;
		return *this;
	}
};

/* EOF */
