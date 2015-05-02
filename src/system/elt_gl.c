#include"system/elt_gl.h"
#include"ExPreProcessor.h"

#if defined(EX_LINUX)
    #define EX_EGL_LIB_MOUDLE_NAME EX_TEXT("libEGL.so")
    #define EX_GLES_LIB_MOUDLE_NAME EX_TEXT("libGLESv2.so")
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
   #define GL_GET_PROC(x) glXGetProcAddress( ( x ) )           /**  get OpenGL function process address */
#elif defined(EX_ANDROID)
    #define EX_EGL_LIB_MOUDLE_NAME EX_TEXT("libEGL.so")      /** */
    #define EX_GLES_LIB_MOUDLE_NAME EX_TEXT("libGLESv2.so")  /** */
    #include<jni.h>
    #include<android/native_activity.h>
	#ifdef GL_ES_VERSION_2_0
        #include<GLES/gl2.h>
        #include<GLES/gl2ext.h>
        #include<GLES/gl2platform.h>
    #else
        #include<GLES/gl.h>
        #include<GLES/glext.h>
        #include<GLES/glplatform.h>
	#endif
    #include<EGL/egl.h>
    #include<EGL/eglext.h>
    #include<EGL/eglplatform.h>
    static EGLDisplay eglDisplay;
#define GL_GET_PROC(x)  eglGetProcAddress(x)                                      /* * get OpenGL function process address */

#elif defined(EX_MAC)
#   include<GL/glu.h>
#endif

#ifdef EX_PNACL
	#include "ppapi/c/ppb.h"
	#include "ppapi/c/pp_errors.h"
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
static int isExtensionSupported(const char* extList, const char* extension){
#if defined(EX_WINDOWS) || defined(EX_LINUX)
	const char* start;
	const char *where, *terminator;
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
#endif
	return FALSE;
}


