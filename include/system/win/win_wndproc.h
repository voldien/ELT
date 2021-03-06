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
 *	User defined window message
 */
#define WM_USER_SIZE (WM_USER + 1)

#ifdef __cplusplus	/*	C++ Environment	*/
extern "C"{
#endif

/*
 *	Disable alt tab
 */
extern ELTDECLSPEC void ELTAPIENTRY ExDisableAltTab(void);

/*
 * Enable alt tab.
 */
extern ELTDECLSPEC void ELTAPIENTRY ExEnableAltTab(void);

/*
 *
 */
extern ELTDECLSPEC ExBoolean ELTAPIENTRY ExEnableDeviceNotification(ExWin hWnd);

/*
 *	Main window message queue procedure.
 *	This WndProc utitilize
 *	\hWnd
 *	\uMsg
 *	\wParam
 *	\lParam
 *	@Return
*/
extern ELTDECLSPEC ERESULT ELTAPISTDENTRY ExMainWndProc(ExWin hWnd, unsigned int uMsg, WPARAM wParam, LPARAM lParam);

/*
 *	Native windows. designed for user interface handling.
 */
extern ELTDECLSPEC ERESULT ELTAPISTDENTRY ExWndProcNative(ExWin hWnd, unsigned int uMsg, WPARAM wParam, LPARAM lParam);

/*
 *	On Window Context menu.
 */
extern ELTDECLSPEC BOOL ELTAPISTDENTRY ExOnContextMenu(ExWin hWnd,int x, int y);

/*
 *	On Window Context menu.
 */
extern ELTDECLSPEC BOOL ELTAPISTDENTRY ExOnContextMenu2(ExWin hWnd, HMENU hmenu, int x, int y);

/*
 *	Display Window Context.
 */
extern ELTDECLSPEC BOOL ELTAPISTDENTRY ExDisplayContextMenu(ExWin hWnd, POINT* pt);

/*
 *
 */
extern ELTDECLSPEC ExHandle ELTAPIENTRY ExHookWndProc(int idHook, HOOKPROC lpfn);

/*
 *
 */
extern ELTDECLSPEC ERESULT ELTAPISTDENTRY DefViewWindowProc(ExWin hwnd, unsigned int message, WPARAM wParam, LPARAM lParam);

/*
 *
 */
extern ELTDECLSPEC ERESULT ELTAPISTDENTRY ListViewWindowProc(ExWin hwnd, unsigned int message, WPARAM wParam, LPARAM lParam);


#ifdef __cplusplus	/*	C++ Environment	*/
}
#endif

#endif
