#include"elt_env.h"
#include<unistd.h>


ExChar* ExGetCurrentUser(void){
	return ExGetEnv("USER");
}

int ExSetEnv(const ExChar* name, const char* pValue){
	return setenv(name, pValue, 0);
}

ExChar* ExGetEnv(const ExChar* name){
	char* outenv = NULL;
	char* env = getenv(name);
	if(env){
		unsigned int len = strlen(env) + 1;
		outenv = malloc(len);
		memcpy(outenv, env, len);
	}
	return outenv;
}

int ExRemoveEnv(const ExChar* name){
	return unsetenv(name);
}

extern char **environ;
ExChar* ExGetAllEnv(void){
	char* outenv = NULL;
	outenv = realloc(outenv, 1);
	int len = 0;
	char** start = environ;
	while(*start != NULL){

		len += strlen(start[0]) + 1;
		start++;
	}
	realloc(outenv, len);
	return outenv;
}
