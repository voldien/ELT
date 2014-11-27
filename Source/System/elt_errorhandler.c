#include"elt_errorhandler.h"
#include"elt_log.h"
#include"./../elt_console.h"
#ifdef EX_WINDOWS
#elif defined(EX_LINUX)
//#include<syslog.h>
#endif
#include<signal.h>
// Error Message text
ExChar* errorText = EX_NULL;
/*
	// ExError
*/
DECLSPEC void ELTAPIENTRY ExError(const ExChar* error,...){
	va_list argptr;

	va_start(argptr,error);
#ifdef EX_UNICODE
	vwfprintf(stderr,error,argptr);
#else
	vfprintf(stderr,error,argptr);
#endif
	va_end(argptr);
#ifdef EX_DEBUG
	exit(EXIT_FAILURE);
#else

#endif
}
/**
	\Error
*/
DECLSPEC void ELTAPIENTRY ExErrorl(Enum flag,const ExChar* error,...){
	ExChar text[512];

	va_list argptr;

	va_start(argptr,error);
    #ifdef EX_UNICODE
	StringCbVPrintf(text,sizeof(text) / sizeof(text[0]),error,argptr);
    #else
	vsprintf(text,error,argptr);
    #endif
	if(flag & EX_ERROR_MESSAGEBOX){
	    #ifdef EX_LINUX
        typedef int(*message_dialog)(void*, unsigned int, unsigned int, unsigned int, char*);
        typedef int(*gtk_window_set_title)(void*, char*);
        typedef int(*gtk_dialog_run)(void*);
	    HANDLE handle;
	    message_dialog h_message;
	    gtk_window_set_title h_win_title;
	    gtk_dialog_run h_dialog;
	    HANDLE *h_widget;
        handle = ExLoadObject("libgobject-2.0.so");
        handle = ExLoadObject("libglib-2.0.so");
        handle = ExLoadObject("libgtk-x11-2.0.so");
        h_message = ExLoadFunction(handle, "gtk_message_dialog_new");
        h_win_title = ExLoadFunction(handle, "gtk_window_set_title");
        h_dialog = ExLoadFunction(handle, "gtk_dialog_run");
        h_widget = (HANDLE)h_message(NULL,
                                    (1 << 0) | (1 << 1),
                                    2, 3,
                                    "Do you wish to save ");
        //h_win_title(h_widget,"Save");
        h_dialog(h_widget);
        //if(h_dialog(h_widget))
        //    exit(1);
        ExUnLoadObject("libgtk-x11-2.0.so");
        #elif defined(EX_WINDOWS)
        /**
            Display MessageBox
        */
		ExMessageBox(EX_NULL,text,EX_TEXT("Error"),MB_OK | MB_SYSTEMMODAL);
        #endif

    }
	if(flag & EX_ERROR_LOG){
        #ifdef UNICODE
		vwprintf(error,argptr);
        #else
		vprintf(error,argptr);
        #endif
    }
    else if(flag & EX_ERROR_LOG_ERR){
        #ifdef UNICODE
		fvwprintf(stderr,error,argptr);
        #else
		vfprintf(stderr,error,argptr);
        #endif
    }
	va_end(argptr);

    #ifdef EX_WINDOWS
    OutputDebugString(text);
    #endif

	if(flag & EX_ERROR_TERMINATE)
		exit(EXIT_FAILURE);
}

ERESULT ex_error[4];
DECLSPEC ERESULT ELTAPIFASTENTRY ExGetError(void){
	return ex_error[0];
}
DECLSPEC void ELTAPIFASTENTRY ExSetError(ERESULT error){
	ex_error[0] = error;
}
DECLSPEC void ELTAPIFASTENTRY ExClearError(void){
	memset(ex_error,E_OK, sizeof(ex_error));
}
/*

*/
DECLSPEC ExChar* ELTAPIENTRY ExGetErrorString(ERESULT errorcode){
	switch(errorcode){
	case E_OK:return EX_TEXT("Sucess");
	case E_FAILURE:return EX_TEXT("failure");
	case E_ERROR:return EX_TEXT("Error");
	case E_INVALID_ARGUMENT:return EX_TEXT("Invalid argument");
	case E_ERROR_SYSTEM:return EX_TEXT("");
	case E_INVALID_ENUM:return EX_TEXT("Invalid enum");
	default:return EX_TEXT("Unknown");
	}
}
#if defined(EX_LINUX)
static int ctxErrorHandler(Display* dpy, XErrorEvent* error){
    char error_buffer[1024];
    XGetErrorText(dpy, error->error_code, error_buffer, sizeof(error_buffer));
    fprintf(stderr,
            "_X Error of failed request: %s\n"
            "_ Major opcode of failed request: % 3d (???)\n"
            "_ Serial number of failed request:% 5d\n"
            "_ Current serial number in output stream:?????\n",
            error_buffer,
            error->request_code,
            error->serial
            );
    return 0;
}
#endif

