// Copyright (C) 2016 by DVO Games

#pragma once

/**
 * Function callback with no parameters.
 *
 * @pre @a CALLBACK must have zero parameters.
 * @tparam CALLBACK The base callback this function will represent.
 */
template <typename CALLBACK>
class CallbackFunction0 : public CALLBACK
{
	static_assert(CALLBACK::PARAM_COUNT == 0, "Incorrect base callback's parameters count.");
public:
	typedef typename CALLBACK::ReturnType (*FuncPtrType)(void);
private:
	/** Function pointer. */
	FuncPtrType		m_function;
public:
	/**
	 * Constructor.
	 *
	 * @param[in] function The pointer to the function to be called by this callback.
	 */
	CallbackFunction0(FuncPtrType function)
		: m_function(function)
	{
	}

	/**
	 * Execute the function.
	 *
	 * @note Please use operator() instead of this function to call the callback.
	 * @see CALLBACK::operator()
	 */
	typename CALLBACK::ReturnType Execute(void) final
	{
		return (*m_function)();
	}
};

/**
 * Function callback with one parameter.
 *
 * @pre @a CALLBACK must have one parameter.
 * @tparam CALLBACK The base callback this function will represent.
 */
template <typename CALLBACK>
class CallbackFunction1 : public CALLBACK
{
	static_assert(CALLBACK::PARAM_COUNT == 1, "Incorrect base callback's parameters count.");
public:
	typedef typename CALLBACK::ReturnType (*FuncPtrType)(typename CALLBACK::Param1Type param1);
private:
	/** Function pointer. */
	FuncPtrType		m_function;
public:
	/**
	 * Constructor.
	 *
	 * @param[in] function The pointer to the function to be called by this callback.
	 */
	CallbackFunction1(FuncPtrType function)
		: m_function(function)
	{
	}

	/**
	 * Execute the function.
	 *
	 * @note Please use operator() instead of this function to call the callback.
	 * @see CALLBACK::operator()
	 *
	 * @param[in] param1 The first parameter to pass to the function.
	 */
	typename CALLBACK::ReturnType Execute(typename CALLBACK::Param1Type param1) final
	{
		return (*m_function)(param1);
	}
};

/**
 * Function callback with two parameters.
 *
 * @pre @a CALLBACK must have two parameters.
 * @tparam CALLBACK The base callback this function will represent.
 */
template <typename CALLBACK>
class CallbackFunction2 : public CALLBACK
{
	static_assert(CALLBACK::PARAM_COUNT == 2, "Incorrect base callback's parameters count.");
public:
	typedef typename CALLBACK::ReturnType (*FuncPtrType)(typename CALLBACK::Param1Type param1, typename CALLBACK::Param2Type param2);
private:
	/** Function pointer. */
	FuncPtrType		m_function;
public:
	/**
	 * Constructor.
	 *
	 * @param[in] function The pointer to the function to be called by this callback.
	 */
	CallbackFunction2(FuncPtrType function)
		: m_function(function)
	{
	}

	/**
	 * Execute the function.
	 *
	 * @note Please use operator() instead of this function to call the callback.
	 * @see CALLBACK::operator()
	 *
	 * @param[in] param1 The first parameter to pass to the function.
	 * @param[in] param2 The second parameter to pass to the function.
	 */
	typename CALLBACK::ReturnType Execute(typename CALLBACK::Param1Type param1, typename CALLBACK::Param2Type param2) final
	{
		return (*m_function)(param1, param2);
	}
};

/**
 * Function callback with three parameters.
 *
 * @pre @a CALLBACK must have three parameters.
 * @tparam CALLBACK The base callback this function will represent.
 */
template <typename CALLBACK>
class CallbackFunction3 : public CALLBACK
{
	static_assert(CALLBACK::PARAM_COUNT == 3, "Incorrect base callback's parameters count.");
public:
	typedef typename CALLBACK::ReturnType (*FuncPtrType)(typename CALLBACK::Param1Type param1, typename CALLBACK::Param2Type param2, typename CALLBACK::Param3Type param3);
private:
	/** Function pointer. */
	FuncPtrType		m_function;
public:
	/**
	 * Constructor.
	 *
	 * @param[in] function The pointer to the function to be called by this callback.
	 */
	CallbackFunction3(FuncPtrType function)
		: m_function(function)
	{
	}

