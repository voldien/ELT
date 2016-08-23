#include"elt.h"
#include"elt_def.h"
#include"system/elt_cl.h"
#include"system/elt_gl.h"
#include"system/elt_errorhandler.h"
#include"system/elt_log.h"
#include"system/elt_audio.h"
#include"elt_loadso.h"
#include"elt_timer.h"



#include"system/unix/unix_win.h"
#include<X11/Xlib.h>
#include<malloc.h>

#include<signal.h>
#include<mcheck.h>


/*
 *
 */
extern Uint64 eltTickTime;		/*	High accuracy timer.	*/
void* xcbConnection;			/*	*/
extern unsigned long int engineflag;

#define ELT_DEINIT ((unsigned long int)(-1))

ERESULT ExInit(Enum flag){
	ERESULT result = E_OK;
	ExHandle hmodule;
	Int32 hConHandle;
	Long lStdHandle;


	/*	if all is already initilated return !	*/
    if(engineflag & ELT_INIT_EVERYTHING){
        return 2;
    }
	engineflag = engineflag & ~ELT_DEINIT;




	/*	enable loggint */
	m_file_log = fopen("EngineExDevLog.txt", "w+" );
	if(dup2(stdout,m_file_log) == -1)
        fprintf(stderr,"error");
    dup2(stdout,stderr);  //redirects stderr to stdout below this line.


    /*	Create Connection with Display Server.	*/
    if(display){
    	display = XOpenDisplay(getenv("DISPLAY"));
    }
    if(!display){
        ExError("couldn't open Display\n");
        abort();
    }

	/*	Initialize sub system	*/
	ExInitSubSystem(flag);


	engineflag |= flag;

	/* release resources even if application exit unexpected or exit without calling ExShutDown */
	atexit(ExShutDown);

	return result;
}

ERESULT ExInitSubSystem(Uint32 flag){
	ERESULT hr = 0;
	ExHandle hmodule;

	/**/
	engineflag = flag & ~ELT_DEINIT;


	if(ELT_INIT_VIDEO & flag){

	}
	if(ELT_INIT_JOYSTICK & flag){


	}
	if(ELT_INIT_AUDIO & flag){
		//ExAudioInit(0);


	}
	if(ELT_INIT_GAMECONTROLLER & flag){

	}
	if(ELT_INIT_EVENTS & flag){
	    /*		enable X events	*/
		XAllowEvents(display , SyncBoth,CurrentTime);
	}
	if(ELT_INIT_TIMER & flag){
		eltTickTime = ExCurrentTime();
	}

	if(ELT_INIT_NET & flag){

	}

	/*	initialize error handler.	*/
	if( ( flag & ELT_INIT_DEBUG ) ){

		mtrace();

		if(!(hr = ExInitErrorHandler())){
			ExError(EX_TEXT("Failed to initialize error handler."));
		}
	}

	return hr;
}

void ExQuitSubSytem(Uint32 flag){

	/**/
	if(ELT_INIT_TIMER & flag){

	}
	if(ELT_INIT_AUDIO & flag){
		//ExUnLoadObject(ExGetFileModule(EX_TEXT("libasound.so")));
	}
	if(ELT_INIT_JOYSTICK & flag){
        ExJoyStickClose(0);
        ExJoyStickClose(1);
        ExJoyStickClose(2);
        ExJoyStickClose(3);
		//ExJoyStickShutDown();
	}
	if(ELT_INIT_GAMECONTROLLER & flag){

	}
	if(ELT_INIT_NET & flag){

	}

	if(ELT_INIT_VIDEO & flag){

	}
}

void ExShutDown(void){
    struct mallinfo mi;

	if(engineflag & ELT_DEINIT){
		return;
	}

	/*	*/
	ExQuitSubSytem(ELT_INIT_EVERYTHING);

	/**/
	if(ExGetCurrentOpenGLContext()){
		ExDestroyGLContext(ExGetCurrentGLDrawable(), ExGetCurrentOpenGLContext());
	}

#if !defined(USE_OPENCL)
	ExDestroyCLContext(ExGetCurrentCLContext());
#endif

	/**/
	if(eglGetCurrentDisplay()){
		eglTerminate(eglGetCurrentDisplay());
	}

	/**/
	XSync(display,True);
	if(display){
		XFlush(display);
	}
    if(display){
    	XCloseDisplay(display);
    	display = NULL;
    }

	/**/
	if(ELT_INIT_DEBUG & engineflag){
		mi = mallinfo();
		printf("Total non-mmapped bytes (arena):       %d\n", mi.arena);
		printf("# of free chunks (ordblks):            %d\n", mi.ordblks);
		printf("# of free fastbin blocks (smblks):     %d\n", mi.smblks);
		printf("# of mapped regions (hblks):           %d\n", mi.hblks);
		printf("Bytes in mapped regions (hblkhd):      %d\n", mi.hblkhd);
		printf("Max. total allocated space (usmblks):  %d\n", mi.usmblks);
		printf("Free bytes held in fastbins (fsmblks): %d\n", mi.fsmblks);
		printf("Total allocated space (uordblks):      %d\n", mi.uordblks);
		printf("Total free space (fordblks):           %d\n", mi.fordblks);
		printf("Topmost releasable block (keepcost):   %d\n", mi.keepcost);

		muntrace();
	}

	/**/
	engineflag |= ELT_DEINIT;
	engineflag = engineflag & ~ELT_INIT_EVERYTHING;
}

ExDisplay ExGetDisplay(void){
	return display;
}
