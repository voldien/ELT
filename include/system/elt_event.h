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
#ifndef _ELT_EVENT_H_
#define _ELT_EVENT_H_ 1
#include"./../ExNT.h"

#ifdef EX_LINUX
	#include<X11/Xlib.h>
#endif
#ifdef  __cplusplus	// C++ Environment
extern "C"{
#endif
struct expoint{
	int x,y;
};

#define EX_EVENT_MOUSE 0x1
#define EX_EVENT_KEY 0x2
#define EX_EVENT_SIZE 0x4
#define EX_EVENT_SYSTEM 0x8
#define EX_EVENT_MOUSEWHEEL 0x10
#define EX_EVENT_JOYSTICK 0x20
#define EX_EVENT_TOUCH 0x40
#define EX_EVENT_DROP 0x80
#define EX_EVENT_QUIT 0x100

typedef struct ex_system_event{
	unsigned int message;			/**/
}ExSystemEvent;

typedef struct ex_size_event{
	int width;				/**/
	int height;				/**/
}ExSizeEvent;

typedef struct ex_joy_stick_event{
	Uint8 button[5];			/**/
}ExJoyStickEvent;

typedef struct ex_joystick_move_event{
	Uint32 x[3];				/**/
}ExJoySticMoveEvent;

typedef struct ex_joystick_button_event{
	Uint8 button[5];			/**/
}ExJoySticButtonEvent;

typedef struct ex_mouse_move_event{
	int x;					/**/
	int y;					/**/
}ExMouseMoveEvent;

typedef struct elt_win_button_event{
	Uint8 button;				/**/
}ExWinButtonEvent;

typedef struct ex_mouse_wheel_event{
	int delta;				/**/
	int x,y;				/**/
}ExMouseWheelEvent;

typedef struct ex_key_event{
	Uint8 code;				/**/
	Uint8 alt;				/**/
	Uint8 shift;				/**/
	Uint8 system;				/**/
	Uint8 ctrl;				/**/
}ExKeyEvent;

struct ex_drop_event{
	int number;
	int cize;
};

typedef struct ex_touch_finger_event{
    unsigned int type;          /*              */
    unsigned int touchid;       /*              */
    unsigned int fingerid;      /*              */
    float x;                    /*              */
    float y;                    /*              */
    float dx;                   /*              */
    float dy;                   /*              */
    float pressure;             /*              */
}ExTouchFingerEvent;


typedef struct window_poll_events{
	Enum event;                                     /*      */
	ExKeyEvent key;                                 /*      */
	ExSizeEvent size;                               /*      */
	ExMouseMoveEvent mouse;                         /*      */
	ExMouseWheelEvent mouseWheelEvent;              /*      */
	EX_C_STRUCT elt_win_button_event button;        /*      */
	EX_C_STRUCT ex_drop_event drop;                 /*      */

#ifdef EX_WINDOWS
	union{
#ifdef EX_INTERNAL_DEVELOP_ENVIROMENT
		MSG msg;
#endif
		struct{
			ExWin       hwnd;		/*      */
			Uint32      message;	/*      */
			Uint32		wParam;		/*      */
			Long		lParam;		/*      */
			ULong       time;		/*      */
			EX_C_STRUCT expoint	pt;	/*      */
		};
	};
#elif defined(EX_LINUX)
	XEvent msg;
#elif defined(EX_MAC)

#elif defined(EX_ANDROID)

#endif
}ExWindowEvent;


EX_ALIGN_PREFIX(4)
typedef struct elt_poll_events{
	union{
        	Enum eventid;				/**/
        	Enum event;				/**/
	};
	ExKeyEvent key;                                 /*          */
	ExMouseMoveEvent mouse;                         /*          */
	ExMouseWheelEvent mouseWheelEvent;              /*          */
	EX_C_STRUCT elt_win_button_event button;        /*          */
	ExSystemEvent sys;                              /*          */
	EX_C_STRUCT ex_drop_event drop;                 /*          */
	ExSizeEvent size;                               /*          */
	ExSystemEvent system;                           /*          */
	ExTouchFingerEvent touch;                       /*          */

#ifdef EX_WINDOWS
	union{
#ifdef EX_INTERNAL_DEVELOP_ENVIROMENT
		MSG msg;
#endif
		struct{
			ExWin       hwnd;
			Uint32      message;
			Uint32		wParam;
			Long		lParam;
			ULong       time;
			EX_C_STRUCT expoint     pt;
		};
	};
#elif defined(EX_LINUX)
	XEvent msg;
#elif defined(EX_ANDROID)
	void* source;
#elif defined(EX_MAC)
	long time;
#endif

}ExEvent;
/**
	Poll Event from process.
	\event
	@return 
*/
extern DECLSPEC Int32 ELTAPIENTRY ExPollEvent(ExEvent* event);
/**
	Poll event from specifed window.
	\window
	\event 
	@return 
*/
//extern DECLSPEC Int32 ELTAPIENTRY ExPollWindowEvent(ExWin window,ExEvent* event);

#ifdef __cplusplus	// C++ Environment
}
#endif
#endif
