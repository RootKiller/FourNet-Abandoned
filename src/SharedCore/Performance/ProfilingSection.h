// Copyright (C) 2016 by DVO Games

#pragma once

#include <list>

#include "AutoPtr.h"
#include "Timer.h"

const size_t PROFILER_NAME_MAX_LENGTH = 64;

class ProfilingSection
{
private:
	/** The name of the profiled section/operation */
	char				m_sectionName[PROFILER_NAME_MAX_LENGTH + 1];

	/** The name of the module */
	char				m_moduleName[PROFILER_NAME_MAX_LENGTH + 1];

	/** The parent profiling section. */
	ProfilingSection	*m_parent;

	/** Child sections list. */
	ProfilingSection	*m_firstChild;

	/** The next profiling section */
	ProfilingSection	*m_next;

	/** This begin recording start */
	time_value			m_recordStart;

	/** The time when recorded this section first time. */
	time_value			m_frameRecordStart;

	/** The time when we stopped recording this section last time. */
	time_value			m_frameRecordEnd;

	/** Total section time in this frame */
	float				m_time;
public:
					ProfilingSection		(const char *const sectionName, const char *const moduleName);
					~ProfilingSection		();

	const char *	GetName					(void) const;
	const char *	GetModule				(void) const;

	bool			Compare					(const char *const sectionName, const char *const moduleName) const;

	void			Begin					(void);
	void			End						(void);

	float			GetDuration				(void) const;

	time_value		GetFrameRecordStart		(void) const;
	time_value		GetFrameRecordEnd		(void) const;

	ProfilingSection *GetParent				(void) const;

	const ProfilingSection *GetChildren		(void) const;
	const ProfilingSection *GetNext			(void) const;

	friend class Profiler;
};

/* eof */
