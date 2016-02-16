#include"input/elt_mouse.h"
#include<windows.h>
#include<dinput.h>

ELTDECLSPEC Int32 ELTAPIENTRY ExCaptureMouse(ExBoolean enabled){
	return (Int32)SetCapture(enabled ? GetFocus() : NULL);
}

ELTDECLSPEC Int32 ELTAPIENTRY ExClipCursor(const ExRect* rect){
	const RECT clip_rect = {rect->x,rect->y,rect->x + rect->width,rect->y + rect->height};
	ExIsWinError(ClipCursor(&clip_rect));
	return TRUE;
}

ELTDECLSPEC ExCursor ELTAPIENTRY ExCreateCursor(const Uint8* data, const Uint8* mask, Int32 width,Int32 height, Int32 hot_x, Int32 hot_y){
	ExCursor cursor;
	//ExIsWinError(!(cursor = CreateCursor(GetModuleHandle(NULL), hot_x, hot_y, width, height, pair, mask)));
	return cursor;
}


ELTDECLSPEC ExCursor ELTAPIENTRY ExCreateSystemCursor(Enum system_id){
	ExChar* arrow;
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
}

ELTDECLSPEC ExBoolean ELTAPIENTRY ExFreeCursor(ExCursor cursor){
	ExBoolean destroyed;
	ExIsWinError(!(destroyed = (ExBoolean)DestroyCursor(cursor)));
	return destroyed;
}


ELTDECLSPEC ExBoolean ELTAPIENTRY ExSetCursor(ExCursor cursor){
	return (SetCursor(cursor) == cursor);
}

ELTDECLSPEC Uint32 ELTAPIENTRY ExGetGlobalMouseState(Int32* x, Int32* y){
	return GetCursorPos((LPPOINT)x);
}

ELTDECLSPEC Uint32 ELTAPIENTRY ExGetMouseState(Int32* x, Int32* y){
	return GetCursorPos((LPPOINT)x);    /*y is next to x in address memory.*/

}

ELTDECLSPEC ExBoolean ELTAPIENTRY ExShowCursor(ExBoolean enabled){
	return (ExBoolean)ShowCursor(enabled);

}

ELTDECLSPEC void ELTAPIENTRY ExWarpMouseGlobal(int x, int y){

}
