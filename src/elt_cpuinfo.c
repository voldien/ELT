#include"elt_cpuinfo.h"
// get AVX

#ifdef EX_WINDOWS
#include<windows.h>
#include<winbase.h>
// get CPUID
#include<immintrin.h>
#   include<intrin.h>
#elif defined(EX_UNIX)
#   include<unistd.h>
#elif defined(EX_MAC)
#   include<sys/sysctl.h>
#endif
#include<setjmp.h>


#ifdef EX_GNUC

#ifdef __SSE__
#   include <xmmintrin.h>
#endif

#ifdef __SSE2__
#   include <emmintrin.h>
#endif

#ifdef __SSE3__
#   include <pmmintrin.h>
#endif

#ifdef __SSSE3__
#   include <tmmintrin.h>
#endif

#if defined (__SSE4_2__) || defined (__SSE4_1__)
#   include <smmintrin.h>
#endif

#if defined (__AES__) || defined (__PCLMUL__)
#   include <wmmintrin.h>
#endif

#else

//#include <wmmintrin.h>

#endif



//http://stackoverflow.com/questions/1666093/cpuid-implementations-in-c

#ifdef EX_WINDOWS       /** WINDOWS */
	#define cpuid __cpuid
#elif defined(EX_LINUX)	/** LINUX   */
    #if defined(EX_X86)
    #   include<cpuid.h>
	#endif

	/** cpuid for linux  */
#if defined(EX_X86) && !defined(EX_CLANG) && !defined(EX_LLVM)
	#define cpuid(regs,i) 	EX_ASSM  __volatile__ \
			("cpuid" : "=a" (regs[0]), "=b" (regs[1]), "=c" (regs[2]), "=d" (regs[3])\
			: "a" (i), "c" (0))

    #define cpuid2(func,a,b,c,d)\
    EX_ASSM __volatile__ ( 		\
"        pushq %%rbx        \n" \
"        cpuid              \n" \
"        movq %%rbx, %%rsi  \n" \
"        popq %%rbx         \n" : \
"           =a" (a), "=S" (b), "=c" (c), "=d" (d) : "a" (func))
#else
	#define cpuid(regs,i)
	#define cpuid2(func,a,b,c,d)
#endif


#elif defined(EX_ANDROID)

#   define cpuid(regs, i)

#else
	#define cpuid(regs,i)	regs
	#define cpuid2(func,a,b,c,d)	func
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

    #if  !defined(EX_ARM)
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
    #endif
    return cpu_name;
#elif defined(EX_ANDROID)

#endif
}

/**
	Has CPU Support For AVX (Advanced Vector Extension)
*/
DECLSPEC ExBoolean ELTAPIENTRY ExHasAVX(void){
	Int32 cpuInfo[4];
	cpuid(cpuInfo,0x1);
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
#elif defined(EX_LINUX) || defined(EX_ANDROID)


	return sysconf(_SC_NPROCESSORS_ONLN);
//#elif defined(__IRIX__)
//	   num_cpus = sysconf(_SC_NPROC_ONLN);
//#elif defined(_SC_NPROCESSORS_ONLN)
//	   /* number of processors online (SVR4.0MP compliant machines) */
//          num_cpus = sysconf(_SC_NPROCESSORS_ONLN);
//#elif defined(_SC_NPROCESSORS_CONF)
	   /* number of processors configured (SVR4.0MP compliant machines) */
//          num_cpus = sysconf(_SC_NPROCESSORS_CONF);
//#endif

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
