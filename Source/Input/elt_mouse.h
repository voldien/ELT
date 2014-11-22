/*
===========================================================================
Copyright (C) 2014 BroodCity Software, Inc. Voldemor2009@hotmail.com

*/
#ifndef ELT_MOUSE_H
#define ELT_MOUSE_H
#include"./../EngineAssembly.h"
#include"./../System/elt_errorhandler.h"
#ifdef EX_WINDOWS

	typedef HCURSOR ExCursor;
	//extern IDirectInputDevice8* hMouseDevice;
#elif defined(EX_LINUX)

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
/*
	//Capture mouse
*/
extern DECLSPEC Int32 ELTAPIENTRY ExCaptureMouse(Boolean enabled);
/*
	// clip cursor onto specificed rect
*/
extern DECLSPEC Int32 ELTAPIENTRY ExClipCursor(const struct exrect* rect);
/*
	// Create Cursor
*/
extern DECLSPEC ExCursor ELTAPIENTRY ExCreateCursor(const Uint8* data, const Uint8* mask, Int32 width,Int32 height, Int32 hot_x, Int32 hot_y);
/*
	// Create System Cursor
*/
extern DECLSPEC ExCursor ELTAPIENTRY ExCreateSystemCursor(Enum system_id);
/*
	// Free cursor
*/
extern DECLSPEC Boolean ELTAPIENTRY ExFreeCursor(ExCursor cursor);
/*
	// Set Cursor
*/
extern DECLSPEC Boolean ELTAPIENTRY ExSetCursor(ExCursor cursor);
/*
	// Get Cursor
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

/*
	// Set Cursor relative to window
*/
extern DECLSPEC void ELTAPIENTRY ExWarpMouseInWindow(ExWin win,Int32 x, Int32 y);

extern DECLSPEC Boolean ELTAPIENTRY ExShowCursor(Boolean enabled);







//---------------------------------------------------
extern DECLSPEC ERESULT ELTAPIENTRY ExInitMouse(ExWin hwnd);

extern DECLSPEC ERESULT ELTAPIENTRY ExSetMouseCooperative(ExWin hWnd, Uint64 flag);

//---------------------------------------------------
/* Update Mouse Buffer.
*/
extern DECLSPEC void ELTAPIENTRY ExUpdateMouse(void);
//---------------------------------------------------
extern DECLSPEC void ELTAPIENTRY ExMouseShutDown(void);

//---------------------------------------------------
extern DECLSPEC const Boolean ELTAPIFASTENTRY ExGetButton(Uint32 keyCode);
//---------------------------------------------------
extern DECLSPEC const Boolean ELTAPIFASTENTRY ExGetButtonDown(Uint32 keyCode);
//---------------------------------------------------
extern DECLSPEC const Boolean ELTAPIFASTENTRY ExGetButtonUp(Uint32 keyCode);

extern DECLSPEC const Int ELTAPIFASTENTRY ExGetMouseDeltaX(void);
extern DECLSPEC const Int ELTAPIFASTENTRY ExGetMouseDeltaY(void);

extern DECLSPEC const Int ELTAPIFASTENTRY ExGetMouseXCoord(void);
extern DECLSPEC const Int ELTAPIFASTENTRY  ExGetMouseYCoord(void);

extern DECLSPEC const Float ELTAPIFASTENTRY ExGetMouseMagnitude(void);

#ifdef __cplusplus	// C++ Environment
}
#endif

#endif
