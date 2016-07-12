FourNet - Multiplayer mod for Grand Theft Auto IV
==========================

# Setup

1. Set environment variable `FOURNET_PROJECT_ROOT` to your project root path.

# Projects

* **Client** - Folder containing all client related projects
	* **ClientShared** - shared client library containing code shared between client launcher, client core, launch libs and game libs
	* **Core** - the main multiplayer client core - compiled to FourNet.dll containing all Game and Launch libs inside.
	* **Launcher** - the client launcher, launching LaunchGTAIV.exe launcher and attaches FourNet.dll into it.
	* **Game** - Folder containg all game libraries
		* **MultiplayerGame** - library containing multiplayer mod functionallity.
	* **Launch** - Folder containing all launch libraries
		* **GameLauncherProxy** - selected when FourNet.dll is attached to LaunchGTAIV.exe process - it is here to inject Game libraries into game process (GTAIV.exe)
* **SharedCore** - shared core library containg low-level code and the core utilities.

# Legal

Grand Theft Auto IV is registered trademark of Take-Two Interactive Software, Inc. 