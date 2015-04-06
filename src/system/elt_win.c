#include"system/elt_win.h"
#include"system/elt_gl.h"
#include"system/elt_cl.h"
#if defined(EX_WINDOWS)
	#include"system/win/win_win32.h"
	#include"system/win/wnd_input.h"
	#include<WindowsX.h>
	#include<EGL/egl.h>
#elif defined(EX_LINUX)
	#include"system/unix/unix_win.h"
	#include<X11/Xlib.h>
	#include<EGL/egl.h>
	#include<GL/glx.h>
	#include<X11/extensions/dpms.h>
#elif defined(EX_ANDROID)
#   include<android/native_window.h>
#   include<android/rect.h>
#   include<android/window.h>
#   include<EGL/egl.h>
#   ifdef GL_ES_VERSION_2_0
        #include<GLES/gl2.h>
        #include<GLES/gl2ext.h>
        #include<GLES/gl2platform.h>
#   else
        #include<GLES/gl.h>
        #include<GLES/glext.h>
        #include<GLES/glplatform.h>
#   endif

#elif defined(EX_MAC)
	#include"system/mac/macosx_win.h"
	#include<EGL/egl.h>
#endif

#include"system/elt_icon.h"
// Ex Create OpenGL ES declaration
extern DECLSPEC void* ELTAPIENTRY ExCreateOpenGLES(ExWin window);


