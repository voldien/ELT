#include"input/elt_mouse.h"
#include<windows.h>
#include<dinput.h>

 int  ExCaptureMouse(ExBoolean enabled){
	return (int)SetCapture(enabled ? GetFocus() : NULL);
}

 int  ExClipCursor(const ExRect* rect){
	const RECT clip_rect = {rect->x,rect->y,rect->x + rect->width,rect->y + rect->height};
	ExIsWinError(ClipCursor(&clip_rect));
	return EX_TRUE;
}

 ExCursor  ExCreateCursor(const unsigned char* data, const unsigned char* mask, int width,int height, int hot_x, int hot_y){
	ExCursor cursor;
	//ExIsWinError(!(cursor = CreateCursor(GetModuleHandle(NULL), hot_x, hot_y, width, height, pair, mask)));
	return cursor;
}


 ExCursor  ExCreateSystemCursor(unsigned int system_id){
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

 unsigned int  ExGetGlobalMouseState(int* x, int* y){
	return GetCursorPos((LPPOINT)x);
}

 unsigned int  ExGetMouseState(int* x, int* y){
	return GetCursorPos((LPPOINT)x);    /*y is next to x in address memory.*/

}

 ExBoolean  ExShowCursor(ExBoolean enabled){
	return (ExBoolean)ShowCursor(enabled);

}

 void  ExWarpMouseGlobal(int x, int y){

}
