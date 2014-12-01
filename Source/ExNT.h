/*
===========================================================================
Copyright (C) 2014 BroodCity Software, Inc. Voldemor2009@hotmail.com

*/
#ifndef EX_NT_H
#define EX_NT_H
#include"ExPreProcessor.h"
#if defined(EX_WINDOWS)
	#include<Windows.h>
#elif defined(EX_LINUX)
	#include<X11/X.h>
#elif defined(EX_ANDROID)

#elif defined(EX_MAC)

#endif
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

// Defination only for simpler understanding of the parameter will do.
#define _IN_	// Header Comments Value will
#define _OUT_	// Header Comments Value will return ou
#define _INOUT_ // Header Will Input a Value as well return.
//

/*
	// type declaration
*/
#if defined(EX_WINDOWS)
	typedef signed __int64 Int64;
	typedef signed __int32 Int32;
	typedef signed __int16 Int16;
	typedef signed __int8  Int8;

	typedef unsigned __int64 Uint64;
	typedef unsigned __int32 Uint32;
	typedef unsigned __int16 Uint16;
	typedef unsigned __int8  Uint8;
	typedef unsigned __int32 Uint;
	typedef unsigned short	 Ushort;

	typedef signed __int32   Int;
	typedef signed short	 Short;
	typedef signed char		 Char;

	typedef float Float;
	typedef double Double;
#ifdef EX_WIN64
	typedef unsigned __int64 uintptr_t;
#else
	typedef unsigned int uintptr_t;
#endif
#if EX_INT_MAX_BITS > 64
	typedef signed __int128 Int128;
	typedef unsigned __int128 Uint128;
#endif

#elif defined(EX_ANDROID) || defined(EX_LINUX)
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
//#ifdef EX_WIN64
//#else
//	typedef unsigned int uintptr_t;
//#endif
#elif defined EX_APPLE
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
typedef Uint32 BitFlag;
typedef Uint8 ColorBitDepth;
typedef Uint64 ULLong;

/* 32 bits [0 to 4,294,967,295] */
typedef Uint32 ClearFlag;
typedef long Long;

/* 64 bits [0 to 18,446,744,073,709,551,615] */
typedef Uint8 InputAxis;
typedef Uint8 Keycode;
typedef void* DataBuffer;


#ifdef __cplusplus
	typedef Uint8 Boolean;
#endif
#ifndef CMD_LIB_H
    typedef enum{xfalse, xtrue }ExBoolean;
#else
    typedef Boolean ExBoolean;
#endif
#ifndef INTERNAL_ENGINEX

#endif

#if !defined(EX_WIN32)
typedef void* HANDLE;
#endif
#ifdef EX_WINDOWS
typedef __success(return >= 0) long ERESULT;
#else
typedef long ERESULT;
#endif
/*
	// ELT Character data type
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
	Float fv;
	Uint32 uv;
	Uint8 ub[4];
} FloatUnion,UintUnion;
typedef union doubleUnion{
	Double Ddata;
	Uint64 Uldata;
	Uint8 ub[8];
}DoubleUnion,UlongUnion;


/*
	// 16 bits high and low value
*/
//
#define EX_MAKEHIWORD(a,b)   {a = ( ( a ) | (( ( b ) << 8) & 0xff00));}
#define EX_MAKELOWORD(a,b)	  {a = ( ( a )  | ( ( b ) & 0x00ff));}
/*
	// 32 bits
*/
#define EX_MAKEHIDWORD(a,b)	{a = ( ( a ) | (( ( b ) << 16) & 0xffff0000));}
#define EX_MAKELODWORD(a,b)	{a = ( ( a ) | ( ( b ) & 0x0000ffff));}
/*
	// 64 bits
*/
#define EX_MAKEHIQWORD(a,b)	{a = ( ( a ) | (( ( b ) << 32) & 0xffffffff00000000));}
#define EX_MAKELOQWORD(a,b) {a = ( ( a ) | ( ( b ) & 0xffffffff00000000));}

/*
	// 128 bits high and low value
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
	// platform specific type
*/
#ifdef EX_WINDOWS
	typedef HWND ExWin;
	typedef HGLRC OpenGLContext;
	typedef HDC WindowContext;
	#define THREAD_CALLBACK __stdcall
#elif defined(EX_LINUX) && defined(GLX_H)
	typedef XID ExWin;
	typedef GLXContext OpenGLContext;
	typedef XID WindowContext;
	#define THREAD_CALLBACK __cdecl
#elif defined(EX_ANDROID)
	typedef XID ExWin;
	typedef GLXContext OpenGLContext;
	typedef XID WindowContext;
	#define THREAD_CALLBACK __cdecl
#elif defined(EX_MAC)
	typedef XID ExWin;
	typedef GLXContext OpenGLContext;
	typedef XID WindowContext;
	#define THREAD_CALLBACK __cdecl
#else
	typedef void* ExWin;
	typedef void* OpenGLContext;
	typedef void* WindowContext;
	#define THREAD_CALLBACK /*__cdecl*/
#endif

#define EX_CALLBACK ELTAPISTDENTRY

/*
	//Thread
*/
typedef void*(THREAD_CALLBACK *thread_routine)(void*);
typedef void* ExThread;

#endif
