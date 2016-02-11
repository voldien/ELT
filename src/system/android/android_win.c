#include"system/elt_win.h"








/*
 *	Show window
 *	\window window handle
 */
ELTDECLSPEC void ELTAPIENTRY ExShowWindow(ExWin window){}

/*
 *	Hide Window
 *	\window Window handle
 */
ELTDECLSPEC void ELTAPIENTRY ExHideWindow(ExWin window){}

/*
 *
 */
ELTDECLSPEC void ELTAPIENTRY ExCloseWindow(ExWin window){}

/*
 *
 */
ELTDECLSPEC void ELTAPIENTRY ExMaximizeWindow(ExWin window){}

/*
 *
 */
ELTDECLSPEC void ELTAPIENTRY ExMinimizeWindow(ExWin window){}

/*
 *	Set window mode
 */
ELTDECLSPEC void ELTAPIENTRY ExSetWindowMode(ExWin window, Enum mode){}



/*
 *	Destroy Window
 *	@return
 */
ELTDECLSPEC ExBoolean ELTAPIENTRY ExDestroyWindow(ExWin window){}

/*
 *	Set Window Title
 *	\window
 *	\title window title
 *	@return
 */
ELTDECLSPEC void ELTAPIENTRY ExSetWindowTitle(ExWin window, const ExChar* title){}





/*
 *	Get Windows Title
 *	\window
 *	\title
 *	@return
 */
ELTDECLSPEC ExChar* ELTAPIENTRY ExGetWindowTitle(ExWin window, ExChar* title){}

/*
 *	Set Windows Position
 *	\window
 *	\x
 *	\y
 */
ELTDECLSPEC void ELTAPIENTRY ExSetWindowPos(ExWin window, Int32 x, Int32 y){}

/*
 *	Set Windows Position
 */
ELTDECLSPEC void ELTAPIENTRY ExSetWindowPosv(ExWin window, const Int32* position){}

/*
 *
 */
ELTDECLSPEC void ELTAPIENTRY ExGetWindowPosv(ExWin window, Int32* position){}

/*
 *	Set Window size
 */
ELTDECLSPEC void ELTAPIENTRY ExSetWindowSize(ExWin window,Int32 width, Int32 height){}

/*
 *	Set Window Size
 */
ELTDECLSPEC void ELTAPIENTRY ExSetWindowSizev(ExWin window, const ExSize* size){}

/*
 *   Get Window Size
 */
ELTDECLSPEC void ELTAPIENTRY ExGetWindowSizev(ExWin window, ExSize* size){}

/*
 *	Set Window Rect
 */
ELTDECLSPEC void ELTAPIENTRY ExSetWindowRect(ExWin window, const ExRect* rect){}

/*
 *	Get Window Rect
 */
ELTDECLSPEC void ELTAPIENTRY ExGetWindowRect(ExWin window, ExRect* rect){}

/*
 *	Get Window mode
 *	@Return
 */
ELTDECLSPEC Uint32 ELTAPIENTRY ExGetWindowFlag(ExWin window){}

/*
 *	Set Window Flag
 */
ELTDECLSPEC void ELTAPIENTRY ExSetWindowFlag(ExWin window, Enum flag){}

/*
 *
 */
ELTDECLSPEC void ELTAPIENTRY ExSetWindowFlagv(ExWin window, Enum flag, Int32 value){}

/*
 *	Assign Icon Handle onto window
 *	@Return
 */
ELTDECLSPEC Int32 ELTAPIENTRY ExSetWindowIcon(ExWin window, ExHandle hIcon){}

/*
 *	Get Window Icon Handle
 *	@Return
 */
ELTDECLSPEC Int32 ELTAPIENTRY ExGetWindowIcon(ExWin window){}
