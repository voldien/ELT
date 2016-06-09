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
#ifndef _ELT_GL_H_
#define _ELT_GL_H_ 1
#include"./../elt_def.h"
#include"elt_egl.h"


/**/
#ifdef EX_WINDOWS
	#define ExSwapBuffers(surface) SwapBuffers(surface)
#elif defined(EX_LINUX)
	#define ExSwapBuffers(window) glXSwapBuffers((Display*)display, (GLXDrawable)window)
#elif defined(EX_MAC)
	#define ExSwapBuffers glSwapBuffers
#elif defined(EX_ANDROID)
	extern ExEGLDisplay eglDisplay;
	#define ExSwapBuffers(surface) eglSwapBuffers((EGLDisplay)eglDisplay, surface)
#else
	extern ELTDECLSPEC void ExSwapBuffers(void* surface);
#endif


/*
 *	GPU Vendors constant of.
 */
#define EX_GPU_VENDOR_UNKNOWN		0x0				/**/
#define EX_NVIDIA					0x1				/**/
#define EX_INTEL					0x2				/**/
#define EX_AMD						0x4				/**/


/*
 *	context attributes.
 */
#define EX_OPENGL_RED_SIZE					0
#define EX_OPENGL_GREEN_SIZE				1
#define EX_OPENGL_BLUE_SIZE					2
#define EX_OPENGL_DEPTH_SIZE				3
#define EX_OPENGL_ALPHA_SIZE				4
#define EX_OPENGL_DOUBLEBUFFER				5
#define EX_OPENGL_STENCIL_SIZE				6
#define EX_OPENGL_ACCUM_RED_SIZE			7
#define EX_OPENGL_ACCUM_GREEN_SIZE			8
#define EX_OPENGL_ACCUM_BLUE_SIZE			9
#define EX_OPENGL_ACCUM_ALPHA_SIZE			10
#define EX_OPENGL_ACCELERATED_VISUAL		11
#define EX_OPENGL_STEREO					12
#define EX_OPENGL_MULTISAMPLEBUFFERS		13
#define EX_OPENGL_MULTISAMPLESAMPLES		14
#define EX_OPENGL_FRAMEBUFFER_SRGB_CAPABLE	15


/*
 *	Context flag attributes.
 */
#define EX_OPENGL_MAJOR_VERSION			17
#define EX_OPENGL_MINOR_VERSION			18
#define EX_OPENGL_CONTEXT_FLAGS			19
#define EX_OPENGL_CONTEXT_PROFILE_MASK	20


/*
 *	Context profile mask flag attributes bit.
 */
#define EX_GL_CONTEXT_PROFILE_CORE           	0x00000001	/*	*/
#define EX_GL_CONTEXT_PROFILE_COMPATIBILITY  	0x00000002	/*	*/
#define EX_GL_CONTEXT_PROFILE_ES             	0x00000004 	/*  */
#define EX_GL_CONTEXT_PROFILE_ES2				0x00000004	/*	*/

/*
 *	Context flag attributes bit.
 */
#define EX_GL_CONTEXT_DEBUG_FLAG              	0x00001		/*	*/
#define EX_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG 	0x00002		/*	*/
#define EX_GL_CONTEXT_ROBUST_ACCESS_FLAG      	0x00004		/*	*/
#define EX_GL_CONTEXT_RESET_ISOLATION_FLAG    	0x00008		/*	*/


