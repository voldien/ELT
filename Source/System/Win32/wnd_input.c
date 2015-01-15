#include"wnd_input.h"
#ifdef EX_WINDOWS
//IDirectInput8* g_pDI = EX_NULL;

DECLSPEC void* ELTAPIENTRY ExGetDirectInput(void){return 0;/*g_pDI;*/}

DECLSPEC ERESULT ELTAPIENTRY ExInitDirectInput(Uint32 flag){
	ERESULT hr;
	// Register with the DIrectInput subSystem and get a pointer
	// to a IDirectInput inteface we can use.
	// Create a DInput Object.
	/*if(FAILED(hr = DirectInput8Create(GetModuleHandle(EX_NULL),DIRECTINPUT_VERSION, IID_IDirectInput8,
		(void**)&g_pDI,EX_NULL))){
			ExIsHError(hr);
		g_pDI = EX_NULL;
		return (hr == S_OK);
	}*/
	return TRUE;
}
#include"./../../Input/elt_keyboard.h"
#include"./../../Input/elt_mouse.h"
#include"./../../Input/elt_joystick.h"
DECLSPEC ERESULT ELTAPIENTRY ExInitDirectInputDevice(ExWin hWnd, Uint32 flag){
	ERESULT hr;
	//if((flag & ENGINE_SUPPORT_JOYSTICK))
		//hr = ExInitJoyStick(hWnd);
	//if((flag & ENGINE_SUPPORT_KEYBOARD))
		//hr = ExInitKeyBoard(hWnd);
	//if((flag & ENGINE_SUPPORT_MOUSE))
		//hr = ExInitMouse(hWnd);
	//if((flag & ENGINE_SUPPORT_XBOX))
	//	hr = ExInitXController();
	return hr;
}



DECLSPEC ERESULT ELTAPIENTRY ExShutDownDirect(void){
	ERESULT ehr = 0;
	/*if(!g_pDI)
		return 2;
	if(!FAILED(ehr = g_pDI->Release())){
		g_pDI = EX_NULL;
	}*/
//	ExJoyStickShutDown();
//	ExPSShutDown();
	//ExXShutDown();
	return ehr;
}


