#include"EngineEx.h"
#include"System/elt_cl.h"
#include"System/elt_gl.h"
#include"System/elt_errorhandler.h"
#ifdef EX_WINDOWS // TODO FIX
	#include"System/Win32/wnd_input.h"
	#include"System/Win32/win_net.h"
#endif
#include"System/elt_log.h"
#include"System/elt_audio.h"
#include<signal.h>

/**
    Linux flags Link
    -lGL -lX11 -lGLEW -lXrender -ldl -lOpenCL -lEGL
*/

#if defined(EX_WINDOWS)
    #if defined(EX_VC)
    #	pragma comment(lib,"opengl32.lib")
    #	include<delayimp.h>
    #	pragma comment(lib,"DelayImp.lib")
    #endif

/**
    // Delay load of .dll file which might not be needed
*/
    #pragma comment(linker,"/DELAYLOAD:avcodec-55.dll")
    #pragma comment(linker,"/DELAY:UNLOAD")
    #pragma comment(linker,"/DELAYLOAD:avdevice-55.dll")
    #pragma comment(linker,"/DELAY:UNLOAD")
    #pragma comment(linker,"/DELAYLOAD:avfilter-4.dll")
    #pragma comment(linker,"/DELAY:UNLOAD")
    #pragma comment(linker,"/DELAYLOAD:postproc-52.dll")
    #pragma comment(linker,"/DELAY:UNLOAD")
    #pragma comment(linker,"/DELAYLOAD:swresample-0.dll")
    #pragma comment(linker,"/DELAY:UNLOAD")
    #pragma comment(linker,"/DELAYLOAD:xinput1_3.dll")
    #pragma comment(linker,"/DELAY:UNLOAD")
    #pragma comment(linker,"/DELAYLOAD:swscale-2.dll")
    #pragma comment(linker,"/DELAY:UNLOAD")
    #pragma comment(linker,"/DELAYLOAD:avutil-52.dll")
    #pragma comment(linker,"/DELAY:UNLOAD")
    #pragma comment(linker,"/DELAYLOAD:avformat-55.dll")
    #pragma comment(linker,"/DELAY:UNLOAD")
    #pragma comment(linker,"/DELAYLOAD:D3D9.dll")
    #pragma comment(linker,"/DELAY:UNLOAD")*/


    //#pragma comment(linker,"/DelayLoad:Ws2_32.Dll")
    //#pragma comment(linker,"/Delay:unload")
/*
    // Instance
*/
    extern HINSTANCE hdllMoudle;
#elif defined(EX_LINUX)
#ifdef EX_DEBUG
#	include<mcheck.h>
#endif
#elif defined(EX_MAC)

#endif
/**
	// allocate data about the creator.
*/
char* Developer = "BroodCity Entertainment";
#ifdef EX_WINDOWS
HINSTANCE hdllMoudle = GetModuleHandle(EX_NULL);

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
	// hinstance of the dll.
	hdllMoudle = hinstDLL;
	return TRUE;
}
#endif

extern unsigned int elt_timer;


/**
    \Initialize Engine Library Toolkit
*/
DECLSPEC ERESULT ELTAPIENTRY ExInit(Enum engineFlag){
	ERESULT _h_result = E_OK;
	HANDLE hmodule;
	Int32 hConHandle;
	Long lStdHandle;

	/*
	*/
    if(engineDescription.EngineFlag & ELT_INIT_EVERYTHING)
        return 2;
	// debug shell
#if defined(EX_DEBUG) || (EX_ENGINE_VERSION_MAJOR <= 0)
#ifdef EX_WINDOWS

#elif defined(EX_LINUX)

#endif
		// redirect unbuffered STDOUT to the console
		//lStdHandle = (long)GetStdHandle(STD_OUTPUT_HANDLE);
		////
		//hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
		//
		m_file_log = fopen("EngineExDevLog.txt", "w+" );
		//
		*stdout = *m_file_log;
		setvbuf(stdout, NULL, _IONBF, 0 );
#endif
#ifdef EX_DEBUG
	#ifdef EX_VC
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_ALLOC_MEM_DF);
		_CrtSetReportMode(_CRT_ASSERT , _CRTDBG_MODE_FILE);
		_CrtSetReportFile(_CRT_ASSERT , _CRTDBG_FILE_STDERR);
	#endif
#endif

// unicode
#ifdef UNICODE
	printf("Initialize engine version: %d.%d.%d\n",EX_ENGINE_VERSION_MAJOR,EX_ENGINE_VERSION_MINOR,EX_ENGINE_VERSION_BUGFIX);
	wprintf(EX_TEXT("Operating System : %s\n"),ExGetOSName());
#endif



#if defined(EX_WINDOWS)

	if(engineFlag & ELT_INIT_VIDEO){
		// load opengl library
		ExIsWinError(!(hmodule = LoadLibrary(EX_TEXT("OpenGL32.dll"))));
	}
	if(engineFlag & ELT_INIT_TIMER){
		elt_time = ExCurrentTime();
	}
	if(engineFlag & ELT_INIT_AUDIO){
		ExAudioInit(0);
	}
	if(engineFlag & ELT_INIT_NET){

	}
	if(engineFlag & ELT_INIT_GAMECONTROLLER){
		//ExInitG
	}
	if(engineFlag & ELT_INIT_EVENTS){

	}

	// Input Request
	if(engineFlag & ENGINE_SUPPORT_INPUT){
		if(!FAILED(_h_result = ExInitDirectInput(engineFlag)))
			ExInitDirectInputDevice(EX_NULL, engineFlag);
	}
