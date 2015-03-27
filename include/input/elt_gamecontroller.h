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
#ifndef ELT_GAME_CONTROLLER_H
#define ELT_GAME_CONTROLLER_H
#include"./../EngineAssembly.h"
#include"elt_joystick.h"

#ifdef __cplusplus	// C++ Environment
extern "C"{
#endif

extern DECLSPEC Int32 ELTAPIENTRY ExGameControllerAddMapping(const char* mappingString);
extern DECLSPEC Int32 ELTAPIENTRY ExGameControllerAddMappinFromFile(const char* filename);
extern DECLSPEC Int32 ELTAPIENTRY ExGameControllerEventState(Int32 state);
extern DECLSPEC Int32 ELTAPIENTRY ExGameControllerEventState(Int32 state);

extern DECLSPEC ExBoolean ELTAPIENTRY ExGameControllerClose(Int32 index);
extern DECLSPEC const char* ELTAPIENTRY ExGameControlerNameForIndex(Int32 index);
extern DECLSPEC ExBoolean ELTAPIENTRY ExGameControllerOpen(Int32 index);
extern DECLSPEC ExBoolean ELTAPIENTRY ExIsGameController(Int32 joystick_index);

extern DECLSPEC Uint16 ELTAPIENTRY ExGameControllerGetAxis(int index, int* axis);


extern DECLSPEC void ELTAPIENTRY ExGameControllerVibration(Int32 index, Int16 LeftMotorSpeed, Int16 RightMotorSpeed);

extern DECLSPEC void ELTAPIENTRY ExGameControllerBattery(Int32 index,Int32 );

#ifdef __cplusplus	// C++ Environment
}
#endif
#endif
