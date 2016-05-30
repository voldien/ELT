#include"elt.h"
#include"elt_def.h"
#include"system/elt_cl.h"
#include"system/elt_gl.h"
#include"system/elt_errorhandler.h"
#include"system/elt_log.h"
#include"system/elt_audio.h"

#ifdef EX_WINDOWS // TODO FIX
#include<windows.h>
#elif defined(EX_LINUX)
#	include"system/unix/unix_win.h"
#	include<X11/Xlib.h>
#	include<malloc.h>
#elif defined(EX_ANDROID)
#   include<android/log.h>
#   include<android/native_activity.h>
#   include<jni.h>
#endif
#include<signal.h>


#if defined(EX_WINDOWS)
#   if defined(EX_VC)
#   	include<delayimp.h>
#   	pragma comment(lib,"delayimp.lib")
#   endif

/**
    Delay load of .dll file which might not be needed TODO how to make it work in the first place...
*/
    /*#pragma comment(linker,"/DELAYLOAD:\"avcodec-55.dll\"")
    #pragma comment(linker,"/DELAYLOAD:\"avdevice-55.dll\"")
    #pragma comment(linker,"/DELAYLOAD:\"avfilter-4.dll\"")
    #pragma comment(linker,"/DELAYLOAD:\"postproc-52.dll\"")
    #pragma comment(linker,"/DELAYLOAD:\"swresample-0.dll\"")
    #pragma comment(linker,"/DELAYLOAD:\"xinput1_3.dll\"")
    #pragma comment(linker,"/DELAYLOAD:\"swscale-2.dll\"")
    #pragma comment(linker,"/DELAYLOAD:\"avutil-52.dll\"")
    #pragma comment(linker,"/DELAYLOAD:\"avformat-55.dll\"")
    #pragma comment(linker,"/DELAYLOAD:\"D3D9.dll\"")
    #pragma comment(linker,"/DELAYLOAD:""OpenCL.dll""")*/
    //#pragma comment(linker,"/delayload:\"libEGL.dll\"")


    //#pragma comment(linker,"/DelayLoad:Ws2_32.dll")
/**
    handle Instance
*/
    extern HINSTANCE hdllMoudle;
#elif defined(EX_LINUX)
#ifdef EX_DEBUG
#	include<mcheck.h>
#endif
#elif defined(EX_MAC)

#endif


/*	TODO relocate to their coresponding platform directory.	*/
#if  defined(EX_WINDOWS) || defined(EX_MSVC)

HINSTANCE hdllMoudle;   /*  handle instance */
BOOL WINAPI DllMain(
_In_  HINSTANCE hinstDLL,
  _In_  DWORD fdwReason,
  _In_  LPVOID lpvReserved){
	switch(fdwReason){
		case DLL_PROCESS_ATTACH:
		  break;
		case DLL_THREAD_ATTACH:
			break;
		case DLL_THREAD_DETACH:
			break;
		case DLL_PROCESS_DETACH:
			break;
		default:
			break;
	}
	// handle instance of the dll.
	hdllMoudle = hinstDLL;
	return TRUE;
}

#endif






/*
 *	High accuracy timer.
 */
extern Uint64 eltTickTime;

/*
 *
 */
extern unsigned long int engineflag;
#define ELT_DEINIT ((unsigned long int)(-1))

/*
 *
 */
void* xcbConnection;



Uint32 ExGetFlag(void){
	return engineflag;
}


void ExEnable(Enum enable){
#ifdef EX_WINDOWS
#endif
	switch(enable){
	case EX_CRASH_TERMINATE:
		signal(SIGTERM,ExSignalCatch);

		break;
	case EX_CRASH_ABORT:

		break;
	case EX_CRASH_FLOAT:

		break;
	case EX_CRASH_EXEPCTION:

		break;
	case EX_OPENCL:
		ExLoadLibrary(EX_TEXT("OpenCL.dll"));
		ExLoadLibrary(EX_TEXT("libOpenCL.so"));
		break;
	default:return;
	}
}

void ExDisable(Enum disable){
#ifdef EX_WINDOWS
#endif
	switch(disable){
	case EX_CRASH_TERMINATE:
		signal(SIGTERM, NULL);
		break;
	case EX_CRASH_ABORT:
		break;
	case EX_CRASH_FLOAT:
		break;
	case EX_CRASH_EXEPCTION:
		break;
	case EX_OPENCL:
		ExUnLoadObject(EX_TEXT("OpenCL.dll"));
		ExUnLoadObject(EX_TEXT("libOpenCL.so"));
		break;
	default:return;
	}
}



#define EX_COMPILER_VERSION(major, minor, revision) EX_TEXT("ELT-")STR(major)EX_TEXT(".")STR(minor)EX_TEXT(".")STR(revision)
const ExChar* ExGetVersion(void){
	return EX_COMPILER_VERSION(EX_VERSION_MAJOR, EX_VERSION_MINOR, EX_VERSION_REVISION);
}

const ExChar* ExGetCompilerName(void){
    return EX_TEXT(EX_COMPILER_NAME);
}
