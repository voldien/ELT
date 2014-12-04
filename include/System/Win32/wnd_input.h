/*
===========================================================================
Copyright (C) 2014 BroodCity Software, Inc. Voldemor2009@hotmail.com

*/
#ifndef WND_INPUT_H
#define WND_INPUT_H
#include"win_win32.h"

#ifdef INTERNAL_ENGINEX
	#include<BaseTsd.h>
	#include<dinput.h>
	#include<dinputd.h>
	#include<Xinput.h>
	#include<Dbt.h>
	#include<oleauto.h>
	#include<shellapi.h>
	#pragma warning( disable : 4996 ) // disable deprecated warning 
	#pragma comment(lib, "dinput8.lib")
	extern IDirectInput8* g_pDI;
#endif
#ifndef DIRECTINPUT_VERSION
#	define DIRECTINPUT_VERSION 0x800
#endif

/*	Get Pointer to Direct Input Device. Explicit to IDirectInput8 */
extern DECLSPEC HANDLE ELTAPIENTRY ExGetDirectInput(Void);
/*			Initialize 		*/
extern DECLSPEC ERESULT ELTAPIENTRY ExInitDirectInput(Uint32 flag);
/* Initlize Direct Input Devices	*/
extern DECLSPEC ERESULT ELTAPIENTRY ExInitDirectInputDevice(ExWin hWnd, Uint32 flag);
/* Shut Down Direct*/
extern DECLSPEC ERESULT ELTAPIENTRY ExShutDownDirect(Void);

/* 			Initialize		*/
extern DECLSPEC ERESULT ELTAPIENTRY ExInitRawInput(ExWin hWnd,ULLong flag);

//extern DECLSPEC Boolean ELTAPIENTRY ExIsXInputDevice(const ExGUID* pGuidProductFromDirectInput);

#endif
