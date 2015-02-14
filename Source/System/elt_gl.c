#include"elt_gl.h"
#include"./../ExPreProcessor.h"
#ifdef EX_WINDOWS
    #define EX_EGL_LIB_MOUDLE_NAME EX_TEXT("libEGL.dll")
    #define EX_GLES_LIB_MOUDLE_NAME EX_TEXT("libGLESv2.dll")
    #pragma warning(disable : 4273) // 'function' : inconsistent DLL linkage

	// library
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
    //#include<GL/glext.h>
    #define GL_GET_PROC(x)   wglGetProcAddress( (LPCSTR)( x ) )         /*  get OpenGL function process address */

#elif defined(EX_LINUX)
    #define EX_EGL_LIB_MOUDLE_NAME EX_TEXT("libEGL.so")
    #define EX_GLES_LIB_MOUDLE_NAME EX_TEXT("libGLESv2.so")
    #include<X11/extensions/Xrender.h>
    #include<X11/Xatom.h>
    #include<X11/keysym.h>
    #include<EGL/egl.h>
    #include<EGL/eglext.h>
    #include<GL/glx.h>
    #include<GL/glxext.h>
    #include<GL/glu.h>
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
#define GL_GET_PROC(x) (x)                                      /* * get OpenGL function process address */

#elif defined(EX_MAC)
#include<GL/glu.h>
#endif


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
#ifdef EX_WINDOWS
//#elif defined(EX_LINUX) || defined(EX_ANDROID)
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
	return 0;
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
	eglDisplay = eglGetDisplay(NULL);
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

/*    if(ExGetOpenGLContextWindow(eglContext) == window)
        return 0;*/

	ExInitOpenGLStates(0);


	return eglContext;
}

/**
	Get window associated with the opengl context
*/
DECLSPEC ExWin ELTAPIENTRY ExGetOpenGLContextWindow(OpenGLContext glc){
#ifdef EX_WINDOWS
	return WindowFromDC(wglGetCurrentDC());
#elif defined(EX_LINUX)
	return glXGetCurrentDrawable();
#elif defined(EX_ANDROID)
	return eglGetCurrentSurface(NULL);
#endif
}
/**
    //Get Drawable
*/
DECLSPEC WindowContext ELTAPIFASTENTRY ExGetCurrentGLDC(void){
#ifdef EX_WINDOWS
	return wglGetCurrentDC();
#elif defined(EX_LINUX)
	return glXGetCurrentDrawable();
#elif defined(EX_ANDROID)
	return eglGetCurrentSurface(NULL);
#endif
}

DECLSPEC OpenGLContext ELTAPIFASTENTRY ExGetCurrentOpenGLContext(void){
#ifdef EX_WINDOWS
	return wglGetCurrentContext();
#elif defined(EX_LINUX)
	return glXGetCurrentContext();
#elif defined(EX_ANDROID)
	return eglGetCurrentContext();
#endif
}

