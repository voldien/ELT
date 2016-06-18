#include"system/unix/unix_win.h"
#include<unistd.h>


#include<EGL/egl.h>
#include<GL/glx.h>
#include<X11/extensions/dpms.h>

#include <X11/X.h>
#include<X11/Xlib.h>
#include<X11/Xatom.h>
#include<X11/keysym.h>

//#include<X11/extensions/XInput.h>
//#include<X11/extensions/Xrender.h>

#include<dlfcn.h>
#include<GL/gl.h>
#include<GL/glx.h>
#include"system/elt_gl.h"


#ifndef _NET_WM_STATE_ADD
	#define _NET_WM_STATE_ADD	1
#endif

ExDisplay display = 0;
void* m_connection = 0;		/*	TODO take a loke*/
extern int* pixAtt;
extern int ExChooseFBconfig(GLXFBConfig* pfbconfig);

ExWin ExCreateNativeWindow(Int32 x, Int32 y, Int32 width, Int32 height){
	Visual* visual;
	Int depth;
	Int textX;
	Int textY;
	XSetWindowAttributes swa = {};
    XSetWindowAttributes  xattr;
    Atom atom;
    int one = 1;
    int screen;
	Window window;
	XFontStruct* fontinfo;
	XGCValues grValues;
	GC gc;
	int winmask = 0;
	XVisualInfo visInfo;


	visual = DefaultVisual(display, 0);
	depth = DefaultDepth(display,0);
	screen = DefaultScreen(display);
    winmask = CWEventMask;

    if(!XMatchVisualInfo(display, screen , depth, TrueColor, &visInfo)){
    	/**/

    }
    visual = visInfo.visual;
    /**/
	swa.background_pixel = XWhitePixel(display,0);
	swa.event_mask = ExposureMask | VisibilityChangeMask | KeyPressMask | PointerMotionMask | StructureNotifyMask | ResizeRedirectMask | VisibilityChangeMask;
	swa.border_pixmap = None;
	swa.border_pixel = 0;
	swa.bit_gravity = StaticGravity;
	/**/
	swa.colormap = XCreateColormap(display, RootWindow(display,visInfo.screen), visInfo.visual, AllocNone);

	/**/
	window = XCreateWindow(display,DefaultRootWindow(display),
                              x,y,width,height,0,
                              depth,InputOutput,visual, winmask,&swa);

    /*	event feed masking	*/
	XSelectInput(display,window, ExposureMask | VisibilityChangeMask | KeyPressMask |
			PointerMotionMask | StructureNotifyMask | ExposureMask | KeyPressMask |
			ButtonPressMask | KeyReleaseMask | ButtonReleaseMask |  StructureNotifyMask | VisibilityChangeMask |
			ButtonMotionMask | PointerMotionMask);


    /*	*/
	fontinfo = XLoadQueryFont(display, EX_TEXT("10x20"));
	grValues.font = fontinfo->fid;
	grValues.foreground = XBlackPixel(display,0);
	gc = XCreateGC(display,window, GCFont + GCForeground, &grValues);

	/**/
    xattr.override_redirect = False;
    XChangeWindowAttributes (display, window, CWOverrideRedirect, &xattr );


	XSync(display, FALSE);
	return window;
}

