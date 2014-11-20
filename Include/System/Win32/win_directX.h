/*
===========================================================================
Copyright (C) 2014 BroodCity Software, Inc. Voldemor2009@hotmail.com

*/
#ifndef WIN_DIRECTX_H
#define WIN_DIRECTX_H
#include"./../../EngineAssembly.h"
#if defined(EX_WINDOWS) && defined(EX_INCLUDE_DIRECTX)

#ifdef EX_CPP
extern "C"{
#endif
// change if needed
extern DECLSPEC Void* ELTAPIFASTENTRY ExGetD3D(Void);
extern DECLSPEC Void* ELTAPIFASTENTRY ExGetDirect3D(Void);

/*
	// Initialize Direct X
*/
extern DECLSPEC ERESULT ELTAPIENTRY ExInitDirectX(HWND hWnd, EngineDescription* desc);

/**/
extern DECLSPEC Void ELTAPIFASTENTRY ExDirectXBegin(Void);
extern DECLSPEC Void ELTAPIFASTENTRY ExDirectXEnd(Void);
extern DECLSPEC Void ELTAPIFASTENTRY ExDirectXPresent(Void);
extern DECLSPEC Void ELTAPIFASTENTRY ExDirectClear(Float* colour);

extern DECLSPEC Void ELTAPIENTRY ExReleaseDirectX(Void);
extern DECLSPEC Void ELTAPIENTRY ExReleaseDirectXContext(Void* d3d);

#ifdef EX_CPP
}
#endif
#endif

#if !defined(EX_WINDOWS) || !defined(EX_INCLUDE_DIRECTX)
#define ExInitDirectX(x,y) EX_UNUSED(0)
#define ExBeginDirectX EX_UNUSED(0)
#define ExEndDirectX EX_UNUSED(0)
#define ExPresentDirectX EX_UNUSED(0)
#define ExClearDirect(x) EX_UNUSED(0)
#define ExReleaseDirect EX_UNUSED(0)
#define ExReleaseDirectContext(x) EX_UNUSED(0)
#endif
#endif