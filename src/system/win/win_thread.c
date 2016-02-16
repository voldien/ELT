#include"elt_thread.h"
#include<windows.h>


ELTDECLSPEC ExThread ELTAPIENTRY ExCreateThread(thread_routine callback, void* lpParamater, Uint32* pid){
	DWORD p_id;
	ExHandle t0;
	if(!(t0 = CreateThread(0,128,(LPTHREAD_START_ROUTINE)callback, (LPVOID)lpParamater, 0, &p_id))){
		ExIsError(t0);
		return NULL;
	}
	if(!pid)
		*pid = p_id;
	EX_START_THREAD(t0);
	return t0;
}


ELTDECLSPEC ExThread ELTAPIENTRY ExCreateThreadAffinity(thread_routine callback, ExHandle lpParamater, Uint32* pid, Int32 ncore){
	DWORD p_id;
	ExHandle t0;
	if(!(t0 = CreateThread(0,128,(LPTHREAD_START_ROUTINE)callback, (LPVOID)lpParamater, 0, &p_id))){
		ExIsError(t0);
		return NULL;
	}
    SetThreadAffinityMask(t0, ncore);
	if(!pid)
		*pid = p_id;
	EX_START_THREAD(t0);
	return t0;
}

ELTDECLSPEC ERESULT ELTAPIENTRY ExDetachThread(ExThread thread){
	return TerminateThread(thread,0);
}










ELTDECLSPEC ERESULT ELTAPIENTRY ExWaitThread(ExThread thread, Int32* status){
    return WaitForSingleObject(thread, INFINITE);
}
