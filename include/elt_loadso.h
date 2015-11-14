/**
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
#ifndef _ELT_LOADSO_H_
#define _ELT_LOADSO_H_ 1
#include"EngineAssembly.h"
#include"system/elt_win.h"

#ifdef  __cplusplus	/* C++ Environment	*/
extern "C"{
#endif


/**/
extern DECLSPEC int ELTAPIENTRY ExLoadNumSymbol(HANDLE handle);

/**/
extern DECLSPEC char* ELTAPIENTRY ExLoadSymbol(HANDLE handle, int index, char* symbol, int len);


/*
	Load function from handle.
	\handle handle to library.
	\pProcName function name.
	@return function pointer.
*/
extern DECLSPEC HANDLE ELTAPIENTRY ExLoadFunction(HANDLE handle, const char* pProcName);
/*
	Load Module object
	@return
*/
extern DECLSPEC HANDLE ELTAPIENTRY ExLoadObject(const ExChar* sofile);
/*
	UnLoad Module object
*/
extern DECLSPEC void ELTAPIENTRY ExUnLoadObject(HANDLE handle);
/*
	Is Module Loaded
	@return
*/
extern DECLSPEC HANDLE ELTAPIENTRY ExIsModuleLoaded(const ExChar* file);
/*
    Is Module Loaded
*/
#define ExGetFileModule ExIsModuleLoaded
/*
    Load Object
*/
#define ExLoadLibrary ExLoadObject

#ifdef  __cplusplus	// C++ Environment
}
#endif

#endif
