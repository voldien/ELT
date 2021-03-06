/**
	ELT (Engine Library Toolkit) is a cross platform engine toolkit
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
#include"elt_event.h"
#include"elt_cl.h"

#ifdef  __cplusplus	/*	C++ Environment	*/
extern "C" {
#endif

#ifdef EX_LINUX
extern ExDisplay display;
#endif

#define EX_WIN_SCREENSAVER_ENABLE   0x200000
#define EX_WIN_SCREENSAVER_DISABLE  0x400000

#define EX_WIN_TOP
#define EX_WIN_BELOW
#define EX_WIN_

/**
 *	Engine Rendering Flags
 */
#define EX_NATIVE (1 << 7)
#define EX_OPENGL (1 << 8)
#define EX_OPENGL_CORE ((1 << 13) | EX_OPENGL)
#define EX_EGL (1 << 9)
#define EX_OPENCL  (1 << 10)
#define EX_DIRECTX  (1 << 11)
#define EX_OPENGL_AND_OPENCL (ENGINE_OPENGL | ENGINE_OPENCL)
#define EX_RENDER_CONTEXT_DEBUG (1 << 12)
#define EX_VULKAN (1 << 14)
#define EX_OPENGLES (1 << 15)

/**
 *	Get ELT Window default Title.
 *
 *	@Return
 */
extern ELTDECLSPEC ExChar* ELTAPIENTRY ExGetDefaultWindowTitle(ExChar* text,
		int length);

/**
 *	Create Window at position and size. With the option to set flag
 *	for what kind of rendering library to attach to the window.
 *
 *	\x : coordinate
 *
 *	\y : coordinate
 *
 *	\width : width of the window
 *
 *	\height : height of the window
 *
 *	\flag : window option flag, default is 0 and will create native window.
 *
 *	@Return window handle pointer if successfully, else NULL pointer.
 */
extern ELTDECLSPEC ExWin ELTAPIENTRY ExCreateWindow(int x, int y, int width,
		int height, unsigned int flag);

/**
 *	Show window.
 *
 *	\window window handle to shdow.
 */
extern ELTDECLSPEC void ELTAPIENTRY ExShowWindow(ExWin window);

/**
 *	Hide Window
 *
 *	\window Window handle
 */
extern ELTDECLSPEC void ELTAPIENTRY ExHideWindow(ExWin window);

/**
 *	Close window.
 *
 *	This will in succession destroy the window.
 */
extern ELTDECLSPEC void ELTAPIENTRY ExCloseWindow(ExWin window);

/**
 *	Maximize window.
 *
 *	\window
 *
 */
extern ELTDECLSPEC void ELTAPIENTRY ExMaximizeWindow(ExWin window);

/**
 *	Minimize Window.
 *
 *	\window
 */
extern ELTDECLSPEC void ELTAPIENTRY ExMinimizeWindow(ExWin window);

/**
 *	Set window mode.
 */
extern ELTDECLSPEC void ELTAPIENTRY ExSetWindowMode(ExWin window,
		unsigned int mode);

/**
 *	Destroy Window and its resources.
 *
 *	\window
 *
 *	@Return
 */
extern ELTDECLSPEC ExBoolean ELTAPIENTRY ExDestroyWindow(ExWin window);

/**
 *	Set Window Title
 *
 *	\window
 *
 *	\title window title
 */
extern ELTDECLSPEC void ELTAPIENTRY ExSetWindowTitle(ExWin window,
		const ExChar* title);

/**
 *	Get window title.
 *
 *	\window
 *
 *	\title
 *
 *	@Return
 */
extern ELTDECLSPEC ExChar* ELTAPIENTRY ExGetWindowTitle(ExWin window,
		ExChar* title);

/**
 *	Set Windows Position.
 *
 *	\window
 *
 *	\x
 *
 *	\y
 */
extern ELTDECLSPEC void ELTAPIENTRY ExSetWindowPos(ExWin window, int x, int y);

/**
 *	Set Windows Position.
 *
 *	\window
 *
 *	\position
 */
extern ELTDECLSPEC void ELTAPIENTRY ExSetWindowPosv(ExWin window,
		const int* position);

/**
 *	Get window position.
 *
 *	\window
 *
 *	\position
 */
extern ELTDECLSPEC void ELTAPIENTRY ExGetWindowPosv(ExWin window, int* position);

/**
 *	Set Window size
 *
 *	\window
 *
 *	\width
 *
 *	\height
 */
extern ELTDECLSPEC void ELTAPIENTRY ExSetWindowSize(ExWin window, int width,
		int height);

/**
 *	Set Window Size
 *
 *	\window
 *
 *	\size
 */
extern ELTDECLSPEC void ELTAPIENTRY ExSetWindowSizev(ExWin window,
		const ExSize* size);

/**
 *   Get Window Size
 *
 *	\window
 *
 *	\size
 */
extern ELTDECLSPEC void ELTAPIENTRY ExGetWindowSizev(ExWin window, ExSize* size);

/**
 *	Set Window Rect
 *
 *	\window
 *
 *	\rect
 *
 */
extern ELTDECLSPEC void ELTAPIENTRY ExSetWindowRect(ExWin window,
		const ExRect* rect);

/**
 *	Get Window Rect.
 *
 *	\window
 *
 *	\rect
 */
extern ELTDECLSPEC void ELTAPIENTRY ExGetWindowRect(ExWin window, ExRect* rect);

/**
 *	Get window mode.
 *
 *	@Return
 */
extern ELTDECLSPEC unsigned int ELTAPIENTRY ExGetWindowFlag(ExWin window);

/**
 *	Set window flag.
 *
 */
extern ELTDECLSPEC void ELTAPIENTRY ExSetWindowFlag(ExWin window,
		unsigned int flag);

/**
 *
 */
extern ELTDECLSPEC void ELTAPIENTRY ExSetWindowFlagv(ExWin window,
		unsigned int flag, int value);

/**
 *	Assign Icon Handle onto window
 *
 *	@Return
 */
extern ELTDECLSPEC int ELTAPIENTRY ExSetWindowIcon(ExWin window, ExHandle hIcon);

/**
 *	Get Window Icon Handle
 *
 *	\window
 *
 *	@Return
 */
extern ELTDECLSPEC int ELTAPIENTRY ExGetWindowIcon(ExWin window);

/*
 *
 *	@Return
 */
extern ELTDECLSPEC int ELTAPIENTRY ExSetWindowFullScreen(ExWin window,
		ExBoolean flag);

/**
 *	Get user-data associated with window handle.
 *
 *	\window
 *
 *	@Return
 */
extern ELTDECLSPEC ExHandle ELTAPIENTRY ExGetWindowUserData(ExWin window);

/**
 *	Set user-data associated with window handle.
 *
 */
extern ELTDECLSPEC void ELTAPIENTRY ExSetWindowUserData(ExWin window,
		ExHandle userdata);

/**
 *
 *	@Return
 */
extern ELTDECLSPEC int ELTAPIENTRY ExSetWindowParent(ExWin parent, ExWin window);

/**
 *	Get window parent handle.
 *
 *	@Return
 */
extern ELTDECLSPEC ExWin ELTAPIENTRY ExGetWindowParent(ExWin window);

/**
 *	Set window child window handle.
 *
 *	@Return
 */
extern ELTDECLSPEC int ELTAPIENTRY ExSetWindowChild(ExWin window, ExWin child);

/**
 *	Get window child.
 *
 *	@Return
 */
extern ELTDECLSPEC ExWin ELTAPIENTRY ExGetWindowChild(ExWin window,
		unsigned int index);

/**
 *	Get number of window children.
 *
 *	@Return
 */
extern ELTDECLSPEC int ELTAPIENTRY ExGetWindowNumChildren(ExWin window);

/**
 *	Get desktop window handle.
 *
 *	@Return
 */
extern ELTDECLSPEC ExWin ELTAPIENTRY ExGetDesktopWindow(void);

/**
 *	Get root window handle.
 *
 *	@Return
 */
extern ELTDECLSPEC ExWin ELTAPIENTRY ExGetRootWindow(void);

extern ELTDECLSPEC void ELTAPIENTRY ExMakeDesktopWindow(ExWin window);

/**
 *
 *	@Return
 */
extern ELTDECLSPEC int ELTAPIENTRY ExMessageBox(ExWin window,
		const ExChar* text, const ExChar* title, unsigned int flags);

/*
 *
 */
extern ELTDECLSPEC int ELTAPIENTRY ExGetDisplayDPI(int displayIndex,
		float* ddpi, float* hdpi, float* vdpi);


#ifdef  __cplusplus	/** C++ Environment */
}
#endif
#endif
