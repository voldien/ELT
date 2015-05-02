#include"system/elt_gl.h"
#include"ExPreProcessor.h"

#define EX_EGL_LIB_MOUDLE_NAME EX_TEXT("libEGL.dll")
#define EX_GLES_LIB_MOUDLE_NAME EX_TEXT("libGLESv2.dll")
#pragma warning(disable : 4273)     // 'function' : inconsistent DLL linkage

/* library  */
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib, "Glu32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib,"libEGL.lib")
#pragma comment(lib,"libGLESv2.lib")

#include<dwmapi.h>
#include<WinUser.h>
#include<Windows.h>
#include<GL/GL.h>
#include<EGL/egl.h>
#include<GL/glext.h>
#include<GL/wglext.h>
#include<GL/glu.h>
#define GL_GET_PROC(x)   wglGetProcAddress( (LPCSTR)( x ) )         /*  get OpenGL function process address */



typedef int (APIENTRY * WGLSWAPINTERVALEXT_T) (int);            /** wglSwapIntervalEXT typedef (Win32 buffer-swap interval control)*/

typedef BOOL (WINAPI * WGLCHOOSEPIXELFORMATARB_T) (HDC, const int *, const FLOAT *, UINT, int *, UINT *);   /** wglChoosePixelFormatARB typedef*/

typedef BOOL (WINAPI * WGLGETPIXELFORMATATTRIBIVARB_T) (HDC, int, int, UINT, const int *, int *);   /* wglGetPixelFormatAttribivARB typedef */

typedef const char *(APIENTRY * WGLGETEXTENSIONSSTRINGEXT_T)( void );   /* wglGetExtensionStringEXT typedef */

typedef const char *(APIENTRY * WGLGETEXTENSIONSSTRINGARB_T)( HDC );    /* wglGetExtensionStringARB typedef */

typedef HGLRC (APIENTRY * WGLCREATECONTEXTATTRIBSARB)(HDC,HGLRC hShareContext,const int *attribList);			/*  */


