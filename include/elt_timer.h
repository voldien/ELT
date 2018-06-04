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
#ifndef _ELT_TIMER_H_
#define _ELT_TIMER_H_ 1
#include"elt_thread.h"

#ifdef __cplusplus	/*	C++ Environment	*/
extern "C" {
#endif

/**
 *
 */
typedef unsigned int ExTimer;

/**
 *	Add timer thread routine.
 *
 *	\ms_interval
 *	\callback
 *
 *	\param
 *
 *
 *	@Return unique timer id.
 */
extern ELTDECLSPEC ExTimer ELTAPIENTRY ExAddTimer(unsigned int ms_interval,
		ExThreadRoutine callback, void* param);

/**
 *	Remove timer thread routine.
 *
 *	@Return EX_TRUE if successful.
 */
extern ELTDECLSPEC ExBoolean ELTAPIENTRY ExRemoveTimer(ExTimer timer_id);

/**
 *	Delay current thread in milliseconds.
 *
 *	\ms milliseconds.
 */
extern ELTDECLSPEC void ELTAPIENTRY ExDelay(unsigned int ms);

/**
 *	Delay current thread in nano seconds.
 *
 *	\ns
 */
extern ELTDECLSPEC void ELTAPIENTRY ExDelayN(unsigned int nanosec);

/**
 *	Get performance frequency for ExGetHiResTime. That is say
 *	the 1 seconds equal to the frequency.
 *
 *	@Return time resolution.
 */
extern ELTDECLSPEC unsigned long int ELTAPIENTRY ExGetPerformanceFrequency(void);

/**
 *	Get numbers Ticks sense ELT_TIMER was initialize.
 *
 *	@Return
 */
extern ELTDECLSPEC long int ELTAPIENTRY ExGetTicks(void);

/**
 *	Get time in high resolution. Use ExGetPerformanceFrequency
 *	to get the how much precision ExGetHiResTime supports.
 *
 *	@Return Get number of ticks.
 */
extern ELTDECLSPEC long int ELTAPIENTRY ExGetHiResTime(void);

/**
 *	@Return
 */
#define EX_TICKS_PER_SECOND CLOCKS_PER_SEC
extern ELTDECLSPEC long int ELTAPIENTRY ExCurrentTime(void);

#ifdef __cplusplus	/*	C++ Environment	*/
}
#endif
#endif	/*	_ELT_TIMER_H_	*/
