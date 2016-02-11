#include"input/elt_keyboard.h"

#ifdef EX_WINDOWS
    #include<dinput.h>
    #include<dbt.h>
    #include<oleauto.h>
    #include<shellapi.h>
	#ifndef DIRECTINPUT_VERSION
		#define DIRECTINPUT_VERSION 0x800
	#endif

#elif defined(EX_LINUX)
    #include<X11/Xlib.h>
    #include<X11/keysym.h>
    #include<X11/extensions/XInput.h>
    #include<X11/extensions/XKB.h>
    #include <X11/XKBlib.h>
    #include <X11/Xatom.h>
    #include<X11/extensions/XInput.h>
    #include"system/unix/unix_win.h"
    #include <linux/input.h>
    #include<X11/Xlib-xcb.h>

#elif defined(EX_ANDROID)
#   include<android/input.h>
#endif

/*	TODO seperate the input implemention to corresponding platform directory!	*/


unsigned char KeyBoardState[2][0xFF];

static inline int ExGetKeyCodeInternal(Uint32 keyCode){
    int keysym;

    switch (keyCode){
    #ifdef EX_LINUX
        case EXK_a:   keysym = XK_A;     break;
        case EXK_b:   keysym = XK_B;     break;
        case EXK_c:   keysym = XK_C;     break;
        case EXK_d:   keysym = XK_D;     break;
        case EXK_e:   keysym = XK_E;     break;
        case EXK_f:   keysym = XK_F;     break;
        case EXK_g:   keysym = XK_G;     break;
        case EXK_h:   keysym = XK_H;     break;
        case EXK_i:   keysym = XK_I;     break;
        case EXK_j:   keysym = XK_J;     break;
        case EXK_k:   keysym = XK_K;     break;
        case EXK_l:   keysym = XK_L;     break;
        case EXK_m:   keysym = XK_M;     break;
        case EXK_n:   keysym = XK_N;     break;
        case EXK_o:   keysym = XK_O;     break;
        case EXK_p:   keysym = XK_P;     break;
        case EXK_q:   keysym = XK_Q;     break;
        case EXK_r:   keysym = XK_R;     break;
        case EXK_s:   keysym = XK_S;     break;
        case EXK_t:   keysym = XK_T;     break;
        case EXK_u:   keysym = XK_U;     break;
        case EXK_v:   keysym = XK_V;     break;
        case EXK_w:   keysym = XK_W;     break;
        case EXK_x:   keysym = XK_X;     break;
        case EXK_y:   keysym = XK_Y;     break;
        case EXK_z:   keysym = XK_Z;     break;
        case EXK_0:   keysym = XK_0;     break;
        case EXK_1:   keysym = XK_1;     break;
        case EXK_2:   keysym = XK_2;     break;
        case EXK_3:   keysym = XK_3;     break;
        case EXK_4:   keysym = XK_4;     break;
        case EXK_5:   keysym = XK_5;     break;
        case EXK_6:   keysym = XK_6;     break;
        case EXK_7:   keysym = XK_7;     break;
        case EXK_8:   keysym = XK_8;     break;
        case EXK_9:   keysym = XK_9;     break;
        case EXK_Left:  keysym = XK_Left;         break;
        case EXK_Right: keysym = XK_Right;        break;
        case EXK_Up:    keysym = XK_Up;           break;
        case EXK_Down:  keysym = XK_Down;         break;
        case EXK_ESCAPE:keysym = XK_Escape;       break;

		case EXK_LControl:   keysym = XK_Control_L;    break;
        case EXK_LShift:     keysym = XK_Shift_L;      break;
        case EXK_LAlt:       keysym = XK_Alt_L;        break;
        case EXK_LSystem:    keysym = XK_Super_L;      break;
        case EXK_RControl:   keysym = XK_Control_R;    break;
        case EXK_RShift:     keysym = XK_Shift_R;      break;
        case EXK_RAlt:       keysym = XK_Alt_R;        break;
        case EXK_RSystem:    keysym = XK_Super_R;      break;
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
        case EXK_SPACE:      keysym = XK_space;        break;
        /*
        case EXK_Return:     keysym = XK_Return;       break;
        case EXK_BackSpace:  keysym = XK_BackSpace;    break;
        case EXK_Tab:        keysym = XK_Tab;          break;
        case EXK_PageUp:     keysym = XK_Prior;        break;
		case EXK_PageDown:   keysym = XK_Next;         break;
		*/
        case EXK_End:        keysym = XK_End;          break;
        case EXK_Home:       keysym = XK_Home;         break;
        case EXK_Insert:     keysym = XK_Insert;       break;
        case EXK_Delete:     keysym = XK_Delete;       break;
        case EXK_Add:        keysym = XK_KP_Add;       break;
        case EXK_Subtract:   keysym = XK_KP_Subtract;  break;
        case EXK_Multiply:   keysym = XK_KP_Multiply;  break;
        case EXK_Divide:     keysym = XK_KP_Divide;    break;
        case EXK_Numpad0:    keysym = XK_KP_0;         break;
        case EXK_Numpad1:    keysym = XK_KP_1;         break;
        case EXK_Numpad2:    keysym = XK_KP_2;         break;
        case EXK_Numpad3:    keysym = XK_KP_3;         break;
        case EXK_Numpad4:    keysym = XK_KP_4;         break;
        case EXK_Numpad5:    keysym = XK_KP_5;         break;
        case EXK_Numpad6:    keysym = XK_KP_6;         break;
        case EXK_Numpad7:    keysym = XK_KP_7;         break;
        case EXK_Numpad8:    keysym = XK_KP_8;         break;
        case EXK_Numpad9:    keysym = XK_KP_9;         break;

        case EXK_F1:         keysym = XK_F1;           break;
        case EXK_F2:         keysym = XK_F2;           break;
        case EXK_F3:         keysym = XK_F3;           break;
        case EXK_F4:         keysym = XK_F4;           break;
        case EXK_F5:         keysym = XK_F5;           break;
        case EXK_F6:         keysym = XK_F6;           break;
        case EXK_F7:         keysym = XK_F7;           break;
        case EXK_F8:         keysym = XK_F8;           break;
        case EXK_F9:         keysym = XK_F9;           break;
        case EXK_F10:        keysym = XK_F10;          break;
        case EXK_F11:        keysym = XK_F11;          break;
        case EXK_F12:        keysym = XK_F12;          break;
        case EXK_F13:        keysym = XK_F13;          break;
        case EXK_F14:        keysym = XK_F14;          break;
        case EXK_F15:        keysym = XK_F15;          break;
        case EXK_Pause:      keysym = XK_Pause;        break;

        #elif defined(EX_WINDOW)
        case EXK_A:          keysym = 'A';           break;
        case EXK_B:          keysym = 'B';           break;
        case EXK_C:          keysym = 'C';           break;
        case EXK_D:          keysym = 'D';           break;
        case EXK_E:          keysym = 'E';           break;
        case EXK_F:          keysym = 'F';           break;
        case EXK_G:          keysym = 'G';           break;
        case EXK_H:          keysym = 'H';           break;
        case EXK_I:          keysym = 'I';           break;
        case EXK_J:          keysym = 'J';           break;
        case EXK_K:          keysym = 'K';           break;
        case EXK_L:          keysym = 'L';           break;
        case EXK_M:          keysym = 'M';           break;
        case EXK_N:          keysym = 'N';           break;
        case EXK_O:          keysym = 'O';           break;
        case EXK_P:          keysym = 'P';           break;
        case EXK_Q:          keysym = 'Q';           break;
        case EXK_R:          keysym = 'R';           break;
        case EXK_S:          keysym = 'S';           break;
        case EXK_T:          keysym = 'T';           break;
        case EXK_U:          keysym = 'U';           break;
        case EXK_V:          keysym = 'V';           break;
        case EXK_W:          keysym = 'W';           break;
        case EXK_X:          keysym = 'X';           break;
        case EXK_Y:          keysym = 'Y';           break;
        case EXK_Z:          keysym = 'Z';           break;
        case EXK_Num0:       keysym = '0';           break;
        case EXK_Num1:       keysym = '1';           break;
        case EXK_Num2:       keysym = '2';           break;
        case EXK_Num3:       keysym = '3';           break;
        case EXK_Num4:       keysym = '4';           break;
        case EXK_Num5:       keysym = '5';           break;
        case EXK_Num6:       keysym = '6';           break;
        case EXK_Num7:       keysym = '7';           break;
        case EXK_Num8:       keysym = '8';           break;
        case EXK_Num9:       keysym = '9';           break;
        case EXK_Escape:     keysym = VK_ESCAPE;     break;
        case EXK_LControl:   keysym = VK_LCONTROL;   break;
        case EXK_LShift:     keysym = VK_LSHIFT;     break;
        case EXK_LAlt:       keysym = VK_LMENU;      break;
        case EXK_LSystem:    keysym = VK_LWIN;       break;
        case EXK_RControl:   keysym = VK_RCONTROL;   break;
        case EXK_RShift:     keysym = VK_RSHIFT;     break;
        case EXK_RAlt:       keysym = VK_RMENU;      break;
        case EXK_RSystem:    keysym = VK_RWIN;       break;
        case EXK_Menu:       keysym = VK_APPS;       break;
        case EXK_LBracket:   keysym = VK_OEM_4;      break;
        case EXK_RBracket:   keysym = VK_OEM_6;      break;
        case EXK_SemiColon:  keysym = VK_OEM_1;      break;
        case EXK_Comma:      keysym = VK_OEM_COMMA;  break;
        case EXK_Period:     keysym = VK_OEM_PERIOD; break;
        case EXK_Quote:      keysym = VK_OEM_7;      break;
        case EXK_Slash:      keysym = VK_OEM_2;      break;
        case EXK_BackSlash:  keysym = VK_OEM_5;      break;
        case EXK_Tilde:      keysym = VK_OEM_3;      break;
        case EXK_Equal:      keysym = VK_OEM_PLUS;   break;
        case EXK_Dash:       keysym = VK_OEM_MINUS;  break;
        case EXK_Space:      keysym = VK_SPACE;      break;
        case EXK_Return:     keysym = VK_RETURN;     break;
        case EXK_BackSpace:  keysym = VK_BACK;       break;
        case EXK_Tab:        keysym = VK_TAB;        break;
        case EXK_PageUp:     keysym = VK_PRIOR;      break;
        case EXK_PageDown:   keysym = VK_NEXT;       break;
        case EXK_End:        keysym = VK_END;        break;
        case EXK_Home:       keysym = VK_HOME;       break;
        case EXK_Insert:     keysym = VK_INSERT;     break;
        case EXK_Delete:     keysym = VK_DELETE;     break;
        case EXK_Add:        keysym = VK_ADD;        break;
        case EXK_Subtract:   keysym = VK_SUBTRACT;   break;
        case EXK_Multiply:   keysym = VK_MULTIPLY;   break;
        case EXK_Divide:     keysym = VK_DIVIDE;     break;
        case EXK_Left:       keysym = VK_LEFT;       break;
        case EXK_Right:      keysym = VK_RIGHT;      break;
        case EXK_Up:         keysym = VK_UP;         break;
        case EXK_Down:       keysym = VK_DOWN;       break;
        case EXK_Numpad0:    keysym = VK_NUMPAD0;    break;
        case EXK_Numpad1:    keysym = VK_NUMPAD1;    break;
        case EXK_Numpad2:    keysym = VK_NUMPAD2;    break;
        case EXK_Numpad3:    keysym = VK_NUMPAD3;    break;
        case EXK_Numpad4:    keysym = VK_NUMPAD4;    break;
        case EXK_Numpad5:    keysym = VK_NUMPAD5;    break;
        case EXK_Numpad6:    keysym = VK_NUMPAD6;    break;
        case EXK_Numpad7:    keysym = VK_NUMPAD7;    break;
        case EXK_Numpad8:    keysym = VK_NUMPAD8;    break;
        case EXK_Numpad9:    keysym = VK_NUMPAD9;    break;
        case EXK_F1:         keysym = VK_F1;         break;
        case EXK_F2:         keysym = VK_F2;         break;
        case EXK_F3:         keysym = VK_F3;         break;
        case EXK_F4:         keysym = VK_F4;         break;
        case EXK_F5:         keysym = VK_F5;         break;
        case EXK_F6:         keysym = VK_F6;         break;
        case EXK_F7:         keysym = VK_F7;         break;
        case EXK_F8:         keysym = VK_F8;         break;
        case EXK_F9:         keysym = VK_F9;         break;
        case EXK_F10:        keysym = VK_F10;        break;
        case EXK_F11:        keysym = VK_F11;        break;
        case EXK_F12:        keysym = VK_F12;        break;
        case EXK_F13:        keysym = VK_F13;        break;
        case EXK_F14:        keysym = VK_F14;        break;
        case EXK_F15:        keysym = VK_F15;        break;
        case EXK_Pause:      keysym = VK_PAUSE;      break;
		#elif defined(EX_ANDROID)
		#elif defined(EX_MAC)
        #endif
        default:             keysym = 0;               break;
    }
    return keysym;
}




