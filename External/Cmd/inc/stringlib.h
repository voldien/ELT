/*
===========================================================================
Copyright (C) 2014 BroodCity Software, Inc. Voldemor2009@hotmail.com

*/
#ifndef STRING_LIB_H
#define STRING_LIB_H
#pragma warning(disable : 4127) // conditional expression is constant: while(1)
#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <time.h>
#include <stdarg.h>

#ifdef __cplusplus // C++ Environment
extern "C"{
#endif

/*
//search for string sequence
*/
int strstrsafe(const char* _Str,const char* _Str_comp, char** _Str_find);
/*search referse*/
char* rstrstr(const char* _Str,const char* _Str_comp,int pos);
/*	search for compare word*/
char* strstword(char* _Str, const char* _Str_comp);

/*	trim c-string	*/
void strtrim(char* _Str);
/*	convert string to lowercase letter	*/
void strlower(char* _Str);
/*	convert string to uppercase letter	*/
void strupper(char* _Str);

int strchalength(char* _Str);
int strchaspace(char* _Str);
/*	repeting sequence	*/
int strsequence(char* _Str,char*_Str_sequence);
/*	repeting word sequence	*/
int strrepword(char* _Str, char* _Str_word_sequence);
/*insert text*/
int strinsert(char** _Str, char* _Str_insert, int pos);
/*	erase porition of c-string	*/
int strerase(char** _Str, int pos, int length);



#ifdef UNICODE

int wcsstrsafe(wchar_t* _Wcs, wchar_t* _Wcs_str, wchar_t** _Wcs_find);
/*	trim c-wide-string	*/
void wcstrim(wchar_t* _wStr);
/*	convert string to lowercase letter	*/
void wcslower(wchar_t* _wStr);
/*	convert string to uppercase letter	*/
void wcsupper(wchar_t* _wStr);

int wcssequence(wchar_t* _wStr, wchar_t* _wStr_sequence);

int wcsrepword(wchar_t* _Str, wchar_t* _Str_word_sequence);

int wcsinsert(wchar_t** _Str, wchar_t* _Str_insert, int pos);

int wcserase(wchar_t** _Wsc,int pos, int length);

/*
	// conversts 
*/
int widetostr(const wchar_t* _Wsc, char* _Str);

int strtowide(const char* _Wsc, wchar_t* _Str);
#endif

#ifdef __cplusplus // C++ Environment
}
#endif
#endif