
#include "ProfilingSection.h"

#include "Profiler.h"

#include <new>

Profiler::Profiler()
	: m_currentFrameSections()
	, m_lastFrameSections()

	, m_currentSection(nullptr)
{
}

Profiler::~Profiler()
{
}

const size_t MAX_SECTION_COUNT = 50000;
char sectionsMemory[sizeof(ProfilingSection) * MAX_SECTION_COUNT];
size_t sectionIndex = 0;
bool flushPoolSwitch = false;

static char *GetSectionMemory(void)
{
	if (sectionIndex == MAX_SECTION_COUNT) {
		ASSERT_MSG(false, "out of section memory pool");
		return nullptr;
	}

	char *const memory = &sectionsMemory[sectionIndex * sizeof(ProfilingSection)];
	memset(memory, 0, sizeof(ProfilingSection));
	sectionIndex += 1;
	return memory;
}

ProfilingSection *Profiler::BeginSection(const char *const sectionName, const char *const sectionModule)
{
	char *const sectionMemory = GetSectionMemory();
	ASSERT(sectionMemory);
	if (!sectionMemory) {
		return nullptr;
	}

	ProfilingSection *const section = new (sectionMemory) ProfilingSection (sectionName, sectionModule);
	if (! m_currentSection) {
		ProfilingSection* old = m_currentFrameSections;
		m_currentFrameSections = section;
		m_currentFrameSections->m_next = old;
	}
	else {
		section->m_parent = m_currentSection;

		ProfilingSection* old = m_currentSection->m_firstChild;
		m_currentSection->m_firstChild = section;
		m_currentSection->m_firstChild->m_next = old;
	}

	m_currentSection = section;
	section->Begin();
	return section;
}

void Profiler::EndSection(ProfilingSection *const section)
{
	section->End();

	if (m_currentSection == section) {
		m_currentSection = section->GetParent();
	}
}

void Profiler::BeginFrame(void)
{
	ASSERT(m_currentFrameSections == nullptr);
}

void Profiler::EndFrame(void)
{
	PROFILE("Profiler:EndFrame", "Engine");
	m_lastFrameSections = m_currentFrameSections;
	m_currentFrameSections = nullptr;

	if (flushPoolSwitch) {
		sectionIndex = 0;
		flushPoolSwitch = false;
	}
	else {
		flushPoolSwitch = true;
	}
}

const ProfilingSection* Profiler::GetSections(void) const
{
	return m_lastFrameSections;
}

/* eof */
