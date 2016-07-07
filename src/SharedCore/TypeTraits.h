// Copyright (C) 2016 by DVO Games

#pragma once

/**
 * Is given type a vector (c-style array)
 *
 * @tparam OBJECT_TYPE Typeto be checked.
 */
//@{
template <typename OBJECT_TYPE>
struct IsVectorType
{
	static const bool Value = false;
};

template <typename OBJECT_TYPE>
struct IsVectorType<OBJECT_TYPE[]>
{
	static const bool Value = true;
};
//@}

/**
 * Are two types equal?
 *
 * @tparam OBJECT_A First type to compare.
 * @tparam OBJECT_B Second type to compare.
 */
//@{
template <typename OBJECT_A, typename OBJECT_B>
struct IsTypeEqual
{
	static const bool Value = false;
};

template <typename OBJECT_A>
struct IsTypeEqual<OBJECT_A, OBJECT_A>
{
	static const bool Value = true;
};
//@}

/**
 * Is given type a primitive type?
 *
 * @tparam OBJECT_TYPE Type of the object to check.
 */
template <typename OBJECT_TYPE>
struct IsPrimitiveType
{
	static const bool Value =
		   IsTypeEqual<OBJECT_TYPE, char>
		|| IsTypeEqual<OBJECT_TYPE, short>
		|| IsTypeEqual<OBJECT_TYPE, int>
		|| IsTypeEqual<OBJECT_TYPE, long>
		|| IsTypeEqual<OBJECT_TYPE, long long>
		|| IsTypeEqual<OBJECT_TYPE, unsigned char>
		|| IsTypeEqual<OBJECT_TYPE, unsigned short>
		|| IsTypeEqual<OBJECT_TYPE, unsigned int>
		|| IsTypeEqual<OBJECT_TYPE, unsigned long long>
		|| IsTypeEqual<OBJECT_TYPE, float>
		|| IsTypeEqual<OBJECT_TYPE, double>
		|| IsTypeEqual<OBJECT_TYPE, long double>
		|| IsTypeEqual<OBJECT_TYPE, size_t>
		|| IsTypeEqual<OBJECT_TYPE, wchar_t>
		|| IsTypeEqual<OBJECT_TYPE, char16_t>
		|| IsTypeEqual<OBJECT_TYPE, char32_t>;
};

/* eof */
