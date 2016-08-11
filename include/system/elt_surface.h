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
#ifndef _ELT_SURFACE_H_
#define _ELT_SURFACE_H_ 1
#include"elt_win.h"
#include"elt_event.h"
#include"../ExNT.h"

#define EX_RGB_COLOR(r,g,b)	(r << 24) | (g << 16) | (b << 8)
#define EX_RGBA_COLOR(r,g,b,a)	((r << 24) | (g << 16) | (b << 8) | a)

#define EX_RGB 0x20
#define EX_RGBA 0x40

typedef void* ExSurface;

#ifdef __cplusplus	/*	C++ Environment	*/
extern "C"{
#endif


/**
 *	Create Surface.
 *
 *	@Return
 */
extern ELTDECLSPEC ExSurface ELTAPIENTRY ExCreateSurface(unsigned int width, unsigned height, unsigned int format);

/**
 *	release surface.
 *
 *	@Return
 */
extern ELTDECLSPEC int ELTAPIFASTENTRY ExDestroySurface(ExSurface handle);

/*
 *
 */
extern ELTDECLSPEC void ExDisplaySurfaceToWindow(ExWin window,ExSurface surface);

/**
 *	Resize surface handle
 *
 *	@Return
 */
extern ELTDECLSPEC ERESULT ELTAPIENTRY ExResizeSurface(ExSurface handle, unsigned int width, unsigned height);

/*
 *
 *	@Return
 */
extern ELTDECLSPEC ERESULT ELTAPIENTRY ExGetSurfaceRect(ExSurface surface, ExRect* rect);

/*
 *	Set surface window
 *	@Return
 */
extern ELTDECLSPEC int ELTAPIENTRY ExSetSurfacePixel(ExSurface handle, unsigned int x, unsigned int y, unsigned long pixel);



/*
 *	Set fill color..
 */
extern ELTDECLSPEC void ELTAPIENTRY ExFillRect(ExSurface handle, ExRect* rect, Uint32 color);

/*
 *
 */
extern ELTDECLSPEC void ExUnlockSurface(ExSurface surface);

/*
 *
 */
extern ELTDECLSPEC void ExLockSurface(ExSurface surface);

#ifdef __cplusplus	/*	C++ Environment	*/
}
#endif

#endif
