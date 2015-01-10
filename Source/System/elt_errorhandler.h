/*
========================================================================
    ELT (Engine Library Toolkit) is a multi platform engine toolkit
    Copyright (C) 2014  Valdemar Lindberg

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/
#ifndef ELT_ERROR_HANDLER_H
#define ELT_ERROR_HANDLER_H
#include"./../EngineAssembly.h"
#include"./../elt_console.h"


typedef void(ELTAPIENTRY *singalcallback)(Int32);
#ifdef  __cplusplus	// C++ Environment
extern "C"{
#endif
/**
	ExInternalError
*/
#define ExIsError(x) { if( ( x ) <= 0 ){ ExDevPrintc("Error",EX_CONSOLE_RED);} }
/**
	C error
*/
#define ExIsCError(x) { if( ( x ) <= 0){ ExDevPrintfc("Error | %s",EX_CONSOLE_RED,strerror(errno));}}



#if defined(EX_WINDOWS)
	#define ExIsWinError(x) { if( (Long)( x ) <= 0 ){ExDevWindowPrintc(EX_TEXT("Error"),EX_CONSOLE_RED);} }
	#define ExIsHError(x) {ERESULT temp; if((temp = ( x ) ) != S_OK ){ExDevWindowHPrintc(EX_TEXT("Error"),temp,EX_CONSOLE_RED);}}
	#define ExIsDXError(x) {ERESULT temp; if((temp = ( x ) ) != S_OK ){ExDevWindowHPrintc(EX_TEXT("Error"),temp,EX_CONSOLE_RED);}}
#elif defined(EX_LINUX)
	//dlerror
	#define ExIsWinError(x) { if( (Long)( x ) <= 0 ){ExDevWindowPrintc(EX_TEXT("Error"),EX_CONSOLE_RED);} }
	#define ExIsXWinError(x)
	#define ExIsHError(x) EX_UNUSED(x)
	#define ExIsDXError(x) EX_UNUSED(x)
#endif
#define EX_ERROR_MESSAGEBOX 0x1
#define EX_ERROR_TERMINATE 0x2
#define EX_ERROR_ERROR_HANDLE 0x4
#define EX_ERROR_LOG 0x8
#define EX_ERROR_LOG_ERR 0x10
#define EX_SIGN_
/**
	Error
	application will terminate with error failure message.
	printout of error messages.
*/
extern DECLSPEC void ELTAPIENTRY ExError(const ExChar* error,...);
/**
	Error with argument of how the error will be treated
*/
extern DECLSPEC void ELTAPIENTRY ExErrorl(Enum flag,const ExChar* error,...);

/**
	Get Error
*/
extern DECLSPEC ERESULT ELTAPIFASTENTRY ExGetError(void);
/**
	Set Error
*/
extern DECLSPEC void ELTAPIFASTENTRY ExSetError(ERESULT error);
/**
	Clear Errors
*/
extern DECLSPEC void ELTAPIFASTENTRY ExClearError(void);
/**
	// Get ELT Error String.
	//
*/
extern DECLSPEC ExChar* ELTAPIENTRY ExGetErrorString(ERESULT errorcode);

#define E_OK				((ERESULT)1L)		/*	No Error */
#define E_FAILURE			((ERESULT)0L)		/*	FAILURE */
#define E_ERROR				((ERESULT)-1L)		/*	Error   */
#define E_INVALID_ARGUMENT	((ERESULT)-2L)		/*	Invalid Argument */
#define E_ERROR_SYSTEM		((ERESULT)-3L)		/*	System Error */
#define E_INVALID_ENUM		((ERESULT)-4L)		/*	Invalid Enum */
#define E_ABI_ERROR			((ERESULT)-5L)		/*	Application Binary interface Error */

#define EX_CRASH_TERMINATE 0x1
#define EX_CRASH_ABORT 0x2
#define EX_CRASH_FLOAT 0x3
#define EX_CRASH_EXEPCTION 0x4

/**
    Initialize Error Handler
*/
extern DECLSPEC ExBoolean ELTAPIENTRY ExInitErrorHandler(void);


/*	Get Error Code In Character out of Error.*/
extern DECLSPEC ExChar* ELTAPIENTRY ExGetErrorMessageW(ULong dw);
/*	Get Error Code In Character out of HRESULT.*/
extern DECLSPEC ExChar* ELTAPIENTRY ExGetHResultErrorMessageW(ERESULT hresult);
/*	Get Error Code Of HModule */
extern DECLSPEC ExChar* ELTAPIENTRY ExGetHModuleErrorMessageW(ERESULT dw);


// UNICODED
#ifdef UNICODE
	#define ExGetErrorMessage ExGetErrorMessageW
	#define ExGetHResultErrorMessage ExGetHResultErrorMessageW
	#define ExGetHModuleErrorMessage ExGetHModuleErrorMessageW
