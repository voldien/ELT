#include"system/win/win_GL.h"
#include"system/win/win_wndproc.h"

#pragma warning(disable : 4273)     // 'function' : inconsistent DLL linkage

/* library  */
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib, "Glu32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib,"libEGL.lib")
#pragma comment(lib,"libGLESv2.lib")

#include<dwmapi.h>
#include<winuser.h>
#include<windows.h>
#include<GL/gl.h>
#include<EGL/egl.h>
#include<GL/glext.h>
#include<GL/wglext.h>
#include<GL/glu.h>
#define GL_GET_PROC(x)   wglGetProcAddress( (LPCSTR)( x ) )         /*  get OpenGL function process address */


#define PIXATTOFFSET 8
int pixAtt[] = {
	/*
	GLX_RENDER_TYPE, GLX_RGBA_BIT,
	GLX_X_RENDERABLE, True,
	GLX_X_VISUAL_TYPE, GLX_TRUE_COLOR,
	GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
	*/
	/**/
	WGL_RED_SIZE,8,
	WGL_GREEN_SIZE,8,
	WGL_BLUE_SIZE,8,
	WGL_DEPTH_SIZE,16,
	WGL_ALPHA_SIZE,0,
	WGL_DOUBLEBUFFER,1,
	WGL_STENCIL_SIZE,0,
	WGL_ACCUM_RED_SIZE,0,
	WGL_ACCUM_GREEN_SIZE,0,
	WGL_ACCUM_BLUE_SIZE,0,
	WGL_ACCUM_ALPHA_SIZE,0,
	//GLX_
	WGL_STEREO,0,
	WGL_SAMPLE_BUFFERS_ARB,0,
	WGL_SAMPLES_ARB,0,
	//WGL_FRAMEBUFFER_SRGB_CAPABLE_ARB,True,
	NULL
};



/**
    Extension function types
*/

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

/**
    Create temporarily OpenGL context for windows
*/
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
		MessageBox(NULL, EX_TEXT("Failed to Create Window OpenGL Context"), EX_TEXT("ERROR"), MB_OK | MB_ICONERROR);
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
/**
    Generate a temporarily window for creating the extension window.
*/
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
	wc.lpszMenuName = NULL;
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


DECLSPEC OpenGLContext ELTAPIENTRY ExCreateGLContext(ExWin window){
	OpenGLContext glc = NULL;
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
	WGL_CONTEXT_MAJOR_VERSION_ARB, !major_version ? ((ExGetOpenGLVersion(NULL,NULL) - (ExGetOpenGLVersion(NULL,NULL) % 100)) / 100) : major_version,
       WGL_CONTEXT_MINOR_VERSION_ARB, minor_version ? ExGetOpenGLVersion(NULL,NULL) % 100 : minor_version,
       WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
       #ifdef EX_DEBUG
       WGL_CONTEXT_FLAGS_ARB,WGL_CONTEXT_DEBUG_BIT_ARB,
       #endif
       NULL
   };


   /*TODO: Naming between context attributes and for choosing a pixel-format
       Create pixel format attributes
   */
	ExCreateContextAttrib(hDC,&pixAttribs[0],(Int32*)&dataSize);


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
   if(!(glc = wglCreateContextAttribsARB(hDC, NULL,pixAttribs))){
       //ExDevPrintf(EX_TEXT("Failed to Create OpenGL Context ARB | %s.\n"),glewGetErrorString(glGetError()));
       //MessageBoxA(NULL,  (LPCSTR)glewGetErrorString(glGetError()),"Error | OpenGL Context",MB_OK | MB_ICONERROR);
		ExMessageBox(NULL, EX_TEXT(""), EX_TEXT(""), MB_OK |MB_ICONERROR);
   }


   if(!ReleaseDC(WindowFromDC(wglGetCurrentDC()),wglGetCurrentDC()))
       wprintf(EX_TEXT("Failed to Release DC : %s \n"),ExGetErrorMessage(GetLastError()));

	return glc;
}



