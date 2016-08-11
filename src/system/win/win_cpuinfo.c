#include"elt_cpuinfo.h"
#include<windows.h>
#include<winbase.h>
// get CPUID
#include<immintrin.h>
#   include<intrin.h>



const ExChar* ExGetCPUName(void){
    static char cpu_name[48] = {0};
	ExGetRegValuec(HKEY_LOCAL_MACHINE, EX_TEXT("HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0\\"), EX_TEXT("ProcessorNameString"), cpu_name);
	return cpu_name;	// TODO
}

Int32 ExGetCPUCount(void){
	SYSTEM_INFO info;
	GetSystemInfo(&info);
	return info.dwNumberOfProcessors;
}
