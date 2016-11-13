/**
    ELT (Engine Library Toolkit) is a multi platform engine toolkit
    Copyright (C) 2014  Valdemar Lindberg

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/
#ifndef _ELT_NT_H_
#define _ELT_NT_H_ 1
#include"elt_def.h"

#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <stdarg.h>

#ifdef __cplusplus	/*	C++ Environment	*/
extern "C"{
#endif


#ifndef TRUE
#	define TRUE 1
#endif
#ifndef FALSE
#	define FALSE 0
#endif




/* 64 bits [0 to 18,446,744,073,709,551,615] */
typedef unsigned char ExKeycode;

/*	*/
typedef unsigned char ExBoolean;

/*
 *	Atom data type.
 */
typedef int ExAtom;

/*
 *
 */
typedef long ERESULT;

/*
 *
 */
typedef unsigned int exivec4 EX_ALIGN_VECTOR(16);
typedef unsigned int exivec3 EX_ALIGN_VECTOR(16);
typedef unsigned int exivec2 EX_ALIGN_VECTOR(8);


/*
 *
 */
#ifdef EX_MSVC
	#define EX_DECLARE_HANDLE(name) struct name##__{int unused;}; typedef struct name##__ *name
#else
	#define EX_DECLARE_HANDLE(name) typedef struct name##__ { int unused; } *name
#endif
/*
 *
 */
EX_DECLARE_HANDLE(ExHandle);




/**/
typedef void* ExDisplay;



/*
 *	ELT Character data type.
 */
typedef wchar_t ExWide;
#ifdef EX_UNICODE
	typedef wchar_t ExChar;
	#define EX_STR_LEN wcslen	/*	length of character of ExChar	*/
#else
	typedef char ExChar;
	#define EX_STR_LEN strlen	/*	length of character of ExChar	*/
#endif

/*
 *	16 bits high and low value
 */
#define EX_MAKEHIWORD(a,b)	{a = ( ( a ) | (( ( b ) << 8) & 0xff00));}
#define EX_MAKELOWORD(a,b)	{a = ( ( a )  | ( ( b ) & 0x00ff));}

/*
 *	32 bits
 */
#define EX_MAKEHIDWORD(a,b)	{a = ( ( a ) | (( ( b ) << 16) & 0xffff0000));}
#define EX_MAKELODWORD(a,b)	{a = ( ( a ) | ( ( b ) & 0x0000ffff));}

/*
 *	64 bits
 */
#define EX_MAKEHIQWORD(a,b)	{a = ( ( a ) | (( ( b ) << 32) & 0xffffffff00000000));}
#define EX_MAKELOQWORD(a,b) {a = ( ( a ) | ( ( b ) & 0xffffffff00000000));}

#define EX_MAKELONG(a, b)      ((long)(((unsigned short)(((unsigned int)(a)) & 0xffff)) | ((unsigned int)((unsigned short)(((unsigned int)(b)) & 0xffff))) << 16))


#define EX_LOWORD(l)        ((unsigned short)(((unsigned short)(l)) & 0xffff))
#define EX_HIWORD(l)        ((unsigned short)((((unsigned short)(l)) >> 16) & 0xffff))
#define EX_LOBYTE(w)        ((unsigned char)(((unsigned short)(w)) & 0xff))
#define EX_HIBYTE(w)        ((unsigned char)((((unsigned short)(w)) >> 8) & 0xff))


/**
 *	platform specific type.
 */
typedef void* ExWin;
typedef void* ExOpenGLContext;
typedef void* ExOpenCLContext;
typedef void* ExEGLContext;
typedef void* ExWindowContext;
typedef void* ExAudioContext;
typedef void* ExEGLDisplay;
typedef void* ExXDisplay;


/*	Thread callback convention.	*/
#ifdef EX_WINDOWS
	#define EX_THREAD_CALLBACK __stdcall
#elif defined(EX_LINUX) && defined(GLX_H)
	#define EX_THREAD_CALLBACK /*__cdecl	*/
#elif defined(EX_ANDROID)
	#define EX_THREAD_CALLBACK /*__cdecl	*/
#elif defined(EX_MAC)
	#define EX_THREAD_CALLBACK __cdecl
#else
	#define EX_THREAD_CALLBACK __cdecl
#endif


/**
 *	callback.
 */
#define EX_CALLBACK ELTAPISTDENTRY
typedef void(EX_CALLBACK* ExCallBack)(void);

/**
 *	Thread callback data types.
 */
typedef void* (EX_CALLBACK *ex_interrupt_routine)(void*);
typedef void* (EX_THREAD_CALLBACK *ex_thread_routine)(void* phandle);
typedef void* (EX_THREAD_CALLBACK *ExThreadRoutine)(void* phandle);
typedef void* ExThread;


#ifdef __cplusplus	/*	C++ Environment	*/
}
#endif

#endif
