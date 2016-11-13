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
#include"./../../elt_def.h"
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
extern ELTDECLSPEC void ELTAPIENTRY ExSetControlEvent(ExWin hWnd, const ExHandle eventHandle);
/*

*/
extern ELTDECLSPEC void ELTAPIENTRY ExSetControlEventv(ExWin hWnd, const ExHandle eventHandle, unsigned int size);

/*	Get Control Event of the Window*/
extern ELTDECLSPEC void* ELTAPIENTRY ExGetControlEvent(ExWin hWnd);
/*	Destroy Window */
extern ELTDECLSPEC void ELTAPIENTRY ExDestroyControl(ExWin hwnd);

/* Set Menu Event Handle */
extern ELTDECLSPEC void ELTAPIENTRY ExSetMenuEvent(ExWin hMenu, ExHandle eventHandle);

/* Get Menu Event Handle */
extern ELTDECLSPEC void* ELTAPIENTRY ExGetMenuEvent(HMENU hMenu);
/*	Remove */
extern ELTDECLSPEC void ELTAPIENTRY ExReleaseMenuEvent(HMENU hMenu);

/*
	// Menu
*/
/*	Set menu Item Event*/
extern ELTDECLSPEC void ELTAPIENTRY SetMenuItemEvent(HMENU subMenu, unsigned int pos, ExHandle eventHandle);
/*	Get menu Item Event*/
extern ELTDECLSPEC void* ELTAPIENTRY GetMenuItemEvent(HMENU subMenu, unsigned int pos);

extern ELTDECLSPEC void ELTAPIENTRY ExRemoveMenuItemEvent(HMENU subMenu, unsigned int pos);

/*	Create Main Menu */
extern ELTDECLSPEC HMENU ELTAPIENTRY ExCreateMainMenu(ExWin hwnd);

#define ADDPOPUPMENU(hmenu, string) \
    HMENU hSubMenu = CreatePopupMenu(); \
    AppendMenu(hmenu, MF_STRING | MF_POPUP, (unsigned int)hSubMenu, string);
#define ADDMENUITEM(hsubMenu, ID, string)\
	AppendMenu(hsubMenu,MF_STRING,ID, string);


extern ELTDECLSPEC HMENU ELTAPIENTRY ExCreatePopupMenu(HMENU hMenu, const ExChar* string);
extern ELTDECLSPEC HMENU ELTAPIENTRY ExCreatePopupMenuB(HMENU hMenu, HBITMAP bitmap);

extern ELTDECLSPEC HMENU ELTAPIENTRY ExCreatePopUpMenuItem2(HMENU hpopupMenu, const ExChar* string, ExCallBack callback);
extern ELTDECLSPEC HMENU ELTAPIENTRY ExCreatePopUpMenuItem(HMENU hpopupMenu, const ExChar* string, unsigned int ID);
/**/
extern ELTDECLSPEC HMENU ELTAPIENTRY ExCreateMenuItemB(HMENU hpopupMenu, HBITMAP bitmap,  ExCallBack callback);

extern ELTDECLSPEC ExBoolean ELTAPIENTRY ExCreateMenuSeparator(HMENU hMenu);

extern ELTDECLSPEC void ELTAPIENTRY ExMenuItemID(HMENU item, unsigned int id);
/*
	// Status Bar
*/
/*	Create Status bar*/
extern ELTDECLSPEC ExWin ELTAPIENTRY ExCreateStatusBar(ExWin parenthWnd);
/*	Set Status Bar Text	*/
extern ELTDECLSPEC void ELTAPIENTRY ExSetStatusBarText(ExWin statusHwnd,const ExChar* string);
/* */
extern ELTDECLSPEC void ELTAPIENTRY ExSetStatusBarTexti(ExWin statusHwnd,int index,const ExChar* string);
/*	Set Status Bar Icon	*/
extern ELTDECLSPEC void ELTAPIENTRY ExSetStatusBarIcon(ExWin statusHwnd,HICON icon);
/**/
extern ELTDECLSPEC void ELTAPIENTRY ExSetStatusBarParts(ExWin statusHwnd,int count);

/*
	// Button
*/
extern ELTDECLSPEC ExWin ELTAPIENTRY ExCreateButton(ExWin parentHwnd,ExCallBack callback);

extern ELTDECLSPEC ExWin ELTAPIENTRY ExCreateRadioButton(ExWin parentHwnd);


extern ELTDECLSPEC ExWin ELTAPIENTRY ExCreateComboBox(ExWin parenthWnd);
extern ELTDECLSPEC void ELTAPIENTRY ExAddComboxString(ExWin parenthWnd);

/*
	// track bar
	// begin-value |----------[]--------| end-value
*/
extern ELTDECLSPEC ExWin ELTAPIENTRY ExCreateTrackBar(ExWin parenthWnd,unsigned int imin, unsigned int imax, unsigned int iselected);

/*
	// progress bar
	// [|||||||||||---------------]
*/
extern ELTDECLSPEC ExWin ELTAPIENTRY ExCreateProgressBar(ExWin parentWnd);

/*
	List View
*/
/*	Create List View	*/
extern ELTDECLSPEC ExWin ELTAPIENTRY ExCreateListView(ExWin parenthWnd);

extern ELTDECLSPEC ExWin ELTAPIENTRY ExCreateHeader(ExWin parenthWnd, int x, int y, int width, int height);

/*
	// Toolbar
*/
/*	Create a toolBar	*/
extern ELTDECLSPEC ExWin ELTAPIENTRY ExCreateToolBar(ExWin parenthWnd);
extern ELTDECLSPEC ExBoolean ELTAPIENTRY ExAddToolBarTemplate(ExWin hWndToolbar, ExChar* text, unsigned int templates,ExButtonPushed buttoncallback);
extern ELTDECLSPEC void ELTAPIENTRY ExAddToolBarButton(ExWin hWndToolbar,ExChar* text,HBITMAP bitmap,unsigned int templates,ExButtonPushed buttoncallback);
extern ELTDECLSPEC void ELTAPIENTRY ExAddToolBarButtonT(ExWin hWndToolbar,ExChar* text);
extern ELTDECLSPEC void ELTAPIENTRY ExAddToolBarButtonB(ExWin hWndToolbar,HBITMAP bitmap);

/*
	// Tab bar
*/
extern ELTDECLSPEC ExWin ELTAPIENTRY ExCreateTabControl(ExWin parenthWnd);
extern ELTDECLSPEC ExWin ELTAPIENTRY ExCreateTab(ExWin tabhWnd);

/*
	List Box
*/

extern ELTDECLSPEC ExWin ELTAPIENTRY ExCreateListBox(ExWin parentHwnd);

/*
	// Edit Control
*/

extern ELTDECLSPEC ExWin ELTAPIENTRY ExCreateTextInput(ExWin parentHwnd);


/*
	// Static Control
*/
// Create Static Control window
extern ELTDECLSPEC ExWin ELTAPIENTRY ExCreateStaticControl(ExWin parenthWnd,ExCallBack callback);
// Set Static control window bitmap texture.
extern ELTDECLSPEC ExWin ELTAPIENTRY ExSetStaticControlBitMap(ExWin staticControl, HBITMAP hBitMap);

/*
	// Ex Create Property Sheet
*/
extern ELTDECLSPEC ExWin ELTAPIENTRY ExCreatePropertySheet(ExWin parenthWnd);

#ifdef  __cplusplus	/* C++ Environment */
}
#endif

#endif
