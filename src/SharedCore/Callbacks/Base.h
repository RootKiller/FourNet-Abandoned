// Copyright (C) 2016 by DVO Games

#pragma once

/**
 * Base callback without parameters.
 *
 * @tparam RETURN_TYPE	The type of the value returned by the callback.
 */
template <typename RETURN_TYPE>
class CallbackBase0
{
public:
	/** Alias to the return type used by classes that implement actual callbacks. */
	typedef RETURN_TYPE		ReturnType;

	/** Count of the params this callback can take. */
	static const size_t		PARAM_COUNT = 0;

	/** Executes the callback */
	virtual typename RETURN_TYPE		Execute(void) = 0;

	/** Executes the callback */
	RETURN_TYPE				operator()(void)
	{
		return Execute();
	}
};

/**
 * Base callback with one parameter.
 *
 * @tparam RETURN_TYPE	The type of the value returned by the callback.
 * @tparam PARAM_1_TYPE	The type of the first parameter callback can take.
 */
template <typename RETURN_TYPE, typename PARAM_1_TYPE>
class CallbackBase1
{
public:
	/** Alias to the return type used by classes that implement actual callbacks. */
	typedef RETURN_TYPE		ReturnType;

	/** Count of the params this callback can take. */
	static const size_t		PARAM_COUNT = 1;

	/** Alias to the first parameter type used by classes that implement actual callbacks. */
	typedef PARAM_1_TYPE	Param1Type;

	/** Executes the callback */
	virtual RETURN_TYPE		Execute(PARAM_1_TYPE param1) = 0;

	/** Executes the callback */
	RETURN_TYPE				operator()(PARAM_1_TYPE param1)
	{
		return Execute(param1);
	}
};

/**
 * Base callback with two parameters.
 *
 * @tparam RETURN_TYPE	The type of the value returned by the callback.
 * @tparam PARAM_1_TYPE	The type of the first parameter callback can take.
 * @tparam PARAM_2_TYPE	The type of the second parameter callback can take.
 */
template <typename RETURN_TYPE, typename PARAM_1_TYPE, typename PARAM_2_TYPE>
class CallbackBase2
{
public:
	/** Alias to the return type used by classes that implement actual callbacks. */
	typedef RETURN_TYPE		ReturnType;

	/** Count of the params this callback can take. */
	static const size_t		PARAM_COUNT = 2;

	/** Aliases to the parameters types used by classes that implement actual callbacks. */
	//@{
	typedef PARAM_1_TYPE	Param1Type;
	typedef PARAM_2_TYPE	Param2Type;
	//@}

	/** Executes the callback */
	virtual RETURN_TYPE		Execute(PARAM_1_TYPE param1, PARAM_2_TYPE param2) = 0;

	/** Executes the callback */
	RETURN_TYPE				operator()(PARAM_1_TYPE param1, PARAM_2_TYPE param2)
	{
		return Execute(param1, param2);
	}
};

/**
 * Base callback with three parameters.
 *
 * @tparam RETURN_TYPE	The type of the value returned by the callback.
 * @tparam PARAM_1_TYPE	The type of the first parameter callback can take.
 * @tparam PARAM_2_TYPE	The type of the second parameter callback can take.
 * @tparam PARAM_3_TYPE	The type of the third parameter callback can take.
 */
template <typename RETURN_TYPE, typename PARAM_1_TYPE, typename PARAM_2_TYPE, typename PARAM_3_TYPE>
class CallbackBase3
{
public:
	/** Alias to the return type used by classes that implement actual callbacks. */
	typedef RETURN_TYPE		ReturnType;

	/** Count of the params this callback can take. */
	static const size_t		PARAM_COUNT = 3;

	/** Aliases to the parameters types used by classes that implement actual callbacks. */
	//@{
	typedef PARAM_1_TYPE	Param1Type;
	typedef PARAM_2_TYPE	Param2Type;
	typedef PARAM_3_TYPE	Param3Type;
	//@}

