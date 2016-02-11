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
#ifndef _ELT_ACTIVITY_H_
#define _ELT_ACTIVITY_H_ 1
#include<stdio.h>
#include"../../EngineAssembly.h"
#ifdef EX_ANDROID
#include<android/log.h>
#endif

#ifdef __cplusplus	/*	C++ Environment	*/
extern "C"{
#endif


/*
 *	Get native Activity pointer
 *	@return
 */
extern ELTDECLSPEC void* ELTAPIENTRY ExGetNativeActivity(void);

/*
 *
 *	@return
 */
extern ELTDECLSPEC void* ELTAPIENTRY ExGetNativeLooper(void);


#ifdef EX_ANDROID
#define fprintf(x,...)   __android_log_print(ANDROID_LOG_INFO,"EngineEx", x ,##__VA_ARGS__ )
#define printf(x,...)    __android_log_print(ANDROID_LOG_INFO,"EngineEx", x ,##__VA_ARGS__ )
#define vfprintf(x,y,...) __android_log_print(ANDROID_LOG_INFO,"EngineEx", x ,##__VA_ARGS__ )
#endif

#ifdef __cplusplus	/*	C++ Environment	*/
}
#endif

#endif