DECLSPEC Boolean ELTAPIENTRY ExInitErrorHandler(void){
#if defined(EX_LINUX)
	if(XSetErrorHandler(ctxErrorHandler))
        ExDevPrintf("error");
#endif
	//interrupt
	ExSetSignal(SIGINT,ExSignalCatch);
#ifdef EX_WINDOWS
	// Sudden Abort
	ExSetSignal(SIGABRT_COMPAT,ExSignalCatch);
#elif defined(EX_LINUX)
	/* Stack fault.  */
	ExSetSignal(SIGSTKFLT,ExSignalCatch);
	/*              */
    ExSetSignal(SIGQUIT, exit);
#endif


	//Software termination signal from kill
	ExSetSignal(SIGTERM,ExSignalCatch);
	//floating point exception
	ExSetSignal(SIGFPE,ExSignalCatch);
	// segment violation
	ExSetSignal(SIGSEGV,ExSignalCatch);
	//illegal instruction
	ExSetSignal(SIGILL,ExSignalCatch);
	return TRUE;
}

DECLSPEC void ELTAPIENTRY ExErrorExit(ExChar* lpszFunction) {
    // Retrieve the system error message for the last-error code
#ifdef EX_WINDOWS
    LPVOID lpMsgBuf;
    LPVOID lpDisplayBuf;
    DWORD dw = GetLastError();
	HRESULT_FROM_WIN32(dw);
    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        EX_NULL,
        dw,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &lpMsgBuf,
        0, EX_NULL );
    // Display the error message and exit the process
    lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
        (lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR));
    StringCchPrintf((LPTSTR)lpDisplayBuf,
        LocalSize(lpDisplayBuf) / sizeof(TCHAR),
        EX_TEXT("%s failed with error %d: %s"),
        lpszFunction, dw, lpMsgBuf);
    MessageBox(EX_NULL, (LPCTSTR)lpDisplayBuf, EX_TEXT("Error"), MB_OK);

    LocalFree(lpMsgBuf);
    LocalFree(lpDisplayBuf);
    ExitProcess(dw);
#endif
	return;
}

DECLSPEC ExChar* ELTAPIENTRY ExGetErrorMessageW(ULong dw){
#ifdef EX_WINDOWS
	if(errorText)
		LocalFree(errorText);
    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        EX_NULL,
        dw,
		MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),
        (ExChar*) &errorText,
        0, EX_NULL );
	return (ExChar*)errorText;
#elif defined(EX_LINUX)
	if(!errorText)
		errorText = (ExChar*)malloc(512);
	XGetErrorText(display,dw,errorText,512);
	return errorText;
#endif
}

DECLSPEC ExChar* ELTAPIENTRY ExGetHResultErrorMessageW(ERESULT hresult){
#ifdef EX_WINDOWS
	if(errorText)LocalFree(errorText);
	FormatMessage(
	// use system message tables to retrieve error text
	   FORMAT_MESSAGE_FROM_SYSTEM
	   // allocate buffer on local heap for error text
	   |FORMAT_MESSAGE_ALLOCATE_BUFFER
	   // Important! will fail otherwise, since we're not
	   // (and CANNOT) pass insertion parameters
	   |FORMAT_MESSAGE_IGNORE_INSERTS,
	   EX_NULL,    // unused with FORMAT_MESSAGE_FROM_SYSTEM
	   hresult,
	   MAKELANGID(LANG_ENGLISH, SUBLANG_DEFAULT),
	   (ExChar*)&errorText,  // output
	   0, // minimum size for output buffer
	   EX_NULL);   // arguments - see note
	return (ExChar*)errorText;
#elif defined(EX_LINUX)
	if(!errorText)
		errorText = (ExChar*)malloc(512);
	XGetErrorText(display,hresult,errorText,512);
	return errorText;
#endif
}

