#include"elt_loadso.h"
#if defined(EX_LINUX)
#   include<link.h>
#   include<dlfcn.h>
#   include<errno.h>
#   include<libgen.h>
#elif defined(EX_WINDOWS)

#endif

/**
*/
DECLSPEC HANDLE ELTAPIENTRY ExLoadFunction(HANDLE handle,const char* pProcName){
#ifdef EX_WINDOWS
	return GetProcAddress((HMODULE)handle,pProcName);
#elif defined(EX_LINUX) || defined(EX_ANDROID) || defined(EX_MAC)
	return dlsym(handle,pProcName);
#endif
}

DECLSPEC HANDLE ELTAPIENTRY ExLoadObject(const ExChar* sofile){
	HANDLE handle;
#ifdef EX_WINDOWS
	ExIsError((handle = LoadLibrary(sofile)));
	return handle;
#elif defined(EX_LINUX) || defined(EX_ANDROID) || defined(EX_MAC)
	handle = dlopen(sofile,RTLD_LAZY);
	if(!handle)
		fprintf(stderr,dlerror());
	return handle;
#endif
}
DECLSPEC void ELTAPIENTRY ExUnLoadObject(HANDLE handle){
#ifdef EX_WINDOWS
	ExIsWinError(FreeLibrary((HMODULE)handle));
#elif defined(EX_LINUX) || defined(EX_ANDROID) || defined(EX_MAC)
#ifdef EX_DEBUG

#endif
	handle = dlclose(handle);
	if(!handle)
		fprintf(stderr,dlerror());
#endif
}
/**
    Check if file module is loaded.
*/
DECLSPEC HANDLE ELTAPIENTRY ExIsModuleLoaded(const ExChar* file){
#ifdef EX_WINDOWS
	return GetModuleHandle(file);
#elif defined(EX_LINUX) || defined(EX_UNIX)
    char buffer[256];
    void* handle = dlopen(NULL, RTLD_NOW);
    #ifdef EX_DEBUG
    if(!handle)
        printf(stderr,dlerror());
    #endif

    void* p = handle;// + sizeof(void*) * 3;
    struct link_map* map = p;
    while(map->l_next){
        map = map->l_next;
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
    return FALSE;
#endif
}
