/*
    ELT (Engine Library Toolkit) is a multi platform engine toolkit
    Copyright (C) 2014  Valdemar Lindberg

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/
#ifndef _ELT_CPUINFO_H_
#define _ELT_CPUINFO_H_ 1
#include"EngineAssembly.h"

#ifdef __cplusplus	/*	C++ Environment	*/
extern "C"{
#endif

/*TODO take a look at which approuch for dealing with cpu information. enum or string?*/
#define EX_CPU_UNKNOWN		0x0
#define EX_CPU_X86        	0x1
#define EX_CPU_X86_64	 	0x2
#define EX_CPU_PPC        	0x3
#define EX_CPU_ARM        	0x4
#define EX_CPU_MIPS       	0x5

/*
 *
 *	@Return
 */
extern ELTDECLSPEC Uint32 ELTAPIENTRY ExGetCPUInstructionArch(void);


/*
 *
 *	@Return
 */
extern ELTDECLSPEC const ExChar* ELTAPIENTRY ExGetCPUType(void);

/*
 *	Get the name of the CPU.
 *	@Return
 */
extern ELTDECLSPEC const ExChar* ELTAPIENTRY ExGetCPUName(void);

/*
 *
 *	@Return
 */
extern ELTDECLSPEC Int32 ELTAPIENTRY ExGetFrequence(void);

/*
 *	Has CPU Support For AVX (Advanced Vector Extension)
 *	@Return
 */
extern ELTDECLSPEC ExBoolean ELTAPIENTRY ExHasAVX(void);

/*
 *	Has CPU Support For AVX2 (Advanced Vector Extension)
 *	@Return
 */
extern ELTDECLSPEC ExBoolean ELTAPIENTRY ExHasAVX2(void);


/*
 *	Has CPU Support For 3DNow (AMD feature)
 *	@Return
 */
extern ELTDECLSPEC ExBoolean ELTAPIENTRY ExHas3DNow(void);

/*
 *	Has CPU Support For MMX (Matrix Math eXtension)
 *	@Return
 */
extern ELTDECLSPEC ExBoolean ELTAPIENTRY ExHasMMX(void);

/*
 *	Get number of cpu's cores.
 *	@Return number of cpu cores.
 */
extern ELTDECLSPEC Int32 ELTAPIENTRY ExGetCPUCount(void);

/*
 *
 *	@Return
 */
extern ELTDECLSPEC Uint ELTAPIENTRY ExGetCPUCacheLineSize(void);

/*
 *	Is SSE ( Streaming SIMD Extensions ) available
 *	@Return
 */
extern ELTDECLSPEC ExBoolean ELTAPIENTRY ExHasSSE(void);

/*
 *	Is SSE 2 ( Streaming SIMD Extensions ) available
 *	@Return
 */
extern ELTDECLSPEC ExBoolean ELTAPIENTRY ExHasSSE2(void);

/*
 *	Is SSE 3 ( Streaming SIMD Extensions ) available
 *	@Return
 */
extern ELTDECLSPEC ExBoolean ELTAPIENTRY ExHasSSE3(void);

/*
 *	Is SSE 41 ( Streaming SIMD Extensions ) available
 *	@Return
 */
extern ELTDECLSPEC ExBoolean ELTAPIENTRY ExHasSSE41(void);

/*
 *	Is SSE 41 ( Streaming SIMD Extensions ) available
 *	@Return	TRUE if available.
 */
extern ELTDECLSPEC ExBoolean ELTAPIENTRY ExHasSSE42(void);

/*
 *	Arm SIMD feature for float point unit fpu.
 *	@Return
 */
extern ELTDECLSPEC ExBoolean ELTAPIENTRY ExHasNeon(void);

/*
 *	Time Stamp Counter
 *	@Return
 */
extern ELTDECLSPEC ExBoolean ELTAPIENTRY ExHasRDTSC(void);

/**/
extern ELTDECLSPEC Enum ELTAPIENTRY ExGetCpuVendor(void);
#ifdef __cplusplus	/*	C++ Environment	*/
}
#endif

#endif
