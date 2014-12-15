#include"elt_cl.h"
#if defined(EX_WINDOWS)
	#include<CL/cl.h>
	#include<CL/cl.h>
	#include<CL/opencl.h>
	#include<CL/cl_gl_ext.h>
	#include<CL/cl_platform.h>
	#include<CL/cl_dx9_media_sharing.h>
	#pragma comment(lib,"OpenCL.lib")
	/*handle to OpenCL Library */
    HANDLE cl_libhandle;
#elif defined(EX_LINUX)
	#include<GL/glew.h>
	#include<CL/cl.h>
	#include<CL/opencl.h>
	#include"CL/cl_gl.h"
#elif defined(EX_MAC)

#endif


#define CL_GET_GPU_INDEX(x) ( ( x ) << (ELT_GPU0 & 0xffffffff))
#define CL_GET_CPU_INDEX(x) ( ( x ) << ELT_CPU0)

cl_context hClContext = NULL;
DECLSPEC void* ELTAPIFASTENTRY ExGetCLContext(void){return hClContext;}

DECLSPEC void* ELTAPIFASTENTRY ExGetCurrentCLContext(void){return hClContext;}


DECLSPEC ERESULT ELTAPIENTRY ExCreateCLContex(Enum flag){
	Int32 cpPlatform,ciErrNum;Uint32 uiDevCount = 0;
	// device ids

    cl_device_id *cdDevices;
    Uint32 errNum;
    cl_context hClContext;
    Uint32 uiDeviceUsed = 0,uiEndDev = 0;

	/**
        Get platform id
	*/
	if(!ExGetCLPlatformID(&cpPlatform,flag))
		ExDevPrint("Failed to Get CL Platform ID");


	cl_context_properties props[] = {
        CL_CONTEXT_PLATFORM,cpPlatform,
		NULL};
	hClContext = clCreateContextFromType(props,CL_DEVICE_TYPE_GPU,NULL, NULL, (cl_int*)&errNum);
    if(!hClContext)
        ExDevPrint("Failed");

	//if(!(hClContext = clCreateContext(props,1, &cdDevices[uiDeviceUsed],0,0,&ciErrNum))){
	//	ExDevPrintf("Failed to Create OpenCL Context based on the OpenGL Context");
	//}
	return (ERESULT)hClContext;
}

DECLSPEC void* ELTAPIENTRY ExCreateCLSharedContext(OpenGLContext glc, WindowContext window,Enum erenderingFlag){
		Int32 cpPlatform,ciErrNum;Uint32 uiDevCount = 0;
		// device ids
	    cl_device_id *cdDevices;
	    Uint32 uiDeviceUsed = 0,uiEndDev = 0;

		// Get Platform ID
		if(!ExGetCLPlatformID(&cpPlatform,erenderingFlag)){
			ExDevPrint("Failed to Get CL Platform ID");
		}

		// Get Device ID
	    if(!(ciErrNum = clGetDeviceIDs((cl_platform_id)cpPlatform, CL_DEVICE_TYPE_GPU, 0, NULL, &uiDevCount))){
			// create OpenCL Devices on the GPU
			cdDevices = (cl_device_id*)malloc(sizeof(cl_device_id) *uiDevCount);
			ciErrNum = clGetDeviceIDs((cl_platform_id)cpPlatform, CL_DEVICE_TYPE_GPU, uiDevCount, cdDevices, NULL);
		}
		// if gpu failure. check CPU
		else if(!(ciErrNum = clGetDeviceIDs((cl_platform_id)cpPlatform, CL_DEVICE_TYPE_CPU, 0, NULL, &uiDevCount))){
			// create OpenCL Devices on the CPU
			cdDevices = (cl_device_id*)malloc(sizeof(cl_device_id) *uiDevCount);
			ciErrNum = clGetDeviceIDs((cl_platform_id)cpPlatform, CL_DEVICE_TYPE_CPU, uiDevCount, cdDevices, NULL);
		}
		// print developing info of the CL
		ExPrintCLDevInfo(0, cdDevices[uiDeviceUsed]);
	    uiDeviceUsed = CLAMP(uiDeviceUsed, 0, uiDevCount - 1);

	#ifdef EX_WINDOWS
		//  get Device Context
		if(window == NULL)window = ExGetCurrentGLDC();
	#endif

		// Context Properties
		cl_context_properties props[7] = {
	        CL_GL_CONTEXT_KHR, (cl_context_properties)glc,
	#ifdef EX_WINDOWS
	        CL_WGL_HDC_KHR, (cl_context_properties)window,
	#elif defined(EX_LINUX)
			CL_GLX_DISPLAY_KHR,(cl_context_properties)window,
	#elif defined(EX_ANDROID)
			CL_EGL_DISPLAY_KHR, (cl_context_properties)window,
	#endif
	        CL_CONTEXT_PLATFORM, (cl_context_properties)cpPlatform,
	        NULL
	    };
#ifdef EX_WINDOWS
		if(erenderingFlag & EX_OPENGL){props[2] = CL_WGL_HDC_KHR;}
		else if(erenderingFlag & EX_DIRECTX){props[0] = CL_CONTEXT_ADAPTER_D3D9_KHR;}
#elif defined(EX_LINUX)
		if(erenderingFlag & EX_OPENGL){props[2] = CL_GLX_DISPLAY_KHR;}
#endif
		else if(erenderingFlag & EX_OPENCL){props[2] = CL_CGL_SHAREGROUP_KHR;}
		else if(erenderingFlag & EX_OPENGLES){props[2] = CL_EGL_DISPLAY_KHR;}

		if(!(hClContext = clCreateContext(props,1, &cdDevices[uiDeviceUsed],0,0,&ciErrNum))){
			ExDevPrint("Failed to Create OpenCL Context based on the OpenGL Context");
		}

		free(cdDevices);
		return (void*)hClContext;
}