#ifdef EX_DEBUG
#define EX_ENGINE_VERSION_STRING EX_TEXT("ELT Version | %d.%d%d%s | OS : %s : OpenGL %d.%d")
#else
#define EX_ENGINE_VERSION_STRING EX_TEXT("ELT Version | %d.%d%d%s | OS : %s : OpenGL %d.%d")
#endif
DECLSPEC ExChar* ELTAPIENTRY ExGetDefaultWindowTitle(ExChar* text, int length){
	if(!text)return NULL;
	ExChar wchar[260] = {};
	int major_version, minor_version;
#ifdef EX_LINUX
    //glGetIntegerv(GL_MAJOR_VERSION, &major_version);
    //glGetIntegerv(GL_MINOR_VERSION, &minor_version);
    glXQueryVersion(XOpenDisplay(NULL),&major_version,&minor_version);
#elif defined(EX_WINDOWS)
	major_version = minor_version = 0;
#endif
#ifdef EX_UNICODE
	wsprintf(wchar,EX_ENGINE_VERSION_STRING,
#else
	sprintf(wchar,EX_ENGINE_VERSION_STRING,
#endif
		EX_ENGINE_VERSION_MAJOR,
		EX_ENGINE_VERSION_MINOR,
		EX_ENGINE_VERSION_REVISION,
		EX_ENGINE_STATUS,
		ExGetOSName(),
		major_version,
		minor_version);
	memcpy(text, wchar, MAX(sizeof(ExChar) * length + sizeof(ExChar),sizeof(wchar) / sizeof(ExChar)));
	return text;
}

static void* create_elt_icon(ExWin window){
    #ifdef EX_WINDOWS
    HANDLE icon;
    icon = CreateIcon(GetModuleHandle(NULL), GetSystemMetrics(SM_CXICON),GetSystemMetrics(SM_CYICON),1,1,0,0);
    ExSetWindowIcon(window,icon);
    #elif defined(EX_LINUX)
    //http://www.sbin.org/doc/Xlib/chapt_03.html
    Pixmap icon_pixmap;
    //XCreatePixmap(display, window, 128,128,8);
	//icon_pixmap = XCreateBitmapFromData(display, window, ELT_ICON,128,128);
    icon_pixmap = XCreatePixmapFromBitmapData(display, window, ELT_ICON, 128,128,0x0,0x001,1);
    return icon_pixmap;
    #endif
}

/**
    Create Window.
    \x left coordination.
    \y top coordination.
    \width width of the window.
    \height height of the window.
*/
DECLSPEC ExWin ELTAPIENTRY ExCreateWindow(Int32 x, Int32 y, Int32 width,Int32 height, Enum flag){
	ExWin window = 0;
	OpenGLContext glc = 0;
#ifdef EX_WINDOWS
    void* directx;
	if((flag & ENGINE_NATIVE) || flag == 0){
		// create default window
		return ExCreateNativeWindow(x,y,width, height);
	}
	// create window dedicated for OpenGL
	else if(flag & EX_OPENGL){
		window = ExCreateOpenGLWindow(x,y,width, height);
		glc = ExCreateGLContext(window);
		ExMakeGLCurrent(GetDC(window),glc);

		if(flag & EX_OPENCL)
			ExCreateCLSharedContext(glc,GetDC(window),EX_OPENGL);


		return window;
	}
	else if(flag & EX_OPENGLES){
		window = (ExWin)ExCreateNativeWindow(x,y,width,height);
		glc = (OpenGLContext)ExCreateOpenGLES(window);
		ExMakeGLCurrent(GetDC(window),glc);
		if(flag & EX_OPENCL)
			ExCreateCLSharedContext(glc,GetDC(window),EX_OPENGLES);
	}
	else if(flag & EX_OPENCL){
		window = ExCreateNativeWindow(x,y,width,height);
		glc = (OpenGLContext)ExCreateCLContext(ELT_GPU0);
	}
	/**
		//	Create window for directX.
		//	not recommended. because ELT won't be designed for handling DirectX because of a reason
		//	Instead its recommend to create the directX context yourself.
		//	however ELT support DirectX 9 context initialization
	*/
#if  defined(EX_INCLUDE_DIRECTX)
	else if(flag & EX_DIRECTX){
		window = ExCreateDirectXWindow(x,y,width, height);
		directx = (void*)ExInitDirectX(window);
		if(flag & EX_OPENCL)
            ExCreateCLSharedContext((OpenGLContext)directx,GetDC(window),EX_DIRECTX);
		return window;
	}
#endif
	else{
		ExSetError(E_INVALID_ENUM);
		return EX_NULL;
	}
	/**
        Linux Window Implementation
	*/
#elif defined(EX_LINUX)
	if((flag & ENGINE_NATIVE) || !flag){
        /**
            Create Native Window.
        */
		return ExCreateNativeWindow(x,y,width, height);
	}
	else if((flag & EX_OPENGL)){
        void* glx_window; //GLXWindow
		window = ExCreateGLWindow(x,y,width, height,&glx_window);
        glc = ExCreateGLContext(glx_window == NULL ? glx_window : window);
		ExMakeGLCurrent(glx_window != NULL ? glx_window : window,glc);
		ExInitOpenGLStates(NULL);

		ExSetWindowIcon(window,       /*TODO make it works nice*/
        create_elt_icon(window));
		if(flag & EX_OPENCL)
			ExCreateCLSharedContext(glXGetCurrentContext(),window,EX_OPENGL);
		return window;
	}
	else if(flag & EX_OPENGLES){
		window = ExCreateNativeWindow(x,y,width,height);
		glc = ExCreateOpenGLES(window);

		if(flag & EX_OPENCL)
			ExCreateCLSharedContext(glc,eglGetCurrentDisplay(),EX_OPENGLES);
        return window;
	}
	else if(flag & EX_OPENCL){
		window = ExCreateNativeWindow(x,y,width,height);
		glc = ExCreateCLContext(0);
		return window;
	}
#elif defined(EX_MAC)
    /**

    */
	if((flag & ENGINE_NATIVE) || flag == 0){

	}
	else if((flag & ENGINE_OPENGL) || (flag & ENGINE_OPENCL)){

	}
	else
		return EX_NULL;


#elif defined(EX_ANDROID)
    /**
        Android
    */

	if((flag & ENGINE_NATIVE) || flag == 0){
        ANativeWindow_acquire(&window);
	}
	else if(flag & EX_OPENGL){
        ANativeWindow_acquire(&window);
        glc = ExCreateGLContext(window);
        /*
        if(flag & EX_OPENCL)
            ExCreateCLSharedContext(glc, window, EX_OPENGL);
        */
        return window;

	}
	else if(flag & EX_OPENGLES){
        ANativeWindow_acquire(&window);
        glc = ExCreateOpenGLES(window);
        /*
        if(flag & EX_OPENCL)
            ExCreateCLSharedContext(glc, window, EX_OPENGL);
        */
        return window;
	}
	else if(flag & EX_OPENCL){
        ANativeWindow_acquire(&window);
        /*
        ExCreateCLContext(0);
        */
        return window;

	}
	else
		return NULL;
#endif
	return NULL;
}

/*

*/
DECLSPEC void ELTAPIENTRY ExShowWindow(ExWin window){
#ifdef EX_WINDOWS
	ShowWindow(window,SW_SHOW);
#elif defined(EX_LINUX)
    XRaiseWindow(display,window);
	XMapWindow(display,(Window*)window);
#elif defined(EX_ANDROID)

#endif
}
DECLSPEC void ELTAPIENTRY ExHideWindow(ExWin window){
#ifdef EX_WINDOWS
	ShowWindow(window,SW_HIDE);
#elif defined(EX_LINUX)
    XUnmapWindow(display,window);
#elif defined(EX_ANDROID)

#endif
}
DECLSPEC void ELTAPIENTRY ExCloseWindow(ExWin window){
#ifdef EX_WINDOWS
    CloseWindow(window);
	DestroyWindow(window);
#elif defined(EX_LINUX)
    XDestroyWindow(display, window);
#elif defined(EX_ANDROID)

#endif
}


DECLSPEC void ELTAPIENTRY ExSetWindowMode(ExWin window, Enum mode){
#ifdef EX_WINDOW
    if(mode & EX_WIN_SCREENSAVER_ENABLE){
        ExLoadLibrary(EX_TEXT("scrnsave.dll"));
    }

#elif defined(EX_LINUX)
    if(mode & EX_WIN_SCREENSAVER_ENABLE){

    }
#endif
}


DECLSPEC ExBoolean ELTAPIENTRY ExDestroyWindow(ExWin window){
#if defined(EX_WINDOWS)
	return DestroyWindow(window);
#elif defined(EX_LINUX)
	return XDestroyWindow(display,(Window*)window);
#elif defined(EX_ANDROID)

#endif
}

DECLSPEC void ELTAPIENTRY ExSetWindowTitle(ExWin window,const ExChar* title){
	if(!window || !title)return;
#if defined(EX_WINDOWS)
	ExIsWinError(SetWindowText(window,title));
#elif defined(EX_LINUX)
	XStoreName(display,(Window*)window,title);
#elif defined(EX_ANDROID)

#endif
}
DECLSPEC void ELTAPIENTRY ExGetWindowTitle(ExWin window, ExChar* title){
	if(!window || !title)return;
#if defined(EX_WINDOWS)
	ExIsWinError(GetWindowText(window,title,EX_STR_LEN(title)));
#elif defined(EX_LINUX)
	XFetchName(display,(Window*)window,&title);
#elif defined(EX_ANDROID)
#endif
}

DECLSPEC void ELTAPIENTRY ExSetWindowPos(ExWin window,Int32 x,Int32 y){
#if defined(EX_WINDOWS)
	RECT winrect;
	if(!window)return;
	GetWindowRect(window,&winrect);
	SetWindowPos(window,EX_NULL,x,y,winrect.right - winrect.left,winrect.bottom - winrect.top,SWP_SHOWWINDOW);
#elif defined(EX_LINUX)
	XMoveWindow(display,(Window*)window,x,y);
#endif
}
DECLSPEC void ELTAPIENTRY ExSetWindowPosv(ExWin window, const Int32* position){
	if(!window || !position)return;
#if defined(EX_WINDOWS)
	RECT winrect;
	GetWindowRect(window,&winrect);
	SetWindowPos(window, EX_NULL,position[0],position[1], winrect.right - winrect.left,winrect.bottom - winrect.top,SWP_SHOWWINDOW);
#elif defined(EX_LINUX)
	XMoveWindow(display,(Window*)window,position[0],position[1]);
#elif defined(EX_ANDROID)

#endif
}
DECLSPEC void ELTAPIENTRY ExGetWindowPosv(ExWin window, Int32* position){
#ifdef EX_WINDOWS
	RECT winrect;
	GetWindowRect(window,&winrect);
	position[0]= winrect.left;
	position[1] = winrect.top;
#elif defined(EX_LINUX)
	XWindowAttributes xwa;
	XGetWindowAttributes(display, window,&xwa);
	position[0] = xwa.x;
	position[1] = xwa.y;
#endif
}

DECLSPEC void ELTAPIENTRY ExSetWindowSize(ExWin window,Int32 width, Int32 height){
#ifdef EX_WINDOWS
	RECT winrect;
	GetWindowRect(window,&winrect);
#elif defined(EX_LINUX)
	XResizeWindow(display,window,width,height);
#endif
}
DECLSPEC void ELTAPIENTRY ExSetWindowSizev(ExWin window,const struct exsize* size){
#ifdef EX_WINDOWS
	RECT winrect;
	GetWindowRect(window,&winrect);
#elif defined(EX_LINUX)
	XResizeWindow(display,window,size->width,size->height);
#endif
}
DECLSPEC void ELTAPIENTRY ExGetWindowSizev(ExWin window, struct exsize* size){
#ifdef EX_WINDOWS
	RECT winrect;
	GetWindowRect(window, &winrect);
	size->width = winrect.right - winrect.left;
	size->height = winrect.bottom - winrect.top;
#elif defined(EX_LINUX)
	XWindowAttributes xwa;
	XGetWindowAttributes(display, window,&xwa);
	size->width = xwa.width;
	size->height= xwa.height;
#endif
}

/**
	// Set Window Rect
*/
DECLSPEC void ELTAPIENTRY ExSetWindowRect(ExWin window, const struct exrect* rect){
#if defined(EX_WINDOWS)
	SetWindowPos(window,HWND_TOP,rect->x,rect->y,rect->width - rect->x,rect->height - rect->y,SWP_SHOWWINDOW);
#elif defined(EX_LINUX)
	XMoveWindow(display,(Window)window,rect->x,rect->y);
	XResizeWindow(display,(Window)window,rect->width - rect->x,rect->height - rect->y);
#endif
}
/**
	// Get Window Rect
*/
DECLSPEC void ELTAPIENTRY ExGetWindowRect(ExWin window, struct exrect* rect){
#if defined(EX_WINDOWS)
	GetWindowRect(window, (RECT*)rect);
#elif defined(EX_LINUX)
	XWindowAttributes xwa;
	XGetWindowAttributes(display, (Window*)window,&xwa);
	rect->width = xwa.width;
	rect->height = xwa.height;
	rect->x = xwa.x;
	rect->y= xwa.y;
#endif
}


// Get Windows flag
DECLSPEC Uint32 ELTAPIENTRY ExGetWindowFlag(ExWin window){
#ifdef EX_WINDOWS
	return GetWindowLong(window,GWL_STYLE);
#elif defined(EX_LINUX)
    //TODO remove or something
	XWindowAttributes xwa;
	XGetWindowAttributes(display, (Window*)window,&xwa);
	return xwa.all_event_masks;
#endif
}


DECLSPEC Int32 ELTAPIENTRY ExSetWindowIcon(ExWin window, HANDLE hIcon){
#ifdef EX_WINDOWS
	LRESULT result;
	result = SetClassLong(window,GCL_HICON, (LONG)hIcon);
	result = SetClassLong(window,GCL_HICONSM,(LONG)hIcon);
	return result;
#elif defined(EX_LINUX)
     //http://www.sbin.org/doc/Xlib/chapt_03.html
    XWMHints *wm_hints;
    Pixmap  icon_pixmap;
    unsigned int count;
    XIconSize *size_list;
/*    if (!(wm_hints = XAllocWMHints())) {
      fprintf(stderr, "%s: failure allocating memory", "ELT");
      return FALSE;
    }*/
    Atom net_wm_icon = XInternAtom(display, "_NET_WM_ICON", False);
    Atom cardinal = XInternAtom(display, "CARDINAL", False);
    wm_hints->initial_state = NormalState;
    /* Does application need keyboard input? */
    wm_hints->input = True;
    wm_hints->icon_pixmap = icon_pixmap;
    wm_hints->flags = IconPixmapHint;

    //XFlush(display);
    //XSetWMHints(display, window, wm_hints);

    XChangeProperty(display, window, net_wm_icon, cardinal, 24, PropModeReplace, (const unsigned char*) ELT_ICON, sizeof(ELT_ICON) / 24);


	return TRUE;
#endif
}

DECLSPEC Int32 ELTAPIENTRY ExGetWindowIcon(ExWin window){
#ifdef EX_WINDOWS

    return NULL;
#elif defined(EX_LINUX)

    return NULL;
#endif // EX_WINDOWS
}

DECLSPEC Int32 ELTAPIENTRY ExIsScreenSaverEnable(void){
#ifdef EX_WINDOWS
    if(ExIsModuleLoaded(""))
        return TRUE;

    return 0;
#elif defined(EX_LINUX)
    int dummy;
   // if(DPMSQueryExtension(display,&dummy,&dummy)){

    //}
    return 0;
#endif
}
