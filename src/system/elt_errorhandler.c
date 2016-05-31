#include"system/elt_errorhandler.h"
#include"system/elt_log.h"
#include"system/elt_win.h"

#ifdef EX_WINDOWS
#	include<windows.h>
#	include <winuser.h>
/*	TODO resolve it's annoying error later*/
//#	include<strsafe.h>

#	include<string.h>
#	include<dbghelp.h>
#   pragma comment(lib, "Dbghelp.lib")

#elif defined(EX_LINUX)
#   include<syslog.h>
#	include<X11/Xlib.h>
#   include"system/unix/unix_win.h"
#   include<unistd.h>
#   include<sys/types.h>
#   include<sys/stat.h>
#   include<fcntl.h>
#elif defined(EX_ANDROID)

#   include<syslog.h>
#   include<android/log.h>
#   include<unistd.h>
#   include<sys/types.h>
#   include<sys/stat.h>
#   include<fcntl.h>
#	define LOG_TAG "ELT"
#   define LOGI(...)   __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#   define LOGE(...)   __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#endif

#include<signal.h>
#include<limits.h>

#ifdef EX_PNACL
	#include "ppapi/c/ppb.h"
	#include "ppapi/c/pp_errors.h"
	#include "ppapi/gles2/gl2ext_ppapi.h"
#endif 





#if defined(EX_LINUX)
static int private_ctxErrorHandler(Display* dpy, XErrorEvent* error){
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

    return NULL;
}
#endif


int ExInitErrorHandler(void){
#if defined(EX_LINUX)
    /*	enable X window error message handler.	*/
	if(!XSetErrorHandler(private_ctxErrorHandler)){
        ExDevPrintf("error");
	}
#endif



	/*	interrupt	*/
	ExSetSignal(SIGINT,ExSignalCatch);
#ifdef EX_WINDOWS
	/*	Sudden Abort	*/
	//ExSetSignal(SIGABRT_COMPAT, ExSignalCatch);
#elif defined(EX_LINUX)
	/* Stack fault.  */
	ExSetSignal(SIGSTKFLT,ExSignalCatch);
	/*              */
    ExSetSignal(SIGQUIT, exit);
#endif

	/*	Software termination signal from kill	*/
	ExSetSignal(SIGTERM, ExSignalCatch);
	/*floating point exception*/
	ExSetSignal(SIGFPE, ExSignalCatch);
	/*	segment violation	*/
	ExSetSignal(SIGSEGV, ExSignalCatch);
	/*	illegal instruction	*/
	ExSetSignal(SIGILL, ExSignalCatch);
	return TRUE;
}




// Error Message text
ExChar* errorText = NULL;


void ExError(const ExChar* error,...){
	va_list argptr;

	va_start(argptr,error);
#ifdef EX_UNICODE

	//vwfprintf(stderr,error,argptr);
#else
	vfprintf(stderr, error, argptr);
#endif
	va_end(argptr);
#ifdef EX_DEBUG
	exit(EXIT_FAILURE);
#else

#endif
}

void ExErrorl(Enum flag, const ExChar* error, ...){
	ExChar text[512];

	va_list argptr;

	va_start(argptr,error);
    //#ifdef EX_UNICODE
	//StringCbVPrintf(text,sizeof(text) / sizeof(text[0]),error,argptr);
    //#else
	vsprintf(text,error,argptr);
    //#endif
	if(flag & EX_ERROR_MESSAGEBOX){
	    #ifdef EX_LINUX

        #elif defined(EX_WINDOWS)
        /**
            Display MessageBox
        */
		ExMessageBox(NULL,text,EX_TEXT("Error"),MB_OK | MB_SYSTEMMODAL);
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
		//fvwprintf(stderr,error,argptr);
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

Int errorIndex = 0;
ERESULT ex_error[4] = {E_OK};
ERESULT ExGetError(void){
	return ex_error[0];
}

void ExSetError(ERESULT error){
	ex_error[errorIndex] = error;
}

void ExClearError(void){
	memset(ex_error,E_OK, sizeof(ex_error));
}


ExChar* ExGetErrorString(ERESULT errorcode){
	switch(errorcode){
	case E_OK:return EX_TEXT("Sucess");
	case E_FAILURE:return EX_TEXT("failure");
	case E_ERROR:return EX_TEXT("Error");
	case E_INVALID_ARGUMENT:return EX_TEXT("Invalid argument");
	case E_ERROR_SYSTEM:return EX_TEXT("");
	case E_INVALID_ENUM:return EX_TEXT("Invalid enum");
	default:return EX_TEXT("Unknown");
	}
	return NULL;
}



void ExErrorExit(ExChar* lpszFunction) {

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
        NULL,
        dw,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &lpMsgBuf,
        0, NULL );
    // Display the error message and exit the process
    lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
        (lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR));
    sprintf((LPTSTR)lpDisplayBuf,
        LocalSize(lpDisplayBuf) / sizeof(TCHAR),
        EX_TEXT("%s failed with error %d: %s"),
        lpszFunction, dw, lpMsgBuf);
    MessageBox(NULL, (LPCTSTR)lpDisplayBuf, EX_TEXT("Error"), MB_OK);

    LocalFree(lpMsgBuf);
    LocalFree(lpDisplayBuf);
    ExitProcess(dw);
#elif defined(EX_LINEX) || defined(EX_ANDROID)
    ExSignalCatch(2);
    exit(EXIT_FAILURE);
#endif

}

