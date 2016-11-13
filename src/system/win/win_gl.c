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
	WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
	WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
	WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
	WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
	/*
	GLX_RENDER_TYPE, GLX_RGBA_BIT,
	GLX_X_RENDERABLE, True,
	GLX_X_VISUAL_TYPE, GLX_TRUE_COLOR,
	GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
	*/
	/**/
	WGL_RED_BITS_ARB,8,
	WGL_GREEN_BITS_ARB,8,
	WGL_BLUE_BITS_ARB,8,
	WGL_DEPTH_BITS_ARB,16,
	WGL_ALPHA_BITS_ARB,0,
	WGL_DOUBLE_BUFFER_ARB,1,
	WGL_STENCIL_BITS_ARB,0,
	WGL_ACCUM_RED_BITS_ARB,0,
	WGL_ACCUM_GREEN_BITS_ARB,0,
	WGL_ACCUM_BLUE_BITS_ARB,0,
	WGL_ACCUM_ALPHA_BITS_ARB,0,
	//GLX_
	WGL_STEREO_ARB,0,
	WGL_SAMPLE_BUFFERS_ARB,0,
	WGL_SAMPLES_ARB,0,
	WGL_FRAMEBUFFER_SRGB_CAPABLE_ARB,EX_TRUE,
	NULL,
	WGL_CONTEXT_MAJOR_VERSION_ARB,3,
	WGL_CONTEXT_MINOR_VERSION_ARB, 3,
	WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
	WGL_CONTEXT_FLAGS_ARB,WGL_CONTEXT_DEBUG_BIT_ARB,
	NULL

};



/**
    Extension function types
*/

typedef int (APIENTRY * WGLSWAPINTERVALEXT_T) (int);            /** wglSwapintervalEXT typedef (Win32 buffer-swap interval control)*/

typedef BOOL (WINAPI * WGLCHOOSEPIXELFORMATARB_T) (HDC, const int *, const FLOAT *, unsigned int, int *, unsigned int *);   /** wglChoosePixelFormatARB typedef*/

typedef BOOL (WINAPI * WGLGETPIXELFORMATATTRIBIVARB_T) (HDC, int, int, unsigned int, const int *, int *);   /* wglGetPixelFormatAttribivARB typedef */

typedef const char *(APIENTRY * WGLGETEXTENSIONSSTRINGEXT_T)( void );   /* wglGetExtensionStringEXT typedef */

typedef const char *(APIENTRY * WGLGETEXTENSIONSSTRINGARB_T)( HDC );    /* wglGetExtensionStringARB typedef */

typedef HGLRC (APIENTRY * WGLCREATECONTEXTATTRIBSARB)(HDC,HGLRC hShareContext,const int *attribList);			/*  */



