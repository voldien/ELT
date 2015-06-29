#include"system/elt_event.h"
#include"ExAssert.h"
#include"ExPreProcessor.h"
#ifdef EX_WINDOWS
#	include"system/win/win_wndproc.h"
#	define WIN32_LEAN_AND_MEAN
#	include<windows.h>
#	include <winuser.h>
#elif defined(EX_LINUX)
#	include"system/unix/unix_win.h"
#	include<X11/X.h>
#	include<X11/Xlib.h>
#elif defined(EX_ANDROID)
#   include<errno.h>
#   include<android/window.h>
#   include<android/rect.h>
#   include<android/input.h>
#   include<android/looper.h>
#   include<android/sensor.h>
#elif defined(EX_MAC)

#endif


DECLSPEC Int32 ELTAPIENTRY ExPollEvent(ExEvent* event){
#ifdef EX_WINDOWS
	assert(event);
	MSG msg;
	PeekMessage(&msg,NULL,NULL,NULL,PM_REMOVE);

	switch(msg.message){
		case WM_DEVICECHANGE:{
		}break;
		case WM_INPUT:{

		}break;
/*
		case WM_INPUT_DEVICE_CHANGE:{
			RID_DEVICE_INFO info;
			info.cbSize = sizeof(info);
			switch(msg.wParam){
			case GIDC_ARRIVAL:
				GetRawInputDeviceInfo((HANDLE)msg.lParam,RIDI_DEVICEINFO,&info,0);
				break;
			case GIDC_REMOVAL:
				break;
			}
		}break;*/
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:

			event->key.code = (Uint8)msg.wParam;
			event->eventid |= EX_EVENT_KEY;
			event->key.alt = !(msg.wParam ^ VK_MENU);
			event->key.shift = !(msg.wParam ^ VK_SHIFT);
			event->key.system = !(msg.wParam ^ VK_LWIN );
			event->key.ctrl  = !(msg.wParam ^ VK_CONTROL);
			break;
		case WM_KEYUP:
		case WM_SYSKEYUP:
			event->eventid = (~EX_EVENT_KEY & event->eventid);
			break;
		case WM_HOTKEY:
			event->key.alt = !(msg.lParam ^ MOD_ALT);
			event->key.shift = !(msg.lParam ^ MOD_SHIFT);
			event->key.system = !(msg.lParam ^ MOD_WIN );
			event->key.ctrl  = !(msg.lParam ^ MOD_CONTROL);
			break;
		case WM_LBUTTONDOWN:
		case WM_RBUTTONDOWN:
		case WM_MBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_RBUTTONUP:
		case WM_MBUTTONUP:
		case WM_MOUSEMOVE:{
			event->mouse.x = GET_X_LPARAM(msg.lParam);
			event->mouse.y = GET_Y_LPARAM(msg.lParam);
			event->eventid = EX_EVENT_MOUSE;
			event->button.button = (Uint8)msg.wParam;
			event->eventid |= EX_EVENT_MOUSE;
		}
/*		case WM_MOUSEWHEEL:{
			event->mouseWheelEvent.x = GET_X_LPARAM(msg.lParam);
			event->mouseWheelEvent.y = GET_X_LPARAM(msg.lParam);
			event->mouseWheelEvent.delta = GET_WHEEL_DELTA_WPARAM(msg.wParam);
			GET_KEYSTATE_WPARAM(msg.wParam);
			event->eventid |= EX_EVENT_MOUSEWHEEL;
		}break;*/
		case WM_DROPFILES:{
			event->drop.number = DragQueryFile((HDROP)msg.wParam,0xFFFFFFFF,0,0);
			event->eventid |= EX_EVENT_DROP;
			break;
		}
		switch(msg.lParam){ /*  network */
		    case FD_ACCEPT:break;
		    case FD_CONNECT:break;
		    case FD_READ:break;
		    case FD_CLOSE:break;
		}
		default:break;
	}

	return TRUE;
#elif defined(EX_LINUX)
	XEvent msg;
	if(XPending(display)){
		XNextEvent(display,&msg);
		event->event = 0;
		switch(msg.type){
		case KeymapNotify:
            XRefreshKeyboardMapping(&msg.xmapping);
        break;
		case KeyPress:{
		    event->event |= EX_EVENT_KEY;
		    event->key.code = XLookupKeysym(&msg.xkey,0);//.keycode;
		    event->mouse.x = msg.xkey.x;
		    event->mouse.y = msg.xkey.y;
		    event->key.alt = msg.xkey.state & Mod1Mask;
		    event->key.ctrl = msg.xkey.state & ControlMask;
		    event->key.shift = msg.xkey.state & ShiftMask;
		    event->key.system = msg.xkey.state & Mod1Mask;

        }break;
		case KeyRelease:{
		    event->event |= EX_EVENT_KEY_RELEASE;
		    event->key.code = XLookupKeysym(&msg.xkey,0);//.keycode;
		    event->mouse.x = msg.xkey.x;
		    event->mouse.y = msg.xkey.y;
		}break;
		case ButtonPress:{
		    event->event |= EX_EVENT_MOUSE;
		    event->button.button = msg.xbutton.button;
		    event->mouse.x = msg.xkey.x;
		    event->mouse.y = msg.xkey.y;
        }break;
		case ButtonRelease:{
		    event->event |= EX_EVENT_MOUSE;
		    event->button.button = msg.xbutton.button;
		    event->mouse.x = msg.xkey.x;
		    event->mouse.y = msg.xkey.y;
		}break;
		case MotionNotify:{
			event->event |= EX_EVENT_MOUSE_MOTION;
			event->motion.xdelta =  msg.xmotion.x - msg.xkey.x;
			event->motion.ydelta =  msg.xmotion.y - msg.xkey.y;
			event->motion.x = msg.xmotion.x;
			event->motion.y = msg.xmotion.y;

		}break;
		case GravityNotify:
			event->event |= EX_EVENT_WINDOW_MOVE;
			break;
		case ResizeRequest:{
            //event->event |= EX_EVENT_SIZE;
            //event->size.width = msg.xresizerequest.width;
            //event->size.height = msg.xresizerequest.height;
		}break;
		case Expose:{
			event->event |= EX_EVENT_EXPOSE;
		}break;
		case ClientMessage:{
            event->event |= EX_EVENT_SIZE;

		}break;
		case ConfigureNotify:{
            event->event |= EX_EVENT_SIZE;
            event->size.width =  msg.xconfigure.width;
            event->size.height = msg.xconfigure.height;
		}break;
		case FocusIn:
			break;
		case FocusOut:
			break;
		case LASTEvent:
			event->event = 0;break;
		}

		event->time = clock();
		event->window = msg.xany.window;
		return TRUE;
	}else {/*XSync(display,TRUE);*/ return FALSE;}
#elif defined(EX_ANDROID)
    int ident;
    int events;
    void* source;

    switch(ident = ALooper_pollAll(0, NULL,&events,&source)){
    	if(source){
    		//source->process(state,source);
    	}


        default:break;
    }

    return TRUE;
#elif defined(EX_MAC)


#elif defined(EX_PNACL)


#elif defined(EX_IPHONE)


#elif defined(EX_WEB)


#elif defined(EX_PS3)


#endif
}