#else
	#define ExGetErrorMessage ExGetErrorMessageW
	#define ExGetHResultErrorMessage ExGetHResultErrorMessageW
	#define ExGetHModuleErrorMessage ExGetHModuleErrorMessageW
#endif


/**
	Signal Catch
*/
extern DECLSPEC void ELTAPIENTRY ExSignalCatch(Int32 signal);
/*
	// Set Signal callback.
*/
extern DECLSPEC ExBoolean ELTAPIENTRY ExSetSignal(unsigned int isignal,singalcallback signal_callback);

#ifdef EX_UNICODE
	#define ExPrint wprintf
	#define ExSPrintf wsprintf
#else
	#define ExPrint printf
	#define ExSPrintf sprintf
#endif

#if  defined(EX_DEBUG)
	// Ex Print For Developing [error code : errormessage, filename, fileline, function name]
	#define EX_DEVELOP_ERROR_LOG "\t ErrorCode %d : %s \t in file %s on line : %d in function %s.\n\n"
	#define EXDEVFILEINFO "\n[FileLine %d : FileName %s]\n"
	#define EXDEVWINDOWINFO "ErrorCode : %d | ErrorMessage : %s\n"
	#define EX_DEV_OPENGL_INFO "ErrorCode :%d | ErrorMessage : %s\n"
#elif defined(EX_RELEASE)
	// Ex Print For Developing
	#define EX_DEVELOP_ERROR_LOG EX_TEXT("\t ErrorCode %d : %s \t in file %s on line : %d in function %s\n")
	#define EXDEVFILEINFO "\n[FileLine %d : FileName %s]\n"
	#define EXDEVWINDOWINFO "ErrorCode : %d | ErrorMessage : %s\n"
	#define EX_DEV_OPENGL_INFO "ErrorCode :%d | ErrorMessage : %s\n"

#endif

