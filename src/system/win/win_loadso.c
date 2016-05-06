#include"elt_loadso.h"
fined(EX_WINDOWS)
#	include<windef.h>
#   include<winbase.h>






int  ExLoadNumSymbol(ExHandle handle){

}


char*  ExLoadSymbol(ExHandle handle, int index, char* symbol, int len){

}


inline ExHandle  ExLoadFunction(ExHandle handle,const char* pProcName){
	return GetProcAddress((HMODULE)handle,pProcName);
}

inline ExHandle ExLoadObject(const ExChar* sofile){
	ExHandle handle;
	ExIsError((handle = LoadLibrary(sofile)));
	return handle;
}

inline void ExUnLoadObject(ExHandle handle){
	ExIsWinError(FreeLibrary((HMODULE)handle));
}

inline ExHandle ExIsModuleLoaded(const ExChar* file){
	return GetModuleHandle(file);
}
