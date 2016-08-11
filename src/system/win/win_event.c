#include"system/elt_event.h"

#ifdef EX_WINDOWS
#	include"system/win/win_wndproc.h"
#	define WIN32_LEAN_AND_MEAN
#	include<windows.h>
#	include <winuser.h>
#	include<windowsx.h>
#	include<ws2dnet.h>
#endif

Int32 ExPollEvent(ExEvent* event){

	assert(event);
	MSG msg;
	if(PeekMessage(&msg,NULL,NULL,NULL,PM_REMOVE)){

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
				event->event |= EX_EVENT_KEY;
				event->key.code = (Uint8)msg.wParam;
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
				event->button.button = (Uint8)msg.wParam;
				event->event |= EX_EVENT_MOUSE;
			}
	/*		case WM_MOUSEWHEEL:{
				event->mouseWheelEvent.x = GET_X_LPARAM(msg.lParam);
				event->mouseWheelEvent.y = GET_X_LPARAM(msg.lParam);
				event->mouseWheelEvent.delta = GET_WHEEL_DELTA_WPARAM(msg.wParam);
				GET_KEYSTATE_WPARAM(msg.wParam);
				event->eventid |= EX_EVENT_MOUSEWHEEL;
			}*/
			break;
			case WM_DROPFILES:{
				event->drop.number = DragQueryFile((HDROP)msg.wParam,0xFFFFFFFF,0,0);
				event->event |= EX_EVENT_DROP;
				break;
			}
			switch(msg.lParam){ /*  network */
				case FD_ACCEPT:
					break;
				case FD_CONNECT:
					break;
				case FD_READ:
					break;
				case FD_CLOSE:
					break;
			}
			break;
			default:
				break;
		}

		return TRUE;
		}
	else
		return FALSE;
	/*
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
    */

}


Int32 ExPollWindowEvent(ExWin window, ExWindowEvent* event){

	MSG msg;
	//event->event = 0;
	// peek Message for given window handle.
	if(PeekMessage(&msg,window,NULL, NULL, PM_REMOVE)){
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
}