ELTDECLSPEC ExKeycode ELTAPIENTRY ExGetKeyFromName(const char* name){
#if defined(EX_WINDOWS)
	switch(name[0]){
	case ' ':return 0;
	}
#elif defined(EX_LINUX)
    KeySym sym = XStringToKeysym(name);
    return sym;
#endif
}

ELTDECLSPEC const char* ELTAPIENTRY ExGetKeyName(ExKeycode keycode){
#ifdef EX_WINDOWS
	char text[20];
	GetKeyNameTextA((keycode << 16),text,sizeof(text));
	return text;
#elif defined(EX_LINUX)
    return XKeysymToString(ExGetKeyCodeInternal(keycode));
#endif

}

ELTDECLSPEC ExWin ELTAPIENTRY ExGetKeyboardFocus(void){
#ifdef EX_WINDOWS
	return GetFocus();
#elif defined(EX_LINUX)
	ExWin window;
	int revert_to_return;
	XGetInputFocus(display,&window,&revert_to_return);
	return window;
#elif defined(EX_ANDROID)
    return NULL;
#elif defined(EX_MAC)
    return NULL;
#endif
}

ELTDECLSPEC void ELTAPIENTRY ExSetKeyboardFocus(ExWin window){
#ifdef EX_LINUX
	XSetInputFocus(display,window,RevertToParent,CurrentTime);
#endif
}