DECLSPEC ExBoolean ELTAPIENTRY ExPollWindowEvent(ExWin hWnd, ExWindowEvent* event){
#ifdef EX_WINDOWS
	MSG msg;
	//event->event = 0;
	// peek Message for given window handle.
	if(PeekMessage(&msg,hWnd,NULL, NULL, PM_REMOVE)){
		DispatchMessage(&msg);
		TranslateMessage(&msg);

		switch(msg.message){
			case WM_SIZE:
			case WM_SIZING:
			case WM_USER_SIZE:{
				event->size.width = EX_LOWORD(msg.lParam);
				event->size.height = EX_HIWORD(msg.lParam);
				event->event = EX_EVENT_SIZE;
			}break;
			/*case WM_DEVICECHANGE:
				break;
			*/
			case WM_INPUT:{

			}break;
/*
			case WM_INPUT_DEVICE_CHANGE:{
				RID_DEVICE_INFO info;
				info.cbSize = sizeof(info);
				switch(msg.wParam){
				case GIDC_ARRIVAL:
					GetRawInputDeviceInfo((HANDLE)msg.lParam,RIDI_DEVICEINFO,&info,0);
					break;
				case GIDC_REMOVAL:
					break;
				}
			}break;*/
			case WM_KEYDOWN:
			case WM_SYSKEYDOWN:
				// keycode
				event->key.code = msg.wParam;
				event->event |= EX_EVENT_KEY;
				event->key.alt = !(msg.wParam ^ VK_MENU);
				event->key.shift = !(msg.wParam ^ VK_SHIFT);
				event->key.system = !(msg.wParam ^ VK_LWIN );
				event->key.ctrl  = !(msg.wParam ^ VK_CONTROL);
				break;
			case WM_KEYUP:
			case WM_SYSKEYUP:
				event->event = (~EX_EVENT_KEY & event->event);
				break;
			case WM_HOTKEY:
				event->key.alt = !(msg.lParam ^ MOD_ALT);
				event->key.shift = !(msg.lParam ^ MOD_SHIFT);
				event->key.system = !(msg.lParam ^ MOD_WIN );
				event->key.ctrl  = !(msg.lParam ^ MOD_CONTROL);
				break;
			case WM_LBUTTONDOWN:
			case WM_RBUTTONDOWN:
			case WM_MBUTTONDOWN:
			case WM_LBUTTONUP:
			case WM_RBUTTONUP:
			case WM_MBUTTONUP:
			case WM_MOUSEMOVE:{
				event->mouse.x = GET_X_LPARAM(msg.lParam);
				event->mouse.y = GET_Y_LPARAM(msg.lParam);
				event->event = EX_EVENT_MOUSE;
				event->button.button = msg.wParam;
				event->event |= EX_EVENT_MOUSE;
			/*
			case WM_MOUSEHWHEEL:
			case WM_MOUSEWHEEL :
				event->mouseWheelEvent.x = GET_X_LPARAM(msg.lParam);
				event->mouseWheelEvent.y = GET_X_LPARAM(msg.lParam);
				event->mouseWheelEvent.delta = GET_WHEEL_DELTA_WPARAM(msg.wParam);
				GET_KEYSTATE_WPARAM(msg.wParam);
				event->event |= EX_EVENT_MOUSEWHEEL;
				break;
			*/
			}break;
			case WM_DROPFILES:{
				event->drop.number = DragQueryFile((HDROP)msg.wParam,0xFFFFFFFF,0,0);
				event->event |= EX_EVENT_DROP;
			}break;
				// no event.
			default:
				event->event = 0;
				break;
		}// message switch
		// return success on handling messsages
		return TRUE;
	}
	return FALSE;
#elif defined(EX_LINUX)
	XEvent msg;
    if(XPending(display))
        XNextEvent(display,&msg);
	return TRUE;
#elif defined(EX_ANDROID)
#endif
}
