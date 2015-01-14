#include"unix_win.h"
#ifdef EX_LINUX
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<X11/Xlib.h>
#include<X11/Xatom.h>
#include<X11/keysym.h>
#include<X11/extensions/XInput.h>
#include<X11/extensions/Xrender.h>
#include<dlfcn.h>
#include<GL/gl.h>
#include<GL/glx.h>
#include"../elt_gl.h"
//mathlib
Display *display = 0;


extern int choose_fbconfig(GLXFBConfig* p_fbconfig);

DECLSPEC XID ELTAPIENTRY ExCreateNativeWindow(Int32 x, Int32 y, Int32 width, Int32 height){
	Visual* visual;
	Int depth, text_x,text_y;
	XSetWindowAttributes swa = {};
    XSetWindowAttributes  xattr;
    Atom  atom;
    int   one = 1;
	Window window;
	XFontStruct* fontinfo;
	XGCValues gr_values;
	GC graphical_context;
	ExChar title[260];
	int winmask = 0;


	visual = DefaultVisual(display, 0);
	depth = DefaultDepth(display,0);
    winmask = CWEventMask;
	//swa.background_pixel = XWhitePixel(display,0);
	swa.event_mask = ExposureMask | PointerMotionMask | KeyPressMask;

	window = XCreateWindow(display,DefaultRootWindow(display),
                              x,y,width,height,0,
                              depth,InputOutput,visual, winmask,&swa);

	XStoreName(display,window, ExGetDefaultWindowTitle(title,sizeof(title)));

    xattr.override_redirect = False;
    XChangeWindowAttributes (display, window, CWOverrideRedirect, &xattr );
	//XSelectInput(display,window,ExposureMask | StructureNotifyMask);

    /*

    */
	fontinfo = XLoadQueryFont(display, EX_TEXT("10x20"));
	gr_values.font = fontinfo->fid;
	gr_values.foreground = XBlackPixel(display,0);
	graphical_context = XCreateGC(display,window, GCFont + GCForeground, &gr_values);

	return window;
}
/**
    Create a Window defined for OpenGL X purpose
*/
DECLSPEC XID ELTAPIENTRY ExCreateGLWindow(Int32 x , Int32 y, Int32 width, Int32 height, void** pglx_window){
	Visual* visual;

	XVisualInfo* vi;
	GLXFBConfig fbConfigs;
	Int depth, text_x,text_y;
	int screen;
	int major,minor;
	Int32 winmask;
	XSetWindowAttributes winAttribs = {0};
	Window window;
	Window* root;
	GLXWindow* glx_window;
	XFontStruct* fontinfo;
	XGCValues gr_values;
	GC graphical_context;
	Colormap cmap;
    Atom del_atom;
	ExChar title[260];
	int VisData[60];
    XRenderPictFormat *pict_format;
	int numfbconfigs,i;
    int num;

    /*
        create attribute
    */
    ExCreateContextAttrib(0,&VisData[0],0,0,EX_OPENGL);

	screen = DefaultScreen(display);
	root = RootWindow(display,screen);
    /*

    */
	if(!glXQueryVersion(display,&major,&minor))
        fprintf(stderr,"could not");



	GLXFBConfig* fbconfigs = glXChooseFBConfig(display,screen, &VisData[0],&numfbconfigs);
    fbConfigs = 0;
	for(i = 0; i < numfbconfigs; i++){
		vi = (XVisualInfo*)glXGetVisualFromFBConfig(display, fbconfigs[i]);

		if(!vi)continue;

		pict_format = XRenderFindVisualFormat(display, vi->visual);
		if(!pict_format)continue;

        fbConfigs = fbconfigs[i];

        if(engineDescription.alphaChannel > 0){
            if(pict_format->direct.alphaMask > 0)break;
        }else break;

	}
    //vi = (XVisualInfo*)glXGetVisualFromFBConfig(display, fbconfigs[0]);


	winAttribs.event_mask = ExposureMask | VisibilityChangeMask | KeyPressMask | PointerMotionMask | StructureNotifyMask | ResizeRedirectMask;
	winAttribs.border_pixel = 0;
	winAttribs.bit_gravity = StaticGravity;

	winAttribs.colormap = XCreateColormap(display, RootWindow(display,vi->screen), vi->visual, AllocNone);

	winmask  = CWBorderPixel | CWBitGravity | CWEventMask| CWColormap;
	window = XCreateWindow(display,
                              root,
                              x,y,width,height,
                              0,
                              vi->depth,
                              InputOutput,
                              vi->visual,
                                winmask,&winAttribs);
	/**
        problems was it was a random pointer as a value....
	*/
    if(major >= 1 && minor >= 3){
        //glx_window = glXCreateWindow(display, fbConfigs,window,0);
        //pglx_window[0] = glx_window;
        if(pglx_window)
            pglx_window[0] = 1;
    }

	XStoreName(display,window, ExGetDefaultWindowTitle(title,sizeof(title)));
    /*
        event feed masking
    */
	XSelectInput(display,window,ExposureMask | KeyPressMask | ButtonPressMask | KeyReleaseMask | ButtonReleaseMask |  StructureNotifyMask | ButtonMotionMask | PointerMotionMask);

/*
    TODO
    SOLVE LATER
*/
//XGrabPointer(display, root, False, ButtonPressMask, GrabModeAsync,
//         GrabModeAsync, None, None, CurrentTime);


	fontinfo = XLoadQueryFont(display, EX_TEXT("10x20"));
	gr_values.font = fontinfo->fid;
	gr_values.foreground = XBlackPixel(display,0);
	graphical_context = XCreateGC(display,window, GCFont + GCForeground, &gr_values);

   //XIfEvent(display, &event, WaitFormMap)

    //if((del_atom = XInternAtom(display, "WM_DELETE_WINDOW", 0)) != None){
    //    XSetWMProtocols(display, window, &del_atom, 1);
    //}
    XFlush(display);
	return window;
}


DECLSPEC int ExSupportOpenGL(void){
    int major,minor;
	if(!glXQueryVersion(display,&major,&minor)){
        fprintf(stderr,"could not");
        return FALSE;
    }
    return TRUE;
}
#endif
