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
	struct sigevent sev;
	struct sigaction sa;

	sa.sa_flags = SA_SIGINFO;

	sev.sigev_notify = SIGEV_SIGNAL;
	sev.sigev_signo = interval;
	sev.sigev_value.sival_ptr = &pid;

	//if(timer_create(CLOCK_REALTIME,&sev,&pid) == -1)
	//	ExDevPrint("error");
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
