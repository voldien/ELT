/**
    ELT (Engine Library Toolkit) is a multi platform engine toolkit
    Copyright (C) 2014  Valdemar Lindberg

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

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

#ifdef  __cplusplus	/* C++ Environment */
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
#ifdef  __cplusplus	/* C++ Environment */
}
#endif
#endif
