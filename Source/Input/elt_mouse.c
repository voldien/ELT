#include"elt_mouse.h"
#ifdef EX_WINDOWS
#   include<dinput.h>
    DIMOUSESTATE2 MouseState[2];
    IDirectInputDevice8* hMouseDevice = EX_NULL;
    //MouseHandler* m_MouseHandler = EX_NULL;
#elif defined(EX_LINUX)
#   include<linux/input.h>
#   include<X11/Xlib.h>
#   include<X11/cursorfont.h>
#   include"./../System/Unix/unix_win.h"
#endif


DECLSPEC Int32 ELTAPIENTRY ExCaptureMouse(ExBoolean enabled){
#ifdef EX_WINDOWS
	return (Int32)SetCapture(enabled ? GetFocus() : EX_NULL);
	#elif defined(EX_LINUX)
	return XGrabPointer(display, 0,False,0,GrabModeSync, GrabModeSync, None, None, CurrentTime);
#endif
	return TRUE;
}
DECLSPEC Int32 ELTAPIENTRY ExClipCursor(const struct exrect* rect){
#ifdef EX_WINDOWS
	const RECT clip_rect = {rect->x,rect->y,rect->x + rect->width,rect->y + rect->height};
	ExIsWinError(ClipCursor(&clip_rect));
	return TRUE;
#elif defined(EX_LINUX)
	XQueryPointer(display,ExGetKeyboardFocus(),0,0,0,0,0,0,0);
	return TRUE;
#endif
}

DECLSPEC ExCursor ELTAPIENTRY ExCreateCursor(const Uint8* data, const Uint8* mask, Int32 width,Int32 height, Int32 hot_x, Int32 hot_y){
#ifdef EX_WINDOWS
	ExCursor cursor;
	ExIsWinError(!(cursor = CreateCursor(GetModuleHandle(EX_NULL),hot_x, hot_y,width, height, data, mask)));
	return cursor;
#elif defined(EX_LINUX)
    return XCreatePixmap(display, 0, width,height,8);
#endif
}
/**
	Create System Cursor
*/
DECLSPEC ExCursor ELTAPIENTRY ExCreateSystemCursor(Enum system_id){
	ExChar* data;
#ifdef EX_WINDOWS
	switch(system_id){
	case EXC_ARROW: data = IDC_ARROW;
	case EXC_IBEAM: data = IDC_IBEAM;
	case EXC_WAIT: data = IDC_WAIT;
	case EXC_CROSS: data = IDC_CROSS;
	case EXC_UPARROW: data = IDC_UPARROW;
	case EXC_SIZE: data = IDC_SIZE;
	case EXC_ICON: data = IDC_ARROW;
	case EXC_SIZENWSE: data = IDC_ARROW;
	case EXC_SIZENESW: data = IDC_ARROW;
	case EXC_SIZEWE: data = IDC_ARROW;
	case EXC_SIZENS: data = IDC_ARROW;
	case EXC_SIZEALL: data = IDC_ARROW;
	case EXC_NO: data = IDC_ARROW;
	case EXC_HAND: data = IDC_ARROW;
	case EXC_APPSTART: data = IDC_ARROW;
	case EXC_HELP: data = IDC_ARROW;
	}
	return LoadCursor(GetModuleHandle(EX_NULL), data);
#elif defined(EX_LINUX)
    switch(system_id){
        case EXC_ARROW:data = XC_arrow;break;
        case EXC_IBEAM:break;
    }
    return XCreateFontCursor(display,data);

#endif
}

DECLSPEC ExBoolean ELTAPIENTRY ExFreeCursor(ExCursor cursor){
	ExBoolean destroyed;
#ifdef EX_WINDOWS
	ExIsWinError(!(destroyed = (ExBoolean)DestroyCursor(cursor)));
#elif defined(EX_LINUX)
    destroyed = XFreeCursor(display,cursor);
#endif
	return destroyed;
}

DECLSPEC ExBoolean ELTAPIENTRY ExSetCursor(ExCursor cursor){
#if defined(EX_WINDOWS)
	return (SetCursor(cursor) == cursor);
#elif defined(EX_LINUX)
    //TODO solve window
    //if(!cursor)
    //   return XUndefinedCursor(display, NULL);
    //else
        return XDefineCursor(display,NULL, cursor);
#endif
}

DECLSPEC Uint32 ELTAPIENTRY ExGetGlobalMouseState(Int32* x, Int32* y){
#if defined(EX_WINDOWS)
	return GetCursorPos((LPPOINT)x);
#elif defined(EX_LINUX)
    int i,j,mask_return;
    Window* root;
	XQueryPointer(display,ExGetKeyboardFocus(),&root,&root,x,y,&i,&i,&mask_return);
	return mask_return;
#endif
}

DECLSPEC Uint32 ELTAPIENTRY ExGetMouseState(Int32* x, Int32* y){
#if defined(EX_WINDOWS)
	return GetCursorPos((LPPOINT)x);
#elif defined(EX_LINUX)
    int i,j,mask_return;
    Window* root;
	XQueryPointer(display,ExGetKeyboardFocus(),&root,&root,&i,&i,x,y,&mask_return);
	return mask_return;
#endif
}

DECLSPEC ExBoolean ELTAPIENTRY ExShowCursor(ExBoolean enabled){
#ifdef EX_WINDOWS
	return (ExBoolean)ShowCursor(enabled);
#elif defined(EX_LINUX)
    if(!enabled)
        return XUndefineCursor(display, ExGetKeyboardFocus());
    else
        return XDefineCursor(display,0, None);

#endif
}

