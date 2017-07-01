#include"system/elt_win.h"
#include"system/elt_gl.h"
#include"system/elt_cl.h"
#if defined(EX_WINDOWS)
	#include"system/win/win_win32.h"
	#include<winuser.h>
	#include<windowsx.h>
	#include<EGL/egl.h>
#elif defined(EX_LINUX)
	#include"system/unix/unix_win.h"
	#include <X11/X.h>
	#include <X11/Xlib.h>
	#include <X11/Xutil.h>
	#include <X11/keysym.h>

	#include<EGL/egl.h>
	#include<GL/glx.h>
	#include<X11/extensions/dpms.h>
#elif defined(EX_ANDROID)
#   include<android/native_window.h>
#   include<android/rect.h>
#   include<android/window.h>
#   include<EGL/egl.h>
	#ifdef GL_ES_VERSION_3_0
		#include<GLES3/gl3.h>
		#include<GLES3/gl3ext.h>
		#include<GLES3/gl3platform.h>
	#elif defined(GL_ES_VERSION_2_0)
		#include<GLES2/gl2.h>
		//#include<GLES2/gl2ext.h>
		//#include<GLES2/gl2platform.h>
	#elif defined(GL_ES_VERSION_1_0)
		#include<GLES/gl.h>
		#include<GLES/glext.h>
		#include<GLES/glplatform.h>
	#endif

#elif defined(EX_MAC)
	#include"system/mac/macosx_win.h"
	#include<EGL/egl.h>
#elif defined(EX_NACL)

#endif

#include"system/elt_icon.h"


