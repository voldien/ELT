#include"eltfile.h"

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
