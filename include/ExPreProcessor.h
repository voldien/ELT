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
#ifndef _EX_PRE_PROCESSOR_H_
#define _EX_PRE_PROCESSOR_H_ 1
#include<stddef.h>
#include<stdint.h>

#ifdef __cplusplus
	#include<cstdio>
	#include<climits>
	#define EX_CPP	// C++ environment
#else
	#include<stdio.h>
	#include<limits.h>
	#define EX_C	// C environment
#endif
/*	khr group	*/
#include<KHR/khrplatform.h>


/*
    Compiler
*/
#ifdef _MSC_VER 	/*	Visual Studio C++ Compiler.	*/
	#define EX_VC
	#define ENGINE_EX_COMPILER 1
	#if _MSC_VER >= 1900
		#define EX_V13 _MSC_VER
	#elif _MSC_VER >= 1800
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

#elif defined(__clang__)  || defined(__llvm__)           /*  LLVM    */
    #define EX_LLVM 1
	#define EX_CLANG 1
	#define ENGINE_EX_COMPILER 5
	#define EX_COMPILER_NAME "LLVM"

#elif defined(__GNUC__) || defined(__SNC__) || defined( __GNUC_MINOR__)	/*  GNU C Compiler*/
	#define EX_GNUC
	#define ENGINE_EX_COMPILER 2
	#define EX_COMPILER_NAME "GNU C"

#elif defined(__GNUG__) /*  GNU C++ Compiler*/
	#define EX_GNUC 1

#elif defined(__ghs__)		// GHS
	#define EX_GHS
	#define ENGINE_EX_COMPILER 3

#elif defined(__HP_cc) || defined(__HP_aCC)

#elif defined(__PGI)

#elif defined(__ICC) || defined(__INTEL_COMPILER) /*  Intel Compiler  */
	#define EX_INTEL
	#define ENGINE_EX_COMPILER 4
	#define EX_COMPILER_NAME "Intel C++"

#elif defined(__SUNPRO_C) || defined(__SUNPRO_CC)

#else
	#error UnSupported Compiler.
#endif



/**
	//  Platform define
	//  Architecture!
*/
#ifdef EX_VC
	#if defined(_M_IX86) || defined(_WIN32)
		#define EX_X86                          /**/
		#define EX_X32                          /**/
		#define EX_WIN32                        /**/
		#define EX_WINDOWS                      /**/
		#define EX_BITS_ARCHITECTURE 32         /**/
	#elif defined(_M_X64) || defined(_WIN64)
		#define EX_X64                          /**/
		#define EX_WIN64                        /**/
		#define EX_WINDOWS                      /**/
		#define EX_BITS_ARCHITECTURE 64         /**/
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
        #define EX_PSP2                         /*	playstation portable 2*/
        #define EX_RAS_PI                       /*	rasberry pi	*/
	#endif
	#if defined(_WIN32) /**  Window*/
		#define EX_WINDOWS                      /**/
		#define EX_BITS_ARCHITECTURE 32         /**/
	#endif
	#if ( defined(__linux__) || defined(__linux) || defined(linux) ) && (!(__ANDROID__) || !(ANDROID))/* Linux */
		#define EX_LINUX 1                       /**/
		#if defined(__amd64) || defined(__x86_64__) || defined(__i386__)
            #define EX_X86 1
		#endif
		#if defined(__arm__)
              #define EX_ARM 1
        #endif

	#elif defined (ANDROID) || defined(__ANDROID__) || __ANDROID_API__ > 9  /** Android */
        #include<jni.h>
		#define EX_ANDROID 1
		/*  android Architecture*/
        #if defined(__arm__)
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
	#elif defined(__CYGWIN) 	/**/
		#define EX_CYGWIN 1
		#define EX_LINUX 1
	#elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__)   /*  BSD*/
		#define EX_BSD
    	#elif defined(__llvm__) || defined(__clang__)   	/*  llvm    */
        	#define EX_LLVM 1
	#endif



	#if defined(__unix__) || defined(__unix) || defined(unix)	/*  Unix    */
        #   define EX_UNIX 1
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



/*
    C Compiler Version
*/
#if (__STDC_VERSION__ == 201112L)
#   define EX_C11
#elif (__STDC_VERSION == 199901L)
#   define EX_C99
#elif defined(__STDC__)
#   define EX_C90
#endif

/*
    macro definition of Release and Debug  build
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
#endif

/*	convert to string in preprocessing */
#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

/*
    Unicode
*/
#ifdef UNICODE  /*  UTF-16*/
	#define EX_UNICODE
	#define _EX_TEXT(quote) L##quote
	#define EX_TEXT(quote)  _EX_TEXT(quote)
#else           /*  ASCI / UTF-8 */
	#define EX_ANSI
    #define EX_TEXT(quote) quote
#endif



