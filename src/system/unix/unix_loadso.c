#include"elt_loadso.h"
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



#if defined(EX_LINUX) && !defined(EX_ANDROID)
static int dlNumSymbolcallback(struct dl_phdr_info *info, size_t size, void *data){
	int j;

	printf("name=%s (%d segments)\n", info->dlpi_name, info->dlpi_phnum);

   for (j = 0; j < info->dlpi_phnum; j++){
		 printf("\t\t header %2d: address=%10p\n", j,
			 (void *) (info->dlpi_addr + info->dlpi_phdr[j].p_vaddr));

   }

   if(data)
	   *((unsigned int*)data) = info->dlpi_phnum;

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



int ExLoadNumSymbol(ExHandle handle){
#if defined(EX_LINUX) && !defined(EX_ANDROID)
	int num = 0;
	dl_iterate_phdr(dlNumSymbolcallback, &num);
	return num;
#endif
}


ExChar* ExLoadSymbol(ExHandle handle, int index, char* symbol, int len){
#if defined(EX_LINUX) && !defined(EX_ANDROID)
	ExSymbolFetch fetchSymbol;
	fetchSymbol.index = index;
	fetchSymbol.symbol = symbol;
	fetchSymbol.len = len;
	return dl_iterate_phdr(dlSymbolcallback, &fetchSymbol) != 0;
#endif
}


inline ExHandle ExLoadFunction(ExHandle handle,const char* pProcName){
	return dlsym(handle,pProcName);
}

inline ExHandle ExLoadObject(const ExChar* sofile){
	ExHandle handle;
#if defined(EX_UNIX) && !(EX_PNACL)
	handle = dlopen(sofile, RTLD_NOW | RTLD_GLOBAL);
    #ifdef EX_DEBUG
	if(!handle)
		fprintf(stderr,dlerror());
    #endif
	return handle;
#endif

}

inline void ExUnLoadObject(ExHandle handle){
    if(handle)
        handle = dlclose(handle);
#ifdef EX_DEBUG
	if(handle)
		fprintf(stderr,dlerror());
#endif
}

inline ExHandle ExIsModuleLoaded(const ExChar* file){
#if defined(EX_UNIX) && !(EX_PNACL) && !(EX_ANDROID)	/*	TODO resolve link_map problem with android*/

	char buffer[PATH_MAX];
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
