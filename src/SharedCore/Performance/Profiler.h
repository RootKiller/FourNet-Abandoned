// Copyright (C) 2016 by DVO Games

#pragma once

#define PROFILER_ENABLED

#include "Singleton.h"

#include "Timer.h"

#include "ProfilingSection.h"

#include "Defines.h"

/**
 * Profiler class.
 */
class Profiler : public ESingleton<Profiler>
{
private:
	ProfilingSection	*m_currentFrameSections;
	ProfilingSection	*m_lastFrameSections;

	ProfilingSection	*m_currentSection;
public:

						Profiler		();
						~Profiler		();

	/** Begin profiling section. */
	ProfilingSection *	BeginSection	(const char *const sectionName, const char *const sectionModule);

	/** End profiling section. */
	void				EndSection		(ProfilingSection *const section);

	/** Begin engine frame. */
	void				BeginFrame			(void);

	/** End engine frame. */
	void				EndFrame			(void);

	/** Get list containing last frame profiler sections */
const ProfilingSection* GetSections		(void) const;
};

/**
 * Helper scope-lifetime profiler object.
 */
class ScopeProfiler
{
private:
	/** The section to be used for profiling */
	ProfilingSection *m_section;
public:
	/** Constructor. */
	ScopeProfiler(const char *const sectionName, const char *const sectionModule)
	{
		m_section = Profiler::Get()->BeginSection(sectionName, sectionModule);
	}

	/** Destructor */
	~ScopeProfiler()
	{
		Profiler::Get()->EndSection(m_section);
		m_section = nullptr;
	}
};

#if defined(DEBUG_BUILD) || defined(PROFILER_ENABLED)
#	define PROFILE(name, module)			ScopeProfiler CONCAT(profiler_, __LINE__)(name, module)
#else
#	define PROFILE(name, module)			do { } while (false)
#endif /* defined(DEBUG_BUILD) || defined(PROFILER_ENABLED) */

/* eof */
