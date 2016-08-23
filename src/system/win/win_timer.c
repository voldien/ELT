#include"elt_timer.h"

#include<windef.h>
#include<windows.h>
#include<sys/time.h>

#include<time.h>
#include<signal.h>

Uint64 eltTickTime = 0;

#define CLOCKID CLOCK_REALTIME
#define SIG SIGUSR2


Uint32 ExAddTimer(Uint32 interval, thread_routine callback, void* param){
	Uint32 pid;
	ExIsWinError(CreateTimerQueueTimer((PHANDLE)&pid,
		0,
		(WAITORTIMERCALLBACK)callback,
		param,
		0,
		interval,
		WT_EXECUTEDEFAULT));
	return pid;

}

ExBoolean ExRemoveTimer(Uint32 timer_id){
	ExBoolean error;
	ExIsWinError(error = DeleteTimerQueueTimer(NULL,(HANDLE)timer_id, NULL));
	return error;
}

void ExDelay(Uint32 ms){
    Sleep(ms);
}

void ExDelayN(Uint32 nanosec){
    struct timeval tv;  	// TODO Does this nano sleep work ?
    tv.tv_sec = nanosec / 1000000000;
    tv.tv_usec = nanosec;
    select(0,0,0,0,&tv);

}

long int ExGetTicks(void){
	return (timeGetTime() - eltTickTime);  /*  return in milliseconds   */

}

long int ExGetHiResTime(void){
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	return (long int)time.QuadPart;
}


long int ExCurrentTime(void){
	return timeGetTime();
}
