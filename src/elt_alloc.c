#include"elt_alloc.h"
#ifdef EX_WINDOWS
#	include<windows.h>
#   include<psapi.h>
#elif defined(EX_UNIX)
#   include<unistd.h>
#endif

int ELTAPIENTRY ExGetPageSize(void){
    #ifdef EX_WINDOWS
	PERFORMANCE_INFORMATION erformance_info;
	GetPerformanceInfo(&erformance_info,sizeof(PERFORMANCE_INFORMATION));
	return erformance_info.PageSize;
    #elif defined(EX_UNIX)
	long sz = sysconf(_SC_PAGESIZE);
	return sz;
    #endif
}

DECLSPEC ExPoolAllocator* ELTAPIENTRY ExPoolCreate(unsigned int num, unsigned int itemsize){
	ExPoolAllocator* alloc;
	ExPoolAllocator* tmp;
	unsigned int i;
	alloc = malloc(num * (itemsize + sizeof(ExPoolAllocator)));

	if(!alloc)
		return 0;

	/*	create pool chain.*/
	tmp = alloc;
	for(i = 0; i < num; i++){
		tmp->next = tmp + sizeof(ExPoolAllocator) + itemsize;
		tmp += sizeof(ExPoolAllocator) + itemsize;
		continue;
	}

	/*	terminator of the pool*/
	tmp -= itemsize + sizeof(ExPoolAllocator);
	tmp->next = NULL;

	return alloc;
}

DECLSPEC void* ELTAPIENTRY ExPoolObtain(ExPoolAllocator* allactor){
	ExPoolAllocator* tmp;
	if(allactor->next == NULL)
		return NULL;

	tmp = allactor->next;
	allactor->next = tmp->next;
	return tmp;
}

DECLSPEC void* ELTAPIENTRY ExPoolReturn(ExPoolAllocator* allactor, void* data, unsigned int len){
	ExPoolAllocator* tmp;
	tmp = (data - (void*)allactor ) + sizeof(ExPoolAllocator);
	tmp->next = allactor->next;
	allactor->next = tmp;

	return tmp;
}

DECLSPEC ExPoolAllocator* ELTAPIENTRY ExPoolResize(ExPoolAllocator* allcotor, unsigned num, unsigned int itemsize){
	ExPoolAllocator* next;
	ExPoolAllocator* terminate = allcotor->next;


	/*	get the last pool*/
	while(terminate->next){
		terminate = terminate->next;
	}
	terminate = terminate->next;


	next = allcotor->next;

	allcotor->next = realloc(allcotor->next,num * itemsize);
	if(!allcotor->next){

	}
	else{

	}

	return allcotor;
}

DECLSPEC void ELTAPIENTRY ExPoolFree(ExPoolAllocator* allactor){
	free(allactor);
}
