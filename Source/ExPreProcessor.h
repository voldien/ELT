/*
===========================================================================
Copyright (C) 2014 BroodCity Software, Inc. Voldemor2009@hotmail.com

*/
#ifndef EX_PRE_PROCESSOR_H
#define EX_PRE_PROCESSOR_H
	#include<stddef.h>

#ifdef __cplusplus
	#include<cstdio>
	#include<climits>
	#define EX_CPP	// C++ environment
#else
	#include<stdio.h>
	#include<limits.h>
	#define EX_C	// C environment
#endif

// Compiler
#ifdef _MSC_VER //	Visual Studio C++ Compiler.
	#define EX_VC
	#define ENGINE_EX_COMPILER 1
	#if _MSC_VER >= 1800
		#define EX_V12 _MSC_VER
	#elif _MSC_VER >= 1700
		#define EX_VC11 _MSC_VER
	#elif _MSC_VER >= 1600
		#define EX_VC10 _MSC_VER
	#elif _MSC_VER >= 1500
		#define EX_VC9 _MSC_VER
	#elif _MSC_VER >= 1400
		#define EX_VC8 _MSC_VER
	#elif _MSC_VER >= 1300
		#define EX_VC7 _MSC_VER
	#else
		#define EX_VC6 _MSC_VER
	#endif
#pragma warning(disable : 4201)
	#define EX_COMPILER_NAME "Visual Studio C++/C"
#elif defined(__GNUC__) || defined(__SNC__)	// GNU compiler
	#ifdef EX_CPP // G++
	#endif
	#define EX_GNUC
	#define ENGINE_EX_COMPILER 2
	#define EX_COMPILER_NAME "GNU C"
#elif defined(__ghs__)		// GHS
	#define EX_GHS
	#define ENGINE_EX_COMPILER 3
#elif defined(__INTEL_COMPILER)
	#define EX_INTEL
	#define ENGINE_EX_COMPILER 4
	#define EX_COMPILER_NAME "Intel C++"
#else
	#error UnSupported Compiler.
#endif

/*
	// platform define
	//	Architecture!
*/
#ifdef EX_VC
	#if defined(_M_IX86) || defined(_WIN32)
		#define EX_X86
		#define EX_X32
		#define EX_WIN32
		#define EX_WINDOWS
		#define EX_BITS_ARCHITECTURE 32
	#elif defined(_M_X64) || defined(_WIN64)
		#define EX_X64
		#define EX_WIN64
		#define EX_WINDOWS
		#define EX_BITS_ARCHITECTURE 64
	#elif defined(_M_PPC)
		#define EX_PPC
		#define EX_X360
		#define EX_VMX
	#elif defined(_M_ARM)
		#define EX_ARM
		#define EX_ARM_NEON
	#endif
#elif defined EX_GNUC
	#ifdef __CELLOS_LV2__
	#define EX_PS3
	#elif defined(__arm__)
	#define EX_PSP2
	#endif
	#if defined(_WIN32)
		#define EX_WINDOWS
		#define EX_BITS_ARCHITECTURE 32
	#endif
	#if defined (__linux__) || defined(__linux) || defined(linux)
		#define EX_LINUX
		#define EX_UNIX
	#elif defined(__unix__)
		#define EX_UNIX
	#elif defined (ANDROID)
		#define EX_ANDROID
		#define EX_UNIX
	#elif defined (__APPLE__)
		#define EX_APPLE
		#define EX_UNIX
		#if defined(__arm__)
			#define EX_APPLE_IOS
		#elif defined(MACOSX) || defined(macintosh) || defined(Macintosh)
			#define EX_MAC
		#endif
	#elif defined(__CYGWIN)
		#define EX_CYGWIN
		#define EX_LINUX
		#define EX_UNIX
	#elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__)
		#define EX_BSD
	#endif
#else
	#error  Unsupported architecture!
#endif
/**
    C Compiler Version
*/
#if (__STDC_VERSION__ == 201112L)
#   define EX_C11
#elif (__STDC_VERSION == 199901L)
#   define EX_C99
#elif defined(__STDC__)
#   define EX_C90
#endif
//#define EX_XBOX
//#define EX_WEB

// defination of compiler settings
#define LINKER_BUILD_TARGET

