#include"system/win/win_wndproc.h"

#include"system/win/win_win32.h"
#include<windows.h>
#include<winuser.h>
#include<commctrl.h>
#include<windowsx.h>
#include<dbt.h>

#ifdef EX_SCREENSAVER
	#include<scrnsave.h>
	#pragma comment(lib,"Scrnsave.lib")
#endif


ExCallBack ExOnFocus = NULL;
ExCallBack ExOnUnFocus = NULL;

void ELTAPIENTRY ExDisableAltTab(void){
	BOOL old;
	RegisterHotKey( 0, 0, MOD_ALT, VK_TAB );

	SystemParametersInfo( SPI_SCREENSAVERRUNNING, 1, &old, 0 );
}

void ELTAPIENTRY ExEnableAltTab(void){
	BOOL old;
	UnregisterHotKey( 0, 0 );

	SystemParametersInfo( SPI_SCREENSAVERRUNNING,0, &old, 0 );
}

GUID WceusbshGUID = { 0x25dbce51, 0x6c8f, 0x4a72,
                      0x8a,0x6d,0xb5,0x4c,0x2b,0x4f,0xc8,0x35 };


ExBoolean ELTAPIENTRY ExEnableDeviceNotification(ExWin hWnd){
	HDEVNOTIFY hDevNotify = 0;
	DEV_BROADCAST_DEVICEINTERFACE  notificationFilter = {0};

	notificationFilter.dbcc_devicetype  = DBT_DEVTYP_DEVICEINTERFACE;
	notificationFilter.dbcc_size = sizeof(DEV_BROADCAST_DEVICEINTERFACE);
	if(!(hDevNotify = RegisterDeviceNotification(hWnd, &notificationFilter,
		DEVICE_NOTIFY_WINDOW_HANDLE | DEVICE_NOTIFY_ALL_INTERFACE_CLASSES ))){			// Sending Message to This Window Handle!
		ExDevWindowPrintc(EX_TEXT("failed to register noticication"), EX_CONSOLE_RED);
	}

	notificationFilter.dbcc_devicetype  = DBT_DEVTYP_DEVICEINTERFACE;
	notificationFilter.dbcc_size = sizeof(DEV_BROADCAST_DEVICEINTERFACE);
	notificationFilter.dbcc_classguid = WceusbshGUID;
	if(!(hDevNotify = RegisterDeviceNotification(hWnd, &notificationFilter,
		DEVICE_NOTIFY_WINDOW_HANDLE ))){			// Sending Message to This Window Handle!
		ExDevWindowPrintc(EX_TEXT("failed to register noticication"), EX_CONSOLE_RED);
	}



	return (ExBoolean)((hDevNotify) ? TRUE : FALSE);
}

