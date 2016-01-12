/// Copyright (C) 2016 by EFLC MP Team
#pragma once

/**
 * Base allocator.
 *
 * @todo Documentation for base allocator and classes that derive from it.
 */
template <typename ELEMENT_TYPE>
class BaseAllocator
{
public:
	typedef ELEMENT_TYPE ElementType;

	virtual ElementType*	Alloc			(const unsigned count = 1)	= 0;
	virtual ElementType*	Realloc			(const unsigned count = 1)	= 0;
	virtual void			Free			(void)						= 0;

	virtual unsigned		GetSize			(void) const				= 0;
	virtual unsigned		GetBytesSize	(void) const				= 0;

	virtual bool			IsDynamic		(void) const				= 0;
};

/* EOF */
