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
#ifndef _WIN_WNDPROC_H_
#define _WIN_WNDPROC_H_ 1
#include"win_win32.h"

/*
 *	## user defied window message
 */
#define WM_USER_SIZE (WM_USER + 1)

#ifdef  __cplusplus	/* C++ Environment */
extern "C"{
#endif

/*
 *
 */
extern DECLSPEC void ELTAPIENTRY ExDisableAltTab(void);
/*
 *
 */
extern DECLSPEC void ELTAPIENTRY ExEnableAltTab(void);
/*
 *
 */
extern DECLSPEC ExBoolean ELTAPIENTRY ExEnableDeviceNotification(ExWin hWnd);
/*
 *	//	main window procedure
 *	//	Remark :
 *	\hWnd
 *	\uMsg
 *	\wParam
 *	\lParam
 *	@return
*/
extern DECLSPEC ERESULT ELTAPISTDENTRY ExMainWndProc(ExWin hWnd, Uint uMsg, WPARAM wParam, LPARAM lParam);

/*
 *	native windows. designed for user interface handling
 *
 */
extern DECLSPEC ERESULT ELTAPISTDENTRY ExWndProcNative(ExWin hWnd, Uint uMsg, WPARAM wParam, LPARAM lParam);
/**
	On Window Context menu
*/
extern DECLSPEC BOOL ELTAPISTDENTRY ExOnContextMenu(ExWin hWnd,Int32 x, Int32 y);
/*	On Window Context menu	*/
extern DECLSPEC BOOL ELTAPISTDENTRY ExOnContextMenu2(ExWin hWnd, HMENU hmenu, Int32 x, Int32 y);
/*	Display Window Context	*/
extern DECLSPEC BOOL ELTAPISTDENTRY ExDisplayContextMenu(ExWin hWnd, POINT* pt);

/*
 *
 */
extern DECLSPEC HANDLE ELTAPIENTRY ExHookWndProc(Int32  idHook, HOOKPROC lpfn);

/*
 *
 */
extern DECLSPEC ERESULT ELTAPISTDENTRY DefViewWindowProc(ExWin hwnd, Uint message, WPARAM wParam, LPARAM lParam);

/*
 *
 */
extern DECLSPEC ERESULT ELTAPISTDENTRY ListViewWindowProc(ExWin hwnd, Uint message, WPARAM wParam, LPARAM lParam);


#ifdef  __cplusplus	/* C++ Environment */
}
#endif

#endif
