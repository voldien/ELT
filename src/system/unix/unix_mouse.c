#include"input/elt_mouse.h"
#   include"system/unix/unix_win.h"
#   include<linux/input.h>
#   include<X11/Xlib.h>
#   include<X11/cursorfont.h>
#	include <X11/Xcursor/Xcursor.h>

#   include <linux/input.h>
#   include<X11/Xlib-xcb.h>


Int32 ExCaptureMouse(ExBoolean enabled){
	return XGrabPointer(display, None, True, 0, GrabModeSync, GrabModeSync, None, ExGetCursor(), CurrentTime);
}

/*	TODO resolve*/
Int32 ExClipCursor(ExWin window){
	if(window)
		return XGrabPointer(display, window, True, 0, GrabModeAsync, GrabModeAsync, window, ExGetCursor(), CurrentTime);
	else{
		XUngrabPointer(display, CurrentTime);
		return;
		XGrabPointer(display, XDefaultRootWindow(display), False, 0, GrabModeAsync, GrabModeAsync, NULL, ExGetCursor(), CurrentTime);
		XAllowEvents(display, ReplayPointer, CurrentTime);
	}
}

ExCursor ExCreateCursor(const Uint8* data, const Uint8* mask, Int32 width,Int32 height, Int32 hot_x, Int32 hot_y){
    return XCreatePixmap(display, 0, width, height, 8);
}

ExCursor ExCreateSystemCursor(Enum system_id){
	unsigned int arrow;
    switch(system_id){
        case EXC_ARROW: arrow = XC_arrow;break;
        case EXC_WAIT: arrow = XC_watch;break;
        default:arrow= XC_X_cursor;
    }
    return XCreateFontCursor(display, arrow);
}

ExBoolean ExFreeCursor(ExCursor cursor){
	ExBoolean destroyed;
    destroyed = XFreeCursor(display, cursor);
	return destroyed;
}

ExBoolean ExSetCursor(ExWin window, ExCursor cursor){
	return XDefineCursor(display, window, cursor);
}

ExCursor ExGetCursor(void){
	return NULL;
}


Uint32 ExGetGlobalMouseState(Int32* x, Int32* y){
    int i,j,mask_return;
    Window* root;
	if(XQueryPointer(display, ExGetKeyboardFocus(), &root, &root, x, y, &i, &i, &mask_return))
		return mask_return;
	else
		return eExMouseNone;
}

Uint32 ExGetMouseState(Int32* x, Int32* y){
    int i,j,mask_return;
    Window* root;
	XQueryPointer(display,ExGetKeyboardFocus(), &root, &root, &i, &i, x, y, &mask_return);
	return mask_return;
}

ExBoolean ExShowCursor(ExBoolean enabled){
    if(!enabled)
        return XUndefineCursor(display, ExGetKeyboardFocus());
    else
        return XDefineCursor(display,0, None);
}

void ExWarpMouseGlobal(int x, int y){
    xcb_connection_t* connection = XGetXCBConnection(display);

    xcb_warp_pointer(connection, None, XDefaultRootWindow(display), 0,0,0,0, x,y);
    xcb_flush(connection);
}
