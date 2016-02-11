/*
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
#ifndef _WIN32_WINDOW_H_
#define _WIN32_WINDOW_H_ 1
#include"./../../elt_def.h"
#include<windows.h>
#include"./../../EngineAssembly.h"
#include"win_wndproc.h"
#include"win_directX.h"
#include"wnd_common.h"

typedef void(ELTAPISTDENTRY *CallBackSTD)(void);
typedef void(ELTAPIENTRY *MotionCallBack)(int x, int y);
typedef void(ELTAPIENTRY *KeyBoardCallBack)(unsigned int key);
typedef void(ELTAPIENTRY *ReShapeCallBack)(unsigned int width, unsigned int height);

typedef void(ELTAPIENTRY *SystemKeyDown)(WPARAM wParam, LPARAM lParam);
typedef int(ELTAPIENTRY *MouseButton)(Enum action, Enum buttonID);

#ifdef  __cplusplus	/* C++ Environment */
extern "C"{
#endif

/*
 *	windows classes
 */
#define EX_OPENGL_WINDOW_CLASS EX_TEXT("OpenGL_Window")
#define EX_NATIVE_WINDOW_CLASS EX_TEXT("Native_Window")
#define EX_DIRECTX_WINDOW_CLASS EX_TEXT("DirectX_Window")

typedef struct desktop_window{	// Use of When Application InterFace is Hooked up With Desktop Handles.

	/*
	 *
	 */
	HWND hookDesktop;
	HHOOK hHookCallWndProc;
	HHOOK hHookCallGetMessage;
	HHOOK hHookCallWndProcRet;
	WNDPROC originalDefWindowProc;// pointer to origional
	WNDPROC originalListViewProc;// pointer to origional
}DESKTOP, *LDESKTOP,DesktopWindow;

typedef struct event_handler{
	SystemKeyDown systemkeyevent;
	KeyBoardCallBack keyboardevent;
	ReShapeCallBack reshapeEvent;
	MouseButton mousebutton;
	MotionCallBack motionevent;
	HMENU contexthmenu;
}EventHandler;

typedef struct ex_nativ_window_handler{
	/*
	 *
	 */
	Enum windowFlag;

	/*
	 *
	 */
	EventHandler events;
}ExNativWindowHandler;

typedef struct ex_gl_window_handler{
	Enum windowFlag;
	EventHandler events;
}ExGLWindowHandler;

typedef struct WindowEvent{
	MSG msg;
}Wevent, *Hevent;

extern ExCallBack ExOnFocus;
extern ExCallBack ExOnUnFocus;


/*
 *	UnRegister all Windows
 */
extern ELTDECLSPEC void ELTAPIENTRY ExUnRegisterClasses(void);

/*
 *	Create Window dedicated for DirectX
 *	@Return
 */
extern ELTDECLSPEC ExWin ELTAPIENTRY ExCreateDirectXWindow(int x, int y, int width, int height);

/*
 *
 */
extern ELTDECLSPEC ExWin ELTAPIENTRY ExCreateOpenGLWindow(int x, int y, int width, int height);

/*
 *	@Return
 */
extern ELTDECLSPEC ExWin ELTAPIENTRY ExCreateNativeWindow(int x, int y, int width, int height);

/*
 *	@Return
*/
extern ELTDECLSPEC ExWin ELTAPIENTRY ExCreateDesktopWindow(int x, int y, int width, int height);

/*
 *	Create MID Window
 *	@Return
*/
extern ELTDECLSPEC ExWin ELTAPIENTRY ExCreateMIDWindow(int x, int y, int width , int height);


/*
 *	Set Window Processor [ HWND hwnd, WNDPROC procPointer]
 */
extern ELTDECLSPEC DWORD ELTAPIENTRY ExSetWindowProc(ExWin hwnd, WNDPROC procPointer);


/*
 *	Get Window Processsor [HWND hwnd]
 */
extern ELTDECLSPEC WNDPROC ELTAPIENTRY ExGetWindowProc(ExWin hwnd);

/*
 *	Window Style
 */
extern ELTDECLSPEC void ELTAPIENTRY ExSetWindowStyle(ExWin hwnd, Long lstyle);
/*
 *
 */
extern ELTDECLSPEC void ELTAPIENTRY ExSetAddiWindowStyle(ExWin hWnd, Long lstyle);
/*
 *
 */
extern ELTDECLSPEC Long ELTAPIENTRY ExGetWindowStyle(ExWin hwnd);
/*
 *
 */
extern ELTDECLSPEC void ELTAPIENTRY ExSetWindowStyleEx(ExWin hwnd, Long ExStyle);
/*
 *
 */
extern ELTDECLSPEC Long ELTAPIENTRY ExGetWindowStyleEx(ExWin hwnd);


/*
 *	Create Sub  Window Based the prevously created one.
 */
extern ELTDECLSPEC ExWin ELTAPIENTRY ExCreateSubWindow(Int32 x,Int32 y, Int32 width, Int32 height);


/*
 *	Update windows for all given windows on the process.
 *	\hwnd if update a particular window.
 *	@Return
*/
extern ELTDECLSPEC int ELTAPIENTRY ExGetWindowMessage(ExWin hwnd);

/*
 *	Update windows for all given windows on the process.
 *	\hwnd
 *	@Return
 */
extern ELTDECLSPEC int ELTAPIENTRY ExGetWindowPeekMessage(ExWin hwnd);

#ifdef  __cplusplus	/* C++ Environment */
}
#endif


#include"win_controls.h"
#endif
