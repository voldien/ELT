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
#ifdef  __cplusplus	/* C++ Environment */
extern "C"{
#endif

#define EX_VENDOR_AMD 0x1
#define EX_VENDOR_NVIDIA 0x2
#define EX_VENDOR_INTEL 0x4





/* Print Information About OpenGL Info*/
extern DECLSPEC void ELTAPIENTRY ExGLPrintDevInfo(void);



//DECLSPEC const gluByte* ExGet
extern DECLSPEC Uint32 ELTAPIENTRY ExGetNVvRam(void);

extern DECLSPEC Uint32 ELTAPIFASTENTRY ExGetGPUMemoryUsage(void);
extern DECLSPEC Int32 ELTAPIFASTENTRY ExMaxCombinedTexture(void);
extern DECLSPEC Int32 ELTAPIFASTENTRY ExMaxTextureUints(void);


#ifdef  __cplusplus	/* C++ Environment */
}
#endif

#endif
#endif
