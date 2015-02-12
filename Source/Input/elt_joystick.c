#include"elt_joystick.h"
#include<string.h>


#ifdef EX_WINDOWS
	#include<Windows.h>
	#include<dinput.h>
	#include<dinputd.h>
	#include<Xinput.h>
	//#pragma comment(lib, "dxguid.lib")
	#pragma comment(lib, "dinput8.lib")
	//typedef struct JoyStickHandler{
	//	 IDirectInputDevice8* p_joystick[1];
	//	 Boolean enabledState[1];
	//	union {
	//		DIJOYSTATE* joyState;
	//		DIJOYSTATE2* joyStateAdv;
	//	};
	//}HJoyStick, *HJOYSTICK;
	struct XINPUT_DEVICE_NODE
	{
		DWORD dwVidPid;
		XINPUT_DEVICE_NODE* pNext;
	};
	struct DI_ENUM_CONTEXT
	{
		DIJOYCONFIG* pPreferredJoyCfg;
		Boolean bPreferredJoyCfgValid;
	};
#elif defined(EX_LINUX)
	#include<unistd.h>
	#include<fcntl.h>
	#include<sys/ioctl.h>
	#include<stdio.h>
	#include<linux/joystick.h>
	Int32 joy_id[4];
#elif defined(EX_ANDROID)
#include<android/input.h>
#include<android/keycodes.h>
#include<android/sensor.h>
#endif


DECLSPEC Uint32 ELTAPIENTRY ExNumJoysticks(void){
#ifdef EX_WINDOWS
	Int32 num = 0;
	Uint32 i,count;
	JOYINFO info;
	count = joyGetNumDevs();
	for(i = 0; i < count; i++){
		if(joyGetPos(JOYSTICKID1+i,&info) == JOYERR_NOERROR)
			num++;
	}
	return num;
#elif defined(EX_LINUX)
	return 0;
#elif defined(EX_MAC)
	return 0;
#else
	return 0;
#endif
}

DECLSPEC void* ELTAPIENTRY ExJoystickOpen(Int32 device_index){
#ifdef EX_WINDOWS
	JOYCAPS caps;
	joyGetDevCaps(device_index,&caps,sizeof(caps));
	if(!GetModuleHandle(caps.szRegKey))
		return ExLoadObject(caps.szRegKey);
	else return (void*)TRUE;
#elif defined(EX_LINUX)
	struct js_event event;

	char device_text[sizeof("/dev/input/js0") + 1] = {0};
	sprintf(device_text,"/dev/input/js%d",device_index);

	joy_id[device_index] = open(device_text, O_RDONLY);
	read(joy_id[device_index],&event,sizeof(event));
	return joy_id[device_index];
#endif
}
DECLSPEC int ELTAPIENTRY ExJoyStickClose(Int32 device_index){
    #ifdef EX_WINDOWS

	return 0;
    #elif defined(EX_LINUX)
    close(joy_id[device_index]);

    #endif // EX_WINDOWS
}

DECLSPEC ExGUID ELTAPIENTRY ExJoystickGetDeviceGUID(Int32 device_index){
	ExGUID guid;
#if defined(EX_WINDOWS)
	JOYCAPS2W caps2;
	joyGetDevCaps(device_index,(LPJOYCAPSW)&caps2,sizeof(caps2));
	memcpy(&guid,&caps2.NameGuid,sizeof(ExGUID));
#elif defined(EX_LINUX)
	//read(joy_id[device_index],&event,sizeof(event));
#endif
	return guid;
}

DECLSPEC const ExChar* ELTAPIENTRY ExJoyStickName(Uint32 ptr){
#ifdef EX_WINDOWS
	JOYCAPS caps;
	joyGetDevCaps(ptr,&caps,sizeof(caps));
	return caps.szPname;
#elif defined(EX_LINUX)
	char name[128];
	if(ioctl(joy_id[ptr],JSIOCGNAME(sizeof(name)),name) < 0)
		strncpy(name,"Unknown", sizeof(name));
#ifdef EX_DEBUG
	printf(name);
#endif
	return name;
#endif
}

DECLSPEC Int32 ELTAPIENTRY ExJoystickNumButtons(Uint32 ptr){
#ifdef EX_WINDOWS
	JOYCAPS caps;
	joyGetDevCaps(ptr,&caps, sizeof(caps));
	return caps.wNumButtons;
#elif defined(EX_LINUX)
    int num_buttons;
    if(!ioctl(joy_id[ptr],JSIOCGBUTTONS,&num_buttons))
        return num_buttons;
    else
        return -1;
#endif
}
DECLSPEC Int32 ELTAPIENTRY ExJoystickNumAxis(Int32 device_index){
    #ifdef EX_WINDOWS
	JOYCAPS caps;
	joyGetDevCaps(device_index,&caps, sizeof(caps));
	return caps.wNumAxes;
    #elif defined(EX_LINUX)
    int num_axis;
    if(!ioctl(joy_id[device_index],JSIOCGAXES,&num_axis))
        return num_axis;
    else
        return -1;
    #endif
}

