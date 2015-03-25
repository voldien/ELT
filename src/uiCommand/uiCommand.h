/*
===========================================================================
Copyright (C) 2014 BroodCity Software, Inc. Voldemor2009@hotmail.com

*/
#ifndef UI_COMMAND_H
#define UI_COMMAND_H
#include"./../EngineAssembly.h"
#include"./../System/elt_win.h"

#define EXUI_OPENGL 0x1
#define EXUI_DIRECTX 0x2
#define EXUI_VIEW_TOP 0x4
#define EXUI_VIEW_BOTTOM 0x8
#define EXUI_VIEW_RIGHT 0x10
#define EXUI_VIEW_LEFT 0x20
#define EXUI_INTERNAL_PROC 0x40	// use of internal command proc
#define EXUI_MESSAGE 0x80		// has a message
#define EXUI_DISABLE 0x100
#define EXUI_ENABLE 0x200
#define EXUI_CUSTOM 0x400
#define EXUI_TRANSPARENT 0x800
#define EXUI_ROLLDOWN 0x1000
#define EXUI_CONSOLE_CHILD 0x2000
#define EXUI_CONSOLE_CREATE_PARENT 0x4000

#define EXUI_DEFAULT (EXUI_VIEW_TOP | EXUI_CONSOLE_CHILD | EXUI_ROLLDOWN | EXUI_TRANSPARENT | EXUI_ENABLE | EXUI_INTERNAL_PROC)

typedef ERESULT(ELTAPIENTRY* ExUICommandProc)(ExWin hWnd, char* cCmd);
typedef struct UiCommandData{
	HANDLE uiConsoleThread;
	ExWin parentHwnd;
	ExWin renderHwnd;
	ExWin hWndConsole;
	Uint32 renderingFlag;
	char* message;
	ExUICommandProc* commandProc;
}UI_COMMAND_DATA;
extern HANDLE uiConsoleThread;
extern UI_COMMAND_DATA* uiConsoleData;
 
#ifdef EX_CPP // C++
#endif
/*
	// UI Command 
*/
extern DECLSPEC ExWin ELTAPIENTRY ExInitUICommand(ExWin hWndrender, ExWin hWndConsole,ExUICommandProc commandProc, Enum uiFlag);

extern DECLSPEC Uint16 ELTAPIENTRY ExHookUICommandProc(ExUICommandProc commandProc);
extern DECLSPEC Uint16 ELTAPIENTRY ExRemoveUICommandProc(ExUICommandProc commandProc);
extern DECLSPEC Uint16 ELTAPIENTRY ExRemoveUICommandProci(Uint32 index);
/*	Set */
extern DECLSPEC Boolean ELTAPIENTRY ExSetUIFlag(Enum renderingFlag);
/*
	//
*/
extern DECLSPEC Enum ELTAPIENTRY ExIsFlagSet(Enum renderingFlag,Enum isFlag);
/*	Set Rect of the UI Console	*/
extern DECLSPEC Void ELTAPIENTRY ExSetUIRect(RECT* rect);

extern DECLSPEC Boolean ELTAPIENTRY ExUpdateUIWindow(Void);

//extern DECLSPEC Void ELTAPIENTRY Ex
extern DECLSPEC Uint32 ELTAPIENTRY ExReleaseUICommand(Void);

extern DECLSPEC Uint32 ELTAPISTDENTRY ExUICommandThread(LPVOID data);
/*
	// Get Message
*/
extern DECLSPEC Uint16 ELTAPIENTRY ExGetUIMessage(Void);

extern DECLSPEC ERESULT ELTAPIENTRY ExUICommandInternalProc(ExWin hWnd, char* cCmd);

#endif