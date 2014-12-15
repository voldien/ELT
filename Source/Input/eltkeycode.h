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
#ifndef _ELT_KEYCODE_H
#define _ELT_KEYCODE_H

enum KeyCodes {
        EK_escape = 0x01,
        EK_NUM1 = 0x02,
        EK_NUM2 = 0x03,
        EK_NUM3 = 0x04,
        EK_NUM4 = 0x05,
        EK_NUM5 = 0x06,
        EK_NUM6 = 0x07,
        EK_NUM7 = 0x08,
        EK_NUM8 = 0x09,
        EK_NUM9 = 0x0A,
        EK_NUM0 = 0x0B,
        EK_MINUS = 0x0C,    /* - on main keyboard */
        EK_EQUALS = 0x0D,
        EK_BACK = 0x0E,    /* backspace */
        EK_TAB = 0x0F,
        EK_Q = 0x10,
        EK_W = 0x11,
        EK_//E = 0x12,
        EK_R = 0x13,
        EK_T = 0x14,
        EK_Y = 0x15,
        EK_U = 0x16,
        EK_I = 0x17,
        EK_O = 0x18,
        EK_P = 0x19,
        EK_LBRACKET = 0x1A,
        EK_RBRACKET = 0x1B,
        EK_RETURN = 0x1C,   /* Enter on main keyboard */
        EK_LCONTROL = 0x1D,
        EK_A = 0x1E,
        EK_S = 0x1F,
        EK_D = 0x20,
        EK_F = 0x21,
        EK_G = 0x22,
        EK_H = 0x23,
        EK_J = 0x24,
        EK_K = 0x25,
        EK_L = 0x26,
        EK_SEMICOLON = 0x27,
        EK_APOSTROPHE = 0x28,
        EK_GRAVE = 0x29,   /* accent grave */
        EK_LSHIFT = 0x2A,
        EK_BACKSLASH = 0x2B,
        EK_Z = 0x2C,
        EK_X = 0x2D,
        EK_C = 0x2E,
        EK_V = 0x2F,
        EK_B = 0x30,
        EK_N = 0x31,
        EK_M = 0x32,
        EK_COMMA = 0x33,
        EK_PERIOD = 0x34,   /* . on main keyboard */
        EK_SLASH = 0x35,  /* / on main keyboard */
        EK_RSHIFT = 0x36,
        EK_MULTIPLY = 0x37,   /* * on numeric keypad */
        EK_LMENU = 0x38,  /* left Alt */
        EK_SPACE = 0x39,
        EK_CAPITAL = 0x3A,
        EK_F1 = 0x3B,
        EK_F2 = 0x3C,
        EK_F3 = 0x3D,
        EK_F4 = 0x3E,
        EK_F5 = 0x3F,
        EK_F6 = 0x40,
        EK_F7 = 0x41,
        EK_F8 = 0x42,
        EK_F9 = 0x43,
        EK_F10 = 0x44,
        EK_NUMLOCK = 0x45,
        EK_SCROLL = 0x46,   /* Scroll Lock */
        EK_NUMPAD7 = 0x47,
        EK_NUMPAD8 = 0x48,
        EK_NUMPAD9 = 0x49,
        EK_SUBTRACT = 0x4A,   /* - on numeric keypad */
        EK_NUMPAD4 = 0x4B,
        EK_NUMPAD5 = 0x4C,
        EK_NUMPAD6 = 0x4D,
        EK_ADD = 0x4E,   /* + on numeric keypad */
        EK_NUMPAD1 = 0x4F,
        EK_NUMPAD2 = 0x50,
        EK_NUMPAD3 = 0x51,
        EK_NUMPAD0 = 0x52,
        EK_decimal = 0x53,   /* . on numeric keypad */
        EK_OEM_102 = 0x56,  /* <> or \| on RT 102-key keyboard (Non-U.S.) */
        EK_F11 = 0x57,
        EK_F12 = 0x58,
        EK_F13 = 0x64,   /*                     (NEC PC98) */
        EK_F14 = 0x65,  /*                     (NEC PC98) */
        EK_F15 = 0x66, /*                     (NEC PC98) */
        EK_KANA = 0x70,/* (Japanese keyboard)            */
        EK_ABNT_C1 = 0x73,   /* /? on Brazilian keyboard */
        EK_CONVERT = 0x79,   /* (Japanese keyboard)            */
        EK_NOCONVERT = 0x7B,   /* (Japanese keyboard)            */
        EK_YEN = 0x7D,   /* (Japanese keyboard)            */
        EK_ABNT_C2 = 0x7E,   /* Numpad . on Brazilian keyboard */
        EK_NUMPADEQUALS = 0x8D,   /* = on numeric keypad (NEC PC98) */
        EK_PREVTRACK = 0x90,   /* Previous Track (CIRCUMFLEX on Japanese keyboard) */
        EK_AT = 0x91,   /*                     (NEC PC98) */
        EK_COLON = 0x92,   /*                     (NEC PC98) */
        EK_UNDERLINE = 0x93,   /*                     (NEC PC98) */
        EK_KANJI = 0x94,   /* (Japanese keyboard)            */
        EK_STOP = 0x95,  /*                     (NEC PC98) */
        EK_AX = 0x96,   /*                     (Japan AX) */
        EK_UNLABELED = 0x97,  /*                        (J3100) */
        EK_NEXTTRACK = 0x99,   /* Next Track */
        EK_NUMPADENTER = 0x9C,   /* Enter on numeric keypad */
        EK_RCONTROL = 0x9D,
        EK_MUTE = 0xA0,   /* Mute */
        EK_CALCULATOR = 0xA1,   /* Calculator */
        EK_PLAYPAUSE = 0xA2,   /* Play / Pause */
        EK_MEDIASTOP = 0xA4,   /* Media Stop */
        EK_VOLUMEDOWN = 0xAE,   /* Volume - */
        EK_VOLUMEUP = 0xB0,   /* Volume + */
        EK_WEBHOME = 0xB2,   /* Web home */
        EK_NUMPADCOMMA = 0xB3,   /* , on numeric keypad (NEC PC98) */
        EK_DIVIDE = 0xB5,  /* / on numeric keypad */
        EK_SYSRQ = 0xB7,
        EK_RMENU = 0xB8,   /* right Alt */
        EK_PAUSE = 0xC5,    /* Pause */
        EK_HOME = 0xC7,    /* Home on arrow keypad */
        EK_UP = 0xC8,    /* UpArrow on arrow keypad */
        EK_PRIOR = 0xC9,    /* PgUp on arrow keypad */
        EK_LEFT = 0xCB,    /* LeftArrow on arrow keypad */
        EK_RIGHT = 0xCD,   /* RightArrow on arrow keypad */
        EK_END = 0xCF,   /* End on arrow keypad */
        EK_DOWN = 0xD0,   /* DownArrow on arrow keypad */
        EK_NEXT = 0xD1,   /* PgDn on arrow keypad */
        EK_INSERT = 0xD2,   /* Insert on arrow keypad */
        EK_Delete = 0xD3,   /* Delete on arrow keypad */
        EK_LWIN = 0xDB,   /* Left Windows key */
        EK_RWIN = 0xDC,   /* Right Windows key */
        EK_APPS = 0xDD,   /* AppMenu key */
        EK_POWER = 0xDE,   /* System Power */
        EK_SLEEP = 0xDF,   /* System Sleep */
        EK_WAKE = 0xE3,   /* System Wake */
        EK_WEBSEARCH = 0xE5,   /* Web Search */
        EK_WEBFAVORITES = 0xE6,   /* Web Favorites */
        EK_WEBREFRESH = 0xE7,   /* Web Refresh */
        EK_WEBSTOP = 0xE8,   /* Web Stop */
        EK_WEBFORWARD = 0xE9,   /* Web Forward */
        EK_WEBBACK = 0xEA,   /* Web Back */
        EK_MYCOMPUTER = 0xEB,   /* My Computer */
        EK_MAIL = 0xEC,   /* Mail */
        EK_MEDIASELECT = 0xED    /* Media Select */
    };


#endif
