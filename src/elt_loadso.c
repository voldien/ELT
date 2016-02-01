#include"elt_loadso.h"


#if defined(EX_UNIX) || defined(EX_ANDROID)

#   include<stdio.h>
#	include<stdlib.h>
#	ifndef EX_PNACL
#			define _GNU_SOURCE
#			define __USE_GNU
#   		include<link.h>
#   		include<dlfcn.h>
#	endif
#   include<errno.h>
#   include<libgen.h>
#elif defined(EX_WINDOWS)
#	include<windef.h>
#   include<winbase.h>
#endif



#if defined(EX_LINUX) && !defined(EX_ANDROID)
static int dlNumSymbolcallback(struct dl_phdr_info *info, size_t size, void *data){
	int j;

	printf("name=%s (%d segments)\n", info->dlpi_name, info->dlpi_phnum);

   for (j = 0; j < info->dlpi_phnum; j++)
		 printf("\t\t header %2d: address=%10p\n", j,
			 (void *) (info->dlpi_addr + info->dlpi_phdr[j].p_vaddr));


   if(data)
	   ((unsigned int*)data)[0] = info->dlpi_phnum;

	return 0;
}

typedef struct symbol_fetch{
	int index;
	char* symbol;
	int len;
}ExSymbolFetch;

static int dlSymbolcallback(struct dl_phdr_info *info, size_t size, ExSymbolFetch *data){

	if(info->dlpi_phnum > data->index){
		//memcpy(data->symbol,info->dlpi_phdr[data->index].

	}
}
#endif



int ELTAPIENTRY ExLoadNumSymbol(HANDLE handle){
#if defined(EX_LINUX) && !defined(EX_ANDROID)
	int num = 0;
	dl_iterate_phdr(dlNumSymbolcallback, &num);
	return num;
#endif
}

char* ELTAPIENTRY ExLoadSymbol(HANDLE handle, int index, char* symbol, int len){
#if defined(EX_LINUX) && !defined(EX_ANDROID)
	ExSymbolFetch fetchSymbol;
	fetchSymbol.index = index;
	fetchSymbol.symbol = symbol;
	fetchSymbol.len = len;
	return dl_iterate_phdr(dlSymbolcallback, &fetchSymbol) != 0;
#endif
}


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
	handle = dlopen(sofile, RTLD_NOW | RTLD_GLOBAL);
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
	if(handle)
		fprintf(stderr,dlerror());
#endif

#endif
}

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

        /*  get library real path.   */
        if(readlink(map->l_name, buffer, sizeof(buffer)) < 0)
        	memcpy(buffer, map->l_name, strlen(map->l_name) + 1);

        /*	check if its a shared library or if buffer has valid path.*/
        if(strstr(&buffer[0],".so")){
            buffer[strstr(buffer,".so") + sizeof(".so") - buffer] = '\0';
        }
        else
        	continue;

        /*	check base name	TODO add support for relative and absolute path!	*/
        if(!strcmp(basename(buffer),file)){
        	dlclose(handle);
            return map->l_ld;
        }
    }

    dlclose(handle);
    return NULL;
#endif
}
