#include"system/elt_egl.h"
#include"elt_loadso.h"

/*	some platform just can't handle EGL	*/
#if !defined(EX_PNACL) || !defined(EX_NACL)


#ifdef EX_WINDOWS
	#include<EGL/egl.h>
    #define EX_EGL_LIB_MOUDLE_NAME EX_TEXT("libEGL.dll")		/**/
    #define EX_GLES_LIB_MOUDLE_NAME EX_TEXT("libGLESv2.dll")	/**/
#elif defined(EX_LINUX) && !defined(EX_ANDROID)
	#include<EGL/egl.h>
    #define EX_EGL_LIB_MOUDLE_NAME EX_TEXT("libEGL.so")			/**/
    #define EX_GLES_LIB_MOUDLE_NAME EX_TEXT("libGLESv2.so")		/**/
#elif defined(EX_ANDROID)
	#include<EGL/egl.h>
	#include<EGL/eglext.h>
	#include<EGL/eglplatform.h>
    #define EX_EGL_LIB_MOUDLE_NAME EX_TEXT("libEGL.so")      	/* */
    #define EX_GLES_LIB_MOUDLE_NAME EX_TEXT("libGLESv2.so")  	/* */
#elif defined(EX_IOS)
	#include<MetalGL/MetalGL.h>
	#include<MetalGL/mglext.h>
#endif 


#ifdef GL_ES_VERSION_3_0
	#include<GLES3/gl3.h>
	#include<GLES3/gl3ext.h>
	#include<GLES3/gl3platform.h>
#elif defined(GL_ES_VERSION_2_0)
	#undef GL_ES_VERSION_2_0
	#include<GLES2/gl2.h>
	#include<GLES2/gl2ext.h>
	#include<GLES2/gl2platform.h>
#elif defined(GL_ES_VERSION_1_0)
	#include<GLES/gl.h>
	#include<GLES/glext.h>
	#include<GLES/glplatform.h>
#else
	#include<GL/gl.h>
	#include<GL/glu.h>
	#include<GL/glext.h>
#endif


EGLint configAttribList[] ={
	EGL_BUFFER_SIZE, 16,
	EGL_RENDERABLE_TYPE,
	EGL_OPENGL_ES2_BIT,
	EGL_NONE
};

ExHandle egl_libhandle	=	NULL;
ExEGLDisplay eglDisplay	=	NULL;

ExEGLContext ExCreateEGLContext(ExWin window, ExEGLContext shared){
	/*	TODO resolve later!!*/

	int major ,minor ;
	EGLint attrs[60];
	EGLint numConfig = 0;
	EGLConfig eglConfig = 0;

	EGLSurface eglSurface;
	EGLContext eglContext;
	ERESULT hr;


	/*	load dynamic library dependency.	*/
	if(!ExIsModuleLoaded(EX_EGL_LIB_MOUDLE_NAME)){
		ExLoadLibrary(EX_EGL_LIB_MOUDLE_NAME);
	}
	if(!ExIsModuleLoaded(EX_GLES_LIB_MOUDLE_NAME)){
		ExLoadLibrary(EX_GLES_LIB_MOUDLE_NAME);
	}


	if(!ExCreateEGLContextAttrib(window, attrs, NULL)){
		return NULL;
	}

	/**/
    EGLint configAttribList[] ={
    	EGL_BUFFER_SIZE, 16,
        EGL_RENDERABLE_TYPE,
        EGL_OPENGL_ES2_BIT,
        EGL_NONE
    };

	/**/
    EGLint ctxattr[] = {
      EGL_CONTEXT_CLIENT_VERSION, 2,
      EGL_NONE
    };



#ifdef EX_WINDOWS
	eglDisplay = eglGetDisplay(NULL);
#elif defined(EX_LINUX)
	eglDisplay = eglGetDisplay((EGLNativeDisplayType)display);
#elif defined(EX_ANDROID)
	eglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
#endif


	if(eglBindAPI(EGL_OPENGL_API) != EGL_TRUE){
        ExError("Bind API!");
	}

    /*	Initialize OpenGL ES	*/
	if((hr = eglInitialize(eglDisplay, &major, &minor)) != EGL_TRUE){
		ExError(EX_TEXT("Failed to Initialize OpenGL ES"));
	}

	/*	Choose Config	*/
	if((hr = eglChooseConfig(eglDisplay, configAttribList, &eglConfig, 1, &numConfig)) != EGL_TRUE){
		ExError(EX_TEXT("failed to Choose config for EGL.\n"));
	}

	if(!(eglSurface = eglCreateWindowSurface(eglDisplay, eglConfig, (EGLNativeWindowType)window, NULL))){
		ExError(EX_TEXT("error"));
	}

	if(!(eglContext = eglCreateContext(eglDisplay, eglConfig, shared, ctxattr)))
        ExError(EX_TEXT("Error"));

	if((hr = eglMakeCurrent(eglDisplay, eglSurface, eglSurface, eglContext)) != EGL_TRUE)
        ExError(EX_TEXT("OpenGL ES Error"));


	/**/
	ExInitOpenGLStates();

	return eglContext;
}

int ExMakeEGLCurrent(EX_RESTRICT ExWindowContext hDC,  EX_RESTRICT ExEGLContext glc){
	return eglMakeCurrent(eglDisplay, hDC, hDC, glc);
}


int ExCreateEGLContextAttrib(ExWin window, int* attrib, unsigned int* size){

	return EX_TRUE;
}

void ExDestroyEGLContext(ExEGLContext context){
	eglDestroyContext(eglGetCurrentDisplay(), context);
}

void ExEGLSetVSync(int interval_ms){
	eglSwapInterval(eglDisplay, interval_ms);
}

void ExSwapEGLBuffer(ExWin context){
	eglSwapBuffers(eglDisplay, context);
}


#endif