/*
    declaration specification
*/
#if !defined(ENGINE_EX_STATIC_BUILD)
	#if defined(EX_WINDOWS) || defined(EX_VC)                 /**     Window      */
		#define EX_IMPORT __declspec(dllimport)
		#define EX_EXPORT __declspec(dllexport)
	#elif defined(EX_LINUX)                 /**     Linux       */
		#define EX_IMPORT	__attribute__ ((__visibility__ ("default")))
		#define EX_EXPORT	__attribute__ ((__visibility__ ("default")))
	#elif defined(EX_ANDROID)               /**      Android     */
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
		#define EX_IMPORT
		#define EX_EXPORT
	#endif
#endif

/*
    Reserved keyword
*/
#define EX_EXTERN extern
#define C_EXTERN extern "C"
#define CPP_EXTERN extern "C++"
#define VIRTUAL virtual
#define NORETURN __declspec(noreturn)				// No Return, will loop forever.

/**
	No Initialization Virtual Table. [4 byte In size] //TODO confirm size of virtual table
	only supports in C++ environments
*/
#ifdef EX_WINDOWS
	#define NOINITVTABLE __declspec(novtable)
#else
	#define NOINITVTABLE
#endif


/*
        Virtual table size
*/
#ifdef __cplusplus   // C++ feature
	#define EX_VIRTUAL_VTAB_SIZE(x)
#else
	#define EX_VIRTUAL_VTAB_SIZE(x) EX_UNUSED(x)
#endif

/*
	No Throw
*/
#ifdef EX_VC
	#define NOTHROW __declspec(nothrow)						// No Throw
#else
	#define NOTHROW
#endif



/*
	Internal
*/
#if defined(_ENGINE_INTERNAL) || (EX_ENGINE_VERSION_MAJOR < 1)	// Macro Definition Only Defined in this solution.
	#define INTERNAL_ENGINEX	// Used for Assembly Data and Include Data structure.
	#define EX_INTERNAL_DEVELOP_ENVIROMENT
#elif defined(EXTERNAL_ENGINE_INTERNAL)
	#define INTERNAL_ENGINEX	// Used for Assembly Data and Include Data structure.
	#define EX_INTERNAL_DEVELOP_ENVIROMENT
#endif

#if (!defined(ENGINE_EX_STATICLIB) && !defined(ENGINE_EX_STATICLIB))
#ifndef ENGINE_EX_LIB
	#define ENGINE_EX_LIB
#endif
#endif

/**
	Calling Convention
*/
#ifdef EX_WINDOWS	        /** Windows Calling Convention.*/
	#define ELTAPIENTRY     __cdecl
	#define ELTAPIFASTENTRY __fastcall
	#define ELTAPITHISENTRY __thiscall
	#define ELTAPISTDENTRY  __stdcall
#elif defined(EX_ANDROID)   /** Android Calling Convention*/
    #define ELTAPIENTRY JNICALL
    #define ELTAPIFASTENTRY JNICALL
    #define ELTAPITHISENTRY JNICALL
    #define ELTAPISTDENTRY JNICALL
#else
#   ifndef __cdecl
        #define __cdecl  __attribute__ ((__cdecl__))
#   endif
	#define ELTAPIENTRY     //__cdecl
	#define ELTAPISTDENTRY  //__cdecl
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

/**
    inline
*/
#if defined(EX_VC)
	#define INLINE inline
	#pragma inline_depth(255)
#else
	#define INLINE inline
#endif

/**
    force inline
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

/**
	No inline
*/
#if defined EX_WINDOWS || defined EX_XBOX
	#define EX_NOINLINE __declspec(noinline)
#elif defined(EX_GNUC)  || defined(EX_GHS)
	#define EX_NOINLINE __attribute__ ((oninline))
#else
	#define EX_NOINLINE
#endif


/**
	#define EXDEPRECATED(x) __declspec(deprecated(x))		// Deprecated deceleration (x = Warning Message)
*/
#ifdef EX_VC
	#define EXDEPRECATED  __declspec(deprecated)		    // Deprecated deceleration (x = Warning Message)
	#define EXDEPRECATEDMESSAGE(x) __declspec(deprecated(x))
#elif defined(EX_GNUC)
	#define EXDEPRECATED __attribute__(( deprecated ))		    // Deprecated deceleration (x = Warning Message)
    	#define EXDEPRECATEDMESSAGE(msg) __attribute__ (( deprecated ( msg ) ))
#endif

/**
	Alignment of data
*/
#ifndef EX_ALIGN
	#if defined(EX_VC)
		#define EX_ALIGN(alignment, decl) __declspec(align(alignment)) decl
		#define EX_ALIGN_PREFIX(alignment) __declspec(align(alignment))
	#elif defined(EX_GNUC)
		#define EX_ALIGN(alignment, decl) decl __attribute__ ((aligned(alignment)))
		#define EX_ALIGN_PREFIX(alignment) __attribute__ ((aligned(alignment)))
	#elif defined(EX_CLANG)
		#define EX_ALIGN(alignment, decl) decl __attribute__ ((aligned(alignment)))
		#define EX_ALIGN_PREFIX(alignment) __attribute__ ((aligned(alignment)))
	#else
		#define EX_ALIGN(alignment, decl)
		#define EX_ALIGN_PREFIX(alignment)
	#endif
