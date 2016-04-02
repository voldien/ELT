/**
    ELT (Engine Library Toolkit) is a multi platform engine toolkit
    Copyright (C) 2016  Valdemar Lindberg

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
#ifndef _ELT_FILE_SYSTEM_H_
#define _ELT_FILE_SYSTEM_H_ 1
#include"./../EngineAssembly.h"

#ifdef __cplusplus	/*	C++ Environment	*/
extern "C"{
#endif

/*
 *
 *	@Return
 */
extern ELTDECLSPEC ExBoolean ELTAPIENTRY ExCreateRamDisk(const ExChar* cdirectory, unsigned int nBytes);

/*
 *
 *	@Return
 */
extern ELTDECLSPEC ExBoolean ELTAPIENTRY ExMount(const ExChar* source, const ExChar* target, const ExChar* filesystemtype, unsigned long mountflags, const void *data);

/*
 *
 *	@Return
 */
extern ELTDECLSPEC ExBoolean ELTAPIENTRY ExUMount(const ExChar* cdirectory);



#ifdef __cplusplus	/*	C++ Environment	*/
}
#endif

#endif