DECLSPEC ExChar* ELTAPIENTRY ExGetHModuleErrorMessageW(ERESULT dw){
#ifdef EX_WINDOWS
	if(errorText)LocalFree(errorText);
	ExIsError(FormatMessage(
	// use system message tables to retrieve error text
		FORMAT_MESSAGE_FROM_HMODULE
	   // allocate buffer on local heap for error text
	   |FORMAT_MESSAGE_ALLOCATE_BUFFER
	   // Important! will fail otherwise, since we're not
	   // (and CANNOT) pass insertion parameters
	   |FORMAT_MESSAGE_IGNORE_INSERTS,
	   EX_NULL,    // unused with FORMAT_MESSAGE_FROM_SYSTEM
	   dw,
	   MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_UK),
	   (ExChar*)&errorText,  // output
	   0, // minimum size for output buffer
	   EX_NULL));   // arguments - see note
	return (ExChar*)errorText;
#elif defined(EX_LINUX)
	XGetErrorText(display,dw,errorText,512);
	return errorText;

#endif
}

#define EX_ERROR_MESSAGE EX_TEXT("%s has just crashed %s Do you want to send a bug report to the developers team?")


/**
    \SignalCatch
    catch signal and interpret the signal
*/
DECLSPEC void ELTAPIENTRY ExSignalCatch(Int32 signal){
	ExChar wchar[512];
	ExChar app_name[PATH_MAX];
	ExChar cfilename[260];
	Uint32 istosend;

	ExGetApplicationName(app_name,sizeof(app_name));

	switch(signal){
	case SIGSEGV:
		ExSPrintf(wchar,EX_ERROR_MESSAGE,app_name,EX_TEXT("Error : segment violation.\n"));
		break;
	case SIGINT:
		ExSPrintf(wchar,EX_ERROR_MESSAGE,app_name,EX_TEXT("Error : interrupt.\n"));
		break;
	case SIGILL:
		ExSPrintf(wchar,EX_ERROR_MESSAGE,app_name,EX_TEXT("Error : illegal instruction - invalid function image.\n"));
		break;
	case SIGFPE:
		ExSPrintf(wchar,EX_ERROR_MESSAGE,app_name,EX_TEXT("Error : floating point exception.\n"));
		break;
	case SIGTERM:
		ExSPrintf(wchar,EX_ERROR_MESSAGE,app_name,EX_TEXT("Error : Software termination signal from kill.\n"));
		break;
	case SIGABRT:
		ExSPrintf(wchar,EX_ERROR_MESSAGE,app_name,EX_TEXT("Error : abnormal termination trigged by abort call.\n"));
		break;
#if defined(EX_LINUX) || defined(EX_UNIX)
    	case SIGQUIT:
        break;
#endif
	default:
		ExSPrintf(wchar,EX_ERROR_MESSAGE,app_name,EX_TEXT("Error Unknown.\n"));
		break;
	}
	ExPrint(wchar);
#ifdef EX_WINDOWS
	istosend = ExMessageBox(EX_NULL, wchar, EX_TEXT("Crash Report"), MB_YESNO);

	SYSTEMTIME time;
	GetSystemTime(&time);
	wsprintf(cfilename, EX_TEXT("ErrorLog_%d_%d_%d_%d_%d_%d.txt"), time.wYear,time.wMonth,time.wDay,time.wHour,time.wMinute,time.wSecond);

#elif defined(EX_LINUX)
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	ExSPrintf(cfilename, EX_TEXT("ErrorLog_%d_%d_%d_%d_%d_%d.txt"), tm.tm_year,tm.tm_mon,tm.tm_wday,tm.tm_hour,tm.tm_min,tm.tm_sec);
#endif

	char* buffer = malloc(fileLenght(stdout) + fileLenght(stderr));
	fseek(stdout,0,SEEK_SET);
	fseek(stderr,0,SEEK_SET);
	fread(buffer, 1, fileLenght(stdout),stdout);
	buffer += fileLenght(stdout);
	fread(buffer, 1, fileLenght(stderr),stderr);
	buffer -= fileLenght(stdout);
	SaveFile(cfilename,buffer,fileLenght(stdout) + fileLenght(stderr));

    fclose(m_file_log);


	// deal with the information
#ifdef EX_WINDOWS
	switch(istosend){
	case IDYES:
		ExPutFTPFile(EX_TEXT("broodcity.hostoi.com"),EX_TEXT("a9178654"),EX_TEXT("smilla1"),(const ExChar*)cfilename,EX_TEXT("public_html"));
		break;
	case IDNO:

		// allocate on computer somewhere!

		break;
	default:break;
	}
#endif
	exit(signal);
	return;
}

DECLSPEC Boolean ELTAPIENTRY ExSetSignal(unsigned int isignal,singalcallback signal_callback){
	Int32 hr;
	hr = (Int32)signal(isignal,signal_callback);
	ExIsError(hr != (Int32)SIG_ERR);
	return (hr != (Int32)SIG_ERR);
}
