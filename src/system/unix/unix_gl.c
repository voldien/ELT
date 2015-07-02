#include"system/elt_gl.h"
#include<X11/extensions/Xrender.h>

#include<X11/Xatom.h>
#include<X11/keysym.h>
#include<EGL/egl.h>
#include<EGL/eglext.h>

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
#else
	#include<GL/glx.h>
	#include<GL/glxext.h>
	#include<GL/glu.h>
#endif

#define GL_GET_PROC(x) glXGetProcAddress( ( x ) )           /**  get OpenGL function process address */



extern int isExtensionSupported(const char* extList, const char* extension);



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

DECLSPEC OpenGLContext ELTAPIENTRY ExCreateTempGLContext(void){
	OpenGLContext glc;
#ifdef EX_LINUX
	GLXFBConfig fbconfig;
	choose_fbconfig(&fbconfig);
	glc = glXCreateNewContext(display, fbconfig, GLX_RGBA_TYPE,0,1);
#endif;
	return glc;
}




void ELTAPIENTRY ExCreateContextAttrib(WindowContext hDc, Int32* attribs,Int32* size,Enum erenderingflag){
	if(!attribs)	/* error */
		ExSetError(EINVAL);

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


         int pixAttribs[] = {
				GLX_RENDER_TYPE, GLX_RGBA_BIT,
              			GLX_X_RENDERABLE, True,
              	GLX_X_VISUAL_TYPE, GLX_TRUE_COLOR,
            	GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
                          GLX_RED_SIZE,    8,
                          GLX_GREEN_SIZE,  8,
                          GLX_BLUE_SIZE,   8,
                          GLX_ALPHA_SIZE,  8,
             			GLX_DOUBLEBUFFER, True,
                          GLX_DEPTH_SIZE,  24,
                          None};

	//	Int32 pixAttribs[] = {
            //    GLX_RENDER_TYPE, GLX_RGBA_BIT,
              //  GLX_X_RENDERABLE, True,
              //  GLX_X_VISUAL_TYPE, GLX_TRUE_COLOR,
            //    GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
             //   GLX_DOUBLEBUFFER, True,
             //   GLX_AUX_BUFFERS, 0,
                /**/
             //   GLX_RED_SIZE, 1,
             //   GLX_GREEN_SIZE, 1,
              //  GLX_BLUE_SIZE, 1,
             //   GLX_ALPHA_SIZE,engineDescription.alphaChannel,
              //  GLX_DEPTH_SIZE, 1,
               // GLX_STENCIL_SIZE,engineDescription.StencilBits,

                //GLX_STEREO,0,
                //GLX_SAMPLE_BUFFERS_ARB,engineDescription.sample[0] != 0 ? 1 : 0,
                //GLX_SAMPLES_ARB,engineDescription.sample[0],
                //GLX_TRANSPARENT_TYPE, GLX_TRANSPARENT_RGB,
                //None,
				/*
			//GLX_TRANSPARENT_ARB, WGL_TRANSPARENT_ALPHA_VALUE_ARB,,*/
		//}; // NULL termination
		if(size)size =sizeof(pixAttribs);
		memcpy(attribs,(int*)pixAttribs,sizeof(pixAttribs));

	}
}


DECLSPEC OpenGLContext ELTAPIENTRY ExCreateGLContext(ExWin window){
	OpenGLContext glc = NULL;
	unsigned int render_vendor;



	XVisualInfo* vi;		//	Visual Info
	int dummy, min,maj, major_version, minor_version;
	GLXFBConfig fbconfig;
    glXQueryVersion(display,&maj,&min);


    /*	Get Current Supported Version of OpenGL	*/
    if(!ExGetOpenGLVersion(&major_version, &minor_version)){
    	/*	bad	*/
    }


	/*if windows doesn't support the opengl, than try to use */

    int context_attribs[]={
        GLX_CONTEXT_MAJOR_VERSION_ARB,major_version,
        GLX_CONTEXT_MINOR_VERSION_ARB,minor_version,
        #ifdef EX_DEBUG
        GLX_CONTEXT_FLAGS_ARB,GLX_CONTEXT_DEBUG_BIT_ARB | GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,   /*  Debug TODO add hint*/
        #else
        GLX_CONTEXT_FLAGS_ARB, GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
        #endif
		//GLX_CONTEXT_PROFILE_MASK_ARB,GLX_CONTEXT_CORE_PROFILE_BIT_ARB,
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
			//TODO resolve
			//glc = glXCreateContextAttribsARB(display, fbconfig,0, True,context_attribs);
			XSync(display, False );
		}
	}
	/*else{
		int att[60] = {0};
		ExCreateContextAttrib(0,&att[0],0,EX_OPENGL);
		vi = glXChooseVisual(display,DefaultScreen(display),att);

		glc = glXCreateContext(display,vi,0,True);
	}*/
	/*

	*/
	if(!glc){
		glc = glXCreateNewContext(display, fbconfig, GLX_RGBA_TYPE,0,True);
	}
	if(!glXIsDirect(display, glc))
        fprintf(stderr,"Indirect GLX rendering context obtained\n");    /*a lose of performance.*/

/*
	if (!glXMakeContextCurrent(Xdisplay, glX_window_handle, glX_window_handle, render_context)) {
        fatalError("glXMakeCurrent failed for window\n");
    	}
*/
	return glc;
    //TODO


}


DECLSPEC OpenGLContext ELTAPIENTRY ExCreateGLSharedContext(ExWin window, OpenGLContext glc){
    int major_version,minor_version;
    OpenGLContext shared_glc;

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
}



DECLSPEC ExBoolean ELTAPIENTRY ExDestroyContext(WindowContext drawable, OpenGLContext glc){
	ExBoolean hr;
	// if hDC is null
	if(!drawable)
		drawable = ExGetCurrentGLDC();

    if(!glXMakeCurrent(display, None, NULL)){
        fprintf(stderr,"error");
        return E_ERROR;
    }
	glXDestroyContext(display,glc);
	return hr;

    //return eglDestroyContext(eglDisplay,glc);

}

DECLSPEC ExBoolean ELTAPIENTRY ExGLFullScreen(ExBoolean cdsfullscreen, ExWin window, Uint32 screenIndex, const Int* screenRes){


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

}
DECLSPEC void ELTAPIENTRY ExSetGLTransparent(ExWin window,Enum ienum){

	XTextProperty textprop = {0};
	XWMHints *startup_state;
	EX_C_STRUCT exsize size;
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

}


