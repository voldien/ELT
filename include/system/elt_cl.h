/*
========================================================================
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
#ifndef _ELT_CL_H_
#define _ELT_CL_H_ 1
#include"./../EngineAssembly.h"


#define ELT_GPU0 0x20                        /* GPU index 0 + offset*/
#define ELT_CPU0 0x40                       /* CPU index 0 + offset*/
#define ELT_CL_FLOPS_HIGHEST 0x400          /* Device with most FLOPS */
#define ELT_CL_AVAILABLE_PLATFORM 0x1000    /* Get available device */
//#define EX_CL_GL_SYNC   0x2000    //TODO check if it's needed
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
extern DECLSPEC ERESULT ELTAPIENTRY ExCreateCLContext(Enum eEnumFlag);

/**
    Query Context information
*/
extern DECLSPEC ERESULT ELTAPIENTRY ExQueryCLContext(void* context,void* param_value,Enum param_name);
/**
	Release Current CL Context
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
