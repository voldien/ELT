/*
===========================================================================
Copyright (C) 2014 BroodCity Software, Inc. Voldemor2009@hotmail.com

*/
#ifndef ELT_WIN_H
#define ELT_WIN_H
#include"./../EngineAssembly.h"
#include"elt_event.h"
#include<Cmd/mathlib.h>	//TODO fix
#ifdef  __cplusplus	// C++ Environment
extern "C"{
#endif

#ifdef EX_WINDOWS
	#define ExMessageBox MessageBox
#else
	#define ExMessageBox(a,b,c,d) gtk_message_dialog_new()
#endif

/*
	//Create Window [x coordination, y coordination]
*/
extern DECLSPEC ExWin ELTAPIENTRY ExCreateWindow(Int32 x, Int32 y, Int32 width, Int32 height,Enum flag);
/*
	// show window
*/
extern DECLSPEC void ELTAPIENTRY ExShowWindow(ExWin window);
/*
	// Hide Window
*/
extern DECLSPEC void ELTAPIENTRY ExHideWindow(ExWin window);
/*
	//
*/
extern DECLSPEC void ELTAPIENTRY ExSetWindowMode(ExWin window, Enum mode);

/*
    // Destroy Window
*/
extern DECLSPEC Boolean ELTAPIENTRY ExDestroyWindow(ExWin window);

/*
	// Set Window Title
*/
extern DECLSPEC void ELTAPIENTRY ExSetWindowTitle(ExWin window,const ExChar* title);
/*
	// Get Windows Title
*/
extern DECLSPEC void ELTAPIENTRY ExGetWindowTitle(ExWin window, ExChar* title);

/*
	// Set Windows Position
*/
extern DECLSPEC void ELTAPIENTRY ExSetWindowPos(ExWin window,Int32 x,Int32 y);

/*
	// Set Windows Position
*/
extern DECLSPEC void ELTAPIENTRY ExSetWindowPosv(ExWin window,const Int32* position);
/*
 */
extern DECLSPEC void ELTAPIENTRY ExGetWindowPosv(ExWin window, Int32* position);
/*
	// Set Window size
*/
extern DECLSPEC void ELTAPIENTRY ExSetWindowSize(ExWin window,Int32 width, Int32 height);
/*
	// Set Window Size
*/
extern DECLSPEC void ELTAPIENTRY ExSetWindowSizev(ExWin window,const Size_t size);
/*
    Get Window Size
*/
extern DECLSPEC void ELTAPIENTRY ExGetWindowSizev(ExWin window, Size_t size);
/*
	// Set Window Rect
*/
extern DECLSPEC void ELTAPIENTRY ExSetWindowRect(ExWin window, const rect_t* rect);
/*
	// Get Window Rect
*/
extern DECLSPEC void ELTAPIENTRY ExGetWindowRect(ExWin window, rect_t* rect);



/*
	//	Get Window mode
*/
extern DECLSPEC Uint32 ELTAPIENTRY ExGetWindowFlag(ExWin window);

/*
 *	Assign Icon Handle onto window
 */
extern DECLSPEC Int32 ELTAPIENTRY ExSetWindowIcon(ExWin window, HANDLE hIcon);
/*
 *	Get Window Icon Handle
 */
extern DECLSPEC Int32 ELTAPIENTRY ExGetWindowIcon(ExWin window);


//extern DECLSPEC Int32 ELTAPIENTRY ExVideoQuit(void);

/*
// Poll Window Event information
// *[HWND] which window to poll event information.
//	Remark: message feed will only be apply to given HWND paramter
//	if HWND is null all window create on this application will be update
//	read more at MSDN for more specific information regarding PeekMessage with null HWND.
// *[ExWindowEvent] pointer to event struct. all event will be stored in it.
//	#return if PeekMessage was success.
// PeekMessage : http://msdn.microsoft.com/en-us/library/windows/desktop/ms644943(v=vs.85).aspx
*/
extern DECLSPEC Boolean ELTAPIENTRY ExPollWindowEvent(ExWin window, ExWindowEvent* event);




#ifdef __cplusplus	//	C++ Env
}
#endif
#endif
