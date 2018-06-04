#include"input/elt_keyboard.h"

#include<X11/Xlib.h>
#include<X11/keysym.h>
//#include<X11/extensions/XInput.h>
#include<X11/extensions/XKB.h>
#include<X11/XKBlib.h>
#include<X11/Xatom.h>
#include"system/unix/unix_win.h"
#include<linux/input.h>
#include<X11/Xlib-xcb.h>

extern xcb_connection_t* xcbConnection;

static inline int private_ExGetKeyCodeinternal(unsigned int keyCode) {
	int keysym;

	switch (keyCode) {
	case EXK_a:
		keysym = XK_A;
		break;
	case EXK_b:
		keysym = XK_B;
		break;
	case EXK_c:
		keysym = XK_C;
		break;
	case EXK_d:
		keysym = XK_D;
		break;
	case EXK_e:
		keysym = XK_E;
		break;
	case EXK_f:
		keysym = XK_F;
		break;
	case EXK_g:
		keysym = XK_G;
		break;
	case EXK_h:
		keysym = XK_H;
		break;
	case EXK_i:
		keysym = XK_I;
		break;
	case EXK_j:
		keysym = XK_J;
		break;
	case EXK_k:
		keysym = XK_K;
		break;
	case EXK_l:
		keysym = XK_L;
		break;
	case EXK_m:
		keysym = XK_M;
		break;
	case EXK_n:
		keysym = XK_N;
		break;
	case EXK_o:
		keysym = XK_O;
		break;
	case EXK_p:
		keysym = XK_P;
		break;
	case EXK_q:
		keysym = XK_Q;
		break;
	case EXK_r:
		keysym = XK_R;
		break;
	case EXK_s:
		keysym = XK_S;
		break;
	case EXK_t:
		keysym = XK_T;
		break;
	case EXK_u:
		keysym = XK_U;
		break;
	case EXK_v:
		keysym = XK_V;
		break;
	case EXK_w:
		keysym = XK_W;
		break;
	case EXK_x:
		keysym = XK_X;
		break;
	case EXK_y:
		keysym = XK_Y;
		break;
	case EXK_z:
		keysym = XK_Z;
		break;
	case EXK_0:
		keysym = XK_0;
		break;
	case EXK_1:
		keysym = XK_1;
		break;
	case EXK_2:
		keysym = XK_2;
		break;
	case EXK_3:
		keysym = XK_3;
		break;
	case EXK_4:
		keysym = XK_4;
		break;
	case EXK_5:
		keysym = XK_5;
		break;
	case EXK_6:
		keysym = XK_6;
		break;
	case EXK_7:
		keysym = XK_7;
		break;
	case EXK_8:
		keysym = XK_8;
		break;
	case EXK_9:
		keysym = XK_9;
		break;
	case EXK_Left:
		keysym = XK_Left;
		break;
	case EXK_Right:
		keysym = XK_Right;
		break;
	case EXK_Up:
		keysym = XK_Up;
		break;
	case EXK_Down:
		keysym = XK_Down;
		break;
	case EXK_ESCAPE:
		keysym = XK_Escape;
		break;

		/**/
	case EXK_LControl:
		keysym = XK_Control_L;
		break;
	case EXK_LShift:
		keysym = XK_Shift_L;
		break;
	case EXK_LAlt:
		keysym = XK_Alt_L;
		break;
	case EXK_LSystem:
		keysym = XK_Super_L;
		break;
	case EXK_RControl:
		keysym = XK_Control_R;
		break;
	case EXK_RShift:
		keysym = XK_Shift_R;
		break;
	case EXK_RAlt:
		keysym = XK_Alt_R;
		break;
	case EXK_RSystem:
		keysym = XK_Super_R;
		break;

		/*
		 case EXK_Menu:       keysym = XK_Menu;         break;

		 case EXK_LBracket:   keysym = XK_bracketleft;  break;
		 case EXK_RBracket:   keysym = XK_bracketright; break;
		 case EXK_SemiColon:  keysym = XK_semicolon;    break;
		 case EXK_Comma:      keysym = XK_comma;        break;
		 case EXK_Period:     keysym = XK_period;       break;
		 case EXK_Quote:      keysym = XK_dead_acute;   break;
		 case EXK_Slash:      keysym = XK_slash;        break;
		 case EXK_BackSlash:  keysym = XK_backslash;    break;
		 case EXK_Tilde:      keysym = XK_dead_grave;   break;
		 case EXK_Equal:      keysym = XK_equal;        break;
		 case EXK_Dash:       keysym = XK_minus;        break;
		 */
	case EXK_SPACE:
		keysym = XK_space;
		break;
	case EXK_RETURN:
		keysym = XK_Return;
		break;
	case EXK_BACKSPACE:
		keysym = XK_BackSpace;
		break;
	case EXK_TAB:
		keysym = XK_Tab;
		break;
		/*
		 case EXK_PageUp:     keysym = XK_Prior;        break;
		 case EXK_PageDown:   keysym = XK_Next;         break;
		 */

	case EXK_End:
		keysym = XK_End;
		break;
	case EXK_Home:
		keysym = XK_Home;
		break;
	case EXK_Insert:
		keysym = XK_Insert;
		break;
	case EXK_Delete:
		keysym = XK_Delete;
		break;
	case EXK_Add:
		keysym = XK_KP_Add;
		break;
	case EXK_Subtract:
		keysym = XK_KP_Subtract;
		break;
	case EXK_Multiply:
		keysym = XK_KP_Multiply;
		break;
	case EXK_Divide:
		keysym = XK_KP_Divide;
		break;
	case EXK_Numpad0:
		keysym = XK_KP_0;
		break;
	case EXK_Numpad1:
		keysym = XK_KP_1;
		break;
	case EXK_Numpad2:
		keysym = XK_KP_2;
		break;
	case EXK_Numpad3:
		keysym = XK_KP_3;
		break;
	case EXK_Numpad4:
		keysym = XK_KP_4;
		break;
	case EXK_Numpad5:
		keysym = XK_KP_5;
		break;
	case EXK_Numpad6:
		keysym = XK_KP_6;
		break;
	case EXK_Numpad7:
		keysym = XK_KP_7;
		break;
	case EXK_Numpad8:
		keysym = XK_KP_8;
		break;
	case EXK_Numpad9:
		keysym = XK_KP_9;
		break;

	case EXK_F1:
		keysym = XK_F1;
		break;
	case EXK_F2:
		keysym = XK_F2;
		break;
	case EXK_F3:
		keysym = XK_F3;
		break;
	case EXK_F4:
		keysym = XK_F4;
		break;
	case EXK_F5:
		keysym = XK_F5;
		break;
	case EXK_F6:
		keysym = XK_F6;
		break;
	case EXK_F7:
		keysym = XK_F7;
		break;
	case EXK_F8:
		keysym = XK_F8;
		break;
	case EXK_F9:
		keysym = XK_F9;
		break;
	case EXK_F10:
		keysym = XK_F10;
		break;
	case EXK_F11:
		keysym = XK_F11;
		break;
	case EXK_F12:
		keysym = XK_F12;
		break;
	case EXK_F13:
		keysym = XK_F13;
		break;
	case EXK_F14:
		keysym = XK_F14;
		break;
	case EXK_F15:
		keysym = XK_F15;
		break;
	case EXK_Pause:
		keysym = XK_Pause;
		break;
	default:
		keysym = 0;
		break;
	}
	return keysym;
}

