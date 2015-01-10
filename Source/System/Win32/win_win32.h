/*
===========================================================================
Copyright (C) 2014 BroodCity Software, Inc. Voldemor2009@hotmail.com

*/
#ifndef WIN32_WINDOW_H
#define WIN32_WINDOW_H
#include"./../../ExPreProcessor.h"
#ifdef EX_WINDOWS
#include<Windows.h>
#include"./../../EngineAssembly.h"
#include"win_wndproc.h"
#include"win_directX.h"
#include"wnd_common.h"
#include"wnd_snd.h"


typedef void(ELTAPIENTRY *CallBack)(void);
typedef void(ELTAPISTDENTRY *CallBackSTD)(void);
typedef void(ELTAPIENTRY *MotionCallBack)(int x, int y);
typedef void(ELTAPIENTRY *KeyBoardCallBack)(unsigned int key);
typedef void(ELTAPIENTRY *ReShapeCallBack)(unsigned int width, unsigned int height);

typedef void(ELTAPIENTRY *SystemKeyDown)(WPARAM wParam, LPARAM lParam);
typedef int(ELTAPIENTRY *MouseButton)(Enum action, Enum buttonID);

#ifdef __cplusplus // C++ environment
C_EXTERN{
#endif
/*
	// windows classes
*/
#define EX_OPENGL_WINDOW_CLASS EX_TEXT("OpenGL_Window")
#define EX_NATIVE_WINDOW_CLASS EX_TEXT("Native_Window")
#define EX_DIRECTX_WINDOW_CLASS EX_TEXT("DirectX_Window")

typedef struct DesktopWindow{	// Use of When Application InterFace is Hooked up With Desktop Handles.
	HWND hookDesktop;
	HHOOK hHookCallWndProc;
	HHOOK hHookCallGetMessage;
	HHOOK hHookCallWndProcRet;
	WNDPROC originalDefWindowProc;// pointer to origional
	WNDPROC originalListViewProc;// pointer to origional
}DESKTOP, *LDESKTOP;


typedef struct ExNativWindowHandler{
	struct EventHandler{
		SystemKeyDown systemkeyevent;
		KeyBoardCallBack keyboardevent;
		ReShapeCallBack reshapeEvent;
		MouseButton mousebutton;
		MotionCallBack motionevent;
		HMENU contexthmenu;
	};
	Enum windowFlag;
	EX_C_STRUCT ExNativWindowHandler::EventHandler events;

}ExNativWindow;
typedef struct ExGLWindowHandler{
	struct EventHandler{
		SystemKeyDown systemkeyevent;
		KeyBoardCallBack keyboardevent;
		ReShapeCallBack reshapeEvent;
		MouseButton mousebutton;
		MotionCallBack motionevent;
		HMENU contexthmenu;
	};
	Enum windowFlag;
	EX_C_STRUCT EventHandler events;
}HExGLWindow;

typedef struct WindowEvent{
	MSG msg;
}Wevent, *Hevent;
extern CallBack ExOnFocus;
extern CallBack ExOnUnFocus;

/* UnRegister all Windows*/
extern DECLSPEC void ELTAPIENTRY ExUnRegisterClasses(void);

/* Create Window dedicated for DirectX*/
extern DECLSPEC ExWin ELTAPIENTRY ExCreateDirectXWindow(Int32 x, Int32 y, Int32 width, Int32 height);
/**/
extern DECLSPEC ExWin ELTAPIENTRY ExCreateOpenGLWindow(Int32 x, Int32 y, Int32 width, Int32 height);
/**/
extern DECLSPEC ExWin ELTAPIENTRY ExCreateNativeWindow(Int32 x, Int32 y, Int32 width, Int32 height);

extern DECLSPEC ExWin ELTAPIENTRY ExCreateDesktopWindow(Int32 x, Int32 y, Int32 width, Int32 height);

/*	Create MID Window*/
extern DECLSPEC ExWin ELTAPIENTRY ExCreateMIDWindow(Int32 x, Int32 y, Int32 width , Int32 height);


/* ReCreate the Window For OpenGL purpose */
extern DECLSPEC ExWin ELTAPIENTRY ExReConstructWindow(ExWin hWnd);

//----------------------------------------------------------------
extern DECLSPEC void ELTAPIENTRY ExOpenWindow(ExWin hWnd);
//----------------------------------------------------------------
extern DECLSPEC void ELTAPIENTRY ExCloseWindow(ExWin hWnd);


/* Set Window Processor [ HWND hwnd, WNDPROC procPointer] */
extern DECLSPEC DWORD ELTAPIENTRY ExSetWindowProc(ExWin hwnd, WNDPROC procPointer);
/* Get Window Processsor [HWND hwnd] */
extern DECLSPEC WNDPROC ELTAPIENTRY ExGetWindowProc(_IN_ ExWin hwnd);

/*
	// Window Style
*/
extern DECLSPEC void ELTAPIENTRY ExSetWindowStyle(ExWin hwnd, Long lstyle);

extern DECLSPEC void ELTAPIENTRY ExSetAddiWindowStyle(ExWin hWnd, Long lstyle);

extern DECLSPEC Long ELTAPIENTRY ExGetWindowStyle(ExWin hwnd);

extern DECLSPEC void ELTAPIENTRY ExSetWindowStyleEx(ExWin hwnd, Long ExStyle);
extern DECLSPEC Long ELTAPIENTRY ExGetWindowStyleEx(ExWin hwnd);


/* Create Sub  Window Basedo the prevously created one. */
extern DECLSPEC ExWin ELTAPIENTRY ExCreateSubWindow(Int32 x,Int32 y, Int32 width, Int32 height);

//* behavior of window
extern DECLSPEC Boolean ELTAPIENTRY ExGetWindowMessage(ExWin hwnd);
extern DECLSPEC Boolean ELTAPIENTRY ExGetWindowPeekMessage(ExWin hwnd);

/**/
extern DECLSPEC void ELTAPIENTRY ExRunWinMessageLoop(void);
/**/
extern DECLSPEC void ELTAPIENTRY ExRunWinPeekMessage(void);

#ifdef __cplusplus // C++ environment
}
#endif


#include"win_controls.h"
#include"wnd_filedialog.h"
#include"wnd_input.h"
#include"win_GL.h"
#endif
#endif
