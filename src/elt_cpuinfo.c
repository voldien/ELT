#include"elt_cpuinfo.h"

#ifdef EX_WINDOWS
#include<windows.h>
#include<winbase.h>
// get CPUID
#include<immintrin.h>
#   include<intrin.h>
#elif defined(EX_UNIX)
#   include<unistd.h>
#endif

#include<setjmp.h>

#define ELT_CPU_HAS_RDSTC
#define ELT_CPU_HAS_MMX
#define ELT_CPU_HAS_3DNOW
#define ELT_CPU_HAS_SSE
#define ELT_CPU_HAS_SSE2
#define ELT_CPU_HAS_SSE3
#define ELT_CPU_HAS_SSE4
#define ELT_CPU_HAS_SSE41
#define ELT_CPU_HAS_SSE42
#define ELT_CPU_HAS_AVX
#define ELT_CPU_HAS_AVX2
#define ELT_CPU_HAS_AVX512


#if defined(EX_X86)
#   include<cpuid.h>
	/*	cpuid for linux	*/
#define cpuid(regs, i) __get_cpuid(i, &regs[0], &regs[1], &regs[2], &regs[3]);
    #define cpuid2(func, a, b, c, d)\
    EX_ASM __volatile__ ( 		\
"        pushq %%rbx        \n" \
"        cpuid              \n" \
"        movq %%rbx, %%rsi  \n" \
"        popq %%rbx         \n" : \
"           =a" (a), "=S" (b), "=c" (c), "=d" (d) : "a" (func))
#elif defined(EX_ANDROID)

#   define cpuid(regs, i)

#endif



Uint32 ExGetCPUArch(void){
#if defined(EX_X86_64)
	return EX_CPU_X86_64;
#elif defined(EX_X86)
	return EX_CPU_X86;
#elif defined(EX_ARM)
	return EX_CPU_ARM;
#endif
}

const ExChar* ExGetCPUName(void){
    static char cpu_name[48] = {0};

#ifdef EX_WINDOWS
	ExGetRegValuec(HKEY_LOCAL_MACHINE,EX_TEXT("HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0\\"), EX_TEXT("ProcessorNameString"), cpu_name);
	return cpu_name;	// TODO
#elif defined(EX_LINUX)

    int i = 0;
    int a,b,c,d;
//https://github.com/soreau/SDL/blob/master/src/cpuinfo/SDL_cpuinfo.c
#if !defined(EX_ARM)
    if(cpu_name[0] == NULL){
		cpuid2(0x80000000, a, b, c, d);
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
    }

	#else	/*	get CPU name for ARM.*/
    #endif
    return cpu_name;
#elif defined(EX_ANDROID)

#endif
}

ExBoolean ExHasAVX(void){
	Int32 cpuInfo[4];
	cpuid(cpuInfo, 0x1);
	return (cpuInfo[2] & bit_AVX);
}

ExBoolean ExHasAVX2(void){
	Int32 cpuInfo[4];
	cpuid(cpuInfo, 1);
	return (cpuInfo[0] & bit_AVX2);
}

ExBoolean ExHasAVX512(void){
	return FALSE;
}

ExBoolean ExHas3DNow(void){
	Int32 cpuInfo[4];
	cpuid(cpuInfo,0x80000001);
	return (cpuInfo[3] & bit_3DNOW) != 0;
}

ExBoolean ExHasMMX(void){
	Int32 cpuInfo[4];
	cpuid(cpuInfo, 1);
	return (cpuInfo[3] & bit_MMX) != 0;
}

Uint ExGetCPUCacheLineSize(void){
#ifdef EX_LINUX
	return sysconf(_SC_LEVEL1_DCACHE_LINESIZE);
#else
	return 0;
#endif
}

ExBoolean ExHasSSE(void){
	Int32 cpuInfo[4];
	return (cpuInfo[3] & bit_SSE) != 0;
}

ExBoolean ExHasSSE2(void){
	Int32 cpuInfo[4];
	cpuid(cpuInfo,1);
	return (cpuInfo[3] & bit_SSE2) != 0;
}

ExBoolean ExHasSSE3(void){
	Int32 cpuInfo[4];
	cpuid(cpuInfo,1);
	return (cpuInfo[2] & bit_SSE3) != 0;
}

ExBoolean ExHasSSE41(void){
	Int32 cpuInfo[4];
	cpuid(cpuInfo,1);
	return (cpuInfo[2] & bit_SSE4_1) != 0;
}

ExBoolean ExHasSSE42(void){
	Int32 cpuInfo[4];
	cpuid(cpuInfo,1);
	return (cpuInfo[2] & bit_SSE4_2) != 0;
}

ExBoolean ExHasNeon(void){
#ifdef EX_ARM
	//EX_ASM volatile ("vldr d18,[fp,#-32]");
#endif
	return FALSE;
}

ExBoolean ExHasRDTSC(void){
	Uint32 cpuInfo[4];
	cpuid(cpuInfo, 1);
	return ( cpuInfo[2] & 0x00000010 ) ? TRUE : FALSE;
}
