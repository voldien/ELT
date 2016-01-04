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
#ifndef _ENGINE_ASSEMBLY_H_
#define _ENGINE_ASSEMBLY_H_ 1
#include"elt_def.h"
#include"ExNT.h"
#include"system/elt_event.h"
#include"EngineEx.h"
#include"ExCommon.h"


#if defined(EX_WINDOWS)
	#include<tchar.h>
	#ifdef EX_VC
		#include<strsafe.h>
	#endif
#elif defined(EX_LINUX)

#elif defined(EX_PNACL)
#	include<ppapi/c/ppb.h>
#elif defined(EX_ANDROID)
#   include<android/api-level.h>
#elif defined(EX_MAC)
#endif

#define EXCAST(type,y) (type)( ( y ) )

/*
 *	Engine Rendering Flags
 */
#define ENGINE_NATIVE (1 << 7)
#define EX_OPENGL (1 << 8)
#define EX_OPENGLES (1 << 9)
#define EX_OPENCL  (1 << 10)
#define EX_DIRECTX  (1 << 11)
#define EX_OPENGL_AND_OPENCL (ENGINE_OPENGL | ENGINE_OPENCL)
#define EX_VULKAN (1 << 12)
#define EX_RENDER_CONTEXT_DEBUG (1 << 12)


/*
 *	High layer flag.
 */

#define ELT_INIT_TIMER			0x00000001
#define ELT_INIT_VIDEO			0x00000020
#define ELT_INIT_AUDIO			0x00000010
#define ELT_INIT_JOYSTICK		0x00000200
#define ELT_INIT_EVENTS			0x00002000
#define ELT_INIT_GAMECONTROLLER 0x00004000
#define ELT_INIT_NET			0x00008000
#define ELT_INIT_DEBUG			0x00010000

#define ELT_INIT_EVERYTHING (							\
	ELT_INIT_VIDEO | ELT_INIT_AUDIO | ELT_INIT_JOYSTICK	\
 | ELT_INIT_TIMER | ELT_INIT_GAMECONTROLLER | ELT_INIT_EVENTS)


#include"elt_timer.h"
#include"system/elt_win.h"
#include"system/elt_errorhandler.h"
#include"system/elt_event.h"
#include"system/elt_net.h"
#include"elt_loadso.h"
#include"input/elt_keyboard.h"
#include"input/elt_mouse.h"
#include"input/elt_joystick.h"
#include"elt_cpuinfo.h"
#include"system/elt_gl.h"
#include"elt_timer.h"
#include"elt_alloc.h"
#include"math/matrix.h"
#include"system/android/elt_activity.h"

#endif
