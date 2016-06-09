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
#ifndef _ELT_DEF_H_
#define _ELT_DEF_H_ 1
#include<stddef.h>
#include<stdint.h>


#ifdef __cplusplus
	#include<cstdio>
	#include<climits>
	#include<ctime>
	#define EX_CPP	/*	C++ environment	*/
#else
	#include<stdio.h>
	#include<limits.h>
	#include<time.h>
	#define EX_C	/*	C environment	*/
#endif


/*
 *	Compiler.
 */
#ifdef _MSC_VER 	/*	Visual Studio C++ Compiler.	*/
	#define EX_MSVC
	#define ENGINE_EX_COMPILER 1
	#if _MSC_VER >= 1900
		#define EX_MSVC13 _MSC_VER
	#elif _MSC_VER >= 1800
		#define EX_MSVC12 _MSC_VER
	#elif _MSC_VER >= 1700
		#define EX_MSVC11 _MSC_VER
	#elif _MSC_VER >= 1600
		#define EX_MSVC10 _MSC_VER
	#elif _MSC_VER >= 1500
		#define EX_MSVC9 _MSC_VER
	#elif _MSC_VER >= 1400
		#define EX_MSVC8 _MSC_VER
	#elif _MSC_VER >= 1300
		#define EX_MSVC7 _MSC_VER
	#else
		#define EX_MSVC6 _MSC_VER
	#endif
    	#pragma warning(disable : 4201)
	#define EX_COMPILER_NAME "Visual Studio C++/C"

#elif defined(__clang__)  || defined(__llvm__)           /*  LLVM, clang   */
    #define EX_LLVM 1
	#define EX_CLANG 1
	#define ENGINE_EX_COMPILER 5
	#define EX_COMPILER_NAME "LLVM/CLANG"
	#define EX_COMPILER_MAJOR_VERSION __clang_major__
	#define EX_COMPILER_MINOR_VERSION __clang_minor__

#elif defined(__GNUC__) || defined(__SNC__) || defined( __GNUC_MINOR__)	/*  GNU C Compiler	*/
	#define EX_GNUC 1
	#define ENGINE_EX_COMPILER 2
	#define EX_COMPILER_NAME "GNU C"
	#define EX_COMPILER_MAJOR_VERSION __clang_major__
	#define EX_COMPILER_MINOR_VERSION __clang_minor__

#elif defined(__GNUG__) /*  GNU C++ Compiler*/
	#define EX_GNUC 2

#elif defined(__ghs__)		/* GHS	*/
	#define EX_GHS 1
	#define ENGINE_EX_COMPILER 3

#elif defined(__HP_cc) || defined(__HP_aCC)			/*	*/

#elif defined(__PGI)			/*	*/

#elif defined(__ICC) || defined(__INTEL_COMPILER) /*  Intel Compiler  */
	#define EX_INTEL
	#define ENGINE_EX_COMPILER 4
	#define EX_COMPILER_NAME "Intel C++"

#elif defined(__SUNPRO_C) || defined(__SUNPRO_CC)

#else
	#error Unsupported Compiler.
#endif




/*
 *	Find platform.
 */
#ifdef EX_MSVC

	#if defined(_M_IX86) || defined(_WIN32)
		#define EX_X86                          /**/
		#define EX_X32                          /**/
		#define EX_WIN32                        /**/
		#define EX_WINDOWS                      /**/
	#elif defined(_M_X64) || defined(_WIN64)
		#define EX_X64                          /**/
		#define EX_WIN64                        /**/
		#define EX_WINDOWS                      /**/
	#elif defined(__WIN32__)
		#define EX_WINDOWS
	#elif defined(__WINDOWS__)
		#define EX_WINDOWS
	#elif defined(_M_PPC)
		#define EX_PPC                          /**/
		#define EX_X360                         /**/
		#define EX_VMX                          /**/
	#elif defined(_M_ARM)
		#define EX_ARM                          /**/
		#define EX_ARM_NEON                     /**/
	#endif

