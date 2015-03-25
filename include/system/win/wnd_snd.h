/*
===========================================================================
Copyright (C) 2014 BroodCity Software, Inc. Voldemor2009@hotmail.com

*/
#ifndef WND_SND_H
#define WND_SND_H
#include"win_win32.h"
#if defined(EX_WINDOWS)
	#pragma comment(lib, "dsound.lib")
	#include <windows.h>
	#include <mmsystem.h>
	#include <dsound.h>
	#include <stdio.h>
	extern LPDIRECTSOUND8 pDS;
#endif

#ifdef __cplusplus // C++ environment
extern "C"{
#endif

/*	
	//Initlize Direct Sound	
*/
extern DECLSPEC ERESULT ELTAPIENTRY ExInitDirectSound(ExWin hWnd, Uint32 flag);
/*
	//
*/
extern DECLSPEC ERESULT ELTAPIENTRY ExSetDirectSoundCooperative(ExWin hWnd, Uint32 flag);


/* Release The DirectSound*/
extern DECLSPEC void ELTAPIENTRY ExReleaseDirectSound(void);
#ifdef __cplusplus // C++ environment
}
#endif
#endif