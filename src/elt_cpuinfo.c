#include"elt_cpuinfo.h"

#if defined(EX_X86_64) || defined(EX_X86)
	#include<immintrin.h>
#endif

#include<unistd.h>

#include<setjmp.h>
#include<stdint.h>

/*	CPU extension features.	*/
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


#if defined(EX_X86_64) || defined(EX_X86)
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



unsigned int ExGetCPUArch(void){
#if defined(EX_X86_64)
	return EX_CPU_X86_64;
#elif defined(EX_X86)
	return EX_CPU_X86;
#elif defined(EX_ARM)
	return EX_CPU_ARM;
#endif
}


unsigned int ExGetEndian(void){
	return 0;
}


ExBoolean ExHasAVX(void){
	int cpuInfo[4];
	cpuid(cpuInfo, 0x1);
	return (cpuInfo[2] & bit_AVX) != 0;
}

ExBoolean ExHasAVX2(void){
	int cpuInfo[4];
	cpuid(cpuInfo, 1);
	return (cpuInfo[1] & bit_AVX2) != 0;
}

ExBoolean ExHasFMA(void){
	int cpuInfo[4];
	cpuid(cpuInfo, 1);
	return (cpuInfo[2] & bit_FMA) != 0;
}

ExBoolean ExHasAVX512(void){
	return EX_FALSE;
}

ExBoolean ExHas3DNow(void){
	int cpuInfo[4];
	cpuid(cpuInfo,0x80000001);
	return (cpuInfo[3] & bit_3DNOW) != 0;
}

ExBoolean ExHasMMX(void){
	int cpuInfo[4];
	cpuid(cpuInfo, 1);
	return (cpuInfo[3] & bit_MMX) != 0;
}

ExBoolean ExHasSSE(void){
	int cpuInfo[4];
	return (cpuInfo[3] & bit_SSE) != 0;
}

ExBoolean ExHasSSE2(void){
	int cpuInfo[4];
	cpuid(cpuInfo,1);
	return (cpuInfo[3] & bit_SSE2) != 0;
}

ExBoolean ExHasSSE3(void){
	int cpuInfo[4];
	cpuid(cpuInfo,1);
	return (cpuInfo[2] & bit_SSE3) != 0;
}

ExBoolean ExHasSSE41(void){
	int cpuInfo[4];
	cpuid(cpuInfo,1);
	return (cpuInfo[2] & bit_SSE4_1) != 0;
}

ExBoolean ExHasSSE42(void){
	int cpuInfo[4];
	cpuid(cpuInfo,1);
	return (cpuInfo[2] & bit_SSE4_2) != 0;
}

ExBoolean ExHasNeon(void){
#ifdef EX_ARM
	//EX_ASM volatile ("vldr d18,[fp,#-32]");
#endif
	return EX_FALSE;
}

ExBoolean ExHasRDTSC(void){
	unsigned int cpuInfo[4];
	cpuid(cpuInfo, 1);
	return ( cpuInfo[2] & 0x00000010 ) != 0;
}

ExBoolean ExHasDRNG(void){
	unsigned int cpuInfo[4];
	cpuid(cpuInfo, 1);
	return ( cpuInfo[2] & bit_RDSEED ) != 0;
}

ExBoolean ExHasAES(void){
	unsigned int cpuInfo[4];
	cpuid(cpuInfo, 1);
	return ( cpuInfo[2] & bit_AES ) != 0;
}