#elif defined(EX_GNUC) || defined(EX_CLANG)

	#ifdef __CELLOS_LV2__   /**/
        #define EX_PS3                          /*	playstation 3*/
	#elif defined(__arm__)	/**/
		#define EX_ARM
        #define EX_PSP2                         /*	playstation portable 2*/
        #define EX_RAS_PI                       /*	rasberry pi	*/
	#endif

	#if defined(_WIN32) || defined(WIN32) || defined(OS_WINDOWS) || defined(_WIN64) /**  Window*/
		#define EX_X86
		#define EX_WINDOWS                      /**/
		#define __WIN32__
	#endif

	#if ( defined(__linux__) || defined(__linux) || defined(linux) ) && (!(__ANDROID__) || !(ANDROID))	/* Linux */
		#define EX_LINUX 1                       /**/
		#if defined(__amd64) || defined(__x86_64__) || defined(__i386__)
            #define EX_X86 1
			#define EX_X86LINUX
		#endif
		#if defined(__arm__)
              #define EX_ARM 1
        #endif

	#elif defined (ANDROID) || defined(__ANDROID__) || __ANDROID_API__ > 9  /** Android */
        #include<jni.h>
		#define EX_ANDROID 1
		/*  android Architecture*/
        #if defined(__arm__)
			#define EX_ARM 1
		  #if defined(__ARM_ARCH_7A__)
			#if defined(__ARM_NEON__)
			  #if defined(__ARM_PCS_VFP)
				#define ABI "armeabi-v7a/NEON (hard-float)"
			  #else
				#define ABI "armeabi-v7a/NEON"
			  #endif
			#else
			  #if defined(__ARM_PCS_VFP)
				#define ABI "armeabi-v7a (hard-float)"
			  #else
				#define ABI "armeabi-v7a"
			  #endif
			#endif
		  #else
		   #define ABI "armeabi"
		  #endif
		#elif defined(__i386__)
		   #define ABI "x86"
		#elif defined(__x86_64__)
		   #define ABI "x86_64"
		#elif defined(__mips64)  /* mips64el-* toolchain defines __mips__ too */
		   #define ABI "mips64"
		#elif defined(__mips__)
		   #define ABI "mips"
		#elif defined(__aarch64__)
		   #define ABI "arm64-v8a"
		#else
		   #define ABI "unknown"
		#endif

	#elif defined (__APPLE__)   /*  Apple product   */
		#define EX_APPLE 1
		#if defined(__arm__)
			#define EX_APPLE_IOS    /*  Apple iphone/ipad OS    */
		#elif defined(MACOSX) || defined(macintosh) || defined(Macintosh)
			#define EX_MAC 1
		#endif
	#elif defined(__CYGWIN__) 	/*	windows*/
		#define EX_CYGWIN 1
		#ifdef EX_UNIX

		#else
				#define EX_WINDOWS 1
		#endif
	#elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__)   /*  BSD	*/
		#define EX_BSD
	#elif defined(__OpenBSD__)
		#define EX_OPENBSD
	#elif defined(__llvm__) || defined(__clang__)   	/*  llvm    */
		#define EX_LLVM 1
	#elif defined(__MINGW32__)

	#endif

#elif defined(__ICC) || defined(__INTEL_COMPILER)

#else
	#error  Unsupported architecture!   /*  No architecture support implicitly. remove this line to compile anyway*/
#endif

#if defined(__native_client__)	/*	nacl google	*/
	#define EX_NACL 1
#endif
#if defined(__pnacl__)          /* portable nacl google */
	#define EX_PNACL 1
#endif
#if defined(__unix__) || defined(__unix) || defined(unix)	/*  Unix    */
	#   define EX_UNIX 1
#endif



/*
 *	Find the arch type.
 */
#if defined(__x86_64__) || defined(_M_X64) || defined(__powerpc64__) || defined(__alpha__) || defined(__ia64__) || defined(__s390__) || defined(__s390x__) || defined(__arm64__) || defined(_aarch64_) || defined(__mips64) || defined(__mips64_)
	#define EX_ARCHITECTURE_64
#else
	#define EX_ARCHITECTURE_32
#endif
#if defined(__arm__)
	  #define EX_ARM 1
#endif


/*
 *	module information for SWIG interpreter.
 */
#ifdef SWIG
	%module elt
#endif



/*
 *
 */
#ifdef GL_ES_VERSION_3_0
	#define EX_GL_ES_VERSION
#endif



/*
 *   C Compiler Version.
 */
#if (__STDC_VERSION__ == 201112L)
#   define EX_C11
#elif (__STDC_VERSION == 199901L)
#   define EX_C99
#elif defined(__STDC__)
#   define EX_C90
#endif


/*
 *	Macro definition of Release and Debug build.
 */
#if defined(_DEBUG) || defined(DEBUG)
	#define EX_DEBUG	1
	#define DEBUGMODE	1
#elif defined(NDEBUG)
	#define EX_RELEASE	1
	#define RELEASEMODE	1