/*
// macro defination of Release and Debug  build
*/
#if defined(_DEBUG) || defined(DEBUG)
	#define EX_DEBUG
	#define DEBUGMODE
#elif NDEBUG
	#define EX_RELEASE
	#define RELEASEMODE
#else
	#define EX_RELEASE
	#define RELEASEMODE
#endif

/*
// Unicode
*/
#ifdef UNICODE
	#define EX_UNICODE
	#define _EX_TEXT(quote) L##quote
	#define EX_TEXT(quote)  _EX_TEXT(quote)
#else
	#define EX_ANSI
    #define EX_TEXT(quote) quote
#endif

//end compiler
// ENGINE EX Declaration Behavior


/*
	// declartion specfication
*/
#if !defined(ENGINE_EX_STATIC_BUILD)
	#if defined(EX_WINDOWS) /*&& defined(EX_VC)*/
		#define EX_IMPORT __declspec(dllimport)
		#define EX_EXPORT __declspec(dllexport)
	#elif defined(EX_LINUX)
		#define EX_IMPORT	__attribute__ ((__visibility__ ("default")))
		#define EX_EXPORT	__attribute__ ((__visibility__ ("default")))
	#elif defined(EX_ANDROID)
		#define EX_IMPORT	__attribute__ ((__visibility__ ("default")))
		#define EX_EXPORT	__attribute__ ((__visibility__ ("default")))
	#elif defined(EX_MAC)
		#define EX_IMPORT	__attribute__ ((__visibility__ ("default")))
		#define EX_EXPORT	__attribute__ ((__visibility__ ("default")))
	#else
		#define EX_IMPORT
		#define EX_EXPORT
	#endif
#endif

/*
	// resered keyword
*/
#define EX_EXTERN extern
#define C_EXTERN extern "C"
#define CPP_EXTERN extern "C++"
#define VIRTUAL virtual
#define NORETURN __declspec(noreturn)				// No Return, while loop forever.

/*
	// No Initialization Virtual Table. [4 BYTE In size]
	// only supports in C++ enviroments
*/
#ifdef EX_WINDOWS
	#define NOINITVTABLE __declspec(novtable)
#else
	#define NOINITVTABLE
#endif

/*
	// No Throw
*/
#ifdef EX_WINDOWS
	#define NOTHROW __declspec(nothrow)						// No Throw
#else
	#define NOTHROW
#endif

/*
	// Properties
*/
#define PROPERTIES(_get, _set,_type) __declspec(property(get = _get, put = _set)) _type
#define READONLY_PROPERTY(t,n) __declspec(property(get = property__get_##x)) t x;\typedef t property__tmp_type_##n
#define GET(x) property__tmp_type_##x property__get_##n()
#define SET(n) void property__set_##x(const property__tmp_type_##x& value)

//
#define SCK_VERSION1 0x0101		//WinSocket Version 1
#define SCK_VERSION2 0x0202		//WinSocket Version 2


/*
	//
*/
#if defined(_ENGINE_INTERNAL) || (EX_ENGINE_VERSION_MAJOR < 1)	// Macro Defination Only Defined in this solution.
	#define INTERNAL_ENGINEX	// Used for Assembly Data and Include Data Structor.
	#define EX_INTERNAL_DEVELOP_ENVIROMENT
#elif defined(EXTERNAL_ENGINE_INTERNAL)
	#define INTERNAL_ENGINEX	// Used for Assembly Data and Include Data Structor.
	#define EX_INTERNAL_DEVELOP_ENVIROMENT
#endif

#if (!defined(ENGINE_EX_STATICLIB) && !defined(ENGINE_EX_STATICLIB))
#ifndef ENGINE_EX_LIB
	#define ENGINE_EX_LIB
#endif
#endif

/*
	Calling Convention
*/
#ifdef EX_WINDOWS	// Windows Calling Convention.
	#define ELTAPIENTRY __cdecl
	#define ELTAPIFASTENTRY __fastcall
	#define ELTAPITHISENTRY __thiscall
	#define ELTAPISTDENTRY __stdcall
#else
	#define __cdecl  __attribute__ ((_cdecl))
	#define ELTAPIENTRY //__cdecl
	#define ELTAPISTDENTRY //__cdecl
	#define ELTAPIFASTENTRY //__cdecl
	#define ELTAPITHISENTRY //__cdecl
