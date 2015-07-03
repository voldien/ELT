#include"system/unix/unix_win.h"
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
#include"system/elt_gl.h"
void* display = 0;


extern int* pixAtt;
extern int ExChooseFBconfig(GLXFBConfig* p_fbconfig);



DECLSPEC ExWin ELTAPIENTRY ExCreateNativeWindow(Int32 x, Int32 y, Int32 width, Int32 height){
	Visual* visual;
	Int depth, text_x,text_y;
	XSetWindowAttributes swa = {};
    XSetWindowAttributes  xattr;
    Atom  atom;
    int   one = 1;
    int screen;
	Window window;
	XFontStruct* fontinfo;
	XGCValues gr_values;
	GC graphical_context;
	ExChar title[260];
	int winmask = 0;
	XVisualInfo vis_info;


	visual = DefaultVisual(display, 0);
	depth = DefaultDepth(display,0);
	screen = DefaultScreen(display);
    winmask = CWEventMask;

    if(!XMatchVisualInfo(display, screen , depth, TrueColor,&vis_info)){

    }
    visual = vis_info.visual;

	swa.background_pixel = XWhitePixel(display,0);
	swa.event_mask =  ExposureMask | VisibilityChangeMask | KeyPressMask | PointerMotionMask | StructureNotifyMask | ResizeRedirectMask;
	swa.border_pixel = 0;
	swa.bit_gravity = StaticGravity;

	swa.colormap = XCreateColormap(display, RootWindow(display,vis_info.screen), vis_info.visual, AllocNone);


	window = XCreateWindow(display,DefaultRootWindow(display),
                              x,y,width,height,0,
                              depth,InputOutput,visual, winmask,&swa);

	XStoreName(display,window, "default");

    xattr.override_redirect = False;
    XChangeWindowAttributes (display, window, CWOverrideRedirect, &xattr );
	//XSelectInput(display,window,ExposureMask | StructureNotifyMask);


    /*	*/
	fontinfo = XLoadQueryFont(display, EX_TEXT("10x20"));
	gr_values.font = fontinfo->fid;
	gr_values.foreground = XBlackPixel(display,0);
	graphical_context = XCreateGC(display,window, GCFont + GCForeground, &gr_values);

	return window;
}

/**
    Create a Window defined for OpenGL X purpose
*/
DECLSPEC ExWin ELTAPIENTRY ExCreateGLWindow(Int32 x , Int32 y, Int32 width, Int32 height, void** pglx_window){
	Visual* visual;
	XVisualInfo* vi;
	int depth, text_x,text_y;
	int screen;
	int major,minor;
	Int32 winmask = 0;
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
	GLXFBConfig fbconfigs;
	int VisData[60];
    XRenderPictFormat *pict_format;
	int numfbconfigs,i;
    int num;


	screen = DefaultScreen(display);
	root = RootWindow(display,screen);

	/*	*/
	if(!glXQueryVersion(display,&major,&minor))
        fprintf(stderr,"could not");


	ExChooseFBconfig(&fbconfigs);
	vi = (XVisualInfo*)glXGetVisualFromFBConfig(display, fbconfigs);


	winAttribs.colormap = XCreateColormap(display, RootWindow(display,vi->screen), vi->visual, AllocNone);

	winAttribs.event_mask = ExposureMask | VisibilityChangeMask | KeyPressMask | PointerMotionMask | StructureNotifyMask | ResizeRedirectMask;
	winAttribs.border_pixmap = None;
	winAttribs.border_pixel = 0;
	winAttribs.bit_gravity = StaticGravity;


	winmask  =CWBackPixmap|
	        CWColormap|
	        CWBorderPixel|
	        CWEventMask;

	window = XCreateWindow(display,
                              root,
                              x,y,width,height,
                              0,
                              vi->depth,
                              InputOutput,
                              vi->visual,
                                winmask,&winAttribs);

	/*	problems was it was a random pointer as a value....	*/
    if(major >= 1 && minor >= 3 && pglx_window){
    	/*glXCreateWindow create opengl for window that might not have capability for OpenGL*/
    	pglx_window[0]= glXCreateWindow(display, fbconfigs,window,0);
    }

	XStoreName(display,window, "default");

    /*	event feed masking	*/
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
    //XFlush(display);
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