#else
	#define EX_RELEASE
	#define RELEASEMODE
	#pragma message("Warning: You'd need to add _DEBUG and DEBUG for this compiler.")
#endif


/*
 *	Converting character into a constant string in the precompiling stage.
 */
#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

/*
 *	Unicode macro for converting constant string to
 */
#ifdef UNICODE  /*  UTF-16*/
	#define EX_UNICODE
	#define _EX_TEXT(quote) L##quote
	#define EX_TEXT(quote)  _EX_TEXT(quote)
#else           /*	ASCII / UTF-8	*/
	#define EX_ANSI
    #define EX_TEXT(quote) quote
#endif



/*
 *	Declaration specification.
*/
#if !defined(ENGINE_EX_STATIC_BUILD)
	#if defined(EX_WINDOWS) || defined(EX_MSVC)					/*	Window	*/
		#define EX_IMPORT __declspec(dllimport)
		#define EX_EXPORT __declspec(dllexport)
	#elif defined(EX_LINUX)										/*	Linux	*/
		#define EX_IMPORT	__attribute__ ((__visibility__ ("default")))
		#define EX_EXPORT	__attribute__ ((__visibility__ ("default")))
	#elif defined(EX_ANDROID)									/*	Android	*/
        #ifndef EX_JINI
            #define EX_IMPORT	__attribute__ ((__visibility__ ("default")))
            #define EX_EXPORT	__attribute__ ((__visibility__ ("default")))
		#else
            #define EX_IMPORT
            #define EX_EXPORT	JNIEXPORT
		#endif
	#elif defined(EX_MAC)
		#define EX_IMPORT	__attribute__ ((__visibility__ ("default")))
		#define EX_EXPORT	__attribute__ ((__visibility__ ("default")))
	#elif defined(EX_NACL) || defined(EX_PNACL)
		#include "ppapi/c/ppp.h"
		#define EX_IMPORT
		#define EX_EXPORT PP_EXPORT
	#else
		#pragma message("Warning: You'd need to add EX_IMPORT and EX_IMPORT for this compiler.")
		#define EX_IMPORT
		#define EX_EXPORT
	#endif
#endif

/*
 *   Reserved keyword.
 */
#define EX_EXTERN extern
#define C_EXTERN extern "C"

/*
 *
 */
#ifdef EX_MSVC
	#define NORETURN __declspec(noreturn)				/* No Return, will loop forever.	*/
#elif defined(EX_GNUC)
	#define NORETURN __attribute__(noreturn)
#else
	#pragma message("Warning: You'd need to add EX_NOTHROW for this compiler.")
#endif


/*
 *	No Throw.
 */
#ifdef EX_MSVC
	#define EX_NOTHROW __declspec(nothrow)						/* No Throw	*/
#elif defined(EX_GNUC)
	#define EX_NOTHROW __attribute__(nothrow)
#else
	#pragma message("Warning: You'd need to add EX_NOTHROW for this compiler.")
#endif



/*
 *	Internal.
 */
#if defined(_ENGINE_INTERNAL) || (EX_ENGINE_VERSION_MAJOR < 1)	/*/ Macro Definition Only Defined in this solution.	*/
	#define INTERNAL_ENGINEX	// Used for Assembly Data and Include Data structure.
	//#define EX_INTERNAL_DEVELOP_ENVIROMENT
#elif defined(EXTERNAL_ENGINE_INTERNAL)
	#define INTERNAL_ENGINEX	// Used for Assembly Data and Include Data structure.
	//#define EX_INTERNAL_DEVELOP_ENVIROMENT
#endif


#if (!defined(ENGINE_EX_STATICLIB) && !defined(ENGINE_EX_STATICLIB))
	#ifndef ENGINE_EX_LIB
		#define ENGINE_EX_LIB
	#endif
#endif


/*
 *	Calling Convention
 *	__cdecl		:
 *	__stdcall	:
 *	__fastcall	:
 *
*/
#ifdef EX_WINDOWS	        				/* Windows Calling Convention.*/
	#define ELTAPIENTRY     __cdecl
	#define ELTAPIFASTENTRY __fastcall
	#define ELTAPITHISENTRY __thiscall
	#define ELTAPISTDENTRY  __stdcall
#elif defined(EX_ANDROID)   				/* Android Calling Convention*/
    #define ELTAPIENTRY JNICALL
    #define ELTAPIFASTENTRY JNICALL
    #define ELTAPITHISENTRY JNICALL
    #define ELTAPISTDENTRY JNICALL
