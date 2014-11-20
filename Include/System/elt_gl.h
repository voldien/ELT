/*
===========================================================================
Copyright (C) 2014 BroodCity Software, Inc. Voldemor2009@hotmail.com

*/
#ifndef ELT_GL_H
#define ELT_GL_H
#include"./../ExPreProcessor.h"
#ifdef EX_INTERNAL_DEVELOP_ENVIROMENT
	#ifndef GLEW_STATIC
		#ifndef EX_DLL
			#define GLEW_STATIC
		#endif
	#endif
#endif

#include<GL/glew.h>
#ifdef EX_WINDOWS

	#include<GL/wglew.h>
	#define ExSwapBuffers SwapBuffers
#elif defined(EX_LINUX)
	#include<GL/glxew.h>
	#define ExSwapBuffers(window) glXSwapBuffers(display,window)
#elif defined(EX_MAC)
	#define ExSwapBuffers glSwapBuffers
#elif defined(EX_ANDROID)
	#ifdef GL_ES_VERSION_2_0
		#include<GLES/gl2.h>
		#include<GLES/gl2ext.h>
		#include<GLES/gl2platform.h>
	#endif
	#define ExSwapBuffers eglSwapBuffers
#endif
/*
	// default opengl includer
*/


#if defined(EX_WINDOWS)
	#include"Win32/win_win32.h"
#elif defined(EX_LINUX)
	#include"Unix/unix_win.h"
#elif defined(EX_MAC)
	#include"Mac/macosx_win.h"
#elif defined(EX_ANDROID)

#endif
#include"elt_win.h"

#ifdef __cplusplus	//	C++ Env
extern "C"{
#endif
/*
	//	Get Window assoicated with OpenGL Context
*/
extern DECLSPEC ExWin ELTAPIENTRY ExGetOpenGLContextWindow(OpenGLContext glc);
/*
	//	Get Device Context Of Current 
*/
extern DECLSPEC WindowContext ELTAPIFASTENTRY ExGetCurrentGLDC(void);
/*
	//	Get OpenGL Context on the current Thread
*/
extern DECLSPEC OpenGLContext ELTAPIFASTENTRY ExGetCurrentOpenGLContext(void);
/*
	// Get OpenGL Context from window
*/
extern DECLSPEC OpenGLContext ELTAPIENTRY ExGetOpenGLCFromWindow(ExWin window);

/*
	// make current
*/
extern DECLSPEC void ELTAPIENTRY ExMakeGLCurrent(WindowContext hDC, OpenGLContext glc);

/*
	// Specif initlize of specific hardware.
*/
extern DECLSPEC ERESULT ELTAPIENTRY ExInitGLAMDExtension(OpenGLContext hrc);
/*
*/
extern DECLSPEC ERESULT ELTAPIENTRY ExInitIntelExtension(OpenGLContext hrc);
/*

*/
extern DECLSPEC ERESULT ELTAPIENTRY ExInitNVExtension(OpenGLContext hrc);

/*
 Create Context Attribute Based on Internal Hardward and engine description.
*/
extern DECLSPEC void ELTAPIENTRY ExCreateContextAttrib(WindowContext hDC,Int32* attrib,Int32* size,EngineDescription* engineDesc,Enum EnumRI);

extern DECLSPEC OpenGLContext ELTAPIENTRY ExCreateGLContext(ExWin window);
/*
	//
*/
extern DECLSPEC OpenGLContext ELTAPIENTRY ExCreateContext(ExWin window,const void *pPFD);
/*
	// Initilize OpenGL States
*/
extern DECLSPEC void ELTAPIENTRY ExInitOpenGLStates(EngineDescription* enginedescription);

/*
	// Destroy OpenGL Context
*/
extern DECLSPEC Boolean ELTAPIENTRY ExDestroyContext(WindowContext hDc, OpenGLContext glc);

/*
	// Destroy and release current Opengl Context attached to curent Thread
*/
extern DECLSPEC Boolean ELTAPIENTRY ExDestroyCurrentContext(void);

/*
	// Initlize OpenGL 
*/
extern DECLSPEC void ELTAPIENTRY ExInitOpenGL(ExWin hwnd, EngineDescription* enginedescription);
/*
	// FullScreen opengl window
*/
extern DECLSPEC Boolean ELTAPIENTRY ExGLFullScreen(Boolean cdsfullscreen, ExWin window, Uint32 screenIndex, const Int* screenRes);


#define EX_GLTRANSPARENT_ENABLE 0x1
#define EX_GLTRANSPARENT_DISABLE 0x0
#define EX_GLTRANSPARENT_FULLBLUR 0x2

/*
// Set OpenGL Transparent.
// remark:
// you'll need to use glClear or from pixel shader alpha channel to see effect
// glClearColor 
// read more about DwmEnableBlurBehindWindow : http://msdn.microsoft.com/en-us/library/windows/desktop/aa969508(v=vs.85).aspx
*/
extern DECLSPEC void ELTAPIENTRY ExSetGLTransparent(ExWin hWnd,Enum ienum);

/*
	//	Get Hardware OpenGL shading Version
*/
extern DECLSPEC Uint32 ELTAPIFASTENTRY ExGetOpenGLShadingVersion(void);
/*
	// Get OpenGL Version
*/
extern DECLSPEC Uint32 ELTAPIFASTENTRY ExGetOpenGLVersion(void);

/*
	// check if graphic card is AMD GPU
*/
extern DECLSPEC Boolean ELTAPIENTRY ExIsVendorAMD(void);
/*
	// check if graphic card is Nvidia GPU	
*/
extern DECLSPEC Boolean ELTAPIENTRY ExIsVendorNvidia(void);
/*
	// check if graphic card is Intel GPU
*/
extern DECLSPEC Boolean ELTAPIENTRY ExIsVendorIntel(void);


#ifdef  __cplusplus	// C++ Environment
}
#endif
#include"elt_win.h"
#endif
