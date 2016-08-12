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
#ifndef _ELT_JOYSTICK_H_
#define _ELT_JOYSTICK_H_ 1
#include"../system.h"

#ifdef __cplusplus	/*	C++ environment	*/
extern "C"{
#endif

typedef void* ExJoyStick;
EX_ALIGN_PREFIX(4)
typedef struct ex_GUID{
	Uint8 data[16];
}ExGUID;

/**
 *	Number of joystick
 *
 *	@Return
 */
extern ELTDECLSPEC Uint32 ELTAPIENTRY ExJoysticksNum(void);

/**
 *	Open joystick by device index
 *
 *	@Return
 */
extern ELTDECLSPEC ExJoyStick ELTAPIENTRY ExJoystickOpen(Int32 index);

/**
 *	Close Joystick by device index
 *
 *	@Return
 */
extern ELTDECLSPEC Int32 ELTAPIENTRY ExJoyStickClose(Int32 index);

/**
 *	Get Joystick Device GUID
 *
 *	@Return
 */
extern ELTDECLSPEC ExGUID ELTAPIENTRY ExJoystickGetDeviceGUID(Int32 index);

/**
 *	Get Joystick name
 *
 *	@Return
*/
extern ELTDECLSPEC const ExChar* ELTAPIENTRY ExJoyStickName(Uint32 ptr);

/**
 *	Get number of buttons on a joystick
 *
 *	@Return
 */
extern ELTDECLSPEC Int32 ELTAPIENTRY ExJoystickNumButtons(Uint32 ptr);

/**
 *	Axis Get number of axis on joystick
 *
 *	@Return
 */
extern ELTDECLSPEC Int32 ELTAPIENTRY ExJoystickNumAxis(Int ptr);

/**
 *
 *	@Return
 */
extern ELTDECLSPEC Int16 ELTAPIENTRY ExJoystickGetAxis(Int32 device_ptr, int axis);

/**
 *   \Button
 *
 *	@Return
 */
extern ELTDECLSPEC Uint8 ELTAPIENTRY ExJoyStickGetButton(Int32 device_index, int button);

/**
 *
 *	@Return
 */
extern ELTDECLSPEC void ELTAPIENTRY ExSetJoyStickState(Enum bitFlag, Uint32 userIndex);

/**
 *
 *	@Return
 */
extern ELTDECLSPEC void ELTAPIENTRY ExGetJoySticAxisMapping(ExJoyStick joystick, ExChar* mapping, unsigned int len);

/**
 *
 *	@Return
 */
extern ELTDECLSPEC void ELTAPIENTRY ExSetJoySticAxisMapping(ExJoyStick joystick, const ExChar* mapping, unsigned int len);


#ifdef __cplusplus /* C++ environment */
};
#endif
#include"elt_gamecontroller.h"
#endif