ExChar* ExGetErrorMessageW(ULong dw){
#ifdef EX_WINDOWS
	if(errorText)   /*free allocated error message.*/
		LocalFree(errorText);
    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
		MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),
        (ExChar*) &errorText,
        0, NULL );
	return (ExChar*)errorText;
#elif defined(EX_LINUX)
	if(!errorText)
		errorText = (ExChar*)malloc(512);
	XGetErrorText(display,dw,errorText,512);
	return errorText;
#elif defined(EX_ANDROID)
    return NULL;
#endif
}

ExChar* ExGetHResultErrorMessageW(ERESULT hresult){
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
	   NULL,    // unused with FORMAT_MESSAGE_FROM_SYSTEM
	   hresult,
	   MAKELANGID(LANG_ENGLISH, SUBLANG_DEFAULT),
	   (ExChar*)&errorText,  // output
	   0, // minimum size for output buffer
	   NULL);   // arguments - see note
	return (ExChar*)errorText;
#elif defined(EX_LINUX)
	if(!errorText)
		errorText = (ExChar*)malloc(512);
	XGetErrorText(display,hresult,errorText,512);
	return errorText;
#elif defined(EX_ANDROID)
    return NULL;
#endif
}

ExChar* ExGetHModuleErrorMessageW(ERESULT dw){
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
	   NULL,    // unused with FORMAT_MESSAGE_FROM_SYSTEM
	   dw,
	   MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_UK),
	   (ExChar*)&errorText,  // output
	   0, // minimum size for output buffer
	   NULL));   // arguments - see note
	return (ExChar*)errorText;
#elif defined(EX_LINUX)
	if(!errorText)
		errorText = (ExChar*)malloc(512);
	XGetErrorText(display,dw,errorText,512);
	return errorText;
#elif defined(EX_ANDROID)
    return NULL;
#endif
}



/**
    back trace
    http://stackoverflow.com/questions/5693192/win32-backtrace-from-c-code
*/
#define TRACE_SIZE 100
static void debugLogTrace(void){
#ifdef EX_WINDOWS
    HANDLE process;
    void* stack[100];
    unsigned int frames;
	unsigned int i,j;
    SYMBOL_INFO* symbol;

    process = GetCurrentProcess();

    SymInitialize(process, NULL,TRUE);

    frames = CaptureStackBackTrace(0,100, stack, NULL);
    symbol = (SYMBOL_INFO*)calloc(sizeof( SYMBOL_INFO ) + 256 * sizeof( char ), 1 );
    symbol->MaxNameLen = 255;
    symbol->SizeOfStruct = sizeof(SYMBOL_INFO);

    for(i = 0; i < frames;i++){
        SymFromAddr(process,(DWORD64)(stack[i]),0, symbol);
        fprintf(stderr,"%i: %s - 0x%0X\n",frames - i - 1, symbol->Name, symbol->Address);
    }
    free(symbol);

#elif defined(EX_LINUX)


    void* trace[TRACE_SIZE];
    char** strings;
    unsigned int i,j;
    /**/
    j = backtrace(trace,TRACE_SIZE);
    /**/
    strings = backtrace_symbols(trace,j);

    if(!strings)
    	ExSetError(-1);

    for(i = 0; i < j; i++){
		fprintf(stderr,"%s\n",strings[i]);
    }
    free(strings);

#elif defined(EX_ANDROID)


#endif
}



#define EX_ERROR_MESSAGE EX_TEXT("%s has just crashed %s Do you want to send a bug report to the developers team?")
void ExSignalCatch(Int32 signal){
	ExChar wchar[512];
	ExChar app_name[256];
	char cfilename[260];
	Uint32 istosend;
	FILE* file;

#ifdef EX_WINDOWS
	SYSTEMTIME time;
#elif defined(EX_LINUX)
    time_t t;
	struct tm tm;
#endif
    /*	log trace information.	*/
    debugLogTrace();

	ExGetApplicationName(&app_name[0],sizeof(app_name));        /*  Get application name   */

	switch(signal){
	case SIGSEGV:
		ExSPrintf(wchar, EX_ERROR_MESSAGE, app_name, EX_TEXT("Error : segment violation.\n"));
		break;
	case SIGINT:
		ExSPrintf(wchar, EX_ERROR_MESSAGE, app_name, EX_TEXT("Error : interrupt.\n"));
		exit(1);
		break;
	case SIGILL:
		ExSPrintf(wchar, EX_ERROR_MESSAGE, app_name, EX_TEXT("Error : illegal instruction - invalid function image.\n"));
		break;
	case SIGFPE:
		ExSPrintf(wchar, EX_ERROR_MESSAGE, app_name, EX_TEXT("Error : floating point exception.\n"));
		break;
	case SIGTERM:
		ExSPrintf(wchar, EX_ERROR_MESSAGE, app_name, EX_TEXT("Error : Software termination signal from kill.\n"));
		break;
	case SIGABRT:
		ExSPrintf(wchar, EX_ERROR_MESSAGE, app_name, EX_TEXT("Error : abnormal termination trigged by abort call.\n"));
		break;
#if defined(EX__UNIX)
    	case SIGQUIT:

        break;
#endif
	default:
		ExSPrintf(wchar, EX_ERROR_MESSAGE, app_name, EX_TEXT("Error Unknown.\n"));
		break;
	}

	exit(signal);
	fclose(m_file_log);	/*	TODO make more genertic*/
}




int ExSetSignal(unsigned int isignal, ExSignalCallback signal_callback){
	int hr;
	hr = (int)signal(isignal,signal_callback);
	ExIsError(hr != (int)SIG_ERR);
	return (hr != (int)SIG_ERR);
}
