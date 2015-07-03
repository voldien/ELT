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
#ifndef _ENGINE_ASSEMBLY_H_
#define _ENGINE_ASSEMBLY_H_ 1

#include"ExPreProcessor.h"
#include"ExNT.h"
#include"system/elt_event.h"
#include"EngineEx.h"
#include"ExCommon.h"
#if defined(EX_WINDOWS)
	#pragma warning(disable : 4480) // enum
	#pragma warning(disable : 4995) // deprecated
	#include<tchar.h>
	#ifdef EX_VC
		#include<strsafe.h>
	#endif
#elif defined(EX_LINUX)
#elif defined(EX_PNACL)
#	include<ppapi/c/ppb.h>
#elif defined(EX_ANDROID)
#   include<android/api-level.h>
#elif defined(EX_MAC)
#endif

/**
		Type
*/
#ifdef __cplusplus //	C++	Environment
	#define TYPE(x) typeid(x)
	#define TYPEX(x) TypeEx(typeid(x),sizeof(x))
	#define TYPEMI(vertex,indices) //MeshInstruction(TYPEX(vertex),TYPEX(indices))
	#define TYPE_EQUAL(x,y) ( (typeid( ( x ) ) == typeid( ( y ) )) ? TRUE : FALSE )
	#define TYPEX_EQUAL(x,y)
	#define TYPEBASE(current,base) typeid(current).before(base)
	#define TYPENAME(x) typeid(x).name()
#else
	#define TYPE(x)	EX_UNUSED(x)
	#define TYPEX(x)	EX_UNUSED(x)
	#define TYPEMI(x)	EX_UNUSED(x)
	#define TYPE_EQUAL(x,y)	EX_UNUSED(x)
	#define TYPEX_EQUAL(x,y)	EX_UNUSED(x)
	#define TYPEBASE(x,y) EX_UNUSED(x)
	#define TYPENAME(x) EX_UNUSED(x)
#endif

#ifdef EX_CPP
	#define CASTP(type,y) reinterpret_cast<type>( ( y ) )
	#define CAST(type,y) static_cast<type>( ( y ) )
	#define CASTD(type,y) dynamic_cast<type>( ( y ) )
#else
	#define CASTP(type, y) (type)( ( y ) )
	#define CAST(type,y) (type)( ( y ) )
	#define CASTD(type,y) (type)( ( y ) )
#endif

/**
    pixel mode
*/
#define ENGINE_ALPHA 0x1UL
#define ENGINE_RGB 0x2UL
#define ENGINE_RGBA (ENGINE_RGB | ENGINE_ALPHA)
#define ENGINE_INDEX 0x8UL



// Engine Rendering Flags
#define ENGINE_NATIVE (1 << 7)
#define EX_OPENGL (1 << 8)
#define EX_OPENGLES (1 << 9)
#define EX_OPENCL  (1 << 10)
#define EX_DIRECTX  (1 << 11)
#define EX_OPENGL_AND_OPENCL (ENGINE_OPENGL | ENGINE_OPENCL)
#define EX_RENDER_CONTEXT_DEBUG (1 << 12)

#define ELT_OPENGL ENGINE_OPENGL
#define ELT_OPENCL ENGINE_OPENCL
#define ELT_OPENGL_ES ENGINE_OPENGL_ES
#define ELT_DIRECTX ENGINE_DIRECTX
#define ELT_OPENGL_AND_OPENGL (ENGINE_OPENGL | ENGINE_OPENCL)


/**
	// high layer flag
*/
#define ELT_INIT_TIMER			0x00000001
#define ELT_INIT_VIDEO			0x00000020
#define ELT_INIT_AUDIO			0x00000010
#define ELT_INIT_JOYSTICK		0x00000200
#define ELT_INIT_EVENTS			0x00002000
#define ELT_INIT_GAMECONTROLLER 0x00004000
#define ELT_INIT_NET			0x00008000
#define ELT_INIT_EVERYTHING (							\
	ELT_INIT_VIDEO | ELT_INIT_AUDIO | ELT_INIT_JOYSTICK	\
 | ELT_INIT_TIMER | ELT_INIT_GAMECONTROLLER | ELT_INIT_EVENTS)


#ifdef __cplusplus	 // C++ environment
extern "C"{
#endif
//---- End Engine Description flag.
typedef struct EngineFormatDescription{
	Uint64 EngineFlag;		// Engine Flag Stats
	Uint32 SampleQuality;	// Sample Quallity Flag Stats
	Uint8 sample[4];        //
	Uint32 BufferCount;		// Number of Buffer Drawn To Window
	Uint32 BufferFlag;		// Buffer Flag Statment
	Uint32 AffinityCount;	// Number Core To Drive The Engine
	Uint32 nVersion;		// Specified Version. for furture release for compadiable
	Uint8 DepthBits;		// Bits Count In Depth Buffer	[if 0 == disable depth test]
	Uint8 ColorBits;		// Bits Count In Color Buffer
	Uint8 StencilBits;		// Bits Count In Stencil Buffer [if 0 == disable stencil Test]
	Uint8 AccumBits;		// Bits Count In Accum Buffer [if 0  == disable accum test]
	Uint8 alphaChannel;		// Bits Count on Alpha Buffer [if 0 == disable Alpha]
	Uint8 PixelType;		// Pixel Type
}EngineDescription, *PENGINEDESCRIPTION,ExEngineDescription, ExEngineDesc;

/**
    Allocation of This Application EngineDescription. Describe the base of the Application.
*/
extern DECLSPEC EngineDescription engineDescription;
/**
    \Set Hint
*/
extern DECLSPEC void ELTAPIENTRY ExSetHint(Enum e_enum, int value);
/**
    \Get Hint
    @return
*/
extern DECLSPEC int ELTAPIENTRY ExGetHint(Enum e_enum);
/**
    Set parameter
    @return
*/
extern DECLSPEC int ELTAPIENTRY ExSetParameteri(Enum eflag, int value);
/**
    Set parameter
    @return
*/
extern DECLSPEC int ELTAPIENTRY ExSetParameterf(Enum eflag, float value);

#define EX_OPENGL_
extern DECLSPEC int ExGeti(Enum Flag);

//extern DECLSPEC int ELTAPIENTRY ExSetCallback(Enum callbackflag, void (*s) (unsigned int) callback);


extern DECLSPEC void ELTAPIENTRY AssignDescription(const EngineDescription* p_engineDescription);

/**
    Get ELT Window default Title!
*/
extern DECLSPEC ExChar* ELTAPIENTRY ExGetDefaultWindowTitle(ExChar* text, int length);


#ifdef __cplusplus
}
#endif
#include"elt_timer.h"
#include"system/elt_win.h"
#include"system/elt_errorhandler.h"
#include"system/elt_event.h"
#include"system/elt_net.h"
#include"elt_loadso.h"
#include"input/elt_keyboard.h"
#include"input/elt_mouse.h"
#include"input/elt_joystick.h"
#include"elt_cpuinfo.h"
#include"system/elt_gl.h"
#include"elt_timer.h"
#include"elt_alloc.h"
#include"math/matrix.h"
#include"system/android/elt_activity.h"
#endif
