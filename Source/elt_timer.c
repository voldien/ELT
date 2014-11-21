#include"elt_timer.h"
#include<signal.h>

Uint32 elt_time = 0;

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
#elif defined(EX_LINUX)
    timer_t timerid;
	struct sigevent sev;
	struct sigaction sa;
    struct itimerspec its;
	long long freq_nanosecs;
	sigset_t mask;


    #define SIG SIGRTMIN
	sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = callback;
    sigemptyset(&sa.sa_mask);
    if(sigaction(SIG,&sa, NULL) == -1)
        ExError("sigaction");

    //sigem
    sigemptyset(&mask);
    sigaddset(&mask, SIG);
    if (sigprocmask(SIG_SETMASK, &mask, NULL) == -1)
        ExError("sigprocmask");

	sev.sigev_notify = SIGEV_SIGNAL;
	sev.sigev_signo = SIG;
	sev.sigev_value.sival_ptr = &timerid;

	if(timer_create(CLOCK_REALTIME,&sev,&timerid) == -1)
		ExDevPrint("error");

    freq_nanosecs = interval * 100000000;
    its.it_value.tv_sec = freq_nanosecs / 1000000000;
    its.it_value.tv_nsec = freq_nanosecs % 100000000;
    its.it_interval.tv_sec = its.it_value.tv_sec;
    its.it_interval.tv_nsec = its.it_value.tv_nsec;

    if(timer_settime(timerid,0,&its,NULL) == -1)
        ExError("timer_settime");
    if (sigprocmask(SIG_UNBLOCK, &mask, NULL) == -1)
               ExError("sigprocmask");


#endif
	return pid;
}
DECLSPEC Boolean ELTAPIENTRY ExRemoveTimer(Uint32 timer_id){
#ifdef EX_WINDOWS
	Boolean error;
	ExIsWinError(error = DeleteTimerQueueTimer(EX_NULL,(HANDLE)timer_id, EX_NULL));
	return error;
#elif defined(EX_LINUX)

	return 0;
#endif
}

DECLSPEC void ELTAPIENTRY ExDelay(Uint32 ms){
	ExSleep(ms);
}

DECLSPEC Uint32 ELTAPIENTRY ExGetTicks(void){
#ifdef EX_WINDOWS
	return (timeGetTime() - elt_time);
#elif defined(EX_LINUX)
	return (time(NULL) - elt_time);
#endif
}
