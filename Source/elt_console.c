#include"elt_console.h"
#include"System/elt_win.h"

DECLSPEC ExWin ELTAPIENTRY ExCreateConsole(void){
#ifdef EX_WINDOWS
	Int32 hConHandle;

	long lStdHandle;

	CONSOLE_SCREEN_BUFFER_INFO coninfo;

	FILE *fp;

	// allocate a console for this app

	AllocConsole();
	// set the screen buffer to be big enough to let us scroll text

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), 

	&coninfo);

	//coninfo.dwSize.Y = (1080 / 2)/8;
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), 
	
	coninfo.dwSize);

	// redirect unbuffered STDOUT to the console

	lStdHandle = (long)GetStdHandle(STD_OUTPUT_HANDLE);

	hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);

	fp = _fdopen( hConHandle, "w" );

	*stdout = *fp;

	setvbuf( stdout, NULL, _IONBF, 0 );

	// redirect unbuffered STDIN to the console

	lStdHandle = (long)GetStdHandle(STD_INPUT_HANDLE);

	hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);

	fp = _fdopen( hConHandle, "r" );
	
	*stdin = *fp;

	setvbuf( stdin, NULL, _IONBF, 0 );

	// redirect unbuffered STDERR to the console

	lStdHandle = (long)GetStdHandle(STD_ERROR_HANDLE);

	hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);

	fp = _fdopen( hConHandle, "w" );


	*stderr = *fp;

	setvbuf( stderr, NULL, _IONBF, 0 );
	// make cout, wcout, cin, wcin, wcerr, cerr, wclog and clog 

	// point to console as well
#ifdef EX_CPP
	std::ios::sync_with_stdio();
#endif

	return (ExWin)hConHandle;
#elif defined(EX_LINUX)
	pid_t i;
	char buf[10];
	Int32 fds, fdm, status;
	fdm = posix_openpt(O_RDWR);
	//grantptr(fdm);
	unlockpt(fdm);

	close(0);
	close(1);
	close(2);

	i = fork();
	if(i == 0){

	}
	else{
		fds = open(ptsname(fdm), O_RDWR);
		dup(fds);
		dup(fds);
		dup(fds);
		sprintf(buf,"xterm -S%c/2", basename(buf));
		system(buf);
	}
#endif
}

DECLSPEC ExWin ELTAPIENTRY ExGetConsoleWindow(void){
#ifdef EX_WINDOWS
	return GetConsoleWindow();
#else
	return 0;
#endif
}

DECLSPEC Boolean ELTAPIENTRY ExSetConsoleSize(HANDLE handle, const Size_t size){
#ifdef EX_WINDOWS

	//ExSetWindowSize(
	//SetConsoleScreenBufferSize(handle,(COORD)*size);
	//SetConsoleScreenBufferSize(handle,(COORD)*size);
	return 0;
#elif defined(EX_LINUX)

#elif defined(EX_MAC)
#endif
}


DECLSPEC Boolean ELTAPIENTRY ExSetConsoleCursorPos(HANDLE handle, Coord* coord){
#ifdef EX_WINDOWS
	return SetConsoleCursorPosition(handle, *(COORD*)coord);
#elif defined(EX_LINUX)
	return 0;
#endif
}
DECLSPEC Boolean ELTAPIENTRY ExGetConsoleCursorPos(HANDLE handle, Coord* coord){
#ifdef EX_WINDOWS
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(handle,&info);
	memcpy(coord,&info.dwCursorPosition,sizeof(Coord));
	return TRUE;
#elif defined(EX_LINUX)
	return 0;
#endif
}

DECLSPEC ERESULT ELTAPIENTRY InsertConsoleInHWND(ExWin hwnd){
#ifdef EX_WINDOWS
	SetConsoleActiveScreenBuffer(hwnd);
#endif
	return 0;
}

DECLSPEC void ELTAPIENTRY ExWriteColorTextA(const char* text, Uint16 hexColor){
	// get current and allocate the
	ExSetConsoleColor(hexColor);
	fprintf(stdin,text);
	return;
}

DECLSPEC void ELTAPIENTRY ExWriteColorTextW(const ExChar* text, Uint16 hexColor){
	// get current and allocate the
	ExPrint(text);
	return;
}

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
#define RESET "\033[0m"

DECLSPEC void ELTAPIENTRY ExSetConsoleColor(Uint16 colour){
#if defined(EX_WINDOWS)
	if(GetStdHandle(STD_OUTPUT_HANDLE) == INVALID_HANDLE_VALUE)return;

	if(!SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),colour))
		wExDevPrintf(EX_TEXT("failed to Set Console Text Attribute | %s"), ExGetErrorMessage(GetLastError()));
#else
	switch(colour){
	case EX_CONSOLE_BLACK:printf(KNRM);break;
	case EX_CONSOLE_BLUE :printf(KBLU);break;
	case EX_CONSOLE_GREEN :printf(KNRM);break;
	case EX_CONSOLE_AQUA :printf(KNRM);break;
	case EX_CONSOLE_RED :printf(KNRM);break;
	case EX_CONSOLE_PURPLE :printf(KNRM);break;
	case EX_CONSOLE_YELLOW :printf(KNRM);break;
	case EX_CONSOLE_WHITE :printf(KNRM);break;
	case EX_CONSOLE_GRAY :printf(KNRM);break;
	case EX_CONSOLE_LIGHT_BLUE :printf(KNRM);break;
	case EX_CONSOLE_LIGHT_GREEN :printf(KNRM);break;
	case EX_CONSOLE_LIGHT_AQUA :printf(KNRM);break;
	case EX_CONSOLE_LIGHT_RED :printf(KNRM);break;
	case EX_CONSOLE_LIGHT_PURPLE :printf(KNRM);break;
	case EX_CONSOLE_LIGHT_YELLOW :printf(KNRM);break;
	case EX_CONSOLE_LIGHT_WHITE :printf(KNRM);break;
	case EX_CONSOLE_COLOR_RESET:printf(RESET);break;
	}
#endif
}

DECLSPEC Uint16 ELTAPIENTRY ExGetConsoleColor(void){
#ifdef EX_WINDOWS
	CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
	if(GetStdHandle(STD_OUTPUT_HANDLE) == INVALID_HANDLE_VALUE)return 0;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&bufferInfo);
	return bufferInfo.wAttributes;
#elif defined(EX_LINUX)
	return 0;
#endif
}

DECLSPEC Int32 ELTAPIENTRY ExGetConsoleFontSize(ULong stdHandle,Coord* coord){
#ifdef EX_WINDOWS
	CONSOLE_FONT_INFO  info;
	if(!GetCurrentConsoleFont(GetStdHandle(stdHandle), FALSE, &info)){
		wExDevPrintf(EX_TEXT("Failed to Get Console Font Size | %s"), ExGetErrorMessage(GetLastError()));
	}
	memcpy(coord, &GetConsoleFontSize(GetStdHandle(stdHandle),info.nFont),sizeof(Coord));
	return TRUE;
#elif defined(EX_LINUX)
	return 0;
#endif
}
