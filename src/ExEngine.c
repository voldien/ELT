#include"EngineEx.h"
#include"system/elt_cl.h"
#include"system/elt_gl.h"
#include"system/elt_errorhandler.h"
#ifdef EX_WINDOWS // TODO FIX
#   include"system/win/wnd_input.h"
#   include"system/win/win_net.h"
#elif defined(EX_LINUX)
#	include"system/unix/unix_win.h"
#elif defined(EX_ANDROID)
#   include<android/log.h>
#   include<android/native_activity.h>
#   include<jni.h>
#endif
#include"system/elt_log.h"
#include"system/elt_audio.h"
#include<signal.h>

/**
    Linux flags Link
    -lGL -lX11 -lGLEW -lXrender -ldl -lOpenCL -lEGL
*/

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

#ifdef EX_WINDOWS

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


extern Uint64 elt_time;     /**  high accuracy timer   */


/**
    \Initialize Engine Library Toolkit
*/
DECLSPEC ERESULT ELTAPIENTRY ExInit(Enum engineFlag){
	ERESULT _h_result = E_OK;
	HANDLE hmodule;
	Int32 hConHandle;
	Long lStdHandle;

	/*
        if all is already initilated return !
	*/
    if(engineDescription.EngineFlag & ELT_INIT_EVERYTHING)
        return 2;


#ifdef EX_DEBUG || (EX_ENGINE_VERSION_MAJOR <= 0)
	#if defined(EX_VC) || defined(EX_WINDOWS)
	// debug shell
	// redirect unbuffered STDOUT to the console
	lStdHandle = (long)GetStdHandle(STD_OUTPUT_HANDLE);
	////
	hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
	/**/
	m_file_log = fopen("EngineExDevLog.txt", "w+" );
	FILE* fopen;
	/**/
	if(dup2(1,(fopen = fdopen(4,"w+"))) == -1)
        fprintf(stderr,"error");
    /**/
    /*  cause fork to fail somehow*/
	*stdout = *m_file_log;
	setvbuf(fopen, NULL, _IONBF, 0 );
	/**
        visual studio debug
	*/
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_ALLOC_MEM_DF);
	_CrtSetReportMode(_CRT_ASSERT , _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ASSERT , _CRTDBG_FILE_STDERR);
	#elif defined(EX_UNIX)
        /**

        */
        mtrace();
	#endif
#endif

/*	unicode		*/
#ifdef UNICODE
	printf(EX_TEXT("Initialize engine version: %d.%d.%d\n"),EX_ENGINE_VERSION_MAJOR,EX_ENGINE_VERSION_MINOR,EX_ENGINE_VERSION_REVISION);
	wprintf(EX_TEXT("Operating System : %s\n"),ExGetOSName());
#endif



#if defined(EX_WINDOWS)


#elif defined(EX_LINUX)
    /**
            Create Connection with Display Server.
    */
    display = XOpenDisplay(getenv("DISPLAY"));
    if(!display)
        ExError("couldn't open Display\n");
    /**
        enable X events
    */
    XAllowEvents(display , SyncBoth,CurrentTime);
#elif defined(EX_APPLE)

#elif defined(EX_MAC)

#elif defined(EX_ANDROID)

#endif
	/**
		Initialize sub system
	*/
	ExInitSubSystem(engineFlag);

	if(_h_result = ExInitErrorHandler()){

	}
	else{
	    ExError(EX_TEXT("Failed to initialize error handler."));
    }

	engineDescription.EngineFlag |= engineFlag;

	return _h_result;
}
/*

*/
DECLSPEC ERESULT ELTAPIENTRY ExInitSubSystem(Uint32 engineflag){
	ERESULT hr = 0;
	HANDLE hmodule;
	if(ELT_INIT_VIDEO & engineflag){
        #ifdef EX_WINDOWS
		/* Load OpenGL library*/
		ExIsWinError(!(hmodule = LoadLibrary(EX_TEXT("OpenGL32.dll"))));
        #elif defined(EX_LINUX)

        #elif defined(EX_ANDROID)

        #endif
	}
	if(ELT_INIT_JOYSTICK & engineflag){

	}
	if(ELT_INIT_AUDIO & engineflag){
		ExAudioInit(0);
	}
	if(ELT_INIT_GAMECONTROLLER & engineflag){
#ifdef EX_WINDOWS
		ExLoadLibrary(EX_TEXT("Xinput.dll"));
		//ExInitGameController();
#elif defined(EX_LINUX)

#elif defined(EX_ANDROID)

#endif
	}
	if(ELT_INIT_EVENTS & engineflag){
#if defined(EX_WINDOWS)

#elif defined(EX_LINUX)

#endif
	}
	if(ELT_INIT_TIMER & engineflag){
		elt_time = clock();
	}
	if(ELT_INIT_NET & engineflag){
	    #ifdef EX_LINUX
        ExLoadLibrary("");
        #elif defined(EX_ANDROID)

        #elif defined(EX_WINDOWS)
        ExLoadLibrary(EX_TEXT("WS2_32.dll"));
        #endif
	}
	return hr;
}


