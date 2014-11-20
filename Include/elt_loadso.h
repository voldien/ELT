/*
===========================================================================
Copyright (C) 2014 BroodCity Software, Inc. Voldemor2009@hotmail.com

*/
#ifndef ELT_LOADSO_H
#define ELT_LOADSO_H
#include"EngineAssembly.h"
#include"System/elt_win.h"
#ifdef  __cplusplus	// C++ Environment
extern "C"{
#endif
/*
	// Load function 
*/
extern DECLSPEC HANDLE ELTAPIENTRY ExLoadFunction(HANDLE handle, const char* pProcName);
/*
	// Load Module object
*/
extern DECLSPEC HANDLE ELTAPIENTRY ExLoadObject(const ExChar* sofile);
/*
	// UnLoad Module object
*/
extern DECLSPEC void ELTAPIENTRY ExUnLoadObject(HANDLE handle);
/*
	// Is Module Loaded
*/
extern DECLSPEC HANDLE ELTAPIENTRY ExIsModuleLoaded(const ExChar* file);

#define ExGetFileModule ExIsModuleLoaded
#define ExLoadLibrary ExLoadObject

#ifdef  __cplusplus	// C++ Environment
}
#endif

#endif
