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
#ifndef _ELT_CL_H_
#define _ELT_CL_H_ 1
#include"./../EngineAssembly.h"

#define EX_CL_GPU0 0x40                        	/*	GPU index 0 + offset	*/
#define EX_CL_CPU0 0x80                       	/*	CPU index 0 + offset	*/
#define EX_CL_CPU_REGION
#define EX_CL_GPU_REGION
#define EX_CL_FLOPS_HIGHEST 0x400          		/*	Device with most FLOPS	*/
#define EX_CL_AVAILABLE_PLATFORM 0x1000    		/*	Get available device	*/
#define EX_CL_
/*#define EX_CL_GL_SYNC   0x2000    			//TODO check if it's needed	*/

#define EX_CL_OPENGL
#define EX_CL_DIRECTX

#define EX_CL_CONTEXT_REFERENCE_COUNT                  0x1080
#define EX_CL_CONTEXT_DEVICES                          0x1081
#define EX_CL_CONTEXT_PROPERTIES                       0x1082
#define EX_CL_CONTEXT_NUM_DEVICES                      0x1083


#define EX_CL_READ_MEM			(1 << 0)
#define EX_CL_WRITE_MEM			(1 << 1)
#define EX_CL_READ_WRITE_MEM 	( EX_CL_READ_MEM | EX_CL_WRITE_MEM )
#define EX_CL_MEM_COPY_HOST


/**
 *	ELT OpenCL data types.
 */
typedef void* ExCLCommandQueue;
typedef void* ExCLKernel;
typedef void* ExCLProgram;
typedef void* ExCLMem;
typedef void* ExCLPlatformID;
typedef void* ExCLDeviceID;

#ifdef __cplusplus	/*	C++ Environment	*/
extern "C"{
#endif


/**
 *	Get current OpenCL context.
 *	@Return OpenCL context.
 */
extern ELTDECLSPEC ExOpenCLContext ELTAPIFASTENTRY ExGetCurrentCLContext(void);

/**
 *	@Return
 */
extern ELTDECLSPEC ExBoolean ELTAPIENTRY ExIsOpenCLSupported(void);

/**
 *	Create OpenCL Context
 *	@Return
 */
extern ELTDECLSPEC ExOpenCLContext ELTAPIENTRY ExCreateCLContext(Enum eEnumFlag, unsigned int platform);

/**
 *	Create shared CL context with OpenGL context
 *	@Return CL context.
 */
extern ELTDECLSPEC ExOpenCLContext ELTAPIENTRY ExCreateCLSharedContext(ExOpenGLContext glc, ExWindowContext window, Enum erenderingFlag);

/*
 *	Query Context information
 *	@Return TODO resolve paramter order
 */
extern ELTDECLSPEC ERESULT ELTAPIENTRY ExQueryCLContext(ExOpenCLContext context, Enum param_name, ExHandle param_value, unsigned int* num);

/**
 *	Destroy OpenCL Context.
 */
extern ELTDECLSPEC void ELTAPIENTRY ExDestroyCLContext(ExOpenCLContext context);

/**
 *	@Return
 */
extern ELTDECLSPEC Int ELTAPIENTRY ExGetOpenCLPlatforms(Uint num_entries, ExCLPlatformID* platforms, Uint* num_platform);


/**
 *	@Return
 */
extern ELTDECLSPEC Int ELTAPIENTRY ExGetOpenCLDevices(ExCLPlatformID platform, Enum type, Uint num_entries, ExCLDeviceID* devices, Uint* num_devices );

/**
 *	Get CL platform identification
 *	@Return current CL context.
 */
extern ELTDECLSPEC Int32 ELTAPIENTRY ExGetCLPlatformID(Int32* clSelectedPlatformID, unsigned int* num, Enum flag);


extern ELTDECLSPEC Int32 ELTAPIENTRY ExGetNumDevices(ExOpenCLContext context);
extern ELTDECLSPEC Int32 ELTAPIENTRY ExGetOpenCLVersion(ExOpenCLContext context);

/**
 *	Create opencl command queue.
 *	@Return
 */
extern ELTDECLSPEC ExCLCommandQueue ELTAPIENTRY ExCreateCommandQueue(ExOpenCLContext context, ExCLDeviceID device);

/**
 *	Create opencl program.
 *	@Return
 */
extern ELTDECLSPEC ExCLProgram ELTAPIENTRY ExCreateProgram(ExOpenCLContext context, ExCLDeviceID device, const ExChar* cfilename, ...);

/**
 *	Release Program.
 *	@Return
 */
extern ELTDECLSPEC int ELTAPIENTRY ExReleaseProgram(ExCLProgram program);

/**
 *	Create function kernel.
 *	@Return
 */
extern ELTDECLSPEC ExCLKernel ELTAPIENTRY ExCreateKernel(ExCLProgram program, const ExChar* kernelname);

/**
 *	Release kernel.
 *	@Return
 */
extern ELTDECLSPEC int ELTAPIENTRY ExReleaseKernel(ExCLProgram program);

/**
 *	Set kernel argument.
 */
extern ELTDECLSPEC void ELTAPIENTRY ExSetCLArg(ExCLKernel kernel, int index, unsigned int size, void* arg);

/**
 *
 */
extern ELTDECLSPEC ExCLMem ELTAPIENTRY ExCreateCLBuffer(ExOpenCLContext context, Enum flag, int size, void* host_ptr);
extern ELTDECLSPEC ExCLMem ELTAPIENTRY ExCreateCLImage(ExOpenCLContext context);


/**
 * 	add interoperability
 */
extern ELTDECLSPEC ExCLMem ExAquireGLObject(ExCLCommandQueue queue, unsigned int num, unsigned int* arg);
extern ELTDECLSPEC ExCLMem ExReleaseGLObject(ExCLCommandQueue queue, unsigned int num, unsigned int* arg);


/**
 *
 */
extern ELTDECLSPEC void ELTAPIENTRY ExPrintCLDevInfo(Int32 iLogMode, ExHandle p_cl_device_id);

/**
 *	Get and return device capability
 *	@Return
 */
extern ELTDECLSPEC Int32 ELTAPIENTRY ExGetClDevCap(void* device);


#ifdef __cplusplus	/*	C++ Environment	*/
}
#endif

#endif
