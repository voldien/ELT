/*
===========================================================================
Copyright (C) 2014 BroodCity Software, Inc. Voldemor2009@hotmail.com

*/
#ifndef WND_INPUT_H
#define WND_INPUT_H
#include"win_win32.h"

#ifdef INTERNAL_ENGINEX

//	extern IDirectInput8* g_pDI;
#endif
#ifndef DIRECTINPUT_VERSION
#	define DIRECTINPUT_VERSION 0x800
#endif
#ifdef __cplusplus // C++ environment
extern "C"{
#endif

/*	Get Pointer to Direct Input Device. Explicit to IDirectInput8 */
extern DECLSPEC HANDLE ELTAPIENTRY ExGetDirectInput(void);
/*			Initialize 		*/
extern DECLSPEC ERESULT ELTAPIENTRY ExInitDirectInput(Uint32 flag);
/* Initlize Direct Input Devices	*/
extern DECLSPEC ERESULT ELTAPIENTRY ExInitDirectInputDevice(ExWin hWnd, Uint32 flag);
/* Shut Down Direct*/
extern DECLSPEC ERESULT ELTAPIENTRY ExShutDownDirect(void);

/* 			Initialize		*/
extern DECLSPEC ERESULT ELTAPIENTRY ExInitRawInput(ExWin hWnd,ULLong flag);

//extern DECLSPEC Boolean ELTAPIENTRY ExIsXInputDevice(const ExGUID* pGuidProductFromDirectInput);

#ifdef __cplusplus // C++ environment
}
#endif

#endif