	/** Executes the callback */
	virtual RETURN_TYPE		Execute(PARAM_1_TYPE param1, PARAM_2_TYPE param2, PARAM_3_TYPE param3) = 0;

	/** Executes the callback */
	RETURN_TYPE				operator()(PARAM_1_TYPE param1, PARAM_2_TYPE param2, PARAM_3_TYPE param3)
	{
		return Execute(param1, param2, param3);
	}
};

/**
 * Base callback with four parameters.
 *
 * @tparam RETURN_TYPE	The type of the value returned by the callback.
 * @tparam PARAM_1_TYPE	The type of the first parameter callback can take.
 * @tparam PARAM_2_TYPE	The type of the second parameter callback can take.
 * @tparam PARAM_3_TYPE	The type of the third parameter callback can take.
 * @tparam PARAM_4_TYPE	The type of the forth parameter callback can take.
 */
template <typename RETURN_TYPE, typename PARAM_1_TYPE, typename PARAM_2_TYPE, typename PARAM_3_TYPE, typename PARAM_4_TYPE>
class CallbackBase4
{
public:
	/** Alias to the return type used by classes that implement actual callbacks. */
	typedef RETURN_TYPE		ReturnType;

	/** Count of the params this callback can take. */
	static const size_t		PARAM_COUNT = 4;

	/** Aliases to the parameters types used by classes that implement actual callbacks. */
	//@{
	typedef PARAM_1_TYPE	Param1Type;
	typedef PARAM_2_TYPE	Param2Type;
	typedef PARAM_3_TYPE	Param3Type;
	typedef PARAM_4_TYPE	Param4Type;
	//@}

	/** Executes the callback */
	virtual RETURN_TYPE		Execute(PARAM_1_TYPE param1, PARAM_2_TYPE param2, PARAM_3_TYPE param3, PARAM_4_TYPE param4) = 0;

	/** Executes the callback */
	RETURN_TYPE				operator()(PARAM_1_TYPE param1, PARAM_2_TYPE param2, PARAM_3_TYPE param3, PARAM_4_TYPE param4)
	{
		return Execute(param1, param2, param3, param4);
	}
};

/**
 * Base callback with five parameters.
 *
 * @tparam RETURN_TYPE	The type of the value returned by the callback.
 * @tparam PARAM_1_TYPE	The type of the first parameter callback can take.
 * @tparam PARAM_2_TYPE	The type of the second parameter callback can take.
 * @tparam PARAM_3_TYPE	The type of the third parameter callback can take.
 * @tparam PARAM_4_TYPE	The type of the forth parameter callback can take.
 * @tparam PARAM_5_TYPE	The type of the fifth parameter callback can take.
 */
template <typename RETURN_TYPE, typename PARAM_1_TYPE, typename PARAM_2_TYPE, typename PARAM_3_TYPE, typename PARAM_4_TYPE, typename PARAM_5_TYPE>
class CallbackBase5
{
public:
	/** Alias to the return type used by classes that implement actual callbacks. */
	typedef RETURN_TYPE		ReturnType;

	/** Count of the params this callback can take. */
	static const size_t		PARAM_COUNT = 5;

	/** Aliases to the parameters types used by classes that implement actual callbacks. */
	//@{
	typedef PARAM_1_TYPE	Param1Type;
	typedef PARAM_2_TYPE	Param2Type;
	typedef PARAM_3_TYPE	Param3Type;
	typedef PARAM_4_TYPE	Param4Type;
	typedef PARAM_5_TYPE	Param5Type;
	//@}

	/** Executes the callback */
	virtual RETURN_TYPE		Execute(PARAM_1_TYPE param1, PARAM_2_TYPE param2, PARAM_3_TYPE param3, PARAM_4_TYPE param4, PARAM_5_TYPE param5) = 0;

	/** Executes the callback */
	RETURN_TYPE				operator()(PARAM_1_TYPE param1, PARAM_2_TYPE param2, PARAM_3_TYPE param3, PARAM_4_TYPE param4, PARAM_5_TYPE param5)
	{
		return Execute(param1, param2, param3, param4, param5);
	}
};

/* eof */