/*	Main Proc designed for OpenGL Window mainly.	*/
ERESULT WINAPI ExMainWndProc(ExWin hWnd,UINT uMsg, WPARAM wParam, LPARAM lParam){
	ExGLWindowHandler* handler;
	switch(uMsg){
	case WM_CREATE:{

		}break;
	case WM_QUIT:{
		CloseWindow(hWnd);
		DestroyWindow(hWnd);
		}break;
	case WM_ERASEBKGND:{

		}break;
	case WM_SIZE:{
			// get handler
			handler = (struct DesktopWindow*)GetWindowLongPtr(hWnd,GWLP_USERDATA);
			if(handler){
				if(handler->events.reshapeEvent)
					handler->events.reshapeEvent(EX_LOWORD(lParam), EX_HIWORD(lParam));
			}
			PostMessage(hWnd, WM_USER_SIZE, wParam,lParam);
		}break;
	case WM_PAINT:{
		}break;
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:{
			handler = (ExGLWindowHandler*)GetWindowLongPtr(hWnd,GWLP_USERDATA);
			Uint32 temp;
			if(wParam & MK_LBUTTON)
				temp |= 1;
			if(wParam & MK_RBUTTON)
				temp |= 2;
			if(wParam & MK_MBUTTON)
				temp |= 4;
			if(handler)
				if(handler->events.keyboardevent)
					handler->events.keyboardevent(temp);
		}break;
	case WM_INPUT:{
		PRAWINPUT pRawInput;
		UINT buffersize;
		HANDLE hHeap;
		GetRawInputData((HRAWINPUT)lParam,RID_INPUT,NULL, &buffersize, sizeof(RAWINPUTHEADER));
		hHeap = GetProcessHeap();
		pRawInput = (PRAWINPUT)HeapAlloc(hHeap,0, buffersize);
		if(!pRawInput)return 0;
		GetRawInputData((HRAWINPUT)lParam,RID_INPUT, pRawInput,&buffersize, sizeof(RAWINPUTHEADER));

		HeapFree(hHeap,0,pRawInput);
		}break;
	case WM_CONTEXTMENU:{
		handler = (ExGLWindowHandler*)GetWindowLongPtr(hWnd,GWLP_USERDATA);
		if(handler){
			if(!ExOnContextMenu2(hWnd,handler->events.contexthmenu,GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam))){

			}
		}
	}break;
	case WM_MENUCOMMAND:{
		// get data;
		MENUITEMINFO menuitemInfo = {sizeof(MENUITEMINFO)};
		menuitemInfo.fMask = MIIM_DATA;
		GetMenuItemInfo((HMENU)lParam,wParam, TRUE,&menuitemInfo);
		// event handler
		ExMenuEvent* menuEvent;
		if(menuEvent = (ExMenuEvent*)menuitemInfo.dwItemData)
			if(menuEvent->buttonPushed)
				menuEvent->buttonPushed();

	}break;
	case WM_SYSCOMMAND:
		if(wParam == SC_SCREENSAVE)
			return 0;// ignore screensaver call from system.
		break;
	case WM_POWER:{
		switch(lParam){
		case PWR_FAIL:
			break;
		case PWR_SUSPENDREQUEST:
			break;
		case PWR_SUSPENDRESUME :
			break;
		case PWR_CRITICALRESUME:
			break;
		}
	}break;
	case WM_SYSKEYDOWN:{//System Key Down
			if(wParam == VK_RETURN){
				//if(ExGeti(ENGINE_FULLSCREEN))
				//ExGLFullScreen(!(engineDescription.EngineFlag & ENGINE_FULLSCREEN) ,hWnd,0,0);
			}
		}break;
	case WM_DEVICECHANGE:{
		WCHAR strBuff[256];
			//temp
			//ExInitXController();
			switch(wParam){
			case DBT_DEVICEARRIVAL:
          //  msgCount++;
            sprintf(
                strBuff, 256,
                TEXT("Message %d: DBT_DEVICEARRIVAL\n"), 0);
            break;
        case DBT_DEVICEREMOVECOMPLETE:
        	sprintf(
                strBuff, 256,
                TEXT("Message %d: DBT_DEVICEREMOVECOMPLETE\n"), 0);
            break;
        case DBT_DEVNODES_CHANGED:
        	sprintf(
                strBuff, 256,
                TEXT("Message %d: DBT_DEVNODES_CHANGED\n"), 0);
            break;
        default:
        	sprintf(
                strBuff, 256,
                TEXT("Message %d: WM_DEVICECHANGE message received, value %d unhandled.\n"),
                0, wParam);
            break;
			}
			MessageBox(0,strBuff,EX_TEXT("ERROR"),MB_OK);
		}break;
	case WM_DEVMODECHANGE:{

		}break;
	case WM_DISPLAYCHANGE:{
			handler = (ExGLWindowHandler*)GetWindowLongPtr(hWnd,GWLP_USERDATA);
			if(handler){
				if(handler->events.reshapeEvent)
					handler->events.reshapeEvent(EX_LOWORD(lParam), EX_HIWORD(lParam));
			}
		}break;
	case WM_KEYDOWN:{
			handler = (ExGLWindowHandler*)GetWindowLongPtr(hWnd,GWLP_USERDATA);
			if(handler){
				if(handler->events.keyboardevent)
					handler->events.keyboardevent(LOWORD(wParam));
			}
		}break;
	case WM_SYSKEYUP:{

		}break;
	case WM_KEYUP:{

		}break;
	case WM_CHAR:{

		}break;
	case WM_KILLFOCUS:{
		if(ExOnUnFocus != NULL)
			ExOnUnFocus();
			// inform key state or something
		}break;
	case WM_SETFOCUS:{
		// assign data to input
		if(ExOnFocus != NULL)
			ExOnFocus();
		/*if(ExIsEngineState(ENGINE_SUPPORT_INPUT)){
			ExSetKeyBoardCooperative(hWnd, ExGetEngineFlag());
			ExSetMouseCooperative(hWnd, ExGetEngineFlag());
		}*/
		}break;
    case WM_NCHITTEST:
		if(FALSE){
			return HTCAPTION;   // allows dragging of the window
		}
		break;

	default:
		break;
	}
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}



