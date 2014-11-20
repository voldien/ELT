/*
===========================================================================
Copyright (C) 2014 BroodCity Software, Inc. Voldemor2009@hotmail.com

*/
#ifndef WIN_GL_H
#define WIN_GL_H
#include"./../../EngineAssembly.h"


#include"./../elt_gl.h"
#include"win_win32.h"
extern OpenGLContext hrc;
extern OpenGLContext hrc2;
#ifdef EX_CPP
extern "C"{
#endif

// Get OpenGL Context of This Application 
DECLSPEC OpenGLContext ELTAPIFASTENTRY ExGetOpenGLContext(Void);
// Get OpenGL Context 2 of This Application 
DECLSPEC OpenGLContext ELTAPIFASTENTRY ExGetOpenGLContext2(Void);

#define EX_VENDOR_AMD 0x1
#define EX_VENDOR_NVIDIA 0x2
#define EX_VENDOR_INTEL 0x4





/*	Release The OpenGL Context.		*/
extern DECLSPEC Void ELTAPIENTRY ExReleaseGL(Void);
/*	Release OpenGL Context	*/
extern DECLSPEC Void ELTAPIENTRY ExReleaseGLContext(HGLRC hrc);


// Initlize OpenGL Extension.
extern DECLSPEC Void ELTAPIENTRY ExInitExtension(ExWin hWnd,HDC deviContext,OpenGLContext hr);

/*		*/
extern DECLSPEC OpenGLContext ELTAPIENTRY ExCreateSharedGLContext(HDC openglHDC, OpenGLContext sharedHRC, HDC hDC);

//Initlize OpenGL States




/* Print Information About OpenGL Info*/
extern DECLSPEC Void ELTAPIENTRY ExGLPrintDevInfo(Void);



//DECLSPEC const gluByte* ExGet
extern DECLSPEC Uint32 ELTAPIENTRY ExGetNVvRam(Void);

extern DECLSPEC Uint32 ELTAPIFASTENTRY ExGetGPUMemoryUsage(Void);
extern DECLSPEC Int32 ELTAPIFASTENTRY ExMaxCombinedTexture(Void);
extern DECLSPEC Int32 ELTAPIFASTENTRY ExMaxTextureUints(Void);


#ifdef EX_CPP
};
#endif
#endif