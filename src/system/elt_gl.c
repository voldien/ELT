#include"system/elt_gl.h"
#include"elt_def.h"

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

	#include"system/unix/unix_win.h"

   #define GL_GET_PROC(x) glXGetProcAddress( ( x ) )           /**  get OpenGL function process address */
#elif defined(EX_ANDROID)

    #include<jni.h>
    #include<android/native_activity.h>
	#include<EGL/egl.h>
	#include<EGL/eglext.h>
	#define GL_ES_VERSION_2_0 1

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


#if defined(GL_ES_VERSION_3_0)
	#include<GLES3/gl3.h>
	//#include<GLES3/gl3ext.h>
	//#include<GLES3/gl3platform.h>
#elif defined(GL_ES_VERSION_2_0)
	#include<GLES2/gl2.h>
	//#include<GLES2/gl2ext.h>
	//#include<GLES2/gl2platform.h>
#elif defined(GL_ES_VERSION_1_0)
	#include<GLES/gl.h>
	#include<GLES/glext.h>
	#include<GLES/glplatform.h>
#else
	#include<GL/gl.h>
	#include<GL/glu.h>
	#include<GL/glext.h>
#endif

/*	TODO perhaps relocate later to their coresponding platform source code files.*/
ELTDECLSPEC inline ExWin ELTAPIENTRY ExGetOpenGLContextWindow(ExOpenGLContext glc){
#ifdef EX_WINDOWS
	return WindowFromDC(wglGetCurrentDC());
#elif defined(EX_LINUX)
	return glXGetCurrentDrawable();
#elif defined(EX_ANDROID)
	return eglGetCurrentSurface(NULL);
#endif
}


ELTDECLSPEC inline ExWindowContext ELTAPIFASTENTRY ExGetCurrentGLDrawable(void){
#ifdef EX_WINDOWS
	return wglGetCurrentDC();
#elif defined(EX_LINUX)
	return glXGetCurrentDrawable();
#elif defined(EX_ANDROID)
	return eglGetCurrentSurface(NULL);
#endif
}

ELTDECLSPEC inline ExOpenGLContext ELTAPIFASTENTRY ExGetCurrentOpenGLContext(void){
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



ELTDECLSPEC inline int ELTAPIENTRY ExMakeGLCurrent(ExWindowContext drawable, ExOpenGLContext glc){
#ifdef EX_WINDOWS
	return wglMakeCurrent(drawable,glc);
#elif defined(EX_LINUX)
	return glXMakeCurrent(display,(GLXDrawable)drawable,(ExOpenGLContext)glc);
#elif defined(EX_ANDROID)
	return eglMakeCurrent(eglDisplay, drawable, drawable, glc);
#endif
}


ELTDECLSPEC void ELTAPIENTRY ExInitOpenGLStates(void){
	int value;
    int sampleSupport;

	// depth
	//glClearDepth(1.0f);
#if  !( defined(EX_ANDROID) ^ defined(EX_PNACL) )
	glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);



	if(ExOpenGLGetAttribute(EX_OPENGL_ALPHA_SIZE, &value) > 0)
		glEnable(GL_ALPHA_TEST);
	else
		glDisable(GL_ALPHA_TEST);

	if(ExOpenGLGetAttribute(EX_OPENGL_MULTISAMPLEBUFFERS, &value) > 0){
        glEnable(GL_MULTISAMPLE_ARB);
        	glGetIntegerv(GL_SAMPLE_BUFFERS,&sampleSupport);
        	if(sampleSupport){

        	}
	}

	glDepthRange(0.0, 1.0);
    glClearDepth(1.0);

	glBlendFunc(GL_ONE, GL_ZERO);


	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glDepthMask(GL_TRUE);

	glPolygonOffset(0.0, 0.0);

	glFrontFace(GL_CW);
	glCullFace(GL_BACK);

#endif

}


ELTDECLSPEC Uint32 ELTAPIFASTENTRY ExGetOpenGLShadingVersion(void){
#ifndef EX_ANDROID
	return (Uint32)(atof((const char*)glGetString(GL_SHADING_LANGUAGE_VERSION)) * 100.0f);
#else
    return 0;
#endif
}

ELTDECLSPEC Uint32 ELTAPIFASTENTRY ExGetOpenGLVersion(int* major,int* minor){
    if(!ExGetCurrentOpenGLContext()){
		/*	create temp*/
		ExWin win;
		unsigned int version;
		ExOpenGLContext glc;

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
		ExDestroyGLContext(NULL,glc);
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

Uint32 ExIsOpenGLExtensionSupported(const char* extension){
	return ExIsExtensionSupported(glGetString(GL_EXTENSIONS), extension);
}

Uint32 ExIsExtensionSupported(const char* extList,const char* extension){
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


#ifndef EX_LINUX
ELTDECLSPEC Int32 ELTAPIENTRY ExIsVendorAMD(void){
#ifndef EX_ANDROID
	return strstr((const char*)glGetString(GL_VENDOR), "AMD") ? TRUE : FALSE;
#endif
}
ELTDECLSPEC Int32 ELTAPIENTRY ExIsVendorNvidia(void){
#ifndef EX_ANDROID
	return strstr((const char*)glGetString(GL_VENDOR), "NVIDIA") ? TRUE : FALSE;
#endif
}
ELTDECLSPEC Int32 ELTAPIENTRY ExIsVendorIntel(void){
#ifndef EX_ANDROID
	return strstr((const char*)glGetString(GL_VENDOR), "INTEL") ? TRUE : FALSE;
#endif
}
#endif

ELTDECLSPEC Enum ELTAPIENTRY ExGetOpenGLVendor(void){
	if(ExIsVendorNvidia())return EX_NVIDIA;
	else if(ExIsVendorAMD())return EX_AMD;
	else if(ExIsVendorIntel())return EX_INTEL;
	else return EX_GPU_VENDOR_UNKNOWN;
}
