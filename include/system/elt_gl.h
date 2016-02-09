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

#ifdef EX_WINDOWS
	#define ExSwapBuffers SwapBuffers
#elif defined(EX_LINUX)
	#define ExSwapBuffers(window) glXSwapBuffers(display,window)
#elif defined(EX_MAC)
	#define ExSwapBuffers glSwapBuffers
#elif defined(EX_ANDROID)
	#define ExSwapBuffers(surface) eglSwapBuffers(eglGetDisplay(EGL_DEFAULT_DISPLAY),surface)
#else
	extern DECLSPEC void ExSwapBuffers(void* surface);
#endif


/*
 *	GPU Vendors constant of.
 */
#define EX_UNKNOWN	0x0				/**/
#define EX_NVIDIA	0x1				/**/
#define EX_INTEL	0x2				/**/
#define EX_AMD		0x4				/**/


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
#define EX_OPENGL_EGL


/*
 *	Context profile mask flag attributes bit.
 */
#define EX_GL_CONTEXT_PROFILE_CORE           	0x00000001	/*	*/
#define EX_GL_CONTEXT_PROFILE_COMPATIBILITY  	0x00000002	/*	*/
#define EX_GL_CONTEXT_PROFILE_ES             	0x00000004 	/* GLX_CONTEXT_ES2_PROFILE_BIT_EXT */
#define EX_GL_CONTEXT_PROFILE_ES2				0x00000008	/*	*/

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

/*
 *	Get Window associated with OpenGL Context.
 *	@Return
 */
extern DECLSPEC ExWin ELTAPIENTRY ExGetOpenGLContextWindow(ExOpenGLContext glc);

/*
 * 	Get device context of current openGL context on current thread
 *	@Return current device context on current thread.
 */
extern DECLSPEC WindowContext ELTAPIFASTENTRY ExGetCurrentGLDC(void);
#define ExGetCurrentGLDrawable ExGetCurrentGLDC

/*
 *	Get OpenGL context on the current thread
 *	@Return
 */
extern DECLSPEC ExOpenGLContext ELTAPIFASTENTRY ExGetCurrentOpenGLContext(void);

/*
 *	Get OpenGL context from given window.
 *	@Return
 */
extern DECLSPEC ExOpenGLContext ELTAPIENTRY ExGetOpenGLCFromWindow(ExWin window);

/*
 *	Make current OpenGL context.
 *	\hDC
 *	\glc
 *	@Return
 */
extern DECLSPEC int ELTAPIENTRY ExMakeGLCurrent(ExWindowContext hDC, ExOpenGLContext glc);

/*
 *  Create Context Attribute Based on Internal Hardware and engine description.
*/
extern DECLSPEC void ELTAPIENTRY ExCreateContextAttrib(ExWindowContext hDC,Int32* attrib, Int32* size);

/*
 *	Create OpenGL context for given window
 *	@Return
 */
extern DECLSPEC ExOpenGLContext ELTAPIENTRY ExCreateGLContext(ExWin window, ExOpenGLContext shareContext);

/*
 *
 *	@Return
 */
extern DECLSPEC ExOpenGLContext ELTAPIENTRY ExCreateTempGLContext(void);

/*
 *	Create Shared OpenGL Context from a already existing context.
 *	@Return
 */
extern DECLSPEC ExOpenGLContext ELTAPIENTRY ExCreateGLSharedContext(ExWin window, ExOpenGLContext context);

/*
 *	Set OpenGL context attribute.
 */
extern DECLSPEC void ELTAPIENTRY ExOpenGLSetAttribute(unsigned int attr, int value);

/*
 *	Get OpenGL context attribute.
 *	@return
 */
extern DECLSPEC int ELTAPIENTRY ExOpenGLGetAttribute(unsigned int attr, int* value);


/*
 *	Reset OpenGL context attributes to default.
 */
extern DECLSPEC void ELTAPIENTRY ExOpenGLResetAttributes(void);

/*
 *	Initialize OpenGL States
 */
extern DECLSPEC void ELTAPIENTRY ExInitOpenGLStates(void);

/*
 *	Destroy OpenGL Context.
 *	@Return
 */
extern DECLSPEC ExBoolean ELTAPIENTRY ExDestroyGLContext(ExWindowContext drawable, ExOpenGLContext glc);

/*
 *	Destroy and release current OpenGL Context attached to current thread
 *	@Return
 */
extern DECLSPEC ExBoolean ELTAPIENTRY ExDestroyCurrentGLContext(void);

/*
 *	Set Window associated with OpenGL context fullScreen.
 *	\
 *	\
 *	\
 *	\
 *
 *	@return TRUE if sucesful.
 */
extern DECLSPEC ExBoolean ELTAPIENTRY ExGLFullScreen(ExBoolean cdsfullscreen, ExWin window, Uint32 screenIndex, const Int* screenRes);


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
extern DECLSPEC void ELTAPIENTRY ExSetGLTransparent(ExWin hWnd, Enum ienum);

/*
 *	Get Hardware OpenGL shading Version
 *	@return
 */
extern DECLSPEC Uint32 ELTAPIFASTENTRY ExGetOpenGLShadingVersion(void);

/*
 *	Get OpenGL Version
 *	@return
 */
extern DECLSPEC Uint32 ELTAPIFASTENTRY ExGetOpenGLVersion(int* major,int* minor);


/*
 *	Get if OpenGL extension is supported on current binded machine.
 *	@return TRUE is supported. Otherwise FALSE.
 */
extern DECLSPEC Uint32 ELTAPIENTRY ExIsOpenGLExtensionSupported(const char* extension);

/*
 *	TODO perhaps move it somewhere else, as some other API may use the same
 *	extension parsing convention.
 */
extern DECLSPEC Uint32 ELTAPIENTRY ExIsExtensionSupported(const char* extList,const char* extension);


/*
 *	Check if graphic card is AMD GPU
 *	@return
 */
extern DECLSPEC Int32 ELTAPIENTRY ExIsVendorAMD(void);

/*
 *	Check if graphic card is Nvidia GPU
 *	@return if Nvidia vendor
 */
extern DECLSPEC Int32 ELTAPIENTRY ExIsVendorNvidia(void);

/*
 *	Check if graphic card is Intel GPU
 *	@return
 */
extern DECLSPEC Int32 ELTAPIENTRY ExIsVendorIntel(void);

/*
 *	Get graphic vendor enumerator
 *	@return
 */
extern DECLSPEC Enum ELTAPIENTRY ExGetOpenGLVendor(void);


/*
 *	Set OpenGL VSync.
 *	@return
 */
extern DECLSPEC ERESULT ELTAPIENTRY ExOpenGLSetVSync(ExBoolean enabled, ExWin window);


#ifdef __cplusplus	/*	C++ environment	*/
}
#endif

#include"elt_win.h"
#endif
