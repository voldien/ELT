#include"elt_thread.h"

#ifdef EX_WINDOWS
	#define EX_START_THREAD(x)	ResumeThread( ( x ) )
#elif defined(EX_LINUX)
	#include<pthread.h>
	#define EX_START_THREAD(x)	pthread_join( ( x ) ,EX_NULL)
#elif defined(EX_MAC)
#endif

//http://pubs.opengroup.org/onlinepubs/7908799/xsh/pthread.h.html

DECLSPEC ExThread ELTAPIENTRY ExCreateThread(thread_routine callback,void* lpParamater,Uint32* pid){
#ifdef EX_WINDOWS
	DWORD p_id;
	HANDLE hnd;
	if(!(hnd = CreateThread(0,128,(LPTHREAD_START_ROUTINE)callback,lpParamater,0,&p_id))){
		ExIsError(hnd);
		return EX_NULL;
	}
	if(!pid)
		*pid = p_id;
	EX_START_THREAD(hnd);
	return hnd;
#else
	pthread_t t0;
	Uint mpid;
	if(!(mpid = pthread_create(&t0,NULL, callback,lpParamater)))
		Error("Failed to Create Thread.");
	EX_START_THREAD(t0);
	return t0;
#endif
}

DECLSPEC ERESULT ELTAPIENTRY ExDetachThread(ExThread thread){
#ifdef EX_WINDOWS
	return TerminateThread(thread,0);
#elif defined(EX_LINUX)
	return pthread_detach(thread);
#endif
}
// Thread
DECLSPEC Uint32 ELTAPIENTRY ExGetThreadID(ExThread thread){
#ifdef EX_WINDOWS
	return GetThreadId(thread);
#elif defined(EX_LINUX)
	return 0;
#endif
}

DECLSPEC const char* ELTAPIENTRY ExGetThreadName(ExThread thread){
#ifdef EX_DEBUG
#ifdef EX_WINDOWS

#elif defined(EX_LINUX)

    char name[64];
    pthread_getname_np(thread,name);
	return name;
#endif
#endif
}

DECLSPEC ERESULT ELTAPIENTRY ExSetThreadPriority(ExThread thread,Enum nPriority){
	if(!thread)return FALSE;
#ifdef EX_WINDOWS
	switch(nPriority){
		case EX_THREAD_PRIORITY_LOW:nPriority =THREAD_PRIORITY_LOWEST;break;
		case EX_THREAD_PRIORITY_MEDIUM:nPriority = THREAD_PRIORITY_NORMAL;break;
		case EX_THREAD_PRIORITY_HIGH:nPriority = THREAD_PRIORITY_HIGHEST;break;
		default:break;
	}
	return SetThreadPriority(thread,nPriority);
#elif defined(EX_LINUX)
	struct sched_param param;
	switch(nPriority){
		case EX_THREAD_PRIORITY_LOW:
		case EX_THREAD_PRIORITY_MEDIUM:
		case EX_THREAD_PRIORITY_HIGH:break;
	}
	return pthread_setschedparam(thread,0,&param);
#endif
}

DECLSPEC ERESULT ELTAPIENTRY ExWaitThread(ExThread thread, Int32* status){
#ifdef EX_WINDOWS

#endif
	return 0;
}
