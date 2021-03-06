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
#ifndef _ELT_H_
#define _ELT_H_ 1
#include"elt_def.h"
#include"window.h"
#include"graphic.h"
#include"system.h"

#ifdef __cplusplus	/*	C++ Environment	*/
extern "C" {
#endif

/**
 *	High layer flag.
 *
 */
#define EX_INIT_NONE				0x00000000			/*	*/
#define EX_INIT_TIMER				0x00000001			/*	Initialize timer.	*/
#define EX_INIT_JOYSTICK			0x00000200			/*	*/
#define EX_INIT_EVENTS				0x00002000			/*	*/
#define EX_INIT_GAMECONTROLLER 		0x00004000			/*	*/
#define EX_INIT_NET					0x00008000			/*	*/
#define EX_INIT_DEBUG				0x00010000			/*	*/
#define EX_INIT_EVERYTHING (						\
	EX_INIT_JOYSTICK | 								\
 EX_INIT_TIMER | EX_INIT_GAMECONTROLLER | EX_INIT_EVENTS | EX_INIT_DEBUG)


/**
 *	Initialize ELT Engine Library ToolKit
 *
 *	\flag
 *
 *	@Return
 */
extern ELTDECLSPEC ERESULT ELTAPIENTRY ExInit(unsigned int flag);


/**
 *	Initialize specific subsystems.
 *
 *	\flag
 *
 *	@Return
 */
extern ELTDECLSPEC ERESULT ELTAPIENTRY ExInitSubSystem(unsigned int flag);

/**
 *	Shut Down Function ELT.
 *
 */
extern ELTDECLSPEC void ELTAPIENTRY ExShutDown(void);

/**
 *	Quit Sub System.
 *
 *	\flag
 */
extern ELTDECLSPEC void ELTAPIENTRY ExQuitSubSytem(unsigned int flag);

/**
 *
 *
 *	@Return
 */
extern ELTDECLSPEC unsigned int ELTAPIENTRY ExGetFlag(void);

/**
 *	Get ELT Version.
 *
 *	@Return non NULL string.
 */
extern ELTDECLSPEC const ExChar* ELTAPIENTRY ExGetVersion(void);

/**
 *	Get compiler compiled the library.
 *
 *	@Return Non NULL pointer.
 */
extern ELTDECLSPEC const ExChar* ELTAPIENTRY ExGetCompilerName(void);


/**
 *	Get display pointer.
 *
 *	@Return display pointer.
 */
extern ELTDECLSPEC ExDisplay ELTAPIENTRY ExGetDisplay(void);

#ifdef __cplusplus	/*	C++ Environment	*/
}
#endif

#endif	/*	_ENGINE_EX_H_	*/
