#include"elt_loadso.h"
#if defined(EX_UNIX) || defined(EX_ANDROID)
#   include<stdio.h>
#	ifndef EX_PNACL
#   		include<link.h>
#   		include<dlfcn.h>
#	endif
#   include<errno.h>
#   include<libgen.h>
#elif defined(EX_WINDOWS)
#	include<windef.h>
#   include<winbase.h>

#endif

/**
*/
DECLSPEC inline HANDLE ELTAPIENTRY ExLoadFunction(HANDLE handle,const char* pProcName){
#ifdef EX_WINDOWS
	return GetProcAddress((HMODULE)handle,pProcName);
#elif defined(EX_UNIX)
	return dlsym(handle,pProcName);
#endif
}

DECLSPEC inline HANDLE ELTAPIENTRY ExLoadObject(const ExChar* sofile){
	HANDLE handle;
#ifdef EX_WINDOWS
	ExIsError((handle = LoadLibrary(sofile)));
	return handle;
#elif defined(EX_UNIX) && !(EX_PNACL)
	handle = dlopen(sofile,RTLD_LAZY);
    #ifdef EX_DEBUG
	if(!handle)
		fprintf(stderr,dlerror());
    #endif
	return handle;
#endif
}
DECLSPEC inline void ELTAPIENTRY ExUnLoadObject(HANDLE handle){
#ifdef EX_WINDOWS
	ExIsWinError(FreeLibrary((HMODULE)handle));
#elif defined(EX_UNIX)
    if(handle)
        handle = dlclose(handle);
#ifdef EX_DEBUG
	if(!handle)
		fprintf(stderr,dlerror());
#endif

#endif
}
/**
    Check if file module is loaded.
*/
DECLSPEC inline HANDLE ELTAPIENTRY ExIsModuleLoaded(const ExChar* file){
#ifdef EX_WINDOWS
	return GetModuleHandle(file);
#elif defined(EX_UNIX) && !(EX_PNACL) && !(EX_ANDROID)	/*	TODO resolve link_map problem with android*/
    char buffer[256];
    void* handle = dlopen(NULL, RTLD_NOW);
    #ifdef EX_DEBUG
    if(!handle)
        printf(stderr,dlerror());
    #endif

    void* p = handle;// + sizeof(void*) * 3;    /*to skip the first waste one .*/
    struct link_map* map = p;
    while(map->l_next){
        map = (struct link_map*)map->l_next;
        readlink(map->l_name, buffer, sizeof(buffer));  /*  get library real name   */
        if(strstr(&buffer[0],".so"))
            (strstr(&buffer[0],".so") + sizeof(".so") - sizeof(char))[0] = '\0';    /*convert the name into what you specif in linker option*/
        else continue;

        if(!strcmp(basename(buffer),file)){
            return TRUE;    //BASE name correct
            // Look if its necessary to look for version extension.
        }
        else continue;
    }
    dlclose(handle);
    return FALSE;
#endif
}
