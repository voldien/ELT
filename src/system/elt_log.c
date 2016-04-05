#include"system/elt_log.h"
FILE* m_file_log = NULL;


void ExLog(const ExChar* format,...){
	va_list va;
	//vfprintf(stdout, format, va_arg());
}

void ExErrorLog(const ExChar* format,...){

}

void ExLogWarning(const ExChar* format,...){

}

void ExLogCritical(const ExChar* format,...){

}

void ExLogInfo(const ExChar* format,...){

}



FILE* ExDupFile(const int _fd){

}
