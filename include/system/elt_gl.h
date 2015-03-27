/*
========================================================================
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
#ifndef _ELT_GL_H_
#define _ELT_GL_H_ 1
#include"./../ExPreProcessor.h"

#ifdef EX_WINDOWS
	#define ExSwapBuffers SwapBuffers
#elif defined(EX_LINUX)
	#define ExSwapBuffers(window) glXSwapBuffers(display,window)
#elif defined(EX_MAC)
	#define ExSwapBuffers glSwapBuffers
#elif defined(EX_ANDROID)
	#define ExSwapBuffers(surface) eglSwapBuffers(eglGetDisplay(EGL_DEFAULT_DISPLAY),surface)
#endif
/**
	default opengl includer
*/
#if defined(EX_WINDOWS)
	#include<Windows.h>
	#include"win/win_win32.h"
#elif defined(EX_LINUX)
	#include"unix/unix_win.h"
#elif defined(EX_MAC)
	#include"mac/macosx_win.h"
#elif defined(EX_ANDROID)

#endif
#include"elt_win.h"



/**
    GPU Vendors constant of.
*/
#define EX_GPU_UNKNOWN 0x0
#define EX_GPU_NVIDIA 0x1
#define EX_GPU_INTEL 0x2
#define EX_GPU_AMD 0x4


#ifdef __cplusplus	//	C++ Environment
extern "C"{
#endif


/**
	Get Window associated with OpenGL Context
*/
extern DECLSPEC ExWin ELTAPIENTRY ExGetOpenGLContextWindow(OpenGLContext glc);
/**
	Get device context of current openGL context on current thread
*/
extern DECLSPEC WindowContext ELTAPIFASTENTRY ExGetCurrentGLDC(void);
#define ExGetCurrentGLDrawable ExGetCurrentGLDC
/**
	Get OpenGL context on the current thread
*/
extern DECLSPEC OpenGLContext ELTAPIFASTENTRY ExGetCurrentOpenGLContext(void);
/**
	Get OpenGL context from given window.
*/
extern DECLSPEC OpenGLContext ELTAPIENTRY ExGetOpenGLCFromWindow(ExWin window);

/**
	Make current OpenGL context.
*/
extern DECLSPEC void ELTAPIENTRY ExMakeGLCurrent(WindowContext hDC, OpenGLContext glc);

/**
    Create Context Attribute Based on Internal Hardware and engine description.
*/
extern DECLSPEC void ELTAPIENTRY ExCreateContextAttrib(WindowContext hDC,Int32* attrib,Int32* size,EngineDescription* engineDesc,Enum EnumRI);
/**
    Create OpenGL context for given window
*/
extern DECLSPEC OpenGLContext ELTAPIENTRY ExCreateGLContext(ExWin window);
/**
    Create Shared OpenGL Context from a already existing context.
*/
extern DECLSPEC OpenGLContext ELTAPIENTRY ExCreateGLSharedContext(ExWin window, OpenGLContext context);

/*
	// Initialize OpenGL States
*/
extern DECLSPEC void ELTAPIENTRY ExInitOpenGLStates(EngineDescription* enginedescription);

/**
	Destroy OpenGL Context
*/
extern DECLSPEC ExBoolean ELTAPIENTRY ExDestroyContext(WindowContext drawable, OpenGLContext glc);

/**
	Destroy and release current OpenGL Context attached to current thread
*/
extern DECLSPEC ExBoolean ELTAPIENTRY ExDestroyCurrentContext(void);



/*
	// Initlize OpenGL
*/
extern DECLSPEC void ELTAPIENTRY ExInitOpenGL(ExWin hwnd, EngineDescription* enginedescription);
/**
	Set Window associated with OpenGL context fullScreen.
*/
extern DECLSPEC ExBoolean ELTAPIENTRY ExGLFullScreen(ExBoolean cdsfullscreen, ExWin window, Uint32 screenIndex, const Int* screenRes);


#define EX_GLTRANSPARENT_ENABLE 0x1
#define EX_GLTRANSPARENT_DISABLE 0x0
#define EX_GLTRANSPARENT_FULLBLUR 0x2

/**
//  Set OpenGL Transparent.
//  remark:
//  you'll need to use glClear or from pixel shader alpha channel to see effect
//  glClearColor
//  ExSetHint(EX_ALPHA, x > 0);
//  read more about DwmEnableBlurBehindWindow : http://msdn.microsoft.com/en-us/library/windows/desktop/aa969508(v=vs.85).aspx
*/
extern DECLSPEC void ELTAPIENTRY ExSetGLTransparent(ExWin hWnd,Enum ienum);

/**
	Get Hardware OpenGL shading Version
*/
extern DECLSPEC Uint32 ELTAPIFASTENTRY ExGetOpenGLShadingVersion(void);
/**
	Get OpenGL Version
*/
extern DECLSPEC Uint32 ELTAPIFASTENTRY ExGetOpenGLVersion(void);

/**
	Check if graphic card is AMD GPU
*/
extern DECLSPEC Int32 ELTAPIENTRY ExIsVendorAMD(void);
/**
	Check if graphic card is Nvidia GPU
*/
extern DECLSPEC Int32 ELTAPIENTRY ExIsVendorNvidia(void);
/**
	Check if graphic card is Intel GPU
*/
extern DECLSPEC Int32 ELTAPIENTRY ExIsVendorIntel(void);
/**
    Get graphic vendor enumerator
*/
extern DECLSPEC Enum ELTAPIENTRY ExGetGLVendorEnum(void);


#ifdef  __cplusplus	// C++ Environment
}
#endif
#include"elt_win.h"
#endif
