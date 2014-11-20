/*
===========================================================================
Copyright (C) 2014 BroodCity Software, Inc. Voldemor2009@hotmail.com

*/
#ifndef WIN_DIRECTX_H
#define WIN_DIRECTX_H
#include"./../../EngineAssembly.h"
#if defined(EX_WINDOWS) && defined(EX_INCLUDE_DIRECTX)

#ifdef __cplusplus // C++ environment
extern "C"{
#endif
/*
	// Get 3D Context
*/
extern DECLSPEC HANDLE ELTAPIFASTENTRY ExGetD3D(void);
/*
	// Get Direct3D Context
*/
extern DECLSPEC HANDLE ELTAPIFASTENTRY ExGetDirect3D(void);
/*
	// Get Direct3D Context from window.
*/
//extern DECLSPEC HANDLE ELTAPIENTRY ExGetDirect3D(ExWin window);

/*
	// Initialize Direct X
*/
extern DECLSPEC ERESULT ELTAPIENTRY ExInitDirectX(ExWin hWnd);

/*
	//
*/
extern DECLSPEC void ELTAPIFASTENTRY ExDirectXBegin(void);
/*
	//
*/
extern DECLSPEC void ELTAPIFASTENTRY ExDirectXEnd(void);
/*
	//
*/
extern DECLSPEC void ELTAPIFASTENTRY ExDirectXPresent(void);
/*
	//
*/
extern DECLSPEC void ELTAPIENTRY ExReleaseDirectX(void);
/*
	
*/
extern DECLSPEC void ELTAPIENTRY ExReleaseDirectXContext(void* d3d);
/*

*/
extern DECLSPEC void ELTAPIENTRY ExDirectFullScreen(Boolean fullscreen);

#ifdef __cplusplus // C++ environment
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
	#define ExDirectFullScreen(x)	EX_UNUSED(0)
#endif
#endif