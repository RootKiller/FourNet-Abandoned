// Copyright (C) 2016 by DVO Games

#pragma once

#include "Debug/Debug.h"
#include "Types.h"

/**
 * Base class of the object with reference counting semantics.
 */
class RefCountObject
{
private:
	/** Count of the references */
	uint32		m_referenceCount;
public:
	/** Constructor */
	RefCountObject()
	{
	}

	/** Destructor */
	virtual ~RefCountObject()
	{
		ASSERT(m_referenceCount == 0);
	}

	/** Add reference count */
	virtual void AddRef(void)
	{
		++m_referenceCount;
	}

	/** Release reference of the object */
	virtual void ReleaseRef(void)
	{
		ASSERT(m_referenceCount > 0);
		if (--m_referenceCount == 0) {
			delete this;
		}
	}
};

/* eof */
