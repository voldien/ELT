/**
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


#ifdef __cplusplus	// C++ Environment
extern "C"{
#endif

/*TODO take a look at which approuch for dealing with cpu information. enum or string?*/
#define EX_CPU_VENDOR_INTEL
#define EX_CPU_VENDOR_AMD
#define EX_CPU_VENDOR_ARM


/*
 *	Get CPU Name
 *	@return
*/
extern DECLSPEC const ExChar* ELTAPIENTRY ExGetCPUName(void);

/**/
extern DECLSPEC Int32 ELTAPIENTRY ExGetFrequence(void);

/*
 *	Has CPU Support For AVX (Advanced Vector Extension)
*/
extern DECLSPEC ExBoolean ELTAPIENTRY ExHasAVX(void);

/*
 *	Has CPU Support For AVX2 (Advanced Vector Extension)
*/
extern DECLSPEC ExBoolean ELTAPIENTRY ExHasAVX2(void);

/*
 *	Has CPU Support For 3DNow (AMD feature)
*/
extern DECLSPEC ExBoolean ELTAPIENTRY ExHas3DNow(void);

/*
 *	Has CPU Support For MMX (Matrix Math eXtension)
*/
extern DECLSPEC ExBoolean ELTAPIENTRY ExHasMMX(void);

/*
 *	Get CPU number of cpu cores
 *	@return number of cpu cores.
 */
extern DECLSPEC Int32 ELTAPIENTRY ExGetCPUCount(void);

/*
 *
 */
extern DECLSPEC ExBoolean ELTAPIENTRY ExGetCPUCacheLineSize(void);

/*
 *	Is SSE ( Streaming SIMD Extensions ) available
 */
extern DECLSPEC ExBoolean ELTAPIENTRY ExHasSSE(void);

/*
 *	Is SSE 2 ( Streaming SIMD Extensions ) available
 */
extern DECLSPEC ExBoolean ELTAPIENTRY ExHasSSE2(void);

/*
 *	Is SSE 3 ( Streaming SIMD Extensions ) available
 */
extern DECLSPEC ExBoolean ELTAPIENTRY ExHasSSE3(void);

/*
 *	Is SSE 41 ( Streaming SIMD Extensions ) available
 */
extern DECLSPEC ExBoolean ELTAPIENTRY ExHasSSE41(void);

/*
 *	Is SSE 41 ( Streaming SIMD Extensions ) available
 */
extern DECLSPEC ExBoolean ELTAPIENTRY ExHasSSE42(void);

/*
 *
 */
extern DECLSPEC ExBoolean ELTAPIENTRY ExHasNeon(void);

/**/
extern DECLSPEC Enum ELTAPIENTRY ExGetCpuVendor(void);

/**/
extern DECLSPEC Enum ELTAPIENTRY ExGetCPUInstructionArchecture(void);

#ifdef __cplusplus	// C++ Environment
}
#endif

#endif
