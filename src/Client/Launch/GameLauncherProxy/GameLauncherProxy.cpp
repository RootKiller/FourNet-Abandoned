// Copyright (C) 2016 by Rage MP Team

#include "GameLauncherProxy.h"

#include "OS/OS.h"

void GameLauncherProxy::Init(void)
{
	OS::ShowMessageBox("GameLauncherProxy::Init", "Launch!");
}

void GameLauncherProxy::Shutdown(void)
{
	OS::ShowMessageBox("GameLauncherProxy::Init", "Shutdown!");
}

/* eof */