ExWin ExCreateGLWindow(Int32 x , Int32 y, Int32 width, Int32 height, void** pglx_window){
	XVisualInfo* vi;
	int screen;
	int major;
	int minor;
	Int32 winmask = 0;
	XSetWindowAttributes winAttribs = {0};
	Window window;
	Window* root;
	XFontStruct* fontinfo;
	XGCValues gr_values;
	GC graphical_context;
	Colormap cmap;
    Atom delMsg;
	GLXFBConfig fbconfigs;
	ExRect rect = {0};


	screen = DefaultScreen(display);
	root = RootWindow(display, screen);


	if(!ExSupportOpenGL())
		return NULL;


	glXQueryVersion(display, &major, &minor);

	/*	choose visualinfo */
	ExChooseFBconfig(&fbconfigs);
	vi = (XVisualInfo*)glXGetVisualFromFBConfig(display, fbconfigs);


	winAttribs.colormap = XCreateColormap(display, RootWindow(display,vi->screen), vi->visual, AllocNone);

	winAttribs.event_mask = ExposureMask | VisibilityChangeMask | KeyPressMask | PointerMotionMask | StructureNotifyMask | ResizeRedirectMask | FocusChangeMask;
	winAttribs.border_pixmap = None;
	winAttribs.border_pixel = 0;
	winAttribs.bit_gravity = StaticGravity;


	winmask = CWBackPixmap|
	        CWColormap|
	        CWBorderPixel|
	        CWEventMask;

	/*	TODO resolve why x and y position is bad. probarly because of multi screencd .	*/
	ExGetPrimaryScreenRect(&rect);
	window = XCreateWindow(display,
                              root,
                              rect.x + x, rect.y + y, width, height,
                              0,
                              vi->depth,
                              InputOutput,
                              vi->visual,
                                winmask, &winAttribs);




	/*	problems was it was a random pointer as a value....	*/
    if( ( major >= 1 && minor >= 3 && pglx_window) ){

    	/*glXCreateWindow create opengl for window that might not have capability for OpenGL	*/
    	pglx_window[0] = NULL;
    	//pglx_window[0] = glXCreateWindow(display, fbconfigs, window, 0);
    }

    /*	event feed masking	*/
	XSelectInput(display,window, ExposureMask | VisibilityChangeMask | KeyPressMask |
			PointerMotionMask | StructureNotifyMask | ExposureMask | KeyPressMask | ResizeRedirectMask |
			ButtonPressMask | KeyReleaseMask | ButtonReleaseMask |  StructureNotifyMask | FocusChangeMask |
			ButtonMotionMask | PointerMotionMask);

/*
    TODO
    SOLVE LATER
*/
	//XGrabPointer(display, root, False, ButtonPressMask, GrabModeAsync,
	//         GrabModeAsync, None, None, CurrentTime);


	/*	create window font	*/
	fontinfo = XLoadQueryFont(display, EX_TEXT("-*-helvetica-*-r-*-*-14-*-*-*-*-*-*-*"));
	if(!fontinfo){
		fontinfo = XLoadQueryFont(display, EX_TEXT("fixed"));
	}
	gr_values.font = fontinfo->fid;
	gr_values.foreground = XBlackPixel(display,0);
	gr_values.background = WhitePixel(display,0);
	graphical_context = XCreateGC(display,window, GCFont + GCForeground, &gr_values);
	XSetFont(display, graphical_context, gr_values.font);
	/*	free font struct.	*/



   //XIfEvent(display, &event, WaitFormMap)


	XFree(vi);
	XFree(graphical_context);
	XFreeFont(display, fontinfo);
	XSync(display, FALSE);
	return window;
}

int ExSupportOpenGL(void){
    int major;
    int minor;

    /*	TODO evaluate this.	*/
	if(!glXQueryVersion(display, &major, &minor)){
        fprintf(stderr,"could not");
        return FALSE;
    }
    return TRUE;
}











/*	=============================================================	*/
/*					generic window implementation					*/
/*	=============================================================	*/

void ExShowWindow(ExWin window){
    XRaiseWindow(display, (Window)window);
	XMapWindow(display, (Window)window);
}

void ExHideWindow(ExWin window){
    XUnmapWindow(display,window);
}

void ExCloseWindow(ExWin window){
    XDestroyWindow(display, window);
}

void ExMaximizeWindow(ExWin window){
	XEvent xev;
	Atom wm_state = XInternAtom(display, "_NET_WM_STATE", False);
	Atom max_horz = XInternAtom(display, "_NET_WM_STATE_MAXIMIZED_HORZ", False);
	Atom max_vert = XInternAtom(display, "_NET_WM_STATE_MAXIMIZED_VERT", False);

	memset(&xev,0,sizeof(xev));
	xev.type = ClientMessage;
	xev.xclient.window = window;
	xev.xclient.message_type = wm_state;
	xev.xclient.format = 32;
	xev.xclient.data.l[0] = _NET_WM_STATE_ADD;
	xev.xclient.data.l[1] = max_horz;
	xev.xclient.data.l[2] = max_vert;

	XSendEvent(display, DefaultRootWindow(display), False, SubstructureNotifyMask, &xev);
}

