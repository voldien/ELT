#include"elt_cpuinfo.h"
// get AVX
#include<immintrin.h>
#ifdef EX_WINDOWS
// get CPUID
#   include<intrin.h>
#elif defined(EX_LINUX)

#endif

//http://stackoverflow.com/questions/1666093/cpuid-implementations-in-c
#ifdef EX_WINDOWS
	#define cpuid __cpuid
#elif defined(EX_LINUX)
	#include <unistd.h>
	#include<cpuid.h>
	// cpuid for linux
	#define cpuid(regs,i) 	asm volatile \
			("cpuid" : "=a" (regs[0]), "=b" (regs[1]), "=c" (regs[2]), "=d" (regs[3])\
			: "a" (i), "c" (0))
#endif

DECLSPEC const ExChar* ELTAPIENTRY ExGetCPUName(void){
#ifdef EX_WINDOWS
	ExChar cpu_name[0xff];
	ExGetRegValuec(HKEY_LOCAL_MACHINE,EX_TEXT("HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0\\"),EX_TEXT("ProcessorNameString"),cpu_name);
	return cpu_name;	// TODO
#elif defined(EX_LINUX)
	FILE* file;
	struct CpuInfo{
		char vendor_id[50];
		int family;
		char model[50];
		float freq;
		char cache[20];
	}info;
	file = fopen("/proc/cpuinfo","rb");
	fread((void*)&info.vendor_id[0], 1, sizeof(info),file);
	fclose(file);
	return info.model;
#endif
}

/*
	// Has CPU Support For AVX (Advanced Vector Extension)
*/
DECLSPEC Boolean ELTAPIENTRY ExHasAVX(void){
	Int32 cpuInfo[4];
	cpuid(cpuInfo,1);
	return (cpuInfo[2] >> 28) &  0x1;
}
DECLSPEC Boolean ELTAPIENTRY ExHasAVX2(void){
	Int32 cpuInfo[4];
	cpuid(cpuInfo,1);
	return 0;
}

DECLSPEC Boolean ELTAPIENTRY ExHas3DNow(void){
	Int32 cpuInfo[4];
	cpuid(cpuInfo,0x80000001);
	if((cpuInfo[3] >> 30) & 0x1)return TRUE;
	else return FALSE;
}

DECLSPEC Boolean ELTAPIENTRY ExHasMMX(void){
	Int32 cpuInfo[4];
	cpuid(cpuInfo,1);
	if((cpuInfo[3] >> 23) & 0x1)
		return TRUE;
	else
		return FALSE;
}
/*
	// Get CPU number of cpu cores
*/
DECLSPEC Int32 ELTAPIENTRY ExGetCPUCount(void){
#ifdef EX_WINDOWS
	SYSTEM_INFO info;
	GetSystemInfo(&info);
	return info.dwNumberOfProcessors;
#else
	return sysconf(_SC_NPROCESSORS_ONLN);
#endif
}

DECLSPEC Boolean ELTAPIENTRY ExHasSSE(void){
	Int32 cpuInfo[4];
	cpuid(cpuInfo,1);
	if((cpuInfo[3] >> 25) & 0x1)
		return TRUE;
	else
		return FALSE;
}
DECLSPEC Boolean ELTAPIENTRY ExHasSSE2(void){
	Int32 cpuInfo[4];
	cpuid(cpuInfo,1);
	if((cpuInfo[3] >> 26) & 0x1)
		return TRUE;
	else
		return FALSE;
}
DECLSPEC Boolean ELTAPIENTRY ExHasSSE3(void){
	Int32 cpuInfo[4];
	cpuid(cpuInfo,1);
	if((cpuInfo[2] >> 9) & 0x1)
		return TRUE;
	else
		return FALSE;
}
DECLSPEC Boolean ELTAPIENTRY ExHasSSE41(void){
	Int32 cpuInfo[4];
	cpuid(cpuInfo,1);
	if((cpuInfo[2] >> 19) & 0x1)
		return TRUE;
	else
		return FALSE;
}
DECLSPEC Boolean ELTAPIENTRY ExHasSSE42(void){
	Int32 cpuInfo[4];
	cpuid(cpuInfo,1);
	if((cpuInfo[2] >> 20) & 0x1)
		return TRUE;
	else
		return FALSE;
}
