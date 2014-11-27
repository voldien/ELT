#include"elt_loadso.h"

#if defined(EX_LINUX)
    #include<dlfcn.h>
#endif


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
/*
    // Check if file module is loaded.
*/
DECLSPEC HANDLE ELTAPIENTRY ExIsModuleLoaded(const ExChar* file){
#ifdef EX_WINDOWS
	return GetModuleHandle(file);
#elif defined(EX_LINUX) || defined(EX_UNIX)
	return dlopen(file,RTLD_NOW);
#endif
}
