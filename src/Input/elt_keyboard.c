#include"elt_keyboard.h"

#ifdef EX_WINDOWS
    #include<dinput.h>
    #include<dinputd.h>
    #include<Dbt.h>
    #include<oleauto.h>
    #include<shellapi.h>
#elif defined(EX_LINUX)
    #include<X11/Xlib.h>
    #include<X11/keysym.h>
    #include<X11/extensions/XInput.h>
    #include<X11/extensions/XKB.h>
    #include <X11/XKBlib.h>
    #include <X11/Xatom.h>
    #include<X11/extensions/XInput.h>
    #include"./../System/Unix/unix_win.h"
    #include <linux/input.h>
    #include<X11/Xlib-xcb.h>

#elif defined(EX_ANDROID)
#   include<android/input.h>
#endif

#ifdef EX_WINDOWS

IDirectInputDevice8* m_keyboard_device;
#endif
unsigned char KeyBoardState[2][0xff];




static inline int ex_get_key_code_internal(Uint32 keyCode){
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

        /*case EXK_Escape:     keysym = XK_Escape;       break;
        case EXK_LControl:   keysym = XK_Control_L;    break;
        case EXK_LShift:     keysym = XK_Shift_L;      break;
        case EXK_LAlt:       keysym = XK_Alt_L;        break;
        case EXK_LSystem:    keysym = XK_Super_L;      break;
        case EXK_RControl:   keysym = XK_Control_R;    break;
        case EXK_RShift:     keysym = XK_Shift_R;      break;
        case EXK_RAlt:       keysym = XK_Alt_R;        break;
        case EXK_RSystem:    keysym = XK_Super_R;      break;
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
        case EXK_Space:      keysym = XK_space;        break;
        case EXK_Return:     keysym = XK_Return;       break;
        case EXK_BackSpace:  keysym = XK_BackSpace;    break;
        case EXK_Tab:        keysym = XK_Tab;          break;
        case EXK_PageUp:     keysym = XK_Prior;        break;
        case EXK_PageDown:   keysym = XK_Next;         break;
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
        */
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
        case EXK_A:          vkey = 'A';           break;
        case EXK_B:          vkey = 'B';           break;
        case EXK_C:          vkey = 'C';           break;
        case EXK_D:          vkey = 'D';           break;
        case EXK_E:          vkey = 'E';           break;
        case EXK_F:          vkey = 'F';           break;
        case EXK_G:          vkey = 'G';           break;
        case EXK_H:          vkey = 'H';           break;
        case EXK_I:          vkey = 'I';           break;
        case EXK_J:          vkey = 'J';           break;
        case EXK_K:          vkey = 'K';           break;
        case EXK_L:          vkey = 'L';           break;
        case EXK_M:          vkey = 'M';           break;
        case EXK_N:          vkey = 'N';           break;
        case Keyboard::O:          vkey = 'O';           break;
        case Keyboard::P:          vkey = 'P';           break;
        case Keyboard::Q:          vkey = 'Q';           break;
        case Keyboard::R:          vkey = 'R';           break;
        case Keyboard::S:          vkey = 'S';           break;
        case Keyboard::T:          vkey = 'T';           break;
        case Keyboard::U:          vkey = 'U';           break;
        case Keyboard::V:          vkey = 'V';           break;
        case Keyboard::W:          vkey = 'W';           break;
        case Keyboard::X:          vkey = 'X';           break;
        case Keyboard::Y:          vkey = 'Y';           break;
        case Keyboard::Z:          vkey = 'Z';           break;
        case Keyboard::Num0:       vkey = '0';           break;
        case Keyboard::Num1:       vkey = '1';           break;
        case Keyboard::Num2:       vkey = '2';           break;
        case Keyboard::Num3:       vkey = '3';           break;
        case Keyboard::Num4:       vkey = '4';           break;
        case Keyboard::Num5:       vkey = '5';           break;
        case Keyboard::Num6:       vkey = '6';           break;
        case Keyboard::Num7:       vkey = '7';           break;
        case Keyboard::Num8:       vkey = '8';           break;
        case Keyboard::Num9:       vkey = '9';           break;
        case Keyboard::Escape:     vkey = VK_ESCAPE;     break;
        case Keyboard::LControl:   vkey = VK_LCONTROL;   break;
        case Keyboard::LShift:     vkey = VK_LSHIFT;     break;
        case Keyboard::LAlt:       vkey = VK_LMENU;      break;
        case Keyboard::LSystem:    vkey = VK_LWIN;       break;
        case Keyboard::RControl:   vkey = VK_RCONTROL;   break;
        case Keyboard::RShift:     vkey = VK_RSHIFT;     break;
        case Keyboard::RAlt:       vkey = VK_RMENU;      break;
        case Keyboard::RSystem:    vkey = VK_RWIN;       break;
        case Keyboard::Menu:       vkey = VK_APPS;       break;
        case Keyboard::LBracket:   vkey = VK_OEM_4;      break;
        case Keyboard::RBracket:   vkey = VK_OEM_6;      break;
        case Keyboard::SemiColon:  vkey = VK_OEM_1;      break;
        case Keyboard::Comma:      vkey = VK_OEM_COMMA;  break;
        case Keyboard::Period:     vkey = VK_OEM_PERIOD; break;
        case Keyboard::Quote:      vkey = VK_OEM_7;      break;
        case Keyboard::Slash:      vkey = VK_OEM_2;      break;
        case Keyboard::BackSlash:  vkey = VK_OEM_5;      break;
        case Keyboard::Tilde:      vkey = VK_OEM_3;      break;
        case Keyboard::Equal:      vkey = VK_OEM_PLUS;   break;
        case Keyboard::Dash:       vkey = VK_OEM_MINUS;  break;
        case Keyboard::Space:      vkey = VK_SPACE;      break;
        case Keyboard::Return:     vkey = VK_RETURN;     break;
        case Keyboard::BackSpace:  vkey = VK_BACK;       break;
        case Keyboard::Tab:        vkey = VK_TAB;        break;
        case Keyboard::PageUp:     vkey = VK_PRIOR;      break;
        case Keyboard::PageDown:   vkey = VK_NEXT;       break;
        case Keyboard::End:        vkey = VK_END;        break;
        case Keyboard::Home:       vkey = VK_HOME;       break;
        case Keyboard::Insert:     vkey = VK_INSERT;     break;
        case Keyboard::Delete:     vkey = VK_DELETE;     break;
        case Keyboard::Add:        vkey = VK_ADD;        break;
        case Keyboard::Subtract:   vkey = VK_SUBTRACT;   break;
        case Keyboard::Multiply:   vkey = VK_MULTIPLY;   break;
        case Keyboard::Divide:     vkey = VK_DIVIDE;     break;
        case Keyboard::Left:       vkey = VK_LEFT;       break;
        case Keyboard::Right:      vkey = VK_RIGHT;      break;
        case Keyboard::Up:         vkey = VK_UP;         break;
        case Keyboard::Down:       vkey = VK_DOWN;       break;
        case Keyboard::Numpad0:    vkey = VK_NUMPAD0;    break;
        case Keyboard::Numpad1:    vkey = VK_NUMPAD1;    break;
        case Keyboard::Numpad2:    vkey = VK_NUMPAD2;    break;
        case Keyboard::Numpad3:    vkey = VK_NUMPAD3;    break;
        case Keyboard::Numpad4:    vkey = VK_NUMPAD4;    break;
        case Keyboard::Numpad5:    vkey = VK_NUMPAD5;    break;
        case Keyboard::Numpad6:    vkey = VK_NUMPAD6;    break;
        case Keyboard::Numpad7:    vkey = VK_NUMPAD7;    break;
        case Keyboard::Numpad8:    vkey = VK_NUMPAD8;    break;
        case Keyboard::Numpad9:    vkey = VK_NUMPAD9;    break;
        case Keyboard::F1:         vkey = VK_F1;         break;
        case Keyboard::F2:         vkey = VK_F2;         break;
        case Keyboard::F3:         vkey = VK_F3;         break;
        case Keyboard::F4:         vkey = VK_F4;         break;
        case Keyboard::F5:         vkey = VK_F5;         break;
        case Keyboard::F6:         vkey = VK_F6;         break;
        case Keyboard::F7:         vkey = VK_F7;         break;
        case Keyboard::F8:         vkey = VK_F8;         break;
        case Keyboard::F9:         vkey = VK_F9;         break;
        case Keyboard::F10:        vkey = VK_F10;        break;
        case Keyboard::F11:        vkey = VK_F11;        break;
        case Keyboard::F12:        vkey = VK_F12;        break;
        case Keyboard::F13:        vkey = VK_F13;        break;
        case Keyboard::F14:        vkey = VK_F14;        break;
        case Keyboard::F15:        vkey = VK_F15;        break;
        case Keyboard::Pause:      vkey = VK_PAUSE;      break;
        #endif
        default:             keysym = 0;               break;
    }
    return keysym;
}





