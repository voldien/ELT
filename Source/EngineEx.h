/*
===========================================================================
Copyright (C) 2014 BroodCity Software, Inc. Voldemor2009@hotmail.com

*/
#ifndef _ENGINE_EX_H
#define _ENGINE_EX_H
#include"EngineAssembly.h"

#define EX_DEVELOPER_EMAIL EX_TEXT("BroodCity@hotmail.com")
#define EX_VENDOR EX_TEXT("BroodCity")

/*
	// Developer information
*/

#ifdef __cplusplus // C++ environment
extern "C"{
#endif

/*
	// Initialization of ELT Engine Library ToolKit
*/
extern DECLSPEC ERESULT ELTAPIENTRY ExInit(Uint32 engineFlag);
/*
	// Initialize specific subsystems
*/
extern DECLSPEC ERESULT ELTAPIENTRY ExInitSubSystem(Uint32 engineFlag);
/*
	// Shut Down Function ELT
*/
extern DECLSPEC void ELTAPIENTRY ExShutDown(void);
#define ExQuit ExShutDown
/*
	// Quit Sub System
*/
extern DECLSPEC void ELTAPIENTRY ExQuitSubSytem(Uint32 engineflag);
/*
	//EngineEx Enable
*/
extern DECLSPEC void ELTAPIENTRY ExEnable(Enum enable);
/*
	//EngineEx Disable
*/
extern DECLSPEC void ELTAPIENTRY ExDisable(Enum disable);
/*
	// Get ELT Version
*/
extern DECLSPEC const ExChar* ELTAPIENTRY ExGetVersion(void);
extern DECLSPEC const ExChar* ELTAPIENTRY ExGetCompilerName(void);
/*
	// print information about the ELT framework
*/
extern DECLSPEC void ELTAPIENTRY ExDevInternalPrint(void);

extern char* Developer;
#ifdef __cplusplus // C++ environment
}
#endif
#endif