DECLSPEC void ELTAPIENTRY ExWarpMouseGlobal(int x, int y){
#ifdef EX_WINDOWS
#elif defined(EX_LINUX)
//    return XWrapPointer(display, 0,0,x,y,0,0,0,0);
return 0;
#endif // EX_WINDOWS
}


DECLSPEC ERESULT ELTAPIENTRY ExInitMouse(ExWin hWnd){
	ERESULT hr;
#if defined(EX_WINDOWS)
	/*if(m_MouseHandler){
		m_MouseHandler = (MouseHandler*)ExMalloc(sizeof(MouseHandler));

		memset(&MouseState[0],0,sizeof(DIMOUSESTATE2));
		memset(&MouseState[1],0,sizeof(DIMOUSESTATE2));
	}
	// Create Device
	if(FAILED(hr = g_pDI->CreateDevice(GUID_SysMouse,&hMouseDevice,EX_NULL))){
		ExIsHError(hr);
		ExMouseShutDown();
		return hr;
	}
	// Data Format
	if(FAILED(hr = hMouseDevice->SetDataFormat(&c_dfDIMouse))){
		ExIsHError(hr);
		ExMouseShutDown();
		return hr;
	}
	// Cooperative Level
	hr = ExSetMouseCooperative(hWnd, ExGetEngineFlag());*/
#elif defined(EX_LINUX)
#endif
	return hr;
}

DECLSPEC ERESULT ELTAPIENTRY ExSetMouseCooperative(ExWin hWnd, Uint64 flag){
	ERESULT hr;
#if defined(EX_WINDOWS)
	if(!hMouseDevice || !hWnd)return FALSE;



	DIPROPDWORD         dipdw;
	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = DIPROPAXISMODE_REL; //or ABS here

	hr = hMouseDevice->SetProperty(DIPROP_AXISMODE, &dipdw.diph);
	if(FAILED(hr = hMouseDevice->SetCooperativeLevel(hWnd,
		DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))){
		ExIsHError(hr);
		return hr;
	}
	if(FAILED(hr = hMouseDevice->Acquire())){
		if(FAILED(hr = hMouseDevice->Unacquire()))
			wExDevPrintf(TEXT("Failed to Acquire DirectInput Mouse : %s\n"),ExGetHResultErrorMessage(hr));
		else
			if(FAILED(hr = hMouseDevice->Acquire()))
				wExDevPrintf(TEXT("Failed to Acquire DirectInput Mouse : %s\n"),ExGetHResultErrorMessage(hr));
		return hr;
	}
	DIDEVCAPS  MouseCapabilities;
	MouseCapabilities.dwSize = sizeof(MouseCapabilities);
	hMouseDevice->GetCapabilities(&MouseCapabilities);
	if(MouseCapabilities.dwFlags & DIDC_ATTACHED){
		int x = 0;
	}
	hr =  hMouseDevice->Poll();
	ExUpdateMouse();
#endif
	return hr;
}

Uint32 mindex = 0;
Uint32 mindex1 = 1;
DECLSPEC void ELTAPIENTRY ExUpdateMouse(void){
	ERESULT hr;
#if defined(EX_WINDOWS)
//	swap(mindex,mindex1);
	/*hr = hMouseDevice->Poll();
	if(FAILED(hr = hMouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&m_MouseHandler->MouseState[mindex]))){
		hr = hMouseDevice->Acquire();
		if(hr == DIERR_INPUTLOST || hr == DIERR_NOTACQUIRED)
			hr = hMouseDevice->Acquire();
	}*/
#elif defined(EX_LINUX)
#endif
	return;
}
DECLSPEC void ELTAPIENTRY ExDisconnectMouse(void){
#ifdef EX_WINDOWS
	//ExIsHError(hMouseDevice->Unacquire());
#endif
	return;
}

DECLSPEC const Int ELTAPIFASTENTRY ExGetMouseDeltaX(void){
#ifdef EX_WINDOWS
	return (MouseState[0].lX -MouseState[1].lX);
#endif
	return 0;
}
DECLSPEC const Int ELTAPIFASTENTRY ExGetMouseDeltaY(void){
#ifdef EX_WINDOWS
	return (MouseState[0].lY -MouseState[1].lY);
#endif
	return 0;
}

DECLSPEC const Int ELTAPIFASTENTRY ExGetMouseXCoord(void){
#ifdef EX_WINDOWS
	return (MouseState[0].lX);
#endif
	return 0;
}
DECLSPEC const Int ELTAPIFASTENTRY  ExGetMouseYCoord(void){
#ifdef EX_WINDOWS
	return (MouseState[0].lY);
#endif
	return 0;
}

DECLSPEC const ExBoolean ELTAPIFASTENTRY ExGetButton(Uint32 keyCode){
#ifdef EX_WINDOWS
	return (MouseState[0].rgbButtons[keyCode] & 0x80) ? TRUE : FALSE;
#endif
	return 0;
}
DECLSPEC const ExBoolean ELTAPIFASTENTRY ExGetButtonDown(Uint32 keyCode){
#ifdef EX_WINDOWS
	return (MouseState[0].rgbButtons[keyCode] & 0x80) ? TRUE : FALSE;
#endif
	return 0;
}
DECLSPEC const ExBoolean ELTAPIFASTENTRY ExGetButtonUp(Uint32 keyCode){
#ifdef EX_WINDOWS
	return !(MouseState[0].rgbButtons[keyCode]  & 0x80) &&
		(MouseState[1].rgbButtons[keyCode]  & 0x80) != FALSE ? TRUE : FALSE;
#endif
	return 0;
}

DECLSPEC const Float ELTAPIFASTENTRY ExGetMouseMagnitude(void){
	return (Float)sqrtf(ExGetMouseDeltaX() * ExGetMouseDeltaX() + ExGetMouseDeltaY() * ExGetMouseDeltaY());
}
