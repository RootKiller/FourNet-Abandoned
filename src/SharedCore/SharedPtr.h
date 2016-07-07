// Copyright (C) 2016 by DVO Games

#pragma once

#include "Debug/Debug.h"

/**
 * Shared pointer object.
 *
 * @note Object held by this smart pointer must inherit from RefCountObject class or implement
 *       AddRef and ReleaseRef methods.
 */
template <typename OBJECT_TYPE>
class SharedPtr
{
private:
	/** Object hold by the smart pointer */
	OBJECT_TYPE			*m_object;
public:
	/** Default constructor. */
	SharedPtr()
		: m_object(nullptr)
	{
	}

	/** Copy constructor */
			SharedPtr		(const SharedPtr& ptr)
		: m_object(nullptr)
	{
		(*this) = ptr;
	}

	/** Move constructor */
			SharedPtr		(SharedPtr&& ptr)
		: m_object(nullptr)
	{
		(*this) = ptr;
	}

	/** Assign constructor */
	explicit SharedPtr		(OBJECT_TYPE* const object)
	{
		m_object = object;
		if (m_object) {
			m_object->AddRef();
		}
	}

			~SharedPtr		()
	{
		Reset();
	}

	void Reset(void)
	{
		if (m_object) {
			m_object->ReleaseRef();
			m_object = nullptr;
		}
	}

	SharedPtr& operator=(const SharedPtr& ptr)
	{
		Reset();
		m_object = ptr.m_object;
		m_object->AddRef();
		return *this;
	}

	SharedPtr& operator=(OBJECT_TYPE* const object)
	{
		Reset();

		m_object = object;
		if (m_object) {
			m_object->AddRef();
		}
		return *this;
	}

	SharedPtr& operator=(SharedPtr&& ptr)
	{
		Reset();

		m_object = ptr.m_object;
		ptr.m_object = nullptr;
		return *this;
	}

	/**
	 * @name Access operators and methods.
	 */
	//@{
	OBJECT_TYPE* Get		(void)
	{
		ASSERT(m_object);
		return m_object;
	}

	OBJECT_TYPE* Get		(void) const
	{
		ASSERT(m_object);
		return m_object;
	}

	OBJECT_TYPE* operator->	(void)	const	{ return Get(); }

	operator OBJECT_TYPE*	(void) const	{ return Get(); }
	//@}

	//! Is shared pointer valid.
	bool IsValid(void) const
	{
		return m_object != nullptr;
	}

	//! Is shared pointer valid.
	operator bool() const
	{
		return IsValid();
	}

	//! Equal operator.
	bool operator ==(const SharedPtr& rhs) const
	{
		return m_object == rhs.m_object;
	}

	//! Not equal operator.
	bool operator !=(const SharedPtr& rhs) const
	{
		return m_object != rhs.m_object;
	}

};

/* eof */
