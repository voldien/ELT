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
#ifndef _ELT_KEYBOARD_H_
#define _ELT_KEYBOARD_H_ 1
#include"../system.h"
#include"eltkeycode.h"

#ifdef __cplusplus /* C++ environment */
extern "C"{
#endif

typedef ExKeycode ExScancode;
#define ExGetKeyCode(array,keycode) ( ( ( array ) [ ( keycode ) /8] )  & (1 << ( ( keycode )  % 8)))


/**
 *	Get KeyCode name identification index
 *
 *	\name
 *
 *	@Return
 */
extern ELTDECLSPEC ExKeycode ELTAPIENTRY ExGetKeyFromName(const char* name);

/**
 *	Get Key from Scancode.
 *
 *	\scancode
 *
 *	@Return
 */
extern ELTDECLSPEC ExKeycode ELTAPIENTRY ExGetKeyFromScancode(ExScancode scancode);

/**
 *	Get KeyCode name.
 *
 *	\keycode
 *
 *	@Return
 */
extern ELTDECLSPEC const char* ELTAPIENTRY ExGetKeyName(ExKeycode keycode);

/**
 *	Get window that keyboard is focus on.
 *
 *	@Return window handle.
 */
extern ELTDECLSPEC ExWin ELTAPIENTRY ExGetKeyboardFocus(void);

/**
 *	Set keyboard focus.
 *
 *	\window
 */
extern ELTDECLSPEC void ELTAPIENTRY ExSetKeyboardFocus(ExWin window);

/**
 *	Get keyboard state.
 *
 *	\numkeys
 *
 *	@Return
 */
extern ELTDECLSPEC const unsigned char* ELTAPIENTRY ExGetKeyboardState(int* numkeys);

/**
 *
 *
 *	@Return
 */
extern ELTDECLSPEC ExKeycode ELTAPIENTRY ExGetModeState(void);

/**
 *	Is any key pressed.
 *
 *	@Return	True if
 */
extern ELTDECLSPEC ExBoolean ELTAPIFASTENTRY ExAnyKey(void);

/**
 *
 *	@Return
 */
extern ELTDECLSPEC ExBoolean ELTAPIFASTENTRY ExAnyKeyDown(void);

/**
 *
 *	@Return
 */
extern ELTDECLSPEC ExBoolean ELTAPIFASTENTRY ExIsKey(unsigned int keyCode);

/**
 *	Check if key is pressed.
 *
 *	@Return 1 if key is pressed.
 */
extern ELTDECLSPEC ExBoolean ELTAPIFASTENTRY ExIsKeyDown(unsigned int keyCode);

/**
 *
 *	@Return
 */
extern ELTDECLSPEC ExBoolean ELTAPIFASTENTRY ExIsKeyReleased(unsigned int keyCode);


#ifdef __cplusplus /* C++ environment */
}
#endif
#endif
