#include"elt_cpuinfo.h"
#include<windows.h>
#include<winbase.h>
// get CPUID
#include<immintrin.h>
#   include<intrin.h>

Int32 ExGetCPUCount(void){
	SYSTEM_INFO info;
	GetSystemInfo(&info);
	return info.dwNumberOfProcessors;
}