#ifdef __cplusplus	/*	C++ environment	*/
extern "C"{
#endif

/**
 *	Get Window associated with OpenGL Context.
 *	@Return
 */
extern ELTDECLSPEC ExWin ELTAPIENTRY ExGetOpenGLContextWindow(ExOpenGLContext glc);

/**
 * 	Get device context of current openGL context on current thread
 *	@Return current device context on current thread.
 */
extern ELTDECLSPEC ExWindowContext ELTAPIFASTENTRY ExGetCurrentGLDrawable(void);

/**
 *	Get OpenGL context on the current thread
 *	@Return
 */
extern ELTDECLSPEC ExOpenGLContext ELTAPIFASTENTRY ExGetCurrentOpenGLContext(void);

/**
 *	Make current OpenGL context.
 *	\hDC
 *	\glc
 *	@Return
 */
extern ELTDECLSPEC int ELTAPIENTRY ExMakeGLCurrent(EX_RESTRICT ExWindowContext hDC,  EX_RESTRICT ExOpenGLContext glc);


/*	//TODO rename
 *
 *	@Return
 */
extern ELTDECLSPEC ExHandle ELTAPIENTRY ExGetOpenGLProc(const ExChar* cprocName);


/**
 *  Create Context Attribute Based on Internal Hardware and engine description.
 */
extern ELTDECLSPEC void ELTAPIENTRY ExCreateContextAttrib(ExWindowContext hDC, Int32* attrib, Int32* size);

/**
 *	Create OpenGL context for given window
 *	@Return
 */
extern ELTDECLSPEC ExOpenGLContext ELTAPIENTRY ExCreateGLContext(ExWin window, ExOpenGLContext shareContext);

/**
 *	@Return
 */
extern ELTDECLSPEC ExOpenGLContext ELTAPIENTRY ExCreateTempGLContext(void);

/**
 *	Create Shared OpenGL Context from a already existing context.
 *	@Return
 */
extern ELTDECLSPEC ExOpenGLContext ELTAPIENTRY ExCreateGLSharedContext(ExWin window, ExOpenGLContext context);

/**
 *	Set OpenGL context attribute.
 */
extern ELTDECLSPEC void ELTAPIENTRY ExOpenGLSetAttribute(unsigned int attr, int value);

/**
 *	Get OpenGL context attribute.
 *	@Return
 */
extern ELTDECLSPEC int ELTAPIENTRY ExOpenGLGetAttribute(unsigned int attr, int* value);


/**
 *	Reset OpenGL context attributes to default.
 */
extern ELTDECLSPEC void ELTAPIENTRY ExOpenGLResetAttributes(void);


/**
 *	Initialize OpenGL States 	 TODO perhaps remove.
 */
extern ELTDECLSPEC void ELTAPIENTRY ExInitOpenGLStates(void);

/**
 *	Destroy OpenGL Context.
 *	@Return
 */
extern ELTDECLSPEC ExBoolean ELTAPIENTRY ExDestroyGLContext(ExWindowContext drawable, ExOpenGLContext glc);

/**
 *	Destroy and release current OpenGL Context attached to current thread
 *	@Return
 */
extern ELTDECLSPEC ExBoolean ELTAPIENTRY ExDestroyCurrentGLContext(void);

/**
 *	Set Window associated with OpenGL context fullScreen.
 *	\
 *	\
 *	\
 *	\
 *
 *	@Return TRUE if sucesful.
 */
extern ELTDECLSPEC ExBoolean ELTAPIENTRY ExGLFullScreen(ExBoolean cdsfullscreen, ExWin window, Uint32 screenIndex, const Int* screenRes);




#define EX_GLTRANSPARENT_ENABLE 0x1
#define EX_GLTRANSPARENT_DISABLE 0x0
#define EX_GLTRANSPARENT_FULLBLUR 0x2

/*
 *  Set OpenGL Transparent.
 *  remark:
 *  you'll need to use glClear or from pixel shader alpha channel to see effect
 *  glClearColor
 *  ExSetHint(EX_ALPHA, x > 0);
 *  read more about DwmEnableBlurBehindWindow : http://msdn.microsoft.com/en-us/library/windows/desktop/aa969508(v=vs.85).aspx
 */
extern ELTDECLSPEC void ELTAPIENTRY ExSetGLTransparent(ExWin window, Enum ienum);

/**
 *	Get current binded OpenGL context shading version.
 *	@Return
 */
extern ELTDECLSPEC Uint32 ELTAPIFASTENTRY ExGetOpenGLShadingVersion(void);

/**
 *	Get current binded OpenGL context version.
 *	@Return
 */
extern ELTDECLSPEC Uint32 ELTAPIFASTENTRY ExGetOpenGLVersion(int* major, int* minor);


/**
 *	Get if OpenGL extension is supported on current binded machine.
 *	@Return TRUE is supported. Otherwise FALSE.
 */
extern ELTDECLSPEC Uint32 ELTAPIENTRY ExIsOpenGLExtensionSupported(const char* extension);


/**
 *	TODO perhaps move it somewhere else, as some other API may use the same
 *	extension parsing convention.
 */
extern ELTDECLSPEC Uint32 ELTAPIENTRY ExIsExtensionSupported(const char* extList, const char* extension);


/**
 *	@Return
 */
extern ELTDECLSPEC const ExChar* ELTAPIENTRY ExGetOpenGLServerExtension(void);

/**
 *	@Return
 */
extern ELTDECLSPEC const ExChar* ELTAPIENTRY ExGetOpenGLClientExtensions(void);

/*
 *	Check if graphic card is AMD GPU
 *	@Return
 */
extern ELTDECLSPEC Int32 ELTAPIENTRY ExIsVendorAMD(void);

/*
 *	Check if graphic card is Nvidia GPU
 *	@Return if Nvidia vendor
 */
extern ELTDECLSPEC Int32 ELTAPIENTRY ExIsVendorNvidia(void);

/*
 *	Check if graphic card is Intel GPU
 *	@Return
 */
extern ELTDECLSPEC Int32 ELTAPIENTRY ExIsVendorIntel(void);

/**
 *	Get graphic vendor enumerator
 *	@Return
 */
extern ELTDECLSPEC Enum ELTAPIENTRY ExGetOpenGLVendor(void);


/**
 *	Set OpenGL VSync.
 *	@Return
 */
extern ELTDECLSPEC ERESULT ELTAPIENTRY ExOpenGLSetVSync(ExBoolean enabled, ExWin window);


#ifdef __cplusplus	/*	C++ environment	*/
}
#endif

#include"elt_win.h"
#endif