ELTDECLSPEC const Uint8* ELTAPIENTRY ExGetKeyboardState(Int32* numkeys){
#ifdef EX_WINDOWS
	if(numkeys)*numkeys=0xff;
	unsigned char ispressed = GetKeyboardState(&KeyBoardState[0][0]);
	return KeyBoardState[0];
#elif defined(EX_LINUX)
	xcb_query_keymap_reply_t* keymap = NULL;
	//keymap = xcb_query_keymap_reply(xcbConnection,xcb_query_keymap(xcbConnection), NULL);*/
	return keymap->keys;

	//if(numkeys)
     //   *numkeys = XQueryKeymap(display,KeyBoardState[0]);
    //else XQueryKeymap(display,KeyBoardState[0]);
	//return KeyBoardState[0];
#endif
}
/**

*/
ELTDECLSPEC ExKeycode ELTAPIENTRY ExGetModeState(void){
#ifdef EX_WINDOWS
	return 0;
#elif defined(EX_LINUX)
    return XGrabKey(display,AnyKey, ControlMask | ShiftMask, ExGetKeyboardFocus(), True, GrabModeAsync, GrabModeSync);
#endif
}

ELTDECLSPEC ExBoolean ELTAPIFASTENTRY ExAnyKey(void){

	return FALSE;
}
ELTDECLSPEC ExBoolean ELTAPIFASTENTRY ExAnyKeyDown(void){

	return FALSE;
}


