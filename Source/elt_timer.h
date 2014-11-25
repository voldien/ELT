/*
===========================================================================
Copyright (C) 2014 BroodCity Software, Inc. Voldemor2009@hotmail.com

*/
#ifndef ELT_TIMER_H
#define ELT_TIMER_H
#include"elt_thread.h"
#ifdef __cplusplus
	#include<ctime>
#else
	#include<time.h>
#endif

#ifdef EX_WINDOWS
	#define ExCurrentTime timeGetTime	// Get Current Time 
#elif defined(EX_LINUX) || defined(EX_UNIX)
	#define ExCurrentTime(x) time(NULL)	// Get Current Time
#endif

#ifdef __cplusplus	// C++ Environment
extern "C"{
#endif

/*
	// Add Timer
*/
extern DECLSPEC Uint32 ELTAPIENTRY ExAddTimer(Uint32 interval, thread_routine callback, void* param);
/*
	// Remove Timer
*/
extern DECLSPEC Boolean ELTAPIENTRY ExRemoveTimer(Uint32 timer_id);
/*
	//	delay current thread.
*/	
extern DECLSPEC void ELTAPIENTRY ExDelay(Uint32 ms);
/*
	//	Get performance counter
*/
extern DECLSPEC Uint64 ELTAPIENTRY ExGetPerformanceCounter(void);
/*
	//
*/
extern DECLSPEC Uint64 ELTAPIENTRY ExGetPerformanceFrequency(void);
/*
	//	Get Ticks sense ELT_TIMER was initlize
*/
extern DECLSPEC Uint32 ELTAPIENTRY ExGetTicks(void);
#ifdef  __cplusplus	// C++ Environment
}
#endif
#endif
