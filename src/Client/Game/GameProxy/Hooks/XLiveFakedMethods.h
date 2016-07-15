// Copyright (C) 2016 by Rage MP Team
// The parts of this file is based on XLiveLess project by Listener.

#ifndef INSIDE_XLIVEHOOKS_CPP
#error This file can be only included inside XLiveHooks.cpp file.
#endif

extern "C" {

// #1: XWSAStartup
int __stdcall XWSAStartup (WORD wVersionRequested, LPWSADATA lpWsaData)
{
	lpWsaData->wVersion = 2;
	return 0;
}

// #2: XWSACleanup
void __stdcall XWSACleanup ()
{
}

// #3: XCreateSocket
SOCKET __stdcall XCreateSocket(int af, int type, int protocol)
{
	return INVALID_SOCKET;
}

// #4: XSockeClose
int __stdcall XSockeClose (SOCKET s)
{
	return 0;
}


// #5: XSocketShutdown
int __stdcall XSocketShutdown (SOCKET s, int how)
{
	return 0;
}

// #6: XSocketIOCTLSocket
int __stdcall XSocketIOCTLSocket (SOCKET s, long cmd, long * argp)
{
	return 0;
}

// #7: XSocketSetSockOpt
int __stdcall XSocketSetSockOpt (SOCKET s, DWORD, DWORD, DWORD, DWORD)
{
	return 0;
}

// #9: XSocketGetSockName
int __stdcall XSocketGetSockName (SOCKET s, sockaddr_in * name, int * namelen)
{
	if (namelen && name && *namelen == sizeof (sockaddr_in)) 
		memset (name, 0, sizeof (sockaddr_in));
	return 0;
}

// #11: XSocketBind
SOCKET __stdcall XSocketBind (SOCKET s, sockaddr_in * addr, int * addrlen)
{
	return INVALID_SOCKET;
}

// #12: XSocketConnect
int __stdcall XSocketConnect (SOCKET s, sockaddr_in * addr, int * addrlen)
{
	return 0;
}

// #13: XSocketListen
int __stdcall XSocketListen (SOCKET s, int backlog)
{
	return 0;
}

// #14: XSocketAccept
SOCKET __stdcall XSocketAccept (SOCKET s, sockaddr_in * addr, int * addrlen)
{
	return INVALID_SOCKET;
}

// #15: XSocketSelect
int __stdcall XSocketSelect (int n, fd_set * readfds, fd_set * writefds, fd_set * exceptfds, const struct timeval * timeout)
{
	return 0;
}

// #18: XSocketRecv
int __stdcall XSocketRecv (SOCKET s, char * buf, int len, int flags)
{
	return 0;
}

// #20: XSocketRecvFrom
int __stdcall XSocketRecvFrom (SOCKET s, char * buf, int len, int flags, sockaddr_in * from, int fromlen)
{
	return 0;
}

// #22: XSocketSend
int __stdcall XSocketSend (SOCKET s, char * buf, int len, int flags)
{
	return 0;
}

// #24: XSocketSendTo
int __stdcall XSocketSendTo (SOCKET s, char * buf, int len, int flags, sockaddr_in * to, int tolen)
{
	return 0;
}

// #26: XSocketInet_Addr
int __stdcall XSocketInet_Addr (char *)
{
	return 0;
}

// #27: XWSAGetLastError
int __stdcall XWSAGetLastError ()
{
	return WSAENETDOWN; // 0 ?
}

// #38: XSocketNTOHS
WORD __stdcall XSocketNTOHS (WORD n)
{
	return ((n&0xFF00) >> 8)|((n&0xFF) << 8);
}

// #39: XSocketNTOHL
DWORD __stdcall XSocketNTOHL (DWORD n)
{
	return ((n&0xFF000000) >> 24)|((n & 0x00FF0000) >> 8)|((n&0x0000FF00) << 8)|((n & 0x000000FF) << 24);
}

// #51: XNetStartup
int __stdcall XNetStartup (void *) // (XNetStartupParams*)
{
	return 0;
}

// #52: XNetCleanup
int __stdcall XNetCleanup ()
{
	return 0;
}

// #54: XNetCreateKey
int __stdcall XNetCreateKey (void * pxnkid, void * pxnkey)
{
	return 0;
}

// #55: XNetRegisterKey
int __stdcall XNetRegisterKey (DWORD, DWORD)
{
	return 0;
}

// #56: XNetUnregisterKey
int __stdcall XNetUnregisterKey (DWORD)
{
	return 0;
}

// #57: XNetXnAddrToInAddr
int __stdcall XNetXnAddrToInAddr (DWORD, DWORD, DWORD * p)
{
	*p = 0;
	return 0;
}

// #58: XNetServerToInAddr
DWORD __stdcall XNetServerToInAddr (DWORD, DWORD, DWORD)
{
	return 0;
}

// #60: XNetInAddrToXnAddr
DWORD __stdcall XNetInAddrToXnAddr (DWORD, DWORD, DWORD)
{
	return 0;
} 

// #63: XNetUnregisterInAddr
int __stdcall XNetUnregisterInAddr (DWORD)
{
	return 0;
}

// #65: XNetConnect
int __stdcall XNetConnect (DWORD)
{
	return 0;
}

// #66: XNetGetConnectStatus
int __stdcall XNetGetConnectStatus (DWORD)
{
	return 0;	
}

// #69: XNetQosListen
DWORD __stdcall XNetQosListen (DWORD, DWORD, DWORD, DWORD, DWORD)
{
	return 0; 
}

// #70: XNetQosLookup
DWORD __stdcall XNetQosLookup (DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD)
{
	return 0; 
}

// #71: XNetQosServiceLookup
DWORD __stdcall XNetQosServiceLookup (DWORD, DWORD, DWORD)
{
	return 0;
}

// #72: XNetQosRelease
DWORD __stdcall XNetQosRelease (DWORD)
{
	return 0; 
}

// #73: XNetGetTitleXnAddr
DWORD __stdcall XNetGetTitleXnAddr (DWORD * pAddr)
{
	*pAddr = 0x0100007F;	// 127.0.0.1
	return 4; 
}

// #75: XNetGetEthernetLinkStatus
DWORD __stdcall XNetGetEthernetLinkStatus ()
{
	return 1; 
}

// #84: XNetSetSystemLinkPort
DWORD __stdcall XNetSetSystemLinkPort (DWORD)
{
	return 0; 
}

// #473: XCustomGetLastActionPress
int __stdcall XCustomGetLastActionPress (DWORD, DWORD, DWORD)
{
	return 0;
}

// #651: XNotifyGetNext
int __stdcall XNotifyGetNext (HANDLE hNotification, DWORD dwMsgFilter, DWORD * pdwId, void * pParam)
{
	return 0;   // no notifications
}

// #652: XNotifyPositionUI
DWORD __stdcall XNotifyPositionUI (DWORD dwPosition)
{
	return 0;
}

// #1082: XGetOverlappedExtendedError
DWORD __stdcall XGetOverlappedExtendedError (void *)
{
	return 0;
}

// #1083: XGetOverlappedResult
DWORD __stdcall XGetOverlappedResult (void *, DWORD * pResult, DWORD bWait)
{
	if (pResult)
		*pResult = 0;	// 0 elements enumerated
	return 0;
}

// #5000: XLiveInitialize
int __stdcall XLiveInitialize (DWORD) // XLiveInitialize(struct _XLIVE_INITIALIZE_INFO *)
{
	return 0;
}

// #5001: XLiveInput
int __stdcall XLiveInput (DWORD * p)
{
	p[5] = 0;
	return 1;	// -1 ?
}

// #5002: XLiveRender
int __stdcall XLiveRender ()
{
	return 0;
}

// #5003: XLiveUninitialize
int __stdcall XLiveUninitialize ()
{
	return 0;
}

// #5005: XLiveOnCreateDevice
int __stdcall XLiveOnCreateDevice (DWORD, DWORD)
{
	return 0;
}

// #5007: XLiveOnResetDevice
int __stdcall XLiveOnResetDevice (DWORD)
{
	return 0;
}

// #5008: XHVCreateEngine
int __stdcall XHVCreateEngine (DWORD, DWORD, void ** ppEngine)
{
    if (ppEngine)
        *ppEngine = NULL;
	return -1;	// disable live voice   
}

// #5022: XLiveGetUpdateInformation
int __stdcall XLiveGetUpdateInformation (DWORD)
{
	return -1; // no update
}

// #5024: XLiveUpdateSystem
int __stdcall XLiveUpdateSystem (DWORD)
{
	return -1; // no update
}

// #5030: XLivePreTranslateMessage
int __stdcall XLivePreTranslateMessage (DWORD)
{
	return 0;
}

// #5031 XLiveSetDebugLevel
int __stdcall XLiveSetDebugLevel (DWORD xdlLevel, DWORD * pxdlOldLevel)
{
	return 0;
}

// #5214: XShowPlayerReviewUI
int __stdcall XShowPlayerReviewUI (DWORD, DWORD, DWORD)
{
	return 0;
}

// #5215: XShowGuideUI
int __stdcall XShowGuideUI (DWORD)
{
	return 1;
}

// #5216: XShowKeyboardUI
int __stdcall XShowKeyboardUI (DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD)
{
	return 0;
}

// #5251: XCloseHandle
int __stdcall XCloseHandle (DWORD)
{
	return 0;
}

// #5252: XShowGamerCardUI
int __stdcall XShowGamerCardUI (DWORD, DWORD, DWORD)
{
	return 0;
}

// #5254: XCancelOverlapped
int __stdcall XCancelOverlapped (DWORD)
{
	return 0;
}

// #5256: XEnumerate
int __stdcall XEnumerate (HANDLE hEnum, void * pvBuffer, DWORD cbBuffer, DWORD * pcItemsReturned, void * pOverlapped)
{
// XEnumerate
//    if (pvBuffer && cbBuffer) 
//        memset (pvBuffer, 0, cbBuffer);
	if (pcItemsReturned) {
		*pcItemsReturned = 0;
	}
	return 0;	// some error ? 
}

// #5260: XShowSigninUI
int __stdcall XShowSigninUI (DWORD, DWORD)
{
	return 0;
}

// #5261: XUserGetXUID
int __stdcall XUserGetXUID (DWORD, DWORD * pXuid)
{
	pXuid[0] = pXuid[1] = 0x10001000; 
	return 0; // ???
}


// #5262: XUserGetSigninState
int __stdcall XUserGetSigninState (DWORD dwUserIndex)
{
	return 1; // eXUserSigninState_SignedInLocally
}

// #5263: XUserGetName
int __stdcall XUserGetName (DWORD dwUserId, char * pBuffer, DWORD dwBufLen)
{
	if (dwBufLen < 8)
		return 1;
	memcpy (pBuffer, "Dictator", 9);
	return 0;
}

// #5264: XUserAreUsersFriends
int __stdcall XUserAreUsersFriends(DWORD dwUserIndex, DWORD * pXuids, DWORD dwXuidCount, DWORD * pResult, void * pOverlapped)
{
    return ERROR_NOT_LOGGED_ON;
}

// #5265: XUserCheckPrivilege
int __stdcall XUserCheckPrivilege (DWORD user, DWORD priv, PBOOL b)
{
	*b = false;
	return ERROR_NOT_LOGGED_ON;
}

struct XUSER_SIGNIN_INFO
{
   DWORD	xuidL;
   DWORD	xuidH;
   DWORD    dwInfoFlags;
   DWORD	UserSigninState;
   DWORD    dwGuestNumber;
   DWORD    dwSponsorUserIndex;
   CHAR     szUserName[16];
};

// #5267: XUserGetSigninInfo
int __stdcall XUserGetSigninInfo (DWORD dwUser, DWORD dwFlags, XUSER_SIGNIN_INFO * pInfo)
{
//	pInfo->xuidL = pInfo->xuidH = dwFlags != 1 ? (dwUser+1)*0x10001000 : 0; // some arbitrary id for offline user, INVALID_XUID for online user
	if (dwFlags != 1)
{
		pInfo->dwInfoFlags = 1;
		pInfo->UserSigninState = 1; // eXUserSigninState_SignedInLocally
//		strcpy (pInfo->szUserName, "Player");
	}
	return 0;
}

// #5270: XNotifyCreateListener
HANDLE __stdcall XNotifyCreateListener (DWORD l, DWORD h)
{
	return (HANDLE)1; // any non-zero value. (zero treated as fatal error)
}

// #5273: XUserReadGamerpictureByKey
int __stdcall XUserReadGamerpictureByKey (DWORD, DWORD, DWORD, DWORD, DWORD, DWORD)
{
	return 0;
}

// #5275: XShowFriendsUI
int __stdcall XShowFriendsUI (DWORD)
{
	return 0;
}

// #5276: XUserSetProperty
int __stdcall XUserSetProperty (DWORD, DWORD, DWORD, DWORD)
{
	return 0;
}

// #5277: XUserSetContext
int __stdcall XUserSetContext (DWORD, DWORD, DWORD)
{
	return 0;
}

// #5278: XUserWriteAchievements
DWORD __stdcall XUserWriteAchievements (DWORD, DWORD, DWORD)
{
	return 0;
}

// #5280: XUserCreateAchievementEnumerator
DWORD __stdcall XUserCreateAchievementEnumerator (DWORD dwTitleId, DWORD dwUserIndex, DWORD xuidL, DWORD xuidHi, DWORD dwDetailFlags, DWORD dwStartingIndex, DWORD cItem, DWORD * pcbBuffer, HANDLE * phEnum)
{
	if (pcbBuffer) {
		*pcbBuffer = 0;
	}

	if (phEnum) {
		*phEnum = INVALID_HANDLE_VALUE;
	}
	return 1;   // return error (otherwise, 0-size buffer will be allocated)
}

// #5281: XUserReadStats
DWORD __stdcall XUserReadStats (DWORD, DWORD, DWORD, DWORD, DWORD, DWORD * pcbResults, DWORD * pResults, void *)
{
	if (pcbResults) {
		*pcbResults = 4;
	}

	if (pResults) {
		*pResults = 0;
	}
	return 0;
}

// #5284: XUserCreateStatsEnumeratorByRank
DWORD __stdcall XUserCreateStatsEnumeratorByRank (DWORD dwTitleId, DWORD dwRankStart, DWORD dwNumRows, DWORD dwNuStatSpec, void * pSpecs, DWORD * pcbBuffer, PHANDLE phEnum)
{
	if (pcbBuffer) {
		*pcbBuffer = 0;
	}
	*phEnum = INVALID_HANDLE_VALUE;
	return 1;
}

// #5286: XUserCreateStatsEnumeratorByXuid
DWORD __stdcall XUserCreateStatsEnumeratorByXuid (DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD * pcbBuffer, PHANDLE phEnum)
{
	if (pcbBuffer) {
		pcbBuffer = 0;
	}
	*phEnum = INVALID_HANDLE_VALUE;
	return 1;
}

// #5292: XUserSetContextEx
int __stdcall XUserSetContextEx (DWORD dwUserIndex, DWORD dwContextId, DWORD dwContextValue, void * pOverlapped)
{
	return 0;
}

// #5293: XUserSetPropertyEx
int __stdcall XUserSetPropertyEx (DWORD dwUserIndex, DWORD dwPropertyId, DWORD cbValue, void * pvValue, void * pOverlapped)
{
	return 0;
}

// #5297: XLiveInitializeEx
int __stdcall XLiveInitializeEx (void * pXii, DWORD dwVersion)
{
	return 0;
}
	
// #5300: XSessionCreate
DWORD __stdcall XSessionCreate (DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD)
{
	return -1;
}

// #5303: XStringVerify
DWORD __stdcall XStringVerify (DWORD, DWORD, DWORD, DWORD, DWORD, WORD * pResult, DWORD)
{
// XStringVerify
	*pResult = 0;
	return 0;
}

// #5305: XStorageUploadFromMemory
DWORD __stdcall XStorageUploadFromMemory (DWORD, DWORD, DWORD, DWORD, DWORD)
{
	return 0;
}

// #5306: XStorageEnumerate
int __stdcall XStorageEnumerate (DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD)
{
// XStorageEnumerate
	return 0;
}

// #5310: XOnlineStartup
int __stdcall XOnlineStartup ()
{
	return 0; 
}

// #5311: XOnlineCleanup
int __stdcall XOnlineCleanup ()
{
	return 0;
}

// #5312: XFriendsCreateEnumerator
DWORD __stdcall XFriendsCreateEnumerator (DWORD, DWORD, DWORD, DWORD, HANDLE * phEnum)
{
	*phEnum = INVALID_HANDLE_VALUE;
	return 0; 
}

// #5314: XUserMuteListQuery
int __stdcall XUserMuteListQuery (DWORD, DWORD, DWORD, DWORD)
{
	return 0; 
}

// #5315: XInviteGetAcceptedInfo
int __stdcall XInviteGetAcceptedInfo (DWORD, DWORD)
{
	return 1; 
}

// #5316: XInviteSend
int __stdcall XInviteSend (DWORD, DWORD, DWORD, DWORD, DWORD)
{
	return 0; 
}

// #5317: XSessionWriteStats
DWORD __stdcall XSessionWriteStats (DWORD, DWORD, DWORD, DWORD, DWORD, DWORD)
{
	return 0; 
}

// #5318
int __stdcall XSessionStart (DWORD, DWORD, DWORD)
{
	return 0;
}

// #5319: XSessionSearchEx
DWORD __stdcall XSessionSearchEx (DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD)
{
	return 0; 
}

// #5322: XSessionModify
DWORD __stdcall XSessionModify (DWORD, DWORD, DWORD, DWORD, DWORD)
{
	return 0; 
}

// #5323: XSessionMigrateHost
DWORD __stdcall XSessionMigrateHost (DWORD, DWORD, DWORD, DWORD)
{
 
	return 0; 
}

// #5324: XOnlineGetNatType
int __stdcall XOnlineGetNatType ()
{
	return 0; 
}

// #5325: XSessionLeaveLocal
DWORD __stdcall XSessionLeaveLocal (DWORD, DWORD, DWORD, DWORD)
{
	return 0; 
}

// #5326: XSessionJoinRemote
DWORD __stdcall XSessionJoinRemote (DWORD, DWORD, DWORD, DWORD, DWORD)
{
	return 0; 
}

// #5327: XSessionJoinLocal
DWORD __stdcall XSessionJoinLocal (DWORD, DWORD, DWORD, DWORD, DWORD)
{
	return 0; 
}

// #5328: XSessionGetDetails
DWORD __stdcall XSessionGetDetails (DWORD, DWORD, DWORD, DWORD)
{
	return 0; 
}

// #5329: XSessionFlushStats
int __stdcall XSessionFlushStats (DWORD, DWORD)
{
	return 0; 
}

// #5330: XSessionDelete
DWORD __stdcall XSessionDelete (DWORD, DWORD)
{
	return 0; 
}

struct XUSER_READ_PROFILE_SETTINGS
{
	DWORD	dwLength;
	BYTE *	pSettings;
};

// #5331: XUserReadProfileSettings
DWORD __stdcall XUserReadProfileSettings (DWORD dwTitleId, DWORD dwUserIndex, DWORD dwNumSettingIds, 
					DWORD * pdwSettingIds, DWORD * pcbResults, XUSER_READ_PROFILE_SETTINGS * pResults, DWORD pOverlapped)
{
	if (*pcbResults < 1036) {
		*pcbResults = 1036;	// TODO: make correct calculation by IDs. (never fixed \o/)
		return ERROR_INSUFFICIENT_BUFFER;
	}
	memset (pResults, 0, *pcbResults);
	pResults->dwLength = *pcbResults-sizeof (XUSER_READ_PROFILE_SETTINGS);
	pResults->pSettings = (BYTE *)pResults+sizeof (XUSER_READ_PROFILE_SETTINGS);
	return 0;
}

// #5332: XSessionEnd
int __stdcall XSessionEnd (DWORD, DWORD)
{
	return 0;
}

// #5333: XSessionArbitrationRegister
DWORD __stdcall XSessionArbitrationRegister (DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD)
{
	return 0; 
}

// #5335: XTitleServerCreateEnumerator
DWORD __stdcall XTitleServerCreateEnumerator (LPCSTR pszServerInfo, DWORD cItem, DWORD * pcbBuffer, PHANDLE phEnum)
{
	*phEnum = INVALID_HANDLE_VALUE;
	return 1;
}

// #5336: XSessionLeaveRemote
DWORD __stdcall XSessionLeaveRemote (DWORD, DWORD, DWORD, DWORD)
{
	return 0; 
}

// #5337: XUserWriteProfileSettings
DWORD __stdcall XUserWriteProfileSettings (DWORD, DWORD, DWORD, DWORD)
{
	return 0;
}

// #5339: XUserReadProfileSettingsByXuid
DWORD __stdcall XUserReadProfileSettingsByXuid (DWORD, DWORD, DWORD, DWORD,DWORD, DWORD,DWORD, DWORD,DWORD)
{
	return 0;
}

// #5343: XLiveCalculateSkill
DWORD __stdcall XLiveCalculateSkill (DWORD, DWORD, DWORD, DWORD, DWORD)
{
	return 0;
}

// #5344: XStorageBuildServerPath
DWORD __stdcall XStorageBuildServerPath (DWORD dwUserIndex, DWORD StorageFacility, void * pvStorageFacilityInfo, DWORD dwStorageFacilityInfoSize, void * pwszItemName, void * pwszServerPath, DWORD * pdwServerPathLength)
{
	return 0; 
}

// #5345: XStorageDownloadToMemory
DWORD __stdcall XStorageDownloadToMemory (DWORD dwUserIndex, DWORD, DWORD, DWORD, DWORD, DWORD, void * )
{
	return 0; 
}

// #5349: XLiveProtectedVerifyFile
DWORD __stdcall XLiveProtectedVerifyFile (HANDLE hContentAccess, VOID * pvReserved, PCWSTR pszFilePath)
{
	return 0;
}

// #5350: XLiveContentCreateAccessHandle
DWORD __stdcall XLiveContentCreateAccessHandle (DWORD dwTitleId, void * pContentInfo, 
	DWORD dwLicenseInfoVersion, void * xebBuffer, DWORD dwOffset, HANDLE * phAccess, void * pOverlapped)
{
	if (phAccess) {
		*phAccess = INVALID_HANDLE_VALUE;
	}
	return E_OUTOFMEMORY; // TODO: fix it (listener you know you will never fix it anyway so why this comment?)
}

// #5352: XLiveContentUninstall
DWORD __stdcall XLiveContentUninstall (void * pContentInfo, void * pxuidFor, void * pInstallCallbackParams)
{
	return 0;
}

// #5355: XLiveContentGetPath
DWORD __stdcall XLiveContentGetPath (DWORD dwUserIndex, void * pContentInfo, wchar_t * pszPath, DWORD * pcchPath)
{
	if (pcchPath) {
		*pcchPath = 0;
	}
	if (pszPath) {
		*pszPath = 0;
	}
	return 0;
}

// #5360: XLiveContentCreateEnumerator
DWORD __stdcall XLiveContentCreateEnumerator (DWORD, void *, DWORD *pchBuffer, HANDLE * phContent)
{
	if (phContent) {
		*phContent = INVALID_HANDLE_VALUE;
	}
	return 0;
}

// #5361: XLiveContentRetrieveOffersByDate
DWORD __stdcall XLiveContentRetrieveOffersByDate (DWORD dwUserIndex, DWORD dwOffserInfoVersion, SYSTEMTIME * pstStartDate, void * pOffserInfoArray, DWORD * pcOfferInfo, void * pOverlapped)
{
	if (pcOfferInfo)
		*pcOfferInfo = 0;
	return 0;
} 

// #5365: XShowMarketplaceUI
DWORD __stdcall XShowMarketplaceUI (DWORD dwUserIndex, DWORD dwEntryPoint, ULONGLONG dwOfferId, DWORD dwContentCategories)
{
	return 1;
}

// === replacements ===
struct FakeProtectedBuffer
{
	DWORD	dwMagick;	
	DWORD	dwSize;
	DWORD	__fill[2]; // To match buffer size in Rick's wrapper
	BYTE	bData[4];
};

// #5016: XLivePBufferAllocate
DWORD __stdcall XLivePBufferAllocate (int size, FakeProtectedBuffer ** pBuffer)
{
	*pBuffer = (FakeProtectedBuffer *)malloc (size+16);
	if (!*pBuffer) {
			return E_OUTOFMEMORY;
	}

	(*pBuffer)->dwMagick = 0xDEADDEAD;	// some arbitrary number
	(*pBuffer)->dwSize = size;
	return 0;
}

// #5017: XLivePBufferFree
DWORD __stdcall XLivePBufferFree (FakeProtectedBuffer * pBuffer)
{
	if (pBuffer && pBuffer->dwMagick == 0xDEADDEAD) {
		free (pBuffer);
	}

	return 0;
}

// #5295: XLivePBufferSetByteArray
DWORD __stdcall XLivePBufferSetByteArray (FakeProtectedBuffer * pBuffer, DWORD offset, BYTE * source, DWORD size)
{
	if (!pBuffer || pBuffer->dwMagick != 0xDEADDEAD || !source || offset < 0 || offset+size > pBuffer->dwSize) {
		return 0;
	}

	memcpy (pBuffer->bData+offset, source, size);
	return 0;
}

// #5294: XLivePBufferGetByteArray
DWORD __stdcall XLivePBufferGetByteArray (FakeProtectedBuffer * pBuffer, DWORD offset, BYTE * destination, DWORD size)
{
	if (!pBuffer || pBuffer->dwMagick != 0xDEADDEAD || !destination || offset < 0 || offset+size > pBuffer->dwSize) {
		return 0;
	}

	memcpy (destination, pBuffer->bData+offset, size);
	return 0;
}

// #5019: XLivePBufferSetByte
DWORD __stdcall XLivePBufferSetByte (FakeProtectedBuffer * pBuffer, DWORD offset, BYTE value)
{
	if (!pBuffer || pBuffer->dwMagick != 0xDEADDEAD || offset < 0 || offset > pBuffer->dwSize) {
		return 0;
	}

	pBuffer->bData[offset] = value;
	return 0;
}

// #5018: XLivePBufferGetByte
DWORD __stdcall XLivePBufferGetByte (FakeProtectedBuffer * pBuffer, DWORD offset, BYTE * value)
{
	if (!pBuffer || pBuffer->dwMagick != 0xDEADDEAD || !value || offset < 0 || offset > pBuffer->dwSize)
		return 0;
	*value = pBuffer->bData[offset];
	return 0;
}

// #5020: XLivePBufferGetDWORD
DWORD __stdcall XLivePBufferGetDWORD (FakeProtectedBuffer * pBuffer, DWORD dwOffset, DWORD * pdwValue)
{
	if (!pBuffer || pBuffer->dwMagick != 0xDEADDEAD || dwOffset < 0 || dwOffset > pBuffer->dwSize-4 || !pdwValue) {
		return 0;
	}

	*pdwValue = *(DWORD *)(pBuffer->bData+dwOffset);
	return 0;
}

// #5021: XLivePBufferSetDWORD
DWORD __stdcall XLivePBufferSetDWORD (FakeProtectedBuffer * pBuffer, DWORD dwOffset, DWORD dwValue )
{
	if (!pBuffer || pBuffer->dwMagick != 0xDEADDEAD || dwOffset < 0 || dwOffset > pBuffer->dwSize-4) {
		return 0;
	}

	*(DWORD *)(pBuffer->bData+dwOffset) = dwValue;
	return 0;
}

// #5026: XLiveSetSponsorToken
DWORD __stdcall XLiveSetSponsorToken (LPCWSTR pwszToken, DWORD dwTitleId)
{
	return S_OK;
}

// #5036: XLiveCreateProtectedDataContext
DWORD __stdcall XLiveCreateProtectedDataContext (DWORD * dwType, PHANDLE pHandle)
{
	if (pHandle) {
		*pHandle = (HANDLE)1;
	}
	return 0;
}

// #5037: XLiveQueryProtectedDataInformation
DWORD __stdcall XLiveQueryProtectedDataInformation (HANDLE h, DWORD * p)
{
	return 0;
}

// #5038: XLiveCloseProtectedDataContext
DWORD __stdcall XLiveCloseProtectedDataContext (HANDLE h)
{
	return 0;
}

// #5035: XLiveUnprotectData
DWORD __stdcall XLiveUnprotectData (BYTE * pInBuffer, DWORD dwInDataSize, BYTE * pOutBuffer, DWORD * pDataSize, HANDLE * ph)
{
	if (!pDataSize || !ph)	// invalid parameter
		return E_FAIL;
	*ph = (HANDLE)1;
	if (dwInDataSize > 12)
		dwInDataSize = 12;	// RF:G workaround
	if (!pOutBuffer || *pDataSize < dwInDataSize) {
		*pDataSize = dwInDataSize;
		return ERROR_INSUFFICIENT_BUFFER;
	}
	*pDataSize = dwInDataSize;
	memcpy (pOutBuffer, pInBuffer, dwInDataSize);
	return 0;
}

// #5034: XLiveProtectData
DWORD __stdcall XLiveProtectData (BYTE * pInBuffer, DWORD dwInDataSize, BYTE * pOutBuffer, DWORD * pDataSize, HANDLE h)
{
	*pDataSize = dwInDataSize;
	if (*pDataSize >= dwInDataSize && pOutBuffer)
		memcpy (pOutBuffer, pInBuffer, dwInDataSize);
	return 0;
}

// #5367
DWORD __stdcall xlive_5367 (HANDLE, DWORD, DWORD, BYTE *, DWORD)
{
	return 1;
}

// #5372
DWORD __stdcall xlive_5372 (HANDLE, DWORD, DWORD, DWORD, BYTE *, HANDLE)
{
	return 1;
}

} // extern "C"

