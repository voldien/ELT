/*
===========================================================================
Copyright (C) 2014 BroodCity Software, Inc. Voldemor2009@hotmail.com

*/
#ifndef CONSOLE_SHELL_H
#define CONSOLE_SHELL_H
#include"System/elt_win.h"
#include <fcntl.h>
#ifdef EX_WINDOWS
	#include <io.h>
#endif

#ifdef __cplusplus	// C++ Environment
extern "C"{
#endif

typedef struct _coord{
	Int16 x,y;
}Coord;
/* Create Console */
extern DECLSPEC ExWin ELTAPIENTRY ExCreateConsole(void);
/*
	// Get Console Window Attached to current process.
*/
extern DECLSPEC ExWin ELTAPIENTRY ExGetConsoleWindow(void);
/*
	// Set Console size
*/
extern DECLSPEC Boolean ELTAPIENTRY ExSetConsoleSize(HANDLE handle, const Size_t size);
/*
	// Get Console size
*/
extern DECLSPEC Boolean ELTAPIENTRY ExGetConsoleSize(HANDLE handle, Size_t size);
/*
	// Set Cursor Position
*/
extern DECLSPEC Boolean ELTAPIENTRY ExSetConsoleCursorPos(HANDLE handle, Coord* coord);
/*
	// Get Cursor position 
*/
extern DECLSPEC Boolean ELTAPIENTRY ExGetConsoleCursorPos(HANDLE handle, Coord* coord);

extern DECLSPEC ERESULT ELTAPIENTRY InsertConsoleInHWND(ExWin hwnd);

/**/
extern DECLSPEC void ELTAPIENTRY ExWriteColorTextA(const char* text, Uint16 hexColor);
/**/
extern DECLSPEC void ELTAPIENTRY ExWriteColorTextW(const ExChar* text, Uint16 hexColor);

extern DECLSPEC HANDLE ExGetConsoleOutHandle(void);
extern DECLSPEC HANDLE ExGetConsoleInHandle(void);


#define EX_CONSOLE_BLACK 0x0
#define EX_CONSOLE_BLUE 0x1
#define EX_CONSOLE_GREEN 0x2
#define EX_CONSOLE_AQUA 0x3
#define EX_CONSOLE_RED 0x4
#define EX_CONSOLE_PURPLE 0x5
#define EX_CONSOLE_YELLOW  0x6
#define EX_CONSOLE_WHITE 0x7
#define EX_CONSOLE_GRAY 0x8
#define EX_CONSOLE_LIGHT_BLUE 0x9
#define EX_CONSOLE_LIGHT_GREEN 0xA
#define EX_CONSOLE_LIGHT_AQUA 0xB
#define EX_CONSOLE_LIGHT_RED 0xC
#define EX_CONSOLE_LIGHT_PURPLE 0xD
#define EX_CONSOLE_LIGHT_YELLOW 0xE
#define EX_CONSOLE_LIGHT_WHITE 0xF
#define EX_CONSOLE_COLOR_RESET 0x10

/*	Set Console Color	*/
extern DECLSPEC void ELTAPIENTRY ExSetConsoleColor(Uint16 colour);
/*	Get Console Color	*/
extern DECLSPEC Uint16 ELTAPIENTRY ExGetConsoleColor();

extern DECLSPEC Int32 ELTAPIENTRY ExGetConsoleFontSize(ULong stdHandle,Coord* coord);

/*	Clear Console Window	*/
extern DECLSPEC void ELTAPIENTRY ExClerConsole(ULong stdHandle);

extern DECLSPEC void ELTAPIENTRY ExConsoleTraparency(HANDLE handle);

#ifdef __cplusplus	// C++ Environment
}
#endif

#endif