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
#ifndef _ELT_LOADSO_H_
#define _ELT_LOADSO_H_ 1
#include"system/elt_win.h"

#ifdef __cplusplus	/*	C++ Environment	*/
extern "C" {
#endif


/**
 *	Load function from handle.
 *
 *	\handle handle to library.
 *
 *	\pProcName function name.
 *
 *	@Return function pointer.
 */
extern ELTDECLSPEC ExHandle ELTAPIENTRY ExLoadFunction(ExHandle handle,
		const char* pProcName);

/**
 *	Load module object to process
 *
 *	@Return pointer to module if successful.
 */
extern ELTDECLSPEC ExHandle ELTAPIENTRY ExLoadObject(const ExChar* sofile);

/**
 *	UnLoad Specified module object from process.
 *
 *	\handle
 */
extern ELTDECLSPEC void ELTAPIENTRY ExUnLoadObject(ExHandle handle);

/**
 * 	Check if a module is loaded in the current application.
 *
 *	@Return
 */
extern ELTDECLSPEC ExHandle ELTAPIENTRY ExIsModuleLoaded(const ExChar* file);

/**
 *	Is Module Loaded
 *
 *	@Return
 */
#define ExGetFileModule ExIsModuleLoaded


#ifdef __cplusplus	/*	C++ Environment	*/
}
#endif

#endif
