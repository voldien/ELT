/*
===========================================================================
Copyright (C) 2014 BroodCity Software, Inc. Voldemor2009@hotmail.com

*/
#ifndef ELT_EVENT_H
#define ELT_EVENT_H
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

struct ExSystemEvent{
	Uint32 message;
};
struct ExSizeEvent{
	Int32 width, height;
};
struct ExJoySticEvent{
	Uint8 button[5];
};
struct ExJoySticMoveEvent{
	Uint32 x[3];
};
struct ExJoySticButtonEvent{
	Uint8 button[5];
};
struct ExMouseMoveEvent{
	Int32 x,y;
};
struct elt_win_button_event{
	Uint8 button;
};
struct ExMouseWheelEvent{
	Int32 delta;
	Int32 x,y;
};
struct ExKeyEvent{
	Uint8 code;
	Uint8 alt;
	Uint8 shift;
	Uint8 system;
	Uint8 ctrl;
};
struct ex_drop_event{
	Int32 number;
	Int32 cize;
};

typedef struct window_poll_events{
	Enum event;
	EX_C_STRUCT ExKeyEvent key;
	EX_C_STRUCT ExSizeEvent size;
	EX_C_STRUCT ExMouseMoveEvent mouse;
	EX_C_STRUCT ExMouseWheelEvent mouseWheelEvent;
	EX_C_STRUCT elt_win_button_event button;
	EX_C_STRUCT ex_drop_event drop;

#ifdef EX_WINDOWS
	union{
#ifdef EX_INTERNAL_DEVELOP_ENVIROMENT
		MSG msg;
#endif
		struct{
			ExWin       hwnd;		//
			Uint32      message;	//
			Uint32		wParam;		//
			Long		lParam;		//
			ULong       time;		//
			EX_C_STRUCT expoint	pt;	//
		};
	};
#elif defined(EX_LINUX)
	XEvent msg;
#elif defined(EX_MAC)
#elif defined(EX_ANDROID)

#endif
}ExWindowEvent;


typedef struct elt_poll_events{
	union{
        Enum eventid;
        Enum event;
	};
	EX_C_STRUCT ExKeyEvent key;
	EX_C_STRUCT ExMouseMoveEvent mouse;
	EX_C_STRUCT ExMouseWheelEvent mouseWheelEvent;
	EX_C_STRUCT elt_win_button_event button;
	EX_C_STRUCT ExSystemEvent sys;
	EX_C_STRUCT ex_drop_event drop;
	EX_C_STRUCT ExSizeEvent size;
	EX_C_STRUCT ExSystemEvent system;

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
#elif defined(EX_MAC)

#endif

}ExEvents,ExEvent;  //TODO change to ExEvent
/*
	//	Get Event
*/
extern DECLSPEC Int32 ELTAPIENTRY ExPollEvent(ExEvents* event);

//extern DECLSPEC Int32 ELTAPIENTRY ExGetDropFileCount(void* data);

#ifdef __cplusplus	// C++ Environment
}
#endif
#endif
