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
    #define cpuid2(func,a,b,c,d)\
    __asm__ __volatile__ ( \
"        pushq %%rbx        \n" \
"        cpuid              \n" \
"        movq %%rbx, %%rsi  \n" \
"        popq %%rbx         \n" : \
            "=a" (a), "=S" (b), "=c" (c), "=d" (d) : "a" (func))
#endif

DECLSPEC const ExChar* ELTAPIENTRY ExGetCPUName(void){
#ifdef EX_WINDOWS
	ExChar cpu_name[0xff];
	ExGetRegValuec(HKEY_LOCAL_MACHINE,EX_TEXT("HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0\\"),EX_TEXT("ProcessorNameString"),cpu_name);
	return cpu_name;	// TODO
#elif defined(EX_LINUX)
    static char cpu_name[48];
    int i = 0;
    int a,b,c,d;
//https://github.com/soreau/SDL/blob/master/src/cpuinfo/SDL_cpuinfo.c
    cpuid2(0x80000000,a,b,c,d);
    if(a >= 0x80000004){
        cpuid2(0x80000002, a, b, c, d);
        cpu_name[i++] = (char)(a & 0xff); a >>= 8;
        cpu_name[i++] = (char)(a & 0xff); a >>= 8;
        cpu_name[i++] = (char)(a & 0xff); a >>= 8;
        cpu_name[i++] = (char)(a & 0xff); a >>= 8;
        cpu_name[i++] = (char)(b & 0xff); b >>= 8;
        cpu_name[i++] = (char)(b & 0xff); b >>= 8;
        cpu_name[i++] = (char)(b & 0xff); b >>= 8;
        cpu_name[i++] = (char)(b & 0xff); b >>= 8;
        cpu_name[i++] = (char)(c & 0xff); c >>= 8;
        cpu_name[i++] = (char)(c & 0xff); c >>= 8;
        cpu_name[i++] = (char)(c & 0xff); c >>= 8;
        cpu_name[i++] = (char)(c & 0xff); c >>= 8;
        cpu_name[i++] = (char)(d & 0xff); d >>= 8;
        cpu_name[i++] = (char)(d & 0xff); d >>= 8;
        cpu_name[i++] = (char)(d & 0xff); d >>= 8;
        cpu_name[i++] = (char)(d & 0xff); d >>= 8;
        cpuid2(0x80000003, a, b, c, d);
        cpu_name[i++] = (char)(a & 0xff); a >>= 8;
        cpu_name[i++] = (char)(a & 0xff); a >>= 8;
        cpu_name[i++] = (char)(a & 0xff); a >>= 8;
        cpu_name[i++] = (char)(a & 0xff); a >>= 8;
        cpu_name[i++] = (char)(b & 0xff); b >>= 8;
        cpu_name[i++] = (char)(b & 0xff); b >>= 8;
        cpu_name[i++] = (char)(b & 0xff); b >>= 8;
        cpu_name[i++] = (char)(b & 0xff); b >>= 8;
        cpu_name[i++] = (char)(c & 0xff); c >>= 8;
        cpu_name[i++] = (char)(c & 0xff); c >>= 8;
        cpu_name[i++] = (char)(c & 0xff); c >>= 8;
        cpu_name[i++] = (char)(c & 0xff); c >>= 8;
        cpu_name[i++] = (char)(d & 0xff); d >>= 8;
        cpu_name[i++] = (char)(d & 0xff); d >>= 8;
        cpu_name[i++] = (char)(d & 0xff); d >>= 8;
        cpu_name[i++] = (char)(d & 0xff); d >>= 8;
        cpuid2(0x80000004, a, b, c, d);
        cpu_name[i++] = (char)(a & 0xff); a >>= 8;
        cpu_name[i++] = (char)(a & 0xff); a >>= 8;
        cpu_name[i++] = (char)(a & 0xff); a >>= 8;
        cpu_name[i++] = (char)(a & 0xff); a >>= 8;
        cpu_name[i++] = (char)(b & 0xff); b >>= 8;
        cpu_name[i++] = (char)(b & 0xff); b >>= 8;
        cpu_name[i++] = (char)(b & 0xff); b >>= 8;
        cpu_name[i++] = (char)(b & 0xff); b >>= 8;
        cpu_name[i++] = (char)(c & 0xff); c >>= 8;
        cpu_name[i++] = (char)(c & 0xff); c >>= 8;
        cpu_name[i++] = (char)(c & 0xff); c >>= 8;
        cpu_name[i++] = (char)(c & 0xff); c >>= 8;
        cpu_name[i++] = (char)(d & 0xff); d >>= 8;
        cpu_name[i++] = (char)(d & 0xff); d >>= 8;
        cpu_name[i++] = (char)(d & 0xff); d >>= 8;
        cpu_name[i++] = (char)(d & 0xff); d >>= 8;
    }

    return cpu_name;
	/*FILE* file;
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
	return info.model;*/
#endif
}

