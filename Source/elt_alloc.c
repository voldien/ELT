#include"elt_alloc.h"
#ifdef EX_WINDOWS
#   include<Windows.h>
#elif defined(EX_LINUX)
#   include<unistd.h>
#endif // EX_WINDOWS


DECLSPEC int ELTAPIENTRY ExGetPageSize(void){
    long sz = sysconf(_SC_PAGESIZE);
    return sz;
}