ELTDECLSPEC ExBoolean ELTAPIFASTENTRY ExIsKey(Uint32 keyCode){
#if defined(EX_WINDOWS)
	return (ExBoolean)GetAsyncKeyState(keyCode);
#elif defined(EX_LINUX)
	return ExIsKeyDown(keyCode);
#endif
}


#ifdef EX_LINUX
	extern xcb_connection_t* xcbConnection;
#endif

ELTDECLSPEC ExBoolean ELTAPIFASTENTRY ExIsKeyDown(Uint32 keyCode){
#if defined(EX_WINDOWS)
	return (ExBoolean)GetAsyncKeyState(keyCode);
#elif defined(EX_LINUX)
	KeySym keysym = ExGetKeyCodeInternal(keyCode);

	if(!xcbConnection)
		xcbConnection = XGetXCBConnection(display);


	unsigned int keycode = XKeysymToKeycode(display, keysym);

	if(keycode != 0){

		xcb_query_keymap_reply_t* keymap = NULL;
		unsigned char isPressed;
		keymap = xcb_query_keymap_reply(xcbConnection,xcb_query_keymap(xcbConnection), NULL);

		isPressed = (keymap->keys[keycode/8] & (1 << (keycode % 8))) ?  1 : 0;

        return isPressed;
	}
	return 0;
#endif
}

ELTDECLSPEC ExBoolean ELTAPIFASTENTRY ExIsKeyUp(Uint32 keyCode){
#if defined(EX_WINDOWS)
	return GetAsyncKeyState(keyCode);
#elif defined(EX_LINUX)
	return ExIsKeyDown(keyCode);
#endif

}
