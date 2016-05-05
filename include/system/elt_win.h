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

#ifdef  __cplusplus	/*	C++ Environment	*/
extern "C"{
#endif

#ifdef EX_LINUX
extern ExDisplay display;
#endif


#define EX_WIN_SCREENSAVER_ENABLE   0x200000
#define EX_WIN_SCREENSAVER_DISABLE  0x400000


#define EX_WIN_TOP
#define EX_WIN_BELOW
#define EX_WIN_


/*
 *	Get ELT Window default Title!
 *	@Return
 */
extern ELTDECLSPEC ExChar* ELTAPIENTRY ExGetDefaultWindowTitle(ExChar* text, Int32 length);

/*
 *	Create Window
 *	\x : coordinate
 *	\y : coordinate
 *	\width : width of the window
 *	\height : height of the window
 *	\flag : window type
 *	@Return window handle
 */
extern ELTDECLSPEC ExWin ELTAPIENTRY ExCreateWindow(Int32 x, Int32 y, Int32 width, Int32 height, Enum flag);

/*
 *	Show window
 *	\window window handle
 */
extern ELTDECLSPEC void ELTAPIENTRY ExShowWindow(ExWin window);

/*
 *	Hide Window
 *	\window Window handle
 */
extern ELTDECLSPEC void ELTAPIENTRY ExHideWindow(ExWin window);

/*
 *
 */
extern ELTDECLSPEC void ELTAPIENTRY ExCloseWindow(ExWin window);

/*
 *
 */
extern ELTDECLSPEC void ELTAPIENTRY ExMaximizeWindow(ExWin window);

/*
 *
 */
extern ELTDECLSPEC void ELTAPIENTRY ExMinimizeWindow(ExWin window);

/*
 *	Set window mode
 */
extern ELTDECLSPEC void ELTAPIENTRY ExSetWindowMode(ExWin window, Enum mode);



/*
 *	Destroy Window
 *	@Return
 */
extern ELTDECLSPEC ExBoolean ELTAPIENTRY ExDestroyWindow(ExWin window);

/*
 *	Set Window Title
 *	\window
 *	\title window title
 *	@Return
 */
extern ELTDECLSPEC void ELTAPIENTRY ExSetWindowTitle(ExWin window, const ExChar* title);

/*
 *	Get Windows Title
 *	\window
 *	\title
 *	@Return
 */
extern ELTDECLSPEC ExChar* ELTAPIENTRY ExGetWindowTitle(ExWin window, ExChar* title);

/*
 *	Set Windows Position
 *	\window
 *	\x
 *	\y
 */
extern ELTDECLSPEC void ELTAPIENTRY ExSetWindowPos(ExWin window, Int32 x, Int32 y);

/*
 *	Set Windows Position
 */
extern ELTDECLSPEC void ELTAPIENTRY ExSetWindowPosv(ExWin window, const Int32* position);

/*
 *
 */
extern ELTDECLSPEC void ELTAPIENTRY ExGetWindowPosv(ExWin window, Int32* position);

/*
 *	Set Window size
 */
extern ELTDECLSPEC void ELTAPIENTRY ExSetWindowSize(ExWin window,Int32 width, Int32 height);

/*
 *	Set Window Size
 */
extern ELTDECLSPEC void ELTAPIENTRY ExSetWindowSizev(ExWin window, const ExSize* size);

/*
 *   Get Window Size
 */
extern ELTDECLSPEC void ELTAPIENTRY ExGetWindowSizev(ExWin window, ExSize* size);

/*
 *	Set Window Rect
 */
extern ELTDECLSPEC void ELTAPIENTRY ExSetWindowRect(ExWin window, const ExRect* rect);

/*
 *	Get Window Rect
 */
extern ELTDECLSPEC void ELTAPIENTRY ExGetWindowRect(ExWin window, ExRect* rect);

/*
 *	Get Window mode
 *	@Return
 */
extern ELTDECLSPEC Uint32 ELTAPIENTRY ExGetWindowFlag(ExWin window);

/*
 *	Set Window Flag
 */
extern ELTDECLSPEC void ELTAPIENTRY ExSetWindowFlag(ExWin window, Enum flag);

/*
 *
 */
extern ELTDECLSPEC void ELTAPIENTRY ExSetWindowFlagv(ExWin window, Enum flag, Int32 value);

/*
 *	Assign Icon Handle onto window
 *	@Return
 */
extern ELTDECLSPEC Int32 ELTAPIENTRY ExSetWindowIcon(ExWin window, ExHandle hIcon);

/*
 *	Get Window Icon Handle
 *	@Return
 */
extern ELTDECLSPEC Int32 ELTAPIENTRY ExGetWindowIcon(ExWin window);

/*
 *
 *	@Return
 */
extern ELTDECLSPEC Int32 ELTAPIENTRY ExSetWindowFullScreen(ExWin window, ExBoolean flag);

/*
 *	Get user-data associated with window handle.
 *	@Return
 */
extern ELTDECLSPEC ExHandle ELTAPIENTRY ExGetWindowUserData(ExWin window);

/*
 *	Set user-data associated with window handle.
 */
extern ELTDECLSPEC void ELTAPIENTRY ExSetWindowUserData(ExWin window, ExHandle userdata);

/*
 *
 *	@Return
 */
extern ELTDECLSPEC Int32 ELTAPIENTRY ExSetWindowParent(ExWin parent,ExWin window);

/*
 *
 *	@Return
 */
extern ELTDECLSPEC ExWin ELTAPIENTRY ExGetWindowParent(ExWin window);

/*
 *
 *	@Return
 */
extern ELTDECLSPEC Int32 ELTAPIENTRY ExSetWindowChild(ExWin window, ExWin child);

/*
 *
 *	@Return
 */
extern ELTDECLSPEC ExWin ELTAPIENTRY ExGetWindowChild(ExWin window, Uint32 index);

/*
 *	Get number of window children.
 *	@Return
 */
extern ELTDECLSPEC Int32 ELTAPIENTRY ExGetWindowNumChildren(ExWin window);

/*
 *	Get desktop window handle.
 *	@Return
 */
extern ELTDECLSPEC ExWin ELTAPIENTRY ExGetDesktopWindow(void);

/*
 *	Get root window handle.
 *	@Return
 */
extern ELTDECLSPEC ExWin ELTAPIENTRY ExGetRootWindow(void);





/*
 *
 *	@Return
 */
extern ELTDECLSPEC int ELTAPIENTRY ExMessageBox(ExWin window, const ExChar* text, const ExChar* title, unsigned int flags);


/*
 *
 */
extern ELTDECLSPEC int ELTAPIENTRY ExGetDisplayDPI(int displayIndex, float* ddpi, float* hdpi, float* vdpi);

/*
 *
 */
extern ELTDECLSPEC Int32 ELTAPIENTRY ExIsScreenSaverEnable(void);

/**/
extern ELTDECLSPEC int ExEnableScreenSaver(void);

/**/
extern ELTDECLSPEC int ExDisableScreenSaver(void);


#ifdef  __cplusplus	/** C++ Environment */
}
#endif
#endif
