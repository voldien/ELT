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
#include"elt_def.h"
#include"ExNT.h"
#include"elt_mutex.h"

#ifdef __cplusplus	/*	C++ Environment	*/
extern "C"{
#endif

typedef void* ExThreadContition;

/**
 *	Thread Priority.
 */
#define EX_THREAD_PRIORITY_LOW 0x1
#define EX_THREAD_PRIORITY_MEDIUM 0x2
#define EX_THREAD_PRIORITY_HIGH 0x3


/**
 *	Create thread.
 *
 *	\callback function to invoke
 *
 *	\lpParameter
 *
 *	@Return thread handle.
 */
extern ELTDECLSPEC ExThread ELTAPIENTRY ExCreateThread(ExThreadRoutine callback, void* lpParamater, Uint32* pid);

/**
 * 	Create Thread with affinity mask.
 *
 *	\callback
 *
 *	@Return thread handle.
 */
extern ELTDECLSPEC ExThread ELTAPIENTRY ExCreateThreadAffinity(ExThreadRoutine callback, ExHandle lpParamater, Uint32* pid, Int32 core);

/**
 *	Detach thread
 *
 *	@Return
 */
extern ELTDECLSPEC ERESULT ELTAPIENTRY ExDetachThread(ExThread thread);


/**
 *	Send signal to thread to terminate.
 */
extern ELTDECLSPEC void ELTAPIENTRY ExTerminateThread(ExThread thread);

/**
 *	\thread is the thread of the current thread.
 */
extern ELTDECLSPEC void ELTAPIENTRY ExThreadExit(void* parg);

/**/
extern ELTDECLSPEC void ELTAPIENTRY ExSuspendThread(ExThread thread);

/**/
extern ELTDECLSPEC void ELTAPIENTRY ExResumeThread(ExThread thread);


/**/
extern ELTDECLSPEC void ELTAPIENTRY ExSetThreadSignal(ExThread thread, Uint signal);
extern ELTDECLSPEC Uint ELTAPIENTRY ExGetThreadSignal(ExThread thread);


/**/
extern ELTDECLSPEC void ELTAPIENTRY ExCreateThreadCondition(void);
extern ELTDECLSPEC void ELTAPIENTRY ExDestroyThreadCondition(void);

/**/
extern ELTDECLSPEC void ELTAPIENTRY ExThreadCondWait(ExThreadContition cond);
extern ELTDECLSPEC void ELTAPIENTRY ExThreadCondBroadcast(ExThreadContition cond);


/**
 *	Get current thread identification.
 *
 *	@Return current thread handle.
 */
extern ELTDECLSPEC ExThread ELTAPIENTRY ExGetCurrentThread(void);

/**
 *	Get Thread ID.
 *
 *	@Return
 */
extern ELTDECLSPEC Uint32 ELTAPIENTRY ExGetThreadID(ExThread thread);


/**
 *	Get Thread name by the invoked function.
 *
 *	@Return get function name.
 */
extern ELTDECLSPEC const ExChar* ELTAPIENTRY ExGetThreadName(ExThread thread);

/**
 *
 */
extern ELTDECLSPEC void ELTAPIENTRY ExSetThreadName(ExThread thread, const ExChar* name);


/**
 *	Set thread priority
 *	@Return
 */
extern ELTDECLSPEC ERESULT ELTAPIENTRY ExSetThreadPriority(ExThread thread, Enum nPriority);

/**
 *
 */
extern ELTDECLSPEC ERESULT ELTAPIENTRY ExSetThreadState(ExThread thread, ExHandle* handle);
extern ELTDECLSPEC ExHandle ELTAPIENTRY ExGetThreadState(ExThread thread);

/**
 *	Wait the thread to be terminated.
 *
 *	\thread
 *
 *	@Return
 */
extern ELTDECLSPEC ERESULT ELTAPIENTRY ExWaitThread(ExThread thread, Int32* status);


/**
 *	@Return cpu core index of current thread.
 */
extern ELTDECLSPEC int ELTAPIENTRY ExGetCPUID(void);

#if defined(EX_WINDOWS)
	#define ExSleep Sleep
#elif defined(EX_LINUX) || defined(EX_ANDROID)
	#define ExSleep usleep
#endif
#ifdef __cplusplus	/*	C++ Environment	*/
}
#endif

#endif
