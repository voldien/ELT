#include"elt_timer.h"

#ifdef EX_WINDOWS
	#include<windef.h>
	#include<windows.h>
#elif defined(EX_UNIX)
#	include<errno.h>
#	include<unistd.h>
#	include <sys/time.h>
#endif

#include<time.h>
#include<signal.h>

Uint64 eltTickTime = 0;

#define CLOCKID CLOCK_REALTIME
#define SIG SIGUSR1

DECLSPEC Uint32 ELTAPIENTRY ExAddTimer(Uint32 interval, thread_routine callback, void* param){
	Uint32 pid;
#ifdef EX_WINDOWS
	ExIsWinError(CreateTimerQueueTimer((PHANDLE)&pid,
		0,
		(WAITORTIMERCALLBACK)callback,
		param,
		0,
		interval,
		WT_EXECUTEDEFAULT));
	return pid;
#elif defined(EX_UNIX) && !defined(EX_PNACL)
	timer_t timerid;
	struct sigevent sev;
	struct itimerspec its;
	long long freq_nanosecs;
	sigset_t mask;
	struct sigaction sa;

	printf("Establishing handler for signal %d\n", SIG);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = callback;
	sigemptyset(&sa.sa_mask);
	sigaction(SIG, &sa, NULL);

	sev.sigev_notify = SIGEV_SIGNAL;
	sev.sigev_signo = SIG;
	sev.sigev_value.sival_ptr = &timerid;
	timer_create(CLOCKID, &sev, &timerid);
	/* Start the timer */

	its.it_value.tv_sec = 0;
	its.it_value.tv_nsec = interval * 1000000;
	its.it_interval.tv_sec = its.it_value.tv_sec;
	its.it_interval.tv_nsec = its.it_value.tv_nsec;

	timer_settime(timerid, 0, &its, NULL);;
	return timerid;
#endif

}

DECLSPEC ExBoolean ELTAPIENTRY ExRemoveTimer(Uint32 timer_id){
#ifdef EX_WINDOWS
	ExBoolean error;
	ExIsWinError(error = DeleteTimerQueueTimer(NULL,(HANDLE)timer_id, NULL));
	return error;
#elif defined(EX_UNIX)
    if(timer_delete(timer_id) == -1)
        fprintf(stderr,strerror(errno));
	return 0;
#endif
}

DECLSPEC void ELTAPIENTRY ExDelay(Uint32 ms){
    #ifdef EX_WINDOWS
    Sleep(ms);
#elif defined(EX_UNIX)
    struct timespec tim;
    tim.tv_sec = 0;
    tim.tv_nsec = ms * 1000000;

#ifdef EX_DEBUG
    if(nanosleep(&tim , NULL) < 0 ){
        fprintf(stderr,"errno error code %d\n"" errno");
    }
#else
    nanosleep(&tim , NULL);
#endif
    #endif
}

DECLSPEC void ELTAPIENTRY ExDelayN(Uint32 nanosec){
    #ifdef EX_WINDOWS
    struct timeval tv;  // TODO Does this nano sleep work ?
    tv.tv_sec = nanosec / 1000000000;
    tv.tv_usec = nanosec;
    select(0,0,0,0,&tv);
    #elif defined(EX_UNIX)
    struct timespec tim, tim2;
    tim.tv_sec = 0;
    tim.tv_nsec = nanosec;

#ifdef EX_DEBUG
    if(nanosleep(&tim , NULL) < 0 ){
        fprintf(stderr,"errno error code %d\n"" errno");
    }
#else
    nanosleep(&tim , NULL);
#endif
    #endif
}

DECLSPEC Uint32 ELTAPIENTRY ExGetTicks(void){
#ifdef EX_WINDOWS
	return (timeGetTime() - eltTickTime);  /*  return in milliseconds   */
#elif defined(EX_UNIX)
	return (clock() - eltTickTime);
#endif
}

DECLSPEC long int ELTAPIENTRY ExGetHiResTime(void){
    #ifdef EX_WINDOWS
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	return (long int)time.QuadPart;
#elif defined(EX_UNIX)
	struct timeval tSpec;
    //struct timespec tSpec;

/*    if(clock_gettime(CLOCK_MONOTONIC,&tSpec) < 0){
    	printf("error from ExGetHiResTime : %d", errno);
    	return tSpec.tv_nsec;
    }
*/
    gettimeofday(&tSpec,NULL);

    //clock_gettime(CLOCK_MONOTONIC, &t_spec);
    //return tSpec.tv_usec * 1000;  /*  return time in nano seconds*/
    return (tSpec.tv_sec*1e6 + tSpec.tv_usec) * 1000;
    #endif
}
