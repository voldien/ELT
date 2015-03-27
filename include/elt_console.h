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
#ifndef CONSOLE_SHELL_H
#define CONSOLE_SHELL_H
#include"system/elt_win.h"

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
extern DECLSPEC ExBoolean ELTAPIENTRY ExSetConsoleSize(HANDLE handle, const Int32* size);
/*
	// Get Console size
*/
extern DECLSPEC ExBoolean ELTAPIENTRY ExGetConsoleSize(HANDLE handle, Int32* size);
/*
	// Set Cursor Position
*/
extern DECLSPEC ExBoolean ELTAPIENTRY ExSetConsoleCursorPos(HANDLE handle, Coord* coord);
/*
	// Get Cursor position
*/
extern DECLSPEC ExBoolean ELTAPIENTRY ExGetConsoleCursorPos(HANDLE handle, Coord* coord);

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
