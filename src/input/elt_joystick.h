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
#ifndef _ELT_JOYSTICK_H_
#define _ELT_JOYSTICK_H_ 1
#include"./../EngineAssembly.h"


typedef struct ex_GUID{
	Uint8 data[16];
}ExGUID;

#ifdef __cplusplus	// C++ Environment
extern "C"{
#endif
/**
	Number of joystick
*/
extern DECLSPEC Uint32 ELTAPIENTRY ExNumJoysticks(void);
/**
    Open joystick by device index
*/
extern DECLSPEC void* ELTAPIENTRY ExJoystickOpen(Int32  device_index);
/**
    Close Joystick by device index
*/
extern DECLSPEC Int32 ELTAPIENTRY ExJoyStickClose(Int32 device_index);

/**
	Get Joystick Device GUID
*/
extern DECLSPEC ExGUID ELTAPIENTRY ExJoystickGetDeviceGUID(Int32 device_index);
/**
	Get Joystick name
*/
extern DECLSPEC const ExChar* ELTAPIENTRY ExJoyStickName(Uint32 ptr);
/**
	Get number of buttons on a joystick
*/
extern DECLSPEC Int32 ELTAPIENTRY ExJoystickNumButtons(Uint32 ptr);
/**
    \Axis Get number of axis on joystick
*/
extern DECLSPEC Int32 ELTAPIENTRY ExJoystickNumAxis(Int ptr);
/**

*/
extern DECLSPEC Int16 ELTAPIENTRY ExJoystickGetAxis(Int32 device_ptr,int axis);
/**
    \Button
*/
extern DECLSPEC Uint8 ELTAPIENTRY ExJoyStickGetButton(Int32 device_index, int button);


extern DECLSPEC ERESULT ELTAPIENTRY ExInitJoyStick(ExWin hwnd);


DECLSPEC void* ELTAPIENTRY GetJoyStickDeviceContext(Uint32 userIndex);


DECLSPEC void ELTAPIENTRY ExSetJoyStickState(Enum bitFlag, const Uint32 userIndex);

DECLSPEC void ELTAPIENTRY ExJoyStickShutDown(void);
DECLSPEC void ELTAPIENTRY ExJoyStickDisConnected(void);		// check which index the disconneted XBox has, to applyed to it later, if it gets connected again.
DECLSPEC void ELTAPIENTRY ExUpdateJoyStickController(void);

#ifdef __cplusplus	// C++ Environment
};
#endif
#include"elt_gamecontroller.h"
#endif