DECLSPEC void* ELTAPIENTRY ExCreateOpenGLES(ExWin window){
	#ifndef EX_ANDROID
	EGLDisplay eglDisplay;
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

	//ExCreateContextAttrib(window,attrs,0,0,EX_OPENGLES);

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

/**
	Get window associated with the opengl context
*/
DECLSPEC inline ExWin ELTAPIENTRY ExGetOpenGLContextWindow(OpenGLContext glc){
#if defined(EX_LINUX)
	return glXGetCurrentDrawable();
#elif defined(EX_ANDROID)
	return eglGetCurrentSurface(NULL);
#endif
}
/**
    //Get Drawable
*/
DECLSPEC inline WindowContext ELTAPIFASTENTRY ExGetCurrentGLDC(void){
#if defined(EX_LINUX)
	return glXGetCurrentDrawable();
#elif defined(EX_ANDROID)
	return eglGetCurrentSurface(NULL);
#endif
}

DECLSPEC inline OpenGLContext ELTAPIFASTENTRY ExGetCurrentOpenGLContext(void){
#if defined(EX_LINUX)
	return glXGetCurrentContext();
#elif defined(EX_ANDROID)
	return eglGetCurrentContext();
#elif defined(EX_NACL)
    return glGetCurrentContextPPAPI();
#endif
}

DECLSPEC inline void ELTAPIENTRY ExMakeGLCurrent(WindowContext drawable, OpenGLContext glc){

#if defined(EX_LINUX)
	/*ExIsGLError*/(glXMakeCurrent(display,(GLXDrawable)drawable,(OpenGLContext)glc));
#elif defined(EX_ANDROID)
	eglMakeCurrent(eglDisplay, drawable, drawable, glc);
#endif
}
/**
=================================00
            Windows GL Impl
=================================00
*/
#if defined(EX_LINUX)
#ifdef EX_DEBUG
static void describe_fbconfig(GLXFBConfig fbconfig){
	int doublebuffer;
	int red_bits,green_bits, blue_bits, alpha_bits, depth_bits;

	glXGetFBConfigAttrib(display,fbconfig,GLX_DOUBLEBUFFER,&doublebuffer);
	glXGetFBConfigAttrib(display,fbconfig,GLX_RED_SIZE,&red_bits);
	glXGetFBConfigAttrib(display,fbconfig,GLX_GREEN_SIZE,&blue_bits);
	glXGetFBConfigAttrib(display,fbconfig,GLX_BLUE_SIZE,&green_bits);
	glXGetFBConfigAttrib(display,fbconfig,GLX_ALPHA_SIZE,&alpha_bits);
	glXGetFBConfigAttrib(display,fbconfig,GLX_DEPTH_SIZE,&depth_bits);
}
#endif

/**choose fb configure  */
static int choose_fbconfig(GLXFBConfig* p_fbconfig){
	GLXFBConfig* fbconfigs;
	XVisualInfo* visual;
	XRenderPictFormat *pict_format;
	int numfbconfigs,i;
	int att[72] = {0};
	ExCreateContextAttrib(NULL,&att[0],0,EX_OPENGL);

	fbconfigs = glXChooseFBConfig(display,DefaultScreen(display), att,&numfbconfigs);
    p_fbconfig[0] = fbconfigs[0];
	for(i = 0; i < numfbconfigs; i++){
		visual = (XVisualInfo*)glXGetVisualFromFBConfig(display, fbconfigs[i]);
		if(!visual)continue;

		pict_format = XRenderFindVisualFormat(display, visual->visual);
		if(!pict_format)continue;

		p_fbconfig[0] = fbconfigs[i];
        if(engineDescription.alphaChannel > 0){
            if(pict_format->direct.alphaMask > 0)break;
        }else break;

	}
	return 1;
}
#endif

void ELTAPIENTRY ExCreateContextAttrib(WindowContext hDc, Int32* attribs,Int32* size,Enum erenderingflag){
	if(!attribs)	/* error */
		ExSetError(EINVAL);
#if defined(EX_LINUX)
	if(erenderingflag & EX_OPENGLES){
		Int32 pixAttribs[] = {
		     /*EGL_PIXMAP_BIT*/
		    EGL_BUFFER_SIZE, 16,
            EGL_DEPTH_SIZE, 16,
            EGL_SAMPLES, engineDescription.sample[0],
		    EGL_OPENGL_ES2_BIT,
		    EGL_NONE
		     };
		if(size)size =sizeof(pixAttribs);
		memcpy(attribs,(int*)pixAttribs,sizeof(pixAttribs));

	}
	else if(erenderingflag & EX_OPENGL){
		Int32 pixAttribs[] = {
                GLX_RENDER_TYPE, GLX_RGBA_BIT,
                GLX_X_RENDERABLE, True,
                GLX_X_VISUAL_TYPE, GLX_TRUE_COLOR,
                GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
                GLX_DOUBLEBUFFER, True,
                GLX_AUX_BUFFERS, 0,
                /**/
                GLX_RED_SIZE, 8,
                GLX_GREEN_SIZE, 8,
                GLX_BLUE_SIZE, 8,
                GLX_ALPHA_SIZE,engineDescription.alphaChannel,
                GLX_DEPTH_SIZE, 24,
                GLX_STENCIL_SIZE,engineDescription.StencilBits,

                GLX_STEREO,0,
                GLX_SAMPLE_BUFFERS_ARB,engineDescription.sample[0] != 0 ? 1 : 0,
                GLX_SAMPLES_ARB,engineDescription.sample[0],
                //GLX_TRANSPARENT_TYPE, GLX_TRANSPARENT_RGB,
                None,
				/*
			//GLX_TRANSPARENT_ARB, WGL_TRANSPARENT_ALPHA_VALUE_ARB,,*/
			}; // NULL termination
		if(size)size =sizeof(pixAttribs);
		memcpy(attribs,(int*)pixAttribs,sizeof(pixAttribs));

	}
#elif defined(EX_ANDROID)

	if(erenderingflag & EX_OPENGL){  /* as for today 2015 -01 -09 must devices on android don't support OpenGL TODO:solve in future*/


	}
	else if(erenderingflag & EX_OPENGLES){
        if(erenderingflag & EX_OPENGLES){
            Int32 pixAttribs[] = {
                //EGL_NATIVE_RENDERABLE, 1,
                /*EGL_PIXMAP_BIT*/
                EGL_BUFFER_SIZE, 16,
            // EGL_GREEN_SIZE, 4,
            // EGL_BLUE_SIZE, 4,
            // EGL_ALPHA_SIZE, 4,
                EGL_DEPTH_SIZE, 16,
                //EGL_SAMPLES, 4,
                //EGL_SURFACE_TYPE,
                EGL_OPENGL_ES2_BIT,
                EGL_NONE
                };
            if(size)size =sizeof(pixAttribs);
            memcpy(attribs,(int*)pixAttribs,sizeof(pixAttribs));
        }

	}
#elif defined(EX_MAC)

#endif
	return;
}

 DECLSPEC OpenGLContext ELTAPIENTRY ExCreateGLContext(ExWin window){
	OpenGLContext glc = 0;
	unsigned int render_vendor;
#if defined(EX_LINUX)
	XVisualInfo* vi;		//	Visual Info
	int dummy, min,maj, major_version, minor_version;
	GLXFBConfig fbconfig;
    glXQueryVersion(display,&maj,&min);

    /**
        Get Current Supported Version of OpenGL
    */
    glGetIntegerv(GL_MAJOR_VERSION, &major_version);
    glGetIntegerv(GL_MINOR_VERSION, &minor_version);



    int context_attribs[]={
        GLX_CONTEXT_MAJOR_VERSION_ARB,/* major_version*/3, //TODO obtain latest major version
        GLX_CONTEXT_MINOR_VERSION_ARB,/* minor_version*/3, //TODO obtain latest minor version
        #ifdef EX_DEBUG
        GLX_CONTEXT_FLAGS_ARB,GLX_CONTEXT_DEBUG_BIT_ARB | GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,   /*  Debug TODO add hint*/
        #else
        GLX_CONTEXT_FLAGS_ARB, GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
        #endif
        None
    };

	if(!glXQueryExtension(display,&dummy, &dummy)){
		ExError("OpenGL not supported by X server\n");
    }

	if(isExtensionSupported(glXQueryExtensionsString(display,DefaultScreen(display)), "GLX_ARB_create_context")){
		typedef GLXContext (*glXCreateContextAttribsARBProc)(Display*, GLXFBConfig, GLXContext, Bool, const int*);
		glXCreateContextAttribsARBProc glXCreateContextAttribsARB = (glXCreateContextAttribsARBProc)glXGetProcAddress((const GLubyte*)"glXCreateContextAttribsARB");

        glXGetProcAddress("glXCreateAssociatedContextAMD"); /*  AMD */

		if(glXCreateContextAttribsARB){
			choose_fbconfig(&fbconfig);

			glc = glXCreateContextAttribsARB(display, fbconfig,0, True,context_attribs);
            glXMakeCurrent(display, window,glc);
			XSync(display,False);
		}
	}
	else{   /*      */
		int att[60] = {0};
		ExCreateContextAttrib(0,&att[0],0,EX_OPENGL);
		vi = glXChooseVisual(display,DefaultScreen(display),att);

		glc = glXCreateContext(display,vi,0,True);
	}
	/*

	*/
	if(!glc){
        glc = glXCreateNewContext(display, fbconfig, GLX_RGBA_TYPE,0,True);
	}
	if(!glXIsDirect(display, glc))
        fprintf(stderr,"Indirect GLX rendering context obtained\n");    /*a lose of performance.*/
	return glc;
#elif defined(EX_ANDROID)

    return ExCreateOpenGLES(window);
#elif defined(EX_NACL)
    PPB_GetInterface inter;
    glInitializePPAPI(inter);

#endif
}

/**
    \Create Shared OpenGL Context from a already existing context.
*/
DECLSPEC OpenGLContext ELTAPIENTRY ExCreateGLSharedContext(ExWin window, OpenGLContext glc){
    int major_version,minor_version;
    OpenGLContext shared_glc;

#if defined(EX_LINUX)
    typedef GLXContext (*glXCreateContextAttribsARBProc)(Display*, GLXFBConfig, GLXContext, Bool, const int*);
    GLXFBConfig fbconfig;
    glXCreateContextAttribsARBProc glXCreateContextAttribsARB;
    glGetIntegerv(GL_MAJOR_VERSION, &major_version);
	glGetIntegerv(GL_MINOR_VERSION, &minor_version);

    /*  query OpenGL context fbconfig id*/
    glXQueryContext(display, glc, GLX_FBCONFIG_ID, &fbconfig);


    int context_attribs[]={
        GLX_CONTEXT_MAJOR_VERSION_ARB,major_version,
        GLX_CONTEXT_MINOR_VERSION_ARB,minor_version,
        #ifdef EX_DEBUG
        GLX_CONTEXT_FLAGS_ARB,GLX_CONTEXT_DEBUG_BIT_ARB | GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,   /*  Debug TODO add hint*/
        #else
        GLX_CONTEXT_FLAGS_ARB, GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
        #endif
        None
    };

    /*  Get context ARB */
    glXCreateContextAttribsARB = (glXCreateContextAttribsARBProc)glXGetProcAddress((const GLubyte*)"glXCreateContextAttribsARB");

    if(glXCreateContextAttribsARB)
        shared_glc = glXCreateContextAttribsARB(display, fbconfig,glc, True,context_attribs);
    else{

    }

    return shared_glc;
    #elif defined(EX_ANDROID)

    #endif
}



DECLSPEC void ELTAPIENTRY ExInitOpenGLStates(EngineDescription* enginedescription){
#if (EX_ENGINE_VERSION_MAJOR < 1 )
#ifdef EX_WINDOWS
	WGLSWAPINTERVALEXT_T wglSwapIntervalEXT = (WGLSWAPINTERVALEXT_T)GL_GET_PROC("wglSwapIntervalEXT");

	ExWin hWnd;	// Window
	RECT rect;	// client Rect
	hWnd = WindowFromDC(wglGetCurrentDC());
	GetClientRect(hWnd,&rect);
	// v-sync
	wglSwapIntervalEXT((engineDescription.EngineFlag & ENGINE_SUPPORT_VSYNC));
	// gl Viewport
	glViewport(0,0,rect.right - rect.left,rect.bottom - rect.top);
#elif defined(EX_LINUX)
    typedef void (*glXSwapIntervalEXTProc)(Display*, GLXDrawable drawable, int intervale);
    glXSwapIntervalEXTProc glXSwapIntervalEXT = (glXSwapIntervalEXTProc)GL_GET_PROC((const GLubyte*)"glXSwapIntervalEXT");
    if(glXSwapIntervalEXT)
        glXSwapIntervalEXT(display, (GLXDrawable)ExGetCurrentGLDC(), 0);
#elif defined(EX_ANDROID)

#endif
#endif
    int sampleSupport;
	// depth
	//glClearDepth(1.0f);
	// color mask
	glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);

	if(engineDescription.alphaChannel > 0)
		glEnable(GL_ALPHA_TEST);
	else glDisable(GL_ALPHA_TEST);

#ifndef EX_ANDROID
    if(engineDescription.sample[0]){
        glEnable(GL_MULTISAMPLE_ARB);
        glGetIntegerv(GL_SAMPLE_BUFFERS,&sampleSupport);
        if(sampleSupport){}
    }
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
	//glDepthRange(0.0, 1.0);
	glDepthMask(GL_TRUE);
	glPolygonOffset(0.0f, 0.0f);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CW);
	glClearColor(0.0f,0.0f,0.0f,1.0f);