/*		*/
typedef void (APIENTRY * PFNGLATTACHSHADERPROC) (GLunsigned int program, GLunsigned int shader);
typedef void (APIENTRY * PFNGLBINDBUFFERPROC) (GLunsigned int target, GLunsigned int buffer);
typedef void (APIENTRY * PFNGLBINDVERTEXARRAYPROC) (GLunsigned int array);
typedef void (APIENTRY * PFNGLBUFFERDATAPROC) (GLunsigned int target, ptrdiff_t size, const GLvoid *pair, GLunsigned int usage);
typedef void (APIENTRY * PFNGLCOMPILESHADERPROC) (GLunsigned int shader);
typedef GLunsigned int (APIENTRY * PFNGLCREATEPROGRAMPROC) (void);
typedef GLunsigned int (APIENTRY * PFNGLCREATESHADERPROC) (GLunsigned int type);
typedef void (APIENTRY * PFNGLDELETEBUFFERSPROC) (GLsizei n, const GLunsigned int *buffers);
typedef void (APIENTRY * PFNGLDELETEPROGRAMPROC) (GLunsigned int program);
typedef void (APIENTRY * PFNGLDELETESHADERPROC) (GLunsigned int shader);
typedef void (APIENTRY * PFNGLDELETEVERTEXARRAYSPROC) (GLsizei n, const GLunsigned int *arrays);
typedef void (APIENTRY * PFNGLDETACHSHADERPROC) (GLunsigned int program, GLunsigned int shader);
typedef void (APIENTRY * PFNGLENABLEVERTEXATTRIBARRAYPROC) (GLunsigned int index);
typedef void (APIENTRY * PFNGLGENBUFFERSPROC) (GLsizei n, GLunsigned int *buffers);
typedef void (APIENTRY * PFNGLGENVERTEXARRAYSPROC) (GLsizei n, GLunsigned int *arrays);
typedef GLint (APIENTRY * PFNGLGETATTRIBLOCATIONPROC) (GLunsigned int program, const char *name);
typedef void (APIENTRY * PFNGLGETPROGRAMINFOLOGPROC) (GLunsigned int program, GLsizei bufSize, GLsizei *length, char *infoLog);
typedef void (APIENTRY * PFNGLGETPROGRAMIVPROC) (GLunsigned int program, GLunsigned int pname, GLint *params);
typedef void (APIENTRY * PFNGLGETSHADERINFOLOGPROC) (GLunsigned int shader, GLsizei bufSize, GLsizei *length, char *infoLog);
typedef void (APIENTRY * PFNGLGETSHADERIVPROC) (GLunsigned int shader, GLunsigned int pname, GLint *params);
typedef void (APIENTRY * PFNGLLINKPROGRAMPROC) (GLunsigned int program);
//typedef void (APIENTRY * PFNGLSHADERSOURCEPROC) (GLunsigned int shader, GLsizei count, const char* *string, const GLint *length);
typedef void (APIENTRY * PFNGLUSEPROGRAMPROC) (GLunsigned int program);
typedef void (APIENTRY * PFNGLVERTEXATTRIBPOINTERPROC) (GLunsigned int index, GLint size, GLunsigned int type, GLboolean normalized, GLsizei stride,
                                                        const GLvoid *pointer);
typedef void (APIENTRY * PFNGLBINDATTRIBLOCATIONPROC) (GLunsigned int program, GLunsigned int index, const char *name);
typedef GLint (APIENTRY * PFNGLGETUNIFORMLOCATIONPROC) (GLunsigned int program, const char *name);
typedef void (APIENTRY * PFNGLUNIFORMMATRIX4FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRY * PFNGLACTIVETEXTUREPROC) (GLunsigned int textureArray);
typedef void (APIENTRY * PFNGLUNIFORM1IPROC) (GLint location, GLint v0);
typedef void (APIENTRY * PFNGLGENERATEMIPMAPPROC) (GLunsigned int target);
typedef void (APIENTRY * PFNGLDISABLEVERTEXATTRIBARRAYPROC) (GLunsigned int index);
typedef void (APIENTRY * PFNGLUNIFORM3FVPROC) (GLint location, GLsizei count, const GLfloat *value);
typedef void (APIENTRY * PFNGLUNIFORM4FVPROC) (GLint location, GLsizei count, const GLfloat *value);