#endif

#if defined(_DLL)
	#define EX_DLL _DLL
#endif

/**
	Function and other predefined macro
*/
#if defined(EX_VC)
	#define EX_FUNCNAME __FUNCTION__
	#define EX_FUNCSIG __FUNCSIG__
	#define EX_FUNCDNAME __FUNCDNAME__
	#define __EX_FILE__ __FILE__
	#define __EX_LINE__ __LINE__
#else
	#define EX_FUNCNAME  __FUNCTION__
	#define EX_FUNCSIG   __FUNCSIG__
	#define EX_FUNCDNAME ""
	#define __EX_FILE__ __FILE__
	#define __EX_LINE__ __LINE__

#endif

/**
	Int max bits size supported by compiler or hardware
*/
#if defined(EX_VC)
	#define EX_INT_MAX_BITS _INTEGRAL_MAX_BITS
#elif defined(EX_GNUC)
	#define EX_INT_MAX_BITS _INTEGRAL_MAX_BITS
#endif
/**
	Unused indication. // will make the compiler exclude it from the final binary.
*/
#define EX_UNUSED(_p)	((void)(_p))


#ifndef APPLICATIONTYPE
#if defined(NSCREENSAVER)
	#define APPLICATIONTYPE SCREENSAVER
#else
	#define APPLICATIONTYPE GAME
#endif
#endif

/**
	Rendering Software Interface.
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

/**
	C struct
*/
#ifdef EX_CPP
	#define EX_C_STRUCT
#else
	#define EX_C_STRUCT struct
#endif


/**
	Assembly instruction identification
*/
#if defined(EX_VC)
	#define EX_ASSM __asm
#elif defined(EX_GNUC)
	#define EX_ASSM __asm__
#elif defined(EX_CLANG)
	#define EX_ASSM asm
#endif

/**
    Export & Import of DLL
*/
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


/**
    ELT Library file name.
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


/**
	ELT Version.
*/
#define EX_ENGINE   "Engine Library Toolkit"

#ifndef EX_VERSION_MAJOR
	#define EX_VERSION_MAJOR 0
#endif
#ifndef EX_VERSION_MINOR
	#define EX_VERSION_MINOR 6
#endif
#ifndef EX_VERSION_REVISION
	#define EX_VERSION_REVISION 11
#endif

#define EX_ENGINE_PREALPHA EX_TEXT("pa")	        /* Pre alpha    */
#define EX_ENGINE_ALPHA EX_TEXT("a")		        /* Alpha        */
#define EX_ENGINE_BETA EX_TEXT("b")		       	    /* Beta         */
#define EX_ENGINE_STABLE EX_TEXT("r")		        /* Stable       */
#define EX_ENGINE_RELEASE_SOMETHING EX_TEXT("rc")	/*              */
#define EX_ENGINE_RELEASE_BETTER EX_TEXT("rc5")		/*          */

/*
	ELT Version [8 bit major | 8 bit minor | 8 bit bugfix | 8 bit reserved ]
*/
#define EX_ENGINE_VERSION ( (EX_VERSION_MAJOR << 16) | (EX_VERSION_MINOR << 8) | (EX_VERSION_REVISION << 0) )

#if defined(EX_VC) && defined(EX_INTERNAL_DEVELOP_ENVIROMENT)
	#pragma comment(linker,"/VERSION:"STR(EX_VERSION_MAJOR)"[."STR(EX_VERSION_MINOR)STR(EX_VERSION_REVISION)"]")
#endif

/*
    ELT status
*/
#ifdef EX_DEBUG
	#define EX_ENGINE_STATUS EX_ENGINE_PREALPHA
#else
	#define EX_ENGINE_STATUS EX_ENGINE_PREALPHA
#endif

/*
	Information
*/
#define EX_ENGINE_COMPILER_ARCHITECTURE
#define EX_ENGINE_BUILT_DATA __DATE__
#define EX_ENGINE_BUILT_TIME __TIME__


/*
    all IDE don't enable NDEBUG || _DEBUG by default. Has be predefined explicitly if not defined.
*/
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


#ifdef EX_VC
	#define WIN32_LEAN_AND_MEAN	    /**	ignoring some tedious useless warnings from window.*/
#endif




#ifdef INTERNAL_ENGINEX
	#ifdef EX_VC
		#pragma warning(disable : 4996)		// Disable a warning
		#pragma warning(disable : 4251) 	// Dll
	#endif
#endif

#endif
