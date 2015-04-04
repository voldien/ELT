/**
    ELT (Engine Library Toolkit) is a multi platform engine toolkit
    Copyright (C) 2014  Valdemar Lindberg

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/
#ifndef _ELT_WIN_H_
#define _ELT_WIN_H_ 1
#include"./../EngineAssembly.h"
#include"elt_event.h"
#include"elt_cl.h"

#ifdef  __cplusplus	// C++ Environment
extern "C"{
#endif

#ifdef EX_WINDOWS
	#define ExMessageBox MessageBox
#else
	#define ExMessageBox(a,b,c,d) gtk_message_dialog_new()
#endif

#define EX_WIN_SCREENSAVER_ENABLE   0x200000
#define EX_WIN_SCREENSAVER_DISABLE  0x400000

struct exsize{unsigned int width,height;};
struct exrect{int x,y,width,height;};

/**
	Create Window
	\x : coordinate 
	\y : coordinate 
	\width : width of the window  
	\height : height of the window
	\flag : window type 
	@return window handle
*/
extern DECLSPEC ExWin ELTAPIENTRY ExCreateWindow(Int32 x, Int32 y, Int32 width, Int32 height,Enum flag);
/**
	Show window
	\window window handle
*/
extern DECLSPEC void ELTAPIENTRY ExShowWindow(ExWin window);
/**
	Hide Window
	\window Window handle
*/
extern DECLSPEC void ELTAPIENTRY ExHideWindow(ExWin window);
/*

*/
extern DECLSPEC void ELTAPIENTRY ExCloseWindow(ExWin window);

/**
	Set window mode
*/
extern DECLSPEC void ELTAPIENTRY ExSetWindowMode(ExWin window, Enum mode);



/**
    Destroy Window
*/
extern DECLSPEC ExBoolean ELTAPIENTRY ExDestroyWindow(ExWin window);

/**
	Set Window Title
	\window 
	\title window title
*/
extern DECLSPEC void ELTAPIENTRY ExSetWindowTitle(ExWin window,const ExChar* title);
/**
	Get Windows Title
	\window
	\title
*/
extern DECLSPEC void ELTAPIENTRY ExGetWindowTitle(ExWin window, ExChar* title);

/**
	Set Windows Position
	\window
	\x
	\y
*/
extern DECLSPEC void ELTAPIENTRY ExSetWindowPos(ExWin window,Int32 x,Int32 y);

/**
	Set Windows Position
*/
extern DECLSPEC void ELTAPIENTRY ExSetWindowPosv(ExWin window,const Int32* position);
/**
 */
extern DECLSPEC void ELTAPIENTRY ExGetWindowPosv(ExWin window, Int32* position);
/**
	Set Window size
*/
extern DECLSPEC void ELTAPIENTRY ExSetWindowSize(ExWin window,Int32 width, Int32 height);
/**
	Set Window Size
*/
extern DECLSPEC void ELTAPIENTRY ExSetWindowSizev(ExWin window,const struct exsize* size);
/*
    Get Window Size
*/
extern DECLSPEC void ELTAPIENTRY ExGetWindowSizev(ExWin window, struct exsize* size);
/*
	// Set Window Rect
*/
extern DECLSPEC void ELTAPIENTRY ExSetWindowRect(ExWin window, const struct exrect* rect);
/*
	// Get Window Rect
*/
extern DECLSPEC void ELTAPIENTRY ExGetWindowRect(ExWin window, struct exrect* rect);



/**
    Get Window mode
*/
extern DECLSPEC Uint32 ELTAPIENTRY ExGetWindowFlag(ExWin window);
/**
    Set Window Flag
*/
extern DECLSPEC void ELTAPIENTRY ExSetWindowFlag(ExWin window, Enum flag);

/**
 *	Assign Icon Handle onto window
 */
extern DECLSPEC Int32 ELTAPIENTRY ExSetWindowIcon(ExWin window, HANDLE hIcon);
/**
 *	Get Window Icon Handle
 */
extern DECLSPEC Int32 ELTAPIENTRY ExGetWindowIcon(ExWin window);

/**

*/
extern DECLSPEC Int32 ELTAPIENTRY ExIsScreenSaverEnable(void);

//extern DECLSPEC Int32 ELTAPIENTRY ExVideoQuit(void);

/*
// Poll Window Event information
// *[HWND] which window to poll event information.
//	Remark: message feed will only be apply to given HWND paramter
//	if HWND is null all window create on this application will be update
//	read more at MSDN for more specific information regarding PeekMessage with null HWND.
// *[ExWindowEvent] pointer to event struct. all event will be stored in it.
//	#return if PeekMessage was success.
// PeekMessage : http://msdn.microsoft.com/en-us/library/windows/desktop/ms644943(v=vs.85).aspx
*/
extern DECLSPEC ExBoolean ELTAPIENTRY ExPollWindowEvent(ExWin window, ExWindowEvent* event);




#ifdef __cplusplus	//	C++ Env
}
#endif
#endif
