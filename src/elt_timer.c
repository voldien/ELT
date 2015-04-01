#include"elt_timer.h"
#include<time.h>
#include<signal.h>
#ifdef EX_WINDOWS
#   include<WinBase.h>
#elif defined(EX_LINUX) || defined(EX_ANDROID)
#   include<errno.h>
#endif // EX_WINDOWS

Uint64 elt_time = 0;

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
#elif defined(EX_LINUX) || defined(EX_ANDROID)
    timer_t timerid;
	struct sigevent sev = {0};;
	struct sigaction sa;
    struct itimerspec its;
    struct itimerspec itval, oitval;
	long long freq_nanosecs;
	sigset_t mask;

    #define SIG SIGRTMIN
	sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = callback;
    sigemptyset(&sa.sa_mask);
    if(sigaction(SIGRTMAX,&sa, NULL) == -1)
        fprintf(stderr,strerror(errno));

	sev.sigev_notify = SIGEV_SIGNAL;
	sev.sigev_signo = SIGRTMAX;
	sev.sigev_value.sival_ptr = &timerid;

	if(timer_create(CLOCK_REALTIME,&sev,&timerid) == -1)
        fprintf(stderr,strerror(errno));

    freq_nanosecs = interval * 1000;
    /*its.it_value.tv_sec = freq_nanosecs / 1000000000;
    its.it_value.tv_nsec = freq_nanosecs % 100000000;
    its.it_interval.tv_sec = its.it_value.tv_sec;
    its.it_interval.tv_nsec = its.it_value.tv_nsec;*/
    its.it_value.tv_nsec = freq_nanosecs;
    its.it_interval.tv_sec = 0;
    its.it_interval.tv_nsec = 0;

    if(timer_settime(timerid,0,&its,&oitval) == -1)
        fprintf(stderr,strerror(errno));
	return timerid;
#endif

}
DECLSPEC ExBoolean ELTAPIENTRY ExRemoveTimer(Uint32 timer_id){
#ifdef EX_WINDOWS
	ExBoolean error;
	ExIsWinError(error = DeleteTimerQueueTimer(EX_NULL,(HANDLE)timer_id, EX_NULL));
	return error;
#elif defined(EX_LINUX) || defined(EX_ANDROID)
    if(timer_delete(timer_id) == -1)
        fprintf(stderr,strerror(errno));
	return 0;
#endif
}

DECLSPEC void ELTAPIENTRY ExDelay(Uint32 ms){
    #ifdef EX_WINDOWS
    Sleep(ms);
#elif defined(EX_LINUX) || defined(EX_ANDROID)
    struct timespec tim, tim2;
    tim.tv_sec = 0;
    tim.tv_nsec = ms * 1000000;

    if(nanosleep(&tim , NULL) < 0 ){
        fprintf(stderr, strerror(errno));
    }
    #endif
}
DECLSPEC void ELTAPIENTRY ExDelayN(Uint32 nano_sec){
    #ifdef EX_WINDOWS
    struct timeval tv;  // TODO Does this nano sleep work ?
    tv.tv_sec = nano_sec / 1000000000;
    tv.tv_usec = nano_sec;
    select(0,0,0,0,&tv);
    #elif defined(EX_LINUX) || defined(EX_ANDROID)
    struct timespec tim, tim2;
    tim.tv_sec = 0;
    tim.tv_nsec = nano_sec;

    if(nanosleep(&tim , NULL) < 0 ){
        fprintf(stderr, strerror(errno));
    }
    #endif
}

DECLSPEC Uint32 ELTAPIENTRY ExGetTicks(void){/*TODO fix high res-resolution*/
#ifdef EX_WINDOWS
	return (timeGetTime() - elt_time);  /*  return in milliseconds   */
#elif defined(EX_LINUX) || defined(EX_ANDROID)
	return (clock() - elt_time);
#endif
}
DECLSPEC long int ELTAPIENTRY ExGetHiResTime(void){
    #ifdef EX_WINDOWS

	return 0;
#elif defined(EX_LINUX) || defined(EX_ANDROID)
    struct timespec t_spec;
    clock_gettime(CLOCK_MONOTONIC, &t_spec);
    return t_spec.tv_nsec;  /*  return time in nano seconds*/
    #endif // EX_WINDOWS
}
