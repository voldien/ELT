#include"system/elt_file.h"

/*	*/
#ifdef EX_WINDOWS
	#include<windows.h>
#endif
/*	*/
#ifdef EX_UNIX
	#include<unistd.h>
	#include<dirent.h>
#endif
#include<errno.h>
#include<string.h>



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
	buffer = (char*)malloc(length + 1);
	((char*)buffer)[length] = 0;
	length = ExSafeRead(f, buffer, length);
	fclose(f);
	*bufferptr = buffer;
	return length;
}

long int ExSaveFile(const ExChar* cfilename, void* racBuffer, unsigned int riSize){
	long int nBytes;
	FILE *f;
	f = ExSafeOpenWrite(cfilename);
	if(!f)
		return -1;
	nBytes = ExSafeWrite(f, racBuffer, riSize);
	fclose(f);
	return nBytes;
}

long int ExAppendFile(const ExChar* cfilename, void* racBuffer, unsigned int csize){
	long int nBytes;
	FILE* f;
	f = ExSafeOpenWrite(cfilename);
	if(!f)
		return -1;

	/*	seek to end of file.	*/
	fseek(f, SEEK_END, 0);
	nBytes = ExSafeWrite(f, racBuffer, csize);
	fclose(f);
	return nBytes;
}

long int ExInsertFile(const ExChar* cfilename, long int offset, void* racBuffer, long int csize){
	long int nBytes;
	long int offsetpoint;
	long int fsize;
	char tmpbuf[4096];
	FILE* f;
	f = ExSafeOpenWrite(cfilename);
	if(!f)
		return -1;

	/*	offset the whole file from offset	*/
	fsize = private_ExGetFileStreamSize(f);
	offsetpoint = fsize;
	fseek(f, SEEK_END, 0);

	/*	TODO fix. make the data movement in block size.	*/
	while(offsetpoint > offset){
		fseek(f, SEEK_END, fsize - offsetpoint - sizeof(tmpbuf));
		fread(tmpbuf, sizeof(tmpbuf), 1, f);
		fseek(f, SEEK_END, fsize - offsetpoint);
		fwrite(f,sizeof(tmpbuf), 1, tmpbuf);
		offsetpoint -= sizeof(tmpbuf);
	}

	fclose(f);
	return nBytes;
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

long int ExSafeWrite(FILE *f, void* buffer, unsigned int count){
	size_t bytes;
	bytes = fwrite(buffer, 1, count, f);
	if(bytes != count){
		printf("File write failure : %s \n", strerror(errno));
	}
	return bytes;
}

long int ExSafeRead(FILE*f, void* buffer, int count){
	size_t bytes;
	bytes = fread(buffer, 1, count, f);
	if(bytes != count){
		printf("File read failure : %s\n", strerror(errno));
	}
	return bytes;
}


FILE* ExSetFileMode(FILE* f, const char* mode){
	return freopen(NULL, mode, f);
}
