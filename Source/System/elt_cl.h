/*
===========================================================================
Copyright (C) 2014 BroodCity Software, Inc. Voldemor2009@hotmail.com

*/
#ifndef ELT_CL_H
#define ELT_CL_H
#include"./../EngineAssembly.h"


#define ELT_GPU0 0x0                        /**/
#define ELT_CPU0 0x20                       /**/
#define ELT_CL_FLOPS_HIGHEST 0x400          /**/
#define ELT_CL_AVAILABLE_PLATFORM 0x1000    /**/
#ifdef __cplusplus	// C++ Environment
extern "C"{
#endif
/**
	Get CL context
*/
extern DECLSPEC void* ELTAPIFASTENTRY ExGetCLContext(void);

/**
	Get current cl context
*/
extern DECLSPEC void* ELTAPIFASTENTRY ExGetCurrentCLContext(void);

/**
    Create OpenCL Context
*/
extern DECLSPEC ERESULT ELTAPIENTRY ExCreateCLContex(Enum eEnumFlag);

/**
	Release CL Context
*/
extern DECLSPEC void ELTAPIENTRY ExReleaseCL(void);
/**
	Release CL Context
*/
extern DECLSPEC void ELTAPIENTRY ExReleaseCLContext(void* context);

/**
	Create shared CL context with OpenGL context
*/
extern DECLSPEC void* ELTAPIENTRY ExCreateCLSharedContext(OpenGLContext glc, WindowContext window,Enum erenderingFlag);

/*Get the binary (PTX) of the program associated with the device*/
extern DECLSPEC Int32 ELTAPIENTRY ExGetProgBinary(void*, void* cdDevice,char** binary, size_t* length);

extern DECLSPEC void ELTAPIENTRY ExLogPtx(void* cpProgram, void* cdDevice, const char* cPtxFilename);
/**
    Get CL platform identification
*/
extern DECLSPEC Int32 ELTAPIENTRY ExGetCLPlatformID(Int32* clSelectedPlatformID,Enum flag);
/**

*/
extern DECLSPEC void ELTAPIENTRY ExPrintCLDevInfo(Int32 iLogMode, void* p_cl_device_id);

/* Get and return device capability */
extern DECLSPEC Int32 ELTAPIENTRY ExGetClDevCap(void* device);


#ifdef __cplusplus	// C++ Environment
}
#endif
#endif
