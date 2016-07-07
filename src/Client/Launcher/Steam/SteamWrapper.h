/// Copyright (C) 2016 by Rage MP MP Team
#pragma once

#include "Strings.h"

#define VERSION_SAFE_STEAM_API_INTERFACES
#include "SteamAPI/steam_api.h"

namespace launcher {

//! Steam api wrapper.
class SteamWrapper
{
private:
	//! Steam context
	CSteamAPIContext*		m_context;

	//! Apps interface.
	ISteamApps*				m_apps;

	//! Destroy context.
	void DestroyContext		(void);

public:
	//! Constructor.
	SteamWrapper			(void);

	//! Destructor.	
	~SteamWrapper			(void);

	//! Initialize steam wrapper.
	bool Init				(void);

	//! Check if game is installed.
	bool IsGameInstalled	(void);

	//! Get game installation path.
	void GetGameInstallPath (PathString &str);
};

} /* namespace launcher */

/* EOF */