void ExMinimizeWindow(ExWin window){
	XEvent xev;
	Atom wm_state = XInternAtom(display, "_NET_WM_STATE", False);
	Atom min_horz = XInternAtom(display, "_NET_WM_STATE_MINIMIZE_HORZ", False);
	Atom min_vert = XInternAtom(display, "_NET_WM_STATE_MINIMIZE_VERT", False);

	memset(&xev,0,sizeof(xev));
	xev.type = ClientMessage;
	xev.xclient.window = window;
	xev.xclient.message_type = wm_state;
	xev.xclient.format = 32;
	xev.xclient.data.l[0] = _NET_WM_STATE_ADD;
	xev.xclient.data.l[1] = min_horz;
	xev.xclient.data.l[2] = min_vert;

	XSendEvent(display, DefaultRootWindow(display), False, SubstructureNotifyMask, &xev);
}

void ExSetWindowMode(ExWin window, Enum mode){
    if(mode & EX_WIN_SCREENSAVER_ENABLE){

    }
}

ExBoolean ExDestroyWindow(ExWin window){
	return XDestroyWindow(display,(Window*)window);
}


void ExSetWindowTitle(ExWin window,const ExChar* title){
	if(!window || !title)
		return;

	XTextProperty textprop;

	textprop.value = (unsigned char*)title;
	textprop.encoding = XA_STRING;
	textprop.format = 8;
	textprop.nitems = strlen(title);

	XSetWMProperties(display, window,&textprop, &textprop,
				NULL, 0,
				NULL,
				NULL,
				NULL);
}

ExChar* ExGetWindowTitle(ExWin window, ExChar* title){
	if(!window || !title)
		return NULL;
	XFetchName(display,(Window*)window,&title);
	return title;
}



void ExSetWindowPos(ExWin window, Int32 x,Int32 y){
	XMoveWindow(display,(Window*)window,x,y);
}

void ExSetWindowPosv(ExWin window, const Int32* position){
	if(!window || !position)
		return;

	XMoveWindow(display,(Window*)window,position[0],position[1]);
}


void ExGetWindowPosv(ExWin window, Int32* position){
	XWindowAttributes xwa;
	XGetWindowAttributes(display, window, &xwa);
	position[0] = xwa.x;
	position[1] = xwa.y;
}

void ExSetWindowSize(ExWin window, Int32 width, Int32 height){
	XResizeWindow(display,window,width,height);
}

void ExSetWindowSizev(ExWin window, const ExSize* size){
	XResizeWindow(display,window,size->width,size->height);
}

void ExGetWindowSizev(ExWin window, ExSize* size){
	XWindowAttributes xwa;
	XGetWindowAttributes(display, window,&xwa);
	size->width = xwa.width;
	size->height= xwa.height;
}

void ExSetWindowRect(ExWin window, const ExRect* rect){
	XMoveWindow(display,(Window)window,rect->x,rect->y);
	XResizeWindow(display,(Window)window,rect->width - rect->x,rect->height - rect->y);
}

void ExGetWindowRect(ExWin window, ExRect* rect){
	XWindowAttributes xwa;
	XGetWindowAttributes(display, (Window*)window,&xwa);
	rect->width = xwa.width;
	rect->height = xwa.height;
	rect->x = xwa.x;
	rect->y= xwa.y;
}


Uint32 ExGetWindowFlag(ExWin window){
    //TODO remove or something
	XWindowAttributes xwa;
	XGetWindowAttributes(display, (Window*)window,&xwa);
	return xwa.all_event_masks;
}


Int32 ExSetWindowIcon(ExWin window, ExHandle hIcon){
     //http://www.sbin.org/doc/Xlib/chapt_03.html
    XWMHints wm_hints = {0};
/*    if (!(wm_hints = XAllocWMHints())) {
      fprintf(stderr, "%s: failure allocating memory", "ELT");
      return FALSE;
    }*/

    Atom net_wm_icon = XInternAtom(display, "_NET_WM_ICON", False);
    Atom cardinal = XInternAtom(display, "CARDINAL", False);


    wm_hints.initial_state = AllHints;
    wm_hints.input = True;
    wm_hints.icon_pixmap = hIcon;
    wm_hints.icon_mask = hIcon;
    wm_hints.flags = IconPixmapHint;
    wm_hints.icon_x = 0x0;
    wm_hints.icon_y = 0x0;
    wm_hints.icon_window = window;

    /**/
    XFlush(display);
    XSetWMHints(display, window, &wm_hints);

	return TRUE;
}