#elif defined(EX_LINUX)     // Linux

    #if defined(EX_DEBUG) || (EX_ENGINE_VERSION_MAJOR <= 0)	// Debugging information
        mtrace();
        //_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_ALLOC_MEM_DF);
        //_CrtSetReportMode(_CRT_ASSERT , _CRTDBG_MODE_FILE);
        //_CrtSetReportFile(_CRT_ASSERT , _CRTDBG_FILE_STDERR);
    #else
        if(engineFlag & ENGINE_SUPPORT_DEBUG_SHELL){

        }
    #endif
    /*
            Create Connection with Display Server.
    */
    display = XOpenDisplay(NULL);

#elif defined(EX_APPLE)
	if(engineFlag & ENGINE_SUPPORT_DEBUG_SHELL){
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_ALLOC_MEM_DF);
		_CrtSetReportMode(_CRT_ASSERT , _CRTDBG_MODE_FILE);
		_CrtSetReportFile(_CRT_ASSERT , _CRTDBG_FILE_STDERR);
	}
#elif defined(EX_ANDROID)
	if(engineFlag & ENGINE_SUPPORT_DEBUG_SHELL){
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_ALLOC_MEM_DF);
		_CrtSetReportMode(_CRT_ASSERT , _CRTDBG_MODE_FILE);
		_CrtSetReportFile(_CRT_ASSERT , _CRTDBG_FILE_STDERR);
	}
#endif

    //ExInitSubSystem(engineFlag);

	if(_h_result = ExInitErrorHandler()){
	}else ExError("Failed to initialize error handler.");

    engineDescription.EngineFlag |= engineFlag;

	return _h_result;
}
/*

*/
DECLSPEC ERESULT ELTAPIENTRY ExInitSubSystem(Uint32 engineFlag){
	ERESULT hr = 0;
	if(ELT_INIT_VIDEO & engineFlag){

	}
	if(ELT_INIT_JOYSTICK & engineFlag){
		ExInitJoyStick(EX_NULL);
	}
	if(ELT_INIT_AUDIO & engineFlag){
		ExAudioInit(0);
	}
	if(ELT_INIT_GAMECONTROLLER & engineFlag){
#ifdef EX_WINDOWS
		LoadLibrary(EX_TEXT("Xinput.dll"));
		//ExInitGameController();
#elif defined(EX_LINUX)
		
#endif
	}
	if(ELT_INIT_EVENTS & engineFlag){
#if defined(EX_WINDOWS

#elif defined(EX_LINUX)

#endif
	}
	if(ELT_INIT_TIMER & engineFlag){
		elt_time = ExCurrentTime();
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
	}
	if(ELT_INIT_JOYSTICK & engineflag){
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
}

DECLSPEC void ELTAPIENTRY ExShutDown(void){
	ExQuitSubSytem(0xFFFFFFFF);
#ifdef EX_LINUX
    struct mallinfo mi;
#endif // EX_LINUX

#ifdef EX_WINDOWS
	DEVMODE d = {};
	Int display;
	ExShutDownFT();
	ExReleaseUICommand();

	ExReleaseCL();
	ExReleaseGL();
	ExUnRegisterClasses();
#if defined(EX_INCLUDE_DIRECTX)
	ExReleaseDirectX();
#endif
	ExReleaseDirectSound();
	ExShutDownDirect();
	ExRelaseNet();
	// restore screen
	display = ChangeDisplaySettings(&d, EX_NULL);
	FreeLibrary(GetModuleHandle(EX_NULL));

/**
    \Linux
*/
#elif defined(EX_LINUX)
	ExReleaseCL();
	ExDestroyContext(ExGetCurrentGLDrawable(), ExGetCurrentOpenGLContext());
	eglTerminate(eglGetCurrentDisplay());
	//ExDestroyCurrentContext();
    XFlush(display);
	XCloseDisplay(display);

#elif defined(EX_APPLE)

#endif
	fclose(m_file_log);
	mi = mallinfo();
	//printf(getenv(MALLOC_TRACE));

	muntrace();
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
		ExLoadLibrary("OpenCL.dll");
		ExLoadLibrary("libOpenCL.so");
	default:return;
	}
}
DECLSPEC void ELTAPIENTRY ExDisable(Enum disable){
#ifdef EX_WINDOWS
#endif
	switch(disable){
	case EX_CRASH_TERMINATE:
		signal(SIGTERM,EX_NULL);
		break;
	case EX_CRASH_ABORT:
		break;
	case EX_CRASH_FLOAT:
		break;
	case EX_CRASH_EXEPCTION:
		break;
	case EX_OPENCL:
		ExUnLoadObject("OpenCL.dll");
		ExUnLoadObject("libOpenCL.so")
	default:return;
	}
}

#define EX_COMPILER_VERSION (major, minor, revision) EX_TEXT("EngineVersion")EX_TEXT("major")EX_TEXT("minor")EX_TEXT("revision")
DECLSPEC const ExChar* ELTAPIENTRY ExGetVersion(void){
	return EX_COMPILER_VERSION(EX_MAJOR_VERSION, EX_MINOR_VERSION, EX_REVISION);//EX_COMPILER_NAME;
}