#else										/*	GNU	*/
#   if !defined(__cdecl) && defined(EX_GNUC)
        #define __cdecl  __attribute__ ((__cdecl__))
        #define __stdcall  __attribute__ ((stdcall))
		#define __fastcall __attribute__((fastcall))
#   endif

	#define ELTAPIENTRY     __cdecl
	#define ELTAPISTDENTRY  __stdcall
	#define ELTAPIFASTENTRY __fastcall
#endif



/*
 *	Disable on SPU because they are not supported
 */
#if defined(EX_MSVC)
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
 *	Inline.
*/
#if defined(EX_MSVC)
	#define EX_INLINE inline
	#pragma inline_depth(255)
#else
	#define EX_INLINE inline
#endif

/*
 *	force inline.
 */
#if defined(EX_MSVC)
	#define EX_FORCE_INLINE __forceinline
#elif defined(EX_LINUX)
	#define EX_FORCE_INLINE inline
#elif defined(EX_GNUC) || defined(EX_GHS)
	#define EX_FORCE_INLINE inline __attribute__((always_inline))
#else
	#pragma message("Warning: You'd need to add EX_FORCE_INLINE for this compiler.")
#endif

/*
 *	No inline.
 */
#if defined EX_WINDOWS || defined EX_XBOX
	#define EX_NOINLINE __declspec(noinline)
#elif defined(EX_GNUC)  || defined(EX_GHS) || defined(EX_CLANG)
	#define EX_NOINLINE __attribute__ ((oninline))
#else
	#pragma message("Warning: You'd need to add Ex_NOINLINE for this compiler.")
#endif


/*
 *	#define EXDEPRECATED(x) __declspec(deprecated(x))		// Deprecated deceleration (x = Warning Message)
 */
#ifdef EX_MSVC
	#define EXDEPRECATED  __declspec(deprecated)		    // Deprecated deceleration (x = Warning Message)
	#define EXDEPRECATEDMESSAGE(x) __declspec(deprecated(x))
#elif defined(EX_GNUC) || defined(EX_CLANG) || defined(EX_GNUCXX)
	#define EXDEPRECATED __attribute__(( deprecated ))		    	// Deprecated deceleration (x = Warning Message)
    #define EXDEPRECATEDMESSAGE(msg) __attribute__ (( deprecated ( msg ) ))
#else
	#pragma message("Warning: You'd need to add EXDEPRECATED for this compiler.")
#endif

/*
 *	Alignment of data.
*/
#ifndef EX_ALIGN
	#if defined(EX_MSVC)
		#define EX_ALIGN(alignment, decl) __declspec(align(alignment)) decl
		#define EX_ALIGN_PREFIX(alignment) __declspec(align(alignment))
		#define EX_ALIGN_VECTOR(alignment)  __declspec ((__vector_size__ (alignment), __may_alias__))
	#elif defined(EX_GNUC)
		#define EX_ALIGN(alignment, decl) decl __attribute__ ((aligned(alignment)))
		#define EX_ALIGN_PREFIX(alignment) __attribute__ ((aligned(alignment)))
		#define EX_ALIGN_VECTOR(alignment)  __attribute__ ((__vector_size__ (alignment), __may_alias__))
	#elif defined(EX_CLANG)
		#define EX_ALIGN(alignment, decl) decl __attribute__ ((aligned(alignment)))
		#define EX_ALIGN_PREFIX(alignment) __attribute__ ((aligned(alignment)))
#define EX_ALIGN_VECTOR(alignment)  __attribute__ ((__vector_size__ (alignment), __may_alias__))
	#else
		#pragma message("Warning: You'd need to add EX_ALIGN, EX_ALIGN_PREFIX, EX_ALIGN_VECTOR for this compiler.")
		#define EX_ALIGN(alignment, decl)
		#define EX_ALIGN_PREFIX(alignment)
		#define EX_ALIGN_VECTOR(alignment)
	#endif
#endif

#if defined(_DLL)
	#define EX_DLL _DLL
#endif


/*
 *	Function and other predefined macro.
 */
#if defined(EX_MSVC) && !defined(EX_DISABLE_SOURCECODE_INFO)
	#define EX_FUNCNAME __FUNCTION__
	#define EX_PRETTYFUNCNAME __PRETTY_FUNCTION__
	#define EX_FUNCSIG __FUNCSIG__
	#define EX_FUNCDNAME __FUNCDNAME__
	#define __EX_FILE__ __FILE__
	#define __EX_LINE__ __LINE__
