#include"input/elt_mouse.h"
#ifdef EX_WINDOWS
#   include<dinput.h>
#elif defined(EX_LINUX)
#   include<linux/input.h>
#   include<X11/Xlib.h>
#   include<X11/cursorfont.h>
#   include"system/unix/unix_win.h"
#   include <linux/input.h>
#   include<X11/Xlib-xcb.h>
#elif defined(EX_ANDROID)
#   include<android/input.h>
#endif


ELTDECLSPEC Int32 ELTAPIENTRY ExCaptureMouse(ExBoolean enabled){
#ifdef EX_WINDOWS
	return (Int32)SetCapture(enabled ? GetFocus() : NULL);
#elif defined(EX_LINUX)
	return XGrabPointer(display, 0, False, 0, GrabModeSync, GrabModeSync, None, None, CurrentTime);
#endif
	return TRUE;
}

ELTDECLSPEC Int32 ELTAPIENTRY ExClipCursor(const ExRect* rect){
#ifdef EX_WINDOWS
	const RECT clip_rect = {rect->x,rect->y,rect->x + rect->width,rect->y + rect->height};
	ExIsWinError(ClipCursor(&clip_rect));
	return TRUE;
#elif defined(EX_LINUX)
	return XGrabPointer(display, 0, False, 0, GrabModeSync, GrabModeSync, None, None, CurrentTime);
	return TRUE;
#endif
}

ELTDECLSPEC ExCursor ELTAPIENTRY ExCreateCursor(const Uint8* data, const Uint8* mask, Int32 width,Int32 height, Int32 hot_x, Int32 hot_y){
#ifdef EX_WINDOWS
	ExCursor cursor;
	//ExIsWinError(!(cursor = CreateCursor(GetModuleHandle(NULL), hot_x, hot_y, width, height, pair, mask)));
	return cursor;
#elif defined(EX_LINUX)
    return XCreatePixmap(display, 0, width,height,8);
#endif
}


ELTDECLSPEC ExCursor ELTAPIENTRY ExCreateSystemCursor(Enum system_id){
	ExChar* arrow;
#ifdef EX_WINDOWS
	switch(system_id){
	case EXC_ARROW: arrow = IDC_ARROW;
	case EXC_IBEAM: arrow = IDC_IBEAM;
	case EXC_WAIT: arrow = IDC_WAIT;
	case EXC_CROSS: arrow = IDC_CROSS;
	case EXC_UPARROW: arrow = IDC_UPARROW;
	case EXC_SIZE: arrow = IDC_SIZE;
	case EXC_ICON: arrow = IDC_ARROW;
	case EXC_SIZENWSE: arrow = IDC_ARROW;
	case EXC_SIZENESW: arrow = IDC_ARROW;
	case EXC_SIZEWE: arrow = IDC_ARROW;
	case EXC_SIZENS: arrow = IDC_ARROW;
	case EXC_SIZEALL: arrow = IDC_ARROW;
	case EXC_NO: arrow = IDC_ARROW;
	//case EXC_HAND: arrow = IDC_ARROW;
	case EXC_APPSTART: arrow = IDC_ARROW;
	//case EXC_HELP: arrow = IDC_ARROW;
	}
	return LoadCursor(GetModuleHandle(NULL), arrow);
#elif defined(EX_LINUX)
    switch(system_id){
        case EXC_ARROW:arrow = XC_arrow;break;
        case EXC_WAIT: arrow = XC_watch;break;
        default:arrow= XC_arrow;
    }
    return XCreateFontCursor(display,arrow);

#endif
}

ELTDECLSPEC ExBoolean ELTAPIENTRY ExFreeCursor(ExCursor cursor){
	ExBoolean destroyed;
#ifdef EX_WINDOWS
	ExIsWinError(!(destroyed = (ExBoolean)DestroyCursor(cursor)));
#elif defined(EX_LINUX)
    destroyed = XFreeCursor(display, cursor);
#endif
	return destroyed;
}


ELTDECLSPEC ExBoolean ELTAPIENTRY ExSetCursor(ExCursor cursor){
#if defined(EX_WINDOWS)
	return (SetCursor(cursor) == cursor);
#elif defined(EX_LINUX)
    //TODO solve window
    //if(!cursor)
    //   return XUndefinedCursor(display, NULL);
    //else
        return XDefineCursor(display, NULL, cursor);
#endif
}

ELTDECLSPEC Uint32 ELTAPIENTRY ExGetGlobalMouseState(Int32* x, Int32* y){
#if defined(EX_WINDOWS)
	return GetCursorPos((LPPOINT)x);
#elif defined(EX_LINUX)
    int i,j,mask_return;
    Window* root;
	XQueryPointer(display,ExGetKeyboardFocus(),&root,&root,x,y,&i,&i,&mask_return);
	return mask_return;
#endif
}

ELTDECLSPEC Uint32 ELTAPIENTRY ExGetMouseState(Int32* x, Int32* y){
#if defined(EX_WINDOWS)
	return GetCursorPos((LPPOINT)x);    /*y is next to x in address memory.*/
#elif defined(EX_LINUX)
    int i,j,mask_return;
    Window* root;
	XQueryPointer(display,ExGetKeyboardFocus(),&root,&root,&i,&i,x,y,&mask_return);
	return mask_return;
#endif
}

ELTDECLSPEC ExBoolean ELTAPIENTRY ExShowCursor(ExBoolean enabled){
#ifdef EX_WINDOWS
	return (ExBoolean)ShowCursor(enabled);
#elif defined(EX_LINUX)
    if(!enabled)
        return XUndefineCursor(display, ExGetKeyboardFocus());
    else
        return XDefineCursor(display,0, None);

#endif
}

ELTDECLSPEC void ELTAPIENTRY ExWarpMouseGlobal(int x, int y){
#ifdef EX_WINDOWS

#elif defined(EX_LINUX)
    xcb_connection_t* connection = XGetXCBConnection(display);

    xcb_warp_pointer(connection, None, XDefaultRootWindow(display), 0,0,0,0, x,y);
    xcb_flush(connection);
#endif // EX_WINDOWS
}
