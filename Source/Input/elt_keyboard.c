#include"elt_keyboard.h"

#ifdef EX_WINDOWS
    #include<dinput.h>
    #include<dinputd.h>
    #include<Dbt.h>
    #include<oleauto.h>
    #include<shellapi.h>
#elif defined(EX_LINUX)
    #include<X11/keysym.h>
    #include<X11/extensions/XInput.h>
#elif defined(EX_ANDROID)

#endif

#ifdef EX_WINDOWS

IDirectInputDevice8* m_keyboard_device;
#endif
unsigned char KeyBoardState[2][0xff];

DECLSPEC Keycode ELTAPIENTRY ExGetKeyFromName(const char* name){
#if defined(EX_WINDOWS)
	switch(name[0]){
	case ' ':return 0;
	}
#elif defined(EX_LINUX)
    KeySym sym = XStringToKeysym(name);
    return XKeysymToKeycode(XOpenDisplay(NULL),sym);
#endif
}
DECLSPEC const char* ELTAPIENTRY ExGetKeyName(Keycode keycode){
#ifdef EX_WINDOWS
	char text[20];
	GetKeyNameTextA((keycode << 16),text,sizeof(text));
	return text;
#elif defined(EX_LINUX)
    return XKeysymToString(XKeycodeToKeysym(display,keycode,0));
#endif

}

DECLSPEC ExWin ELTAPIENTRY ExGetKeyboardFocus(void){
#ifdef EX_WINDOWS
	return GetFocus();
#elif defined(EX_LINUX)
	ExWin window;
	int revert_to_return;
	XGetInputFocus(display,&window,&revert_to_return);
	return window;
#elif defined(EX_MAC)
    return NULL;
#endif
}
DECLSPEC const Uint8* ELTAPIENTRY ExGetKeyboardState(Int32* numkeys){
#ifdef EX_WINDOWS
	if(numkeys)*numkeys=0xff;
	unsigned char ispressed = GetKeyboardState(&KeyBoardState[0][0]);
	return KeyBoardState[0];
#elif defined(EX_LINUX)
	if(numkeys)*numkeys=0xff;
	XQueryKeymap(display,KeyBoardState[0]);
	//XQueryKeyboard(display);
	//XGetPointerMapping(display,(unsigned char*)KeyBoardState[0],255);
	//XQueryDeviceState(display,)
	return KeyBoardState[0];
#endif
}

DECLSPEC ERESULT ELTAPIENTRY ExInitKeyBoard(ExWin win){
	ERESULT hr;
#if defined(EX_WINDOWS)
/*	if(FAILED(hr = g_pDI->CreateDevice(GUID_SysKeyboard, &m_keyboard_device,EX_NULL))){
		ExIsHError(hr);
		ExKeyBoardShutDown();
		return hr;
	}
	if(FAILED(hr = m_keyboard_device->SetDataFormat(&c_dfDIKeyboard))){
		ExIsHError(hr);
		ExKeyBoardShutDown();
		return hr;
	}
	hr = ExSetKeyBoardCooperative(win,ExGetEngineFlag());
	*/
#endif
	return hr;
}

DECLSPEC ERESULT ELTAPIENTRY ExSetKeyBoardCooperative(ExWin win, Uint32 flag){
	ERESULT hr;
#if defined(EX_WINDOWS)
/*	if(!m_keyboard_device)return FALSE;// no device!
	if(!win)
		win = GetFocus();
	if(win){
		if(IsWindowVisible(win)){
			m_keyboard_device->Unacquire();
			if(FAILED(hr = m_keyboard_device->SetCooperativeLevel(win,
				DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))){
				ExIsHError(hr);
			}
		}
	}
	if(FAILED(hr = m_keyboard_device->Acquire())){
		ExIsHError(hr);
	}
	ExUpdateKeyboard();*/
#endif
	return hr;
}
Uint32 _index = 0;
Uint32 _index1 = 1;
DECLSPEC void ELTAPIENTRY ExUpdateKeyboard(void){
	ERESULT hr;
#if defined(EX_WINDOWS)
	//swap(index,index1);
	/*if(FAILED(hr = m_keyboard_device->GetDeviceState(sizeof(Boolean)* 256, (LPVOID)m_KeyBoard->KeyBoardState[_index]))){
		if(FAILED(hr = m_keyboard_device->Acquire())) // connect to the keyboard
			ExIsHError(hr);
		while(hr == DIERR_INPUTLOST || hr == DIERR_NOTACQUIRED){
			hr = m_keyboard_device->Acquire(); // try to connect to the keyboard again!
		}
	}*/
#elif defined(EX_LINUX)

#endif
	return;
}
DECLSPEC void ELTAPIENTRY ExKeyBoardShutDown(void){
	ERESULT hr;
#if defined(EX_WINDOWS)
	if(FAILED(hr = m_keyboard_device->Release()))
		ExIsHError(hr);
#elif defined(EX_LINUX)

#endif
	return;
}

DECLSPEC Boolean ELTAPIFASTENTRY ExAnyKey(void){
	/*for(Uint32 x = 0; x < CHAR_MAX; x++){
		if(m_KeyBoard->KeyBoardState[x] != 0)
			return TRUE;
		else
			continue;
	}*/
	return FALSE;
}
DECLSPEC Boolean ELTAPIFASTENTRY ExAnyKeyDown(void){
	/*for(Uint32 x = 0; x < 255; x++){
		if(m_KeyBoard->KeyBoardState[x] != 0)
			return TRUE;
		else
			continue;
	}*/
	return FALSE;
}
DECLSPEC Boolean ELTAPIFASTENTRY ExIsKey(const Uint32 keyCode){
#if defined(EX_WINDOWS)
	return GetAsyncKeyState(keyCode);
	ExUpdateKeyboard();
	return (KeyBoardState[_index][keyCode] & 0x80);
#elif defined(EX_LINUX)
	return 0;
#endif
}
DECLSPEC Boolean ELTAPIFASTENTRY ExIsKeyDown(const Uint32 keyCode){
#if defined(EX_WINDOWS)
	return GetAsyncKeyState(keyCode);
	return (KeyBoardState[_index][keyCode] & 0x80) != FALSE ? TRUE : FALSE;
#elif defined(EX_LINUX)
	return 0;
#endif
}
DECLSPEC Boolean ELTAPIFASTENTRY ExIsKeyUp(const Uint32 keyCode){
#if defined(EX_WINDOWS)
	return GetAsyncKeyState(keyCode);
	if(!((KeyBoardState[_index][keyCode]) & 0x80))
		if(((KeyBoardState[_index1][keyCode]) & 0x80))
			return TRUE;
#elif defined(EX_LINUX)
	return FALSE;
#endif

}