Int32 ExGetWindowIcon(ExWin window){

	Atom iconAtom = XInternAtom(display, "_NET_WM_ICON_NAME", FALSE);
	//XGetWindowProperty(display, window, iconAtom, XA_ATOM, )
    return NULL;
}

Int32 ExSetWindowFullScreen(ExWin window, ExBoolean flag){
    int one = 1;
	XEvent xev = {0};
    XWindowAttributes xwa;
    XSetWindowAttributes xattr;
    Atom fullscreen;
    Atom wmState;
    const int screenIndex = 0;


    xattr.override_redirect = False;
    XChangeWindowAttributes(display, window, CWOverrideRedirect, &xattr);

    /**/
	wmState = XInternAtom(display, "_NET_WM_STATE", FALSE);
    fullscreen = XInternAtom(display, "_NET_WM_STATE_FULLSCREEN", FALSE);

    /**/
    XChangeProperty(display, window,  XInternAtom(display,"_NET_WM_STATE", True), XA_ATOM, 32, PropModeReplace, &fullscreen, 1);
    /**/


    /*XChangeProperty (display, window,
      XInternAtom ( display, "_HILDON_NON_COMPOSITED_WINDOW", True ),
      XA_INTEGER,  32,  PropModeReplace,
      (unsigned char*) &one,  1);
	*/

	//XF86VideoModeSwitchToMode(display, screenIndex, modes[bestMode]);
    Atom atoms[2] = { XInternAtom(display, "_NET_WM_STATE_FULLSCREEN", False), None };


	xev.type = ClientMessage;
	xev.xclient.window = window;
	xev.xclient.message_type = wmState;
	xev.xclient.format = 32;
	xev.xclient.data.l[0] = (flag & TRUE) ? 1 : 0;
	xev.xclient.data.l[1] = fullscreen;
	xev.xclient.data.l[2] = screenIndex;
	xev.xclient.data.l[3] = screenIndex;
	xev.xclient.data.l[4] = screenIndex;

	XSendEvent(display,
            DefaultRootWindow(display),
            FALSE,
            SubstructureNotifyMask
			|SubstructureRedirectMask
			,&xev);
	//XSendEvent(display,DefaultRootWindow(window,False,
	//	SubstructureRedirectMask | SubstructureNotifyMask, &xev);


	return TRUE;
}

ExHandle ExGetWindowUserData(ExWin window){
	ExHandle data;
	//XAssoc a;
	//XGetWindowProperty(display,window,NULL,0,0,0,0,)
	//XAssocTable table;
	//XLookUpAssoc(display, &table, window);
	return data;
}

void ExSetWindowUserData(ExWin window, ExHandle userdata){
	//XGetWindowProperty(display,window,NULL,0,0,0,0,)
	//XAssocTable table;
	//XLookUpAssoc(display, &table, window);
}




Int32 ExSetWindowParent(ExWin parent, ExWin window){
	int pos[2];
	ExGetWindowPosv(parent, pos);
	return XReparentWindow(display, window, parent, 0, 0);
}

ExWin ExGetWindowParent(ExWin window){

	int screen = DefaultScreen(display);
	ExWin root = RootWindow(display,screen);
	ExWin parent;
	ExWin* children;
	ExWin win;
	int n;

	XQueryTree(display, window, &win, &parent, &children, &n);
	return parent;

}

Int32 ExSetWindowChild(ExWin window,ExWin child){
	Int32 pos[2];
	ExGetWindowPosv(window,pos);
	return XReparentWindow(display,child,window,pos[0],pos[1]);
}

ExWin ExGetWindowChild(ExWin window,unsigned int index){
	int screen = DefaultScreen(display);
	ExWin root = RootWindow(display,screen);
	ExWin parent;
	ExWin* children;
	ExWin win;
	int n;

	XQueryTree(display, window, &win, &parent, &children, &n);
	return children[index];

}

