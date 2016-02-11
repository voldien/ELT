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
#ifndef _ELT_THREAD_H_
#define _ELT_THREAD_H_ 1
#include"EngineAssembly.h"
#include"ExNT.h"

#if defined(EX_WINDOWS)
	#define ExSleep Sleep
#elif defined(EX_LINUX) || defined(EX_ANDROID)
	#define ExSleep usleep
#endif

#ifdef __cplusplus	/*	C++ Environment	*/
extern "C"{
#endif

/*
 *	Thread Priority
 */
#define EX_THREAD_PRIORITY_LOW 0x1
#define EX_THREAD_PRIORITY_MEDIUM 0x2
#define EX_THREAD_PRIORITY_HIGH 0x3


/*
 *	Create thread.
 *	\callback function to invoke
 *	\lpParameter
 *	@return thread handle.
 */
extern ELTDECLSPEC ExThread ELTAPIENTRY ExCreateThread(thread_routine callback, void* lpParamater, Uint32* pid);

/*
 *    Create Thread with affinity mask.
 *    @return thread handle.
 */
extern ELTDECLSPEC ExThread ELTAPIENTRY ExCreateThreadAffinity(thread_routine callback, ExHandle lpParamater, Uint32* pid, Int32 core);

/*
 *	Detach thread
 */
extern ELTDECLSPEC ERESULT ELTAPIENTRY ExDetachThread(ExThread thread);


/**/
extern ELTDECLSPEC void ELTAPIENTRY ExTerminateThread(ExThread thread);

/*
	\thread is the thread of the current thread.
	TODO check if to replace  this function with ExTerminateThread.
*/
extern ELTDECLSPEC ERESULT ELTAPIENTRY ExExitThread(ExThread thread);

/**
	Lock Thread
*/
extern ELTDECLSPEC void ELTAPIENTRY ExLockThread(ExThread thread);

/**
    UnLock thread
    @return
*/
extern ELTDECLSPEC void ELTAPIENTRY ExUnLockThread(ExThread thread);

/**/
extern ELTDECLSPEC void ELTAPIENTRY ExSuspendThread(ExThread thread);


/**/
extern ELTDECLSPEC void ELTAPIENTRY ExResumeThread(ExThread thread);


/**/
extern ELTDECLSPEC void ELTAPIENTRY ExCreateThreadCondition(void);

/*
 *	Get current thread identification.
 *	@return current thread handle.
 */
extern ELTDECLSPEC ExThread ELTAPIENTRY ExGetCurrentThread(void);

/*
 *	Get Thread ID
 *	@return
 */
extern ELTDECLSPEC Uint32 ELTAPIENTRY ExGetThreadID(ExThread thread);

/*
 *	Get Thread name by the invoked function.
 *	@return get function name.
 */
extern ELTDECLSPEC const char* ELTAPIENTRY ExGetThreadName(ExThread thread);

/*
 *	Set thread priority
 *	@return
 */
extern ELTDECLSPEC ERESULT ELTAPIENTRY ExSetThreadPriority(ExThread thread, Enum nPriority);

/*
 *	Wait the thread
 *	@return
 */
extern ELTDECLSPEC ERESULT ELTAPIENTRY ExWaitThread(ExThread thread, Int32* status);

#ifdef __cplusplus	/*	C++ Environment	*/
}
#endif

#endif
