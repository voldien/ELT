/*
===========================================================================
Copyright (C) 2014 BroodCity Software, Inc. Voldemor2009@hotmail.com

*/
#ifndef WIN_CONSTROLS_H
#define WIN_CONSTROLS_H
#include"./../../ExPreProcessor.h"
#include"win_win32.h"
#ifdef EX_WINDOWS
	#include <commctrl.h>
	#pragma comment(lib, "comctl32.lib")
	#	pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#ifdef EX_CPP
extern "C"{
#endif

#define ExSetWindowEvent ExSetControlEvent
#define ExGetWindowEvent ExGetControlEvent

typedef Void(ELTAPIENTRY* ExButtonPushed)(Void);
typedef Void(ELTAPIENTRY* ExSelected)(Void);
typedef Void(ELTAPIENTRY* ExBoxItemSelected)(LONG_PTR handle);
typedef Void(ELTAPIENTRY* ExProgressBar)(Float value);
typedef Void(ELTAPIENTRY* ExTextInput)(Void* wparam);

/*	TODO make them into typedef of defintion to prevent syntax error*/
typedef struct ex_menu_event{
	ExButtonPushed buttonPushed;
}ExMenuEvent;	
typedef struct ex_list_box_Event{
	ExSelected selected;
}ExListBoxEvent;
typedef struct ex_list_view_event{
	ExSelected selected;
}ExListViewEvent;
struct ExButtonEvent{
	ExButtonPushed buttonPushed;
};
struct ExStaticControlEvent{
	ExButtonPushed buttonPushed;
};
struct ExProgressbarEvent{
	ExProgressBar progressbar;
};
struct ExTextInputEvent{
	ExTextInput textInput;
};
/*
	//Assign the event control
*/
extern DECLSPEC Void ELTAPIENTRY ExSetControlEvent(ExWin hWnd, Void* eventHandle);
/*	Get Control Event of the Window*/
extern DECLSPEC Void* ELTAPIENTRY ExGetControlEvent(ExWin hWnd);
/*	Destroy Window */
extern DECLSPEC Void ELTAPIENTRY ExDestroyControl(ExWin hwnd);

/* Set Menu Event Handle */
extern DECLSPEC Void ELTAPIENTRY ExSetMenuEvent(ExWin hMenu, Void* eventHandle);

/* Get Menu Event Handle */
extern DECLSPEC Void* ELTAPIENTRY ExGetMenuEvent(HMENU hMenu);
/*	Remove */
extern DECLSPEC Void ELTAPIENTRY ExReleaseMenuEvent(HMENU hMenu);

/*
	// Menu 
*/
/*	Set menu Item Event*/
extern DECLSPEC Void ELTAPIENTRY SetMenuItemEvent(HMENU subMenu, Uint32 pos, Void* eventHandle);
/*	Get menu Item Event*/
extern DECLSPEC Void* ELTAPIENTRY GetMenuItemEvent(HMENU subMenu, Uint32 pos);

extern DECLSPEC Void ELTAPIENTRY ExRemoveMenuItemEvent(HMENU subMenu, Uint32 pos);

/*	Create Main Menu */
extern DECLSPEC HMENU ELTAPIENTRY ExCreateMainMenu(ExWin hwnd);

#define ADDPOPUPMENU(hmenu, string) \
    HMENU hSubMenu = CreatePopupMenu(); \
    AppendMenu(hmenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, string);
#define ADDMENUITEM(hsubMenu, ID, string)\
	AppendMenu(hsubMenu,MF_STRING,ID, string); 


extern DECLSPEC HMENU ELTAPIENTRY ExCreatePopupMenu(HMENU hMenu,const ExChar* string);
extern DECLSPEC HMENU ELTAPIENTRY ExCreatePopupMenuB(HMENU hMenu,HBITMAP bitmap);

extern DECLSPEC HMENU ELTAPIENTRY ExCreatePopUpMenuItem2(HMENU hpopupMenu,const ExChar* string, CallBack callback);
extern DECLSPEC HMENU ELTAPIENTRY ExCreatePopUpMenuItem(HMENU hpopupMenu,const ExChar* string, Uint32 ID);
/**/
extern DECLSPEC HMENU ELTAPIENTRY ExCreateMenuItemB(HMENU hpopupMenu, HBITMAP bitmap,  CallBack callback);

extern DECLSPEC Boolean ELTAPIENTRY ExCreateMenuSeparator(HMENU hMenu);

extern DECLSPEC Void ELTAPIENTRY ExMenuItemID(HMENU item, Uint32 id);
/*
	// Status Bar
*/
/*	Create Status bar*/
extern DECLSPEC HWND ELTAPIENTRY ExCreateStatusBar(ExWin parenthWnd);
/*	Set Status Bar Text	*/
extern DECLSPEC Void ELTAPIENTRY ExSetStatusBarText(ExWin statusHwnd,const ExChar* string);
/* */
extern DECLSPEC Void ELTAPIENTRY ExSetStatusBarTexti(ExWin statusHwnd,Int32 index,const ExChar* string);
/*	Set Status Bar Icon	*/
extern DECLSPEC Void ELTAPIENTRY ExSetStatusBarIcon(ExWin statusHwnd,HICON icon); 
/**/
extern DECLSPEC Void ELTAPIENTRY ExSetStatusBarParts(ExWin statusHwnd,Int32 count);
/*
	// Button
*/
extern DECLSPEC ExWin ELTAPIENTRY ExCreateButton(ExWin parentHwnd,CallBack callback);

extern DECLSPEC ExWin ELTAPIENTRY ExCreateRadioButton(ExWin parentHwnd);


extern DECLSPEC ExWin ELTAPIENTRY ExCreateComboBox(ExWin parenthWnd);
extern DECLSPEC Void ELTAPIENTRY ExAddComboxString(ExWin parenthWnd);

/*
	// track bar
	// begin-value |----------[]--------| end-value
*/
extern DECLSPEC ExWin ELTAPIENTRY ExCreateTrackBar(ExWin parenthWnd,Uint32 imin, Uint32 imax, Uint32 iselected);

/*
	// progress bar
	// [|||||||||||---------------]
*/
extern DECLSPEC ExWin ELTAPIENTRY ExCreateProgressBar(ExWin parentWnd);

/*
	List View 
*/
/*	Create List View	*/
extern DECLSPEC ExWin ELTAPIENTRY ExCreateListView(ExWin parenthWnd);

extern DECLSPEC ExWin ELTAPIENTRY ExCreateHeader(ExWin parenthWnd, Int32 x, Int32 y, Int32 width, Int32 height);

/*
	// Toolbar
*/
/*	Create a toolBar	*/
extern DECLSPEC ExWin ELTAPIENTRY ExCreateToolBar(ExWin parenthWnd);
extern DECLSPEC Boolean ELTAPIENTRY ExAddToolBarTemplate(ExWin hWndToolbar, ExChar* text, Uint32 templates,ExButtonPushed buttoncallback);
extern DECLSPEC Void ELTAPIENTRY ExAddToolBarButton(ExWin hWndToolbar,ExChar* text,HBITMAP bitmap,Uint32 templates,ExButtonPushed buttoncallback);
extern DECLSPEC Void ELTAPIENTRY ExAddToolBarButtonT(ExWin hWndToolbar,ExChar* text);
extern DECLSPEC Void ELTAPIENTRY ExAddToolBarButtonB(ExWin hWndToolbar,HBITMAP bitmap);

/*
	// Tab bar
*/
extern DECLSPEC ExWin ELTAPIENTRY ExCreateTabControl(ExWin parenthWnd);
extern DECLSPEC ExWin ELTAPIENTRY ExCreateTab(ExWin tabhWnd);

/*
	List Box
*/

extern DECLSPEC ExWin ELTAPIENTRY ExCreateListBox(ExWin parentHwnd);

/*
	// Edit Control
*/

extern DECLSPEC ExWin ELTAPIENTRY ExCreateTextInput(ExWin parentHwnd);


/*
	// Static Control
*/
// Create Static Control window 
extern DECLSPEC ExWin ELTAPIENTRY ExCreateStaticControl(ExWin parenthWnd,CallBack callback);
// Set Static control window bitmap texture.
extern DECLSPEC ExWin ELTAPIENTRY ExSetStaticControlBitMap(ExWin staticControl, HBITMAP hBitMap);

/* 
	// Ex Create Property Sheet
*/
extern DECLSPEC ExWin ELTAPIENTRY ExCreatePropertySheet(ExWin parenthWnd);

#ifdef EX_CPP
}
#endif
#endif