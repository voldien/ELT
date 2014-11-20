#include"elt_event.h"
#include"Unix/unix_win.h"
#include"./../ExAssert.h"
#ifndef MATH_LIB_H
	#include<Cmd/mathlib.h>
#endif
#ifdef EX_WINDOWS
	#include<WindowsX.h>
#elif defined(EX_LINUX)

#endif



DECLSPEC Int32 ELTAPIENTRY ExPollEvent(ExEvents* event){

#ifdef EX_WINDOWS
	assert(event);
	PeekMessage(&event->msg,NULL,NULL,NULL,PM_REMOVE);

	switch(event->msg.message){
		case WM_DEVICECHANGE:{
		}break;
		case WM_INPUT:{

		}break;
		case WM_INPUT_DEVICE_CHANGE:{
			RID_DEVICE_INFO info;
			info.cbSize = sizeof(info);
			switch(event->msg.wParam){
			case GIDC_ARRIVAL:
				GetRawInputDeviceInfo((HANDLE)event->msg.lParam,RIDI_DEVICEINFO,&info,0);
				break;
			case GIDC_REMOVAL:
				break;
			}
		}break;
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
			// keycode
			event->key.code = (Uint8)event->msg.wParam;
			event->eventid |= EX_EVENT_KEY;
			event->key.alt = !(event->msg.wParam ^ VK_MENU);
			event->key.shift = !(event->msg.wParam ^ VK_SHIFT);
			event->key.system = !(event->msg.wParam ^ VK_LWIN );
			event->key.ctrl  = !(event->msg.wParam ^ VK_CONTROL);
			break;
		case WM_KEYUP:
		case WM_SYSKEYUP:
			event->eventid = (~EX_EVENT_KEY & event->eventid);
			break;
		case WM_HOTKEY:
			event->key.alt = !(event->msg.lParam ^ MOD_ALT);
			event->key.shift = !(event->msg.lParam ^ MOD_SHIFT);
			event->key.system = !(event->msg.lParam ^ MOD_WIN );
			event->key.ctrl  = !(event->msg.lParam ^ MOD_CONTROL);
			break;
		case WM_LBUTTONDOWN:
		case WM_RBUTTONDOWN:
		case WM_MBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_RBUTTONUP:
		case WM_MBUTTONUP:
		case WM_MOUSEMOVE:{
			event->mouse.x = GET_X_LPARAM(event->msg.lParam);
			event->mouse.y = GET_Y_LPARAM(event->msg.lParam);
			event->eventid = EX_EVENT_MOUSE;
			event->button.button = (Uint8)event->msg.wParam;
			event->eventid |= EX_EVENT_MOUSE;
		}
		case WM_MOUSEHWHEEL:
		case WM_MOUSEWHEEL :{
			event->mouseWheelEvent.x = GET_X_LPARAM(event->msg.lParam);
			event->mouseWheelEvent.y = GET_X_LPARAM(event->msg.lParam);
			event->mouseWheelEvent.delta = GET_WHEEL_DELTA_WPARAM(event->msg.wParam);
			GET_KEYSTATE_WPARAM(event->msg.wParam);
			event->eventid |= EX_EVENT_MOUSEWHEEL;
		}break;
		case WM_DROPFILES:{
			event->drop.number = DragQueryFile((HDROP)event->wParam,0xFFFFFFFF,0,0);
			event->eventid |= EX_EVENT_DROP;
			break;
		}
		default:break;
	}

	return TRUE;
#elif defined(EX_LINUX)
	if(XPending(display)){
		XNextEvent(display,&event->msg);

		switch(event->msg.type){
		case KeyPress:{
		    event->eventid |= EX_EVENT_KEY;
		    event->key.code = event->msg.xkey.keycode;
        }break;
		case KeyRelease:{
		    event->eventid |= EX_EVENT_KEY;
		    event->key.code = event->msg.xkey.keycode;
		}break;
		case ButtonPress:{
		    event->eventid |= EX_EVENT_MOUSE;
		    event->button.button = event->msg.xbutton.button;
        }break;
		case ButtonRelease:{
		    event->eventid |= EX_EVENT_MOUSE;
		    event->button.button = event->msg.xbutton.button;
		}break;
		case ResizeRequest:{
            event->eventid |= EX_EVENT_SIZE;
		}break;
		case MotionNotify:{
            event->mouse.x = event->msg.xmotion.x;
            event->mouse.y = event->msg.xmotion.y;
		}break;
		case ClientMessage:{

		}break;
		case ConfigureNotify:{

		}break;
		default:event->eventid = 0;break;
		}

		return TRUE;
	}else {XSync(display,0); return FALSE;}
#elif defined(EX_ANDROID)

#elif defined(EX_MAC)

#elif defined(EX_IPHONE)

#endif
}
