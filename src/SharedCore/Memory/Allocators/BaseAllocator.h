// Copyright (C) 2016 by DVO Games

#pragma once

/**
 * One-time allocator base class.
 *
 * This allocator can be used to allocate buffer used by some class for example String.
 *
 * Calling Alloc twice is not allowed - you have to free memory hold by this allocator
 * using the Free method and then you can use Alloc again.
 *
 * (Or you can simply call Realloc which frees the memory internally)
 */
template <typename ELEMENT_TYPE>
class BaseAllocator
{
public:
	typedef ELEMENT_TYPE ElementType;

	// Dummy default constructor.
							BaseAllocator	() {};

	// Dummy destructor.
	virtual					~BaseAllocator	() {};

	/**
	 * Allocate given counts of elements.
	 *
	 * In debug build implementation should cause assert when user is trying
	 * to allocate something when there is already some object hold.
	 * But in release builds implementation should simply return @c nullptr.
	 *
	 * @param[in] count The count of elements to be allocated.
	 * @return Pointer to the allocated memory or @c nullptr in case allocation
	 *         was not possible.
	 */
	virtual ElementType*	Alloc			(const unsigned count = 1)	= 0;

	/**
	 * Reallocate storage to the given count of elements.
	 *
	 * Performs free of the currently hold buffer and allocates new one.
	 *
	 * @param[in] count The count of elements to be allocated.
	 * @return Pointer to the allocated memory or @c nullptr in case allocation
	 *         was not possible.
	 */
	virtual ElementType*	Realloc			(const unsigned count = 1)
	{
		Free();
		return Alloc(count);
	}

	/**
	 * Free buffer currently hold by allocator.
	 *
	 * Implementation should allow calling this method even if nothing is allocated.
	 */
	virtual void			Free			(void)						= 0;

	/**
	 * Get number of element allocated by this allocator.
	 */
	virtual unsigned		GetSize			(void) const				= 0;

	/**
	 * Get number of bytes allocated by this allocator.
	 */
	virtual unsigned		GetBytesSize	(void) const				= 0;

	/**
	 * Is allocator dynamic?
	 */
	virtual bool			IsDynamic		(void) const				= 0;

	// By default all allocators have copy and move semantic disabled.
							BaseAllocator	(const BaseAllocator& alloc) = delete;
	BaseAllocator&			operator=		(const BaseAllocator& alloc) = delete;

							BaseAllocator	(const BaseAllocator&& alloc) = delete;
	BaseAllocator&			operator=		(BaseAllocator&& alloc) = delete;
};

/* EOF */
