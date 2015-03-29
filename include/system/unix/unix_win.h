/*
========================================================================
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
#ifndef _UNIX_WIN_H_
#define _UNIX_WIN_H_ 1
#include"./../../EngineAssembly.h"

#ifdef EX_LINUX
#ifdef __cplusplus // C++ environment
extern "C"{
#endif

extern Display *display;

extern DECLSPEC XID ELTAPIENTRY ExCreateNativeWindow(Int32 x, Int32 y, Int32 width, Int32 height);

extern DECLSPEC XID ELTAPIENTRY ExCreateGLWindow(Int32 x , Int32 y, Int32 width, Int32 height, void** glx_window);



extern DECLSPEC int ExSupportOpenGL(void);


#ifdef __cplusplus // C++ environment
};
#endif

#endif
#endif
