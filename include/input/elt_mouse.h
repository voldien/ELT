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
#ifndef _ELT_MOUSE_H_
#define _ELT_MOUSE_H_ 1
#include"./../system/elt_errorhandler.h"
#include"../system/elt_event.h"

#ifdef __cplusplus	/* C++ Environment */
extern "C" {
#endif

typedef void* ExCursor;

#define EXC_ARROW		0x1
#define EXC_IBEAM		0x2
#define EXC_WAIT		0x3
#define EXC_CROSS		0x4
#define EXC_UPARROW		0x5
#define EXC_SIZE		0x6
#define EXC_ICON		0x7
#define EXC_SIZENWSE	0x8
#define EXC_SIZENESW	0x9
#define EXC_SIZEWE		0xA
#define EXC_SIZENS		0xB
#define EXC_SIZEALL		0xC
#define EXC_NO			0xD
#if(WINVER >= 0x0500)
#define EXC_HAND		0xE
#endif
#define EXC_APPSTART	0xF
#if(WINVER >= 0x0400)
#define EXC_HELP		0x10
#endif

enum ExMouseCode {
	eExMouseNone, eExMouseLeft, eExMouseRight, eExMouseMiddle, eExMousePadding
};

/**
 *	Capture mouse.
 *
 *	\enable
 *
 *	@Return
 */
extern ELTDECLSPEC int ELTAPIENTRY ExCaptureMouse(ExBoolean enabled);

/**
 *	Clip cursor onto specified rectangle view
 *
 *	@Return
 */
extern ELTDECLSPEC int ELTAPIENTRY ExClipCursor(ExWin window);

/**
 *
 */
extern ELTDECLSPEC int ELTAPIENTRY ExClipCursorRect(ExRect* rect);

/**
 *	Create Cursor
 *
 *	@Return
 */
extern ELTDECLSPEC ExCursor ELTAPIENTRY ExCreateCursor(
		const unsigned char* data, const unsigned char* mask, int width,
		int height, int hot_x, int hot_y);

/**
 *	Create System Cursor
 *
 *	@Return
 */
extern ELTDECLSPEC ExCursor ELTAPIENTRY ExCreateSystemCursor(
		unsigned int system_id);

/**
 *	Free cursor
 *
 *	@Return
 */
extern ELTDECLSPEC ExBoolean ELTAPIENTRY ExFreeCursor(ExCursor cursor);

/**
 *	Set Cursor
 *
 *	@Return
 */
extern ELTDECLSPEC ExBoolean ELTAPIENTRY ExSetCursor(ExWin window,
		ExCursor cursor);

/**
 *	Get Cursor
 *
 *	@Return
 */
extern ELTDECLSPEC ExCursor ELTAPIENTRY ExGetCursor(void);

/**
 *	Get default system cursor pointer.
 *
 *	@Return
 */
extern ELTDECLSPEC ExCursor ELTAPIENTRY ExGetDefaultCursor(void);

/**
 *
 *
 *	@Return
 */
extern ELTDECLSPEC ExWin ELTAPIENTRY ExGetMouseFocus(void);

/**
 *	Get Global Mouse State
 *
 *	@Return button pressed.
 */
extern ELTDECLSPEC unsigned int ELTAPIENTRY ExGetGlobalMouseState(int* x,
		int* y);

/**
 *
 *	@Return
 */
extern ELTDECLSPEC unsigned int ELTAPIENTRY ExGetMouseState(int* x, int* y);

/**
 *	Set cursor in screen space respect to monitor resolution.
 *
 */
extern ELTDECLSPEC void ELTAPIENTRY ExWarpMouseGlobal(int x, int y);

/**
 *	Set Cursor relative to window
 *
 */
extern ELTDECLSPEC void ELTAPIENTRY ExWarpMouseInWindow(ExWin win, int x, int y);

/**
 *	Show Cursor
 *
 *
 *	@Return if successfully then return value is equal to input value.
 */
extern ELTDECLSPEC ExBoolean ELTAPIENTRY ExShowCursor(ExBoolean enabled);

/*	TODO FIX for touch.	*/

/**
 *
 * 	@Return
 */
extern ELTDECLSPEC int ELTAPIENTRY ExGetTouchDown(unsigned int fingerid);

/**
 *
 * @Return
 */
extern ELTDECLSPEC int ELTAPIENTRY ExGetTouchPosition(unsigned int fingerid,
		float* pos);

#ifdef __cplusplus	/* C++ Environment */
}
#endif

#endif
