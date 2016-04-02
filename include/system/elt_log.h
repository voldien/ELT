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
#include"./../EngineAssembly.h"
extern FILE* m_file_log;


/*
 *
 */
extern ELTDECLSPEC void ELTAPIENTRY ExLog(const ExChar* format,...);

/*
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
 *
 */
extern ELTDECLSPEC FILE* ELTAPIENTRY ExDupFile(const int _fd);




#endif