DECLSPEC void ELTAPIENTRY ExReleaseCL(void){
	if(hClContext)
		if(clReleaseContext(hClContext) != CL_FALSE)
			ExDevPrint("Failed to Release Contex");
}
DECLSPEC void ELTAPIENTRY ExReleaseCLContext(void* context){
	ExIsCLError(clReleaseContext(context));
}

DECLSPEC Int32 ELTAPIENTRY ExGetCLPlatformID(Int32* clSelectedPlatformID,Enum flag){
    char chBuffer[1024];
    cl_uint num_platforms,num_device;
    cl_uint num_gpu,num_cpu;
    cl_device_id device_id[32];
    cl_device_info device_info;

    cl_platform_id temp_clPlatformIDs;
    cl_platform_id* clPlatformIDs;
    cl_int ciErrNum;
    *clSelectedPlatformID = NULL;

    /**
        Get number of platform identification
    */
    ciErrNum = clGetPlatformIDs (0, NULL, &num_platforms);
    if (ciErrNum != CL_SUCCESS){
        ExDevPrintf(" Error %i in clGetPlatformIDs Call !!!", ciErrNum);
        return -1000;
    }
	else{
		if(num_platforms == 0){
            ExDevPrint("No OpenCL platform found!");
			return -2000;
		}
		else{
			cl_uint i;

            ciErrNum = clGetPlatformIDs (num_platforms, &temp_clPlatformIDs, NULL);

			ciErrNum = clGetDeviceIDs(temp_clPlatformIDs,CL_DEVICE_TYPE_GPU, NULL,NULL,&num_gpu);

			ciErrNum = clGetDeviceIDs(temp_clPlatformIDs,CL_DEVICE_TYPE_CPU, NULL,NULL,&num_cpu);
			if(ciErrNum == CL_DEVICE_NOT_FOUND)
                ExDevPrint("Couldn't find");


			if((clPlatformIDs = (cl_platform_id*)malloc(num_platforms * sizeof(cl_platform_id))) == EX_NULL){
				ExDevPrint("Failed to allocate memory for cl_platform ID's!");
				return -3000;
			}

            // get platform info for each platform and trap the NVIDIA platform if found
            ciErrNum = clGetPlatformIDs (num_platforms, clPlatformIDs, NULL);
            for(i = 0; i < num_platforms; ++i){


                ciErrNum = clGetDeviceIDs(clPlatformIDs[i], CL_DEVICE_TYPE_GPU,1,&device_id[0],NULL);
                //clGetDeviceInfo(clPlatformIDs[i], CL_DEVICE_TYPE_GPU,1,&device_id,&num_cpu);
                ciErrNum = clGetPlatformInfo (clPlatformIDs[i], CL_PLATFORM_NAME, 1024, &chBuffer, NULL);


                //ExPrintCLDevInfo(0,&device_id[0]);

                //clGetDeviceInfo(device_id,&device_info,0,0,0);

                if(ciErrNum == CL_SUCCESS){
                    if(strstr(chBuffer, "NVIDIA") != NULL){	// nvidia exists
                        *clSelectedPlatformID = (Int)clPlatformIDs[i];
                        break;
                    }else if(strstr(chBuffer,"AMD") != NULL){
                        *clSelectedPlatformID = (Int)clPlatformIDs[i];
                        break;
                    }
                }
				continue;
            }

			//ExPrintCLDevInfo(0,*clPlatformIDs);
            // default to zeroeth platform if NVIDIA not found
            if(*clSelectedPlatformID == NULL){
                ExPrintf("WARNING: NVIDIA OpenCL platform not found - defaulting to first platform!\n\n");
                *clSelectedPlatformID = (Int)clPlatformIDs[0];
            }

            free(clPlatformIDs);
			return ciErrNum;
		}

	}
	return FALSE;
}

