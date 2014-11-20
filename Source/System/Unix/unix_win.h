/*
===========================================================================
Copyright (C) 2014 BroodCity Software, Inc. Voldemor2009@hotmail.com

*/
#ifndef UNIX_WIN_H
#define UNIX_WIN_H
#include"./../../EngineAssembly.h"
#ifdef EX_LINUX
#ifdef __cplusplus // C++ environment
extern "C"{
#endif

extern Display *display;
extern DECLSPEC XID ELTAPIENTRY ExCreateNativeWindow(Int32 x, Int32 y, Int32 width, Int32 height);
extern DECLSPEC XID ELTAPIENTRY ExCreateGLWindow(Int32 x , Int32 y, Int32 width, Int32 height, void** glx_window);
extern DECLSPEC XID ELTAPIENTRY ExCreateSimpleGLWindow(Int32 x , Int32 y, Int32 width, Int32 height);
#ifdef __cplusplus // C++ environment
};
#endif

#endif
#endif
