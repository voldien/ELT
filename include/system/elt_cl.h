/**
	ELT (Engine Library Toolkit) is a cross platform engine toolkit
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
#include"elt_win.h"

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
extern "C" {
#endif

/**
 *	Get current OpenCL context.
 *
 *	@Return OpenCL context.
 */
extern ELTDECLSPEC ExOpenCLContext ELTAPIFASTENTRY ExGetCurrentCLContext(void);

/**
 *	Check if OpenCL is supported.
 *
 *	@Return
 */
extern ELTDECLSPEC ExBoolean ELTAPIENTRY ExIsOpenCLSupported(void);

/**
 *	Create OpenCL Context
 *
 *
 *	@Return
 */
extern ELTDECLSPEC ExOpenCLContext ELTAPIENTRY ExCreateCLContext(
		unsigned int intFlag, unsigned int platform);

/**
 *	Create shared CL context with OpenGL context
 *
 *
 *	@Return CL context.
 */
extern ELTDECLSPEC ExOpenCLContext ELTAPIENTRY ExCreateCLSharedContext(
		ExOpenGLContext glc, unsigned int erenderingFlag);

/*
 *	Query Context information
 *
 *	@Return TODO resolve paramter order
 */
extern ELTDECLSPEC ERESULT ELTAPIENTRY ExQueryCLContext(ExOpenCLContext context,
		unsigned int param_name, ExHandle param_value, unsigned int* num);

/**
 *	Destroy OpenCL Context.
 *
 *	\context
 */
extern ELTDECLSPEC void ELTAPIENTRY ExDestroyCLContext(ExOpenCLContext context);

/**
 *
 *
 *	@Return
 */
extern ELTDECLSPEC int ELTAPIENTRY ExGetOpenCLPlatforms(
		unsigned int num_entries, ExCLPlatformID* platforms,
		unsigned int* num_platform);

/**
 *	@Return
 */
extern ELTDECLSPEC int ELTAPIENTRY ExGetOpenCLDevices(ExCLPlatformID platform,
		unsigned int type, unsigned int num_entries, ExCLDeviceID* devices,
		unsigned int* num_devices);

/**
 *
 */
extern ELTDECLSPEC int ELTAPIENTRY ExGetContextDevices(ExOpenCLContext context,
		ExCLDeviceID* devices, unsigned int* num);

/**
 *	Get CL platform identification
 *	@Return current CL context.
 */
extern ELTDECLSPEC int ELTAPIENTRY ExGetCLPlatformID(int* clSelectedPlatformID,
		unsigned int* num, unsigned int flag);

/**
 *	Get number of devices associated with OpenCL context.
 *
 *	@Return
 */
extern ELTDECLSPEC int ELTAPIENTRY ExGetNumDevices(ExOpenCLContext context);
extern ELTDECLSPEC int ELTAPIENTRY ExGetOpenCLVersion(ExOpenCLContext context);

/**
 *	Create opencl command queue.
 *
 *	@Return
 */
extern ELTDECLSPEC ExCLCommandQueue ELTAPIENTRY ExCreateCommandQueue(
		ExOpenCLContext context, ExCLDeviceID device);

/**
 *	Create OpenCL program.
 *
 *	@Return
 */
extern ELTDECLSPEC ExCLProgram ELTAPIENTRY ExCreateProgram(
		ExOpenCLContext context, ExCLDeviceID device, const ExChar* cfilename,
		...);

/**
 *	Release Program.
 *
 *	@Return
 */
extern ELTDECLSPEC int ELTAPIENTRY ExReleaseProgram(ExCLProgram program);

/**
 *	Create function kernel.
 *
 *	@Return
 */
extern ELTDECLSPEC ExCLKernel ELTAPIENTRY ExCreateKernel(ExCLProgram program,
		const ExChar* kernelname);

/**
 *	Release kernel.
 *
 *	@Return
 */
extern ELTDECLSPEC int ELTAPIENTRY ExReleaseKernel(ExCLProgram program);

/**
 *	Set kernel argument.
 *
 */
extern ELTDECLSPEC void ELTAPIENTRY ExSetCLArg(ExCLKernel kernel, int index,
		unsigned int size, void* arg);

/**
 *
 *	@Return
 */
extern ELTDECLSPEC ExCLMem ELTAPIENTRY ExCreateCLBuffer(ExOpenCLContext context,
		unsigned int flag, int size, void* host_ptr);
extern ELTDECLSPEC ExCLMem ELTAPIENTRY ExCreateCLImage(ExOpenCLContext context);

extern ELTDECLSPEC ExCLMem ELTAPIENTRY ExCreateCLImage(ExOpenCLContext context);

/**
 * 	add interoperability
 *
 *	@Return
 */
extern ELTDECLSPEC ExCLMem ExAquireGLObject(ExCLCommandQueue queue,
		unsigned int num, unsigned int* arg);
extern ELTDECLSPEC ExCLMem ExReleaseGLObject(ExCLCommandQueue queue,
		unsigned int num, unsigned int* arg);

/**
 *
 */
extern ELTDECLSPEC void ELTAPIENTRY ExPrintCLDevInfo(int iLogMode,
		ExHandle p_cl_device_id);

/**
 *	Get and return device capability
 *	@Return
 */
extern ELTDECLSPEC int ELTAPIENTRY ExGetClDevCap(void* device);

#ifdef __cplusplus	/*	C++ Environment	*/
}
#endif

#endif
