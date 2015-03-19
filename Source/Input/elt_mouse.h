/*
========================================================================
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
#ifndef _ELT_MOUSE_H_
#define _ELT_MOUSE_H_ 1
#include"./../EngineAssembly.h"
#include"./../System/elt_errorhandler.h"
#ifdef EX_WINDOWS
	typedef HCURSOR ExCursor;
	//extern IDirectInputDevice8* hMouseDevice;
#elif defined(EX_UNIX)
	typedef void* ExCursor;
#endif
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
#define ExMouseButton(x) (m_MouseHandler->MouseState[0]->rgbButtons[x] & 0x80)
#define ExMousePoint	m_MouseHandler->MouseState[0]->lX
#define ExMouseMotion

#ifdef __cplusplus	// C++ Environment
extern "C"{
#endif
/**
	Capture mouse
*/
extern DECLSPEC Int32 ELTAPIENTRY ExCaptureMouse(ExBoolean enabled);
/**
    clip cursor onto specified rectangle view
*/
extern DECLSPEC Int32 ELTAPIENTRY ExClipCursor(const struct exrect* rect);
/**
	Create Cursor
*/
extern DECLSPEC ExCursor ELTAPIENTRY ExCreateCursor(const Uint8* data, const Uint8* mask, Int32 width,Int32 height, Int32 hot_x, Int32 hot_y);
/**
	Create System Cursor
*/
extern DECLSPEC ExCursor ELTAPIENTRY ExCreateSystemCursor(Enum system_id);
/**
	Free cursor
*/
extern DECLSPEC ExBoolean ELTAPIENTRY ExFreeCursor(ExCursor cursor);
/**
	Set Cursor
*/
extern DECLSPEC ExBoolean ELTAPIENTRY ExSetCursor(ExCursor cursor);
/**
	Get Cursor
*/
extern DECLSPEC ExCursor ELTAPIENTRY ExGetCursor(void);

extern DECLSPEC ExCursor ELTAPIENTRY ExGetDefaultCursor(void);

extern DECLSPEC ExWin ELTAPIENTRY ExGetMouseFocus(void);
/*
	// Get Global Mouse State
*/
extern DECLSPEC Uint32 ELTAPIENTRY ExGetGlobalMouseState(Int32* x, Int32* y);

extern DECLSPEC Uint32 ELTAPIENTRY ExGetMouseState(Int32* x, Int32* y);
/*
	// Set cursor in screen space
*/
extern DECLSPEC void ELTAPIENTRY ExWarpMouseGlobal(Int32 x, Int32 y);

/**
	Set Cursor relative to window
*/
extern DECLSPEC void ELTAPIENTRY ExWarpMouseInWindow(ExWin win,Int32 x, Int32 y);
/**
    Show Cursor
*/
extern DECLSPEC ExBoolean ELTAPIENTRY ExShowCursor(ExBoolean enabled);






//---------------------------------------------------
extern DECLSPEC const ExBoolean ELTAPIFASTENTRY ExGetButton(Uint32 keyCode);
//---------------------------------------------------
extern DECLSPEC const ExBoolean ELTAPIFASTENTRY ExGetButtonDown(Uint32 keyCode);
//---------------------------------------------------
extern DECLSPEC const ExBoolean ELTAPIFASTENTRY ExGetButtonUp(Uint32 keyCode);



/**/
extern DECLSPEC const int ELTAPIENTRY ExGetTouchDown(unsigned int fingerid);

extern DECLSPEC const int ELTAPIENTRY ExGetTouchPosition(unsigned int fingerid, float* pos);

#ifdef __cplusplus	// C++ Environment
}
#endif

#endif
