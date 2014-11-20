/*
===========================================================================
Copyright (C) 2014 BroodCity Software, Inc. Voldemor2009@hotmail.com

*/
#ifndef ENGINE_ASSEMBLY_DEFINITION
#define ENGINE_ASSEMBLY_DEFINITION

#include"ExPreProcessor.h"
#include<Cmd/cmdlib.h>
#include"ExNT.h"
#include"System/elt_event.h"
#include"EngineEx.h"
#include"ExCommon.h"
#include"Input/XBoxControllerHandler.h"
#if defined(EX_WINDOWS)
	#pragma warning(disable : 4480) // enum
	#pragma warning(disable : 4995) // deprecated
	#include<tchar.h>
	#define SIZEOF(type) sizeof(type)
	#ifdef EX_VC 
		#include<strsafe.h>
	#endif
#elif defined(EX_LINUX)

#elif defined(EX_ANDROID)

#elif defined(EX_MAC)

#endif
#include<signal.h>
#include<string.h>

#define ENGINEDESCRIPTIONDEFAULT EngineDefaultDescription
#define ENGINEDESCRIPTIONDESKTOP EngineDesktopDescription
#define ENGINEDESCRIPTIONDIRECTX EngineDirectXDescription
#define ENGINEDESCRIPTIONOPENGL EngineOpenGLDescription

#define ENGINEDESCRIPTIONLOWENDCOMPUTER EngineLowEndComputerDescription
#define ENGINEDESCRIPTIONHIEGHENDCOMPUTER EngineHighEndComputerDescription

