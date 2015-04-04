#include"elt_thread.h"

#ifdef EX_WINDOWS           /*  Windows */
#   define EX_START_THREAD(x)	ResumeThread( ( x ) )
#elif defined(EX_LINUX) || defined(EX_ANDROID)    /*  Linux & android  */
#   define _GNU_SOURCE
#   define __USE_GNU
#   include<pthread.h>
#   include<errno.h>
#   include<unistd.h>
#   include <sched.h>
#   include <stdlib.h>
#   include <unistd.h>
#   include <stdio.h>
#   include <assert.h>
#   define EX_START_THREAD(x)	pthread_detach( ( x ))  /*TODO change*/
#elif defined(EX_MAC)

#endif
#include<signal.h>

//http://pubs.opengroup.org/onlinepubs/7908799/xsh/pthread.h.html

DECLSPEC ExThread ELTAPIENTRY ExCreateThread(thread_routine callback,void* lpParamater,Uint32* pid){
#ifdef EX_WINDOWS
	DWORD p_id;
	HANDLE t0;
	if(!(t0 = CreateThread(0,128,(LPTHREAD_START_ROUTINE)callback,lpParamater,0,&p_id))){
		ExIsError(t0);
		return EX_NULL;
	}
	if(!pid)
		*pid = p_id;
	EX_START_THREAD(t0);
	return hnd;
#elif defined(EX_UNIX)
	pthread_t t0;
    pthread_attr_t attr;
    int mpid;

    pthread_attr_init(&attr);
	if((mpid = pthread_create(&t0,&attr, callback,lpParamater)) == -1)
        fprintf(stderr, strerror(errno));

    if(pid)//TODO
        *pid = mpid;
	return t0;
#endif
}


DECLSPEC ExThread ELTAPIENTRY ExCreateThreadAffinity(thread_routine callback,void* lpParamater,Uint32* pid,unsigned int ncore){
#if defined(EX_WINDOWS)
	DWORD p_id;
	HANDLE t0;
	if(!(t0 = CreateThread(0,128,(LPTHREAD_START_ROUTINE)callback,lpParamater,0,&p_id))){
		ExIsError(t0);
		return EX_NULL;
	}
    SetThreadAffinityMask(t0, ncore);
	if(!pid)
		*pid = p_id;
	EX_START_THREAD(t0);
	return t0;
#elif defined(EX_UNIX)
	pthread_t t0;
    pthread_attr_t attr;
    #ifdef EX_LINUX
    cpu_set_t cpus;
    #endif
    int mpid;

    pthread_attr_init(&attr);
#ifdef EX_LINUX    /*  Android don't seem to support */
    CPU_ZERO(&cpus);
    CPU_SET(ncore,&cpus);

    pthread_attr_setaffinity_np(&attr, sizeof(cpu_set_t),&cpus);
#endif

	if((mpid = pthread_create(&t0,&attr, callback,lpParamater)) == -1)
        fprintf(stderr, strerror(errno));

    if(pid)//TODO
        *pid = mpid;
	return t0;
#endif

}

DECLSPEC ERESULT ELTAPIENTRY ExDetachThread(ExThread thread){
#ifdef EX_WINDOWS
	return TerminateThread(thread,0);
#elif defined(EX_UNIX)
    if(pthread_detach(thread) == -1){
        fprintf(stderr, strerror(errno));
        return 0;
    }
	return 1;
#endif
}
DECLSPEC ERESULT ELTAPIENTRY ExExitThread(ExThread thread){
#ifdef EX_WINDOWS
	return TerminateThread(thread,NULL);
#elif defined(EX_UNIX)
   return pthread_kill(thread,0);
    //pthread_exit(thread);

#endif
}

DECLSPEC ExThread ELTAPIENTRY ExGetCurrentThread(void){
#ifdef EX_WINDOWS
    return GetCurrentThread();
#elif defined(EX_UNIX)
    return pthread_self();
#endif

}

// Thread
DECLSPEC Uint32 ELTAPIENTRY ExGetThreadID(ExThread thread){
#ifdef EX_WINDOWS
	return GetThreadId(thread);
#elif defined(EX_UNIX)
	return thread;
#endif
}

DECLSPEC const char* ELTAPIENTRY ExGetThreadName(ExThread thread){
#ifdef EX_DEBUG
#ifdef EX_WINDOWS
    return NULL;
#elif defined(EX_UNIX)
    char name[64];
    pthread_getname_np(thread,name,sizeof(name));
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
#elif defined(EX_UNIX)
	struct sched_param param;
	switch(nPriority){
		case EX_THREAD_PRIORITY_LOW:break;
		case EX_THREAD_PRIORITY_MEDIUM:break;
		case EX_THREAD_PRIORITY_HIGH:break;
	}
	return pthread_setschedparam(thread,0,&param);
#endif
}

DECLSPEC ERESULT ELTAPIENTRY ExWaitThread(ExThread thread, Int32* status){
#ifdef EX_WINDOWS
    WaitForSingleObject(thread,INFINITE);
#elif defined(EX_UNIX)
    if(pthread_join(thread,NULL) == -1)
        fprintf(stderr,strerror(errno));
#endif
	return TRUE;
}
