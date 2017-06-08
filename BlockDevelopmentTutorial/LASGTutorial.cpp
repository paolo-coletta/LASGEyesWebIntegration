// LASGTutorial.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"

using namespace Eyw;

static CSTR g_szDllIdentifier = "LASGTUTORIAL_{5AF07DC7-298F-446E-9DD6-877262B32267}";


BOOL APIENTRY DllMain( HMODULE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch( ul_reason_for_call )
	{
	case DLL_PROCESS_ATTACH:
		if( !SDKInit( hModule, g_szDllIdentifier ) )
			return FALSE;
		break;

	case DLL_PROCESS_DETACH:
		SDKDone();
		break;
	}

    return TRUE;
}

