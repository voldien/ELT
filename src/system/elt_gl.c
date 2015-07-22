#include"system/elt_gl.h"
#include"ExPreProcessor.h"

#ifdef EX_WINDOWS
#include<GL/gl.h>
#include<GL/glext.h>
#elif defined(EX_LINUX)

//    #ifdef EX_X86
        #include<X11/extensions/Xrender.h>
//    #endif

    #include<X11/Xatom.h>
    #include<X11/keysym.h>
    #include<GL/glx.h>
    #include<GL/glxext.h>
    #include<GL/glu.h>
	#include"system/unix/unix_win.h"



   #define GL_GET_PROC(x) glXGetProcAddress( ( x ) )           /**  get OpenGL function process address */
#elif defined(EX_ANDROID)

    #include<jni.h>
    #include<android/native_activity.h>
	#include<EGL/egl.h>

	extern EGLDisplay eglDisplay;
#define GL_GET_PROC(x)  eglGetProcAddress(x)                                      /* * get OpenGL function process address */

#elif defined(EX_MAC)
#   include<GL/glu.h>
#endif


#ifdef EX_PNACL
	#include"ppapi/gles2/gl2ext_ppapi.h"
#endif

#ifdef EX_NACL
#	include<ppapi/c/ppb.h>

#endif



#ifdef GL_ES_VERSION_3_0
	#include<GLES3/gl3.h>
	#include<GLES3/gl3ext.h>
	#include<GLES3/gl3platform.h>
#elif defined(GL_ES_VERSION_2_0)
	#include<GLES2/gl2.h>
	#include<GLES2/gl2ext.h>
	#include<GLES2/gl2platform.h>
#elif defined(GL_ES_VERSION_1_0)
	#include<GLES/gl.h>
	#include<GLES/glext.h>
	#include<GLES/glplatform.h>
#else

#endif

#include<GLES2/gl2.h>
#include<GLES2/gl2ext.h>
#include<GLES2/gl2platform.h>



/*  check if extension is supported */
int isExtensionSupported(const char* extList, const char* extension){
	const char* start;
	const char *where;
	const char*terminator;
	where = strchr(extension, ' ');
	if(where || extension[0] == '\0')
		return 0;

	for(start = extList; ; ){
		where = strstr(start, extension);

		if(!where)break;

		terminator = where + strlen(extension);

		if(where == start || *(where - 1) == ' ')
			if(*terminator == ' ' || *terminator == '\0')
				return 1;

		start  = terminator;
	}
	return FALSE;
}

/*	Get window associated with the opengl context	*/
DECLSPEC inline ExWin ELTAPIENTRY ExGetOpenGLContextWindow(OpenGLContext glc){
#ifdef EX_WINDOWS
	return WindowFromDC(wglGetCurrentDC());
#elif defined(EX_LINUX)
	return glXGetCurrentDrawable();
#elif defined(EX_ANDROID)
	return eglGetCurrentSurface(NULL);
#endif
}
/**
    //Get Drawable
*/
DECLSPEC inline WindowContext ELTAPIFASTENTRY ExGetCurrentGLDC(void){
#ifdef EX_WINDOWS
	return wglGetCurrentDC();
#elif defined(EX_LINUX)
	return glXGetCurrentDrawable();
#elif defined(EX_ANDROID)
	return eglGetCurrentSurface(NULL);
#endif
}

DECLSPEC inline OpenGLContext ELTAPIFASTENTRY ExGetCurrentOpenGLContext(void){
#ifdef EX_WINDOWS
	return wglGetCurrentContext();
#elif defined(EX_LINUX)
	return glXGetCurrentContext();
#elif defined(EX_ANDROID)
	return eglGetCurrentContext();
#elif defined(EX_NACL) || defined(EX_PNACL)
    return glGetCurrentContextPPAPI();
#endif
}





DECLSPEC inline void ELTAPIENTRY ExMakeGLCurrent(WindowContext drawable, OpenGLContext glc){
#ifdef EX_WINDOWS
	ExIsWinError(wglMakeCurrent(drawable,glc));
#elif defined(EX_LINUX)
	glXMakeCurrent(display,(GLXDrawable)drawable,(OpenGLContext)glc);
#elif defined(EX_ANDROID)
	eglMakeCurrent(eglDisplay, drawable, drawable, glc);
#endif
}



/**
    Create Shared OpenGL Context from a already existing context.
*/


