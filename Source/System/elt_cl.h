/*
===========================================================================
Copyright (C) 2014 BroodCity Software, Inc. Voldemor2009@hotmail.com

*/
#ifndef ELT_CL_H
#define ELT_CL_H
#include"./../EngineAssembly.h"

#define ELT_GPU 0x1
#define ELT_CPU 0x2
#ifdef __cplusplus	// C++ Environment
extern "C"{
#endif
/*
	//
*/

extern DECLSPEC void* ELTAPIFASTENTRY ExGetCLContext(void);
extern DECLSPEC void* ELTAPIFASTENTRY ExGetCLContext2(void);
/**

*/
extern DECLSPEC ERESULT ELTAPIENTRY ExCreateCLContex(Enum eEnumFlag);

/*	Release CL Context	*/
extern DECLSPEC void ELTAPIENTRY ExReleaseCL(void);
/*	Release CL Context	*/
extern DECLSPEC void ELTAPIENTRY ExReleaseCLContext(void* context);

/*
	//
*/
extern DECLSPEC void* ELTAPIENTRY ExCreateCLSharedContext(OpenGLContext glc, WindowContext window,Enum erenderingFlag);

/*Get the binary (PTX) of the program associated with the device*/
extern DECLSPEC Int32 ELTAPIENTRY ExGetProgBinary(void*, void* cdDevice,char** binary, size_t* length);

extern DECLSPEC void ELTAPIENTRY ExLogPtx(void* cpProgram, void* cdDevice, const char* cPtxFilename);

extern DECLSPEC Int32 ELTAPIENTRY ExGetCLPlatformID(Int32* clSelectedPlatformID);

extern DECLSPEC void ELTAPIENTRY ExPrintCLDevInfo(Int32 iLogMode, void* p_cl_device_id);

/* Get and return device capability */
extern DECLSPEC Int32 ELTAPIENTRY ExGetClDevCap(void* device);

/*	Get the Devices with the most FLOPS (Float operation per second;*/
extern DECLSPEC void* ELTAPIENTRY ExGetMaxFlopsDev(void* cxGPUContext);

#ifdef __cplusplus	// C++ Environment
}
#endif
#endif
