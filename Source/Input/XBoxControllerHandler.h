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

#ifndef XBOX_CONTROLLER_H
#define XBOX_CONTROLLER_H
#include"./../EngineAssembly.h"

#include"elt_gamecontroller.h"

#define EX_CONTROLLER_MAX_COUNT 0x4
#define EX_CONTROLLER_ENABLED 0x1
#define EX_CONTROLLER_DISABLED 0x2
#define EX_CONTROLLER_DISCONNECTED 0x4
#ifdef EX_CPP	//	C++ Environment
extern "C"{
#endif


/*
	// XBox Controller
*/

//----------------------------------------------------------
DECLSPEC void* ELTAPIENTRY GetXBoxHandler(void);
//----------------------------------------------------------
DECLSPEC ERESULT ELTAPIENTRY ExInitXController(void);
//----------------------------------------------------------
DECLSPEC ERESULT ELTAPIENTRY ExInit_XController(const Uint32 userIndex);

//----------------------------------------------------------
/* DisConnect All XBox Controller.
 */
DECLSPEC void ELTAPIENTRY ExXDisConnected(void);		// check which index the disconneted XBox has, to applyed to it later, if it gets connected again.
//----------------------------------------------------------
/* Shut Down XBox Handler.
 */
DECLSPEC void ELTAPIENTRY ExXShutDown(void);
//----------------------------------------------------------
DECLSPEC void ELTAPIENTRY ExUpdateXControllers(void);
//----------------------------------------------------------
DECLSPEC void ELTAPIFASTENTRY ExUpdateXController(Uint8 userIndex);
//----------------------------------------------------------
DECLSPEC void ELTAPIENTRY ExSetXVibration(Ushort leftMotor, Ushort rightMotor, Uint userIndex);
//----------------------------------------------------------
DECLSPEC Float ELTAPIENTRY ExgetLMagnitude(Uint8 userIndex);
//----------------------------------------------------------
DECLSPEC Float ELTAPIENTRY ExgetRMagnitude(Uint8 userIndex);

DECLSPEC Float ELTAPIENTRY ExGetXLX(Uint8 userIndex);
DECLSPEC Float ELTAPIENTRY ExGetXLY(Uint8 userIndex);
DECLSPEC Float ELTAPIENTRY ExGetXRX(Uint8 userIndex);
DECLSPEC Float ELTAPIENTRY ExGetXRY(Uint8 userIndex);
DECLSPEC ExBoolean ELTAPIENTRY ExXIsPad(Uint32 keyCode, Uint32 userIndex);
DECLSPEC ExBoolean ELTAPIENTRY ExXIsPadDown(Uint32 keyCode, Uint32 userIndex);
DECLSPEC ExBoolean ELTAPIENTRY ExXIsPadUp(Uint32 keyCode, Uint32 userIndex);
DECLSPEC void ELTAPIENTRY ExGetXBatteryLevel(Uint32 userIndex);
DECLSPEC Uint8 ELTAPIENTRY ExGetXBatteryType(Uint32 userIndex);
//DECLSPEC ExGUID* ELTAPIENTRY ExGetXSoundCaptureGUID(Uint32 userIndex);
//DECLSPEC ExGUID* ELTAPIENTRY ExGetXSoundRenderGUID(Uint32 userIndex);
//----------------------------------------------------------
/* Disable All Input of All Xbox Device. */
DECLSPEC void ELTAPIENTRY ExSetXInputEnabled(const ExBoolean enabled);
//--------------------------------------------------------------
//Capabilities
DECLSPEC ExBoolean ELTAPIENTRY ExGetIsXWireLess(Uint32 userIndex);
DECLSPEC ExBoolean ELTAPIENTRY ExGetSupportVoice(Uint32 userIndex);

#ifdef EX_CPP	//	C++ Environment
}
#endif
#endif