static void ELTAPIENTRY ExCreatePFD( void* pPFD, Int32 colorbits, Int32 depthbits, Int32 stencilbits){

	PIXELFORMATDESCRIPTOR* pfd = (PIXELFORMATDESCRIPTOR*)pPFD;
	memset(pfd,0,sizeof(PIXELFORMATDESCRIPTOR));
	pfd->nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd->nVersion = 1;
	pfd->dwFlags  = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd->iPixelType =  PFD_TYPE_RGBA;
	pfd->iLayerType = PFD_MAIN_PLANE;
	pfd->cColorBits = colorbits;
	pfd->cDepthBits = depthbits;
	pfd->cStencilBits = stencilbits;

}
static void ELTAPIENTRY ExCreatePFD2( void *pPFD, EngineDescription* desc){

	PIXELFORMATDESCRIPTOR pfd = {0};
	if(desc){
		pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		pfd.nVersion = 1;
		pfd.dwFlags  =  PFD_SUPPORT_OPENGL
		| PFD_DRAW_TO_WINDOW
		| ((desc->EngineFlag & ENGINE_SUPPORT_DOUBLEBUFFER) != 0 ? PFD_DOUBLEBUFFER : 0)
		| ((desc->EngineFlag & ENGINE_SUPPORT_STEROVISION) != 0 ? PFD_STEREO : 0);
		pfd.iPixelType = ((desc->PixelType & ENGINE_RGB) != 0 || (desc->PixelType & ENGINE_RGBA) != 0) != 0 ? PFD_TYPE_RGBA : PFD_TYPE_COLORINDEX;
		pfd.iLayerType = PFD_MAIN_PLANE;
		pfd.cColorBits = desc->ColorBits;
		pfd.cDepthBits = desc->DepthBits;
		pfd.cAccumBits = desc->AccumBits;
		pfd.cStencilBits = desc->StencilBits;
		pfd.cAlphaBits = desc->alphaChannel;
	}
	else{
		// default engine Description allocated on the heap.
		pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		pfd.nVersion = 1;
		pfd.dwFlags  =  PFD_SUPPORT_OPENGL
		| PFD_DRAW_TO_WINDOW
		| ((engineDescription.EngineFlag & ENGINE_SUPPORT_DOUBLEBUFFER) != 0 ? PFD_DOUBLEBUFFER : 0)
		| ((engineDescription.EngineFlag & ENGINE_SUPPORT_STEROVISION) != 0 ? PFD_STEREO : 0);
		pfd.iPixelType = ((engineDescription.PixelType & ENGINE_RGB) != 0 || (engineDescription.PixelType & ENGINE_RGBA) != 0) != 0 ? PFD_TYPE_RGBA : PFD_TYPE_COLORINDEX;
		pfd.iLayerType = PFD_MAIN_PLANE;
		pfd.cColorBits = engineDescription.ColorBits;
		pfd.cDepthBits = engineDescription.DepthBits;
		pfd.cAccumBits = engineDescription.AccumBits;
		pfd.cStencilBits = engineDescription.StencilBits;
		pfd.cAlphaBits = engineDescription.alphaChannel;

	}		//assign the data of the pixelformat description.
	memcpy(pPFD,&pfd, sizeof(PIXELFORMATDESCRIPTOR));
}
static OpenGLContext create_temp_gl_context(HWND window){
	PIXELFORMATDESCRIPTOR pfd;
	OpenGLContext gl_context,hrc;
	int npixelFormat;
	HDC hDC;
	/**
        Create Pixel Description
	*/
	ExCreatePFD(&pfd,32,24,0);
	hDC = GetDC(window);    /*Get device context*/
	/**
        // Choose Pixel Format.
	*/
	if(!(npixelFormat = ChoosePixelFormat(hDC,(const PIXELFORMATDESCRIPTOR*)&pfd))){
		ExIsWinError(npixelFormat);
		return NULL;
	}
	/**
        // Set Pixel format
	*/
	if(!SetPixelFormat(hDC, npixelFormat,(const PIXELFORMATDESCRIPTOR*)&pfd)){
		wExDevPrintf(EX_TEXT("Failed to Set PixelFormat : %s\n"), ExGetErrorMessage(GetLastError()));
		return NULL;
	}
	/**
		// Create OpenGL Context
	*/
	if(!(gl_context = wglCreateContext(hDC))){
		wExDevPrintf(EX_TEXT("Failed to Create OpenGL Context : %s\n"), ExGetErrorMessage(GetLastError()));
		MessageBox(EX_NULL, EX_TEXT("Failed to Create Window OpenGL Context"), EX_TEXT("ERROR"), MB_OK | MB_ICONERROR);
		return NULL;
	}
	/**
        // Make Current Context On this Thread
	*/
	if(!wglMakeCurrent(hDC,gl_context)){
		wExDevPrintf(EX_TEXT("Failed to Make OpenGL Current : %s\n"), ExGetErrorMessage(GetLastError()));
		return NULL;
	}

	hrc = gl_context;
	// Release Context
	/*if(ReleaseDC(window,hDC))
		return gl_context;
	else{
		wExDevPrintf(EX_TEXT("Failed to Release DC : %s \n"), ExGetErrorMessage(GetLastError()));
		return gl_context;
	}*/
	return gl_context;
}
static HWND create_temp_gl_win(OpenGLContext* pglc_context){
    HWND hwnd;
    OpenGLContext glc;
    WNDCLASSEX  wc= {0};
    #define TEMP_WINDOW_CLASS EX_TEXT("temp")
    wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wc.lpfnWndProc = MainWndProc;
	wc.hInstance = GetModuleHandle(NULL);
    wc.hIcon = (HICON)LoadIcon(wc.hInstance,NULL);
    wc.hCursor = LoadCursor(wc.hInstance, NULL);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpfnWndProc = MainWndProc;
	wc.hbrBackground =  (HBRUSH) 0;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.lpszMenuName = EX_NULL;
    wc.lpszClassName = TEMP_WINDOW_CLASS;

	RegisterClassEx(&wc);

    hwnd = CreateWindowEx(WS_EX_APPWINDOW,TEMP_WINDOW_CLASS,EX_TEXT(""),
		(WS_OVERLAPPEDWINDOW ^WS_THICKFRAME ^ WS_MAXIMIZEBOX),0, 0,
		 10,
		 10,
		NULL,
		NULL,
		wc.hInstance,
		NULL);
	if(!hwnd)
			return (HWND)0;
    glc = create_temp_gl_context(hwnd);/*create temp opengl context*/
    if(!glc)
        ExError(EX_TEXT("Failure"));
    if(pglc_context)
        *pglc_context = glc;
    return hwnd;
}


