#include"elt_timer.h"
#include"system/elt_log.h"

#include<unistd.h>
#include<sys/time.h>
#include<time.h>
#include<signal.h>
#include<errno.h>
#include<string.h>

Uint64 eltTickTime = 0;
#define CLOCKID CLOCK_REALTIME
#define SIG SIGUSR2


ExTimer ExAddTimer(Uint32 ms_interval, ExThreadRoutine callback, void* param){
	Uint32 pid;
	timer_t timerid;
	struct sigevent sev;
	struct itimerspec its;
	long long freq_nanosecs;
	sigset_t mask;
	struct sigaction sa;

	ExPrintf("Establishing handler for signal %d\n", SIG);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = callback;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);

	sev.sigev_notify = SIGEV_SIGNAL;
	sev.sigev_signo = SIGUSR1;
	sev.sigev_value.sival_ptr = &timerid;
	if(timer_create(CLOCKID, &sev, &timerid) < -1)
		return FALSE;

	/* Start the timer */
	its.it_value.tv_sec = 0;
	its.it_value.tv_nsec = ms_interval * 1000000;
	its.it_interval.tv_sec = its.it_value.tv_sec;
	its.it_interval.tv_nsec = its.it_value.tv_nsec;

	if(timer_settime(timerid, 0, &its, NULL) == -1){
		ExPrintfError("timer_settimer error.\n");
	}
	return timerid;
}

ExBoolean ExRemoveTimer(ExTimer timer_id){
    if(timer_delete(timer_id) < -1){
    	ExLogCritical(strerror(errno));
        return FALSE;
    }
	return TRUE;
}

void ExDelay(Uint32 ms){
    struct timespec tim;
    tim.tv_sec = 0;
    tim.tv_nsec = ms * 1E6;

#ifdef EX_DEBUG
    if(nanosleep(&tim , NULL) < 0 ){
        fprintf(stderr,"errno error code %d\n"" errno");
    }
#else
    nanosleep(&tim , NULL);
#endif
}

void ExDelayN(Uint32 nanosec){
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
}

Uint64 ExGetPerformanceFrequency(void){
	struct timespec spec;
	clock_getres(CLOCK_MONOTONIC, &spec);
	return (1E9 / spec.tv_nsec);
}

long int ExGetTicks(void){
	return (clock() - eltTickTime);
}

long int ExGetHiResTime(void){
	struct timeval tSpec;
    gettimeofday(&tSpec, NULL);
    return (tSpec.tv_sec*1e6 + tSpec.tv_usec) * 1000;
}