#ifndef EX_ANDROID
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
#endif
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

}

DECLSPEC int ELTAPIENTRY ExDestroyContext(WindowContext drawable, OpenGLContext glc){
	int hr;
	// if hDC is null
	if(!drawable)
		drawable = ExGetCurrentGLDC();
#if defined(EX_LINUX)
    if(!glXMakeCurrent(display, None, NULL)){
        fprintf(stderr,"error");
        return E_ERROR;
    }
	glXDestroyContext(display,glc);
	return hr;
#elif defined(EX_ANDROID)
    return eglDestroyContext(eglDisplay,glc);
#endif
}

/**
    Opengl Fullscreen
*/
DECLSPEC ExBoolean ELTAPIENTRY ExGLFullScreen(ExBoolean cdsfullscreen, ExWin window, Uint32 screenIndex, const Int* screenRes){

#elif defined(EX_LINUX)
    int one = 1;
	XEvent xev = {0};
    XWindowAttributes xwa;
    XSetWindowAttributes xattr;

    xattr.override_redirect = False;
    XChangeWindowAttributes(display, window, CWOverrideRedirect, &xattr);

	Atom wm_state = XInternAtom(display, "_NET_WM_STATE", FALSE);
    Atom fullscreen = XInternAtom(display, "_NET_WM_STATE_FULLSCREEN", FALSE);

    /**/
    XChangeProperty(display,window,  XInternAtom(display,"_NET_WM_STATE", True), XA_ATOM, 32, PropModeReplace,&fullscreen, 1);
    /**/
    XChangeProperty (display, window,
      XInternAtom ( display, "_HILDON_NON_COMPOSITED_WINDOW", True ),
      XA_INTEGER,  32,  PropModeReplace,
      (unsigned char*) &one,  1);


	//XF86VideoModeSwitchToMode(display, screenIndex, modes[bestMode]);
    Atom atoms[2] = { XInternAtom(display, "_NET_WM_STATE_FULLSCREEN", False), None };


	xev.type = ClientMessage;
	xev.xclient.window = window;
	xev.xclient.message_type = wm_state;
	xev.xclient.format = 32;
	xev.xclient.data.l[0] = 1;
	xev.xclient.data.l[1] = fullscreen;


	//XGetWindowAttributes(display, DefaultRootWindow(display),&xwa);
    //ExSetWindowSize(window,xwa.width,xwa.height);
	//XMapWindow(display,window);

    //XChangeProperty(display, window,XInternAtom(display, "_NET_WM_STATE", False), 4, 32, PropModeReplace, atoms,1);
	XSendEvent(display,
            DefaultRootWindow(display),
            FALSE,
            SubstructureNotifyMask,&xev);
	//XSendEvent(display,DefaultRootWindow(window,False,
	//	SubstructureRedirectMask | SubstructureNotifyMask, &xev);


	return TRUE;
#elif defined(EX_ANDROID)


	return TRUE;
#endif
}

