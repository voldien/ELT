/*
========================================================================
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
#ifndef ELT_THREAD_H_ 1
#define ELT_THREAD_H_ 1
#include"EngineAssembly.h"
#include"ExNT.h"
#if defined(EX_WINDOWS)
	#define ExSleep Sleep
#elif defined(EX_LINUX)
	#define ExSleep usleep
#elif defined(EX_MAC)
	#define ExSleep usleep
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
/**
	Create thread.
	\callback function to invoke
	\lpParameter
*/
extern DECLSPEC ExThread ELTAPIENTRY ExCreateThread(thread_routine callback,void* lpParamater,Uint32* pid);

extern DECLSPEC ExThread ELTAPIENTRY ExCreateThreadAffinity(thread_routine callback,void* lpParamater,Uint32* pid,unsigned int core);
/**
	Detach thread
*/
extern DECLSPEC ERESULT ELTAPIENTRY ExDetachThread(ExThread thread);
/*
*/
extern DECLSPEC ERESULT ELTAPIENTRY ExExitThread(ExThread thread);

/**
	Lock Thread
*/
extern DECLSPEC void ELTAPIENTRY ExLockThread(ExThread thread);

/**
    UnLock thread
*/
extern DECLSPEC void ELTAPIENTRY ExUnLockThread(ExThread thread);

/**
    Get current thread identification.
*/
extern DECLSPEC ExThread ELTAPIENTRY ExGetCurrentThread(void);
/**
	Get Thread ID
*/
extern DECLSPEC Uint32 ELTAPIENTRY ExGetThreadID(ExThread thread);
/**
	Get Thread name
*/
extern DECLSPEC const char* ELTAPIENTRY ExGetThreadName(ExThread thread);
/**
	Set thread priority
*/
extern DECLSPEC ERESULT ELTAPIENTRY ExSetThreadPriority(ExThread thread,Enum nPriority);
/**
	Wait the thread
*/
extern DECLSPEC ERESULT ELTAPIENTRY ExWaitThread(ExThread thread, Int32* status);

#ifdef  __cplusplus	// C++ Environment
}
#endif

#endif
