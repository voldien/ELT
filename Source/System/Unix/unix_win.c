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
#undef glXChooseFBConfig
#undef glXGetVisualFromFBConfig
#undef glXGetFBConfigs
#undef glXGetFBConfigAttrib
#undef glXCreateWindow
#include<GL/gl.h>
#include<GL/glx.h>
#include"../elt_gl.h"


Display *display = EX_NULL;
DECLSPEC XID ELTAPIENTRY ExCreateNativeWindow(Int32 x, Int32 y, Int32 width, Int32 height){
	Visual* visual;
	Int depth, text_x,text_y;
	XSetWindowAttributes swa = {};
	Window window;
	XFontStruct* fontinfo;
	XGCValues gr_values;
	GC graphical_context;
	ExChar title[260];

	visual = DefaultVisual(display, 0);
	depth = DefaultDepth(display,0);

	swa.background_pixel = XWhitePixel(display,0);
	swa.event_mask = ExposureMask | PointerMotionMask | KeyPressMask;

	window = XCreateWindow(display,DefaultRootWindow(display),
                              x,y,width,height,0,
                              depth,InputOutput,visual, CWBackPixel,&swa);

	XStoreName(display,window, ExGetDefaultWindowTitle(title,sizeof(title)));
	XSelectInput(display,window,ExposureMask | StructureNotifyMask);

	fontinfo = XLoadQueryFont(display, EX_TEXT("10x20"));
	gr_values.font = fontinfo->fid;
	gr_values.foreground = XBlackPixel(display,0);
	graphical_context = XCreateGC(display,window, GCFont + GCForeground, &gr_values);

	XMapWindow(display,window);

	return window;
}
/*
    // Create a Window defined for OpenGL X purpose
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


	winAttribs.event_mask = ExposureMask | VisibilityChangeMask | KeyPressMask | PointerMotionMask | StructureNotifyMask;
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
        pglx_window[0] = 1;
    }

	XStoreName(display,window, ExGetDefaultWindowTitle(title,sizeof(title)));

	//XSelectInput(display,window,ExposureMask | StructureNotifyMask);

	//fontinfo = XLoadQueryFont(display, EX_TEXT("10x20"));
	//gr_values.font = fontinfo->fid;
	//gr_values.foreground = XBlackPixel(display,0);
	//graphical_context = XCreateGC(display,window, GCFont + GCForeground, &gr_values);

    XMapWindow(display,window);
   //XIfEvent(display, &event, WaitFormMap)

    //if((del_atom = XInternAtom(display, "WM_DELETE_WINDOW", 0)) != None){
    //    XSetWMProtocols(display, window, &del_atom, 1);
    //}

	return window;
}/*
DECLSPEC XID ELTAPIENTRY ExCreateSimpleGLWindow(Int32 x , Int32 y, Int32 width, Int32 height){
	Window* root,win;
	Colormap cmap;
	XSetWindowAttributes swa;
	GLXContext glc;
	XVisualInfo* vi;
	ExChar title[260];
	GLint att[60] = {
			GLX_RGBA,
			GLX_RED_SIZE, 8,
			GLX_GREEN_SIZE, 8,
			GLX_BLUE_SIZE, 8,
			GLX_ALPHA_SIZE, 4,
			GLX_DEPTH_SIZE, 24,
			GLX_STENCIL_SIZE, 0,
			GLX_DOUBLEBUFFER,
			None };

	root = DefaultRootWindow(display);

	vi = glXChooseVisual(display,0,att);

	cmap = XCreateColormap(display,root, vi->visual,AllocNone);

	swa.colormap = cmap;
	swa.event_mask = ExposureMask | KeyPressMask;

	win = XCreateWindow(display,root, x, y, width,height,0,vi->depth,InputOutput, vi->visual,CWColormap | CWEventMask, &swa);


	XStoreName(display,win, ExGetDefaultWindowTitle(title, sizeof(title)));
	XMapWindow(display,win);

	return win;
}*/


#endif
