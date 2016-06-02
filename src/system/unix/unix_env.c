#include"elt_env.h"
#include<stdio.h>
#include<string.h>
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
	int len = 0;
	int strle;
	int offset = 0;
	char** start = environ;

	/*	compute the full size.	*/
	while(*start != NULL){
		len += strlen(start[0]) + 1;
		start++;
	}
	outenv = realloc(outenv, len);
	start = environ;

	/*	write env data.	*/
	while(*start != NULL){
		strle = strlen(*start);
		memcpy(outenv + offset, *start,strle);
		offset += strle + 1;
		start++;
	}

	return outenv;
}

void ExFreeEnv(ExChar* env){
	free(env);
}