Int32 ExGetWindowNumChildren(ExWin window){

	int screen = DefaultScreen(display);
	ExWin root = RootWindow(display,screen);
	ExWin parent;
	ExWin* children;
	ExWin win;
	int n;

	XQueryTree(display, window, &win, &parent, &children, &n);
	return n;
}



ExWin ExGetDesktopWindow(void){

	int i;
	unsigned int n;
	int screen = DefaultScreen(display);
	ExWin win = RootWindow(display,screen);
	ExWin root = RootWindow(display,screen);
	ExWin troot, parent, *children;
	char *name;
	int status;
	int width  = DisplayWidth (display, screen);
	int height = DisplayHeight (display, screen);
	ExWin desktop;
	XWindowAttributes attrs;
	Atom workeara;

	workeara = XInternAtom(display, "_NET_WORKAREA", False);


	#define DEFAULT_DESKTOP_WINDOW_NAME "Desktop"
	XQueryTree(display, root, &troot, &parent, &children, &n);
	for (i = 0; i < (int) n; i++){
		status = XFetchName(display, children[i], &name);
		status |= XGetWindowAttributes(display, children[i], &attrs);
		if ((status != 0) && (NULL != name)){
			if( (attrs.map_state != 0) && (attrs.width == width) &&
					(attrs.height == height) && (!strcmp(name, DEFAULT_DESKTOP_WINDOW_NAME)) ){
				//DEBUG_MSG("Found Window:%s\n", name);
				win = children[i];
				XFree(children);
				XFree(name);
				desktop = win;
				return win;
			}
			if(name){
				XFree(name);
			}
		}
	}
	return (ExWin)0x280000a;
}

ExWin ExGetRootWindow(void){
	return RootWindow(display, DefaultScreen(display));
}
















typedef struct{
    int x, y;
    unsigned int width, height;
    int textx, texty;
    int mouseover;
    int clicked;
    const char* text;
}button;



static void draw_button( button* b, int fg, int bg, Display* dpy, Window w, GC gc ){
    if( b->mouseover ){
        XFillRectangle( dpy, w, gc, b->clicked+b->x, b->clicked+b->y,
                                    b->width, b->height );
        XSetForeground( dpy, gc, bg );
        XSetBackground( dpy, gc, fg );
    }
    else{
        XSetForeground( dpy, gc, fg );
        XSetBackground( dpy, gc, bg );
        XDrawRectangle( dpy, w, gc, b->x, b->y, b->width, b->height );
    }

    XDrawString( dpy, w, gc, b->clicked+b->textx, b->clicked+b->texty,
                 b->text, strlen(b->text) );
    XSetForeground( dpy, gc, fg );
    XSetBackground( dpy, gc, bg );
}

static int is_point_inside( button* b, int px, int py ){

    return px>=b->x && px<=(b->x+(int)b->width-1) &&
           py>=b->y && py<=(b->y+(int)b->height-1);
}



