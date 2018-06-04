#include"elt_loadso.h"
#include<elt_def.h>

#include<linux/limits.h>
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

#include<errno.h>
#include<unistd.h>

ExHandle ExLoadFunction(ExHandle handle, const char* pProcName) {
	return dlsym(handle, pProcName);
}

ExHandle ExLoadObject(const ExChar* sofile) {
	ExHandle handle;
#if defined(EX_UNIX) && !(EX_PNACL)
	handle = dlopen(sofile, RTLD_NOW | RTLD_GLOBAL);
#ifdef EX_DEBUG
	if (!handle)
		fprintf(stderr, dlerror());
#endif
	return handle;
#endif

}

void ExUnLoadObject(ExHandle handle) {
	if (handle) {
		handle = dlclose(handle);
	}
#ifdef EX_DEBUG
	if (handle)
		fprintf(stderr, dlerror());
#endif
}

ExHandle ExIsModuleLoaded(const ExChar* file) {
#if defined(EX_UNIX) && !(EX_PNACL) && !(EX_ANDROID)	/*	TODO resolve link_map problem with android*/

	char buffer[PATH_MAX];
	void* handle = dlopen(NULL, RTLD_NOW);
#ifdef EX_DEBUG
	if (!handle)
		printf(stderr, dlerror());
#endif

	void* p = handle; // + sizeof(void*) * 3;    /*to skip the first waste one .*/
	struct link_map* map = p;

	while (map->l_next) {
		map = (struct link_map*) map->l_next;

		/*  get library real path.   */
		if (readlink(map->l_name, buffer, sizeof(buffer)) < 0)
			memcpy(buffer, map->l_name, strlen(map->l_name) + 1);

		/*	check if its a shared library or if buffer has valid path.*/
		if (strstr(&buffer[0], ".so")) {
			buffer[strstr(buffer, ".so") + sizeof(".so") - buffer] = '\0';
		} else
			continue;

		/*	check base name	TODO add support for relative and absolute path!	*/
		if (!strcmp(basename(buffer), file)) {
			dlclose(handle);
			return map->l_ld;
		}
	}

	dlclose(handle);
	return NULL;
#endif
}
