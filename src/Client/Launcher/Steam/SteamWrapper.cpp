/// Copyright (C) 2016 by Rage MP Team

#include "SteamWrapper.h"
#include "Debug/Debug.h"

#include <Windows.h>

namespace launcher {

//! Game appid.
extern unsigned GAME_APPID;

//! Constructor.
SteamWrapper::SteamWrapper(void)
	: m_context(nullptr)
	, m_apps(nullptr)
{
}

//! Destructor.
SteamWrapper::~SteamWrapper(void)
{
	DestroyContext();
}

/**
 * Destroy context.
 */
void SteamWrapper::DestroyContext(void)
{
	if (m_context) {
		delete m_context;
		m_context = nullptr;
	}
}

/**
 * Initialize steam wrapper.
 *
 * @return @c false in case of fail @c true in case everything seems to be OK.
 */
bool SteamWrapper::Init(void)
{
	ASSERT(!m_context);

	if(!SteamAPI_IsSteamRunning()) {
		MessageBoxA(NULL, "To run GTA EFLC Multiplayer your Steam client must be running.", "Fatal error", MB_ICONERROR);
		return false;
	}

	// If this assert occurs it's possible that you have not placed
	// steam_appid.txt file inside Launcher folder.
	ASSERT(SteamAPI_InitSafe());

	m_context = new CSteamAPIContext();
	m_context->Init();

	// Collect pointers we will use later.
	m_apps = m_context->SteamApps();
	if(!m_apps) {
		DestroyContext();
		return false;
	}

	return true;
}

/**
 * Check if game is installed.
 *
 * @return @c true if game is installed @c false if not.
 */
bool SteamWrapper::IsGameInstalled(void)
{
	ASSERT(m_context);
	return m_apps->BIsAppInstalled(static_cast<AppId_t>(GAME_APPID));
}

/**
 * Get game installation path.
 *
 * @param[out] str The string to store install path.
 */
void SteamWrapper::GetGameInstallPath(PathString &str)
{
	ASSERT(m_context);
	char installFolder[MAX_PATH] = { 0 };
	m_apps->GetAppInstallDir(static_cast<AppId_t>(GAME_APPID), installFolder, MAX_PATH);
	str = installFolder;
}

} /* namespace launcher */

/* EOF */
