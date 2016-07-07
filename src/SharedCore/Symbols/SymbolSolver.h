// Copyright (C) 2016 by DVO Games

#pragma once

/**
 * Dynamic-library symbol solver.
 *
 * Remember! The returned addresses are valid as long as SymbolSolver
 * is alive. If the object is destroyed all the addresses become invalid.
 */
class SymbolSolver
{
private:
	void	*GetProcAddress		(const char *const procName);

	/// Dynamic library handle.
	void	*m_handle;
public:

explicit	SymbolSolver		(const char *const dynLibName);

			~SymbolSolver		();

inline bool IsValid				(void) const { return m_handle != nullptr; }

	template <typename PROCEDURE_TYPE>
	inline PROCEDURE_TYPE GetProcAddress(const char *const procName)
	{
		return static_cast<PROCEDURE_TYPE>(GetProcAddress(procName));
	}
};

/* eof */
