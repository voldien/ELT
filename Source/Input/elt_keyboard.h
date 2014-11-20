/*
===========================================================================
Copyright (C) 2014 BroodCity Software, Inc. Voldemor2009@hotmail.com

*/
#ifndef ELT_KEYBOARD_H
#define ELT_KEYBOARD_H
#include"./../EngineAssembly.h"
#ifndef DIRECTINPUT_VERSION
#	define DIRECTINPUT_VERSION 0x800
#endif
typedef Keycode ExScancode;
#ifdef __cplusplus	// C++ Environment
extern "C"{
#endif
/*
	// Get KeyCode name identifiction index
*/
extern DECLSPEC Keycode ELTAPIENTRY ExGetKeyFromName(const char* name);
/*
	//	Get Key from Scancode
*/
extern DECLSPEC Keycode ELTAPIENTRY ExGetKeyFromScancode(ExScancode scancode);
/*
	// Get KeyCode name
*/
extern DECLSPEC const char* ELTAPIENTRY ExGetKeyName(Keycode keycode);

/*
	// Get Window that is keyboard is focus to
*/
extern DECLSPEC ExWin ELTAPIENTRY ExGetKeyboardFocus(void);
/*
	//
*/
extern DECLSPEC const Uint8* ELTAPIENTRY ExGetKeyboardState(Int32* numkeys);
/*
	//
*/
extern DECLSPEC Keycode ELTAPIENTRY ExGetModeState(void);

/*
	// is any key pressed
*/
extern DECLSPEC Boolean ELTAPIFASTENTRY ExAnyKey(void);
/*
	//
*/
extern DECLSPEC Boolean ELTAPIFASTENTRY ExAnyKeyDown(void);
/*
	//
*/
extern DECLSPEC Boolean ELTAPIFASTENTRY ExIsKey(const Uint32 keyCode);
extern DECLSPEC Boolean ELTAPIFASTENTRY ExIsKeyDown(const Uint32 keyCode);
extern DECLSPEC Boolean ELTAPIFASTENTRY ExIsKeyUp(const Uint32 keyCode);


#ifdef INTERNAL_ENGINEX

#ifdef EX_WINDOWS
extern IDirectInputDevice8* m_keyboard_device;
#endif
extern DECLSPEC ERESULT ELTAPIENTRY ExInitKeyBoard(ExWin win); 
extern DECLSPEC ERESULT ELTAPIENTRY ExSetKeyBoardCooperative(ExWin win, Uint32 flag); 
extern DECLSPEC void ELTAPIENTRY ExUpdateKeyboard(void);
extern DECLSPEC void ELTAPIENTRY ExKeyBoardShutDown(void);
#endif


#if defined(EX_WINDOWS) // if directX
#ifndef KEYCODES_ENUM
#define KEYCODES_ENUM
#pragma warning(disable : 4480)
    enum KeyCodes : Uint8{
        escape = 0x01,
        NUM1 = 0x02,
        NUM2 = 0x03,
        NUM3 = 0x04,
        NUM4 = 0x05,
        NUM5 = 0x06,
        NUM6 = 0x07,
        NUM7 = 0x08,
        NUM8 = 0x09,
        NUM9 = 0x0A,
        NUM0 = 0x0B,
        MINUS = 0x0C,    /* - on main keyboard */
        EQUALS = 0x0D,
        BACK = 0x0E,    /* backspace */
        TAB = 0x0F,
        Q = 0x10,
        W = 0x11,
        //E = 0x12,
        R = 0x13,
        T = 0x14,
        Y = 0x15,
        U = 0x16,
        I = 0x17,
        O = 0x18,
        P = 0x19,
        LBRACKET = 0x1A,
        RBRACKET = 0x1B,
        RETURN = 0x1C,   /* Enter on main keyboard */
        LCONTROL = 0x1D,
        A = 0x1E,
        S = 0x1F,
        D = 0x20,
        F = 0x21,
        G = 0x22,
        H = 0x23,
        J = 0x24,
        K = 0x25,
        L = 0x26,
        SEMICOLON = 0x27,
        APOSTROPHE = 0x28,
        GRAVE = 0x29,   /* accent grave */
        LSHIFT = 0x2A,
        BACKSLASH = 0x2B,
        Z = 0x2C,
        X = 0x2D,
        C = 0x2E,
        V = 0x2F,
        B = 0x30,
        N = 0x31,
        M = 0x32,
        COMMA = 0x33,
        PERIOD = 0x34,   /* . on main keyboard */
        SLASH = 0x35,  /* / on main keyboard */
        RSHIFT = 0x36,
        MULTIPLY = 0x37,   /* * on numeric keypad */
        LMENU = 0x38,  /* left Alt */
        SPACE = 0x39,
        CAPITAL = 0x3A,
        F1 = 0x3B,
        F2 = 0x3C,
        F3 = 0x3D,
        F4 = 0x3E,
        F5 = 0x3F,
        F6 = 0x40,
        F7 = 0x41,
        F8 = 0x42,
        F9 = 0x43,
        F10 = 0x44,
        NUMLOCK = 0x45,
        SCROLL = 0x46,   /* Scroll Lock */
        NUMPAD7 = 0x47,
        NUMPAD8 = 0x48,
        NUMPAD9 = 0x49,
        SUBTRACT = 0x4A,   /* - on numeric keypad */
        NUMPAD4 = 0x4B,
        NUMPAD5 = 0x4C,
        NUMPAD6 = 0x4D,
        ADD = 0x4E,   /* + on numeric keypad */
        NUMPAD1 = 0x4F,
        NUMPAD2 = 0x50,
        NUMPAD3 = 0x51,
        NUMPAD0 = 0x52,
        decimal = 0x53,   /* . on numeric keypad */
        OEM_102 = 0x56,  /* <> or \| on RT 102-key keyboard (Non-U.S.) */
        F11 = 0x57,
        F12 = 0x58,
        F13 = 0x64,   /*                     (NEC PC98) */
        F14 = 0x65,  /*                     (NEC PC98) */
        F15 = 0x66, /*                     (NEC PC98) */
        KANA = 0x70,/* (Japanese keyboard)            */
        ABNT_C1 = 0x73,   /* /? on Brazilian keyboard */
        CONVERT = 0x79,   /* (Japanese keyboard)            */
        NOCONVERT = 0x7B,   /* (Japanese keyboard)            */
        YEN = 0x7D,   /* (Japanese keyboard)            */
        ABNT_C2 = 0x7E,   /* Numpad . on Brazilian keyboard */
        NUMPADEQUALS = 0x8D,   /* = on numeric keypad (NEC PC98) */
        PREVTRACK = 0x90,   /* Previous Track (CIRCUMFLEX on Japanese keyboard) */
        AT = 0x91,   /*                     (NEC PC98) */
        COLON = 0x92,   /*                     (NEC PC98) */
        UNDERLINE = 0x93,   /*                     (NEC PC98) */
        KANJI = 0x94,   /* (Japanese keyboard)            */
        STOP = 0x95,  /*                     (NEC PC98) */
        AX = 0x96,   /*                     (Japan AX) */
        UNLABELED = 0x97,  /*                        (J3100) */
        NEXTTRACK = 0x99,   /* Next Track */
        NUMPADENTER = 0x9C,   /* Enter on numeric keypad */
        RCONTROL = 0x9D,
        MUTE = 0xA0,   /* Mute */
        CALCULATOR = 0xA1,   /* Calculator */
        PLAYPAUSE = 0xA2,   /* Play / Pause */
        MEDIASTOP = 0xA4,   /* Media Stop */
        VOLUMEDOWN = 0xAE,   /* Volume - */
        VOLUMEUP = 0xB0,   /* Volume + */
        WEBHOME = 0xB2,   /* Web home */
        NUMPADCOMMA = 0xB3,   /* , on numeric keypad (NEC PC98) */
        DIVIDE = 0xB5,  /* / on numeric keypad */
        SYSRQ = 0xB7,
        RMENU = 0xB8,   /* right Alt */
        PAUSE = 0xC5,    /* Pause */
        HOME = 0xC7,    /* Home on arrow keypad */
        UP = 0xC8,    /* UpArrow on arrow keypad */
        PRIOR = 0xC9,    /* PgUp on arrow keypad */
        LEFT = 0xCB,    /* LeftArrow on arrow keypad */
        RIGHT = 0xCD,   /* RightArrow on arrow keypad */
        END = 0xCF,   /* End on arrow keypad */
        DOWN = 0xD0,   /* DownArrow on arrow keypad */
        NEXT = 0xD1,   /* PgDn on arrow keypad */
        INSERT = 0xD2,   /* Insert on arrow keypad */
        Delete = 0xD3,   /* Delete on arrow keypad */
        LWIN = 0xDB,   /* Left Windows key */
        RWIN = 0xDC,   /* Right Windows key */
        APPS = 0xDD,   /* AppMenu key */
        POWER = 0xDE,   /* System Power */
        SLEEP = 0xDF,   /* System Sleep */
        WAKE = 0xE3,   /* System Wake */
        WEBSEARCH = 0xE5,   /* Web Search */
        WEBFAVORITES = 0xE6,   /* Web Favorites */
        WEBREFRESH = 0xE7,   /* Web Refresh */
        WEBSTOP = 0xE8,   /* Web Stop */
        WEBFORWARD = 0xE9,   /* Web Forward */
        WEBBACK = 0xEA,   /* Web Back */
        MYCOMPUTER = 0xEB,   /* My Computer */
        MAIL = 0xEC,   /* Mail */
        MEDIASELECT = 0xED    /* Media Select */
    };
#endif
#elif defined(EX_LINUX)
#ifndef KEYCODES_ENUM
#define KEYCODES_ENUM
    enum KeyCodes{
        escape = 0x01,
        NUM1 = 0x02,
        NUM2 = 0x03,
        NUM3 = 0x04,
        NUM4 = 0x05,
        NUM5 = 0x06,
        NUM6 = 0x07,
        NUM7 = 0x08,
        NUM8 = 0x09,
        NUM9 = 0x0A,
        NUM0 = 0x0B,
        MINUS = 0x0C,    /* - on main keyboard */
        EQUALS = 0x0D,
        BACK = 0x0E,    /* backspace */
        TAB = 0x0F,
        Q = 0x10,
        W = 0x11,
        //E = 0x12,
        R = 0x13,
        T = 0x14,
        Y = 0x15,
        U = 0x16,
        I = 0x17,
        O = 0x18,
        P = 0x19,
        LBRACKET = 0x1A,
        RBRACKET = 0x1B,
        RETURN = 0x1C,   /* Enter on main keyboard */
        LCONTROL = 0x1D,
        A = 0x1E,
        S = 0x1F,
        D = 0x20,
        F = 0x21,
        G = 0x22,
        H = 0x23,
        J = 0x24,
        K = 0x25,
        L = 0x26,
        SEMICOLON = 0x27,
        APOSTROPHE = 0x28,
        GRAVE = 0x29,   /* accent grave */
        LSHIFT = 0x2A,
        BACKSLASH = 0x2B,
        Z = 0x2C,
        X = 0x2D,
        C = 0x2E,
        V = 0x2F,
        B = 0x30,
        N = 0x31,
        M = 0x32,
        COMMA = 0x33,
        PERIOD = 0x34,   /* . on main keyboard */
        SLASH = 0x35,  /* / on main keyboard */
        RSHIFT = 0x36,
        MULTIPLY = 0x37,   /* * on numeric keypad */
        LMENU = 0x38,  /* left Alt */
        SPACE = 0x39,
        CAPITAL = 0x3A,
        F1 = 0x3B,
        F2 = 0x3C,
        F3 = 0x3D,
        F4 = 0x3E,
        F5 = 0x3F,
        F6 = 0x40,
        F7 = 0x41,
        F8 = 0x42,
        F9 = 0x43,
        F10 = 0x44,
        NUMLOCK = 0x45,
        SCROLL = 0x46,   /* Scroll Lock */
        NUMPAD7 = 0x47,
        NUMPAD8 = 0x48,
        NUMPAD9 = 0x49,
        SUBTRACT = 0x4A,   /* - on numeric keypad */
        NUMPAD4 = 0x4B,
        NUMPAD5 = 0x4C,
        NUMPAD6 = 0x4D,
        ADD = 0x4E,   /* + on numeric keypad */
        NUMPAD1 = 0x4F,
        NUMPAD2 = 0x50,
        NUMPAD3 = 0x51,
        NUMPAD0 = 0x52,
        decimal = 0x53,   /* . on numeric keypad */
        OEM_102 = 0x56,  /* <> or \| on RT 102-key keyboard (Non-U.S.) */
        F11 = 0x57,
        F12 = 0x58,
        F13 = 0x64,   /*                     (NEC PC98) */
        F14 = 0x65,  /*                     (NEC PC98) */
        F15 = 0x66, /*                     (NEC PC98) */
        KANA = 0x70,/* (Japanese keyboard)            */
        ABNT_C1 = 0x73,   /* /? on Brazilian keyboard */
        CONVERT = 0x79,   /* (Japanese keyboard)            */
        NOCONVERT = 0x7B,   /* (Japanese keyboard)            */
        YEN = 0x7D,   /* (Japanese keyboard)            */
        ABNT_C2 = 0x7E,   /* Numpad . on Brazilian keyboard */
        NUMPADEQUALS = 0x8D,   /* = on numeric keypad (NEC PC98) */
        PREVTRACK = 0x90,   /* Previous Track (CIRCUMFLEX on Japanese keyboard) */
        AT = 0x91,   /*                     (NEC PC98) */
        COLON = 0x92,   /*                     (NEC PC98) */
        UNDERLINE = 0x93,   /*                     (NEC PC98) */
        KANJI = 0x94,   /* (Japanese keyboard)            */
        STOP = 0x95,  /*                     (NEC PC98) */
        AX = 0x96,   /*                     (Japan AX) */
        UNLABELED = 0x97,  /*                        (J3100) */
        NEXTTRACK = 0x99,   /* Next Track */
        NUMPADENTER = 0x9C,   /* Enter on numeric keypad */
        RCONTROL = 0x9D,
        MUTE = 0xA0,   /* Mute */
        CALCULATOR = 0xA1,   /* Calculator */
        PLAYPAUSE = 0xA2,   /* Play / Pause */
        MEDIASTOP = 0xA4,   /* Media Stop */
        VOLUMEDOWN = 0xAE,   /* Volume - */
        VOLUMEUP = 0xB0,   /* Volume + */
        WEBHOME = 0xB2,   /* Web home */
        NUMPADCOMMA = 0xB3,   /* , on numeric keypad (NEC PC98) */
        DIVIDE = 0xB5,  /* / on numeric keypad */
        SYSRQ = 0xB7,
        RMENU = 0xB8,   /* right Alt */
        PAUSE = 0xC5,    /* Pause */
        HOME = 0xC7,    /* Home on arrow keypad */
        UP = 0xC8,    /* UpArrow on arrow keypad */
        PRIOR = 0xC9,    /* PgUp on arrow keypad */
        LEFT = 0xCB,    /* LeftArrow on arrow keypad */
        RIGHT = 0xCD,   /* RightArrow on arrow keypad */
        END = 0xCF,   /* End on arrow keypad */
        DOWN = 0xD0,   /* DownArrow on arrow keypad */
        NEXT = 0xD1,   /* PgDn on arrow keypad */
        INSERT = 0xD2,   /* Insert on arrow keypad */
        Delete = 0xD3,   /* Delete on arrow keypad */
        LWIN = 0xDB,   /* Left Windows key */
        RWIN = 0xDC,   /* Right Windows key */
        APPS = 0xDD,   /* AppMenu key */
        POWER = 0xDE,   /* System Power */
        SLEEP = 0xDF,   /* System Sleep */
        WAKE = 0xE3,   /* System Wake */
        WEBSEARCH = 0xE5,   /* Web Search */
        WEBFAVORITES = 0xE6,   /* Web Favorites */
        WEBREFRESH = 0xE7,   /* Web Refresh */
        WEBSTOP = 0xE8,   /* Web Stop */
        WEBFORWARD = 0xE9,   /* Web Forward */
        WEBBACK = 0xEA,   /* Web Back */
        MYCOMPUTER = 0xEB,   /* My Computer */
        MAIL = 0xEC,   /* Mail */
        MEDIASELECT = 0xED    /* Media Select */
    };
#endif
#endif

#ifdef __cplusplus	// C++ Environment
}
#endif
#endif