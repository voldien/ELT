/*
===========================================================================
Copyright (C) 2014 BroodCity Software, Inc. Voldemor2009@hotmail.com

this file is a part of ELT source code.

ELT source code is free software; you can redistribute it
and/or modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of the License,
or (at your option) any later version.

ELT source code is distributed in the hope that it will be
useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

*/

//**************************************************************//
//																//
//	CopyRight � BroodCity 2014 voldemor2009@hotmail.com			//
//																//
//	EngineEx is Extension version of a Fundemental Engine		//
//	Providing More than Basic to run a Game Engine. EngineEx	//
//	Support OPENGL & DIRECTX Rendering Interface.				//
//	Support to Compile as 32 Bit Application.					//
//																//
//	Designed for Engine Development.							//
//	UpComing Version Deployment to Linux & Android.				//
//	Mac Might Be apply in further. Iphone Won't be added		//
//	Because of it's License & Software Issue.					//
//																//
//																//
//--------------------------------------------------------------//

// #define ENGINE_EX_STATIC_BUILD			// Use as Static Lib
// #define ENGINE_EX_STATIC_TO_DLL_BUILD	// Use as Static Lib to DLL
// #define ENGINE_EX_DLL_IMPORT				// Import DLL 
// #define ENGINE_EX_DLL_INSIDE				// DLL inside of current DLL's Lib Connection File.
#ifndef ENGINE_EX_API
#define ENGINE_EX_API

#ifndef EX_EXTERNAL_DICTIONARY
	#define EX_INTERNAL_DICTIONARY
#endif
#ifdef EX_INTERNAL_DICTIONARY
#include"ExPreProcessor.h"
// Library Import
//define EX_AUTO_LINKER
#ifdef ENGINE_EX_STATIC
#ifdef EX_VC
	// NOT NEEDDED!
	//#pragma comment(lib, "Cmd.lib")
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
#include"System/elt_win.h"
#include"System/elt_gl.h"
#include"elt_thread.h"
#include"System/elt_cl.h"
#if defined(EX_WINDOWS)

#elif defined(EX_LINUX)

#elif defined(EX_MAC)

#elif defined(EX_ANDROID)
	//#include"System
#elif defined(EX_PS4)
	
#elif defined(EX_PS3)
	
#elif defined(EX_PSP)
	
#elif defined(EX_WEB)
	
#else
	#error "Error! no supporting Devices"
#endif

#include"ExCommon.h"
/*End*/
#else
// External Dictory
#include<EngineAssembly.h>
#include<EngineEx.h>


#endif
#endif
