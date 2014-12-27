#ifndef _ELT_FILE_H
#define _ELT_FILE_H

#ifdef __cplusplus //	C++ Enviroment
extern "C"{
#endif
/**
	Get file size in bytes
*/
extern DECLSPEC int ELTAPIENTRY ExGetFilSize(const char* cfilname);
/*
	Load data by specified pathname
*/
extern DECLSPEC int ELTAPIENTRY ExLoadFile(const char* cfilename,void** data);
/**
	Save File by specified file name
*/
extern DECLSPEC int ELTAPIENTRY ExSaveFile(const char* cfilename, void* data, unsigned int csize);


#ifdef __cplusplus
}
#endif

#endif // _ELT_FILE_H
