#include"system/win/win_win32.h"
#	include<windows.h>	// Window header
#	include<windowsx.h>
#	include <commctrl.h>
#	include<winuser.h>
#	include<uxtheme.h>
#	include<wininet.h>
#	include<dwmapi.h>	// DW
#	include<time.h>
#	include<signal.h>
#	include <io.h>
#	include <fcntl.h>

#	pragma comment(lib,"Dwmapi.lib")
#	pragma comment(lib, "winmm.lib")
#	pragma comment(lib,"User32.lib")
#	pragma comment(lib,"comctl32.lib")
#	pragma comment(lib,"UxTheme.lib")





void ELTAPIENTRY ExUnRegisterClasses(void){
	ExChar text[MAX_PATH];
	if(!FindWindowEx(0,0,EX_OPENGL_WINDOW_CLASS,0))
		if(UnregisterClass(EX_OPENGL_WINDOW_CLASS, GetModuleHandle(NULL)))
			wsprintf(text, EX_TEXT("failed to unregister class : %s"), EX_OPENGL_WINDOW_CLASS);

	if(!FindWindowEx(0,0,EX_NATIVE_WINDOW_CLASS,0))
		if(UnregisterClass(EX_NATIVE_WINDOW_CLASS, GetModuleHandle(NULL)))
			wsprintf(text, EX_TEXT("failed to unregister class : %s"), EX_NATIVE_WINDOW_CLASS);

	if(!FindWindowEx(0,0,EX_DIRECTX_WINDOW_CLASS,0))
		if(UnregisterClass(EX_DIRECTX_WINDOW_CLASS, GetModuleHandle(NULL)))
			wsprintf(text, EX_TEXT("failed to unregister class : %s"), EX_DIRECTX_WINDOW_CLASS);
}

ExWin ELTAPIENTRY ExCreateDirectXWindow(int x, int y, int width, int height){
	HWND hWnd;
	ExChar title[260];
	WNDCLASSEX wc = {0};
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = MainWndProc;
	wc.hInstance = GetModuleHandle(NULL);
	/*
	wc.hIcon = (HICON)LoadImage(GetModuleHandle(NULL),MAKEINTRESOURCE(IDI_ICON1),IMAGE_ICON,GetSystemMetrics(SM_CXICON),
		GetSystemMetrics(SM_CYICON),LR_DEFAULTCOLOR);
	wc.hIconSm = (HICON)LoadImage(GetModuleHandle(NULL),MAKEINTRESOURCE(IDI_ICON1),IMAGE_ICON,GetSystemMetrics(SM_CXSMICON),
		GetSystemMetrics(SM_CYSMICON),LR_DEFAULTCOLOR);
	*/
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = EX_DIRECTX_WINDOW_CLASS;
	if(!FindWindowEx(NULL, NULL, EX_DIRECTX_WINDOW_CLASS, NULL)){
		if(!RegisterClassEx(&wc)){
			if(GetLastError() != ERROR_CLASS_ALREADY_EXISTS)
				ExDevWindowPrintc(EX_TEXT("register directX class failed"), EX_CONSOLE_RED);
		}
	}
	hWnd = CreateWindowEx(WS_EX_APPWINDOW,EX_DIRECTX_WINDOW_CLASS,ExGetDefaultWindowTitle(title,sizeof(title) / sizeof(title[0])),
		(WS_OVERLAPPEDWINDOW ^WS_THICKFRAME ^ WS_MAXIMIZEBOX),x, y,
		 width,
		 height,
		NULL,
		NULL,
		wc.hInstance,
		NULL);
	SetForegroundWindow(hWnd); // check error
	return hWnd;
}