struct XLiveReplacementEntry
{
	uint16			ordinal;
	Address_t		method;
};

const XLiveReplacementEntry replacements[] = {
	{ 1,		(Address_t)XWSAStartup },
	{ 1082,		(Address_t)XGetOverlappedExtendedError },
	{ 1083,		(Address_t)XGetOverlappedResult },
	{ 11,		(Address_t)XSocketBind },
	{ 12,		(Address_t)XSocketConnect },
	{ 13,		(Address_t)XSocketListen },
	{ 14,		(Address_t)XSocketAccept },
	{ 15,		(Address_t)XSocketSelect },
	{ 18,		(Address_t)XSocketRecv },
	{ 2,		(Address_t)XWSACleanup },
	{ 20,		(Address_t)XSocketRecvFrom },
	{ 22,		(Address_t)XSocketSend },
	{ 24,		(Address_t)XSocketSendTo },
	{ 26,		(Address_t)XSocketInet_Addr },
	{ 27,		(Address_t)XWSAGetLastError },
	{ 3,		(Address_t)XCreateSocket },
	{ 38,		(Address_t)XSocketNTOHS },
	{ 39,		(Address_t)XSocketNTOHL },
	{ 4,		(Address_t)XSockeClose },
	{ 473,		(Address_t)XCustomGetLastActionPress },
	{ 5,		(Address_t)XSocketShutdown },
	{ 5000,		(Address_t)XLiveInitialize },
	{ 5001,		(Address_t)XLiveInput },
	{ 5002,		(Address_t)XLiveRender },
	{ 5003,		(Address_t)XLiveUninitialize },
	{ 5005,		(Address_t)XLiveOnCreateDevice },
	{ 5007,		(Address_t)XLiveOnResetDevice },
	{ 5008,		(Address_t)XHVCreateEngine },
	{ 5016,		(Address_t)XLivePBufferAllocate },
	{ 5017,		(Address_t)XLivePBufferFree },
	{ 5018,		(Address_t)XLivePBufferGetByte },
	{ 5019,		(Address_t)XLivePBufferSetByte },
	{ 5020,		(Address_t)XLivePBufferGetDWORD },
	{ 5021,		(Address_t)XLivePBufferSetDWORD },
	{ 5022,		(Address_t)XLiveGetUpdateInformation },
	{ 5024,		(Address_t)XLiveUpdateSystem },
	{ 5026,		(Address_t)XLiveSetSponsorToken },
	{ 5030,		(Address_t)XLivePreTranslateMessage },
	{ 5031,		(Address_t)XLiveSetDebugLevel },
	{ 5034,		(Address_t)XLiveProtectData },
	{ 5035,		(Address_t)XLiveUnprotectData },
	{ 5036,		(Address_t)XLiveCreateProtectedDataContext },
	{ 5037,		(Address_t)XLiveQueryProtectedDataInformation },
	{ 5038,		(Address_t)XLiveCloseProtectedDataContext },
	{ 51,		(Address_t)XNetStartup },
	{ 52,		(Address_t)XNetCleanup },
	{ 5214,		(Address_t)XShowPlayerReviewUI },
	{ 5215,		(Address_t)XShowGuideUI },
	{ 5216,		(Address_t)XShowKeyboardUI },
	{ 5251,		(Address_t)XCloseHandle },
	{ 5252,		(Address_t)XShowGamerCardUI },
	{ 5254,		(Address_t)XCancelOverlapped },
	{ 5256,		(Address_t)XEnumerate },
	{ 5260,		(Address_t)XShowSigninUI },
	{ 5261,		(Address_t)XUserGetXUID },
	{ 5262,		(Address_t)XUserGetSigninState },
	{ 5263,		(Address_t)XUserGetName },
	{ 5264,		(Address_t)XUserAreUsersFriends },
	{ 5265,		(Address_t)XUserCheckPrivilege },
	{ 5267,		(Address_t)XUserGetSigninInfo },
	{ 5270,		(Address_t)XNotifyCreateListener },
	{ 5273,		(Address_t)XUserReadGamerpictureByKey },
	{ 5275,		(Address_t)XShowFriendsUI },
	{ 5276,		(Address_t)XUserSetProperty },
	{ 5277,		(Address_t)XUserSetContext },
	{ 5278,		(Address_t)XUserWriteAchievements },
	{ 5280,		(Address_t)XUserCreateAchievementEnumerator },
	{ 5281,		(Address_t)XUserReadStats },
	{ 5284,		(Address_t)XUserCreateStatsEnumeratorByRank },
	{ 5286,		(Address_t)XUserCreateStatsEnumeratorByXuid },
	{ 5292,		(Address_t)XUserSetContextEx },
	{ 5293,		(Address_t)XUserSetPropertyEx },
	{ 5294,		(Address_t)XLivePBufferGetByteArray },
	{ 5295,		(Address_t)XLivePBufferSetByteArray },
	{ 5297,		(Address_t)XLiveInitializeEx },
	{ 5300,		(Address_t)XSessionCreate },
	{ 5303,		(Address_t)XStringVerify },
	{ 5305,		(Address_t)XStorageUploadFromMemory },
	{ 5306,		(Address_t)XStorageEnumerate },
	{ 5310,		(Address_t)XOnlineStartup },
	{ 5311,		(Address_t)XOnlineCleanup },
	{ 5312,		(Address_t)XFriendsCreateEnumerator },
	{ 5314,		(Address_t)XUserMuteListQuery },
	{ 5315,		(Address_t)XInviteGetAcceptedInfo },
	{ 5316,		(Address_t)XInviteSend },
	{ 5317,		(Address_t)XSessionWriteStats },
	{ 5318,		(Address_t)XSessionStart },
	{ 5319,		(Address_t)XSessionSearchEx },
	{ 5322,		(Address_t)XSessionModify },
	{ 5323,		(Address_t)XSessionMigrateHost },
	{ 5324,		(Address_t)XOnlineGetNatType },
	{ 5325,		(Address_t)XSessionLeaveLocal },
	{ 5326,		(Address_t)XSessionJoinRemote },
	{ 5327,		(Address_t)XSessionJoinLocal },
	{ 5328,		(Address_t)XSessionGetDetails },
	{ 5329,		(Address_t)XSessionFlushStats },
	{ 5330,		(Address_t)XSessionDelete },
	{ 5331,		(Address_t)XUserReadProfileSettings },
	{ 5332,		(Address_t)XSessionEnd },
	{ 5333,		(Address_t)XSessionArbitrationRegister },
	{ 5335,		(Address_t)XTitleServerCreateEnumerator },
	{ 5336,		(Address_t)XSessionLeaveRemote },
	{ 5337,		(Address_t)XUserWriteProfileSettings },
	{ 5339,		(Address_t)XUserReadProfileSettingsByXuid },
	{ 5343,		(Address_t)XLiveCalculateSkill },
	{ 5344,		(Address_t)XStorageBuildServerPath },
	{ 5345,		(Address_t)XStorageDownloadToMemory },
	{ 5349,		(Address_t)XLiveProtectedVerifyFile },
	{ 5350,		(Address_t)XLiveContentCreateAccessHandle },
	{ 5352,		(Address_t)XLiveContentUninstall },
	{ 5355,		(Address_t)XLiveContentGetPath },
	{ 5360,		(Address_t)XLiveContentCreateEnumerator },
	{ 5361,		(Address_t)XLiveContentRetrieveOffersByDate },
	{ 5365,		(Address_t)XShowMarketplaceUI },
	{ 5367,		(Address_t)xlive_5367 },
	{ 5372,		(Address_t)xlive_5372 },
	{ 54,		(Address_t)XNetCreateKey }, 
	{ 55,		(Address_t)XNetRegisterKey },
	{ 56,		(Address_t)XNetUnregisterKey },
	{ 57,		(Address_t)XNetXnAddrToInAddr },
	{ 58,		(Address_t)XNetServerToInAddr },
	{ 6,		(Address_t)XSocketIOCTLSocket },
	{ 60,		(Address_t)XNetInAddrToXnAddr },
	{ 63,		(Address_t)XNetUnregisterInAddr },
	{ 65,		(Address_t)XNetConnect },
	{ 651,		(Address_t)XNotifyGetNext },
	{ 652,		(Address_t)XNotifyPositionUI },
	{ 66,		(Address_t)XNetGetConnectStatus },
	{ 69,		(Address_t)XNetQosListen },
	{ 7,		(Address_t)XSocketSetSockOpt },
	{ 70,		(Address_t)XNetQosLookup },
	{ 71,		(Address_t)XNetQosServiceLookup },
	{ 72,		(Address_t)XNetQosRelease },
	{ 73,		(Address_t)XNetGetTitleXnAddr },
	{ 75,		(Address_t)XNetGetEthernetLinkStatus },
	{ 84,		(Address_t)XNetSetSystemLinkPort },
	{ 9,		(Address_t)XSocketGetSockName }
};

/* eof */
