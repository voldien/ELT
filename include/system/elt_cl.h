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

#define EX_GPU0 0x20                        	/*	GPU index 0 + offset	*/
#define EX_CPU0 0x40                       	/*	CPU index 0 + offset	*/
#define EX_CPU_REGION
#define EX_GPU_REGION
#define EX_CL_FLOPS_HIGHEST 0x400          	/*	Device with most FLOPS	*/
#define EX_CL_AVAILABLE_PLATFORM 0x1000    	/*	Get available device	*/
//#define EX_CL_GL_SYNC   0x2000    			//TODO check if it's needed

#ifdef __cplusplus	/*	C++ Environment	*/
extern "C"{
#endif


/*
 *	Get current OpenCL context.
 *	@return OpenCL context.
 */
extern ELTDECLSPEC ExOpenCLContext ELTAPIFASTENTRY ExGetCurrentCLContext(void);

/*
 *	Create OpenCL Context
 *	@return
 */
extern ELTDECLSPEC ExOpenCLContext ELTAPIENTRY ExCreateCLContext(Enum eEnumFlag, ExOpenCLContext sharedCLContext);

/*
 *	Create shared CL context with OpenGL context
 *	@return CL context.
 */
extern ELTDECLSPEC ExOpenCLContext ELTAPIENTRY ExCreateCLSharedContext(ExOpenGLContext glc, ExWindowContext window, Enum erenderingFlag);

/*
 *	Query Context information
 *	@return
 */
extern ELTDECLSPEC ERESULT ELTAPIENTRY ExQueryCLContext(ExOpenCLContext context, ExHandle param_value, Enum param_name);

/*
 *	Destroy OpenCL Context.
 */
extern ELTDECLSPEC void ELTAPIENTRY ExDestroyCLContext(ExOpenCLContext context);


/*
 *
 *	@return
 */
extern ELTDECLSPEC void* ExCreateCommandQueue(ExOpenCLContext context, ExHandle device);

/*
 *
 *	@return
 */
extern ELTDECLSPEC void* ExCreateProgram(ExOpenCLContext context, ExHandle device, const ExChar* cfilename,...);

/*
 *	Get CL platform identification
 *	@return current CL context.
 */
extern ELTDECLSPEC Int32 ELTAPIENTRY ExGetCLPlatformID(Int32* clSelectedPlatformID, Enum flag);

/*
 *
 */
extern ELTDECLSPEC void ELTAPIENTRY ExPrintCLDevInfo(Int32 iLogMode, ExHandle p_cl_device_id);

/*
 *	Get and return device capability
 *	@return
 */
extern ELTDECLSPEC Int32 ELTAPIENTRY ExGetClDevCap(void* device);


#ifdef __cplusplus	/*	C++ Environment	*/
}
#endif

#endif