int ExMessageBox(ExWin window, const char* text, const char* title, unsigned int flags){
    const char* wmDeleteWindow = "WM_DELETE_WINDOW";
    int black, white, height = 0, direction, ascent, descent, X, Y, W=0, H;
    size_t i, lines = 0;
    char *atom;
    const char *end, *temp;
    button ok;
    Display* dpy;
    Window w;
    Atom wmDelete;
    GC gc;
    XFontStruct* font;
    XCharStruct overall;
    XSizeHints hints;
    XEvent e;

    /* Open a display */
    if( !(dpy = XOpenDisplay( 0 )) )
        return -1;

    /* Get us a white and black color */
    black = BlackPixel( dpy, DefaultScreen(dpy) );
    white = WhitePixel( dpy, DefaultScreen(dpy) );

    /* Create a window with the specified title */
    w = XCreateSimpleWindow( dpy, DefaultRootWindow(dpy), 0, 0, 100, 100,
                             0, black, black );

    XSelectInput( dpy, w, ExposureMask | StructureNotifyMask |
                          KeyReleaseMask | PointerMotionMask |
                          ButtonPressMask | ButtonReleaseMask );


    ExShowWindow(w);
    ExSetWindowTitle(w,title);

    wmDelete = XInternAtom( dpy, wmDeleteWindow, True );
    XSetWMProtocols( dpy, w, &wmDelete, 1 );

    /* Create a graphics context for the window */
    gc = XCreateGC( dpy, w, 0, 0 );

    XSetForeground( dpy, gc, white );
    XSetBackground( dpy, gc, black );

    /* Compute the printed width and height of the text */
    if( !(font = XQueryFont( dpy, XGContextFromGC(gc) )) )
        goto cleanup;

    for( temp=text; temp; temp = end ? (end+1) : NULL, ++lines )
    {
        end = strchr( temp, '\n' );

        XTextExtents( font, temp, end ? (unsigned int)(end-temp):strlen(temp),
                      &direction, &ascent, &descent, &overall );

        W = overall.width>W ? overall.width : W;
        height = (ascent+descent)>height ? (ascent+descent) : height;
    }

    /* Compute the shape of the window and adjust the window accordingly */
    W += 20;
    H = lines*height + height + 40;
    X = DisplayWidth ( dpy, DefaultScreen(dpy) )/2 - W/2;
    Y = DisplayHeight( dpy, DefaultScreen(dpy) )/2 - H/2;

    XMoveResizeWindow( dpy, w, X, Y, W, H );

    /* Compute the shape of the OK button */
    XTextExtents( font, "OK", 2, &direction, &ascent, &descent, &overall );

    ok.width = overall.width + 30;
    ok.height = ascent + descent + 5;
    ok.x = W/2 - ok.width/2;
    ok.y = H   - height - 15;
    ok.textx = ok.x + 15;
    ok.texty = ok.y + ok.height - 3;
    ok.mouseover = 0;
    ok.clicked = 0;
    ok.text = "OK";

    XFreeFontInfo( NULL, font, 1 ); /* We don't need that anymore */

    /* Make the window non resizeable */
    XUnmapWindow( dpy, w );

    hints.flags      = PSize | PMinSize | PMaxSize;
    hints.min_width  = hints.max_width  = hints.base_width  = W;
    hints.min_height = hints.max_height = hints.base_height = H;

    XSetWMNormalHints( dpy, w, &hints );
    XMapRaised( dpy, w );
    XFlush( dpy );

    /* Event loop */
    while( 1 ){
        XNextEvent( dpy, &e );
        ok.clicked = 0;

        if( e.type == MotionNotify ){
            if( is_point_inside( &ok, e.xmotion.x, e.xmotion.y ) ){
                if( !ok.mouseover )
                    e.type = Expose;

                ok.mouseover = 1;
            }
            else{
                if( ok.mouseover )
                    e.type = Expose;

                ok.mouseover = 0;
                ok.clicked = 0;
            }
        }

        switch( e.type )
        {
        case ButtonPress:
        case ButtonRelease:
            if( e.xbutton.button!=Button1 )
                break;

            if( ok.mouseover )
            {
                ok.clicked = e.type==ButtonPress ? 1 : 0;

                if( !ok.clicked )
                    goto cleanup;
            }
            else
            {
                ok.clicked = 0;
            }

        case Expose:
        case MapNotify:
            XClearWindow( dpy, w );

            /* Draw text lines */
            for( i=0, temp=text; temp; temp=end ? (end+1) : NULL, i+=height )
            {
                end = strchr( temp, '\n' );

                XDrawString( dpy, w, gc, 10, 10+height+i, temp,
                             end ? (unsigned int)(end-temp) : strlen(temp) );
            }

            /* Draw OK button */
            draw_button( &ok, white, black, dpy, w, gc );
            XFlush( dpy );
            break;

        case KeyRelease:
            if( XLookupKeysym( &e.xkey, 0 ) == XK_Escape )
                goto cleanup;
            break;

        case ClientMessage:
            atom = XGetAtomName( dpy, e.xclient.message_type );

            if( *atom == *wmDeleteWindow )
            {
                XFree( atom );
                goto cleanup;
            }

            XFree( atom );
            break;
        }
    }

cleanup:
    XFreeGC( dpy, gc );
    XDestroyWindow( dpy, w );
    XCloseDisplay( dpy );

	return 1;
}