DECLSPEC ExWin ELTAPIENTRY ExGetOpenGLContextWindow(OpenGLContext glc){
	return WindowFromDC(wglGetCurrentDC());
}

DECLSPEC WindowContext ELTAPIFASTENTRY ExGetCurrentGLDC(void){
	return wglGetCurrentDC();
}


DECLSPEC OpenGLContext ELTAPIFASTENTRY ExGetCurrentOpenGLContext(void){
	return wglGetCurrentContext();
}

DECLSPEC void ELTAPIENTRY ExMakeGLCurrent(WindowContext hDC, OpenGLContext glc){
	ExIsWinError(wglMakeCurrent(drawable,glc));
}


DECLSPEC void ELTAPIENTRY ExCreateContextAttrib(WindowContext hDC,Int32* attrib,Int32* size,Enum EnumRI){
	if(!attribs)	/* error */
		ExSetError(EINVAL);
   WGLCHOOSEPIXELFORMATARB_T wglGetPixelFormatAttribivARB;
	int attrib[] = { WGL_NUMBER_PIXEL_FORMATS_ARB };
	unsigned int nResults[1] = {0};
	int pixFmt[1] = {0};
	unsigned int attrSize = 0;

    /**
        Get Pixel Format attribute
    */
    wglGetPixelFormatAttribivARB = (WGLCHOOSEPIXELFORMATARB_T)GL_GET_PROC("wglGetPixelFormatAttribivARB");/*Get the process*/

	if(wglGetPixelFormatAttribivARB(hDc, pixFmt,0, 1, attrib, &nResults[0])){

	}
    if(erenderingflag & EX_OPENGL){
        Int32 pixAttribs[] = {
            WGL_SUPPORT_OPENGL_ARB, GL_TRUE, // Must support OGL rendering
            WGL_DRAW_TO_WINDOW_ARB, GL_TRUE, // pf that can run a window
            WGL_DOUBLE_BUFFER_ARB, (engineDescription.EngineFlag & ENGINE_SUPPORT_DOUBLEBUFFER) != 0 ? TRUE : FALSE,
            WGL_DEPTH_BITS_ARB, engineDescription.DepthBits,
            WGL_STENCIL_BITS_ARB, engineDescription.StencilBits,
            WGL_COLOR_BITS_ARB, engineDescription.ColorBits,
            WGL_ALPHA_BITS_ARB, engineDescription.alphaChannel,
            WGL_ACCELERATION_ARB,WGL_FULL_ACCELERATION_ARB, // must be HW accelerated
            WGL_PIXEL_TYPE_ARB,WGL_TYPE_RGBA_ARB, // pf should be RGBA type
            WGL_TRANSPARENT_ARB, WGL_TRANSPARENT_ALPHA_VALUE_ARB,
            WGL_SWAP_METHOD_ARB,WGL_SWAP_EXCHANGE_ARB,
            WGL_SAMPLE_BUFFERS_ARB,engineDescription.sample[0] != 0 ? TRUE : 0 ,// sample buffer
            WGL_SAMPLES_ARB, engineDescription.sample[0],
            0}; // NULL termination
            // create pixel attribute block
        //copy block
        memcpy(attribs,pixAttribs,sizeof(pixAttribs));
    }
    else if(erenderingflag & EX_OPENGLES){
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
}


DECLSPEC OpenGLContext ELTAPIENTRY ExCreateGLContext(ExWin window){
	OpenGLContext glc = 0;
	unsigned int render_vendor;


    WGLSWAPINTERVALEXT_T wglSwapIntervalEXT;
    WGLCHOOSEPIXELFORMATARB_T wglChoosePixelFormatARB;
    WGLGETPIXELFORMATATTRIBIVARB_T wglGetPixelFormatAttribivARB;
    WGLGETEXTENSIONSSTRINGEXT_T wglGetExtensionStringEXT;
    WGLGETEXTENSIONSSTRINGARB_T wglGetExtensionStringARB;
    WGLCREATECONTEXTATTRIBSARB wglCreateContextAttribsARB;
    HWND temp_gl_hwnd;
	PIXELFORMATDESCRIPTOR pfd;
	HDC hDC;
    int pixAttribs[60] = {0};
	int pixelFormat[1];
    int major_version = 0, minor_version = 0;
    int attrib[] = {WGL_NUMBER_PIXEL_FORMATS_ARB};
    int nResults[1] ={0};
    int pixFmt = 1;
	unsigned int dataSize;

    /**
        Create Temporarily openGL Context and it's associated window
    */
	if(temp_gl_hwnd = (HWND)create_temp_gl_win(&glc))
		printf("Success to Create Default OpenGL Context.\n");
	ExMakeGLCurrent(GetDC(temp_gl_hwnd), glc);
#ifdef EX_DEBUG
	printf("opengl Version : %u",ExGetOpenGLVersion());
#endif

	/*
		latest version aviable
	*/


    /**
		Get supported opengl version.
    */
    glGetIntegerv(GL_MAJOR_VERSION, &major_version);
    glGetIntegerv(GL_MINOR_VERSION, &minor_version);

	//ExGLPrintDevInfo();
	hDC = GetDC(window);
	/**
        \ TODO change the condition.
	*/
    /**
        Create all entry point to create extension openGL context.
    */
	wglSwapIntervalEXT =            (WGLSWAPINTERVALEXT_T)GL_GET_PROC("wglSwapIntervalEXT");
	wglChoosePixelFormatARB =       (WGLCHOOSEPIXELFORMATARB_T)GL_GET_PROC("wglChoosePixelFormatARB");
	wglGetPixelFormatAttribivARB =  (WGLGETPIXELFORMATATTRIBIVARB_T)GL_GET_PROC("wglGetPixelFormatAttribivARB");
	wglGetExtensionStringEXT =      (WGLGETEXTENSIONSSTRINGEXT_T)GL_GET_PROC("wglGetExtensionStringEXT");
	wglGetExtensionStringARB =      (WGLGETEXTENSIONSSTRINGARB_T)GL_GET_PROC("wglGetExtensionStringARB");
	wglCreateContextAttribsARB =    (WGLCREATECONTEXTATTRIBSARB)GL_GET_PROC("wglCreateContextAttribsARB");


	if(!wglCreateContextAttribsARB)	/*	exit because we can get a better opengl context*/
		return glc;


	if(!wglGetPixelFormatAttribivARB(hDC, pixFmt,0,1, attrib, nResults))
		ExError(EX_TEXT("Error"));




    /*
        Context attributes
    */
    int context_attribs[]={
	WGL_CONTEXT_MAJOR_VERSION_ARB, !major_version ? ((ExGetOpenGLVersion() - (ExGetOpenGLVersion() % 100)) / 100) : major_version,
        WGL_CONTEXT_MINOR_VERSION_ARB, minor_version ? ExGetOpenGLVersion() % 100 : minor_version,
        WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
        #ifdef EX_DEBUG
        WGL_CONTEXT_FLAGS_ARB,WGL_CONTEXT_DEBUG_BIT_ARB,
        #endif
        NULL
    };


    /*TODO: Naming between context attributes and for choosing a pixel-format
        Create pixel format attributes
    */
	ExCreateContextAttrib(hDC,&pixAttribs[0],(Int32*)&dataSize,&engineDescription, EX_OPENGL);


	if(!wglChoosePixelFormatARB(hDC, &pixAttribs[0], NULL, 1, pixelFormat, (unsigned int*)&nResults[0]))
		ExError(EX_TEXT("function : wglChoosePixelFormatARB Failed"));


	if(ExDestroyContext(hDC,glc)){  /*  destroy temp context    */
		DestroyWindow(temp_gl_hwnd);
	}else ExDevPrint("Failed to delete Temp OpenGL Context.\n");

    /*
        Get Device Context from window
    */
    hDC = GetDC(window);

    if(SetPixelFormat(hDC, pixelFormat[0], &pfd))
        printf("Succedded to Set PixelFormat With the PixelFormat Number %i.\n",nResults[0] );
    else
        wExDevPrintf(EX_TEXT("Failed to Set PixelFormat : %s \n"),ExGetErrorMessage(GetLastError()));

    /**
        Create OpenGL Context.
    */
    if(!(glc = wglCreateContextAttribsARB(hDC, EX_NULL,pixAttribs))){
        //ExDevPrintf(EX_TEXT("Failed to Create OpenGL Context ARB | %s.\n"),glewGetErrorString(glGetError()));
        //MessageBoxA(EX_NULL,  (LPCSTR)glewGetErrorString(glGetError()),"Error | OpenGL Context",MB_OK | MB_ICONERROR);
		ExMessageBox(EX_NULL, EX_TEXT(""), EX_TEXT(""), MB_OK |MB_ICONERROR);
    }


    if(!ReleaseDC(WindowFromDC(wglGetCurrentDC()),wglGetCurrentDC()))
        wprintf(EX_TEXT("Failed to Release DC : %s \n"),ExGetErrorMessage(GetLastError()));

	return glc;

}


DECLSPEC OpenGLContext ELTAPIENTRY ExCreateGLSharedContext(ExWin window, OpenGLContext context){
    int major_version,minor_version;
    OpenGLContext shared_glc;
    HDC hdc;
    WGLSWAPINTERVALEXT_T wglSwapIntervalEXT;
    WGLCHOOSEPIXELFORMATARB_T wglChoosePixelFormatARB;
    WGLGETPIXELFORMATATTRIBIVARB_T wglGetPixelFormatAttribivARB;
    WGLGETEXTENSIONSSTRINGEXT_T wglGetExtensionStringEXT;
    WGLGETEXTENSIONSSTRINGARB_T wglGetExtensionStringARB;
    WGLCREATECONTEXTATTRIBSARB wglCreateContextAttribsARB;

    hdc = GetDC(window);

	/**
		Get major and minor version of opengl
	*/
    glGetIntegerv(GL_MAJOR_VERSION, &major_version);
	glGetIntegerv(GL_MINOR_VERSION, &minor_version);


	int attribs[] ={
			WGL_CONTEXT_MAJOR_VERSION_ARB, major_version,
			WGL_CONTEXT_MINOR_VERSION_ARB, minor_version,
			WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,
#ifdef EX_DEBUG
			WGL_CONTEXT_FLAGS_ARB,WGL_CONTEXT_DEBUG_BIT_ARB,
#endif
			NULL
	};

    if(!wglChoosePixelFormatARB(hdc,0,0,0,0,0))
        ExError(EX_TEXT(""));
    //if(!SetPixelFormat(hdc, 0, 0))

    shared_glc = wglCreateContextAttribsARB(hdc,glc,0);
    wglCopyContext(glc, shared_glc, GL_ALL_ATTRIB_BITS);
    wglShareLists(glc, shared_glc);

    return shared_glc;
}

DECLSPEC int ELTAPIENTRY ExDestroyContext(WindowContext drawable, OpenGLContext glc){
	int hr;
	// if hDC is null
	if(!drawable)
		drawable = ExGetCurrentGLDC();
	ExMakeGLCurrent(0,0);
	ExIsError(hr = wglDeleteContext(glc));
	DeleteDC(drawable);
	return hr;
}

extern DECLSPEC ExBoolean ELTAPIENTRY ExDestroyCurrentContext(void);

extern DECLSPEC ExBoolean ELTAPIENTRY ExGLFullScreen(ExBoolean cdsfullscreen, ExWin window, Uint32 screenIndex, const Int* screenRes){
	RECT rect;
	DEVMODE dm;
	DISPLAY_DEVICE dd;
	Int cdsRet;

	if(!window)
		return FALSE;
	// going for fullscreen.
	if(cdsfullscreen){
		// Get Window Rect
		GetWindowRect(window,&rect);

		dd = ExGetMonitor(screenIndex);
		dm;
		if(!EnumDisplaySettings(dd.DeviceName, ENUM_CURRENT_SETTINGS, &dm))
			wExDevPrintf(EX_TEXT("EnumDisplay Settings Failed | %s.\n"), ExGetErrorMessage(GetLastError()));
		dm.dmSize = sizeof(dm);
		if(!screenRes){
			// resolution from the window.
			dm.dmPelsWidth = (rect.right - rect.left);
			dm.dmPelsHeight = (rect.bottom - rect.top);
		}
		else{
			// specified resolution
			dm.dmPelsWidth = screenRes[0];
			dm.dmPelsHeight = screenRes[1];
		}
		dm.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT;
		if(engineDescription.ColorBits != 0){
			// glw_state.allowdisplaydepthchange )
			dm.dmBitsPerPel = engineDescription.ColorBits;
			dm.dmFields |= DM_BITSPERPEL;
			ExPrintf("Using colorbits of %d\n", engineDescription.ColorBits);
		}
		SetWindowLong(window, GWL_STYLE, GetWindowLong(window,GWL_STYLE) | WS_VISIBLE);		//Change Window Class Style.
		//SetWindowLongPtr(hWnd,GWL_EXSTYLE, WS_EX_APPWINDOW);							//Change Extened Window Class Style.
		ShowWindow(window, SW_MAXIMIZE);

		if((cdsRet = ChangeDisplaySettingsEx(dd.DeviceName,&dm,EX_NULL,(CDS_TEST),0)) == DISP_CHANGE_SUCCESSFUL){
			cdsRet = ChangeDisplaySettingsEx(dd.DeviceName,&dm,EX_NULL,(CDS_FULLSCREEN),0);
			ExPrintf("displayed changed to fullscreen Mode\n");
			//engineDescription.EngineFlag |= ENGINE_FULLSCREEN;
			return cdsfullscreen;
		}
		// try to find another rus
		wExDevPrintf(EX_TEXT("Failed to Fullscreen : [error] %s"), ExGetErrorMessage(GetLastError()));
		return !cdsfullscreen;
	}
	else{
		ExPrintf("restoring display settings\n");
		SetWindowLongPtr(window, GWL_STYLE,WS_OVERLAPPEDWINDOW);	//Change Window Class Style.
		SetWindowLongPtr(window, GWL_EXSTYLE, WS_EX_APPWINDOW);
		ChangeDisplaySettings(0,0);
		ShowWindow(window, SW_NORMAL);
		//engineDescription.EngineFlag = (~ENGINE_FULLSCREEN & engineDescription.EngineFlag);
		UpdateWindow(window);
		SetForegroundWindow(window);
		return (ExBoolean)!cdsfullscreen;
	}
}

/**
//  Set OpenGL Transparent.
//  remark:
//  you'll need to use glClear or from pixel shader alpha channel to see effect
//  glClearColor
//  ExSetHint(EX_ALPHA, x > 0);
//  read more about DwmEnableBlurBehindWindow : http://msdn.microsoft.com/en-us/library/windows/desktop/aa969508(v=vs.85).aspx
*/
DECLSPEC void ELTAPIENTRY ExSetGLTransparent(ExWin hWnd,Enum ienum){
	DWM_BLURBEHIND bb = {0};
	HRESULT hr;
	// cheap way of creating the effect.
	bb.hRgnBlur = CreateRectRgn(0,0,1,1);
	bb.dwFlags = DWM_BB_ENABLE | DWM_BB_BLURREGION | DWM_BB_TRANSITIONONMAXIMIZED;
	bb.fTransitionOnMaximized = TRUE;
	if(ienum & 0x1)
		bb.fEnable = TRUE;
	else
		bb.fEnable = FALSE;
	ExIsHError(hr = DwmEnableBlurBehindWindow(window, &bb));
}

