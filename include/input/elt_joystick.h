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
	unsigned char data[16];
}ExGUID;

/**
 *	Number of joystick
 *
 *	@Return
 */
extern ELTDECLSPEC unsigned int ELTAPIENTRY ExJoysticksNum(void);

/**
 *	Open joystick by device index
 *
 *	@Return
 */
extern ELTDECLSPEC ExJoyStick ELTAPIENTRY ExJoystickOpen(int index);

/**
 *	Close Joystick by device index
 *
 *	@Return
 */
extern ELTDECLSPEC int ELTAPIENTRY ExJoyStickClose(int index);

/**
 *	Get Joystick Device GUID
 *
 *	@Return
 */
extern ELTDECLSPEC ExGUID ELTAPIENTRY ExJoystickGetDeviceGUID(int index);

/**
 *	Get Joystick name
 *
 *	@Return
*/
extern ELTDECLSPEC const ExChar* ELTAPIENTRY ExJoyStickName(unsigned int ptr);

/**
 *	Get number of buttons on a joystick
 *
 *	@Return
 */
extern ELTDECLSPEC int ELTAPIENTRY ExJoystickNumButtons(unsigned int ptr);

/**
 *	Axis Get number of axis on joystick
 *
 *	@Return
 */
extern ELTDECLSPEC int ELTAPIENTRY ExJoystickNumAxis(int ptr);

/**
 *
 *	@Return
 */
extern ELTDECLSPEC short ELTAPIENTRY ExJoystickGetAxis(int device_ptr, int axis);

/**
 *   \Button
 *
 *	@Return
 */
extern ELTDECLSPEC unsigned char ELTAPIENTRY ExJoyStickGetButton(int device_index, int button);

/**
 *
 *	@Return
 */
extern ELTDECLSPEC void ELTAPIENTRY ExSetJoyStickState(unsigned int bitFlag, unsigned int userIndex);

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
