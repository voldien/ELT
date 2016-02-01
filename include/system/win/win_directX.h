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
#ifndef _WIN_DIRECTX_H_
#define _WIN_DIRECTX_H_ 1
#include"./../../EngineAssembly.h"

#ifdef __cplusplus	/*	C++ Environment	*/
extern "C"{
#endif

typedef void* ExDX9D;
typedef void* ExDevice9D;


/*
 *	Get 3D Context
 *  @return
 */
extern DECLSPEC HANDLE ELTAPIFASTENTRY ExGetD3DContext(void);

/*
 *	Get Direct3D Context
 *   @return
 */
extern DECLSPEC HANDLE ELTAPIFASTENTRY ExGetDirect3DContext(void);

/*
 *    @return
 */
extern DECLSPEC ExDevice9D ELTAPIENTRY ExCreateDirectXContext(ExWin window);

/*
 *
 */
extern DECLSPEC void ELTAPIENTRY ExDestroyDirectXContext(ExDevice9D d3d);

/*
 *
 */
extern DECLSPEC void ELTAPIENTRY ExDirectFullScreen(ExBoolean fullscreen);

#ifdef __cplusplus	/*	C++ Environment	*/
}
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
