#include <elt_def.h>
#include <ExNT.h>
#include <signal.h>
#include <stddef.h>
#include <system/elt_errorhandler.h>
#include <system/elt_win.h>
#include "elt.h"

unsigned int engineflag;

unsigned int ExGetFlag(void) {
	return engineflag;
}


#define EX_COMPILED_VERSION(major, minor, revision) EX_STR(major)EX_TEXT(".")EX_STR(minor)EX_TEXT(".")EX_STR(revision)
const ExChar* ExGetVersion(void) {
	return EX_COMPILED_VERSION(EX_VERSION_MAJOR, EX_VERSION_MINOR,
			EX_VERSION_REVISION);
}

const ExChar* ExGetCompilerName(void) {
	return EX_TEXT(EX_COMPILER_NAME);
}

