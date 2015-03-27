#include"system/eltfile.h"

static long ExGetFileStreamSize(FILE* file ){
    fpos_t pos;
    long size;
/*    pos = ftell(file);
    fseek(file, 0,SEEK_END);
    size = ftell(file);
    fseek(file, pos, SEEK_SET);*/
    return size;
}

DECLSPEC long ELTAPIENTRY ExGetFileSize(const char* cfilname){
    FILE* file;
    fpos_t pos;
    long size;
    file = fopen(cfilname,"rb");
    fseek(file, 0,SEEK_END);
    size = ftell(file);
    fclose(file);
    return size;
}

DECLSPEC int ELTAPIENTRY ExLoadFile(const char* cfilename,void** data){
    FILE* file;
    unsigned long size;
    file = fopen(cfilename,"rb");
    if(!file)
        return 0;
    size = ExGetFileStreamSize(file);

    data[0] = malloc(size);
    if(fread(data[0], 1, size,file) != size)
        return 0;

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
