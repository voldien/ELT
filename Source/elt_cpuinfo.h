/*
===========================================================================
Copyright (C) 2014 BroodCity Software, Inc. Voldemor2009@hotmail.com

*/
#ifndef ELT_CPUINFO_H
#define ELT_CPUINFO_H
#include"EngineAssembly.h"

#ifdef __cplusplus	// C++ Environment
extern "C"{
#endif
/*
	// Get CPU Name
*/
extern DECLSPEC const ExChar* ELTAPIENTRY ExGetCPUName(void);


extern DECLSPEC Int32 ELTAPIENTRY ExGetFrequence(void);
/*
	// Has CPU Support For AVX (Advanced Vector Extension)
*/
extern DECLSPEC Boolean ELTAPIENTRY ExHasAVX(void);
/*
	// Has CPU Support For AVX2 (Advanced Vector Extension)
*/
extern DECLSPEC Boolean ELTAPIENTRY ExHasAVX2(void);
/*
	// Has CPU Support For 3DNow (AMD feature)
*/
extern DECLSPEC Boolean ELTAPIENTRY ExHas3DNow(void);
/*
	//
*/
extern DECLSPEC Boolean ELTAPIENTRY ExHasMMX(void);
/*
	// Get CPU number of cpu cores
*/
extern DECLSPEC Int32 ELTAPIENTRY ExGetCPUCount(void);
/*
	//
*/
extern DECLSPEC Boolean ELTAPIENTRY ExGetCPUCacheLineSize(void);
/*
	// Is SSE ( Streaming SIMD Extensions ) available
*/
extern DECLSPEC Boolean ELTAPIENTRY ExHasSSE(void);
/*
	// Is SSE 2 ( Streaming SIMD Extensions ) available
*/
extern DECLSPEC Boolean ELTAPIENTRY ExHasSSE2(void);
/*
	// Is SSE 3 ( Streaming SIMD Extensions ) available
*/
extern DECLSPEC Boolean ELTAPIENTRY ExHasSSE3(void);
/*
	// Is SSE 41 ( Streaming SIMD Extensions ) available
*/
extern DECLSPEC Boolean ELTAPIENTRY ExHasSSE41(void);
/*
	// Is SSE 41 ( Streaming SIMD Extensions ) available
*/
extern DECLSPEC Boolean ELTAPIENTRY ExHasSSE42(void);


#ifdef __cplusplus	// C++ Environment
}
#endif

#endif