ERESULT WINAPI ExWndProcNative(ExWin hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
	switch(uMsg){
	case WM_CREATE:
		return DefWindowProc(hWnd,uMsg,wParam,lParam);
	case WM_DESTROY:{

	}break;
	case WM_QUIT:{
		CloseWindow(hWnd);
		DestroyWindow(hWnd);
	}break;
	case WM_SIZE:{
		HWND hWndChild;
		PostMessage(hWnd, WM_USER_SIZE, wParam,lParam);
		// send message to all the children of resizing!
		for(hWndChild = GetTopWindow(hWnd); hWndChild != NULL; hWndChild = GetNextWindow(hWndChild, GW_HWNDNEXT)){
			SendMessage(hWndChild, uMsg, wParam, lParam);
		}
	}break;
	case WM_NCCREATE:{
		CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
		if(pCreate->lpCreateParams)
			SetWindowLongPtr(hWnd, GWLP_USERDATA,(LONG_PTR)pCreate->lpCreateParams);
	}break;
	case WM_PAINT:{
		 PAINTSTRUCT ps;
		 if(BeginPaint(hWnd,&ps)){

		 }
		 EndPaint(hWnd,&ps);
	}break;
	case WM_ERASEBKGND:{

	}break;
	case WM_INITMENUPOPUP:{

	}break;
	case CCM_SETWINDOWTHEME :break;
	case WM_NOTIFY:{
		switch(wParam){
		/*	status bar!	*/
		case NM_CLICK:{
			LPNMMOUSE lpnmmouse = (LPNMMOUSE)lParam;
			}break;
		case SBN_SIMPLEMODECHANGE:{
			NMHDR* lpnmh = (NMHDR*) lParam;
			SendMessage(lpnmh->hwndFrom,WM_SIZE,0,0);
		}break;
		}
		//NMHDR* h = (NMHDR*)lParam;
		//SendMessage(h->hwndFrom,h->code,0,0);
	}break;
	case WM_COMMAND:{
		switch(HIWORD(wParam)){
			// buttons
			case BN_CLICKED:{
				HWND bhwnd =(HWND)(lParam );
				ExButtonEvent* event = (ExButtonEvent*)GetWindowLongPtr(bhwnd, GWLP_USERDATA);
				if(event->buttonPushed != NULL)event->buttonPushed();
			}break;
			case BN_SETFOCUS:
			case BN_KILLFOCUS:
			case BN_DBLCLK:break;
			case LBN_DBLCLK:{

			}break;
				// selected change
			case LBN_SELCHANGE:{
				HWND bhwnd =(HWND)(lParam);
				Int index = SendMessage(bhwnd,LB_GETCURSEL,0,0);

				ExListBoxEvent* event = (ExListBoxEvent*)GetWindowLongPtr(bhwnd, GWLP_USERDATA);
				if(event->selected != NULL)event->selected();
			}break;
				// static clicked
			/*case STN_CLICKED:{
				HWND bhwnd =(HWND)(lParam);
				ExStaticControlEvent* event = (ExStaticControlEvent*)GetWindowLongPtr(bhwnd, GWLP_USERDATA);
				if(event->selected != NULL)event->selected();*/
			//}break;
			//case
			case EN_CHANGE :{
				ExTextInputEvent* event = (ExTextInputEvent*)GetWindowLongPtr((HWND)lParam,GWLP_USERDATA);
				if(event){
					if(event->textInput){
						//SendMessage((HWND)lParam,EM_GETLINE,0, sizeof(
						event->textInput(0);
					}
				}
			}break;
		}
	}break;
	case WM_MENUCOMMAND:{
		// get menu item data;
		MENUITEMINFO menuitemInfo = {sizeof(MENUITEMINFO)};
		menuitemInfo.fMask = MIIM_DATA;
		GetMenuItemInfo((HMENU)lParam,wParam, TRUE,&menuitemInfo);
		// event handler
		ExMenuEvent* menuEvent;
		if(menuEvent = (ExMenuEvent*)menuitemInfo.dwItemData)
			if(menuEvent->buttonPushed)
				menuEvent->buttonPushed();

	}break;
	case WM_CONTEXTMENU:{
		ExNativWindowHandler* handler = (ExNativWindowHandler*)GetWindowLongPtr(hWnd,GWLP_USERDATA);
		if(handler){
			if(!ExOnContextMenu2(hWnd,handler->events.contexthmenu,GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam))){

			}
		}
	}break;
	case WM_KEYDOWN:{
		ExNativWindowHandler* winhandler = (ExNativWindowHandler*)GetWindowLongPtr(hWnd,GWLP_USERDATA);
		if(winhandler){
			if(winhandler->events.keyboardevent)
				winhandler->events.keyboardevent(LOWORD(wParam));
		}
		}break;
	case WM_SYSKEYDOWN:{//System Key Down
			ExNativWindowHandler* winhandler = (ExNativWindowHandler*)GetWindowLongPtr(hWnd,GWLP_USERDATA);
			if(winhandler){
				if(winhandler->events.systemkeyevent)
					winhandler->events.systemkeyevent(wParam,lParam);
			}
		}break;
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:{
			Uint temp;
			if(wParam & MK_LBUTTON)
				temp |= 1;
			if(wParam & MK_RBUTTON)
				temp |= 2;
			if(wParam & MK_MBUTTON)
				temp |= 4;
			ExNativWindowHandler* winhandler = (ExNativWindowHandler*)GetWindowLongPtr(hWnd,GWLP_USERDATA);
			if(winhandler){
				if(winhandler->events.mousebutton)
					winhandler->events.mousebutton(wParam,lParam);
			}
	}break;
	/*
	case WM_INPUT_DEVICE_CHANGE:{
		RID_DEVICE_INFO info;
		info.cbSize = sizeof(info);
		switch(wParam){
		case GIDC_ARRIVAL:
			GetRawInputDeviceInfo((HANDLE)lParam,RIDI_DEVICEINFO,&info,0);
			break;
		case GIDC_REMOVAL:
			break;
		}
	}break;
	*/
	case WM_DEVICECHANGE:{
		WCHAR strBuff[256];
			//temp
			//ExInitXController();
			switch(wParam){
			case DBT_DEVICEARRIVAL:{
				DEV_BROADCAST_HDR*  hdr = (DEV_BROADCAST_HDR*)lParam;
				//if(hdr->dbch_devicetype == 5){
				//	DEV_BROADCAST_DEVICEINTERFACE* inf = (DEV_BROADCAST_DEVICEINTERFACE*)lParam;
				//	if(ExIsXInputDevice(&inf->dbcc_classguid))
				//		MessageBox(0, EX_TEXT("XBox Controller"),EX_TEXT("Message"), MB_OK);
				//}

          //  msgCount++;
				sprintf(
                strBuff, 256,
                TEXT("Message %d: DBT_DEVICEARRIVAL\n"), 0);
			}break;
        case DBT_DEVICEREMOVECOMPLETE:{
			DEV_BROADCAST_HDR*  hdr = (DEV_BROADCAST_HDR*)lParam;

			sprintf(
                strBuff, 256,
                TEXT("Message %d: DBT_DEVICEREMOVECOMPLETE\n"), 0);
			}break;
        case DBT_DEVNODES_CHANGED:
        	sprintf(
                strBuff, 256,
                TEXT("Message %d: DBT_DEVNODES_CHANGED\n"), 0);
            break;
        default:
        	sprintf(
                strBuff, 256,
                TEXT("Message %d: WM_DEVICECHANGE message received, value %d unhandled.\n"),
                0, wParam);
            break;
			}
			MessageBox(0,strBuff,EX_TEXT("ERROR"),MB_OK);
		}break;
	case WM_MOVE:{
		ExNativWindowHandler* winhandler = (ExNativWindowHandler*)GetWindowLongPtr(hWnd,GWLP_USERDATA);
		if(winhandler)
			if(winhandler->events.motionevent)
				winhandler->events.motionevent(EX_LOWORD(lParam),EX_HIWORD(lParam));
	}
	break;
	default:
		break;
	}
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
	//return CallWindowProc ((WNDPROC)GetWindowLong(hWnd,GWL_WNDPROC),hWnd, uMsg, wParam, lParam);
}


