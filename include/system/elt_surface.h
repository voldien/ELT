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
#define _ElT_SURFACE_H_ 1
#include"elt_win.h"

#define EXRGB_COLOR(r,g,b)	(r << 24) | (g << 16) | (b << 8)
#define EXRGBA_COLOR(r,g,b,a)	((r << 24) | (g << 16) | (b << 8) | a)

#define EX_RGB 0x20
#define EX_RGBA 0x40

typedef void* ExSurface;

#ifdef  __cplusplus	/* C++ Environment */
extern "C"{
#endif


/*	Create Surface	*/
extern DECLSPEC ExSurface ExCreateSurface(unsigned int width, unsigned height, unsigned int format);

/*	release surface.	*/
extern DECLSPEC int ExDestroySurface(ExSurface handle);

/**/
extern DECLSPEC void ExDisplaySurfaceToWindow(ExWin window,ExSurface surface);

/*	resize surface handle	*/
extern DECLSPEC int ExResizeSurface(ExSurface handle, unsigned int width, unsigned height);

/*	*/
extern DECLSPEC int ExGetSurfaceRect(ExSurface surface, ExRect* rect);

/*	set surface window	*/
extern DECLSPEC int ExSetSurfacePixel(ExSurface handle, unsigned int x, unsigned int y, unsigned long pixel);



/*	set fill color..	*/
extern DECLSPEC void ExFillRect(ExSurface handle, ExRect* rect, Uint32 color);

/**/
extern DECLSPEC ExUnlockSurface(ExSurface surface);

/**/
extern DECLSPEC ExLockSurface(ExSurface surface);

#ifdef  __cplusplus	/* C++ Environment */
}
#endif

#endif
