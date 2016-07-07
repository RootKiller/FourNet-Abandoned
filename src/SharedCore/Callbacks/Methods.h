// Copyright (C) 2016 by DVO Games

#pragma once

/**
 * Class/struct method callback with no parameters.
 *
 * @pre @a CALLBACK must have zero parameters.
 * @tparam CLIENT The client that owns the method represent by this callback.
 * @tparam CALLBACK The base callback this method will represent.
 */
template <typename CLIENT, typename CALLBACK>
class CallbackMethod0 : public CALLBACK
{
	static_assert(CALLBACK::PARAM_COUNT == 0, "Incorrect base callback's parameters count.");
public:
	typedef typename CALLBACK::ReturnType (CLIENT::*FuncPtrType)();
private:
	/** The client owning the method. */
	CLIENT			*m_client;

	/** The method to be called. */
	FuncPtrType		m_method;
public:
	/**
	 * Constructor.
	 *
	 * @param[in] client	The client owning the method.
	 * @param[in] method	The method to be called.
	 */
	CallbackMethod0(CLIENT *const client, FuncPtrType method)
		: m_client(client)
		, m_method(method)
	{
	}

	/**
	 * Execute the method.
	 *
	 * @note Please use operator() instead of this function to call the callback.
	 * @see CALLBACK::operator()
	 */
	typename CALLBACK::ReturnType Execute(void) final
	{
		(m_client->*m_method)();
	}
};

/**
 * Class/struct method callback with one parameter.
 *
 * @pre @a CALLBACK must have one parameter.
 * @tparam CLIENT The client that owns the method represent by this callback.
 * @tparam CALLBACK The base callback this method will represent.
 */
template <typename CLIENT, typename CALLBACK>
class CallbackMethod1 : public CALLBACK
{
	static_assert(CALLBACK::PARAM_COUNT == 1, "Incorrect base callback's parameters count.");
public:
	typedef typename CALLBACK::ReturnType (CLIENT::*FuncPtrType)(typename CALLBACK::Param1Type param1);
private:
	/** The client owning the method. */
	CLIENT			*m_client;

	FuncPtrType		m_method;
public:
	/**
	 * Constructor.
	 *
	 * @param[in] client	The client owning the method.
	 * @param[in] method	The method to be called.
	 */
	CallbackMethod1(CLIENT *const client, FuncPtrType method)
		: m_client(client)
		, m_method(method)
	{
	}

	/**
	 * Execute the method.
	 *
	 * @note Please use operator() instead of this function to call the callback.
	 * @see CALLBACK::operator()
	 *
	 * @param[in] param1 The first parameter to pass to the function.
	 */
	typename CALLBACK::ReturnType Execute(typename CALLBACK::Param1Type param1) final
	{
		return (m_client->*m_method)(param1);
	}
};

/**
 * Class/struct method callback with two parameters.
 *
 * @pre @a CALLBACK must have two parameters.
 * @tparam CLIENT The client that owns the method represent by this callback.
 * @tparam CALLBACK The base callback this method will represent.
 */
template <typename CLIENT, typename CALLBACK>
class CallbackMethod2 : public CALLBACK
{
	static_assert(CALLBACK::PARAM_COUNT == 2, "Incorrect base callback's parameters count.");
public:
	typedef typename CALLBACK::ReturnType (CLIENT::*FuncPtrType)(typename CALLBACK::Param1Type param1, typename CALLBACK::Param2Type param2);
private:
	/** The client owning the method. */
	CLIENT			*m_client;

	FuncPtrType		m_method;
public:
	/**
	 * Constructor.
	 *
	 * @param[in] client	The client owning the method.
	 * @param[in] method	The method to be called.
	 */
	CallbackMethod2(CLIENT *const client, FuncPtrType method)
		: m_client(client)
		, m_method(method)
	{
	}

