#include"system/elt_event.h"
#include"system/unix/unix_win.h"
#include"ExAssert.h"
#include"ExPreProcessor.h"
#ifdef EX_WINDOWS
#   include<WindowsX.h>
#elif defined(EX_LINUX)
#   include<X11/X.h>
#elif defined(EX_ANDROID)
#   include<errno.h>
#   include<android/window.h>
#   include<android/rect.h>
#   include<android/input.h>
#   include<android/looper.h>
#   include<android/sensor.h>
#endif



DECLSPEC Int32 ELTAPIENTRY ExPollEvent(ExEvent* event){

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
		switch(lParam){ /*  network */
            case FD_ACCEPT:break;
            case FD_CONNECT:break;
            case FD_READ:break;
            case FD_CLOSE:break;
		}
		default:break;
	}

	return TRUE;
#elif defined(EX_LINUX)
	if(XPending(display)){
		XNextEvent(display,&event->msg);

		switch(event->msg.type){
    case KeymapNotify:
            XRefreshKeyboardMapping(&event->msg.xmapping);
        break;
		case KeyPress:{
		    event->eventid |= EX_EVENT_KEY;
		    event->key.code = XLookupKeysym(&event->msg.xkey,0);//.keycode;
		    event->mouse.x = event->msg.xkey.x;
		    event->mouse.y = event->msg.xkey.y;
		    event->key.alt = event->msg.xkey.state & Mod1Mask;
		    event->key.ctrl = event->msg.xkey.state & ControlMask;
		    event->key.shift = event->msg.xkey.state & ShiftMask;
		    event->key.system = event->msg.xkey.state & Mod1Mask;
        }break;
		case KeyRelease:{
		    event->eventid |= EX_EVENT_KEY;
		    event->key.code = XLookupKeysym(&event->msg.xkey,0);//.keycode;
		    event->mouse.x = event->msg.xkey.x;
		    event->mouse.y = event->msg.xkey.y;
		}break;
		case ButtonPress:{
		    event->eventid |= EX_EVENT_MOUSE;
		    event->button.button = event->msg.xbutton.button;
		    event->mouse.x = event->msg.xkey.x;
		    event->mouse.y = event->msg.xkey.y;
        }break;
		case ButtonRelease:{
		    event->eventid |= EX_EVENT_MOUSE;
		    event->button.button = event->msg.xbutton.button;
		    event->mouse.x = event->msg.xkey.x;
		    event->mouse.y = event->msg.xkey.y;
		}break;
		case ResizeRequest:{
            event->eventid |= EX_EVENT_SIZE;
            event->size.width = event->msg.xresizerequest.width;
            event->size.height = event->msg.xresizerequest.height;
		}break;
		case Expose:{
            event->eventid |= EX_EVENT_SIZE;
            event->size.width = event->msg.xexpose.width;
            event->size.height = event->msg.xexpose.height;
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
	}else {/*XSync(display,0);*/ return FALSE;}
#elif defined(EX_ANDROID)
    int ident;
    int events;

    switch(ident = ALooper_pollAll(0, NULL,&events,&event->source)){


        default:break;
    }

    return TRUE;
#elif defined(EX_MAC)

#elif defined(EX_IPHONE)

#elif defined(EX_WEB)

#elif defined(EX_PS3)

#endif
}



DECLSPEC ExBoolean ELTAPIENTRY ExPollWindowEvent(ExWin hWnd, ExWindowEvent* event){
#ifdef EX_WINDOWS
	//event->event = 0;
	// peek Message for given window handle.
	if(PeekMessage(&event->msg,hWnd,EX_NULL, EX_NULL, PM_REMOVE)){
		DispatchMessage(&event->msg);
		TranslateMessage(&event->msg);

		switch(event->msg.message){
			case WM_SIZE:
			case WM_SIZING:
			case WM_USER_SIZE:{
				event->size.width = EX_LOWORD(event->msg.lParam);
				event->size.height = EX_HIWORD(event->msg.lParam);
				event->event = EX_EVENT_SIZE;
			}break;
			case WM_DEVICECHANGE:
				break;
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
				event->key.code = event->msg.wParam;
				event->event |= EX_EVENT_KEY;
				event->key.alt = !(event->msg.wParam ^ VK_MENU);
				event->key.shift = !(event->msg.wParam ^ VK_SHIFT);
				event->key.system = !(event->msg.wParam ^ VK_LWIN );
				event->key.ctrl  = !(event->msg.wParam ^ VK_CONTROL);
				break;
			case WM_KEYUP:
			case WM_SYSKEYUP:
				event->event = (~EX_EVENT_KEY & event->event);
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
				event->event = EX_EVENT_MOUSE;
				event->button.button = event->msg.wParam;
				event->event |= EX_EVENT_MOUSE;
			case WM_MOUSEHWHEEL:
			case WM_MOUSEWHEEL :
				event->mouseWheelEvent.x = GET_X_LPARAM(event->msg.lParam);
				event->mouseWheelEvent.y = GET_X_LPARAM(event->msg.lParam);
				event->mouseWheelEvent.delta = GET_WHEEL_DELTA_WPARAM(event->msg.wParam);
				GET_KEYSTATE_WPARAM(event->msg.wParam);
				event->event |= EX_EVENT_MOUSEWHEEL;
				break;
			}break;
			case WM_DROPFILES:{
				event->drop.number = DragQueryFile((HDROP)event->msg.wParam,0xFFFFFFFF,0,0);
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
    if(XPending(display))
        XNextEvent(display,&event->msg);
	return TRUE;
#elif defined(EX_ANDROID)
#endif
}