DECLSPEC void ELTAPIENTRY ExMakeGLCurrent(WindowContext drawable, OpenGLContext glc){
#ifdef EX_WINDOWS
	ExIsWinError(wglMakeCurrent(drawable,glc));
#elif defined(EX_LINUX)
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
#ifdef EX_WINDOWS
/**
    Extension function types
*/

typedef int (APIENTRY * WGLSWAPINTERVALEXT_T) (int);            /** wglSwapIntervalEXT typedef (Win32 buffer-swap interval control)*/

typedef BOOL (WINAPI * WGLCHOOSEPIXELFORMATARB_T) (HDC, const int *, const FLOAT *, UINT, int *, UINT *);   // wglChoosePixelFormatARB typedef

typedef BOOL (WINAPI * WGLGETPIXELFORMATATTRIBIVARB_T) (HDC, int, int, UINT, const int *, int *);   // wglGetPixelFormatAttribivARB typedef

typedef const char *(APIENTRY * WGLGETEXTENSIONSSTRINGEXT_T)( void );   // wglGetExtensionStringEXT typedef

typedef const char *(APIENTRY * WGLGETEXTENSIONSSTRINGARB_T)( HDC );    // wglGetExtensionStringARB typedef

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
/**
    Generate a temporarily window for creating the extension window.
*/
static HWND  create_temp_gl_win(OpenGLContext* pglc_context){
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

/**
=================================00
            LINUX GL Impl
=================================00
*/
#elif defined(EX_LINUX)
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
	ExCreateContextAttrib(NULL,&att[0],0,0,EX_OPENGL);

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

void ELTAPIENTRY ExCreateContextAttrib(WindowContext hDc, Int32* attribs,Int32* size,EngineDescription* engineDesc,Enum erenderingflag){
	if(!attribs)	// error
		return;
#ifdef EX_WINDOWS
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
#elif defined(EX_LINUX)
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
	else if(erenderingflag & EX_OPENGL){
		Int32 pixAttribs[] = {
                GLX_RENDER_TYPE, GLX_RGBA_BIT,
                GLX_X_RENDERABLE, True,
                GLX_X_VISUAL_TYPE, GLX_TRUE_COLOR,
                GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
                GLX_DOUBLEBUFFER, True,
                GLX_RED_SIZE, 8,
                GLX_GREEN_SIZE, 8,
                GLX_BLUE_SIZE, 8,
                GLX_ALPHA_SIZE,engineDescription.alphaChannel,
                GLX_DEPTH_SIZE, 24,
                GLX_STENCIL_SIZE,engineDescription.StencilBits,
                GLX_STEREO,0,
                GLX_SAMPLE_BUFFERS_ARB,engineDescription.sample[0] != 0 ? 1 : 0,
                GLX_SAMPLES_ARB,engineDescription.sample[0],
                //GLX_TRANSPARENT_TYPE, engineDescription.alphaChannel > 0 ? GLX_TRANSPARENT_RGB : GLX_NONE,
                None,
				/*
			//GLX_TRANSPARENT_ARB, WGL_TRANSPARENT_ALPHA_VALUE_ARB,,
			0*/ }; // NULL termination
		if(size)size =sizeof(pixAttribs);
		memcpy(attribs,(int*)pixAttribs,sizeof(pixAttribs));

	}
#elif defined(EX_ANDROID)

	if(erenderingflag & EX_OPENGL){  /* as for today 2015 -01 -09 must devices on android don't support OpenGL TODO:solve in future*/

	}
	else if(erenderingflag & EX_OPENGLES){

	}
#elif defined(EX_MAC)

#endif
	return;
}

 DECLSPEC OpenGLContext ELTAPIENTRY ExCreateGLContext(ExWin window){
	OpenGLContext glc = 0;
	unsigned int render_vendor;
#ifdef EX_WINDOWS

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

#elif defined(EX_LINUX)
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
        GLX_CONTEXT_MINOR_VERSION_ARB,/* minor_version*/2, //TODO obtain latest minor version
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
		ExCreateContextAttrib(0,&att[0],0,0,EX_OPENGL);
		vi = glXChooseVisual(display,DefaultScreen(display),att);

		glc = glXCreateContext(display,vi,0,0);
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



    return glc;
#endif
}

/**
    \Create Shared OpenGL Context from a already existing context.
*/
DECLSPEC OpenGLContext ELTAPIENTRY ExCreateGLSharedContext(ExWin window, OpenGLContext glc){
    int major_version,minor_version;
    OpenGLContext shared_glc;
#   ifdef EX_WINDOWS
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
#   elif defined(EX_LINUX)
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
	glClearDepth(1.0f);
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
	glDepthRange(0.0, 1.0);
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

DECLSPEC ExBoolean ELTAPIENTRY ExDestroyContext(WindowContext drawable, OpenGLContext glc){
	ExBoolean hr;
	// if hDC is null
	if(!drawable)
		drawable = ExGetCurrentGLDC();
#ifdef EX_WINDOWS
	ExMakeGLCurrent(0,0);
	ExIsError(hr = wglDeleteContext(glc));
	DeleteDC(drawable);
	return hr;
#elif defined(EX_LINUX)
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
#ifdef EX_WINDOWS
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
		if(screenRes == EX_NULL){
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
#ifdef EX_WINDOWS
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
#elif defined(EX_LINUX)
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
#ifndef EX_ANDROID
	return (Uint32)(atof((const char*)glGetString(GL_SHADING_LANGUAGE_VERSION)) * 100.0f);
#else
    return 0;
#endif
}
DECLSPEC Uint32 ELTAPIFASTENTRY ExGetOpenGLVersion(void){
    if(!ExGetCurrentOpenGLContext()){
    }
    else{
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