	/**
	 * Execute the method.
	 *
	 * @note Please use operator() instead of this function to call the callback.
	 * @see CALLBACK::operator()
	 *
	 * @param[in] param1 The first parameter to pass to the function.
	 * @param[in] param2 The second parameter to pass to the function.
	 */
	typename CALLBACK::ReturnType Execute(typename CALLBACK::Param1Type param1, typename CALLBACK::Param2Type param2) final
	{
		return (m_client->*m_method)(param1, param2);
	}
};

/**
 * Class/struct method callback with three parameters.
 *
 * @pre @a CALLBACK must have three parameters.
 * @tparam CLIENT The client that owns the method represent by this callback.
 * @tparam CALLBACK The base callback this method will represent.
 */
template <typename CLIENT, typename CALLBACK>
class CallbackMethod3 : public CALLBACK
{
	static_assert(CALLBACK::PARAM_COUNT == 3, "Incorrect base callback's parameters count.");
public:
	typedef typename CALLBACK::ReturnType (CLIENT::*FuncPtrType)(typename CALLBACK::Param1Type param1, typename CALLBACK::Param2Type param2, typename CALLBACK::Param3Type param3);
private:
	/** The client owning the method. */
	CLIENT			*m_client;

	FuncPtrType		m_method;
public:
	/**
	 * Constructor.
	 *
	 * @param[in] client	The client owning the method.
	 * @param[in] method	The method to be called.
	 */
	CallbackMethod3(CLIENT *const client, FuncPtrType method)
		: m_client(client)
		, m_method(method)
	{
	}

	/**
	 * Execute the method.
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
		return (m_client->*m_method)(param1, param2, param3);
	}
};

/**
 * Class/struct method callback with four parameters.
 *
 * @pre @a CALLBACK must have four parameters.
 * @tparam CLIENT The client that owns the method represent by this callback.
 * @tparam CALLBACK The base callback this method will represent.
 */
template <typename CLIENT, typename CALLBACK>
class CallbackMethod4 : public CALLBACK
{
	static_assert(CALLBACK::PARAM_COUNT == 4, "Incorrect base callback's parameters count.");
public:
	typedef typename CALLBACK::ReturnType (CLIENT::*FuncPtrType)(typename CALLBACK::Param1Type param1, typename CALLBACK::Param2Type param2, typename CALLBACK::Param3Type param3, typename CALLBACK::Param4Type param4);
private:
	/** The client owning the method. */
	CLIENT			*m_client;

	FuncPtrType		m_method;
public:
	/**
	 * Constructor.
	 *
	 * @param[in] client	The client owning the method.
	 * @param[in] method	The method to be called.
	 */
	CallbackMethod4(CLIENT *const client, FuncPtrType method)
		: m_client(client)
		, m_method(method)
	{
	}

	/**
	 * Execute the method.
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
		return (m_client->*m_method)(param1, param2, param3, param4);
	}
};

/**
 * Class/struct method callback with five parameters.
 *
 * @pre @a CALLBACK must have five parameters.
 * @tparam CLIENT The client that owns the method represent by this callback.
 * @tparam CALLBACK The base callback this method will represent.
 */
template <typename CLIENT, typename CALLBACK>
class CallbackMethod5 : public CALLBACK
{
	static_assert(CALLBACK::PARAM_COUNT == 5, "Incorrect base callback's parameters count.");
public:
	typedef typename CALLBACK::ReturnType (CLIENT::*FuncPtrType)(typename CALLBACK::Param1Type param1, typename CALLBACK::Param2Type param2, typename CALLBACK::Param3Type param3, typename CALLBACK::Param4Type param4, typename CALLBACK::Param5Type param5);
private:
	/** The client owning the method. */
	CLIENT			*m_client;

	FuncPtrType		m_method;
public:
	/**
	 * Constructor.
	 *
	 * @param[in] client	The client owning the method.
	 * @param[in] method	The method to be called.
	 */
	CallbackMethod5	(CLIENT *const client, FuncPtrType method)
		: m_client	(client)
		, m_method	(method)
	{
	}

	/**
	 * Execute the method.
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
		return (m_client->*m_method)(param1, param2, param3, param4, param5);
	}
};

/* eof */
