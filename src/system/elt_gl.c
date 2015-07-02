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
    #include<EGL/egl.h>
    #include<EGL/eglext.h>
    #include<GL/glx.h>
    #include<GL/glxext.h>
    #include<GL/glu.h>
	#include"system/unix/unix_win.h"

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

   #define GL_GET_PROC(x) glXGetProcAddress( ( x ) )           /**  get OpenGL function process address */
#elif defined(EX_ANDROID)

    #include<jni.h>
    #include<android/native_activity.h>
	#ifdef GL_ES_VERSION_3_0
        #include<GLES3/gl3.h>
        #include<GLES3/gl3ext.h>
        #include<GLES3/gl3platform.h>
	#elif defined(GL_ES_VERSION_2_0)
        #include<GLES2/gl2.h>
        #include<GLES2/gl2ext.h>
        #include<GLES2/gl2platform.h>
    #else
        #include<GLES/gl.h>
        #include<GLES/glext.h>
        #include<GLES/glplatform.h>
	#endif
    #include<EGL/egl.h>
    #include<EGL/eglext.h>
    #include<EGL/eglplatform.h>

#define GL_GET_PROC(x)  eglGetProcAddress(x)                                      /* * get OpenGL function process address */

#elif defined(EX_MAC)
#   include<GL/glu.h>
#endif


#ifdef EX_PNACL
	#include"ppapi/gles2/gl2ext_ppapi.h"
#endif

#ifdef EX_NACL
#	include<ppapi/c/ppb.h>
#ifdef GL_ES_VERSION_2_0
        #include<GLES2/gl2.h>
        #include<GLES2/gl2ext.h>
        #include<GLES2/gl2platform.h>
#endif 
#endif


/*

*/
#define ExDevGLPrint(pFormat)	printf(pFormat EX_DEVELOP_ERROR_LOG,glGetError(),glewGetErrorString(glGetError()), __FILE__,__LINE__, EX_FUNCDNAME);
#define ExDevGLPrintc(pFormat,color)	{Uint16 __colour__ = ExGetConsoleColor();ExSetConsoleColor(color);printf(pFormat EX_DEVELOP_ERROR_LOG,glGetError(),glewGetString(glGetError()),__LINE__, __FILE__,EX_FUNCNAME);ExSetConsoleColor(__colour__);}
#define ExDevGLPrintf(pFormat,...)	{Uint16 __colour__ = ExGetConsoleColor();ExSetConsoleColor(color);printf(pFormat  EX_DEVELOP_ERROR_LOG,__VA_ARGS__,glGetError(),glewGetString(glGetError()),LINE__, __FILE__,EX_FUNCNAME);ExSetConsoleColor(__colour__);}
#define ExDevGLPrintfc(pFormat,color,...){Uint16 __colour__ = ExGetConsoleColor();ExSetConsoleColor(color);printf(pFormat EX_DEVELOP_ERROR_LOG,__VA_ARGS__,glGetError(), glewGetString(glGetError()), __LINE__, __FILE__,EX_FUNCNAME	);ExSetConsoleColor(__colour__);}
/**
	OpenGL Error
*/
#define ExIsGLError(x)  { if( ( x ) <= 0 ){ ExDevGLPrintc("Error",EX_CONSOLE_RED); } }


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
#elif defined(EX_NACL)
    return glGetCurrentContextPPAPI();
#endif
}





DECLSPEC inline void ELTAPIENTRY ExMakeGLCurrent(WindowContext drawable, OpenGLContext glc){
#ifdef EX_WINDOWS
	ExIsWinError(wglMakeCurrent(drawable,glc));
#elif defined(EX_LINUX)
	/*ExIsGLError*/(glXMakeCurrent(display,(GLXDrawable)drawable,(OpenGLContext)glc));
#elif defined(EX_ANDROID)
	eglMakeCurrent(eglDisplay, drawable, drawable, glc);
#endif
}



/**
    Create Shared OpenGL Context from a already existing context.
*/