DECLSPEC ERESULT ELTAPIENTRY ExInitRawInput(HWND hWnd,Uint64 flag){

	RAWINPUTDEVICE Rid[8];
	Int DevicCount = 0;

	//if(flag & ENGINE_SUPPORT_JOYSTICK){
	//	Rid[0].usUsagePage = 0x01; 
	//	Rid[0].usUsage = 0x05; 
	//	Rid[0].dwFlags = 0;                 // adds game pad
	//	Rid[0].hwndTarget = hWnd;
	//	DevicCount++;
	//}
	//if(flag & ENGINE_SUPPORT_GAMEPAD){
	//
	//	DevicCount++;
	//}
	//if(flag & ENGINE_SUPPORT_KEYBOARD){
	//
	//	DevicCount++;
	//}
	//if(flag & ENGINE_SUPPORT_MOUSE){
	//
	//	DevicCount++;
	//}
	//if(flag & ENGINE_SUPPORT_JOYSTICK){
	//
	//}
	Rid[0].usUsagePage = 0x01; 
	Rid[0].usUsage = 0x05; 
	Rid[0].dwFlags = 0;                 // adds game pad
	Rid[0].hwndTarget = hWnd;

	Rid[1].usUsagePage = 0x01; 
	Rid[1].usUsage = 0x04; 
	Rid[1].dwFlags = 0;                 // adds joystick
	Rid[1].hwndTarget = hWnd;

	Rid[2].usUsagePage = 0x0B; 
	Rid[2].usUsage = 0x00; 
	Rid[2].dwFlags = RIDEV_PAGEONLY;    //adds devices from telephony page
	Rid[2].hwndTarget = hWnd;

	Rid[3].usUsagePage = 0x0B; 
	Rid[3].usUsage = 0x02; 
	Rid[3].dwFlags = RIDEV_EXCLUDE;     //excludes answering machines
	Rid[3].hwndTarget = hWnd;

	if (RegisterRawInputDevices(Rid,DevicCount,DevicCount * sizeof(RAWINPUTDEVICE)) == FALSE) {
		wExDevPrintf(EX_TEXT("Failed to Register Raw Input Device | %s"), ExGetErrorMessage(GetLastError()));
		return FALSE;
	}
	return TRUE;
}
/*
#include <Wbemcli.h>
# pragma comment(lib, "wbemuuid.lib")
#define SAFE_DELETE(p)  { if(p) { delete (p);     (p)=NULL; } }
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }
Boolean                   g_bFilterOutXinputDevices = FALSE;
XINPUT_DEVICE_NODE*     g_pXInputDeviceList = NULL;
DECLSPEC Boolean ELTAPIENTRY ExIsXInputDevice(const GUID* pGuidProductFromDirectInput){
	IWbemLocator*           pIWbemLocator  = NULL;
    IEnumWbemClassObject*   pEnumDevices   = NULL;
    IWbemClassObject*       pDevices[20]   = {0};
    IWbemServices*          pIWbemServices = NULL;
    BSTR                    bstrNamespace  = NULL;
    BSTR                    bstrDeviceID   = NULL;
    BSTR                    bstrClassName  = NULL;
    DWORD                   uReturned      = 0;
    Boolean                 bIsXinputDevice= FALSE;
    UINT                    iDevice        = 0;
    VARIANT                 var;
    HRESULT                 hr;
	Boolean					bCleanupCOM ;

	// CoInit if nedded 
	hr = CoInitialize(EX_NULL);
	bCleanupCOM = SUCCEEDED(hr);

	hr = CoCreateInstance(__uuidof(WbemLocator),
						EX_NULL,
						CLSCTX_INPROC_SERVER,__uuidof(IWbemLocator), (LPVOID*)&pIWbemLocator);
	if(FAILED(hr) || !pIWbemLocator)
		goto LCleanup;
	
    // Create BSTRs for WMI
    bstrNamespace = SysAllocString( L"\\\\.\\root\\cimv2" ); if( bstrNamespace == NULL ) goto LCleanup;
    bstrDeviceID = SysAllocString( L"DeviceID" );           if( bstrDeviceID == NULL )  goto LCleanup;
    bstrClassName = SysAllocString( L"Win32_PNPEntity" );    if( bstrClassName == NULL ) goto LCleanup;

    // Connect to WMI 
    hr = pIWbemLocator->ConnectServer( bstrNamespace, NULL, NULL, 0L,
                                       0L, NULL, NULL, &pIWbemServices );
    if( FAILED( hr ) || pIWbemServices == NULL )
        goto LCleanup;

	LCleanup:
    if(bstrNamespace)
        SysFreeString(bstrNamespace);
    if(bstrDeviceID)
        SysFreeString(bstrDeviceID);
    if(bstrClassName)
        SysFreeString(bstrClassName);
    for( iDevice=0; iDevice<20; iDevice++ )
        SAFE_RELEASE( pDevices[iDevice] );
    SAFE_RELEASE( pEnumDevices );
    SAFE_RELEASE( pIWbemLocator );
    SAFE_RELEASE( pIWbemServices );

 // Switch security level to IMPERSONATE
    CoSetProxyBlanket( pIWbemServices, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, NULL,
                       RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, 0 );

    // Get list of Win32_PNPEntity devices
    hr = pIWbemServices->CreateInstanceEnum( bstrClassName, 0, NULL, &pEnumDevices );
    if( FAILED( hr ) || pEnumDevices == NULL )
        goto LCleanup;

    // Loop over all devices
    for(; ; )
    {
        // Get 20 at a time
        hr = pEnumDevices->Next( 10000, 20, pDevices, &uReturned );
        if( FAILED( hr ) )
            goto LCleanup;
        if( uReturned == 0 )
            break;

        for( iDevice = 0; iDevice < uReturned; iDevice++ )
        {
            // For each device, get its device ID
            hr = pDevices[iDevice]->Get( bstrDeviceID, 0L, &var, NULL, NULL );
            if( SUCCEEDED( hr ) && var.vt == VT_BSTR && var.bstrVal != NULL )
            {
                // Check if the device ID contains "IG_".  If it does, then it’s an XInput device
                // Unfortunately this information can not be found by just using DirectInput 
                if( wcsstr( var.bstrVal, L"IG_" ) )
                {
                    // If it does, then get the VID/PID from var.bstrVal
                    DWORD dwPid = 0, dwVid = 0;
                    WCHAR* strVid = wcsstr( var.bstrVal, L"VID_" );
                    if( strVid && swscanf( strVid, L"VID_%4X", &dwVid ) != 1 )
                        dwVid = 0;
                    WCHAR* strPid = wcsstr( var.bstrVal, L"PID_" );
                    if( strPid && swscanf( strPid, L"PID_%4X", &dwPid ) != 1 )
                        dwPid = 0;

                    DWORD dwVidPid = MAKELONG( dwVid, dwPid );

                    // Add the VID/PID to a linked list
                    XINPUT_DEVICE_NODE* pNewNode = new XINPUT_DEVICE_NODE;
                    if( pNewNode )
                    {
                        pNewNode->dwVidPid = dwVidPid;
                        pNewNode->pNext = g_pXInputDeviceList;
                        g_pXInputDeviceList = pNewNode;
                    }
                }
            }
            SAFE_RELEASE( pDevices[iDevice] );
        }
    }

   if( bCleanupCOM )
       CoUninitialize();
   
   return bIsXinputDevice;
return 0;
}
*/
#endif