BOOL ExOnContextMenu(ExWin hWnd,Int x, Int y){
	RECT rc;                    // client area of window
    POINT pt = { x, y };        // location of mouse click

    // Get the bounding rectangle of the client area.

    GetClientRect(hWnd, &rc);

    // Convert the mouse position to client coordinates.

    ScreenToClient(hWnd, &pt);

    // If the position is in the client area, display a
    // shortcut menu.

    if (PtInRect(&rc, pt)) {
        ClientToScreen(hWnd, &pt);
        ExDisplayContextMenu(hWnd, &pt);
        return TRUE;
    }
    // Return FALSE if no menu is displayed.
    return FALSE;
}

ELTDECLSPEC BOOL WINAPI ExOnContextMenu2(ExWin hWnd, HMENU hmenuTrackPopup, Int x, Int y){
	if(!hmenuTrackPopup)return FALSE;
	RECT rc;                    // client area of window
    POINT pt = { x, y };        // location of mouse click
    // Get the bounding rectangle of the client area.
    GetClientRect(hWnd, &rc);
    // Convert the mouse position to client coordinates.
    ScreenToClient(hWnd, &pt);
    // If the position is in the client area, display a
    // shortcut menu.
    if (PtInRect(&rc, pt)) {
        ClientToScreen(hWnd, &pt);

		// Display the shortcut menu. Track the right mouse
		// button.
		TrackPopupMenu(hmenuTrackPopup,
				TPM_LEFTALIGN | TPM_RIGHTBUTTON,
				pt.x, pt.y, 0, hWnd, NULL);
		return TRUE;
    }
    // Return FALSE if no menu is displayed.
    return FALSE;
}

BOOL WINAPI ExDisplayContextMenu(ExWin hWnd, POINT* pt){
	HMENU hmenu;            // top-level menu
    HMENU hmenuTrackPopup;  // shortcut menu

    // Load the menu resource.

	hmenu = GetMenu(hWnd);
    // TrackPopupMenu cannot display the menu bar so get
    // a handle to the first shortcut menu.

    hmenuTrackPopup = GetSubMenu(hmenu, 0);

    // Display the shortcut menu. Track the right mouse
    // button.

    TrackPopupMenu(hmenuTrackPopup,
            TPM_LEFTALIGN | TPM_RIGHTBUTTON,
            pt->x, pt->y, 0, hWnd, NULL);
	return TRUE;
}

ExHandle ELTAPIENTRY ExHookWndProc(Int32  idHook, HOOKPROC lpfn){
	HHOOK hook;
	ExIsWinError(hook =SetWindowsHookEx(idHook,lpfn,GetModuleHandle(NULL),0));
	return hook;
}
