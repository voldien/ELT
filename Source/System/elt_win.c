#include"elt_win.h"
#include"elt_gl.h"
#include"elt_cl.h"
#include<Cmd/mathlib.h>	//TODO fix
#if defined(EX_WINDOWS)
	#include"Win32/win_win32.h"
	#include"Win32/wnd_input.h"
	#include<EGL/egl.h>
#elif defined(EX_LINUX)
	#include"Unix/unix_win.h"
	#include<X11/Xlib.h>
	#include<EGL/egl.h>
#elif defined(EX_MAC)
	#include"Mac/macosx_win.h"
	#include<EGL/egl.h>
#endif

#include"../elt_icon.h"
// Ex Create OpenGL ES declaration
extern DECLSPEC void* ELTAPIENTRY ExCreateOpenGLES(ExWin window);


#ifdef EX_DEBUG
#define EX_ENGINE_VERSION_STRING EX_TEXT("Engine Ex Version | %d.%d%d%s | OS : %s [CPU : %s] : OpenGL %d.%d")
#else
#define EX_ENGINE_VERSION_STRING EX_TEXT("Engine Ex Version | %d.%d%d%s | OS : %s [CPU : %s] : OpenGL %d.%d")
#endif
DECLSPEC ExChar* ELTAPIENTRY ExGetDefaultWindowTitle(ExChar* text, int length){
	if(!text)return NULL;
	ExChar wchar[260] = {};
#ifdef EX_UNICODE
	wsprintf(wchar,EX_ENGINE_VERSION_STRING,
#else
	sprintf(wchar,EX_ENGINE_VERSION_STRING,
#endif
		EX_ENGINE_VERSION_MAJOR,
		EX_ENGINE_VERSION_MINOR,
		EX_ENGINE_VERSION_REVISION,
		EX_ENGINE_STATUS,
		ExGetCPUName(),
		ExGetOSName(),
		3,
		3);
	memcpy(text, wchar, MAX(sizeof(ExChar) * length + sizeof(ExChar),sizeof(wchar) / sizeof(ExChar)));
	return text;
}

static void* create_elt_icon(ExWin window){
    #ifdef EX_WINDOWS
    HANDLE icon;
    icon = CreateIcon(GetModuleFile(NULL), GetSystemMetrics(SM_CXICON),GetSystemMetrics(SM_CYICON),1,1,0,0);
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
	if((flag & ENGINE_NATIVE) || flag == 0){
		// create default window
		return ExCreateNativWindow(x,y,width, height);
	}
	// create window dedicated for opengl
	else if(flag & ENGINE_OPENGL){
		window = ExCreateOpenGLWindow(x,y,width, height);
		glc = ExCreateSharedGLContext(ExGetCurrentGLDC(), ExGetOpenGLContext(),GetDC(window));
		if(glc){
            // set the window to be current opengl Context.
            ExMakeGLCurrent(EX_NULL,EX_NULL);
            ExMakeGLCurrent(GetDC(window),glc);
		}
		if(flag & ENGINE_OPENCL)
			ExCreateCLSharedContext(glc,GetDC(window));
		return window;
	}
	else if(flag & EX_OPENGLES){
		window = ExCreateNativeWindow(x,y,width,height);
		glc = ExCreateOpenGLES(window);

		if(flag & EX_OPENCL)
			ExCreateCLSharedContext(glc,GetDC(window));
	}
	else if(flag & ENGINE_OPENCL){
		window = ExCreateOpenGLWindow(x,y,width, height);
		ExCreateOpenGLES(window);

	}
	/*
		//	create window for directX.
		//	not recommanded. becasue ELT won't be designed for handling DirectX
		//	Instead its recommened to create the directX context yourself.
		//	however ELT support DirectX 9 context initilization
	*/
#if  defined(EX_INCLUDE_DIRECTX)
	else if(flag & ENGINE_DIRECTX){
		window = ExCreateDirectXWindow(x,y,width, height);
		ExInitDirectX(window);
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
		ExMakeGLCurrent(glx_window == NULL ? glx_window : window,glc);
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
		//eglSwapBuffers(eglDisplay, eglSurface);
		if(flag & EX_OPENCL)
			ExCreateCLSharedContext(glc,eglGetCurrentDisplay(),EX_OPENGLES);
        return window;
	}
	else if(flag & EX_OPENCL){
		window = ExCreateNativeWindow(x,y,width,height);
		glc = ExCreateCLContex(0);
		return window;
	}
#elif defined(EX_MAC)
	if((flag & ENGINE_NATIVE) || flag == 0){

	}
	else if((flag & ENGINE_OPENGL) || (flag & ENGINE_OPENCL)){

	}
	else
		return EX_NULL;
#elif defined(EX_ANDROID)
	if((flag & ENGINE_NATIVE) || flag == 0){

	}
	else if((flag & ENGINE_OPENGL) ||(flag & ENGINE_OPENCL)){

	}
	else
		return EX_NULL;
#endif
	return EX_NULL;
}

/*

*/
DECLSPEC void ELTAPIENTRY ExShowWindow(ExWin window){
#ifdef EX_WINDOWS
	ShowWindow(window,SW_SHOW);
#else
    XRaiseWindow(display,window);
	XMapWindow(display,(Window*)window);
#endif
}
DECLSPEC void ELTAPIENTRY ExHideWindow(ExWin window){
#ifdef EX_WINDOWS
	ShowWindow(window,SW_HIDE);
#elif defined(EX_LINUX)
    XUnmapWindow(display,window);
#endif
}
DECLSPEC void ELTAPIENTRY ExCloseWindow(ExWin window){
#ifdef EX_WINDOWS
    CloseWindow(window);
	DestroyWindow(window,SW_HIDE);
#elif defined(EX_LINUX)
    XDestroyWindow(display, window);
#endif
}


DECLSPEC Boolean ELTAPIENTRY ExDestroyWindow(ExWin window){
#if defined(EX_WINDOWS)
	return DestroyWindow(window);
#elif defined(EX_LINUX)
	return XDestroyWindow(display,(Window*)window);
#endif
}

DECLSPEC void ELTAPIENTRY ExSetWindowTitle(ExWin window,const ExChar* title){
	if(!window || !title)return;
#if defined(EX_WINDOWS)
	ExIsWinError(SetWindowText(window,title));
#elif defined(EX_LINUX)
	XStoreName(display,(Window*)window,title);
#endif
}
DECLSPEC void ELTAPIENTRY ExGetWindowTitle(ExWin window, ExChar* title){
	if(!window || !title)return;
#if defined(EX_WINDOWS)
	ExIsWinError(GetWindowText(window,title,EX_STR_LEN(title)));
#elif defined(EX_LINUX)
	XFetchName(display,(Window*)window,&title);
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
    if (!(wm_hints = XAllocWMHints())) {
      fprintf(stderr, "%s: failure allocating memory", "ELT");
      return FALSE;
    }

    wm_hints->initial_state = NormalState;
    /* Does application need keyboard input? */
    wm_hints->input = True;
    wm_hints->icon_pixmap = icon_pixmap;
    wm_hints->flags = IconPixmapHint;

    XFlush(display);
    XSetWMHints(display, window, wm_hints);
	return TRUE;
#endif
}

DECLSPEC Boolean ELTAPIENTRY ExPollWindowEvent(ExWin hWnd, ExWindowEvent* event){
#ifdef EX_WINDOWS
	//event->event = 0;
	// peek Message for given window handle.
	if(PeekMessage(&event->msg,hWnd,EX_NULL, EX_NULL, PM_REMOVE)){
		DispatchMessage(&event->msg);
		TranslateMessage(&event->msg);

		switch(event->msg.message){
			case WM_SIZE:
			case WM_SIZING:
			case WM_USER_SIZE:{
				event->size.width = EX_LOWORD(event->msg.lParam);
				event->size.height = EX_HIWORD(event->msg.lParam);
				event->event = EX_EVENT_SIZE;
			}break;
			case WM_DEVICECHANGE:
				break;
			case WM_INPUT:{

			}break;
			case WM_INPUT_DEVICE_CHANGE:{
				RID_DEVICE_INFO info;
				info.cbSize = sizeof(info);
				switch(event->msg.wParam){
				case GIDC_ARRIVAL:
					GetRawInputDeviceInfo((HANDLE)event->msg.lParam,RIDI_DEVICEINFO,&info,0);
					break;
				case GIDC_REMOVAL:
					break;
				}
			}break;
			case WM_KEYDOWN:
			case WM_SYSKEYDOWN:
				// keycode
				event->key.code = event->msg.wParam;
				event->event |= EX_EVENT_KEY;
				event->key.alt = !(event->msg.wParam ^ VK_MENU);
				event->key.shift = !(event->msg.wParam ^ VK_SHIFT);
				event->key.system = !(event->msg.wParam ^ VK_LWIN );
				event->key.ctrl  = !(event->msg.wParam ^ VK_CONTROL);
				break;
			case WM_KEYUP:
			case WM_SYSKEYUP:
				event->event = (~EX_EVENT_KEY & event->event);
				break;
			case WM_HOTKEY:
				event->key.alt = !(event->msg.lParam ^ MOD_ALT);
				event->key.shift = !(event->msg.lParam ^ MOD_SHIFT);
				event->key.system = !(event->msg.lParam ^ MOD_WIN );
				event->key.ctrl  = !(event->msg.lParam ^ MOD_CONTROL);
				break;
			case WM_LBUTTONDOWN:
			case WM_RBUTTONDOWN:
			case WM_MBUTTONDOWN:
			case WM_LBUTTONUP:
			case WM_RBUTTONUP:
			case WM_MBUTTONUP:
			case WM_MOUSEMOVE:{
				event->mouse.x = GET_X_LPARAM(event->msg.lParam);
				event->mouse.y = GET_Y_LPARAM(event->msg.lParam);
				event->event = EX_EVENT_MOUSE;
				event->button.button = event->msg.wParam;
				event->event |= EX_EVENT_MOUSE;
			case WM_MOUSEHWHEEL:
			case WM_MOUSEWHEEL :
				event->mouseWheelEvent.x = GET_X_LPARAM(event->msg.lParam);
				event->mouseWheelEvent.y = GET_X_LPARAM(event->msg.lParam);
				event->mouseWheelEvent.delta = GET_WHEEL_DELTA_WPARAM(event->msg.wParam);
				GET_KEYSTATE_WPARAM(event->msg.wParam);
				event->event |= EX_EVENT_MOUSEWHEEL;
				break;
			}break;
			case WM_DROPFILES:{
				event->drop.number = DragQueryFile((HDROP)event->msg.wParam,0xFFFFFFFF,0,0);
				event->event |= EX_EVENT_DROP;
			}break;
				// no event.
			default:
				event->event = 0;
				break;
		}// message switch
		// return success on handling messsages
		return TRUE;
	}
	return FALSE;
#elif defined(EX_LINUX)
    if(XPending(display))
        XNextEvent(display,&event->msg);
	return TRUE;
#elif defined(EX_ANDROID)
#endif
}
