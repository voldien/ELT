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
#ifndef _WIN_CONSTROLS_H_
#define _WIN_CONSTROLS_H_ 1
#include"./../../ExPreProcessor.h"
#include"win_win32.h"



#ifdef  __cplusplus	/* C++ Environment */
extern "C"{
#endif

#define ExSetWindowEvent ExSetControlEvent
#define ExGetWindowEvent ExGetControlEvent

#define ExSetWindowEventv ExSetControlEventv

typedef void(ELTAPIENTRY* ExButtonPushed)(void);
typedef void(ELTAPIENTRY* ExSelected)(void);
typedef void(ELTAPIENTRY* ExBoxItemSelected)(LONG_PTR handle);
typedef void(ELTAPIENTRY* ExProgressBar)(float value);
typedef void(ELTAPIENTRY* ExTextInput)(void* wparam);


typedef struct ex_menu_event{
	ExButtonPushed buttonPushed;
}ExMenuEvent;
typedef struct ex_list_box_Event{
	ExSelected selected;
}ExListBoxEvent;
typedef struct ex_list_view_event{
	ExSelected selected;
}ExListViewEvent;
typedef struct ex_button_event{
	ExButtonPushed buttonPushed;
}ExButtonEvent;
typedef struct ex_static_control_event{
	ExButtonPushed buttonPushed;
}ExStaticControlEvent;
typedef struct ex_progressbar_event{
	ExProgressBar progressbar;
}ExProgressbarEvent;
typedef struct ex_text_input_event{
	ExTextInput textInput;
}ExTextInputEvent;
/*
	//Assign the event control
*/
extern DECLSPEC void ELTAPIENTRY ExSetControlEvent(ExWin hWnd,const HANDLE eventHandle);
/*

*/
extern DECLSPEC void ELTAPIENTRY ExSetControlEventv(ExWin hWnd,const HANDLE eventHandle, Uint32 size);

/*	Get Control Event of the Window*/
extern DECLSPEC void* ELTAPIENTRY ExGetControlEvent(ExWin hWnd);
/*	Destroy Window */
extern DECLSPEC void ELTAPIENTRY ExDestroyControl(ExWin hwnd);

/* Set Menu Event Handle */
extern DECLSPEC void ELTAPIENTRY ExSetMenuEvent(ExWin hMenu, HANDLE eventHandle);

/* Get Menu Event Handle */
extern DECLSPEC void* ELTAPIENTRY ExGetMenuEvent(HMENU hMenu);
/*	Remove */
extern DECLSPEC void ELTAPIENTRY ExReleaseMenuEvent(HMENU hMenu);

/*
	// Menu
*/
/*	Set menu Item Event*/
extern DECLSPEC void ELTAPIENTRY SetMenuItemEvent(HMENU subMenu, Uint32 pos, HANDLE eventHandle);
/*	Get menu Item Event*/
extern DECLSPEC void* ELTAPIENTRY GetMenuItemEvent(HMENU subMenu, Uint32 pos);

extern DECLSPEC void ELTAPIENTRY ExRemoveMenuItemEvent(HMENU subMenu, Uint32 pos);

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

extern DECLSPEC ExBoolean ELTAPIENTRY ExCreateMenuSeparator(HMENU hMenu);

extern DECLSPEC void ELTAPIENTRY ExMenuItemID(HMENU item, Uint32 id);
/*
	// Status Bar
*/
/*	Create Status bar*/
extern DECLSPEC ExWin ELTAPIENTRY ExCreateStatusBar(ExWin parenthWnd);
/*	Set Status Bar Text	*/
extern DECLSPEC void ELTAPIENTRY ExSetStatusBarText(ExWin statusHwnd,const ExChar* string);
/* */
extern DECLSPEC void ELTAPIENTRY ExSetStatusBarTexti(ExWin statusHwnd,Int32 index,const ExChar* string);
/*	Set Status Bar Icon	*/
extern DECLSPEC void ELTAPIENTRY ExSetStatusBarIcon(ExWin statusHwnd,HICON icon);
/**/
extern DECLSPEC void ELTAPIENTRY ExSetStatusBarParts(ExWin statusHwnd,Int32 count);

/*
	// Button
*/
extern DECLSPEC ExWin ELTAPIENTRY ExCreateButton(ExWin parentHwnd,CallBack callback);

extern DECLSPEC ExWin ELTAPIENTRY ExCreateRadioButton(ExWin parentHwnd);


extern DECLSPEC ExWin ELTAPIENTRY ExCreateComboBox(ExWin parenthWnd);
extern DECLSPEC void ELTAPIENTRY ExAddComboxString(ExWin parenthWnd);

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
extern DECLSPEC ExBoolean ELTAPIENTRY ExAddToolBarTemplate(ExWin hWndToolbar, ExChar* text, Uint32 templates,ExButtonPushed buttoncallback);
extern DECLSPEC void ELTAPIENTRY ExAddToolBarButton(ExWin hWndToolbar,ExChar* text,HBITMAP bitmap,Uint32 templates,ExButtonPushed buttoncallback);
extern DECLSPEC void ELTAPIENTRY ExAddToolBarButtonT(ExWin hWndToolbar,ExChar* text);
extern DECLSPEC void ELTAPIENTRY ExAddToolBarButtonB(ExWin hWndToolbar,HBITMAP bitmap);

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

#ifdef  __cplusplus	/* C++ Environment */
}
#endif

#endif
