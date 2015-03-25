/*
===========================================================================
Copyright (C) 2014 BroodCity Software, Inc. Voldemor2009@hotmail.com

*/
#ifndef WIN_GL_H
#define WIN_GL_H
#include"./../../EngineAssembly.h"
#ifdef EX_WINDOWS

#include"./../elt_gl.h"
#include"win_win32.h"
extern OpenGLContext hrc;
extern OpenGLContext hrc2;
#ifdef __cplusplus // C++ environment
extern "C"{
#endif

// Get OpenGL Context of This Application 
DECLSPEC OpenGLContext ELTAPIFASTENTRY ExGetOpenGLContext(void);
// Get OpenGL Context 2 of This Application 
DECLSPEC OpenGLContext ELTAPIFASTENTRY ExGetOpenGLContext2(void);

#define EX_VENDOR_AMD 0x1
#define EX_VENDOR_NVIDIA 0x2
#define EX_VENDOR_INTEL 0x4





/*	Release The OpenGL Context.		*/
extern DECLSPEC void ELTAPIENTRY ExReleaseGL(void);
/*	Release OpenGL Context	*/
extern DECLSPEC void ELTAPIENTRY ExReleaseGLContext(HGLRC hrc);


// Initlize OpenGL Extension.
extern DECLSPEC void ELTAPIENTRY ExInitExtension(ExWin hWnd,HDC deviContext,OpenGLContext hr);

/*		*/
extern DECLSPEC OpenGLContext ELTAPIENTRY ExCreateSharedGLContext(HDC openglHDC, OpenGLContext sharedHRC, HDC hDC);

//Initlize OpenGL States




/* Print Information About OpenGL Info*/
extern DECLSPEC void ELTAPIENTRY ExGLPrintDevInfo(void);



//DECLSPEC const gluByte* ExGet
extern DECLSPEC Uint32 ELTAPIENTRY ExGetNVvRam(void);

extern DECLSPEC Uint32 ELTAPIFASTENTRY ExGetGPUMemoryUsage(void);
extern DECLSPEC Int32 ELTAPIFASTENTRY ExMaxCombinedTexture(void);
extern DECLSPEC Int32 ELTAPIFASTENTRY ExMaxTextureUints(void);


#ifdef __cplusplus // C++ environment
};
#endif

#endif
#endif