/*	framebuffer	*/
typedef void (APIENTRY * PFNGLBINDFRAMEBUFFERPROC) (GLunsigned int target, GLunsigned int framebuffer);
typedef void (APIENTRY * PFNGLBINDRENDERBUFFERPROC) (GLunsigned int target, GLunsigned int renderbuffer);
typedef void (APIENTRY * PFNGLBLITFRAMEBUFFERPROC) (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLunsigned int filter);
typedef GLunsigned int (APIENTRY * PFNGLCHECKFRAMEBUFFERSTATUSPROC) (GLunsigned int target);
typedef void (APIENTRY * PFNGLDELETEFRAMEBUFFERSPROC) (GLsizei n, const GLunsigned int* framebuffers);
typedef void (APIENTRY * PFNGLDELETERENDERBUFFERSPROC) (GLsizei n, const GLunsigned int* renderbuffers);
typedef void (APIENTRY * PFNGLFRAMEBUFFERRENDERBUFFERPROC) (GLunsigned int target, GLunsigned int attachment, GLunsigned int renderbuffertarget, GLunsigned int renderbuffer);
typedef void (APIENTRY * PFNGLFRAMEBUFFERTEXTURE1DPROC) (GLunsigned int target, GLunsigned int attachment, GLunsigned int textarget, GLunsigned int texture, GLint level);
typedef void (APIENTRY * PFNGLFRAMEBUFFERTEXTURE2DPROC) (GLunsigned int target, GLunsigned int attachment, GLunsigned int textarget, GLunsigned int texture, GLint level);
typedef void (APIENTRY * PFNGLFRAMEBUFFERTEXTURE3DPROC) (GLunsigned int target, GLunsigned int attachment, GLunsigned int textarget, GLunsigned int texture, GLint level, GLint layer);
typedef void (APIENTRY * PFNGLFRAMEBUFFERTEXTURELAYERPROC) (GLunsigned int target,GLunsigned int attachment, GLunsigned int texture,GLint level,GLint layer);
typedef void (APIENTRY * PFNGLGENFRAMEBUFFERSPROC) (GLsizei n, GLunsigned int* framebuffers);
typedef void (APIENTRY * PFNGLGENRENDERBUFFERSPROC) (GLsizei n, GLunsigned int* renderbuffers);
typedef void (APIENTRY * PFNGLGENERATEMIPMAPPROC) (GLunsigned int target);
typedef void (APIENTRY * PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC) (GLunsigned int target, GLunsigned int attachment, GLunsigned int pname, GLint* params);
typedef void (APIENTRY * PFNGLGETRENDERBUFFERPARAMETERIVPROC) (GLunsigned int target, GLunsigned int pname, GLint* params);
typedef GLboolean (APIENTRY * PFNGLISFRAMEBUFFERPROC) (GLunsigned int framebuffer);
typedef GLboolean (APIENTRY * PFNGLISRENDERBUFFERPROC) (GLunsigned int renderbuffer);
typedef void (APIENTRY * PFNGLRENDERBUFFERSTORAGEPROC) (GLunsigned int target, GLunsigned int internalformat, GLsizei width, GLsizei height);
typedef void (APIENTRY * PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC) (GLunsigned int target, GLsizei samples, GLunsigned int internalformat, GLsizei width, GLsizei height);




/**/
PFNGLATTACHSHADERPROC glAttachShader;
PFNGLBINDBUFFERPROC glBindBuffer;
PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
PFNGLBUFFERDATAPROC glBufferData;
PFNGLCOMPILESHADERPROC glCompileShader;
PFNGLCREATEPROGRAMPROC glCreateProgram;
PFNGLCREATESHADERPROC glCreateShader;
PFNGLDELETEBUFFERSPROC glDeleteBuffers;
PFNGLDELETEPROGRAMPROC glDeleteProgram;
PFNGLDELETESHADERPROC glDeleteShader;
PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;
PFNGLDETACHSHADERPROC glDetachShader;
PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
PFNGLGENBUFFERSPROC glGenBuffers;
PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation;
PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
PFNGLGETPROGRAMIVPROC glGetProgramiv;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
PFNGLGETSHADERIVPROC glGetShaderiv;
PFNGLLINKPROGRAMPROC glLinkProgram;
PFNGLSHADERSOURCEPROC glShaderSource;
PFNGLUSEPROGRAMPROC glUseProgram;
PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation;
PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
//PFNGLACTIVETEXTUREPROC glActiveTexture;
PFNGLUNIFORM1IPROC glUniform1i;
PFNGLGENERATEMIPMAPPROC glGenerateMipmap;
PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;
PFNGLUNIFORM3FVPROC glUniform3fv;
PFNGLUNIFORM4FVPROC glUniform4fv;




