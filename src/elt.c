#include"elt.h"
#include"elt_def.h"
#include"system/elt_cl.h"
#include"system/elt_gl.h"
#include"system/elt_errorhandler.h"
#include"system/elt_log.h"

#include<signal.h>

unsigned int engineflag;

unsigned int ExGetFlag(void){
	return engineflag;
}

void ExEnable(unsigned int enable){
	switch(enable){
	case EX_CRASH_TERMINATE:
		signal(SIGTERM, ExSignalCatch);

		break;
	case EX_CRASH_ABORT:

		break;
	case EX_CRASH_FLOAT:

		break;
	case EX_CRASH_EXEPCTION:

		break;
	case EX_OPENCL:
		break;
	default:return;
	}
}

void ExDisable(unsigned int disable){
	switch(disable){
	case EX_CRASH_TERMINATE:
		signal(SIGTERM, NULL);
		break;
	case EX_CRASH_ABORT:
		break;
	case EX_CRASH_FLOAT:
		break;
	case EX_CRASH_EXEPCTION:
		break;
	case EX_OPENCL:
		break;
	default:return;
	}
}

#define EX_COMPILED_VERSION(major, minor, revision) EX_STR(major)EX_TEXT(".")EX_STR(minor)EX_TEXT(".")EX_STR(revision)
const ExChar* ExGetVersion(void){
	return EX_COMPILED_VERSION(EX_VERSION_MAJOR, EX_VERSION_MINOR, EX_VERSION_REVISION);
}

const ExChar* ExGetCompilerName(void){
    return EX_TEXT(EX_COMPILER_NAME);
}