ExWin ELTAPIENTRY ExCreateOpenGLWindow(Int32 x, Int32 y, Int32 width, Int32 height){
	HWND hWnd;
	WNDCLASSEX wc;
	ATOM reg;
	ExChar title[260];
	wc.cbSize = sizeof(wc);
	wc.hInstance = GetModuleHandle(NULL);
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	/*
	wc.hIcon = (HICON)LoadImage(GetModuleHandle(NULL),MAKEINTRESOURCE(IDI_ICON1),IMAGE_ICON,GetSystemMetrics(SM_CXICON),
		GetSystemMetrics(SM_CYICON),LR_DEFAULTCOLOR);
	wc.hIconSm = (HICON)LoadImage(GetModuleHandle(NULL),MAKEINTRESOURCE(IDI_ICON1),IMAGE_ICON,GetSystemMetrics(SM_CXSMICON),
		GetSystemMetrics(SM_CYSMICON),LR_DEFAULTCOLOR);
	*/
	wc.lpfnWndProc = MainWndProc;
	wc.hbrBackground =  (HBRUSH) 0;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = EX_OPENGL_WINDOW_CLASS;
	if(!FindWindowEx(NULL,NULL,EX_OPENGL_WINDOW_CLASS,NULL)){
		if(!(reg =RegisterClassEx(&wc))){
			if(GetLastError() != ERROR_CLASS_ALREADY_EXISTS)
				ExDevWindowPrintc(EX_TEXT("register opengl class failed"), EX_CONSOLE_RED);
		}
	}
	if(!(hWnd = CreateWindowEx(WS_EX_APPWINDOW,EX_OPENGL_WINDOW_CLASS,ExGetDefaultWindowTitle(title,sizeof(title) / sizeof(title[0])),
		WS_OVERLAPPEDWINDOW,
		// MaximizeBox Disable
			x,
			y,
			width,
			height,
			NULL,
			NULL,
			wc.hInstance,
			NULL))){
		MessageBox(NULL, TEXT("Failed"), TEXT("ERROR"), MB_OK | MB_ICONERROR);
		ExDevWindowPrintc(EX_TEXT("Failed to Create OpenGL Windows"),EX_CONSOLE_RED);
		return NULL;
	}
	SetForegroundWindow(hWnd);
	UpdateWindow(hWnd);
	return hWnd;
}

ExWin ELTAPIENTRY ExCreateNativeWindow(Int32 x, Int32 y, Int32 width, Int32 height){

	ATOM reg;
	HWND hwnd;
	ExChar title[260];
	WNDCLASSEX wc = {0};
	wc.cbSize = sizeof(wc);
	wc.hInstance = GetModuleHandle(NULL);
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC ;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	/*
	wc.hIcon = (HICON)LoadImage(GetModuleHandle(NULL),MAKEINTRESOURCE(IDI_ICON1),IMAGE_ICON,GetSystemMetrics(SM_CXICON),
		GetSystemMetrics(SM_CYICON),LR_DEFAULTCOLOR);
	wc.hIconSm = (HICON)LoadImage(GetModuleHandle(NULL),MAKEINTRESOURCE(IDI_ICON1),IMAGE_ICON,GetSystemMetrics(SM_CXSMICON),
		GetSystemMetrics(SM_CYSMICON),LR_DEFAULTCOLOR);
	*/
	wc.lpfnWndProc = WndProcNative;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOWFRAME;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = EX_NATIVE_WINDOW_CLASS;


	// register window class
	if(!(reg = RegisterClassEx(&wc))){
		if(GetLastError() != ERROR_CLASS_ALREADY_EXISTS)
			MessageBoxW(NULL, TEXT("ERROR : Failed to Register"), EX_TEXT("ERROR"), MB_OK | MB_ICONWARNING);
	}
	// create Window
	if(!(hwnd = CreateWindowEx(WS_EX_APPWINDOW,EX_NATIVE_WINDOW_CLASS,ExGetDefaultWindowTitle(title,sizeof(title) / sizeof(title[0])),
		(WS_OVERLAPPEDWINDOW),x,y,width,height,NULL, NULL, wc.hInstance,NULL))){		// MaximizeBox Disable
		MessageBox(NULL, EX_TEXT("ERROR : Failed to Create Window"), TEXT("ERROR"), MB_OK | MB_ICONWARNING);
	}
	return hwnd;
}

