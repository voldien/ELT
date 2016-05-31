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
#ifndef _ENGINE_EX_H_
#define _ENGINE_EX_H_ 1
#include"elt_def.h"
#include"window.h"
#include"graphic.h"
#include"system.h"
#include"audio.h"

#ifdef __cplusplus	/*	C++ Environment	*/
extern "C"{
#endif

/**
 *	Initialize ELT Engine Library ToolKit
 *	\engineflag
 *	@Return
 */
extern ELTDECLSPEC ERESULT ELTAPIENTRY ExInit(Uint32 engineFlag);	/*TODO perhaps add argc,argv*/
extern ELTDECLSPEC ERESULT ELTAPIENTRY ExInit2(Uint32 engineFlag, Int argc, const ExChar* argv);

/*
 *	Initialize specific subsystems
 *	\engineflag
 *	@Return
 */
extern ELTDECLSPEC ERESULT ELTAPIENTRY ExInitSubSystem(Uint32 engineFlag);

/*
 *	Shut Down Function ELT.
 */
extern ELTDECLSPEC void ELTAPIENTRY ExShutDown(void);
#define ExQuit ExShutDown

/*
 *	Quit Sub System
 *	\engineflag
 */
extern ELTDECLSPEC void ELTAPIENTRY ExQuitSubSytem(Uint32 engineflag);


/*
 *
 *	@Return
 */
extern ELTDECLSPEC Uint32 ELTAPIENTRY ExGetFlag(void);


/*
 *	Enable.
 */
extern ELTDECLSPEC void ELTAPIENTRY ExEnable(Enum enable);

/*
 *	Disable.
 */
extern ELTDECLSPEC void ELTAPIENTRY ExDisable(Enum disable);


/**
 *	Create interrupt event.
 *	TODO put ExCreateInterrupt somewhere else!
 *	@Return
 */
extern ELTDECLSPEC int ELTAPIENTRY ExCreateInterrupt(interrupt_routine callback, Uint32 type);


/**
 *	Get ELT Version.
 *	@Return
 */
extern ELTDECLSPEC const ExChar* ELTAPIENTRY ExGetVersion(void);

/**
 *	Get compiler compiled with ELT.
 *	@Return
 */
extern ELTDECLSPEC const ExChar* ELTAPIENTRY ExGetCompilerName(void);

#ifdef __cplusplus	/*	C++ Environment	*/
}
#endif

#endif
