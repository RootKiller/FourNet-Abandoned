// Copyright (C) 2016 by DVO Games

#pragma once

#include "Defines.h"
#include "Debug/Debug.h"

/**
 * The class definition
 */
class ClassDefinition
{
private:
	/** Name the stringized name of the class */
	const char*				name;

	/** The parent class defintion */
	const ClassDefinition*	parentClass;

public:
	/**
	 * Constructor.
	 *
	 * @param[in] theName        The name of the class.
	 * @param[in] theParentClass The pointer to the parent class definition (can be nullptr).
	 */
	ClassDefinition(const char *const theName, const ClassDefinition *const theParentClass)
		: name(theName)
		, parentClass(theParentClass)
	{
	}

	/**
	 * Get stringized name of the class.
	 */
	const char *GetName(void) const
	{
		ASSERT_MSG(name, "No name defined for class definition");
		return name;
	}

	/**
	 * Get pointer to the parent class.
	 */
	const ClassDefinition* GetParentClass(void) const
	{
		ASSERT_MSG(parentClass, "No parent class defined for class definition");
		return parentClass;
	}

	friend class BaseClass;
};

/**
 * Base class containing class definition.
 *
 * This is our own RTTI like implementation.
 */
class BaseClass
{
public:
	/**
	 * Get definition of the class (object variant)
	 *
	 * @return This class definition.
	 */
	virtual const ClassDefinition*GetClassDefinition	(void) const = 0;

	/**
	 * Get name of this class (object variant)
	 *
	 * @return Stringized name of this class.
	 */
	virtual const char*			GetClassName		(void) const = 0;

	/**
	 * Get definition of the class (static variant)
	 *
	 * @return This class definition.
	 */
	static const ClassDefinition *GetStaticClassDefinition(void)
	{
		return nullptr;
	}

	/**
	 * Get name of this class (static variant)
	 *
	 * @return Stringized name of this class.
	 */
	static const char *GetStaticClassName(void)
	{
		return "BaseClass";
	}

	/**
	 * Check if this class inherits from class represent by @a theDefinition.
	 *
	 * @param[in] theDefinition The class definition to check this class aganist.
	 * @return @c true if this class inherits from @a theDefinition @c false otherwise.
	 */
	bool	InheritsFrom		(const ClassDefinition *const theDefinition) const
	{
		const ClassDefinition *definition = GetClassDefinition();
		while (definition) {
			if (definition == theDefinition) {
				return true;
			}

			definition = definition->parentClass;
		}
		return false;
	}

	/**
	 * Do safe cast (similar to dynamic_cast in C++) with type checking.
	 *
	 * @tparam CAST_TO_TYPE The type to cast.
	 * @return Cast pointer in case this class inherits from type represent by @a CAST_TO_TYPE
	 *         otherwise @c nullptr.
	 */
	template <typename CAST_TO_TYPE>
	CAST_TO_TYPE *SafeCast		(void)
	{
		if (InheritsFrom(CAST_TO_TYPE::GetStaticClassDefinition())) {
			return static_cast<CAST_TO_TYPE*>(this);
		}
		return nullptr;
	}

	/**
	 * Do safe cast (similar to dynamic_cast in C++) with type checking. (const variant)
	 *
	 * @tparam CAST_TO_TYPE The type to cast.
	 * @return Cast pointer in case this class inherits from type represent by @a CAST_TO_TYPE
	 *         otherwise @c nullptr.
	 */
	template <typename CAST_TO_TYPE>
	const CAST_TO_TYPE *SafeCast	(void) const
	{
		if (InheritsFrom(CAST_TO_TYPE::GetStaticClassDefinition())) {
			return static_cast<const CAST_TO_TYPE*>(this);
		}
		return nullptr;
	}
};

/**
 *
 */
#define CLASS(name)\
private:\
	/** This class definition */ \
	static const ClassDefinition classDefinition;\
public:\
	\
	static const char *GetStaticClassName(void)		{ return STRINGIZE(name); } \
	const char *GetClassName(void) const override	{ return STRINGIZE(name); } \
	\
	static const ClassDefinition *GetStaticClassDefinition(void)		{ return &classDefinition; } \
	const ClassDefinition *GetClassDefinition(void) const override		{ return &classDefinition; } \

#define CLASS_IMPL(name)\
	const ClassDefinition name::classDefinition(STRINGIZE(name), Super::GetStaticClassDefinition())

/* eof */
