#include"system/eltfile.h"
#ifdef EX_WINDOWS
	#include<windows.h>
#endif
#include<stdio.h>

static long unsigned int ExGetFileStreamSize(FILE* file){
    unsigned int pos;
    long size;
    pos = ftell(file);
    fseek(file, 0,SEEK_END);
    size = ftell(file);
    fseek(file, pos, SEEK_SET);
    return size;
}

DECLSPEC long unsigned int  ELTAPIENTRY ExGetFileSize(const char* cfilname){
    FILE* file;
    fpos_t pos;
    long size;
    file = fopen(cfilname,"rb");
    size = ExGetFileStreamSize(file);
    fclose(file);
    return size;
}

DECLSPEC int ELTAPIENTRY ExLoadFile(const char* cfilename, void** data){
    FILE* file;
    unsigned long size;
    file = fopen(cfilename,"rb");
    if(!file)
        return 0;
    size = ExGetFileStreamSize(file);

    data[0] = (void*)malloc(size);

    if(fread(data[0], 1, size,file) != size){
    	fclose(file);
        return -1;
    }

    fclose(file);
    return size;
}


DECLSPEC int ELTAPIENTRY ExSaveFile(const char* cfilename, void* data, unsigned int csize){
    FILE* file;
    file = fopen(cfilename,"wb");
    unsigned long size;
    if(!file)
        return 0;

    if(fwrite(data, 1, csize, file) != csize)
        return 0;
    fclose(file);
    return TRUE;
}

DECLSPEC int ELTAPIENTRY ExCreateDirectory(const char* directory){
#ifdef EX_UNIX
	return mkdir(directory,644);
#elif defined(EX_WINDOWS)
	return CreateDirectory(directory,NULL);
#endif
}