#elif ( defined(EX_GNUC) || defined(EX_CLANG) ) && !defined(EX_DISABLE_SOURCECODE_INFO)
	#define EX_FUNCNAME  __FUNCTION__
	#define EX_PRETTYFUNCNAME __PRETTY_FUNCTION__
	#define EX_FUNCSIG   __FUNCSIG__
	#define EX_FUNCDNAME ""
	#define __EX_FILE__ __FILE__
	#define __EX_LINE__ __LINE__
#else
	#define EX_FUNCNAME  ""
	#define EX_FUNCSIG   ""
	#define EX_FUNCDNAME ""
	#define __EX_FILE__ ""
	#define __EX_LINE__ __LINE__
#endif

/*
 *	Int max bits size supported by compiler or hardware.
 */
#if defined(EX_MSVC)
	#define EX_INT_MAX_BITS _INTEGRAL_MAX_BITS
#elif defined(EX_GNUC)
	#define EX_INT_MAX_BITS _INTEGRAL_MAX_BITS
#elif defined(EX_CLANG)
	#define EX_INT_MAX_BITS	64
#endif

/*
 *	Unused macro, will make the compiler to exclude it from the final binary.
 */
#define EX_UNUSED(_p)	((void)(_p))


/*
 *	Rendering API interface.
*/
#ifdef EX_WINDOWS
	#define EX_SUPPORT_OPENGL
	#define EX_SUPPORT_DIRECTX
#elif defined(EX_LINUX)
	#define EX_SUPPORT_OPENGL
#elif defined(EX_ANDROID)
	#define EX_OPENGL_ES
#elif EX_WEB
	#define EX_OPENGL_ES
#elif defined(EX_PS3) || defined(EX_PS4)
	#define EX_SUPPORT_OPENGL
	#define EX_EDGE
#endif

/*
 *	C struct.
 */
#ifdef EX_CPP
	#define EX_C_STRUCT
#else
	#define EX_C_STRUCT struct
#endif


/*
 *	Compiler assembly instruction identification.
 */
#if defined(EX_MSVC)
	#define EX_ASM __asm
#elif defined(EX_GNUC) || defined(EX_GNUCXX)
	#define EX_ASM __asm__
#elif defined(EX_CLANG)
	#define EX_ASM asm
#endif


/*
 *	Export and import deceleration.
 */
#ifndef PROCCLASSEXPORT
	#if defined(INTERNAL_ENGINEX)  && (!defined(ENGINE_EX_STATIC_BUILD))	// Export In DLL Format
		#define ELTDECLSPEC EX_EXPORT
	#elif defined(ENGINE_EX_LIB)  && (!defined(ENGINE_EX_STATIC_BUILD) && !defined(ENGINE_EX_STATIC_TO_DLL_BUILD))	// Import In DLL Format
		#define ELTDECLSPEC EX_IMPORT
	#elif defined(ENGINE_EX_STATIC_TO_DLL_BUILD)	//
		#define ELTDECLSPEC EX_EXPORT
	#else
		#define ELTDECLSPEC // defines nothing. preventing compiling errors
	#endif
#endif

/*
 *
 */
#ifndef EX_RESTRICT
	#if defined(EX_GNUC)
		#define EX_RESTRICT __restrict
	#else
		#define EX_RESTRICT
	#endif
#endif


/*
 *    ELT shared/dynamic Library file name.
 */
#ifdef EX_DEBUG
#   ifdef EX_WINDOWS
#       define EX_LIBRARY_NAME "libEngineEx.dll"
#   elif defined(EX_UNIX)
#       define EX_LIBRARY_NAME "libEngineExD.so"
#   endif
#else
#   if defined(EX_WINDOWS)
#       define EX_LIBRARY_NAME "libEngineEx.dll"
#   elif defined(EX_UNIX)
#       define EX_LIBRARY_NAME "libEngineEx.so"
#   endif
#endif


/*
 *	ELT Version.
 */
#define EX_ENGINE EX_TEXT("Engine Library Toolkit")


/*
 *
 */
#ifndef EX_VERSION_MAJOR
	#ifdef MAJOR_VERSION
		#define EX_VERSION_MAJOR MAJOR_VERSION
	#else
		#define EX_VERSION_MAJOR 0
	#endif
#endif

/*
 *
 */
#ifndef EX_VERSION_MINOR
	#ifdef MINOR_VERSION
		#define EX_VERSION_MINOR MINOR_VERSION
	#else
		#define EX_VERSION_MINOR 6
	#endif
#endif

/*
 *
 */
