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
/*	
	//Initlize Direct Sound	
*/
DECLSPEC ERESULT ELTAPIENTRY ExInitDirectSound(ExWin hWnd, Uint32 flag);
/*
	//
*/
DECLSPEC ERESULT ELTAPIENTRY ExSetDirectSoundCooperative(ExWin hWnd, Uint32 flag);


/* Release The DirectSound*/
DECLSPEC Void ELTAPIENTRY ExReleaseDirectSound(Void);


#endif