#if !defined(EX_DISABLE_DEV_PRINT)
		#ifdef EX_RELEASE
			/*		*/
			#define ExPrintf(pFormat,...) printf(pFormat,##__VA_ARGS__)
			#define ExPrintfc(pFormat, color,...) {Uint16 __colour__ = ExGetConsoleColor();ExSetConsoleColor(color);printf(pFormat,__VA_ARGS__);ExSetConsoleColor(__colour__);}

			/* Print Developer Information With Arguments*/
			#define ExDevPrintfc(pFormat, color,...) {Uint16 __colour__ = ExGetConsoleColor();ExSetConsoleColor(color);printf(pFormat EX_DEVELOP_ERROR_LOG,__VA_ARGS__,EX_FUNCNAME,__LINE__, __FILE__);ExSetConsoleColor(__colour__);}
			#define ExDevPrintf(pFormat,...) printf(pFormat EXDEVFILEINFO, ##__VA_ARGS__,__LINE__, __FILE__)

			/* Print Developer Information Without Arguments*/
			#define ExDevPrint(pFormat) printf(pFormat EXDEVFILEINFO,__LINE__, __FILE__)
			#define ExDevPrintc(pFormat,color) {Uint16 __colour__ = ExGetConsoleColor();ExSetConsoleColor(color);printf(pFormat EXDEVFILEINFO,__LINE__, __FILE__);ExSetConsoleColor(__colour__);}

			/*Print Dever information without arguments Unicode*/
			#define wExDevPrint(pFormat) ExPrint(pFormat EX_TEXT(EXDEVFILEINFO),__LINE__, EX_TEXT(__FILE__))
			#define wExDevPrintc(pFormat,color) {Uint16 __colour__ = ExGetConsoleColor();ExSetConsoleColor(color);ExPrint(pFormat EX_TEXT(EXDEVFILEINFO),__LINE__, EX_TEXT(__FILE__));ExSetConsoleColor(__colour__);}

			/* Print Developer Information With Arguments Unicode*/
			#define wExDevPrintfc(pFormat,color,...) {Uint16 __colour__ = ExGetConsoleColor();ExSetConsoleColor(color);ExPrint(pFormat EX_TEXT(EXDEVFILEINFO),__VA_ARGS__,__LINE__, EX_TEXT(__FILE__));ExSetConsoleColor(__colour__);}
			#define wExDevPrintf(pFormat,...) wprintf(pFormat  EX_TEXT(EXDEVFILEINFO),__VA_ARGS__,__LINE__, EX_TEXT(__FILE__))

			/*Print Developer information Window Error Message */
			#define ExDevWindowPrint(pFormat)	{ExPrint(pFormat,EX_TEXT(EXDEVWINDOWINFO),GetLastError(),ExGetErrorMessage(GetLastError()));}
			#define ExDevWindowPrintc(pFormat,color)	{Uint16 __colour__ = ExGetConsoleColor();ExSetConsoleColor(color);ExPrint(pFormat EX_TEXT(EXDEVWINDOWINFO) EX_TEXT(EXDEVFILEINFO),GetLastError(),ExGetErrorMessage(GetLastError()),__LINE__, EX_TEXT(__FILE__));ExSetConsoleColor(__colour__);}
			#define ExDevWindowPrintf(pFormat,...)	{ExPrint(pFormat EX_TEXT(EXDEVWINDOWINFO) EX_TEXT(EXDEVFILEINFO),GetLastError(),ExGetErrorMessage(GetLastError()), __VA_ARGS__, __LINE__,EX_TEXT(__FILE__));}
			#define ExDevWindowPrintfc(pFormat,color,...)	{Uint16 __colour__ = ExGetConsoleColor();ExSetConsoleColor(color);ExPrint(pFormat EX_TEXT(EXDEVWINDOWINFO) EX_TEXT(EXDEVFILEINFO),GetLastError(),ExGetErrorMessage(GetLastError()), __VA_ARGS__,__LINE__, EX_TEXT(__FILE__));ExSetConsoleColor(__colour__);}

			#define ExDevWindowHPrint(pFormat)	{ExPrint(pFormat,EX_TEXT(EXDEVWINDOWINFO),GetLastError(),ExGetErrorMessage(GetLastError()));}
			#define ExDevWindowHPrintc(pFormat,color)	{}
			#define ExDevWindowHPrintf(pFormat,...)	{}
			#define ExDevWindowHPrintfc(pFormat,color,...)	{}

			#define ExDevGLPrint(pFormat)	printf(pFormat EXDEVWINDOWINFO EXDEVFILEINFO,glGetError(),glewGetErrorString(glGetError()), __LINE__, __FILE__);
			#define ExDevGLPrintc(pFormat,color)	{Uint16 __colour__ = ExGetConsoleColor();ExSetConsoleColor(color);printf(pFormat EXDEVWINDOWINFO EXDEVFILEINFO,glGetError(),glewGetString(glGetError()),__LINE__, __FILE__);ExSetConsoleColor(__colour__);}
			#define ExDevGLPrintf(pFormat,...)	{Uint16 __colour__ = ExGetConsoleColor();ExSetConsoleColor(color);printf(pFormat EXDEVWINDOWINFO EXDEVFILEINFO,__VA_ARGS__,glewGetString(glGetError()),LINE__, __FILE__,);ExSetConsoleColor(__colour__);}
			#define ExDevGLPrintfc(pFormat,color,...){Uint16 __colour__ = ExGetConsoleColor();ExSetConsoleColor(color);printf(pFormat EX_DEV_OPENGL_INFO EXDEVFILEINFO,__VA_ARGS__,glGetError(), glewGetString(glGetError()), __LINE__, __FILE__);ExSetConsoleColor(__colour__);}

		#else
			/*		*/
			#define ExPrintf(pFormat,...) printf(pFormat , ##__VA_ARGS__)
			#define ExPrintfc(pFormat, color, ... ) {Uint16 __colour__ = ExGetConsoleColor();ExSetConsoleColor(color);printf(pFormat,##__VA_ARGS__);ExSetConsoleColor(__colour__);}

			/* Print Developer Information With Arguments*/
			#define ExDevPrintfc(pFormat, color,...) {Uint16 __colour__ = ExGetConsoleColor();ExSetConsoleColor(color);printf(pFormat EX_DEVELOP_ERROR_LOG,__VA_ARGS__,0,"",__FILE__,__LINE__ ,EX_FUNCDNAME);ExSetConsoleColor(__colour__);}
			#define ExDevPrintf(pFormat,...) printf(pFormat EX_DEVELOP_ERROR_LOG, __VA_ARGS__,0,"",__FILE__,__LINE__ ,EX_FUNCDNAME)

			/* Print Developer Information Without Arguments*/
			#define ExDevPrint(pFormat) printf(pFormat EX_DEVELOP_ERROR_LOG,0,"",__FILE__,__LINE__ ,EX_FUNCDNAME)
			#define ExDevPrintc(pFormat,color) {Uint16 __colour__ = ExGetConsoleColor();ExSetConsoleColor(color);printf(pFormat EX_DEVELOP_ERROR_LOG,0,"",__FILE__,__LINE__ ,EX_FUNCDNAME);ExSetConsoleColor(__colour__);}

			/*Print Dever information without arguments Unicode*/
			#define wExDevPrint(pFormat) wprintf(pFormat EX_TEXT(EX_DEVELOP_ERROR_LOG),0,EX_TEXT(""),EX_TEXT(__FILE__),__LINE__ ,EX_TEXT(EX_FUNCDNAME))
			#define wExDevPrintc(pFormat,color) {Uint16 __colour__ = ExGetConsoleColor();ExSetConsoleColor(color);ExPrint(pFormat EX_TEXT(EXDEVFILEINFO),__LINE__, EX_TEXT(__FILE__));ExSetConsoleColor(__colour__);}

			/* Print Developer Information With Arguments Unicode*/
			#define wExDevPrintfc(pFormat,color,...) {Uint16 __colour__ = ExGetConsoleColor();ExSetConsoleColor(color);ExPrint(pFormat EX_TEXT(EX_DEVELOP_ERROR_LOG),__VA_ARGS__,0,"",EX_TEXT(__FILE__),__LINE__, EX_TEXT(EX_FUNCDNAME));ExSetConsoleColor(__colour__);}
			#define wExDevPrintf(pFormat,...) wprintf(pFormat  EX_TEXT(EX_DEVELOP_ERROR_LOG),__VA_ARGS__,0,EX_TEXT(""),EX_TEXT(__FILE__),__LINE__, EX_TEXT(EX_FUNCDNAME))

			/*Print Developer information Window Error Message */
			#define ExDevWindowPrint(pFormat)	{ExPrint(pFormat,EX_TEXT(EX_DEVELOP_ERROR_LOG),GetLastError(),ExGetErrorMessage(GetLastError()),EX_TEXT(__FILE__),__LINE__,EX_TEXT(EX_FUNCNAME) );}
			#define ExDevWindowPrintc(pFormat,color)	{Uint16 __colour__ = ExGetConsoleColor();ExSetConsoleColor(color);ExPrint(pFormat EX_TEXT(EX_DEVELOP_ERROR_LOG),GetLastError(),ExGetErrorMessage(GetLastError()),EX_TEXT(__FILE__),__LINE__,EX_TEXT(EX_FUNCNAME) );ExSetConsoleColor(__colour__);}
			#define ExDevWindowPrintf(pFormat,...)	{ExPrint(pFormat EX_TEXT(EX_DEVELOP_ERROR_LOG),__VA_ARGS__,GetLastError(),ExGetErrorMessage(GetLastError()),EX_TEXT(__FILE__),__LINE__,EX_TEXT(EX_FUNCNAME));}
			#define ExDevWindowPrintfc(pFormat,color,...)	{Uint16 __colour__ = ExGetConsoleColor();ExSetConsoleColor(color);ExPrint(pFormat EX_TEXT(EX_DEVELOP_ERROR_LOG),__VA_ARGS__,GetLastError(),ExGetErrorMessage(GetLastError()), EX_TEXT(__FILE__),__LINE__,EX_TEXT(EX_FUNCDNAME));ExSetConsoleColor(__colour__);}

			#define ExDevWindowHPrint(pFormat)	{ExPrint(pFormat,EX_TEXT(EXDEVWINDOWINFO),GetLastError(),ExGetErrorMessage(GetLastError()));}
			#define ExDevWindowHPrintc(pFormat,hresult,color)	{Uint16 __colour__ = ExGetConsoleColor();ExSetConsoleColor(color);ExPrint(pFormat EX_TEXT(EX_DEVELOP_ERROR_LOG),hresult,ExGetHResultErrorMessage(hresult),EX_TEXT(__FILE__),__LINE__,EX_TEXT(EX_FUNCNAME)); ExSetConsoleColor(__colour__); }
			#define ExDevWindowHPrintf(pFormat,hresult,...)	{}
			#define ExDevWindowHPrintfc(pFormat,hresult,color,...)	{}


		#endif


		#ifdef EX_RELEASE
			/* Print Developer Information With Arguments*/
			#define ExDevPrintf(pFormat,...) printf(pFormat EXDEVFILEINFO, ##__VA_ARGS__,__LINE__, __FILE__)
			/* Print Developer Information Without Arguments*/
			#define ExDevPrint(pFormat) printf(pFormat EXDEVFILEINFO,__LINE__, __FILE__)
			/* Print Developer Information With Arguments Unicode*/
			#define wExDevPrint(pFormat) wprintf(pFormat EX_TEXT(EXDEVFILEINFO),__LINE__, __FILE__)
		#else
			/* Print Developer Information With Arguments*/
			#define ExDevPrintf(pFormat,...) printf(pFormat EXDEVFILEINFO, ##__VA_ARGS__,__LINE__, __FILE__)
			/* Print Developer Information Without Arguments*/
			#define ExDevPrint(pFormat) printf(pFormat EXDEVFILEINFO,__LINE__, __FILE__)
			/* Print Developer Information With Arguments Unicode*/
			#define wExDevPrint(pFormat) wprintf(pFormat EX_TEXT(EXDEVFILEINFO),__LINE__, __FILE__)
		#endif
#else
// no error message

#endif



#ifdef  __cplusplus	// C++ Environment
}
#endif
#endif