static void  ExCreatePFD( void* pPFD, int colorbits, int depthbits, int stencilbits){

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

static void  ExCreatePFD2( void *pPFD){

	PIXELFORMATDESCRIPTOR pfd = {0};

	// default engine Description allocated on the heap.
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags  =  PFD_SUPPORT_OPENGL
	| PFD_DRAW_TO_WINDOW
	| PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.cColorBits = 24;
	pfd.cDepthBits = 16;
	pfd.cAccumBits = 0;
	pfd.cStencilBits = 0;
	pfd.cAlphaBits = 0;
	memcpy(pPFD,&pfd, sizeof(PIXELFORMATDESCRIPTOR));
}


static ExOpenGLContext create_temp_gl_context(HWND window){
	PIXELFORMATDESCRIPTOR pfd;
	ExOpenGLContext gl_context,hrc;
	int npixelFormat;
	HDC hDC;
	/*	Create Pixel Description	*/
	ExCreatePFD(&pfd,32,24,0);
	hDC = GetDC(window);    /*Get device context*/

	/*	Choose Pixel Format.	*/
	if(!(npixelFormat = ChoosePixelFormat(hDC,(const PIXELFORMATDESCRIPTOR*)&pfd))){
		ExIsWinError(npixelFormat);
		return NULL;
	}

	/*	Set Pixel format	*/
	if(!SetPixelFormat(hDC, npixelFormat,(const PIXELFORMATDESCRIPTOR*)&pfd)){
		wExDevPrintf(EX_TEXT("Failed to Set PixelFormat : %s\n"), ExGetErrorMessage(GetLastError()));
		return NULL;
	}

	/*	Create OpenGL Context	*/
	if(!(gl_context = wglCreateContext(hDC))){
		wExDevPrintf(EX_TEXT("Failed to Create OpenGL Context : %s\n"), ExGetErrorMessage(GetLastError()));
		MessageBox(NULL, EX_TEXT("Failed to Create Window OpenGL Context"), EX_TEXT("ERROR"), MB_OK | MB_ICONERROR);
		return NULL;
	}


	/*	Make Current Context On this Thread	*/
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


static HWND create_temp_gl_win(ExOpenGLContext* pglc_context){
    ExWin hwnd;
    ExOpenGLContext glc;
    WNDCLASSEX  wc= {0};
    #define TEMP_WINDOW_CLASS EX_TEXT("temp")
    wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wc.lpfnWndProc = ExMainWndProc;
	wc.hInstance = GetModuleHandle(NULL);
    wc.hIcon = (HICON)LoadIcon(wc.hInstance,NULL);
    wc.hCursor = LoadCursor(wc.hInstance, NULL);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpfnWndProc = ExMainWndProc;
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


ExOpenGLContext  ExCreateGLContext(ExWin window, ExOpenGLContext shared){
	ExOpenGLContext glc = NULL;
	unsigned int render_vendor;


	WGLSWAPINTERVALEXT_T wglSwapintervalEXT;
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
	int major = 0, minor = 0;
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
	glGetintegerv(GL_MAJOR_VERSION, &major);
	glGetintegerv(GL_MINOR_VERSION, &minor);

	//ExGLPrintDevInfo();
	hDC = GetDC(window);
	/**
       \ TODO change the condition.
	*/
   /**
       Create all entry point to create extension openGL context.
   */
	wglSwapintervalEXT =            (WGLSWAPINTERVALEXT_T)GL_GET_PROC("wglSwapintervalEXT");
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
	WGL_CONTEXT_MAJOR_VERSION_ARB, !major ? ((ExGetOpenGLVersion(NULL,NULL) - (ExGetOpenGLVersion(NULL,NULL) % 100)) / 100) : major,
       WGL_CONTEXT_MINOR_VERSION_ARB, minor ? ExGetOpenGLVersion(NULL,NULL) % 100 : minor,
       WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
       #ifdef EX_DEBUG
       WGL_CONTEXT_FLAGS_ARB,WGL_CONTEXT_DEBUG_BIT_ARB,
       #endif
       NULL
   };


   /*TODO: Naming between context attributes and for choosing a pixel-format
       Create pixel format attributes
   */
	ExCreateContextAttrib(hDC,&pixAttribs[0],(int*)&dataSize);


	if(!wglChoosePixelFormatARB(hDC, &pixAttribs[0], NULL, 1, pixelFormat, (unsigned int*)&nResults[0]))
		ExError(EX_TEXT("function : wglChoosePixelFormatARB Failed"));


	if(ExDestroyGLContext(hDC,glc)){  /*  destroy temp context    */
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

   /*
       Create OpenGL Context.
   */
   switch(ExGetOpenGLVendor()){
	   case EX_AMD:
		   break;
	   case EX_NVIDIA:
		   break;
	   case EX_INTEL:
		   break;
	   default:
		   break;
   }

   if(!(glc = wglCreateContextAttribsARB(hDC, NULL,pixAttribs))){
       //ExDevPrintf(EX_TEXT("Failed to Create OpenGL Context ARB | %s.\n"),glewGetErrorString(glGetError()));
       //MessageBoxA(NULL,  (LPCSTR)glewGetErrorString(glGetError()),"Error | OpenGL Context",MB_OK | MB_ICONERROR);
		ExMessageBox(NULL, EX_TEXT(""), EX_TEXT(""), MB_OK |MB_ICONERROR);
   }


   if(!ReleaseDC(WindowFromDC(wglGetCurrentDC()),wglGetCurrentDC()))
       wprintf(EX_TEXT("Failed to Release DC : %s \n"),ExGetErrorMessage(GetLastError()));


   /*	get opengl functions */



	return glc;
}



void  ExCreateContextAttrib(ExWindowContext hDc, int* attribs,int* size){
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


ExOpenGLContext  ExCreateGLSharedContext(ExWin window, ExOpenGLContext glc){
	return ExCreateGLContext(window,glc);

}


/*
DECLSPEC void  ExInitExtension(ExWin hWnd,WindowContext deviContext,HGLRC hr){
	// temp variable
	HGLRC tempHRC = hr;PIXELFORMATDESCRIPTOR pfd;
	int majorVer, minorVer;
	// get information
	int attrib[] = { WGL_NUMBER_PIXEL_FORMATS_ARB };
	int nResults[1] = {0};
	int pixFmt = 1;

	if(wglGetPixelFormatAttribivARB(deviContext, pixFmt,0, 1, attrib, nResults))
		printf("This Hardware Supports %i PixelFormat.\n", *nResults);
	// Get Current OpenGL Version

	glGetintegerv(GL_MAJOR_VERSION, &majorVer);
	glGetintegerv(GL_MINOR_VERSION, &minorVer);
	// version
	int attribs[] ={
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


	int dataSize;
	int* pixAttribs = NULL;
	// Create Context Attrib
	ExCreateContextAttrib(deviContext,&pixAttribs,&dataSize,&engineDescription);

	// mayabe change to differnect function depenpded on hardware


	int pixelFormat[1];
	if(wglChoosePixelFormatARB(deviContext, &pixAttribs[0], NULL, 1, pixelFormat,(unsigned int*)&nResults[0]))
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



 ExBoolean  ExDestroyGLContext(ExWindowContext drawable, ExOpenGLContext glc){
	ExBoolean hr;
	// if hDC is null
	if(!drawable)
		drawable = ExGetCurrentGLDC();

	ExMakeGLCurrent(0,0);
	ExIsError(hr = wglDeleteContext(glc));
	DeleteDC(drawable);
	return hr;
}

 ExBoolean  ExGLFullScreen(ExBoolean cdsfullscreen, ExWin window, unsigned int screenIndex, const int* screenRes){

	RECT rect;
	DEVMODE dm;
	DISPLAY_DEVICE dd;
	int cdsRet;

	if(!window)
		return EX_FALSE;
	// going for fullscreen.
	if(cdsfullscreen){
		// Get Window Rect
		GetWindowRect(window,&rect);

		dd = ExGetMonitor(screenIndex);
		dm;
		if(!unsigned intDisplaySettings(dd.DeviceName, unsigned int_CURRENT_SETTINGS, &dm))
			wExDevPrintf(EX_TEXT("unsigned intDisplay Settings Failed | %s.\n"), ExGetErrorMessage(GetLastError()));
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
			// glw_state.allowdisplaydepthchange )
			dm.dmBitsPerPel = ExOpenGLGetAttribute(EX_OPENGL_RED_SIZE,NULL) +
				ExOpenGLGetAttribute(EX_OPENGL_GREEN_SIZE,NULL) +
				ExOpenGLGetAttribute(EX_OPENGL_BLUE_SIZE,NULL) +
				ExOpenGLGetAttribute(EX_OPENGL_BLUE_SIZE,NULL);
		dm.dmFields |= DM_BITSPERPEL;
		//ExPrintf("Using colorbits of %d\n", engineDescription.ColorBits);
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



/*  read more about DwmEnableBlurBehindWindow : http://msdn.microsoft.com/en-us/library/windows/desktop/aa969508(v=vs.85).aspx	*/
void ExSetGLTransparent(ExWin window,unsigned int iunsigned int){

	DWM_BLURBEHIND bb = {0};
	HRESULT hr;
	// cheap way of creating the effect.
	bb.hRgnBlur = CreateRectRgn(0,0,1,1);
	bb.dwFlags = DWM_BB_ENABLE | DWM_BB_BLURREGION | DWM_BB_TRANSITIONONMAXIMIZED;
	bb.fTransitionOnMaximized = EX_TRUE;
	if(iunsigned int & 0x1)
		bb.fEnable = EX_TRUE;
	else
		bb.fEnable = EX_FALSE;
	hr = DwmEnableBlurBehindWindow(window, &bb);
}



/*
DECLSPEC OpenGLContext  ExCreateSharedGLContext(HDC openglHDC, OpenGLContext sharedHRC, WindowContext hDC){
	HGLRC hrc2;
	int majorVer, minorVer;
	int dataSize;
	int nResults[1];
	int* pixAttribs = NULL;
	PIXELFORMATDESCRIPTOR pfd;

	// Create Context Attrib
	ExCreateContextAttrib(hDC,&pixAttribs,&dataSize,&engineDescription);

	// mayabe change to differnect function depenpded on hardware
	int pixelFormat[1];
	if(!wglChoosePixelFormatARB(hDC, &pixAttribs[0], NULL, 1, pixelFormat,(unsigned int*)&nResults[0]))
		ExDevGLPrintfc("Failed to Choose PixelFormat Number %i.\n",EX_CONSOLE_RED,nResults[0]);
	if(!SetPixelFormat(hDC, pixelFormat[0], &pfd))
		ExDevWindowPrintfc(EX_TEXT("Failed to Set PixelFormat Number %i.\n"),EX_CONSOLE_RED,nResults[0]);
	free(pixAttribs);

	glGetintegerv(GL_MAJOR_VERSION, &majorVer);
	glGetintegerv(GL_MINOR_VERSION, &minorVer);
	int attribs[] ={
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

DECLSPEC unsigned int ELTAPIFASTENTRY ExGetGPUMemoryUsage(void){
	int pvalue;
	glGetintegerv(GL_GPU_MEMORY_INFO_EVICTED_MEMORY_NVX ,&pvalue);
	return pvalue;
}
DECLSPEC int ELTAPIFASTENTRY ExMaxCombinedTexture(void){
	int pvalue;
	glGetintegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS ,&pvalue);
	return pvalue;
}
DECLSPEC int ELTAPIFASTENTRY ExMaxTextureunsigned ints(void){
	int pvalue;
	glGetintegerv(GL_MAX_TEXTURE_IMAGE_UNITS ,&pvalue);
	return pvalue;
}

*/

void ExOpenGLSetAttribute(unsigned int attr, int value){
	pixAtt[PIXATTOFFSET + (2 * attr) + 1] = value;
}

int ExOpenGLGetAttribute(unsigned int attr, int* value){
	if(value)
		value = (unsigned int)pixAtt[PIXATTOFFSET + (2 * attr) + 1];
	return pixAtt[PIXATTOFFSET + (2 * attr) + 1];
}

void ExOpenGLResetAttributes(void){




}


ERESULT ExOpenGLSetVSync(ExBoolean enabled, ExWin window){
	WGLSWAPINTERVALEXT_T wglSwapintervalEXT = (WGLSWAPINTERVALEXT_T)GL_GET_PROC("wglSwapintervalEXT");
    if(wglSwapintervalEXT){
        glXSwapintervalEXT( enabled);
        return EX_TRUE;
    }
    else
    	return EX_FALSE;
}