#endif

// disable on SPU because they are not supported
#if defined(EX_VC)
	#define EX_PUSH_PACK_DEFAULT __pragma(pack(push,8))
	#define EX_POP_PACK			 __pragma(pack(pop))
#elif (defined(EX_GNUC) && !defined(__SPU__)) || defined(EX_GHS)
	#define EX_PUSH_PACK_DEFAULT _Pragma("pack(push,8)")
	#define EX_POP_PACK			 _Pragma("pack(pop)")
#else
	#define EX_PUSH_PACK_DEFAULT
	#define EX_POP_PACK
#endif

/*
// inline
*/
#ifdef EX_WINDOWS
	#define INLINE inline
	#pragma inline_depth(255)
#else
	#define INLINE inline
#endif

/*
// force inline
*/
#if defined(EX_VC)
	#define EX_FORCE_INLINE __forceinline
#elif defined(EX_LINUX)
	#define EX_FORCE_INLINE inline
#elif defined(EX_GNUC) || defined(EX_GHS)
	#define EX_FORCE_INLINE inline __attribute__((always_inline))
#else
	#define EX_FORCE_INLINE inline
#endif

/*
	//	No Inline
*/
#if defined EX_WINDOWS || defined EX_XBOX
	#define EX_NOINLINE __declspec(noinline)
#elif defined(EX_GNUC)  || defined(EX_GHS)
	#define EX_NOINLINE __attribute__ ((oninline))
#else
	#define EX_NOINLINE
#endif

/*
	//Null Pointer
 */
#ifdef EX_WINDOWS
#if  (__cplusplus == 201103L)
	#define EX_NULL nullptr;
#else
	#define EX_NULL NULL
#endif
#else
	#define EX_NULL NULL
#endif

/*
	#define EXDEPRECATED(x) __declspec(deprecated(x))		// deprecated Decleration (x = Warning Message)
*/
#ifdef EX_WINDOWS
	#define EXDEPRECATED  __declspec(deprecated)		// deprecated Decleration (x = Warning Message)
	#define EXDEPRECATEDMESSAGE(x) __declspec(deprecated(x))
#else
	#define EXDEPRECATED(x) attribute(deprecated(x))		// deprecated Decleration (x = Warning Message)
#define EXDEPRECATEDMESSAGE(x) attribute(deprecated(x))
#endif

/*
	// alignment
*/
#ifndef EX_ALIGN
	#if defined(EX_VC)
			#define EX_ALIGN(alignment, decl) __declspec(align(alignment)) decl
			#define EX_ALIGN_PREFIX(alignment) __declspec(align(alignment))
	#elif defined(EX_GNUC)
			#define EX_ALIGN(alignment, decl) decl __attribute__ ((aligned(alignment)))
			#define EX_ALIGN_PREFIX(alignment) __declspec(align(alignment))
	#else
			#define EX_ALIGN(alignment, decl)
			#define EX_ALIGN_PREFIX(alignment)
	#endif
#endif

#if defined(_DLL)
	#define EX_DLL _DLL
#endif

/*
	// Function and other premacro
*/
#if defined(EX_VC)
	#define EX_FUNCNAME __FUNCTION__
	#define EX_FUNCSIG __FUNCSIG__
	#define EX_FUNCDNAME __FUNCDNAME__
	#define __EX_FILE__ __FILE__
	#define __EX_LINE__ __LINE__
#else
	#define EX_FUNCNAME  " "
	#define EX_FUNCSIG   " "
	#define EX_FUNCDNAME " "
	#define __EX_FILE__ __FILE__
	#define __EX_LINE__ __LINE__

#endif

/*
	// Int max bits size supported by compiler or hardware
*/
#if defined(EX_VC)
	#define EX_INT_MAX_BITS _INTEGRAL_MAX_BITS
#else
	#define EX_INT_MAX_BITS 32
#endif
/*
	// Unused
*/
#define EX_UNUSED(_p)	((void)(_p))


#ifndef APPLICATIONTYPE
#if defined(NSCREENSAVER)
	#define APPLICATIONTYPE SCREENSAVER
#else
	#define APPLICATIONTYPE GAME