DECLSPEC void ELTAPIENTRY ExPrintCLDevInfo(Int32 iLogMode, void* p_cl_device_id){
    if(!p_cl_device_id)
        return;
    return 0;
    char device_string[1024];
    Boolean nv_device_attibute_query = FALSE;
	cl_device_id device = (cl_device_id)p_cl_device_id;
    // CL_DEVICE_NAME
    clGetDeviceInfo(device, CL_DEVICE_NAME, sizeof(device_string), &device_string, EX_NULL);
    ExPrintf("  CL_DEVICE_NAME: \t\t\t%s\n", device_string);

    // CL_DEVICE_VENDOR
    clGetDeviceInfo(device, CL_DEVICE_VENDOR, sizeof(device_string), &device_string, EX_NULL);
    ExPrintf("  CL_DEVICE_VENDOR: \t\t\t%s\n", device_string);

    // CL_DRIVER_VERSION
    clGetDeviceInfo(device, CL_DRIVER_VERSION, sizeof(device_string), &device_string, EX_NULL);
    ExPrintf("  CL_DRIVER_VERSION: \t\t\t%s\n", device_string);

    // CL_DEVICE_VERSION
    clGetDeviceInfo(device, CL_DEVICE_VERSION, sizeof(device_string), &device_string, EX_NULL);
    ExPrintf("  CL_DEVICE_VERSION: \t\t\t%s\n", device_string);

	#if !defined(__APPLE__) && !defined(__MACOSX)
    // CL_DEVICE_OPENCL_C_VERSION (if CL_DEVICE_VERSION version > 1.0)
    if(strncmp("OpenCL 1.0", device_string, 10) != 0){
        // This code is unused for devices reporting OpenCL 1.0, but a def is needed anyway to allow compilation using v 1.0 headers
        // This constant isn't #defined in 1.0
        #ifndef CL_DEVICE_OPENCL_C_VERSION
            #define CL_DEVICE_OPENCL_C_VERSION 0x103D
        #endif

        clGetDeviceInfo(device, CL_DEVICE_OPENCL_C_VERSION, sizeof(device_string), &device_string, NULL);
        ExPrintf("  CL_DEVICE_OPENCL_C_VERSION: \t\t%s\n", device_string);
    }
#endif


    // CL_DEVICE_TYPE
    cl_device_type type;
    clGetDeviceInfo(device, CL_DEVICE_TYPE, sizeof(type), &type, NULL);
    if( type & CL_DEVICE_TYPE_CPU )
        ExPrintf("  CL_DEVICE_TYPE:\t\t\t%s\n", "CL_DEVICE_TYPE_CPU");
    if( type & CL_DEVICE_TYPE_GPU )
        ExPrintf("  CL_DEVICE_TYPE:\t\t\t%s\n", "CL_DEVICE_TYPE_GPU");
    if( type & CL_DEVICE_TYPE_ACCELERATOR )
        ExPrintf("  CL_DEVICE_TYPE:\t\t\t%s\n", "CL_DEVICE_TYPE_ACCELERATOR");
    if( type & CL_DEVICE_TYPE_DEFAULT )
        ExPrintf("  CL_DEVICE_TYPE:\t\t\t%s\n", "CL_DEVICE_TYPE_DEFAULT");

    // CL_DEVICE_MAX_COMPUTE_UNITS
    cl_uint compute_units;
    clGetDeviceInfo(device, CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(compute_units), &compute_units, NULL);
    ExPrintf("  CL_DEVICE_MAX_COMPUTE_UNITS:\t\t%u\n", compute_units);

	// CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS
    size_t workitem_dims;
    clGetDeviceInfo(device, CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, sizeof(workitem_dims), &workitem_dims, NULL);
    ExPrintf( "  CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS:\t%u\n", workitem_dims);

    // CL_DEVICE_MAX_WORK_ITEM_SIZES
    size_t workitem_size[3];
    clGetDeviceInfo(device, CL_DEVICE_MAX_WORK_ITEM_SIZES, sizeof(workitem_size), &workitem_size, NULL);
    ExPrintf("  CL_DEVICE_MAX_WORK_ITEM_SIZES:\t%u / %u / %u \n", workitem_size[0], workitem_size[1], workitem_size[2]);

    // CL_DEVICE_MAX_WORK_GROUP_SIZE
    size_t workgroup_size;
    clGetDeviceInfo(device, CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(workgroup_size), &workgroup_size, NULL);
    ExPrintf("  CL_DEVICE_MAX_WORK_GROUP_SIZE:\t%u\n", workgroup_size);

    // CL_DEVICE_MAX_CLOCK_FREQUENCY
    cl_uint clock_frequency;
    clGetDeviceInfo(device, CL_DEVICE_MAX_CLOCK_FREQUENCY, sizeof(clock_frequency), &clock_frequency, NULL);
    ExPrintf("  CL_DEVICE_MAX_CLOCK_FREQUENCY:\t%u MHz\n", clock_frequency);

    // CL_DEVICE_ADDRESS_BITS
    cl_uint addr_bits;
    clGetDeviceInfo(device, CL_DEVICE_ADDRESS_BITS, sizeof(addr_bits), &addr_bits, NULL);
    ExPrintf("  CL_DEVICE_ADDRESS_BITS:\t\t%u\n", addr_bits);

    // CL_DEVICE_MAX_MEM_ALLOC_SIZE
    cl_ulong max_mem_alloc_size;
    clGetDeviceInfo(device, CL_DEVICE_MAX_MEM_ALLOC_SIZE, sizeof(max_mem_alloc_size), &max_mem_alloc_size, NULL);
    ExPrintf("  CL_DEVICE_MAX_MEM_ALLOC_SIZE:\t\t%u MByte\n", (unsigned int)(max_mem_alloc_size / (1024 * 1024)));

    // CL_DEVICE_GLOBAL_MEM_SIZE
    cl_ulong mem_size;
    clGetDeviceInfo(device, CL_DEVICE_GLOBAL_MEM_SIZE, sizeof(mem_size), &mem_size, NULL);
    ExPrintf("  CL_DEVICE_GLOBAL_MEM_SIZE:\t\t%u MByte\n", (unsigned int)(mem_size / (1024 * 1024)));

    // CL_DEVICE_ERROR_CORRECTION_SUPPORT
    cl_bool error_correction_support;
    clGetDeviceInfo(device, CL_DEVICE_ERROR_CORRECTION_SUPPORT, sizeof(error_correction_support), &error_correction_support, NULL);
    ExDevPrintf("  CL_DEVICE_ERROR_CORRECTION_SUPPORT:\t%s\n", error_correction_support == CL_TRUE ? "yes" : "no");

    // CL_DEVICE_LOCAL_MEM_TYPE
    cl_device_local_mem_type local_mem_type;
    clGetDeviceInfo(device, CL_DEVICE_LOCAL_MEM_TYPE, sizeof(local_mem_type), &local_mem_type, NULL);
     ExPrintf("  CL_DEVICE_LOCAL_MEM_TYPE:\t\t%s\n", local_mem_type == 1 ? "local" : "global");

    // CL_DEVICE_LOCAL_MEM_SIZE
    clGetDeviceInfo(device, CL_DEVICE_LOCAL_MEM_SIZE, sizeof(mem_size), &mem_size, NULL);
    ExPrintf("  CL_DEVICE_LOCAL_MEM_SIZE:\t\t%u KByte\n", (unsigned int)(mem_size / 1024));

    // CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE
    clGetDeviceInfo(device, CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE, sizeof(mem_size), &mem_size, NULL);
     ExPrintf("  CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE:\t%u KByte\n", (unsigned int)(mem_size / 1024));

    // CL_DEVICE_QUEUE_PROPERTIES
    cl_command_queue_properties queue_properties;
    clGetDeviceInfo(device, CL_DEVICE_QUEUE_PROPERTIES, sizeof(queue_properties), &queue_properties, NULL);
    if( queue_properties & CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE )
        ExPrintf("  CL_DEVICE_QUEUE_PROPERTIES:\t\t%s\n", "CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE");
    if( queue_properties & CL_QUEUE_PROFILING_ENABLE )
         ExPrintf("  CL_DEVICE_QUEUE_PROPERTIES:\t\t%s\n", "CL_QUEUE_PROFILING_ENABLE");

    // CL_DEVICE_IMAGE_SUPPORT
    cl_bool image_support;
    clGetDeviceInfo(device, CL_DEVICE_IMAGE_SUPPORT, sizeof(image_support), &image_support, NULL);
     ExPrintf("  CL_DEVICE_IMAGE_SUPPORT:\t\t%u\n", image_support);

    // CL_DEVICE_MAX_READ_IMAGE_ARGS
    cl_uint max_read_image_args;
    clGetDeviceInfo(device, CL_DEVICE_MAX_READ_IMAGE_ARGS, sizeof(max_read_image_args), &max_read_image_args, NULL);
     ExPrintf("  CL_DEVICE_MAX_READ_IMAGE_ARGS:\t%u\n", max_read_image_args);

    // CL_DEVICE_MAX_WRITE_IMAGE_ARGS
    cl_uint max_write_image_args;
    clGetDeviceInfo(device, CL_DEVICE_MAX_WRITE_IMAGE_ARGS, sizeof(max_write_image_args), &max_write_image_args, NULL);
     ExPrintf("  CL_DEVICE_MAX_WRITE_IMAGE_ARGS:\t%u\n", max_write_image_args);

    // CL_DEVICE_SINGLE_FP_CONFIG
    cl_device_fp_config fp_config;
    clGetDeviceInfo(device, CL_DEVICE_SINGLE_FP_CONFIG, sizeof(cl_device_fp_config), &fp_config, NULL);
     ExPrintf("  CL_DEVICE_SINGLE_FP_CONFIG:\t\t%s%s%s%s%s%s\n",
        fp_config & CL_FP_DENORM ? "denorms " : "",
        fp_config & CL_FP_INF_NAN ? "INF-quietNaNs " : "",
        fp_config & CL_FP_ROUND_TO_NEAREST ? "round-to-nearest " : "",
        fp_config & CL_FP_ROUND_TO_ZERO ? "round-to-zero " : "",
        fp_config & CL_FP_ROUND_TO_INF ? "round-to-inf " : "",
        fp_config & CL_FP_FMA ? "fma " : "");

    // CL_DEVICE_IMAGE2D_MAX_WIDTH, CL_DEVICE_IMAGE2D_MAX_HEIGHT, CL_DEVICE_IMAGE3D_MAX_WIDTH, CL_DEVICE_IMAGE3D_MAX_HEIGHT, CL_DEVICE_IMAGE3D_MAX_DEPTH
    size_t szMaxDims[5];
    ExPrintf("\n  CL_DEVICE_IMAGE <dim>");
    clGetDeviceInfo(device, CL_DEVICE_IMAGE2D_MAX_WIDTH, sizeof(size_t), &szMaxDims[0], NULL);
     ExPrintf("\t\t\t2D_MAX_WIDTH\t %u\n", szMaxDims[0]);
    clGetDeviceInfo(device, CL_DEVICE_IMAGE2D_MAX_HEIGHT, sizeof(size_t), &szMaxDims[1], NULL);
     ExPrintf("\t\t\t\t\t2D_MAX_HEIGHT\t %u\n", szMaxDims[1]);
    clGetDeviceInfo(device, CL_DEVICE_IMAGE3D_MAX_WIDTH, sizeof(size_t), &szMaxDims[2], NULL);
     ExPrintf("\t\t\t\t\t3D_MAX_WIDTH\t %u\n", szMaxDims[2]);
    clGetDeviceInfo(device, CL_DEVICE_IMAGE3D_MAX_HEIGHT, sizeof(size_t), &szMaxDims[3], NULL);
     ExPrintf("\t\t\t\t\t3D_MAX_HEIGHT\t %u\n", szMaxDims[3]);
    clGetDeviceInfo(device, CL_DEVICE_IMAGE3D_MAX_DEPTH, sizeof(size_t), &szMaxDims[4], NULL);
     ExPrintf("\t\t\t\t\t3D_MAX_DEPTH\t %u\n", szMaxDims[4]);

    // CL_DEVICE_EXTENSIONS: get device extensions, and if any then parse & log the string onto separate lines
    clGetDeviceInfo(device, CL_DEVICE_EXTENSIONS, sizeof(device_string), &device_string, NULL);
    if (device_string != 0) {
      /*   ExPrintf("\n  CL_DEVICE_EXTENSIONS:");
        std::string stdDevString;
        stdDevString = std::string(device_string);
        size_t szOldPos = 0;
        size_t szSpacePos = stdDevString.find(' ', szOldPos); // extensions string is space delimited
        while (szSpacePos != stdDevString.npos)
        {
            if( strcmp("cl_nv_device_attribute_query", stdDevString.substr(szOldPos, szSpacePos - szOldPos).c_str()) == 0 )
                nv_device_attibute_query = true;

            if (szOldPos > 0){
                ExPrintf("\t\t");
            }
             ExPrintf("\t\t\t%s\n", stdDevString.substr(szOldPos, szSpacePos - szOldPos).c_str());

            do {
                szOldPos = szSpacePos + 1;
                szSpacePos = stdDevString.find(' ', szOldPos);
            } while (szSpacePos == szOldPos);
        }
         ExPrintf("\n");*/
    }
    else{
         ExPrintf("  CL_DEVICE_EXTENSIONS: None\n");
    }

    if(nv_device_attibute_query){
        cl_uint compute_capability_major, compute_capability_minor;
        clGetDeviceInfo(device, CL_DEVICE_COMPUTE_CAPABILITY_MAJOR_NV, sizeof(cl_uint), &compute_capability_major, NULL);
        clGetDeviceInfo(device, CL_DEVICE_COMPUTE_CAPABILITY_MINOR_NV, sizeof(cl_uint), &compute_capability_minor, NULL);
         ExPrintf("\n  CL_DEVICE_COMPUTE_CAPABILITY_NV:\t%u.%u\n", compute_capability_major, compute_capability_minor);

         ExPrintf("  NUMBER OF MULTIPROCESSORS:\t\t%u\n", compute_units); // this is the same value reported by CL_DEVICE_MAX_COMPUTE_UNITS
        // ExDevPrintf("  NUMBER OF CUDA CORES:\t\t\t%u\n", ConvertSMVer2Cores(compute_capability_major, compute_capability_minor) * compute_units);

        cl_uint regs_per_block;
        clGetDeviceInfo(device, CL_DEVICE_REGISTERS_PER_BLOCK_NV, sizeof(cl_uint), &regs_per_block, NULL);
         ExPrintf("  CL_DEVICE_REGISTERS_PER_BLOCK_NV:\t%u\n", regs_per_block);

        cl_uint warp_size;
        clGetDeviceInfo(device, CL_DEVICE_WARP_SIZE_NV, sizeof(cl_uint), &warp_size, NULL);
         ExPrintf("  CL_DEVICE_WARP_SIZE_NV:\t\t%u\n", warp_size);

        cl_bool gpu_overlap;
        clGetDeviceInfo(device, CL_DEVICE_GPU_OVERLAP_NV, sizeof(cl_bool), &gpu_overlap, NULL);
         ExPrintf("  CL_DEVICE_GPU_OVERLAP_NV:\t\t%s\n", gpu_overlap == CL_TRUE ? "CL_TRUE" : "CL_FALSE");

        cl_bool exec_timeout;
        clGetDeviceInfo(device, CL_DEVICE_KERNEL_EXEC_TIMEOUT_NV, sizeof(cl_bool), &exec_timeout, NULL);
         ExPrintf("  CL_DEVICE_KERNEL_EXEC_TIMEOUT_NV:\t%s\n", exec_timeout == CL_TRUE ? "CL_TRUE" : "CL_FALSE");

        cl_bool integrated_memory;
        clGetDeviceInfo(device, CL_DEVICE_INTEGRATED_MEMORY_NV, sizeof(cl_bool), &integrated_memory, NULL);
         ExPrintf("  CL_DEVICE_INTEGRATED_MEMORY_NV:\t%s\n", integrated_memory == CL_TRUE ? "CL_TRUE" : "CL_FALSE");
    }

    // CL_DEVICE_PREFERRED_VECTOR_WIDTH_<type>
     ExPrintf("  CL_DEVICE_PREFERRED_VECTOR_WIDTH_<t>\t");
    cl_uint vec_width [6];
    clGetDeviceInfo(device, CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR, sizeof(cl_uint), &vec_width[0], NULL);
    clGetDeviceInfo(device, CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT, sizeof(cl_uint), &vec_width[1], NULL);
    clGetDeviceInfo(device, CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT, sizeof(cl_uint), &vec_width[2], NULL);
    clGetDeviceInfo(device, CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG, sizeof(cl_uint), &vec_width[3], NULL);
    clGetDeviceInfo(device, CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT, sizeof(cl_uint), &vec_width[4], NULL);
    clGetDeviceInfo(device, CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE, sizeof(cl_uint), &vec_width[5], NULL);
     ExPrintf("CHAR %u, SHORT %u, INT %u, LONG %u, FLOAT %u, DOUBLE %u\n\n\n",
           vec_width[0], vec_width[1], vec_width[2], vec_width[3], vec_width[4], vec_width[5]);

}