ExKeycode ExGetKeyFromName(const char* name) {
	KeySym sym = XStringToKeysym(name);
	return sym;
}

const char* ExGetKeyName(ExKeycode keycode) {
	return XKeysymToString(private_ExGetKeyCodeinternal(keycode));
}

ExWin ExGetKeyboardFocus(void) {
	ExWin window;
	int revert_to_return;
	XGetInputFocus(display, &window, &revert_to_return);
	return window;
}

void ExSetKeyboardFocus(ExWin window) {
	XSetInputFocus(display, window, RevertToParent, CurrentTime);
}

const unsigned char* ExGetKeyboardState(int* numkeys) {

	xcb_query_keymap_reply_t* keymap = NULL;
	//keymap = xcb_query_keymap_reply(xcbConnection,xcb_query_keymap(xcbConnection), NULL);*/
	return keymap->keys;

	//if(numkeys)
	//   *numkeys = XQueryKeymap(display,KeyBoardState[0]);
	//else XQueryKeymap(display,KeyBoardState[0]);
	//return KeyBoardState[0];
}

ExKeycode ExGetModeState(void) {
	return XGrabKey(display, AnyKey, ControlMask | ShiftMask,
			ExGetKeyboardFocus(), True, GrabModeAsync, GrabModeSync);
}

ExBoolean ExAnyKey(void) {
	char keys[32];
	XQueryKeymap(display, keys);
	return EX_FALSE;
}

ExBoolean ExAnyKeyDown(void) {
	char keys[32];
	XQueryKeymap(display, keys);
	return EX_FALSE;
}

ExBoolean ExIsKey(unsigned int keyCode) {
	return ExIsKeyDown(keyCode);

}

ExBoolean ExIsKeyDown(unsigned int keyCode) {
	KeySym keysym = private_ExGetKeyCodeinternal(keyCode);

	unsigned int keycode = XKeysymToKeycode(display, keysym);

	if (keycode != 0) {

		xcb_query_keymap_reply_t* keymap = NULL;
		unsigned char isPressed;
		XLockDisplay(display);
		keymap = xcb_query_keymap_reply(xcbConnection,
				xcb_query_keymap(xcbConnection), NULL);
		XUnlockDisplay(display);
		isPressed = (keymap->keys[keycode / 8] & (1 << (keycode % 8))) ? 1 : 0;

		free(keymap);

		return isPressed;
	}
	return 0;

}

ExBoolean ExIsKeyUp(unsigned int keyCode) {
	return ExIsKeyDown(keyCode);
}
