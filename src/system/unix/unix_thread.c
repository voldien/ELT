#include"elt_thread.h"
#include"elt_def.h"

#define _MULTI_THREADED
#   define _GNU_SOURCE
#   define __USE_GNU
#	include <pthread.h>
#	include <stdio.h>
#	include <sys/signal.h>
#   include<errno.h>
#   include<unistd.h>
#   include <sched.h>
#   include <stdlib.h>
#   include <unistd.h>
#   include <stdio.h>
#   include <assert.h>
#   define EX_START_THREAD(x)	pthread_detach( ( x ))  /*TODO change*/

#include<signal.h>
#include<string.h>


/*	TODO resolve the evaluate of the implementation.	*/
#define SIGNAL_MASK_ID_KEY 0xfff


ExThread ExCreateThread(ExThreadRoutine callback, void* lpParamater, Uint32* pid){
	pthread_t t0;
    pthread_attr_t attr;
    sigset_t mask;
    int mpid;

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	if((mpid = pthread_create(&t0, &attr, callback,lpParamater)) == -1){
		ExPrintfError(strerror(errno));
	}

	/*
    sigemptyset(&mask);
    for (i = 0; sig_list[i]; ++i) {
        sigaddset(&mask, sig_list[i]);
    }
    pthread_sigmask(SIG_BLOCK, &mask, 0);
    */

	pthread_attr_destroy(&attr);
	if(pid)//TODO
		*pid = mpid;
	return t0;
}

ExThread ExCreateThreadAffinity(ExThreadRoutine callback, ExHandle lpParamater, Uint32* pid, Int32 ncore){
	pthread_t t0;
	pthread_attr_t attr;
#if !defined(EX_ANDROID) && !defined(EX_PNACL) && !defined(EX_NACL)      /*  Android don't seem to support */
	cpu_set_t cpus;
#endif
	int mpid;

	pthread_attr_init(&attr);
#if !defined(EX_ANDROID) && !defined(EX_PNACL) && !defined(EX_NACL)      /*  Android don't seem to support */
	CPU_ZERO(&cpus);
	CPU_SET(ncore,&cpus);

	pthread_attr_setaffinity_np(&attr, sizeof(cpu_set_t),&cpus);
#endif

	if((mpid = pthread_create(&t0, &attr, callback, lpParamater)) == -1){
		ExPrintfError(stderr, strerror(errno));
	}

	pthread_attr_destroy(&attr);

	if(pid)//TODO
		*pid = mpid;
	return t0;
}


ERESULT ExDetachThread(ExThread thread){
    if(pthread_detach(thread) == -1){
    	ExPrintfError(stderr, strerror(errno));
        return FALSE;
    }
	return TRUE;
}


void ExTerminateThread(ExThread thread){
	pthread_cancel(thread);
}


void ExThreadExit(void* __retval){
	pthread_exit(__retval);
}


void ExSuspendThread(ExThread thread){
	//pthread_suspend_np(thread);
	ExLockMutex(NULL);
	//m_suspendFlag = 1;
	ExUnLockMutex(NULL);
}

void ExResumeThread(ExThread thread){
	ExLockMutex(NULL);
	//m_suspendflag = 0;
	//ExThreadCondBroadcast(NULL);
	ExUnLockMutex(NULL);

}

void ExSetThreadSignal(ExThread thread, Uint signal){
	pthread_kill(thread, signal);
}


Uint ExGetThreadSignal(ExThread thread){
//	int signal;
//	sigset_t* set = pthread_getspecific(SIGNAL_MASK_ID_KEY);
//	if(sigwait(set, &signal) != 0){
//
//	}
//	return signal;
}





ExThread ExGetCurrentThread(void){
    return pthread_self();
}













Uint32 ExGetThreadID(ExThread thread){
	//pthread_id_np_t tid;
	//pthread_getunique_np(thread, &tid);
	//return tid;
}


#define MAX_THREAD_NAME 16
const ExChar* ExGetThreadName(ExThread thread){
	char name[MAX_THREAD_NAME];
	pthread_getname_np(thread, name, sizeof(name));
	return name;
}

void ExSetThreadName(ExThread thread, const ExChar* name){
	int status;

	if(strlen(name) > MAX_THREAD_NAME - 1){

	}
	status = pthread_setname_np(thread, name);
	if(status == ERANGE){
		ExLogCritical("%s\n", strerror(errno));
	}
}

ERESULT ExSetThreadPriority(ExThread thread, Enum nPriority){
	struct sched_param sch;
	int policy;
	if(pthread_getschedparam(thread, &policy, &sch) < 0){

	}

	switch(nPriority){
		case EX_THREAD_PRIORITY_LOW:
			sch.__sched_priority = sched_get_priority_min(&policy);
			pthread_setschedprio(thread, 2);
			break;
		case EX_THREAD_PRIORITY_MEDIUM:
			sch.__sched_priority = sched_get_priority_min(&policy);
			pthread_setschedprio(thread, 1);
			break;
		case EX_THREAD_PRIORITY_HIGH:
			sch.__sched_priority = sched_get_priority_max(&policy);
			pthread_setschedprio(thread, 0);
			break;
		default:{
			int max_prio = sched_get_priority_max(policy);
			int min_prio = sched_get_priority_min(policy);
			sch.__sched_priority = (min_prio + (max_prio - min_prio) * 0.5);
		}
	}

	if(pthread_setschedparam(thread, policy, &sch) < 0){
		ExLogCritical("%s\n", strerror(errno));
	}
	return E_OK;
}

ERESULT ExWaitThread(ExThread thread, Int32* status){
    if(pthread_join(thread, &status) < 0){
    	ExLogCritical("%s\n", strerror(errno));
        return FALSE;
    }
	return E_OK;
}