DECLSPEC void ELTAPIENTRY ExSetGLTransparent(ExWin window,Enum ienum){
#if defined(EX_LINUX)
	XTextProperty textprop = {0};
	XWMHints *startup_state;
	EX_C_STRUCT exsize size ;
	XSizeHints hints;

	ExGetWindowSizev(window,&size);

    hints.x = 0;
    hints.y = 0;
    hints.width = size.width;
    hints.height = size.height;
    hints.flags = USPosition |USSize;

	startup_state = XAllocClassHint();
	startup_state->initial_state = NormalState;
    startup_state->flags = StateHint;

    XSetWMProperties(display,window, &textprop, &textprop, NULL, 0, &hints,  startup_state, NULL );
    XFree(startup_state);
#elif defined(EX_ANDROID)

#endif
}


DECLSPEC Uint32 ELTAPIFASTENTRY ExGetOpenGLShadingVersion(void){
	return (Uint32)(atof((const char*)glGetString(GL_SHADING_LANGUAGE_VERSION)) * 100.0f);
}

DECLSPEC Uint32 ELTAPIFASTENTRY ExGetOpenGLVersion(int* major,int* minor){
    if(!ExGetCurrentOpenGLContext()){
	/*	create temp*/
	unsigned int version;
	OpenGLContext glc;
	//glc = ExCreateTempGLContext();
	version = (atof((const char*)glGetString(GL_VERSION)) * 100.0f);
	if(major)
		glGetIntegerv(GL_MAJOR_VERSION, major);
	if(minor)
		glGetIntegerv(GL_MINOR_VERSION, minor);

	//ExDestroyContext(glc);
	return version;
    }
    else{
	if(major)
		glGetIntegerv(GL_MAJOR_VERSION, major);
	if(minor)
		glGetIntegerv(GL_MINOR_VERSION, minor);

        return (Uint32)(atof((const char*)glGetString(GL_VERSION)) * 100.0f);
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