DECLSPEC void ELTAPIENTRY ExQuitSubSytem(Uint32 engineflag){
	if(ELT_INIT_TIMER & engineflag){
        #ifdef EX_WINDOWS   // EX_WINDOWS

        #elif defined(EX_LINUX)

        #endif
	}
	if(ELT_INIT_AUDIO & engineflag){
        #ifdef EX_WINDOWS
        ExUnLoadObject(ExGetFileModule(EX_TEXT("")));
        #elif defined(EX_LINUX)
        ExUnLoadObject(ExGetFileModule(EX_TEXT("libasound.so")));
        #endif
		ExAudioInit(0);
	}
	if(ELT_INIT_JOYSTICK & engineflag){
        ExJoyStickClose(0);
        ExJoyStickClose(1);
        ExJoyStickClose(2);
        ExJoyStickClose(3);
		//ExJoyStickShutDown();
	}
	if(ELT_INIT_GAMECONTROLLER & engineflag){
        #ifdef EX_WINDOWS
            ExUnLoadObject(ExGetFileModule(EX_TEXT("Xinput.dll")));
        #endif // EX_WINDOWS
	}
	if(ELT_INIT_NET & engineflag){
#ifdef EX_WINDOWS
		ExUnLoadObject(ExGetFileModule(EX_TEXT("Wininet.dll")));
#elif defined(EX_LINUX)

#endif
	}
	if(ELT_INIT_VIDEO & engineflag){

	}
	if(ELT_INIT_NET & engineflag){
	    #ifdef EX_LINUX
        ExLoadLibrary("");
        #elif defined(EX_WINDOWS)
        ExLoadLibrary(EX_TEXT(""));
        #endif
	}
}
/*

*/
DECLSPEC void ELTAPIENTRY ExShutDown(void){
#ifdef EX_LINUX
    struct mallinfo mi;
#endif 	// EX_LINUX
	ExQuitSubSytem(0xFFFFFFFF);
#ifdef EX_WINDOWS
	DEVMODE d = {0};
	Int32 display;

	/*
		delete opencl and opengl context
	*/
	ExReleaseCL();
	ExDestroyContext(ExGetCurrentGLDrawable(), ExGetCurrentOpenGLContext());

	ExUnRegisterClasses();
	if(ExIsModuleLoaded(EX_TEXT("Ws2_32.dll")))
		WSACleanup();

	#if defined(EX_INCLUDE_DIRECTX)
	ExReleaseDirectX();
	#endif
	ExReleaseDirectSound();
	ExRelaseNet();

	// restore screen
	display = ChangeDisplaySettings(&d, EX_NULL);
	FreeLibrary(GetModuleHandle(EX_NULL));

/**
    Linux
*/
#elif defined(EX_LINUX)
	ExReleaseCL();
	ExDestroyContext(ExGetCurrentGLDrawable(), ExGetCurrentOpenGLContext());
	eglTerminate(eglGetCurrentDisplay());
	//ExDestroyCurrentContext();
    	XFlush(display);
	XCloseDisplay(display);

#elif defined(EX_APPLE)

#elif defined(EX_MAC)

#endif


/*
	debug information
*/
#ifdef EX_DEBUG || (EX_ENGINE_VERSION_MAJOR <= 0)
	#if defined(EX_VC) || defined(EX_WINDOWS)

	#elif defined(EX_UNIX)
	mi = mallinfo();
	printf("%d\n", mi.arena);

	muntrace();
	#endif

#endif
	fclose(m_file_log);
}

DECLSPEC void ELTAPIENTRY ExEnable(Enum enable){
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
	default:return;
	}
}
DECLSPEC void ELTAPIENTRY ExDisable(Enum disable){
#ifdef EX_WINDOWS
#endif
	switch(disable){
	case EX_CRASH_TERMINATE:
		signal(SIGTERM,NULL);
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
	default:return;
	}
}


#define EX_TO_TEXT(x) "x"
#define EX_COMPILER_VERSION(major, minor, revision) EX_TEXT("ELT-")EX_TO_TEXT(major)EX_TEXT(".")EX_TO_TEXT(minor)EX_TEXT(".")EX_TO_TEXT(revision)
DECLSPEC const ExChar* ELTAPIENTRY ExGetVersion(void){
	return EX_COMPILER_VERSION(EX_MAJOR_VERSION, EX_MINOR_VERSION, EX_REVISION);
}

DECLSPEC const ExChar* ELTAPIENTRY ExGetCompilerName(void){
    return EX_TEXT(EX_COMPILER_NAME);
}