#ifndef EX_VERSION_REVISION
	#ifdef REVISION_VERSION
		#define	EX_VERSION_REVISION REVISION_VERSION
	#else
		#define EX_VERSION_REVISION 11
	#endif
#endif

/*
 *
 */
#define EX_ENGINE_PREALPHA EX_TEXT("pa")	        /* Pre alpha    */
#define EX_ENGINE_ALPHA EX_TEXT("a")		        /* Alpha        */
#define EX_ENGINE_BETA EX_TEXT("b")		       	    /* Beta         */
#define EX_ENGINE_STABLE EX_TEXT("r")		        /* Stable       */
#define EX_ENGINE_RELEASE_SOMETHING EX_TEXT("rc")	/*              */
#define EX_ENGINE_RELEASE_BETTER EX_TEXT("rc5")		/*          */

/*
 *	ELT Version [8 bit major | 8 bit minor | 8 bit bug fix | 8 bit reserved ]
 */
#define EX_ENGINE_VERSION ( (EX_VERSION_MAJOR << 16) | (EX_VERSION_MINOR << 8) | (EX_VERSION_REVISION << 0) )

#if defined(EX_MSVC) && defined(EX_INTERNAL_DEVELOP_ENVIROMENT)
	#pragma comment(linker,"/VERSION:"STR(EX_VERSION_MAJOR)"[."STR(EX_VERSION_MINOR)STR(EX_VERSION_REVISION)"]")
#endif

/*
 *	ELT library status.
 */
#ifdef EX_DEBUG
	#define EX_ENGINE_STATUS EX_ENGINE_PREALPHA
#else
	#define EX_ENGINE_STATUS EX_ENGINE_PREALPHA
#endif

/*
 *	Information
 */
#define EX_ENGINE_COMPILER_ARCHITECTURE
#define EX_ENGINE_BUILT_DATA __DATE__
#define EX_ENGINE_BUILT_TIME __TIME__


/*
 *	All IDE don't enable NDEBUG || _DEBUG by default. Has to be predefined explicitly if not defined.
 */
#if (NDEBUG || _DEBUG)
	#if !(defined NDEBUG ^ defined _DEBUG)
		#error Exactly one of NDEBUG and _DEBUG needs to be defined by preprocessor
	#endif
#endif

/*
 *	variable argument list.
 */
#ifdef EX_MSVC
	#define EX_VA_ARGS __VA_ARGS__
#elif defined(EX_GNUC)
	#define EX_VA_ARGS __VA_ARGS__
#else
	#define EX_ARGS ...
#endif


/*
 *	Disable some useless and tedious compiler warning
 *	for visual studios C++ compiler.
 */
#ifdef EX_MSVC
	/*	ignoring some tedious useless warnings from Windows.*/
	#define WIN32_LEAN_AND_MEAN

	// Turn off warnings generated by long std templates
	// This warns about truncation to 255 characters in debug/browse info
	#   pragma warning (disable : 4786)
	// Turn off warnings generated by long std templates
	// This warns about truncation to 255 characters in debug/browse info
	#   pragma warning (disable : 4503)
	// disable: "<type> needs to have dll-interface to be used by clients'
	// Happens on STL member variables which are not public therefore is ok
	#   pragma warning (disable : 4251)
	// disable: "non dll-interface class used as base for dll-interface class"
	// Happens when deriving from Singleton because bug in compiler ignores
	// template export
	#   pragma warning (disable : 4275)
	// disable: "C++ Exception Specification ignored"
	// This is because MSVC 6 did not implement all the C++ exception
	// specifications in the ANSI C++ draft.
	#   pragma warning( disable : 4290 )
	// disable: "no suitable definition provided for explicit template
	// instantiation request" Occurs in VC7 for no justifiable reason on all
	// #includes of Singleton
	#   pragma warning( disable: 4661)
	// disable: deprecation warnings when using CRT calls in VC8
	// These show up on all C runtime lib code in VC8, disable since they clutter
	// the warnings with things we may not be able to do anything about (e.g.
	// generated code from nvparse etc). I doubt very much that these calls
	// will ever be actually removed from VC anyway, it would break too much code.
	#   pragma warning( disable: 4996)
	// disable: "conditional expression constant", always occurs on
	// OGRE_MUTEX_CONDITIONAL when no threading enabled
	#   pragma warning (disable : 201)
	// disable: "unreferenced formal parameter"
	// Many versions of VC have bugs which generate this error in cases where they shouldn't
	#   pragma warning (disable : 4100)
#endif

#endif