DECLSPEC Keycode ELTAPIENTRY ExGetKeyFromName(const char* name){
#if defined(EX_WINDOWS)
	switch(name[0]){
	case ' ':return 0;
	}
#elif defined(EX_LINUX)
    KeySym sym = XStringToKeysym(name);
    return sym;
#endif
}
DECLSPEC const char* ELTAPIENTRY ExGetKeyName(Keycode keycode){
#ifdef EX_WINDOWS
	char text[20];
	GetKeyNameTextA((keycode << 16),text,sizeof(text));
	return text;
#elif defined(EX_LINUX)
    return XKeysymToString(keycode);
#endif

}

DECLSPEC ExWin ELTAPIENTRY ExGetKeyboardFocus(void){
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
DECLSPEC const Uint8* ELTAPIENTRY ExGetKeyboardState(Int32* numkeys){
#ifdef EX_WINDOWS
	if(numkeys)*numkeys=0xff;
	unsigned char ispressed = GetKeyboardState(&KeyBoardState[0][0]);
	return KeyBoardState[0];
#elif defined(EX_LINUX)
	if(numkeys)
        *numkeys = XQueryKeymap(display,KeyBoardState[0]);
    else XQueryKeymap(display,KeyBoardState[0]);
	return KeyBoardState[0];
#endif
}
/**

*/
DECLSPEC Keycode ELTAPIENTRY ExGetModeState(void){
#ifdef EX_WINDOWS
	return 0;
#elif defined(EX_LINUX)
    return XGrabKey(display,AnyKey, ControlMask | ShiftMask,ExGetKeyboardFocus(), True, GrabModeAsync,GrabModeSync);
#endif
}

DECLSPEC ExBoolean ELTAPIFASTENTRY ExAnyKey(void){

	return FALSE;
}
DECLSPEC ExBoolean ELTAPIFASTENTRY ExAnyKeyDown(void){

	return FALSE;
}
DECLSPEC ExBoolean ELTAPIFASTENTRY ExIsKey(const Uint32 keyCode){
#if defined(EX_WINDOWS)
	return (ExBoolean)GetAsyncKeyState(keyCode);
	ExUpdateKeyboard();
	return (KeyBoardState[_index][keyCode] & 0x80);
#elif defined(EX_LINUX)
	return 0;
#endif
}


DECLSPEC ExBoolean ELTAPIFASTENTRY ExIsKeyDown(const Uint32 keyCode){
#if defined(EX_WINDOWS)
	return (ExBoolean)GetAsyncKeyState(keyCode);
#elif defined(EX_LINUX)
    KeySym keysym = 0;
    switch (keyCode){
        case EXK_a:          keysym = XK_A;            break;
        case EXK_b:          keysym = XK_B;            break;
        case EXK_c:          keysym = XK_C;            break;
        case EXK_d:          keysym = XK_D;            break;
        case EXK_e:          keysym = XK_E;            break;
        case EXK_f:          keysym = XK_F;            break;
        case EXK_g:          keysym = XK_G;            break;
        case EXK_h:          keysym = XK_H;            break;
        case EXK_i:          keysym = XK_I;            break;
        case EXK_j:          keysym = XK_J;            break;
        case EXK_k:          keysym = XK_K;            break;
        case EXK_l:          keysym = XK_L;            break;
        case EXK_m:          keysym = XK_M;            break;
        case EXK_n:          keysym = XK_N;            break;
        case EXK_o:          keysym = XK_O;            break;
        case EXK_p:          keysym = XK_P;            break;
        case EXK_q:          keysym = XK_Q;            break;
        case EXK_r:          keysym = XK_R;            break;
        case EXK_s:          keysym = XK_S;            break;
        case EXK_t:          keysym = XK_T;            break;
        case EXK_u:          keysym = XK_U;            break;
        case EXK_v:          keysym = XK_V;            break;
        case EXK_w:          keysym = XK_W;            break;
        case EXK_x:          keysym = XK_X;            break;
        case EXK_y:          keysym = XK_Y;            break;
        case EXK_z:          keysym = XK_Z;            break;
        /*case EXK_Num0:       keysym = XK_0;            break;
        case EXK_Num1:       keysym = XK_1;            break;
        case EXK_Num2:       keysym = XK_2;            break;
        case EXK_Num3:       keysym = XK_3;            break;
        case EXK_Num4:       keysym = XK_4;            break;
        case EXK_Num5:       keysym = XK_5;            break;
        case EXK_Num6:       keysym = XK_6;            break;
        case EXK_Num7:       keysym = XK_7;            break;
        case EXK_Num8:       keysym = XK_8;            break;
        case EXK_Num9:       keysym = XK_9;            break;*/
        /*case EXK_Escape:     keysym = XK_Escape;       break;
        case EXK_LControl:   keysym = XK_Control_L;    break;
        case EXK_LShift:     keysym = XK_Shift_L;      break;
        case EXK_LAlt:       keysym = XK_Alt_L;        break;
        case EXK_LSystem:    keysym = XK_Super_L;      break;
        case EXK_RControl:   keysym = XK_Control_R;    break;
        case EXK_RShift:     keysym = XK_Shift_R;      break;
        case EXK_RAlt:       keysym = XK_Alt_R;        break;
        case EXK_RSystem:    keysym = XK_Super_R;      break;
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
        case EXK_Space:      keysym = XK_space;        break;
        case EXK_Return:     keysym = XK_Return;       break;
        case EXK_BackSpace:  keysym = XK_BackSpace;    break;
        case EXK_Tab:        keysym = XK_Tab;          break;
        case EXK_PageUp:     keysym = XK_Prior;        break;
        case EXK_PageDown:   keysym = XK_Next;         break;
        case EXK_End:        keysym = XK_End;          break;
        case EXK_Home:       keysym = XK_Home;         break;
        case EXK_Insert:     keysym = XK_Insert;       break;
        case EXK_Delete:     keysym = XK_Delete;       break;
        case EXK_Add:        keysym = XK_KP_Add;       break;
        case EXK_Subtract:   keysym = XK_KP_Subtract;  break;
        case EXK_Multiply:   keysym = XK_KP_Multiply;  break;
        case EXK_Divide:     keysym = XK_KP_Divide;    break;
        case EXK_Left:       keysym = XK_Left;         break;
        case EXK_Right:      keysym = XK_Right;        break;
        case EXK_Up:         keysym = XK_Up;           break;
        case EXK_Down:       keysym = XK_Down;         break;
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
        */
        default:             keysym = 0;               break;
    }

    xcb_connection_t* connection = XGetXCBConnection(display);

    unsigned int keycode = XKeysymToKeycode(display, keysym);

    if(keycode != 0){


        xcb_query_keymap_reply_t* keymap = xcb_query_keymap_reply(connection,xcb_query_keymap(connection), NULL);

        unsigned char isPressed = (keymap->keys[keycode/8] & (1 << (keycode % 8))) ?  1 : 0;

        free(keymap);   //TODO check how to allocate a buffer, so we don't need to reallocate it every time
        return isPressed;
    }
    return 0;
#endif
}
DECLSPEC ExBoolean ELTAPIFASTENTRY ExIsKeyUp(const Uint32 keyCode){
#if defined(EX_WINDOWS)
	return GetAsyncKeyState(keyCode);
	if(!((KeyBoardState[_index][keyCode]) & 0x80))
		if(((KeyBoardState[_index1][keyCode]) & 0x80))
			return TRUE;
#elif defined(EX_LINUX)
	return FALSE;
#endif

}