DECLSPEC Int32 ELTAPIENTRY ExGetClDevCap(void* device){
    char cDevString[1024];
    Boolean bDevAttributeQuery = FALSE;
    int iDevArch = -1;
	cl_int iComputeCapMajor, iComputeCapMinor;

    // Get device extensions, and if any then search for cl_nv_device_attribute_query
    clGetDeviceInfo((cl_device_id)device, CL_DEVICE_EXTENSIONS, sizeof(cDevString), &cDevString, NULL);
    if (cDevString != 0) {
		//string stdDevString;
        //stdDevString = std::string(cDevString);
        //size_t szOldPos = 0;
        //size_t szSpacePos = stdDevString.find(' ', szOldPos); // extensions string is space delimited
        //while (szSpacePos != stdDevString.npos)
        //{
        //    if( strcmp("cl_nv_device_attribute_query", stdDevString.substr(szOldPos, szSpacePos - szOldPos).c_str()) == 0 )
        //    {
        //        bDevAttributeQuery = true;
        //    }
        //
        //    do {
        //        szOldPos = szSpacePos + 1;
        //        szSpacePos = stdDevString.find(' ', szOldPos);
        //    } while (szSpacePos == szOldPos);
        //}
    }

    // if search succeeded, get device caps
    if(bDevAttributeQuery){

        clGetDeviceInfo((cl_device_id)device, CL_DEVICE_COMPUTE_CAPABILITY_MAJOR_NV, sizeof(cl_uint), (void*)&iComputeCapMajor, NULL);
        clGetDeviceInfo((cl_device_id)device, CL_DEVICE_COMPUTE_CAPABILITY_MINOR_NV, sizeof(cl_uint), (void*)&iComputeCapMinor, NULL);
        iDevArch = (10 * iComputeCapMajor) + iComputeCapMinor;
    }

    return iDevArch;
}
