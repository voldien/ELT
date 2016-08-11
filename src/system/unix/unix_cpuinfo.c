#include"elt_cpuinfo.h"
# include<unistd.h>
# include<setjmp.h>


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

#endif


const ExChar* ExGetCPUName(void){
    static char cpu_name[48] = {0};

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
}



Uint ExGetCPUCacheLineSize(void){
	return sysconf(_SC_LEVEL1_DCACHE_LINESIZE);
}


Int32 ExGetCPUCount(void){
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
}
