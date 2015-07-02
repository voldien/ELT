/**
    ELT (Engine Library Toolkit) is a multi platform engine toolkit
    designed for OpenGL and OpenCL.
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

/*
=================================INFO===================================

    Info : The project is called ELT (Engine Library toolkit). however
    the syntax doesn't really live up to it. Because ExInit for initialize
    the project should have actually be named EltInit. That's because
    it's original names was EngineEx because it was a engine extension
    onto the current engine I was developing back in the old days.
    I would guess they are a bit synomny. however the Syntax is
    Ex[function name].

========================================================================
*/

// #define ENGINE_EX_STATIC_BUILD			// Use as Static Lib
// #define ENGINE_EX_STATIC_TO_DLL_BUILD	// Use as Static Lib to DLL
// #define ENGINE_EX_DLL_IMPORT				// Import DLL
// #define ENGINE_EX_DLL_INSIDE				// DLL inside of current DLL's Lib Connection File.
#ifndef _ENGINE_EX_API_
#define _ENGINE_EX_API_ 1


#include"ExPreProcessor.h"
// Library Import
//define EX_AUTO_LINKER
#ifdef ENGINE_EX_STATIC
#ifdef EX_VC
	// debug version
	#ifdef EX_DEBUG
		#ifdef EX_X86
			#pragma comment(lib, "EngineEx.lib")

		#elif EX_X64
			#pragma comment(lib, "EngineEx_64.lib")
		#endif
	// release version
	#elif defined(EX_RELEASE)
		#ifdef EX_X86
			#pragma comment(lib, "EngineEx.lib")
		#elif EX_X64
			#pragma comment(lib, "EngineEx_64.lib")
		#endif
	#endif
#elif defined(EX_BORDERLAND)
#elif defined(EX_LCC)
#elif defined(EX_LINUX)
	#ifdef EX_DEBUG
		#ifdef EX_X86
			#pragma comment(lib, "EngineExUnix.lib")
		#endif
	#endif
#elif defined(EX_APPLE)
	#pragma comment(lib, "EngineEx.lib")
#endif
#endif

#include"EngineAssembly.h"
#include"EngineEx.h"
#include"elt_thread.h"

#if defined(EX_WINDOWS)

#elif defined(EX_LINUX)

#elif defined(EX_MAC)

#elif defined(EX_ANDROID)

#elif defined(EX_PS4)

#elif defined(EX_PS3)

#elif defined(EX_PSP)

#elif defined(EX_WEB)

#elif defined(EX_PNACL)

#elif defined(EX_NACL)

#else
	#error "Error! no supporting Devices"   /**/
#endif

#include"ExCommon.h"

#endif
