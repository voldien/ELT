#include"input/elt_mouse.h"

#   include<linux/input.h>
#   include<X11/Xlib.h>
#   include<X11/cursorfont.h>
#   include"system/unix/unix_win.h"
#   include <linux/input.h>
#   include<X11/Xlib-xcb.h>


ELTDECLSPEC Int32 ELTAPIENTRY ExCaptureMouse(ExBoolean enabled){
	return XGrabPointer(display, 0, False, 0, GrabModeSync, GrabModeSync, None, None, CurrentTime);	return TRUE;
}

ELTDECLSPEC Int32 ELTAPIENTRY ExClipCursor(const ExRect* rect){
	return XGrabPointer(display, 0, False, 0, GrabModeSync, GrabModeSync, None, None, CurrentTime);
}

ELTDECLSPEC ExCursor ELTAPIENTRY ExCreateCursor(const Uint8* data, const Uint8* mask, Int32 width,Int32 height, Int32 hot_x, Int32 hot_y){
    return XCreatePixmap(display, 0, width, height, 8);
}

ELTDECLSPEC ExCursor ELTAPIENTRY ExCreateSystemCursor(Enum system_id){
	ExChar* arrow;
    switch(system_id){
        case EXC_ARROW:arrow = XC_arrow;break;
        case EXC_WAIT: arrow = XC_watch;break;
        default:arrow= XC_arrow;
    }
    return XCreateFontCursor(display,arrow);
}

ELTDECLSPEC ExBoolean ELTAPIENTRY ExFreeCursor(ExCursor cursor){
	ExBoolean destroyed;
    destroyed = XFreeCursor(display, cursor);
	return destroyed;
}


ELTDECLSPEC ExBoolean ELTAPIENTRY ExSetCursor(ExCursor cursor){
    //TODO solve window
    //if(!cursor)
    //   return XUndefinedCursor(display, NULL);
    //else
        return XDefineCursor(display, NULL, cursor);
}

ELTDECLSPEC Uint32 ELTAPIENTRY ExGetGlobalMouseState(Int32* x, Int32* y){
    int i,j,mask_return;
    Window* root;
	XQueryPointer(display,ExGetKeyboardFocus(),&root,&root,x,y,&i,&i,&mask_return);
	return mask_return;
}

ELTDECLSPEC Uint32 ELTAPIENTRY ExGetMouseState(Int32* x, Int32* y){
    int i,j,mask_return;
    Window* root;
	XQueryPointer(display,ExGetKeyboardFocus(),&root,&root,&i,&i,x,y,&mask_return);
	return mask_return;
}

ELTDECLSPEC ExBoolean ELTAPIENTRY ExShowCursor(ExBoolean enabled){
    if(!enabled)
        return XUndefineCursor(display, ExGetKeyboardFocus());
    else
        return XDefineCursor(display,0, None);

}

ELTDECLSPEC void ELTAPIENTRY ExWarpMouseGlobal(int x, int y){
    xcb_connection_t* connection = XGetXCBConnection(display);

    xcb_warp_pointer(connection, None, XDefaultRootWindow(display), 0,0,0,0, x,y);
    xcb_flush(connection);
}
