#include"input/elt_mouse.h"
#include<windows.h>
#include<dinput.h>

 Int32  ExCaptureMouse(ExBoolean enabled){
	return (Int32)SetCapture(enabled ? GetFocus() : NULL);
}

 Int32  ExClipCursor(const ExRect* rect){
	const RECT clip_rect = {rect->x,rect->y,rect->x + rect->width,rect->y + rect->height};
	ExIsWinError(ClipCursor(&clip_rect));
	return TRUE;
}

 ExCursor  ExCreateCursor(const Uint8* data, const Uint8* mask, Int32 width,Int32 height, Int32 hot_x, Int32 hot_y){
	ExCursor cursor;
	//ExIsWinError(!(cursor = CreateCursor(GetModuleHandle(NULL), hot_x, hot_y, width, height, pair, mask)));
	return cursor;
}


 ExCursor  ExCreateSystemCursor(Enum system_id){
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

 ExBoolean  ExFreeCursor(ExCursor cursor){
	ExBoolean destroyed;
	ExIsWinError(!(destroyed = (ExBoolean)DestroyCursor(cursor)));
	return destroyed;
}


 ExBoolean  ExSetCursor(ExCursor cursor){
	return (SetCursor(cursor) == cursor);
}

 Uint32  ExGetGlobalMouseState(Int32* x, Int32* y){
	return GetCursorPos((LPPOINT)x);
}

 Uint32  ExGetMouseState(Int32* x, Int32* y){
	return GetCursorPos((LPPOINT)x);    /*y is next to x in address memory.*/

}

 ExBoolean  ExShowCursor(ExBoolean enabled){
	return (ExBoolean)ShowCursor(enabled);

}

 void  ExWarpMouseGlobal(int x, int y){

}
