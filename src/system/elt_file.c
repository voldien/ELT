#include"system/elt_file.h"
#ifdef EX_WINDOWS
	#include<windows.h>
#endif
#include<stdio.h>

static long int ExGetFileStreamSize(FILE* file){
    unsigned int pos;
    long size;
    pos = ftell(file);
    fseek(file, 0,SEEK_END);
    size = ftell(file);
    fseek(file, pos, SEEK_SET);
    return size;
}

DECLSPEC long int ELTAPIENTRY ExGetFileSize(const char* cfilname){
    FILE* file;
    fpos_t pos;
    long size;
    file = fopen(cfilname,"rb");
    size = ExGetFileStreamSize(file);
    fclose(file);
    return size;
}

DECLSPEC int ELTAPIENTRY ExLoadFile(const char* cfilename, void** bufferptr){
	FILE*f;
	void* buffer;
	long length;
	*bufferptr = NULL;

	if(!cfilename || strlen(cfilename) == 0){
		return -1;
	}

	f = fopen(cfilename,"rb");
	if(!f){
		return -1;
	}
	length = ExGetFileStreamSize(f);
	buffer = malloc(length + 1);
	((char*)buffer)[length] = 0;
	ExSafeRead(f,buffer,length);
	fclose(f);
	*bufferptr = buffer;
	return length;
}

int ELTAPIENTRY ExSaveFile(const char* cfilename, void* racBuffer, unsigned int riSize){
	FILE *f;
	f = ExSafeOpenWrite(cfilename);
	ExSafeWrite(f,racBuffer,riSize);
	fclose(f);
	return f ? 1 : 0;
}

FILE* ExSafeOpenWrite(const char *filename){
	FILE* f;
	f = fopen(filename, "wb");
	if(!f){
		printf ("Error opening file %s: %s\n",filename,strerror(errno));
	}
	return f;
}

FILE* ExSafeOpenRead(const char *filename){
	FILE* f;
	f = fopen(filename,"rb");
	if(!f){
		printf ("Error opening file %s : %s\n",filename,strerror(errno));
	}
	return f;
}

void ExSafeWrite(FILE *f, void* buffer, unsigned int count){
	if((int)fwrite(buffer,1, count, f) != count){
		printf("File write failure : %s \n",strerror(errno));
	}
}

void ExSafeRead(FILE*f, void* buffer, int count){
	if((int)fread(buffer,1,count,f) != count){
		printf("File read failure : %s\n",strerror(errno));
	}
}


int ELTAPIENTRY ExCreateDirectory(const char* directory){
#ifdef EX_UNIX
	return mkdir(directory,644);
#elif defined(EX_WINDOWS)
	return CreateDirectory(directory,NULL);
#endif
}
