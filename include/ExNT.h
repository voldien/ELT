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
#ifndef _EX_NT_H_
#define _EX_NT_H_ 1
#include"elt_def.h"

#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <stdarg.h>

#ifndef TRUE
#	define TRUE 1
#endif
#ifndef FALSE
#	define FALSE 0
#endif

/*
 *	Type declaration
*/
#if defined(EX_WINDOWS)
	typedef signed __int64 		Int64;
	typedef signed __int32 		Int32;
	typedef signed __int16 		Int16;
	typedef signed __int8  		Int8;

	typedef unsigned __int64 	Uint64;
	typedef unsigned __int32 	Uint32;
	typedef unsigned __int16 	Uint16;
	typedef unsigned __int8  	Uint8;
	typedef unsigned __int32 	Uint;
	typedef unsigned short	 	Ushort;

	typedef signed __int32   	Int;
	typedef signed short	 	Short;
	typedef signed char	 		Char;

#if EX_INT_MAX_BITS > 64
	typedef signed __int128 Int128;
	typedef unsigned __int128 Uint128;
#endif

#elif defined(EX_UNIX)
	typedef signed long long 	Int64;
	typedef signed int		 	Int32;
	typedef signed short	 	Int16;
	typedef signed char		 	Int8;

	typedef signed int	 		Int;
	typedef signed short 		Short;
	typedef signed char  		Char;

	typedef unsigned long long  Uint64;
	typedef unsigned int		Uint32;
	typedef unsigned short		Uint16;
	typedef unsigned char		Uint8;
	typedef unsigned int		Uint;
	typedef unsigned short		Ushort;

#if EX_INT_MAX_BITS > 64
	typedef signed __int128 Int128;
	typedef unsigned __int128 Uint128;
#endif

#elif defined(EX_APPLE)
	typedef signed long long Int64;
	typedef signed int		 Int32;
	typedef signed short	 Int16;
	typedef signed char		 Int8;

	typedef signed int	 Int;
	typedef signed short Short;
	typedef signed char  Char;

	typedef unsigned long long  Uint64;
	typedef unsigned int		Uint32;
	typedef unsigned short		Uint16;
	typedef unsigned char		Uint8;
	typedef unsigned int		Uint;
	typedef unsigned short		Ushort;

	typedef float Float;
	typedef double Double;
#endif
/* 32 bits [0 to 4,294,967,295] */
typedef unsigned long ULong;
/* 32 bits [0 to 4,294,967,295] */
typedef Uint32 Enum;
/* 32 bits [0 to 4,294,967,295] */
typedef Uint8 ColorBitDepth;
typedef Uint64 ULLong;

/* 32 bits [0 to 4,294,967,295] */
typedef Uint32 ClearFlag;
typedef long Long;

/* 64 bits [0 to 18,446,744,073,709,551,615] */
typedef Uint8 Keycode;
/**/
typedef Uint8 ExBoolean;


#ifndef EX_WIN32
	typedef void* HANDLE;
	//EX_DECLARE_HANDLE(HANDLE);
#endif

typedef long ERESULT;

/*
    ELT Character data type
*/
#ifdef EX_UNICODE
	typedef wchar_t ExChar;
	#define EX_STR_LEN wcslen	// length of character of ExChar
#else
	typedef char ExChar;
	#define EX_STR_LEN strlen	// length of character of ExChar
#endif

// TODO change location later on!!
/*
	// window platform...
*/

typedef union floatUnion{
	float fv;
	Uint32 uv;
	Uint8 ub[4];
} FloatUnion,UintUnion;
typedef union doubleUnion{
	double Ddata;
	Uint64 Uldata;
	Uint8 ub[8];
}DoubleUnion,UlongUnion;


/**
	16 bits high and low value
*/
#define EX_MAKEHIWORD(a,b)   {a = ( ( a ) | (( ( b ) << 8) & 0xff00));}
#define EX_MAKELOWORD(a,b)	  {a = ( ( a )  | ( ( b ) & 0x00ff));}
/**
	32 bits
*/
#define EX_MAKEHIDWORD(a,b)	{a = ( ( a ) | (( ( b ) << 16) & 0xffff0000));}
#define EX_MAKELODWORD(a,b)	{a = ( ( a ) | ( ( b ) & 0x0000ffff));}
/**
	64 bits
*/
#define EX_MAKEHIQWORD(a,b)	{a = ( ( a ) | (( ( b ) << 32) & 0xffffffff00000000));}
#define EX_MAKELOQWORD(a,b) {a = ( ( a ) | ( ( b ) & 0xffffffff00000000));}

/**
	128 bits high and low value
*/
#define MAKEHIDQWORD(a,b)
#define MAKELODQWORD(a,b)


#define EX_MAKELONG(a, b)      ((long)(((Uint16)(((Uint32)(a)) & 0xffff)) | ((Uint32)((Uint16)(((Uint32)(b)) & 0xffff))) << 16))


#define EX_LOWORD(l)        ((Uint16)(((Uint16)(l)) & 0xffff))
#define EX_HIWORD(l)        ((Uint16)((((Uint16)(l)) >> 16) & 0xffff))
#define EX_LOBYTE(w)        ((Uint8)(((Uint16)(w)) & 0xff))
#define EX_HIBYTE(w)        ((Uint8)((((Uint16)(w)) >> 8) & 0xff))

/*
#define EX_LOQWORD(q)			((QWORD)(((DWORD_PTR)(l)) & 0xffffffff))
#define EX_HIQWORD(q)			((QWORD)((((DWORD_PTR)(l)) >> 32) & 0xffffffff))
*/

#ifdef EX_VC
	#define EX_DECLARE_HANDLE(name) struct name##__{int unused;}; typedef struct name##__ *name
#else
	#define EX_DECLARE_HANDLE(name) struct name##__{int unused;}; typedef struct name##__ *name
#endif

/*
 *	platform specific type
*/
typedef void* ExWin;
typedef void* OpenGLContext;
typedef void* ExOpenGLContext;
typedef void* OpenCLContext;
typedef void* ExOpenCLContext;
typedef void* WindowContext;
typedef void* ExWindowContext;
typedef void* ExAudioContext;

#ifdef EX_WINDOWS

	#define THREAD_CALLBACK __stdcall
#elif defined(EX_LINUX) && defined(GLX_H)
	#define THREAD_CALLBACK //__cdecl
#elif defined(EX_ANDROID)
	#define THREAD_CALLBACK //__cdecl
#elif defined(EX_MAC)
	#define THREAD_CALLBACK __cdecl
#else

	#define THREAD_CALLBACK __cdecl
#endif

#define EX_CALLBACK ELTAPISTDENTRY

/*
 *	Thread
*/
typedef void*(*interrupt_routine)(void*);
typedef void*(THREAD_CALLBACK *thread_routine)(void*);
typedef void* ExThread;

#endif