/**
	Has CPU Support For AVX (Advanced Vector Extension)
*/
DECLSPEC ExBoolean ELTAPIENTRY ExHasAVX(void){
	Int32 cpuInfo[4];
	cpuid(cpuInfo,1);
	return (cpuInfo[2] >> 28) &  0x1;
}
DECLSPEC ExBoolean ELTAPIENTRY ExHasAVX2(void){
	Int32 cpuInfo[4];
	cpuid(cpuInfo,1);
	return 0;
}

DECLSPEC ExBoolean ELTAPIENTRY ExHas3DNow(void){
	Int32 cpuInfo[4];
	cpuid(cpuInfo,0x80000001);
	if((cpuInfo[3] >> 30) & 0x1)return TRUE;
	else return FALSE;
}

DECLSPEC ExBoolean ELTAPIENTRY ExHasMMX(void){
	Int32 cpuInfo[4];
	cpuid(cpuInfo,1);
	if((cpuInfo[3] >> 23) & 0x1)
		return TRUE;
	else
		return FALSE;
}
/**
	Get number of CPU cores
*/
DECLSPEC Int32 ELTAPIENTRY ExGetCPUCount(void){
#ifdef EX_WINDOWS
	SYSTEM_INFO info;
	GetSystemInfo(&info);
	return info.dwNumberOfProcessors;
#elif defined(EX_LINUX)
	return sysconf(_SC_NPROCESSORS_ONLN);
#endif
}

DECLSPEC ExBoolean ELTAPIENTRY ExHasSSE(void){
	Int32 cpuInfo[4];
	cpuid(cpuInfo,1);
	if((cpuInfo[3] >> 25) & 0x1)
		return TRUE;
	else
		return FALSE;
}
DECLSPEC ExBoolean ELTAPIENTRY ExHasSSE2(void){
	Int32 cpuInfo[4];
	cpuid(cpuInfo,1);
	if((cpuInfo[3] >> 26) & 0x1)
		return TRUE;
	else
		return FALSE;
}
DECLSPEC ExBoolean ELTAPIENTRY ExHasSSE3(void){
	Int32 cpuInfo[4];
	cpuid(cpuInfo,1);
	if((cpuInfo[2] >> 9) & 0x1)
		return TRUE;
	else
		return FALSE;
}
DECLSPEC ExBoolean ELTAPIENTRY ExHasSSE41(void){
	Int32 cpuInfo[4];
	cpuid(cpuInfo,1);
	if((cpuInfo[2] >> 19) & 0x1)
		return TRUE;
	else
		return FALSE;
}
DECLSPEC ExBoolean ELTAPIENTRY ExHasSSE42(void){
	Int32 cpuInfo[4];
	cpuid(cpuInfo,1);
	if((cpuInfo[2] >> 20) & 0x1)
		return TRUE;
	else
		return FALSE;
}
