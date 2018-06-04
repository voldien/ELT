#include"elt.h"
#include"elt_def.h"
#include"system/elt_cl.h"
#include"system/elt_gl.h"
#include"system/elt_errorhandler.h"
#include"system/elt_log.h"
#include"elt_loadso.h"
#include"elt_timer.h"

#include"system/unix/unix_win.h"
#include<X11/Xlib.h>
#include<X11/X.h>
#include<malloc.h>

#include<signal.h>
#include<mcheck.h>

/*
 *
 */
extern unsigned long int eltTickTime; /*	High accuracy timer.	*/
void* xcbConnection = NULL; /*	*/
extern unsigned int engineflag;

#define ELT_DEINIT ((unsigned long int)(-1))

ERESULT ExInit(unsigned int flag) {
	ERESULT result = E_OK;
	ExHandle hmodule;
	int hConHandle;
	long lStdHandle;

	/*	if all is already initilated return !	*/
	if (engineflag & EX_INIT_EVERYTHING) {
		return 2;
	}
	engineflag = engineflag & ~ELT_DEINIT;

	/*	Create Connection with Display Server.	*/
	if (XInitThreads() == 0) {
		printf("Failed to init multithreading support\n");
	}
	if (display == NULL) {
		display = XOpenDisplay(ExGetEnv("DISPLAY"));
	}
	if (!display) {
		ExError("couldn't open Display\n");
		abort();
	}
	if (xcbConnection == NULL) {
		xcbConnection = XGetXCBConnection(display);
	}

	/*	Initialize sub system	*/
	ExInitSubSystem(flag);

	engineflag |= flag;

	/* release resources even if application exit unexpected or exit without calling ExShutDown */
	atexit(ExShutDown);

	return result;
}

ERESULT ExInitSubSystem(unsigned int flag) {
	ERESULT hr = 0;
	ExHandle hmodule;

	/**/
	engineflag = flag & ~ELT_DEINIT;

	if (EX_INIT_JOYSTICK & flag) {

	}
	if (EX_INIT_GAMECONTROLLER & flag) {

	}
	if (EX_INIT_EVENTS & flag) {
		/*		enable X events	*/
		XAllowEvents(display, SyncBoth, CurrentTime);
	}
	if (EX_INIT_TIMER & flag) {
		eltTickTime = ExCurrentTime();
	}

	if (EX_INIT_NET & flag) {

	}

	/*	initialize error handler.	*/
	if (flag & EX_INIT_DEBUG) {
		ExLog("Enable ELT Debug.\n");
		mtrace();

		/*	enable loggint */
		m_file_log = fopen("EngineExDevLog.txt", "w+");
		if (dup2(stdout, m_file_log) == -1)
			fprintf(stderr, "error");
		dup2(stdout, stderr);  //redirects stderr to stdout below this line.

		if (!(hr = ExInitErrorHandler())) {
			ExError(EX_TEXT("Failed to initialize error handler."));
		}
	}

	return hr;
}

void ExQuitSubSytem(unsigned int flag) {

	/**/
	if (EX_INIT_TIMER & flag) {

	}
	if (EX_INIT_JOYSTICK & flag) {
		ExJoyStickClose(0);
		ExJoyStickClose(1);
		ExJoyStickClose(2);
		ExJoyStickClose(3);
		//ExJoyStickShutDown();
	}
	if (EX_INIT_GAMECONTROLLER & flag) {

	}
	if (EX_INIT_NET & flag) {

	}
}

void ExShutDown(void) {
	struct mallinfo mi;

	if (engineflag & ELT_DEINIT) {
		return;
	}

	/*	*/
	ExQuitSubSytem(EX_INIT_EVERYTHING);

	/**/
	if (ExGetCurrentOpenGLContext()) {
		ExDestroyGLContext(ExGetCurrentGLDrawable(),
				ExGetCurrentOpenGLContext());
	}

	/**/
	if (eglGetCurrentDisplay()) {
		eglTerminate(eglGetCurrentDisplay());
	}

	/**/
	XSync(display, True);
	if (display) {
		XFlush(display);
	}
	if (display) {
		XCloseDisplay(display);
		display = NULL;
	}

	/**/
	if (EX_INIT_DEBUG & engineflag) {
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
	engineflag = engineflag & ~EX_INIT_EVERYTHING;
}

ExDisplay ExGetDisplay(void) {
	return display;
}
