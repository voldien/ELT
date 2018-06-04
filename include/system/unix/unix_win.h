/**
	ELT (Engine Library Toolkit) is a cross platform engine toolkit
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
#ifndef _UNIX_WIN_H_
#define _UNIX_WIN_H_ 1
#include"system.h"

#ifdef __cplusplus /* C++ environment */
extern "C" {
#endif

/**
 *	@Return
 */
extern ELTDECLSPEC ExWin ELTAPIENTRY ExCreateNativeWindow(int x, int y,
		int width, int height);

/**
 *   @Return
 */
extern ELTDECLSPEC ExWin ELTAPIENTRY ExCreateGLWindow(int x, int y, int width,
		int height, void** glx_window);

/**
 *
 */
extern ELTDECLSPEC int ExSupportOpenGL(void);

#ifdef __cplusplus /* C++ environment */
};
#endif

#endif
