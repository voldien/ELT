#include"elt_alloc.h"
#ifdef EX_WINDOWS
#	include<windows.h>
#   include<psapi.h>
#elif defined(EX_UNIX)
#   include<unistd.h>
#endif

DECLSPEC int ELTAPIENTRY ExGetPageSize(void){
    #ifdef EX_WINDOWS
	PERFORMANCE_INFORMATION erformance_info;
	GetPerformanceInfo(&erformance_info,sizeof(PERFORMANCE_INFORMATION));
	return erformance_info.PageSize;
    #elif defined(EX_UNIX)
	long sz = sysconf(_SC_PAGESIZE);
	return sz;
    #endif
}


DECLSPEC ExPoolAllactor* ELTAPIENTRY ExPoolCreate(unsigned int num, unsigned int itemsize){
	ExPoolAllactor* alloc;
	ExPoolAllactor* tmp;
	unsigned int i;
	alloc = malloc(num * (itemsize + sizeof(ExPoolAllactor)));

	if(!alloc)
		return 0;

	/*	create pool chain.*/
	tmp = alloc;
	for(i = 0; i < num; i++){
		tmp->next = tmp + sizeof(ExPoolAllactor) + itemsize;
		tmp += sizeof(ExPoolAllactor) + itemsize;
		continue;
	}

	/*	terminator of the pool*/
	tmp -= itemsize + sizeof(ExPoolAllactor);
	tmp->next = NULL;

	return alloc;
}
DECLSPEC void* ELTAPIENTRY ExPoolObtain(ExPoolAllactor* allactor){
	ExPoolAllactor* tmp;
	if(allactor->next == NULL)
		return NULL;

	tmp = allactor->next;
	allactor->next = tmp->next;
	return tmp;
}
DECLSPEC void* ELTAPIENTRY ExPoolReturn(ExPoolAllactor* allactor, void* data, unsigned int len){
	ExPoolAllactor* tmp;
	tmp = (data - (void*)allactor ) + sizeof(ExPoolAllactor);
	tmp->next = allactor->next;
	allactor->next = tmp;

	return tmp;
}
DECLSPEC void ELTAPIENTRY ExPoolFree(ExPoolAllactor* allactor){
	free(allactor);
}
