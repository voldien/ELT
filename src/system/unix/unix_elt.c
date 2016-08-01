#include"elt.h"
#include"elt_def.h"
#include"system/elt_cl.h"
#include"system/elt_gl.h"
#include"system/elt_errorhandler.h"
#include"system/elt_log.h"
#include"system/elt_audio.h"

#include"system/unix/unix_win.h"
#include<X11/Xlib.h>
#include<malloc.h>

#include<signal.h>
#include<mcheck.h>

/*
 *	High accuracy timer.
 */
extern Uint64 eltTickTime;

/*
 *
 */
unsigned long int engineflag = 0;
#define ELT_DEINIT ((unsigned long int)(-1))

/*
 *
 */
void* xcbConnection;


ERESULT ExInit(Enum engineFlag){
	ERESULT result = E_OK;
	ExHandle hmodule;
	Int32 hConHandle;
	Long lStdHandle;


	/*	if all is already initilated return !	*/
    if(engineflag & ELT_INIT_EVERYTHING){
        return 2;
    }
	engineflag = engineflag & ~ELT_DEINIT;

	mtrace();


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
	ExInitSubSystem(engineFlag);




	engineflag |= engineFlag;

	/* release resources even if application exit unexpected or exit without calling ExShutDown */
	atexit(ExShutDown);

	return result;
}




ERESULT ExInitSubSystem(Uint32 engineflag){
	ERESULT hr = 0;
	ExHandle hmodule;

	/**/
	engineflag = engineflag & ~ELT_DEINIT;


	if(ELT_INIT_VIDEO & engineflag){

	}
	if(ELT_INIT_JOYSTICK & engineflag){


	}
	if(ELT_INIT_AUDIO & engineflag){
		//ExAudioInit(0);


	}
	if(ELT_INIT_GAMECONTROLLER & engineflag){

	}
	if(ELT_INIT_EVENTS & engineflag){
	    /*		enable X events	*/
		XAllowEvents(display , SyncBoth,CurrentTime);
	}
	if(ELT_INIT_TIMER & engineflag){
		eltTickTime = ExCurrentTime();
	}

	if(ELT_INIT_NET & engineflag){
        ExLoadLibrary("");
	}
	/*	initialize error handler.	*/
	if(engineflag & ELT_INIT_DEBUG){
		if(!(hr = ExInitErrorHandler())){
			ExError(EX_TEXT("Failed to initialize error handler."));
		}
	}


	return hr;
}



void ExQuitSubSytem(Uint32 engineflag){

	if(ELT_INIT_TIMER & engineflag){

	}
	if(ELT_INIT_AUDIO & engineflag){
		//ExUnLoadObject(ExGetFileModule(EX_TEXT("libasound.so")));
	}
	if(ELT_INIT_JOYSTICK & engineflag){
        ExJoyStickClose(0);
        ExJoyStickClose(1);
        ExJoyStickClose(2);
        ExJoyStickClose(3);
		//ExJoyStickShutDown();
	}
	if(ELT_INIT_GAMECONTROLLER & engineflag){

	}
	if(ELT_INIT_NET & engineflag){

	}

	if(ELT_INIT_VIDEO & engineflag){

	}
	if(ELT_INIT_NET & engineflag){
        ExLoadLibrary("");
	}

}



void ExShutDown(void){
    struct mallinfo mi;
	if(engineflag & ELT_DEINIT)
		return;

	ExQuitSubSytem(ELT_INIT_EVERYTHING);

	if(ExGetCurrentOpenGLContext()){
		ExDestroyGLContext(ExGetCurrentGLDrawable(), ExGetCurrentOpenGLContext());
	}

#if !(defined(EX_ANDROID) || !defined(SUPPORT_OPENCL))
	ExDestroyCLContext(ExGetCurrentCLContext());
#endif

	if(eglGetCurrentDisplay())
		eglTerminate(eglGetCurrentDisplay());

	if(xcbConnection){
		XCloseDisplay(xcbConnection);
	}
	XSync(display,True);
	if(display){
		XFlush(display);
	}
    if(display){
    	XCloseDisplay(display);
    	display = NULL;
    }
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

	/**/
	engineflag |= ELT_DEINIT;
	engineflag = engineflag & ~ELT_INIT_EVERYTHING;

	//fclose(m_file_log);
}


ExDisplay ExGetDisplay(void){
	return display;
}
