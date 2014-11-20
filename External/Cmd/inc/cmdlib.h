/*
===========================================================================
Copyright (C) 2014 BroodCity Software, Inc. Voldemor2009@hotmail.com

*/
#ifndef CMD_LIB_H
#define CMD_LIB_H
#ifdef _WIN32 
	#pragma warning(disable : 4244) // mips
	#pragma warning(disable : 4136) // x86
	#pragma warning(disable : 4051) // alpha

	#pragma warning(disable : 4018) // signed / unsigned mismatch
	#pragma warning(disable : 4305)	// truncate from double to float

	#pragma warning(disable : 4995) // #pragma marked deprecated
	//#pragma warning(disable :  4996) //
	#include<string.h>
	#pragma intrinsic(memset,memcpy)
	#define EXPORT_DLL __declspec(dllexport)
	#define IMPORT_DLL __declspec(dllimport)
#ifdef _DLL
	#pragma comment(lib,"Cmd.lib")
#endif
#else
	
#endif

#include<stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <time.h>
#include <stdarg.h>
#include<limits.h>

typedef unsigned char byte;
	
#ifndef __cplusplus
  typedef enum{false,true}Boolean;
#else
  typedef unsigned char Boolean;
#endif
#ifdef __cplusplus
extern "C"{
#endif
#define _optional_
#define STATIC_ASSERT(x) (sizeof(x))

/*
	// file managerment
*/

/*	get file length in bytes	*/
int fileLenght(FILE* f);
 
FILE *SafeOpenWrite (const char *filename);
FILE *SafeOpenRead (const char *filename);

void SafeWrite(FILE *f,void* buffer, unsigned int count);
void SafeRead(FILE*f, void* buffer, int count);

void InsertFreeSpace(FILE* file, unsigned int pos, unsigned int length);

/*file exist*/
Boolean FileExist(const char* cfilename);
/*
	// Save data onto file
*/
void SaveFile(const char* cfilename, void* buffer, unsigned int count);
/*
	// Load File From File
*/
int LoadFile(const char* cfilename, void** bufferptrs);

int	CopyFile(const char* cfilename, const char* new_cfilename);
int CopyFilef(FILE* stream, FILE* fnewstream);

/*
	// Error
*/
void Error(const char* errorChar, ... );

/*
	// memory functionallity
*/
void memoryshiftl(void* source,unsigned int byteoffset);
void memoryshiftr(void* source,unsigned int byteoffset);


void replacedata(void);

#ifdef __cplusplus
}
#endif
#endif