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
#include"./../EngineAssembly.h"
#include"eltkeycode.h"

typedef Keycode ExScancode;

#ifdef __cplusplus /* C++ environment */
extern "C"{
#endif


#define ExGetKeyCode(array,keycode) ( ( ( array ) [ ( keycode ) /8] )  & (1 << ( ( keycode )  % 8)))

/*
 *	Get KeyCode name identification index
 *	@return
*/
extern DECLSPEC Keycode ELTAPIENTRY ExGetKeyFromName(const char* name);

/*
 *	Get Key from Scancode
 *	@return
 */
extern DECLSPEC Keycode ELTAPIENTRY ExGetKeyFromScancode(ExScancode scancode);

/*
 *	Get KeyCode name
 *	@return
 */
extern DECLSPEC const char* ELTAPIENTRY ExGetKeyName(Keycode keycode);

/*
 *	Get Window that is keyboard is focus to
 *	@return
 */
extern DECLSPEC ExWin ELTAPIENTRY ExGetKeyboardFocus(void);

/*
 *
 */
extern DECLSPEC void ELTAPIENTRY ExSetKeyboardFocus(ExWin window);

/*
 *	Get keyboard state.
 *	@return
 */
extern DECLSPEC const Uint8* ELTAPIENTRY ExGetKeyboardState(Int32* numkeys);

/*
 *	@return
 */
extern DECLSPEC Keycode ELTAPIENTRY ExGetModeState(void);

/*
 *	Is any key pressed
 *	@return
 */
extern DECLSPEC ExBoolean ELTAPIFASTENTRY ExAnyKey(void);

/*
 *	@return
 */
extern DECLSPEC ExBoolean ELTAPIFASTENTRY ExAnyKeyDown(void);

/*
 *	@return
 */
extern DECLSPEC ExBoolean ELTAPIFASTENTRY ExIsKey(Uint32 keyCode);

/*
 *
 */
extern DECLSPEC ExBoolean ELTAPIFASTENTRY ExIsKeyDown(Uint32 keyCode);

/*
 *
 */
extern DECLSPEC ExBoolean ELTAPIFASTENTRY ExIsKeyReleased(Uint32 keyCode);




#ifdef __cplusplus /* C++ environment */
}
#endif
#endif
