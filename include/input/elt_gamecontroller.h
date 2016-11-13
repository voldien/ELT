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
#ifndef ELT_GAME_CONTROLLER_H
#define ELT_GAME_CONTROLLER_H
#include"elt_joystick.h"

#ifdef __cplusplus /* C++ environment */
extern "C"{
#endif

/**
 *
 */
extern ELTDECLSPEC int ELTAPIENTRY ExGameControllerAddMapping(const char* mappingString);

/**
 *
 */
extern ELTDECLSPEC int ELTAPIENTRY ExGameControllerAddMappinFromFile(const char* filename);

/**
 *
 */
extern ELTDECLSPEC int ELTAPIENTRY ExGameControllerEventState(int state);

/**
 *
 */
extern ELTDECLSPEC int ELTAPIENTRY ExGameControllerEventState(int state);

/**
 *
 */
extern ELTDECLSPEC ExBoolean ELTAPIENTRY ExGameControllerClose(int index);

/*
 *
 */
extern ELTDECLSPEC const char* ELTAPIENTRY ExGameControlerNameForIndex(int index);

/*
 *
 */
extern ELTDECLSPEC ExBoolean ELTAPIENTRY ExGameControllerOpen(int index);

/*
 *
 */
extern ELTDECLSPEC ExBoolean ELTAPIENTRY ExIsGameController(int joystick_index);

extern ELTDECLSPEC unsigned short ELTAPIENTRY ExGameControllerGetAxis(int index, int* axis);


extern ELTDECLSPEC void ELTAPIENTRY ExGameControllerVibration(int index, short LeftMotorSpeed, short RightMotorSpeed);

extern ELTDECLSPEC void ELTAPIENTRY ExGameControllerBattery(int index,int );

#ifdef __cplusplus /* C++ environment */
}
#endif
#endif