DECLSPEC Int16 ELTAPIENTRY ExJoystickGetAxis(Int32 device_index,int axis){
    #ifdef EX_WINDOWS
    JOYINFO  pji;
    joyGetPos(device_index,&pji);
    return ((unsigned int*)&pji)[axis];
    #elif defined(EX_LINUX)
    struct js_event js;
    if(read(joy_id[device_index], &js,sizeof(struct js_event))){
        if(js.type & JS_EVENT_AXIS)
            return js.value;
    }else return -1;
    #endif
}
/**
    \Button Get joystick button
*/
DECLSPEC Uint8 ELTAPIENTRY ExJoyStickGetButton(Int32 device_index, int button){
    #ifdef EX_WINDOWS
    JOYINFO  pji;
    joyGetPos(device_index,&pji);
    return ((unsigned int*)&pji)[button];
    #elif defined(EX_LINUX)
    struct js_event js;
    if(read(joy_id[device_index], &js,sizeof(struct js_event))){
        if(js.type & JS_EVENT_BUTTON)
            return js.value;
    }else return -1;
    #endif // EX_WINDOWS
}

//http://msdn.microsoft.com/en-us/library/windows/desktop/ms645546(v=vs.85).aspx

//HJoyStick* m_joyStickhandler = EX_NULL;
/*
DECLSPEC ERESULT ELTAPIENTRY ExInitJoyStick( ExWin hwnd){
#ifdef EX_WINDOWS
	ERESULT hr;
	RAWINPUTDEVICE rid;

	ExIsWinError(LoadLibrary(EX_TEXT("dinput.dll")));

	IDirectInput8* DI = g_pDI;
	rid.usUsagePage = 1;
	rid.usUsage = 4;
	rid.dwFlags = 0;
	rid.hwndTarget = hwnd;
	if(!RegisterRawInputDevices(&rid, 1, sizeof(RAWINPUTDEVICE)))
			return -1;
	return 1;
	//if(!m_joyStickhandler){
	//	m_joyStickhandler = (HJoyStick*)ExMalloc(sizeof(HJoyStick));
	//	memset(m_joyStickhandler,0, sizeof(HJoyStick));
	//	m_joyStickhandler->joyState = (DIJOYSTATE*)ExMalloc(sizeof(DIJOYSTATE));
	//}
	////for(Uint32 x = 0; x < EX_JOYSTICK_MAX_COUNT; x++){
	////	continue;
	////}
	//
	//DIJOYCONFIG preferredJoyCfg = {0};
	//DI_ENUM_CONTEXT enumContext;
	//enumContext.pPreferredJoyCfg = &preferredJoyCfg;
	//enumContext.bPreferredJoyCfgValid = false;
	////enumContext.
	//
	//IDirectInputJoyConfig8* pJoyConfig = NULL;
	//if(FAILED(hr = g_pDI->QueryInterface(IID_IDirectInputJoyConfig8,(void**)&pJoyConfig))){
	//	// print some error regarding the failure!!
	//	return hr;
	//}
	//preferredJoyCfg.dwSize = sizeof(preferredJoyCfg);
	//if(SUCCEEDED(pJoyConfig->GetConfig(0,&preferredJoyCfg,DIJC_GUIDINSTANCE))){
	//	enumContext.bPreferredJoyCfgValid = true;
	//}
	//// Look for a simple joystick we can use for this sample program.
	//if(FAILED(hr = DI->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoysticksCallback,&enumContext, DIEDFL_ATTACHEDONLY))){
	//	return hr;
	//}
	//
	//if(NULL == m_joyStickhandler->p_joystick[0]){
	//	// FAILURE
	//	return hr;
	//}
	//
	//if(FAILED(hr = m_joyStickhandler->p_joystick[0]->SetDataFormat(&c_dfDIJoystick)))
	//	return hr;
	//
	//if(FAILED(hr = m_joyStickhandler->p_joystick[0]->SetCooperativeLevel(hwnd,		((ExGetEngineFlag() & ENGINE_SUPPORT_INPUT_FOREGROUND) != 0 ? DISCL_FOREGROUND : 0)
	//	| ((ExGetEngineFlag() & ENGINE_SUPPORT_INPUT_BACKGROUND) != 0 ? DISCL_BACKGROUND : 0)
	//	| ((ExGetEngineFlag() & ENGINE_SUPPORT_INPUT_EXCLUSIVE) == 0 ? DISCL_NONEXCLUSIVE : DISCL_EXCLUSIVE))))
	//	return hr;
	//
	//if(FAILED(hr = m_joyStickhandler->p_joystick[0]->EnumObjects(EnumObjectsCallBack, (void*)hwnd, DIDFT_ALL)))
	//	return hr;
	//return S_OK;
#endif
	return 0;
}*/
