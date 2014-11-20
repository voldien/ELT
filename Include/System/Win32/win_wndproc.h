/*
===========================================================================
Copyright (C) 2014 BroodCity Software, Inc. Voldemor2009@hotmail.com

*/
#ifndef WIN_WNDPROC_H
#define WIN_WNDPROC_H

#include"win_win32.h"
#include"win_GL.h"
#ifdef EX_SCREENSAVER
	#include<ScrnSave.h>
	#pragma comment(lib,"Scrnsave.lib")
#endif
/*
	## user defied window message
*/
#define WM_USER_SIZE (WM_USER + 1)

#ifdef EX_CPP
extern "C"{
#endif

extern DECLSPEC Void ELTAPIENTRY WIN_DisableAltTab(Void);
extern DECLSPEC Void ELTAPIENTRY WIN_EnableAltTab(Void);

extern DECLSPEC Boolean ELTAPIENTRY WIN_EnableDeviceNotification(ExWin hWnd);
/*
	//	main window procedure
	//	Remark : 
*/
extern DECLSPEC LRESULT WINAPI MainWndProc(ExWin hWnd,UINT uMsg, WPARAM wParam, LPARAM lParam);
/*
	// native windows. designed for user interface handling  
*/
extern DECLSPEC LRESULT WINAPI WndProcNative(ExWin hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

/*	On Window Context menu	*/
extern DECLSPEC BOOL WINAPI ExOnContextMenu(ExWin hWnd,Int32 x, Int32 y);
/*	On Window Context menu	*/
extern DECLSPEC BOOL WINAPI ExOnContextMenu2(ExWin hWnd,HMENU hmenu,Int32 x, Int32 y);
/*	Display Window Context	*/
extern DECLSPEC BOOL WINAPI ExDisplayContextMenu(ExWin hWnd, POINT& pt);

extern DECLSPEC HANDLE ELTAPIENTRY ExHookWndProc(Int32  idHook, HOOKPROC lpfn);
/*
	STATIC LRESULT CALLBACK DefViewWindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
	STATIC LRESULT CALLBACK ListViewWindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
*/

#ifdef EX_CPP
}
#endif



#endif