/*
	// Type
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

enum EngineSupport{
		eUnknown = (0 << 0),
		eFullScreen = (1 << 4),					// FullScreen
		eSingleBuffer = (1 << 5),				// Single Buffer On OpenGL || DirectX 
		eDoubleBuffer = (1 << 6),				// double buffer On OpenGL || DirectX 
		eSteroVision = (1 << 7),				// Stero Vision Buffer On either single or double buffer
		eOpenCL = (1 << 8),
		eNative = (1 << 9),					// Native Window
		eOpenGL =  (1 << 10),					// OpenGL Rendering software Interface
		eDirectX = (1 << 11),					// DirectX rendering software Interface	
		eExtension = (1 << 12),				// Extension [Designed for OpenGL]
		eHardwareAcceleration = (1 << 13),		// use HardWare Acceleration 
		eShareRenderContext = (1 << 14),		// Shared rendering context. [Desgined for OpenGL] becuase rendering context is connected by the Thread.
		eForwardRendering = (1 << 15),			// Forward Rendering buffer System 
		eDefferedRendering = (1 << 16),		// Deffered Rendering buffer System.
		eVertexLitRendering = (1 << 17),		// Vertex Lit Rendering buffer System. 
		eBuiltInMatrix = (1 << 18),			// Built In Matrix
		eVSync = (1 << 19),					// V Sync 
		eInput = (1 << 20),					// Input system. depending on OS system.
		eDebugShell = (1 << 21),				// Debug Shell. will be written to default stream buffer. UNIX
		eDebugProfile = (1 << 22),			// debug Profile Consol
		eConsoleWindow = (1 << 23),			// 
		e32Window = (1 << 24),

		eInputForeGround = (1 << 27),
		eInputBackGround = (1 << 28),

		// eTCP 
		eWindowRender = (1 << 30),			// Create Render Context Onto a Window
#ifdef EX_DEBUG
		ExVideo = (eDoubleBuffer | eInput | eDebugShell | eExtension | e32Window),
		ExDesktop = (0),
#else
		ExVideo  = (eDoubleBuffer |  eInput),
#endif
};

#define ENGINE_ALPHA 0x1UL
#define ENGINE_RGB 0x2UL
#define ENGINE_RGBA (ENGINE_RGB | ENGINE_ALPHA)
#define ENGINE_INDEX 0x8UL

// Engine Rendering Flags
#define ENGINE_UNKNOWN (Uint64)EngineSupport::eUnknown
//#define ENGINE_NATIVE EngineSupport::eNative	//	Use Native Window of Current OS System
//#define ENGINE_OPENGL EngineSupport::eOpenGL	//	Use OpenGL Rendering Interface of Current OS System. [Support Most Platform]
//#define ENGINE_DIRECTX (Uint64)EngineSupport::eDirectX	//	User DirectX Rendering Interface. [Support only Microsoft, As PC-Window]

#define ENGINE_NATIVE (1 << 7)
#define EX_OPENGL (1 << 8)
#define EX_OPENGLES (1 << 9)
#define EX_OPENCL  (1 << 10)
#define EX_DIRECTX  (1 << 11)
#define EX_OPENGL_AND_OPENCL (ENGINE_OPENGL | ENGINE_OPENCL)

#define ELT_OPENGL ENGINE_OPENGL
#define ELT_OPENCL ENGINE_OPENCL
#define ELT_OPENGL_ES ENGINE_OPENGL_ES
#define ELT_DIRECTX ENGINE_DIRECTX
#define ELT_OPENGL_AND_OPENGL (ENGINE_OPENGL | ENGINE_OPENCL)



#define ENGINE_SUPPORT_SINGLEBUFFER (Uint64)eSingleBuffer		//	Use Single Buffer As OutPut Color On Monitor
#define ENGINE_SUPPORT_DOUBLEBUFFER (Uint64)eDoubleBuffer		//	Use Double Buffer AS OutPut Color On Monitor
#define ENGINE_SUPPORT_STEROVISION (Uint64)eSteroVision			//	Use SteroVision. Uses Of 3D Vision Glasses
#define ENGINE_SUPPORT_EXTENSION (Uint64)eExtension				//	Use Rendering Context Extension.
#define ENGINE_SUPPORT_COREFUNCTIONALITY (Uint64)eExtension				//	Use Rendering Context Extension.
#define ENGINE_HARDWARE_ACCELERATION (Uint64)eHardwareAcceleration	//	Use HardWare Acceraltaion for 3D Rendering
#define ENGINE_SHARE_RENDERCONTEXT (Uint64)eShareRenderContext			//	Use Multiable RenderingThread[OPENGL]
#define ENGINE_SUPPORT_EXT_MATRIX (Uint64)eBuiltInMatrix				//	Build In Matrix.
#define ENGINE_SUPPORT_VSYNC (Uint64)eVSync				//	Use VSync [Sync Rendering to Monitor Hz]
//#define ENGINE_SUPPORT_INPUT (Uint64)EngineSupport::eInput				//	Support Input By User on this Application.

#define ENGINE_SUPPORT_DEBUG_SHELL (Uint64)eDebugShell		// Support Debug View Shell.



#define ENGINE_SUPPORT_INPUT_FOREGROUND (Uint64)eInputForeGround	// Input Accessordability. Can be only access on application In Focous.
#define ENGINE_SUPPORT_INPUT_BACKGROUND (Uint64)eInputBackGround	// Input Accessordability Can be access even off fokus on Application.



#define ENGINE_FULLSCREEN (Uint64)EngineSupport::eFullScreen


//#define ENGINE_WINDOW (Uint64)EngineSupport::eWindowRender				//	Create Window To Display Rendering.

/*
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
	Int32 width;			// Screen Width In X Direction Of main Window
	Int32 height;			// Screen Height In Y Direction	Of Main Window
	Uint32 XCoordination;	// Screen X Coordination In X Direcion Of Main Window
	Uint32 YCoordination;	// Screen Y Coordination In Y Direction Of Main Window
	Uint32 FullScreen_Hz;	// Screen Refresh Hz On FullScreen Mode
	Uint32 SampleQuality;	// Sample Quallity Flag Stats
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

/* Allocation of This Application EngineDescription. Describe the base of the Application. */
extern DECLSPEC EngineDescription engineDescription;
extern DECLSPEC void ELTAPIENTRY ExSetHint(Enum e_enum, int value);
extern DECLSPEC int ELTAPIENTRY ExGetHint(Enum e_enum);

extern DECLSPEC void ELTAPIENTRY AssignDescription(const EngineDescription* p_engineDescription);
extern DECLSPEC const Uint64 ELTAPIENTRY ExGetEngineFlag(void);
// Get if bit state of engine description is true or false.
extern DECLSPEC Boolean ELTAPIENTRY ExIsEngineState(const Uint64 engineBitState);
extern DECLSPEC EngineDescription ELTAPIENTRY ExGetEngineDescription(void);
extern DECLSPEC EngineDescription* ELTAPIENTRY ExGetEngineDescriptionPointer(void);

/*
	// Get ELT Window default Title!
*/
extern DECLSPEC ExChar* ELTAPIENTRY ExGetDefaultWindowTitle(ExChar* text, int length);



#define EX_ENGINE_DEVELOPER EX_TEXT("BroodCity Entertainment")

#ifdef __cplusplus
}
#endif
#include"elt_timer.h"
#include"System/elt_win.h"
#include"System/elt_errorhandler.h"
#include"System/elt_event.h"
#include"elt_loadso.h"
#include"Input/elt_keyboard.h"
#include"Input/elt_mouse.h"
#include"Input/elt_joystick.h"
#include"elt_cpuinfo.h"
#include"elt_timer.h"
#include"elt_matrix.h"
#endif