DECLSPEC void ELTAPIENTRY ExInitOpenGLStates(EngineDescription* enginedescription){
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
   // if(glXSwapIntervalEXT)
    //    glXSwapIntervalEXT(display, (GLXDrawable)ExGetCurrentGLDC(), 0);
#elif defined(EX_ANDROID)

#endif
#endif
    int sampleSupport;
	// depth
	//glClearDepth(1.0f);
	// color mask
	glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);

#ifndef EX_PNACL
	if(engineDescription.alphaChannel > 0)
		glEnable(GL_ALPHA_TEST);
	else glDisable(GL_ALPHA_TEST);
#endif

#ifndef EX_ANDROID
//    if(engineDescription.sample[0]){
//        glEnable(GL_MULTISAMPLE_ARB);
//        glGetIntegerv(GL_SAMPLE_BUFFERS,&sampleSupport);
//        if(sampleSupport){}
//    }
#endif
//if(engineDescription.EngineFlag & ENGINE_SUPPORT_PRIMITIV_SAMPLE){
//
//	Int32 sampleSupport;
//	glGetIntegerv(GL_SAMPLE_BUFFERS,&sampleSupport);
//	if(sampleSupport)
//
//}
//else{ glDisable(GL_MULTISAMPLE_ARB);}

	// depth

	//glDrawBuffer(GL_BACK);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
#ifndef EX_ANDROID
	glDepthRange(0.0, 1.0);
#endif
	glDepthMask(GL_TRUE);
	glPolygonOffset(0.0f, 0.0f);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CW);
	glClearColor(0.0f,0.0f,0.0f,1.0f);
#if !(defined(GL_ES_VERSION_3_0) || defined(GL_ES_VERSION_2_0) || defined(GL_ES_VERSION_1_0) || defined(EX_ANDROID))
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
#endif
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

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
#if !(defined(EX_ANDROID) || defined(EX_WINDOWS))
		win = ExCreateGLWindow(0,0,1,1,0);
		glc = ExCreateTempGLContext();
		ExMakeGLCurrent(win, glc);
		version = ExGetOpenGLShadingVersion();
		/*TODO resolve later*/
#if !(defined(GL_ES_VERSION_3_0) || defined(GL_ES_VERSION_2_0) || defined(GL_ES_VERSION_1_0))
		if(major)
			glGetIntegerv(GL_MAJOR_VERSION, major);
		if(minor)
			glGetIntegerv(GL_MINOR_VERSION, minor);
#endif
#endif
		ExMakeGLCurrent(0,0);
		ExDestroyContext(NULL,glc);
		ExDestroyWindow(win);
		return version;
    }
    else{
#if !(defined(GL_ES_VERSION_3_0) || defined(GL_ES_VERSION_2_0) || defined(GL_ES_VERSION_1_0))
		if(major)
			glGetIntegerv(GL_MAJOR_VERSION, major);
		if(minor)
			glGetIntegerv(GL_MINOR_VERSION, minor);
#endif

        return ExGetOpenGLShadingVersion();
    }
}

//TODO see if it can be obtain before creating the context.
DECLSPEC Int32 ELTAPIENTRY ExIsVendorAMD(void){
	return strstr((const char*)glGetString(GL_VENDOR), "AMD") ? TRUE : FALSE;
}
DECLSPEC Int32 ELTAPIENTRY ExIsVendorNvidia(void){
	return (strstr((const char*)glGetString(GL_VENDOR), "NVIDIA")) ? TRUE : FALSE;
}
DECLSPEC Int32 ELTAPIENTRY ExIsVendorIntel(void){
	return strstr((const char*)glGetString(GL_VENDOR), "INTEL") ? TRUE : FALSE;
}
DECLSPEC Enum ELTAPIENTRY ExGetGLVendorEnum(void){
	if(ExIsVendorNvidia())return EX_GPU_NVIDIA;
	else if(ExIsVendorAMD())return EX_GPU_AMD;
	else if(ExIsVendorIntel())return EX_GPU_INTEL;
	else return EX_GPU_UNKNOWN;
}
