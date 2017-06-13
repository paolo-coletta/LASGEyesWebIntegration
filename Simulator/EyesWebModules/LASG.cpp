// LASG.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"

using namespace Eyw;

static CSTR g_szDllIdentifier = "LASG_{8EBE99BE-E0FE-451C-A833-EE3B8CD4B10C}";


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