#endif
#endif

/*
	Rendering Software Interface.
 */
#ifdef EX_WINDOWS
	#define EX_SUPPORT_OPENGL
	#define EX_SUPPORT_DIRECTX
#elif defined(EX_LINUX)
	#define EX_SUPPORT_OPENGL
#elif EX_ANDROID
	#define EX_OPENGL_ES
#elif EX_WEB
	#define EX_OPENGL_ES
#elif defined(EX_PS3) || defined(EX_PS4)
	#define EX_SUPPORT_OPENGL
	#define EX_EDGE
#endif

/*
	// c structs
*/
#ifdef EX_CPP
	#define EX_C_STRUCT
#else
	#define EX_C_STRUCT struct
#endif


/*
	// assembly instruction identication
*/
#if defined(EX_WINDOWS) && defined(EX_VC)
	#define EX_ASSM __asm
#else
	#define EX_ASSM __asm__
#endif


// Export & Import of DLL
#ifndef PROCCLASSEXPORT
	#if defined(INTERNAL_ENGINEX)  && (!defined(ENGINE_EX_STATIC_BUILD))	// Export In DLL Format
		#define DECLSPEC EX_EXPORT
	#elif defined(ENGINE_EX_LIB)  && (!defined(ENGINE_EX_STATIC_BUILD) && !defined(ENGINE_EX_STATIC_TO_DLL_BUILD))	// Import In DLL Format
		#define DECLSPEC EX_IMPORT
	#elif defined(ENGINE_EX_STATIC_TO_DLL_BUILD)	//
		#define DECLSPEC EX_EXPORT
	#else
		#define DECLSPEC // defines nothing. preventing compiling errors
	#endif
#endif

/*
	// ELT Version
*/
#define EX_ENGINE_VERSION_MAJOR 0x0
#define EX_ENGINE_VERSION_MINOR 0x5
#define EX_ENGINE_VERSION_REVISION 0x38

#define EX_ENGINE_PREALPHA EX_TEXT("pa")	        /* Pre alpha    */
#define EX_ENGINE_ALPHA EX_TEXT("a")		        /* Alpha        */
#define EX_ENGINE_BETA EX_TEXT("b")		            /* Beta         */
#define EX_ENGINE_STABLE EX_TEXT("r")		        /* Stable       */
#define EX_ENGINE_RELEASE_SOMETHING EX_TEXT("rc")	/*              */
#define EX_ENGINE_RELEASE_BETTER EX_TEXT("rc5")		/*          */
/*
	// ELT Version [8 bit major | 8 bit minor | 8 bit bugfix | 8 bit reserved ]
*/
#define EX_ENGINE_VERSION ((EX_ENGINE_VERSION_MAJOR << 24) + (EX_ENGINE_VERSION_MINOR << 16) + (EX_ENGINE_VERSION_REVISION << 8) + 0)

#if defined(EX_VC) && defined(EX_INTERNAL_DEVELOP_ENVIROMENT)
	#pragma comment(linker,"/VERSION:0[.50]")
#endif


#ifdef EX_DEBUG
	#define EX_ENGINE_STATUS EX_ENGINE_PREALPHA
#else
	#define EX_ENGINE_STATUS EX_ENGINE_PREALPHA
#endif
/*
	// information
*/
#define EX_ENGINE_COMPILER_ARCHITECTURE
#define EX_ENGINE_BUILT_DATA __DATE__
#define EX_ENGINE_BUILT_TIME __TIME__


// all project don't support NDEBUG || _DEBUG
#if (NDEBUG || _DEBUG)
	#if !(defined NDEBUG ^ defined _DEBUG)
		#error Exactly one of NDEBUG and _DEBUG needs to be defined by preprocessor
	#endif
#endif

/*
	Argumentental function
*/
#ifdef EX_VC
	#define EX_VA_ARGS __VA_ARGS__
#elif defined(EX_GNUC)
	#define EX_VA_ARGS __VA_ARGS__
#else
	#define EX_ARGS ...
#endif

#ifdef INTERNAL_ENGINEX
	#ifdef EX_WINDOWS
		#pragma warning(disable : 4996)	// Disable a warning
		#pragma warning(disable : 4251) // Dll
	#endif
#endif

#endif
