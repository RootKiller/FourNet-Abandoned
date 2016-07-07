// Copyright (C) 2016 DVO Games

#pragma once

#include "Debug/Debug.h"

/**
 * Explicit singleton class.
 *
 * User needs to create instance of class handled by this method.
 */
template <typename CLASS_TYPE>
class ESingleton
{
private:
	// Object instance.
	static CLASS_TYPE*		ms_instance;
public:
			ESingleton		(void)
	{
		ASSERT(ms_instance == nullptr);
		ms_instance = static_cast<CLASS_TYPE*>(this);
	}

			~ESingleton		(void)
	{
		ASSERT(ms_instance != nullptr);
		ms_instance = nullptr;
	}

	static bool	HasInstance	(void)
	{
		return ms_instance != nullptr;
	}

	static CLASS_TYPE*	Get	(void)
	{
		ASSERT(ms_instance);
		return ms_instance;
	}
};

template <typename CLASS_NAME>
CLASS_NAME* ESingleton<CLASS_NAME>::ms_instance = nullptr;

/* eof */
