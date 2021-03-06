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
	return EX_TRUE;
}

#endif






/*
 *	High accuracy timer.
 */
extern unsigned int64 eltTickTime;

/*
 *
 */
unsigned long int engineflag = 0;
#define ELT_DEINIT ((unsigned long int)(-1))

/*
 *
 */
void* xcbConnection;


ERESULT ExInit(unsigned int engineFlag){
	ERESULT result = E_OK;
	ExHandle hmodule;
	int hConHandle;
	Long lStdHandle;


	/*	if all is already initilated return !	*/
    if(engineflag & ELT_INIT_EVERYTHING){
        return 2;
    }
	engineflag = engineflag & ~ELT_DEINIT;


    /*	*/
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
        mtrace();		/**/
	#endif
#endif


	/*	enable loggint */
	m_file_log = fopen("EngineExDevLog.txt", "w+" );
	if(dup2(stdout,m_file_log) == -1)
        fprintf(stderr,"error");
    dup2(stdout,stderr);  //redirects stderr to stdout below this line.

#if defined(EX_WINDOWS)


#elif defined(EX_LINUX)

    /*	Create Connection with Display Server.	*/
    display = XOpenDisplay(getenv("DISPLAY"));
    if(!display){
        ExError("couldn't open Display\n");
        abort();
    }



#elif defined(EX_APPLE)

#elif defined(EX_MAC)

#elif defined(EX_ANDROID)

#endif


	/*	Initialize sub system	*/
	ExInitSubSystem(engineFlag);


	/*	initialize error handler.	*/
	if(engineFlag & ELT_INIT_DEBUG){
		if(!(result = ExInitErrorHandler())){
			ExError(EX_TEXT("Failed to initialize error handler."));
		}
	}

	engineflag |= engineFlag;

	/* release resources even if application exit unexpected or exit without calling ExShutDown */
	atexit(ExShutDown);

	return result;
}




ERESULT ExInitSubSystem(unsigned int engineflag){
	ERESULT hr = 0;
	ExHandle hmodule;

	/**/
	engineflag = engineflag & ~ELT_DEINIT;



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
		//ExAudioInit(0);


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
	    /*		enable X events	*/
		XAllowEvents(display , SyncBoth,CurrentTime);
#endif
	}
	if(ELT_INIT_TIMER & engineflag){
		eltTickTime = ExCurrentTime();
	}
	if(ELT_INIT_NET & engineflag){

	    #ifdef EX_LINUX
        ExLoadLibrary("");
        #elif defined(EX_ANDROID)

        #elif defined(EX_WINDOWS)
        if(!ExIsModuleLoaded(EX_TEXT("WS2_32.dll")))
        	ExLoadLibrary(EX_TEXT("WS2_32.dll"));
        #endif

	}
	return hr;
}



void ExQuitSubSytem(unsigned int engineflag){

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
    	if(ExIsModuleLoaded(EX_TEXT("Ws2_32.dll")))
    		WSACleanup();
        #endif
	}

}



void ExShutDown(void){
	if(engineflag & ELT_DEINIT)
		return;

	ExQuitSubSytem(ELT_INIT_EVERYTHING);


	if(ExGetCurrentOpenGLContext())
		ExDestroyGLContext(ExGetCurrentGLDrawable(), ExGetCurrentOpenGLContext());

#if !(defined(EX_ANDROID) || defined(SUPPORT_OPENCL))
	ExDestroyCLContext(ExGetCurrentCLContext());
#endif



#if defined(EX_INCLUDE_DIRECTX)
	ExReleaseDirectX();
#endif

	DEVMODE d = {0};
	int display;

	ExUnRegisterClasses();

	// restore screen
	display = ChangeDisplaySettings(&d, NULL);
	FreeLibrary(GetModuleHandle(NULL));



	/**/
	engineflag |= ELT_DEINIT;
	engineflag = engineflag & ~ELT_INIT_EVERYTHING;

	//fclose(m_file_log);
}


ExDisplay ExGetDisplay(void){
	return NULL;
}

