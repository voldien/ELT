#include"input/elt_keyboard.h"
#include"input/eltkeycode.h"

#include<dinput.h>
#include<dbt.h>
#include<oleauto.h>
#include<shellapi.h>
#ifndef DIRECTINPUT_VERSION
	#define DIRECTINPUT_VERSION 0x800
#endif

/*	TODO seperate the input implemention to corresponding platform directory!	*/

unsigned char KeyBoardState[2][0xFF];

static inline int ExGetKeyCodeInternal(Uint32 keyCode){
    int keysym;

    switch (keyCode){
        case EXK_a:          keysym = 'A';           break;
        case EXK_b:          keysym = 'B';           break;
        case EXK_c:          keysym = 'C';           break;
        case EXK_d:          keysym = 'D';           break;
        case EXK_e:          keysym = 'E';           break;
        case EXK_f:          keysym = 'F';           break;
        case EXK_g:          keysym = 'G';           break;
        case EXK_h:          keysym = 'H';           break;
        case EXK_i:          keysym = 'I';           break;
        case EXK_j:          keysym = 'J';           break;
        case EXK_k:          keysym = 'K';           break;
        case EXK_l:          keysym = 'L';           break;
        case EXK_m:          keysym = 'M';           break;
        case EXK_n:          keysym = 'N';           break;
        case EXK_o:          keysym = 'O';           break;
        case EXK_p:          keysym = 'P';           break;
        case EXK_q:          keysym = 'Q';           break;
        case EXK_r:          keysym = 'R';           break;
        case EXK_s:          keysym = 'S';           break;
        case EXK_t:          keysym = 'T';           break;
        case EXK_u:          keysym = 'U';           break;
        case EXK_v:          keysym = 'V';           break;
        case EXK_w:          keysym = 'W';           break;
        case EXK_x:          keysym = 'X';           break;
        case EXK_y:          keysym = 'Y';           break;
        case EXK_z:          keysym = 'Z';           break;
        /*
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
		*/
        case EXK_LControl:   keysym = VK_LCONTROL;   break;
        case EXK_LShift:     keysym = VK_LSHIFT;     break;
        case EXK_LAlt:       keysym = VK_LMENU;      break;
        case EXK_LSystem:    keysym = VK_LWIN;       break;
        case EXK_RControl:   keysym = VK_RCONTROL;   break;
        case EXK_RShift:     keysym = VK_RSHIFT;     break;
        case EXK_RAlt:       keysym = VK_RMENU;      break;
        case EXK_RSystem:    keysym = VK_RWIN;       break;
        /*
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
        */
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
        default:             keysym = 0;               break;
    }
    return keysym;
}




ELTDECLSPEC ExKeycode ELTAPIENTRY ExGetKeyFromName(const char* name){
	switch(name[0]){
	case ' ':return 0;
	}

}

ELTDECLSPEC const char* ELTAPIENTRY ExGetKeyName(ExKeycode keycode){
	char text[20];
	GetKeyNameTextA((keycode << 16),text,sizeof(text));
	return text;
}

ELTDECLSPEC ExWin ELTAPIENTRY ExGetKeyboardFocus(void){
	return GetFocus();
}

ELTDECLSPEC void ELTAPIENTRY ExSetKeyboardFocus(ExWin window){

}


ELTDECLSPEC const Uint8* ELTAPIENTRY ExGetKeyboardState(Int32* numkeys){
	if(numkeys)*numkeys=0xff;
	unsigned char ispressed = GetKeyboardState(&KeyBoardState[0][0]);
	return KeyBoardState[0];
}

ELTDECLSPEC ExKeycode ELTAPIENTRY ExGetModeState(void){

	return 0;
}

ELTDECLSPEC ExBoolean ELTAPIFASTENTRY ExAnyKey(void){

	return FALSE;
}
ELTDECLSPEC ExBoolean ELTAPIFASTENTRY ExAnyKeyDown(void){

	return FALSE;
}


ExBoolean ELTAPIFASTENTRY ExIsKey(Uint32 keyCode){
	return (ExBoolean)GetAsyncKeyState(keyCode);
}

ExBoolean ELTAPIFASTENTRY ExIsKeyDown(Uint32 keyCode){
	return (ExBoolean)GetAsyncKeyState(keyCode);
}

ExBoolean ELTAPIFASTENTRY ExIsKeyUp(Uint32 keyCode){
	return GetAsyncKeyState(keyCode);
}