DECLSPEC void ELTAPIENTRY ExInitOpenGLStates(void){
	int value;
#if (EX_ENGINE_VERSION_MAJOR < 1 )
#ifdef EX_WINDOWS

	/*
		WGLSWAPINTERVALEXT_T wglSwapIntervalEXT = (WGLSWAPINTERVALEXT_T)GL_GET_PROC("wglSwapIntervalEXT");

		ExWin hWnd;	// Window
		RECT rect;	// client Rect
		hWnd = WindowFromDC(wglGetCurrentDC());
		GetClientRect(hWnd,&rect);
		// v-sync
		wglSwapIntervalEXT((engineDescription.EngineFlag & ENGINE_SUPPORT_VSYNC));
		// gl Viewport
		glViewport(0,0,rect.right - rect.left,rect.bottom - rect.top);
	*/
#elif defined(EX_LINUX)
    typedef void (*glXSwapIntervalEXTProc)(Display*, GLXDrawable drawable, int intervale);
    glXSwapIntervalEXTProc glXSwapIntervalEXT = (glXSwapIntervalEXTProc)GL_GET_PROC((const GLubyte*)"glXSwapIntervalEXT");
    //if(glXSwapIntervalEXT)
    //    glXSwapIntervalEXT(display, (GLXDrawable)ExGetCurrentGLDC(), 0);
#elif defined(EX_ANDROID)

#endif
#endif
    int sampleSupport;
	// depth
	//glClearDepth(1.0f);
	// color mask
	glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);

#if !( defined(EX_PNACL) ^ defined(EX_ANDROID) )
	if(ExOpenGLGetAttribute(EX_OPENGL_ALPHA_SIZE,&value) > 0)
		glEnable(GL_ALPHA_TEST);
	else glDisable(GL_ALPHA_TEST);
#endif

#if  !( defined(EX_ANDROID) ^ defined(EX_PNACL) )
	if(ExOpenGLGetAttribute(EX_OPENGL_MULTISAMPLEBUFFERS,&value) > 0){
        glEnable(GL_MULTISAMPLE_ARB);
//        	glGetIntegerv(GL_SAMPLE_BUFFERS,&sampleSupport);
//			if(sampleSupport){}
	}
#endif

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
#if !(defined(EX_ANDROID) ^ defined(EX_PNACL))
	glDepthRange(0.0, 1.0);
#endif
	glDepthMask(GL_TRUE);
	glPolygonOffset(0.0f, 0.0f);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CW);
	glClearColor(0.0f,0.0f,0.0f,1.0f);
#if !( defined(EX_ANDROID) ^ defined(EX_PNACL) )
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);


#endif
}




DECLSPEC Uint32 ELTAPIFASTENTRY ExGetOpenGLShadingVersion(void){
#ifndef EX_ANDROID
	return (Uint32)(atof((const char*)glGetString(GL_SHADING_LANGUAGE_VERSION)) * 100.0f);
#else
    return 0;
#endif
}

DECLSPEC Uint32 ELTAPIFASTENTRY ExGetOpenGLVersion(int* major,int* minor){
    if(!ExGetCurrentOpenGLContext()){
		/*	create temp*/
		ExWin win;
		unsigned int version;
		OpenGLContext glc;
#if !(defined(EX_ANDROID) ^ defined(EX_WINDOWS)  ^ defined(EX_PNACL))
		win = ExCreateGLWindow(0,0,1,1,0);
		glc = ExCreateTempGLContext();
		ExMakeGLCurrent(win, glc);
		version = ExGetOpenGLShadingVersion();
#endif
		/*TODO resolve later*/
#if !( defined(EX_ANDROID)  ^ defined(EX_PNACL))
		if(major)
			glGetIntegerv(GL_MAJOR_VERSION, major);
		if(minor)
			glGetIntegerv(GL_MINOR_VERSION, minor);

		ExMakeGLCurrent(0,0);
		ExDestroyContext(NULL,glc);
		ExDestroyWindow(win);
#endif
		return version;
    }
    else{
#if !(defined(EX_ANDROID) ^ defined(EX_PNACL))
		if(major)
			glGetIntegerv(GL_MAJOR_VERSION, major);
		if(minor)
			glGetIntegerv(GL_MINOR_VERSION, minor);
#endif

        return ExGetOpenGLShadingVersion();
    }
}

#ifndef EX_LINUX
DECLSPEC Int32 ELTAPIENTRY ExIsVendorAMD(void){
#ifndef EX_ANDROID
	return strstr((const char*)glGetString(GL_VENDOR), "AMD") ? TRUE : FALSE;
#endif
}
DECLSPEC Int32 ELTAPIENTRY ExIsVendorNvidia(void){
#ifndef EX_ANDROID
	return strstr((const char*)glGetString(GL_VENDOR), "NVIDIA") ? TRUE : FALSE;
#endif
}
DECLSPEC Int32 ELTAPIENTRY ExIsVendorIntel(void){
#ifndef EX_ANDROID
	return strstr((const char*)glGetString(GL_VENDOR), "INTEL") ? TRUE : FALSE;
#endif
}
#endif

DECLSPEC Enum ELTAPIENTRY ExGetOpenGLVendor(void){
	if(ExIsVendorNvidia())return EX_NVIDIA;
	else if(ExIsVendorAMD())return EX_AMD;
	else if(ExIsVendorIntel())return EX_INTEL;
	else return EX_UNKNOWN;
}