void ELTAPIENTRY ExCreateContextAttrib(WindowContext hDc, Int32* attribs,Int32* size,Enum erenderingflag){
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
}


/**
    Create Shared OpenGL Context from a already existing context.
*/
DECLSPEC OpenGLContext ELTAPIENTRY ExCreateGLSharedContext(ExWin window, OpenGLContext glc){
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


/*
DECLSPEC void ELTAPIENTRY ExInitExtension(ExWin hWnd,WindowContext deviContext,HGLRC hr){
	// temp variable
	HGLRC tempHRC = hr;PIXELFORMATDESCRIPTOR pfd;
	Int majorVer, minorVer;
	// get information
	Int attrib[] = { WGL_NUMBER_PIXEL_FORMATS_ARB };
	Int nResults[1] = {0};
	Int pixFmt = 1;

	if(wglGetPixelFormatAttribivARB(deviContext, pixFmt,0, 1, attrib, nResults))
		printf("This Hardware Supports %i PixelFormat.\n", *nResults);
	// Get Current OpenGL Version

	glGetIntegerv(GL_MAJOR_VERSION, &majorVer);
	glGetIntegerv(GL_MINOR_VERSION, &minorVer);
	// version
	Int attribs[] ={
			WGL_CONTEXT_MAJOR_VERSION_ARB, majorVer,
			WGL_CONTEXT_MINOR_VERSION_ARB, minorVer,
			WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,
#ifdef EX_DEBUG
			WGL_CONTEXT_FLAGS_ARB,WGL_CONTEXT_DEBUG_BIT_ARB,
#endif
			0
	};
	// print out OpenGL Version
	printf("OpenGL Version %i%i0.\n",majorVer,minorVer);


	Int dataSize;
	Int* pixAttribs = NULL;
	// Create Context Attrib
	ExCreateContextAttrib(deviContext,&pixAttribs,&dataSize,&engineDescription);

	// mayabe change to differnect function depenpded on hardware


	Int pixelFormat[1];
	if(wglChoosePixelFormatARB(deviContext, &pixAttribs[0], NULL, 1, pixelFormat,(Uint*)&nResults[0]))
		printf("Succedded to Choose PixelFormat With the PixelFormat Number %i.\n",nResults[0]);


	if(!ExDestroyContext(deviContext,hrc))
		ExDevPrint("Failed to delete Temp OpenGL Context.\n");
	deviContext = GetDC(ExReConstructWindow(hWnd));


	if(SetPixelFormat(deviContext, pixelFormat[0], &pfd))
		printf("Succedded to Set PixelFormat With the PixelFormat Number %i.\n",nResults[0] );
	else
		wExDevPrintf(EX_TEXT("Failed to Set PixelFormat : %s \n"),ExGetErrorMessage(GetLastError()));

	// Create OpenGL Context ARB
	if(!(hrc = wglCreateContextAttribsARB(deviContext, NULL,attribs))){
		ExDevPrintf("Failed to Create OpenGL Context ARB | %s.\n",glewGetErrorString(glGetError()));
		MessageBoxA(NULL,  (LPCSTR)glewGetErrorString(glGetError()),"Error | OpenGL Context",MB_OK | MB_ICONERROR);
	}
	// Create a Shared OpenGL Context out of First Device Context
	if(ExIsEngineState(ENGINE_SHARE_RENDERCONTEXT))
		if(!(hrc2 = wglCreateContextAttribsARB(deviContext, hrc,attribs)))
			ExDevPrintf("Failed to Create Shared OpenGL Context ARB | %s.\n",glewGetErrorString(glGetError()));
	if(hr){ // hr valid
		// success
		wglMakeCurrent(NULL, NULL);
		wglMakeCurrent(deviContext, hrc);
	}
	free(pixAttribs);
	return;
}
*/



DECLSPEC ExBoolean ELTAPIENTRY ExDestroyContext(WindowContext drawable, OpenGLContext glc){
	ExBoolean hr;
	// if hDC is null
	if(!drawable)
		drawable = ExGetCurrentGLDC();

	ExMakeGLCurrent(0,0);
	ExIsError(hr = wglDeleteContext(glc));
	DeleteDC(drawable);
	return hr;
}


/**
    Opengl Fullscreen
*/
DECLSPEC ExBoolean ELTAPIENTRY ExGLFullScreen(ExBoolean cdsfullscreen, ExWin window, Uint32 screenIndex, const Int* screenRes){

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

		if((cdsRet = ChangeDisplaySettingsEx(dd.DeviceName,&dm,NULL,(CDS_TEST),0)) == DISP_CHANGE_SUCCESSFUL){
			cdsRet = ChangeDisplaySettingsEx(dd.DeviceName,&dm,NULL,(CDS_FULLSCREEN),0);
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


DECLSPEC void ELTAPIENTRY ExSetGLTransparent(ExWin window,Enum ienum){

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
	hr = DwmEnableBlurBehindWindow(window, &bb);
}



/*
DECLSPEC OpenGLContext ELTAPIENTRY ExCreateSharedGLContext(HDC openglHDC, OpenGLContext sharedHRC, WindowContext hDC){
	HGLRC hrc2;
	Int majorVer, minorVer;
	Int dataSize;
	Int nResults[1];
	Int* pixAttribs = NULL;
	PIXELFORMATDESCRIPTOR pfd;

	// Create Context Attrib
	ExCreateContextAttrib(hDC,&pixAttribs,&dataSize,&engineDescription);

	// mayabe change to differnect function depenpded on hardware
	Int pixelFormat[1];
	if(!wglChoosePixelFormatARB(hDC, &pixAttribs[0], NULL, 1, pixelFormat,(Uint32*)&nResults[0]))
		ExDevGLPrintfc("Failed to Choose PixelFormat Number %i.\n",EX_CONSOLE_RED,nResults[0]);
	if(!SetPixelFormat(hDC, pixelFormat[0], &pfd))
		ExDevWindowPrintfc(EX_TEXT("Failed to Set PixelFormat Number %i.\n"),EX_CONSOLE_RED,nResults[0]);
	free(pixAttribs);

	glGetIntegerv(GL_MAJOR_VERSION, &majorVer);
	glGetIntegerv(GL_MINOR_VERSION, &minorVer);
	Int attribs[] ={
			WGL_CONTEXT_MAJOR_VERSION_ARB, majorVer,
			WGL_CONTEXT_MINOR_VERSION_ARB, minorVer,
			WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,
#ifdef EX_DEBUG
			WGL_CONTEXT_FLAGS_ARB,WGL_CONTEXT_DEBUG_BIT_ARB,
#endif
			0
	};
	if(!(hrc2 = wglCreateContextAttribsARB(hDC, sharedHRC,attribs))){
		ExDevPrintf("Failed to Create Shared OpenGL Context ARB | %s.\n",glewGetErrorString(glGetError()));
	}
	wglCopyContext(hrc, hrc2, GL_ALL_ATTRIB_BITS);
	wglShareLists(hrc, hrc2);
	return hrc2;
}

DECLSPEC Uint32 ELTAPIFASTENTRY ExGetGPUMemoryUsage(void){
	Int pvalue;
	glGetIntegerv(GL_GPU_MEMORY_INFO_EVICTED_MEMORY_NVX ,&pvalue);
	return pvalue;
}
DECLSPEC Int32 ELTAPIFASTENTRY ExMaxCombinedTexture(void){
	Int pvalue;
	glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS ,&pvalue);
	return pvalue;
}
DECLSPEC Int32 ELTAPIFASTENTRY ExMaxTextureUints(void){
	Int pvalue;
	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS ,&pvalue);
	return pvalue;
}

*/