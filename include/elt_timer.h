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
#ifndef _ELT_TIMER_H_
#define _ELT_TIMER_H_ 1
#include"elt_thread.h"
#ifdef __cplusplus
	#include<ctime>
#else
	#include<time.h>
#endif

#ifdef EX_WINDOWS
	#define ExCurrentTime timeGetTime	// Get Current Time
#elif defined(EX_LINUX) || defined(EX_UNIX) || defined(EX_ANDROID)
	#define ExCurrentTime(x) time(NULL)	// Get Current Time
#endif

#define ExGetCurrentTimeHiRes clock
#define EX_TICKS_PER_SECOND CLOCKS_PER_SEC

#ifdef __cplusplus	// C++ Environment
extern "C"{
#endif

/**
	Add timer thread routine
	@return timer handle
*/
extern DECLSPEC Uint32 ELTAPIENTRY ExAddTimer(Uint32 interval, thread_routine callback, void* param);
/**
	Remove timer thread routine
	@return if successfully removed
*/
extern DECLSPEC ExBoolean ELTAPIENTRY ExRemoveTimer(Uint32 timer_id);
/**
	Delay current thread in milliseconds.
	\ms milliseconds.
*/
extern DECLSPEC void ELTAPIENTRY ExDelay(Uint32 ms);

/**
	Delay current thread in nano seconds.
*/
extern DECLSPEC void ELTAPIENTRY ExDelayN(Uint32 nanosec);

/**
	Get performance counter
*/
extern DECLSPEC Uint64 ELTAPIENTRY ExGetPerformanceCounter(void);
/**
    Get Performance frequency
*/
extern DECLSPEC Uint64 ELTAPIENTRY ExGetPerformanceFrequency(void);
/**
	Get numbers Ticks sense ELT_TIMER was initialize
	@return
*/
extern DECLSPEC Uint32 ELTAPIENTRY ExGetTicks(void);
/**
	Get numbers Ticks sense ELT_TIMER was initialize
	@return get number of ticks.
*/
extern DECLSPEC long int ELTAPIENTRY ExGetHiResTime(void);

//extern DECLSPEC long int ELTAPIENTRY ExGetTimeMil

/**
    Get in seconds in float. where 1.0 is a second.
*/
#define ExGetSecondsf ((float)ExGetTicks() / (float)EX_TICKS_PER_SECOND)


#ifdef  __cplusplus	// C++ Environment
}
#endif
#endif
