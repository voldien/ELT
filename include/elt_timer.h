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

#define ExCurrentTime clock
#define EX_TICKS_PER_SECOND CLOCKS_PER_SEC

#ifdef __cplusplus	/*	C++ Environment	*/
extern "C"{
#endif
typedef Uint32 ExTimer;

/*
 *	Add timer thread routine.
 *	@Return .
 */
extern ELTDECLSPEC ExTimer ELTAPIENTRY ExAddTimer(Uint32 ms_interval, ExThreadRoutine callback, void* param);

/*
 *	Remove timer thread routine.
 *	@Return TRUE if successful.
 */
extern ELTDECLSPEC ExBoolean ELTAPIENTRY ExRemoveTimer(ExTimer timer_id);
/*
 *	Delay current thread in milliseconds.
 *	\ms milliseconds.
 */
extern ELTDECLSPEC void ELTAPIENTRY ExDelay(Uint32 ms);

/*
 *	Delay current thread in nano seconds.
 *	\ns
 */
extern ELTDECLSPEC void ELTAPIENTRY ExDelayN(Uint32 nanosec);

/*
 *	Get performance counter
 *	@Return
 */
extern ELTDECLSPEC Uint64 ELTAPIENTRY ExGetPerformanceCounter(void);	/*	TODO remove, as GetHiResTime does the same thing!.	*/

/*
 *	Get Performance frequency
 *	@Return
 */
extern ELTDECLSPEC Uint64 ELTAPIENTRY ExGetPerformanceFrequency(void);

/*
 *	Get numbers Ticks sense ELT_TIMER was initialize
 *	@Return
 */
extern ELTDECLSPEC long int ELTAPIENTRY ExGetTicks(void);

/*
 *
 *	@Return get number of ticks.
 */
extern ELTDECLSPEC long int ELTAPIENTRY ExGetHiResTime(void);

//extern ELTDECLSPEC long int ELTAPIENTRY ExGetTimeMil


/**
    Get in seconds in float. where 1.0 is a second.
*/
#define ExGetSecondsf ((float)ExGetTicks() / (float)EX_TICKS_PER_SECOND)


#ifdef __cplusplus	/*	C++ Environment	*/
}
#endif
#endif
