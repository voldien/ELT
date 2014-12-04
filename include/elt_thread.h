/*
===========================================================================
Copyright (C) 2014 BroodCity Software, Inc. Voldemor2009@hotmail.com

*/
#ifndef ELT_THREAD_H
#define ELT_THREAD_H
#include"EngineAssembly.h"
#include"ExNT.h"
#if defined(EX_WINDOWS)
	#define ExSleep Sleep
#elif defined(EX_LINUX)

	#define ExSleep sleep
#elif defined(EX_MAC)
	#define ExSleep sleep
#endif

#ifdef  __cplusplus	// C++ Environment
extern "C"{
#endif
/*
	// Thread Priority
*/
#define EX_THREAD_PRIORITY_LOW 0x1
#define EX_THREAD_PRIORITY_MEDIUM 0x2
#define EX_THREAD_PRIORITY_HIGH 0x3
/*
	// Create thread
*/
extern DECLSPEC ExThread ELTAPIENTRY ExCreateThread(thread_routine callback,void* lpParamater,Uint32* pid);
/*
	// Deatch thread
*/
extern DECLSPEC ERESULT ELTAPIENTRY ExDetachThread(ExThread thread);
/*
	//
*/
extern DECLSPEC void ExLockThread(ExThread thread);
/*
	// Get Thread ID
*/
extern DECLSPEC Uint32 ELTAPIENTRY ExGetThreadID(ExThread thread);
/*
	// Get Thread name
*/
extern DECLSPEC const char* ELTAPIENTRY ExGetThreadName(ExThread thread);
/*
	// 
*/
extern DECLSPEC ERESULT ELTAPIENTRY ExSetThreadPriority(ExThread thread,Enum nPriority);
/*
	// wait the thread
*/
extern DECLSPEC ERESULT ELTAPIENTRY ExWaitThread(ExThread thread, Int32* status);

#ifdef  __cplusplus	// C++ Environment
}
#endif

#endif
