#include"elt_alloc.h"
#ifdef EX_WINDOWS
#   include<Windows.h>
#elif defined(EX_LINUX)
#   include<unistd.h>
#endif // EX_WINDOWS


DECLSPEC int ELTAPIENTRY ExGetPageSize(void){
    #ifdef EX_WINDOWS
	PERFORMANCE_INFORMATION erformance_info;
	GetPerformanceInfo(&erformance_info,sizeof(performance_info));
	return erformance_info.PageSize;
    #elif defined(EX_LINUX)
    long sz = sysconf(_SC_PAGESIZE);
    return sz;
    #endif
}
