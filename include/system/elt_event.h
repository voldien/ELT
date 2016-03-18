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
#ifndef _ELT_EVENT_H_
#define _ELT_EVENT_H_ 1
#include"./../ExNT.h"

#ifdef __cplusplus	/*	C++ Environment	*/
extern "C"{
#endif


EX_ALIGN_PREFIX(4)
typedef struct ex_point{
	int x,y;
}ExPoint;

EX_ALIGN_PREFIX(4)
typedef struct ex_size{
	unsigned int width;
	unsigned int height;
}ExSize;

EX_ALIGN_PREFIX(4)
typedef struct ex_rect{
	int x;
	int y;
	int width;
	int height;
}ExRect;







#define EX_EVENT_KEY 0x1
#define EX_EVENT_KEY_RELEASE 0x2
#define EX_EVENT_KEY_PRESSED 0x4
#define EX_EVENT_MOUSE 0x8
#define EX_EVENT_MOUSE_PRESSED 0x10
#define EX_EVENT_MOUSE_RELEASED 0x20
#define EX_EVENT_SIZE 0x40
#define EX_EVENT_RESIZE 0x40
#define EX_EVENT_SYSTEM 0x80
#define EX_EVENT_MOUSEWHEEL 0x100
#define EX_EVENT_JOYSTICK 0x200
#define EX_EVENT_TOUCH 0x400
#define EX_EVENT_DROP 0x800
#define EX_EVENT_QUIT 0x1000
#define EX_EVENT_MOUSE_MOTION 0x2000
#define EX_EVENT_EXPOSE	0x4000
#define EX_EVENT_ON_FOCUSE	0x8000
#define EX_EVENT_ON_UNFOCUSE 0x10000
#define EX_EVENT_WINDOW_MOVE 0x20000
#define EX_EVENT_WINDOW_DESTROYED 0x40000



EX_ALIGN_PREFIX(4)
typedef struct ex_system_event{

	/*
	 *
	 */
	unsigned int message;
}ExSystemEvent;

EX_ALIGN_PREFIX(4)
typedef struct ex_joy_stick_event{

	/*
	 *
	 */
	Uint8 button[5];
}ExJoyStickEvent;

EX_ALIGN_PREFIX(4)
typedef struct ex_joystick_move_event{

	/*
	 *
	 */
	Uint32 x[3];
}ExJoySticMoveEvent;

EX_ALIGN_PREFIX(4)
typedef struct ex_joystick_button_event{

	/*
	 *
	 */
	Uint8 button[8];
}ExJoySticButtonEvent;

EX_ALIGN_PREFIX(4)
typedef struct ex_mouse_move_event{
	/*
	 *
	 */
	int x;

	/*
	 *
	 */
	int y;
}ExMouseMoveEvent;

EX_ALIGN_PREFIX(4)
typedef struct ex_mouse_motion_event{
	int x;						/**/
	int y;						/**/
	int xdelta;					/**/
	int ydelta;					/**/
}ExMouseMotionEvent;

EX_ALIGN_PREFIX(4)
typedef struct elt_win_button_event{
	Uint8 button;				/**/
}ExWinButtonEvent;

EX_ALIGN_PREFIX(4)
typedef struct ex_mouse_wheel_event{
	int delta;					/**/
	int x,y;					/**/
}ExMouseWheelEvent;

EX_ALIGN_PREFIX(4)
typedef struct ex_key_event{
	/**/
	Uint8 code;
	/**/
	Uint8 alt;
	/**/
	Uint8 shift;
	/**/
	Uint8 system;
	/**/
	Uint8 ctrl;
}ExKeyEvent;

EX_ALIGN_PREFIX(4)
typedef struct ex_drop_event{
	/**/
	int number;
	/**/
	int cize;
}ExDropEvent;


EX_ALIGN_PREFIX(4)
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


EX_ALIGN_PREFIX(4)
typedef struct ex_window_destroy{
	/*
	 *
	 */
	ExWin window;
}ExEventDestroyedWindow;




EX_ALIGN_PREFIX(8)
typedef struct window_poll_events{
	Enum event;                                     /*      */
	ExKeyEvent key;                                 /*      */
	ExSize size;                               		/*      */
	ExMouseMoveEvent mouse;                         /*      */
	ExMouseWheelEvent mouseWheelEvent;              /*      */
	ExWinButtonEvent button;        				/*      */
	ExDropEvent drop;                 				/*      */
	unsigned long int time;							/*		*/
	void* display;									/*		*/
	ExWin window;
}ExWindowEvent;


EX_ALIGN_PREFIX(8)
typedef struct elt_poll_events{
	Enum event;									/*			*/
	ExKeyEvent key;                            	/*          */
	ExMouseMoveEvent mouse;                    	/*          */
	ExMouseWheelEvent mouseWheelEvent;         	/*          */
	ExWinButtonEvent button;    				/*          */
	ExSystemEvent sys;                         	/*          */
	ExDropEvent drop;            				/*          */
	ExSize size;                          		/*          */
	ExSystemEvent system;                      	/*          */
	ExTouchFingerEvent touch;                  	/*          */
	ExMouseMotionEvent motion;					/*			*/
	ExEventDestroyedWindow destroy;				/*			*/
	unsigned long int time;						/*			*/
	void* display;								/*			*/
	/*ExPoint location;	*/
	ExWin window;
}ExEvent;




/*
 *	Poll Event from process.
 *	\event
 *	@Return
*/
extern ELTDECLSPEC Int32 ELTAPIENTRY ExPollEvent(ExEvent* event);

/*
 *	Poll event from specifed window.
 *	\window
 *	\event
 *	@Return
*/


/*
 * Poll Window Event information
 * *[HWND] which window to poll event information.
 *	Remark: message feed will only be apply to given HWND paramter
 *	if HWND is null all window create on this application will be update
 *	read more at MSDN for more specific information regarding PeekMessage with null HWND.
 *	[ExWindowEvent] pointer to event struct. all event will be stored in it.
 *	#return if PeekMessage was success.
 *	PeekMessage : http://msdn.microsoft.com/en-us/library/windows/desktop/ms644943(v=vs.85).aspx
*/
extern ELTDECLSPEC Int32 ELTAPIENTRY ExPollWindowEvent(ExWin window, ExWindowEvent* event);


/*
 *
 *	@Return
 */
extern ELTDECLSPEC Int32 ELTAPIENTRY ExForwardEvent(Uint32 event, ExHandle data, Uint32 size);


#ifdef __cplusplus	/*	C++ Environment	*/
}
#endif
#endif