ExWin ELTAPIENTRY ExCreateMIDWindow(Int32 x, Int32 y, Int32 width, Int32 height){

	WNDCLASSEX wc;
	ExWin hwnd;
	memset(&wc,0, sizeof(wc));
	wc.cbSize = sizeof(wc);
	wc.hInstance = GetModuleHandle(NULL);
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC ;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpszClassName = EX_TEXT("ExMIDWindow");
	wc.hbrBackground = NULL;
	wc.lpfnWndProc = MainWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.lpszMenuName = NULL;


	if(! RegisterClassEx(&wc)){

	}

	if(!(hwnd = CreateMDIWindow(EX_TEXT("ExMIDWindow"),EX_TEXT(""),WS_MAXIMIZE, x,y,width, height, GetDesktopWindow(),wc.hInstance, NULL))){
		wExDevPrintf(EX_TEXT("Failed to Create MID Window | %s"), ExGetErrorMessage(GetLastError()));
	}

	return hwnd;
}

ExWin ELTAPIENTRY ExReConstructWindow(ExWin hWnd){
	RECT rect;
	GetWindowRect(hWnd, &rect);
	DestroyWindow(hWnd);
	// copy the properties
	hWnd = ExCreateOpenGLWindow(
		rect.left,
		rect.top,
		(rect.right - rect.left),
		(rect.bottom - rect.top));
	return hWnd;
}

DWORD ELTAPIENTRY ExSetWindowProc(ExWin hwnd, WNDPROC procPointer){
	if(!hwnd)
		return -1;
	unsigned long _result = SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG)procPointer);
	return _result;
}

WNDPROC ELTAPIENTRY ExGetWindowProc(_IN_ ExWin hwnd){
	if(!hwnd)
		return 0;
	return (WNDPROC)GetWindowLongPtr(hwnd, GWLP_WNDPROC);
}

void ELTAPIENTRY ExSetWindowStyle(ExWin hwnd, Long style){
	SetWindowLongPtr(hwnd, GWL_STYLE, style);return;
}

void ELTAPIENTRY ExSetAddiWindowStyle(ExWin hWnd, Long lstyle){
	SetWindowLong(hWnd,GWL_STYLE,GetWindowLong(hWnd, GWL_STYLE) | lstyle);
}

Long ELTAPIENTRY ExGetWindowStyle(ExWin hwnd){
	return GetWindowLongPtr(hwnd, GWL_STYLE);
}

void ELTAPIENTRY ExSetWindowStyleEx(ExWin hwnd, Long ExStyle){
	SetWindowLongPtr(hwnd, GWL_EXSTYLE, ExStyle);return;
}

Long ELTAPIENTRY ExGetWindowStyleEx(ExWin hwnd){
	return GetWindowLongPtr(hwnd, GWL_EXSTYLE);
}


int ELTAPIENTRY ExGetWindowMessage(ExWin hWnd){
	MSG messageHandler;
	if(GetMessage(&messageHandler, hWnd, NULL, NULL)){
		TranslateMessage(&messageHandler);
		DispatchMessage(&messageHandler);
		return TRUE;
	}

	return FALSE;
}

int ELTAPIENTRY ExGetWindowPeekMessage(ExWin hwnd){
	MSG messageHandler;
	if(PeekMessage(&messageHandler,hwnd, 0,0,PM_REMOVE)){
		TranslateMessage(&messageHandler);
		DispatchMessage(&messageHandler);
		return TRUE;
	}

	return FALSE;
}

void ELTAPIENTRY ExRunWinMessageLoop(void){
	MSG messageHandler;

	while(GetMessage(&messageHandler, NULL, NULL, NULL)){
		TranslateMessage(&messageHandler);
		DispatchMessage(&messageHandler);
	}

}

void ELTAPIENTRY ExRunWinPeekMessage(void){
	MSG messageHandler;

	while(PeekMessage(&messageHandler,NULL, NULL,NULL,PM_REMOVE)){
		TranslateMessage(&messageHandler);
		DispatchMessage(&messageHandler);
	}

}


int ELTAPIENTRY ExMessageBox(ExWin window, const char* text, const char* title,  unsigned int flags ){
	return MessageBox(window,text,title,flags);
}




