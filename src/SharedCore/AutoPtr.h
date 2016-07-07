// Copyright (C) 2016 by DVO Games

#pragma once

#include "Memory/MemFunctions.h"

#include "Debug/Debug.h"

/**
 * Auto pointer class.
 *
 * Suitable for objects.
 */
template <typename OBJECT_TYPE>
class AutoPtr
{
public:
	using ObjectType = OBJECT_TYPE;
private:
	mutable ObjectType	*m_object;

public:
			AutoPtr		()
		: m_object(nullptr)
	{
	}

			AutoPtr		(const AutoPtr& ptr)
		: m_object(nullptr)
	{
		Transfer(ptr);
	}

explicit	AutoPtr		(ObjectType* const object)
	{
		m_object = object;
	}

			~AutoPtr	()
	{
		Reset();
	}

	/**
	 * Reset object hold by the pointer.
	 */
	void	Reset		(void)
	{
		if (m_object) {
			// Call the correct deleter for the object type.
			DeleteCompleteObject(m_object);

			m_object = nullptr;
		}
	}

	/**
	 * Transfer object from different auto pointer.
	 *
	 * @param[in] ptr The auto pointer from which we take the object.
	 */
	void	Transfer	(const AutoPtr& ptr)
	{
		Reset();

		m_object = ptr.m_object;
		ptr.m_object = nullptr;
	}

	/**
	 * Release object hold by this auto pointer.
	 *
	 * @return Object hold by this auto pointer. Can be nullptr if no object is hold.
	 */
	ObjectType* Release	(void)
	{
		ObjectType* const object = m_object;
		m_object = nullptr;
		return object;
	}

	/**
	 * Assign object.
	 *
	 * @param[in] ptr The object.
	 */
	void	Assign	(ObjectType* const ptr)
	{
		Reset();

		m_object = ptr;
	}

	/**
	 * Move assignment operator.
	 */
	void	operator=	(const AutoPtr& ptr)
	{
		Transfer(ptr);
	}

	/**
	 * Move assignment operator.
	 */
	void	operator=	(ObjectType* const ptr)
	{
		Assign(ptr);
	}

	/**
	 * @name Access operators and methods.
	 */
	//@{
	ObjectType* Get		(void)
	{
		ASSERT(m_object);
		return m_object;
	}

	ObjectType* Get		(void) const
	{
		ASSERT(m_object);
		return m_object;
	}

	ObjectType* operator->	(void)	const	{ return Get(); }
	ObjectType* operator*	(void)	const	{ return Get(); }

	operator ObjectType&	(void) const	{ return *Get(); }
	operator ObjectType*	(void) const	{ return Get(); }
	//@}

	//! Is auto pointer valid.
	bool IsValid(void) const
	{
		return m_object != nullptr;
	}

	//! Is auto pointer valid.
	operator bool() const
	{
		return IsValid();
	}

	bool operator==(const AutoPtr& autoPtr) const
	{
		return m_object == autoPtr.m_object;
	}

	bool operator!=(const AutoPtr& autoPtr) const
	{
		return m_object != autoPtr.m_object;
	}
};

/**
 * Auto pointer class.
 *
 * Suitable for arrays.
 */
template <typename OBJECT_TYPE>
class AutoPtr<OBJECT_TYPE[]>
{
public:
	using ObjectType = OBJECT_TYPE;
private:
	mutable ObjectType	*m_object;

public:
			AutoPtr		()
		: m_object(nullptr)
	{
	}

			AutoPtr		(const AutoPtr& ptr)
	{
		Transfer(ptr);
	}

explicit	AutoPtr		(ObjectType* const object)
	{
		m_object = object;
	}

			~AutoPtr	()
	{
		Reset();
	}

	/**
	 * Reset object hold by the pointer.
	 */
	void	Reset		(void)
	{
		if (m_object) {
			// Call the correct deleter for the object type.
			DeleteCompleteArray(m_object);

			m_object = nullptr;
		}
	}

	/**
	 * Transfer object from different auto pointer.
	 *
	 * @param[in] ptr The auto pointer from which we take the object.
	 */
	void	Transfer	(const AutoPtr& ptr)
	{
		Reset();

		m_object = ptr.m_object;
		ptr.m_object = nullptr;
	}

	/**
	 * Release object hold by this auto pointer.
	 *
	 * @return Object hold by this auto pointer. Can be nullptr if no object is hold.
	 */
	ObjectType* Release	(void)
	{
		ObjectType* const object = m_object;
		m_object = nullptr;
		return object;
	}

	/**
	 * Assign object.
	 *
	 * @param[in] ptr The object.
	 */
	void	Assign	(ObjectType* const ptr)
	{
		Reset();

		m_object = ptr;
	}

	/**
	 * Move assignment operator.
	 */
	void	operator=	(AutoPtr& ptr)
	{
		Transfer(ptr);
	}

	/**
	 * Move assignment operator.
	 */
	void	operator=	(ObjectType* const ptr)
	{
		Assign(ptr);
	}

	/**
	 * @name Access operators and methods.
	 */
	//@{
	ObjectType* Get		(void)
	{
		ASSERT(m_object);
		return m_object;
	}

	ObjectType* Get		(void) const
	{
		ASSERT(m_object);
		return m_object;
	}

	ObjectType* operator->	(void)			{ return Get(); }
	ObjectType* operator->	(void)	const	{ return Get(); }
	ObjectType* operator*	(void)	const	{ return Get(); }
	//@}

	/**
	 * Array accessing functionallity.
	 */
	//@{
	ObjectType& operator[](const size_t index) const
	{
		return m_object[index];
	}
	//@}

	//! Is auto pointer valid.
	bool IsValid(void) const
	{
		return m_object != nullptr;
	}

	//! Is auto pointer valid.
	operator bool() const
	{
		return IsValid();
	}

	bool operator==(const AutoPtr& autoPtr) const
	{
		return m_object == autoPtr.m_object;
	}

	bool operator!=(const AutoPtr& autoPtr) const
	{
		return m_object != autoPtr.m_object;
	}
};

/* eof */