#define EX_ENGINE_VERSION_STRING EX_TEXT("ELT Version | %d.%d%d%s | OS : %s : OpenGL %d.%d")
ExChar* ExGetDefaultWindowTitle(ExChar* text, int length){
	if(!text)
		return NULL;

	ExChar wchar[512] = {'\0'};
	int major;
	int minor;

	ExGetOpenGLVersion(&major,&minor);

#ifdef EX_UNICODE
	wsprintf(wchar,EX_ENGINE_VERSION_STRING,
#else
	sprintf(wchar,EX_ENGINE_VERSION_STRING,
#endif
		EX_VERSION_MAJOR,
		EX_VERSION_MINOR,
		EX_VERSION_REVISION,
		EX_ENGINE_STATUS,
		"",//ExGetOSName(),
		major,
		minor);
	memcpy(text, wchar, EX_MAX(sizeof(ExChar) * length + sizeof(ExChar),sizeof(wchar) / sizeof(ExChar)));
	return text;
}

ExWin ExCreateWindow(int x, int y, int width, int height, unsigned int flag) {
	ExWin window = NULL;
	ExOpenGLContext glc = NULL;
	ExOpenCLContext clc = NULL;
	ExHandle handle;
	char title[256];
	typedef ExOpenCLContext (*pExCreateCLSharedContext)(ExOpenGLContext glc, ExWindowContext window, unsigned int flag);
	pExCreateCLSharedContext opencl;
	unsigned int tmpCore = ExOpenGLGetAttribute(EX_OPENGL_CONTEXT_PROFILE_MASK, NULL);
	handle = ExLoadObject("");
	if(flag & EX_OPENCL){
		opencl = ExLoadFunction(handle, "ExCreateCLSharedContext");
	}



    if( (flag & EX_OPENGL_CORE) == EX_OPENGL_CORE ){
    	ExOpenGLSetAttribute(EX_OPENGL_CONTEXT_PROFILE_MASK, EX_GL_CONTEXT_PROFILE_CORE);
    }

#ifdef EX_WINDOWS
    void* directx;
	if((flag & EX_NATIVE) || flag == 0){
		// create default window
		return ExCreateNativeWindow(x,y,width, height);
	}
	// create window dedicated for OpenGL
	else if(flag & EX_OPENGL){
		window = ExCreateOpenGLWindow(x,y,width, height);
		glc = ExCreateGLContext(window,NULL);
		ExMakeGLCurrent(GetDC(window),glc);
#ifdef SUPPORT_OPENCL
		if(flag & EX_OPENCL)
			ExCreateCLSharedContext(glc,GetDC(window),EX_OPENGL);
#endif
		return window;
	}
	else if(flag & EX_EGL){
		window = (ExWin)ExCreateNativeWindow(x,y,width,height);
		glc = (ExOpenGLContext)ExCreateEGLContext(window,NULL);
		ExMakeGLCurrent(GetDC(window),glc);
#ifdef SUPPORT_OPENCL
		if(flag & EX_OPENCL)
			ExCreateCLSharedContext(glc,GetDC(window),EX_EGL);
#endif
	}
	else if(flag & EX_OPENCL){
		window = ExCreateNativeWindow(x,y,width,height);
#ifdef SUPPORT_OPENCL
		glc = (ExOpenCLContext)ExCreateCLContext(EX_GPU0, NULL);
#endif
	}
	/**
		//	Create window for directX.
		//	not recommended. because ELT won't be designed for handling DirectX because for a reason
		//	Instead its recommend to create the directX context yourself.
		//	however ELT support DirectX 9 context initialization
	*/
#if  defined(EX_INCLUDE_DIRECTX)
	else if(flag & EX_DIRECTX){
		window = ExCreateDirectXWindow(x,y,width, height);
		directx = (void*)ExCreateDirectXContext(window);
#ifdef SUPPORT_OPENCL
		if(flag & EX_OPENCL)
            ExCreateCLSharedContext((OpenGLContext)directx, GetDC(window), EX_DIRECTX);
#endif
	}
#endif
	else{
		ExSetError(E_INVALID_unsigned int);
	}
	/*	Linux Window Implementation	*/
#elif defined(EX_LINUX) || defined(EX_MAC)
	if((flag & EX_NATIVE) || !flag){
		window = ExCreateNativeWindow(x, y, width, height);
	}
	else if((flag & EX_OPENGL) || (flag & EX_OPENGL_CORE)){
        void* glx_window; //GLXWindow

		window = ExCreateGLWindow(x, y ,width, height, &glx_window);
        glc = ExCreateGLContext(glx_window != NULL ? glx_window : window, NULL);
		ExMakeGLCurrent(glx_window != NULL ? glx_window : window,glc);
		ExInitOpenGLStates();

#ifdef SUPPORT_OPENCL
		if(flag & EX_OPENCL){
			opencl(glXGetCurrentContext(), window, EX_OPENGL);
		}
#endif
	}
	else if(flag & EX_EGL){

		window = ExCreateNativeWindow(x, y, width, height);
		glc = ExCreateEGLContext(window, NULL);

#ifdef SUPPORT_OPENCL
		if(flag & EX_OPENCL){
			opencl(glc, eglGetCurrentDisplay(), EX_EGL);
		}
#endif
	}
	else if(flag & EX_VULKAN){

	}
	else if(flag & EX_OPENCL){
		window = ExCreateNativeWindow(x,y,width,height);
#ifdef SUPPORT_OPENCL
		//glc = ExCreateCLContext(0,NULL);
#endif

	}
#elif defined(EX_MAC)
    /**

    */
	if((flag & EX_NATIVE) || flag == 0){

	}
	else if((flag & ENGINE_OPENGL) || (flag & ENGINE_OPENCL)){

	}

#elif defined(EX_ANDROID)
    /**
        Android
    */
	if((flag & EX_NATIVE) || flag == 0){
        ANativeWindow_acquire(&window);
	}
	else if(flag & EX_OPENGL){
        ANativeWindow_acquire(&window);

#ifdef SUPPORT_OPENCL
        glc = ExCreateGLContext(window);

        if(flag & EX_OPENCL)
            ExCreateCLSharedContext(glc, window, EX_OPENGL);
#endif

	}
	else if(flag & EX_EGL){
        ANativeWindow_acquire(&window);
        glc = ExCreateEGLContext(window);

        //if(flag & EX_OPENCL)
        //    ExCreateCLSharedContext(glc, window, EX_OPENGL);

        return window;
	}
	else if(flag & EX_OPENCL){
        ANativeWindow_acquire(&window);
        //ExCreateCLContext(0);

	}
#elif defined(EX_PNACL) || defined(EX_NACL)
    if(flag & EX_NATIVE){


    }
    else if(flag & EX_OPENGL){
    	printf("pnacl create window");
		//window = ExCreateGLWindow(x,y,width, height,&glx_window);
    	window = NULL;
        glc = ExCreateGLContext(window,NULL);
    }

#endif


    /*	icon	*/
    ExSetWindowIcon(window, private_CreateELTIcon(window));

    /*	title*/
    ExGetDefaultWindowTitle(title, sizeof(title) / sizeof(title[0]));
	ExSetWindowTitle(window, title);
	return window;
}
