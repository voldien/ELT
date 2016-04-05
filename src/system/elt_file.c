#include"system/elt_file.h"
#include<stdio.h>
/*	*/
#ifdef EX_WINDOWS
	#include<windows.h>
#endif
/*	*/
#ifdef EX_UNIX
	#include<unistd.h>
	#include<dirent.h>
#endif

inline static long int private_ExGetFileStreamSize(FILE* file){
    unsigned int pos;
    long size;
    pos = ftell(file);
    fseek(file, 0,SEEK_END);
    size = ftell(file);
    fseek(file, pos, SEEK_SET);
    return size;
}

long int ExGetFileStreamSize(FILE* file){
    unsigned int pos;
    long size;
    pos = ftell(file);
    fseek(file, 0, SEEK_END);
    size = ftell(file);
    fseek(file, pos, SEEK_SET);
    return size;
}

long int ExGetFileSize(const ExChar* cfilname){
    FILE* file;
    fpos_t pos;
    long size;
    file = fopen(cfilname,"rb");
    size = private_ExGetFileStreamSize(file);
    fclose(file);
    return size;
}

long int ExLoadFile(const ExChar* cfilename, void** bufferptr){
	FILE*f;
	void* buffer;
	long length;
	*bufferptr = NULL;

	if(!cfilename || strlen(cfilename) == 0){
		return -1;
	}

	f = ExSafeOpenRead(cfilename);
	if(!f){
		return -1;
	}
	length = private_ExGetFileStreamSize(f);
	buffer = malloc(length + 1);
	((char*)buffer)[length] = 0;
	ExSafeRead(f,buffer,length);
	fclose(f);
	*bufferptr = buffer;
	return length;
}

long int ExSaveFile(const ExChar* cfilename, void* racBuffer, unsigned int riSize){
	FILE *f;
	f = ExSafeOpenWrite(cfilename);
	ExSafeWrite(f,racBuffer,riSize);
	fclose(f);
	return f ? TRUE : FALSE;
}

FILE* ExSafeOpenWrite(const ExChar* cfilename){
	FILE* f;
	f = fopen(cfilename, "wb");
	if(!f){
		printf ("Error opening file %s: %s\n", cfilename, strerror(errno));
	}
	return f;
}

FILE* ExSafeOpenRead(const ExChar* cfilename){
	FILE* f;
	f = fopen(cfilename,"rb");
	if(!f){
		printf ("Error opening file %s : %s\n", cfilename, strerror(errno));
	}
	return f;
}

Uint ExSafeWrite(FILE *f, void* buffer, unsigned int count){
	size_t bytes;
	bytes = fwrite(buffer, 1, count, f);
	if(bytes != count){
		printf("File write failure : %s \n", strerror(errno));
	}
	return bytes;
}

Uint ExSafeRead(FILE*f, void* buffer, int count){
	size_t bytes;
	bytes = fread(buffer, 1, count, f);
	if(bytes != count){
		printf("File read failure : %s\n", strerror(errno));
	}
	return bytes;
}
