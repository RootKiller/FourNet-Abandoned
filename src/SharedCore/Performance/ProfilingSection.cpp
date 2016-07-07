// Copyright (C) 2016 by DVO Games

#include "ProfilingSection.h"


ProfilingSection::ProfilingSection(const char *const sectionName, const char *const moduleName)
	: m_sectionName()
	, m_moduleName()

	, m_parent(nullptr)
	, m_firstChild(nullptr)
	, m_next(nullptr)

	, m_frameRecordStart(Nil())
	, m_frameRecordEnd(Nil())

	, m_recordStart(Nil())
	, m_time(0.0f)
{
	ASSERT(sectionName && strlen(sectionName) <= PROFILER_NAME_MAX_LENGTH);
	ASSERT(moduleName && strlen(moduleName) <= PROFILER_NAME_MAX_LENGTH);

	strncpy(m_sectionName, sectionName, PROFILER_NAME_MAX_LENGTH);
	strncpy(m_moduleName,  moduleName,  PROFILER_NAME_MAX_LENGTH);
}

ProfilingSection::~ProfilingSection()
{
}

const char *ProfilingSection::GetName(void) const
{
	return m_sectionName;
}

const char *ProfilingSection::GetModule(void) const
{
	return m_moduleName;
}

bool ProfilingSection::Compare(const char *const sectionName, const char *const moduleName) const
{
	if (strncmp(m_sectionName, sectionName, PROFILER_NAME_MAX_LENGTH) != 0) {
		return false;
	}

	if (strncmp(m_moduleName, moduleName, PROFILER_NAME_MAX_LENGTH) != 0) {
		return false;
	}
	return true;
}

void ProfilingSection::Begin(void)
{
	ASSERT(IsNil(m_recordStart));
	m_frameRecordStart = Timer::GetNow();
	m_recordStart = Timer::GetNow();
}

void ProfilingSection::End(void)
{
	ASSERT(NotNil(m_recordStart));
	m_time = Timer::GetDiff(m_recordStart);
	m_frameRecordEnd = Timer::GetNow();
	m_recordStart = Nil();
}

float ProfilingSection::GetDuration(void) const
{
	return m_time;
}

time_value ProfilingSection::GetFrameRecordStart(void) const
{
	return m_frameRecordStart;
}

time_value ProfilingSection::GetFrameRecordEnd(void) const
{
	return m_frameRecordEnd;
}

ProfilingSection *ProfilingSection::GetParent(void) const
{
	return m_parent;
}

const ProfilingSection* ProfilingSection::GetChildren(void) const
{
	return m_firstChild;
}

const ProfilingSection* ProfilingSection::GetNext(void) const
{
	return m_next;
}

/* eof */