	/**
	 * Execute the function.
	 *
	 * @note Please use operator() instead of this function to call the callback.
	 * @see CALLBACK::operator()
	 *
	 * @param[in] param1 The first parameter to pass to the function.
	 * @param[in] param2 The second parameter to pass to the function.
	 * @param[in] param3 The third parameter to pass to the function.
	 */
	typename CALLBACK::ReturnType Execute(typename CALLBACK::Param1Type param1, typename CALLBACK::Param2Type param2, typename CALLBACK::Param3Type param3) final
	{
		return (*m_function)(param1, param2, param3);
	}
};

/**
 * Function callback with four parameters.
 *
 * @pre @a CALLBACK must have four parameters.
 * @tparam CALLBACK The base callback this function will represent.
 */
template <typename CALLBACK>
class CallbackFunction4 : public CALLBACK
{
	static_assert(CALLBACK::PARAM_COUNT == 4, "Incorrect base callback's parameters count.");
public:
	typedef typename CALLBACK::ReturnType (*FuncPtrType)(typename CALLBACK::Param1Type param1, typename CALLBACK::Param2Type param2, typename CALLBACK::Param3Type param3, typename CALLBACK::Param4Type param4);
private:
	/** Function pointer. */
	FuncPtrType m_function;
public:
	/**
	 * Constructor.
	 *
	 * @param[in] function The pointer to the function to be called by this callback.
	 */
	CallbackFunction4(FuncPtrType function)
		: m_function(function)
	{
	}

	/**
	 * Execute the function.
	 *
	 * @note Please use operator() instead of this function to call the callback.
	 * @see CALLBACK::operator()
	 *
	 * @param[in] param1 The first parameter to pass to the function.
	 * @param[in] param2 The second parameter to pass to the function.
	 * @param[in] param3 The third parameter to pass to the function.
	 * @param[in] param4 The forth parameter to pass to the function.
	 */
	typename CALLBACK::ReturnType Execute(typename CALLBACK::Param1Type param1, typename CALLBACK::Param2Type param2, typename CALLBACK::Param3Type param3, typename CALLBACK::Param4Type param4) final
	{
		return (*m_function)(param1, param2, param3, param4);
	}
};

/**
 * Function callback with five parameters.
 *
 * @pre @a CALLBACK must have five parameters.
 * @tparam CALLBACK The base callback this function will represent.
 */
template <typename CALLBACK>
class CallbackFunction5 : public CALLBACK
{
	static_assert(CALLBACK::PARAM_COUNT == 5, "Incorrect base callback's parameters count.");
public:
	typedef typename CALLBACK::ReturnType (*FuncPtrType)(typename CALLBACK::Param1Type param1, typename CALLBACK::Param2Type param2, typename CALLBACK::Param3Type param3, typename CALLBACK::Param4Type param4, typename CALLBACK::Param5Type param5);
private:
	/** Function pointer. */
	FuncPtrType		m_function;
public:
	/**
	 * Constructor.
	 *
	 * @param[in] function The pointer to the function to be called by this callback.
	 */
	CallbackFunction5(FuncPtrType function)
		: m_function(function)
	{
	}

	/**
	 * Execute the function.
	 *
	 * @note Please use operator() instead of this function to call the callback.
	 * @see CALLBACK::operator()
	 *
	 * @param[in] param1 The first parameter to pass to the function.
	 * @param[in] param2 The second parameter to pass to the function.
	 * @param[in] param3 The third parameter to pass to the function.
	 * @param[in] param4 The forth parameter to pass to the function.
	 * @param[in] param5 The fifth parameter to pass to the function.
	 */
	typename CALLBACK::ReturnType Execute(typename CALLBACK::Param1Type param1, typename CALLBACK::Param2Type param2, typename CALLBACK::Param3Type param3, typename CALLBACK::Param4Type param4, typename CALLBACK::Param5Type param5) final
	{
		return (*m_function)(param1, param2, param3, param4, param5);
	}
};

/* eof */
