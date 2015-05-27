#include"elt_alloc.h"
#ifdef EX_WINDOWS
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
