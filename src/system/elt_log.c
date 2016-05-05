#include"system/elt_log.h"
FILE* m_file_log = NULL;


void ExLog(const ExChar* format,...){
	ExSetConsoleColor(0);
	va_list va;
	va_start(va, format);
	vfprintf(stdout, format,va);
	va_end(va);
	ExSetConsoleColor(0);
}

void ExErrorLog(const ExChar* format,...){
	ExSetConsoleColor(0);
	va_list va;
	va_start(va, format);
	vfprintf(stdout, format,va);
	va_end(va);
	ExSetConsoleColor(0);
}

void ExLogWarning(const ExChar* format,...){
	ExSetConsoleColor(0);
	va_list va;
	va_start(va, format);
	vfprintf(stdout, format,va);
	va_end(va);
	ExSetConsoleColor(0);
}

void ExLogCritical(const ExChar* format,...){
	ExSetConsoleColor(0);
	va_list va;
	va_start(va, format);
	vfprintf(stdout, format,va);
	va_end(va);
	ExSetConsoleColor(0);
}

void ExLogInfo(const ExChar* format,...){
	ExSetConsoleColor(0);
	va_list va;
	va_start(va, format);
	vfprintf(stdout, format,va);
	va_end(va);
	ExSetConsoleColor(0);
}

FILE* ExDupFile(const int _fd){

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




void ExSetConsoleColor(Uint16 colour){
#if defined(EX_WINDOWS)
	if(GetStdHandle(STD_OUTPUT_HANDLE) == INVALID_HANDLE_VALUE)return;

	if(!SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),colour))
		wExDevPrintf(EX_TEXT("failed to Set Console Text Attribute | %s"), ExGetErrorMessage(GetLastError()));
#elif defined(EX_LINUX)
	switch(colour){
	case EX_CONSOLE_BLACK: printf(KNRM);break;
	case EX_CONSOLE_BLUE : printf(KBLU);break;
	case EX_CONSOLE_GREEN : printf(KNRM);break;
	case EX_CONSOLE_AQUA : printf(KNRM);break;
	case EX_CONSOLE_RED : printf(KNRM);break;
	case EX_CONSOLE_PURPLE : printf(KNRM);break;
	case EX_CONSOLE_YELLOW : printf(KNRM);break;
	case EX_CONSOLE_WHITE : printf(KNRM);break;
	case EX_CONSOLE_GRAY : printf(KNRM);break;
	case EX_CONSOLE_LIGHT_BLUE : printf(KNRM);break;
	case EX_CONSOLE_LIGHT_GREEN : printf(KNRM);break;
	case EX_CONSOLE_LIGHT_AQUA : printf(KNRM);break;
	case EX_CONSOLE_LIGHT_RED : printf(KNRM);break;
	case EX_CONSOLE_LIGHT_PURPLE : printf(KNRM);break;
	case EX_CONSOLE_LIGHT_YELLOW : printf(KNRM);break;
	case EX_CONSOLE_LIGHT_WHITE : printf(KNRM);break;
	case EX_CONSOLE_COLOR_RESET: printf(RESET);break;
	}
#endif
}


Uint16 ExGetConsoleColor(void){
#ifdef EX_WINDOWS
	CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
	if(GetStdHandle(STD_OUTPUT_HANDLE) == INVALID_HANDLE_VALUE)return 0;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&bufferInfo);
	return bufferInfo.wAttributes;
#elif defined(EX_UNIX)
	return 0;
#endif
}


