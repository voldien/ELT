/*
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
#ifndef _ELT_LOG_H_
#define _ELT_LOG_H_ 1
#include"../system.h"
#include"elt_errorhandler.h"
extern FILE* m_file_log;

/**
 *
 */
extern ELTDECLSPEC void ELTAPIENTRY ExLog(const ExChar* format,...);

/**
 *
 */
extern ELTDECLSPEC void ELTAPIENTRY ExErrorLog(const ExChar* format,...);

/*
 *
 */
extern ELTDECLSPEC void ELTAPIENTRY ExLogWarning(const ExChar* format,...);

/*
 *
 */
extern ELTDECLSPEC void ELTAPIENTRY ExLogCritical(const ExChar* format,...);

/*
 *
 */
extern ELTDECLSPEC void ELTAPIENTRY ExLogInfo(const ExChar* format,...);


/*
 *	@Return
 */
extern ELTDECLSPEC FILE* ELTAPIENTRY ExDupFile(const int _fd);



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


/*
 *
 */
extern ELTDECLSPEC void ELTAPIENTRY ExSetConsoleColor(Uint16 colour);

/*
 *
 */
extern ELTDECLSPEC Uint16 ELTAPIENTRY ExGetConsoleColor(void);




#endif
