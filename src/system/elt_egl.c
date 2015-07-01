#include"system/elt_egl.h"

/*	some platform just can't handle EGL	*/
#if !defined(EX_PNACL) || !defined(EX_NACL)

#include<EGL/egl.h>


#ifdef EX_WINDOWS
    #define EX_EGL_LIB_MOUDLE_NAME EX_TEXT("libEGL.dll")		/**/
    #define EX_GLES_LIB_MOUDLE_NAME EX_TEXT("libGLESv2.dll")	/**/
#elif defined(EX_LINUX)
    #define EX_EGL_LIB_MOUDLE_NAME EX_TEXT("libEGL.so")			/**/
    #define EX_GLES_LIB_MOUDLE_NAME EX_TEXT("libGLESv2.so")		/**/
#elif defined(EX_ANDROID)
    #define EX_EGL_LIB_MOUDLE_NAME EX_TEXT("libEGL.so")      	/* */
    #define EX_GLES_LIB_MOUDLE_NAME EX_TEXT("libGLESv2.so")  	/* */
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
#endif

static EGLDisplay eglDisplay;

DECLSPEC OpenGLContext ELTAPIENTRY ExCreateEGLContext(ExWin window){
	/*	TODO resolve later!!*/
	#ifndef EX_ANDROID
	#endif


	int major ,minor ;
	EGLint attrs[60];
	EGLint numConfig = 0;
	EGLConfig eglConfig = 0;

	EGLSurface eglSurface;
	EGLContext eglContext;
	ERESULT hr;

	/*
		load dynamic library dependency.
	*/
	if(!ExIsModuleLoaded(EX_EGL_LIB_MOUDLE_NAME))
		ExLoadLibrary(EX_EGL_LIB_MOUDLE_NAME);
	if(!ExIsModuleLoaded(EX_GLES_LIB_MOUDLE_NAME))
		ExLoadLibrary(EX_GLES_LIB_MOUDLE_NAME);



	if(!ExCreateEGLContextAttrib(window,attrs,NULL)){

	}

    EGLint configAttribList[] =
    {
    EGL_BUFFER_SIZE, 16,
          EGL_RENDERABLE_TYPE,
          EGL_OPENGL_ES2_BIT,
          EGL_NONE
    };



#ifdef EX_WINDOWS
	eglDisplay = eglGetDisplay(NULL);
	if(eglBindAPI(EGL_OPENGL_API) != EGL_TRUE)
        ExError("Bind API!");
    EGLint ctxattr[] = {
      EGL_CONTEXT_CLIENT_VERSION, 2,
      EGL_NONE
    };
#elif defined(EX_LINUX)
	if(eglBindAPI(EGL_OPENGL_API) != EGL_TRUE)
        ExError("Bind API!");
	eglDisplay = eglGetDisplay((EGLNativeDisplayType)display);
    EGLint ctxattr[] = {
      EGL_CONTEXT_CLIENT_VERSION, 2,
      EGL_NONE
    };
#elif defined(EX_ANDROID)
	eglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    EGLint ctxattr[] = {
      EGL_CONTEXT_CLIENT_VERSION, 2,
      EGL_NONE
    };
#endif
	/**
        Initialize OpenGL ES
	*/

	if((hr = eglInitialize(eglDisplay, &major, &minor)) != EGL_TRUE)
        ExError(EX_TEXT("Failed to Initialize OpenGL ES"));
	//	Choose Config
	if((hr = eglChooseConfig(eglDisplay, configAttribList, &eglConfig, 1, &numConfig)) != EGL_TRUE)
        ExError(EX_TEXT(""));

	if(!(eglSurface = eglCreateWindowSurface(eglDisplay,eglConfig,(EGLNativeWindowType)window,NULL)))
        ExError(EX_TEXT("error"));

	if(!(eglContext = eglCreateContext(eglDisplay,eglConfig,EGL_NO_CONTEXT,ctxattr)))
        ExError(EX_TEXT("Error"));

	if((hr = eglMakeCurrent(eglDisplay, eglSurface, eglSurface, eglContext)) != EGL_TRUE)
        ExError(EX_TEXT("OpenGL ES Error"));

	ExInitOpenGLStates(0);

	return eglContext;
}
int ExCreateEGLContextAttrib(ExWin window,int* attrib, unsigned int* size){


	return 1;
}

#endif
