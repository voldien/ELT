#include"system/win/win_controls.h"

#include<windows.h>
#include<uxtheme.h>
#include<winuser.h>

#include <commctrl.h>
#pragma comment(lib, "comctl32.lib")
#	pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

void ExSetControlEvent(ExWin hWnd, const ExHandle eventExHandle){
	if(!SetWindowLongPtr(hWnd,GWLP_USERDATA, (LONG_PTR)eventExHandle) && !(eventExHandle)){
		// Ex Control Event assignment failed.
		//ExDevWindowPrintc(EX_TEXT("Failed to Assign Control Event."),EX_CONSOLE_RED);
	}
}

void ExSetControlEventv(ExWin hWnd,const ExHandle eventHandle, unsigned int size){
	ExHandle datahandle = (ExHandle)malloc(size);
	memcpy(datahandle,eventHandle, size);
	if(!SetWindowLongPtr(hWnd,GWLP_USERDATA, (LONG_PTR)datahandle) && !(datahandle)){
		// Ex Control Event assignment failed.
		//ExDevWindowPrintc(EX_TEXT("Failed to Assign Control Event."),EX_CONSOLE_RED);
	}
}

void* ExGetControlEvent(ExWin hWnd){
	return (void*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
}

void ExSetMenuEvent(ExWin hMenu, ExHandle eventHandle){
	MENUINFO info;
	info.cbSize = sizeof(MENUINFO);
	info.fMask = MIM_MENUDATA;
	info.dwMenuData = (ULONG_PTR)eventHandle;
	if(!SetMenuInfo(hMenu,&info))
		ExDevWindowPrint(EX_TEXT("Failed to Set Menu Info"));
}

void* ExGetMenuEvent(HMENU hMenu){
	MENUINFO info;
	info.cbSize = sizeof(MENUINFO);
	info.fMask = MIM_MENUDATA;
	if(!GetMenuInfo(hMenu,&info))
		ExDevWindowPrint(EX_TEXT("Failed to Get Menu Info"));
	return (void*)info.dwMenuData;
}

void  ExReleaseMenuEvent(HMENU hMenu){
	MENUINFO info;
	info.cbSize = sizeof(MENUINFO);
	info.fMask = MIM_MENUDATA;
	// get menu info data.
	if(!GetMenuInfo(hMenu, &info))
		ExDevWindowPrintc(EX_TEXT("Failure"),EX_CONSOLE_RED);
	free((void*)info.dwMenuData);
}
/*	Set menu Item Event*/
void SetMenuItemEvent(HMENU subMenu, unsigned int pos, ExHandle eventHandle){
	MENUITEMINFO menuInfo;
	menuInfo.cbSize = sizeof(MENUINFO);
	menuInfo.fMask = MIIM_DATA;
	menuInfo.dwItemData = (ULONG_PTR)eventHandle;
	if(!SetMenuItemInfo(subMenu, pos, EX_TRUE,&menuInfo)){
		ExDevWindowPrintc(EX_TEXT("Failed Set Menu Item"),EX_CONSOLE_RED);//failed;
	}
	return;
}
/*	Get menu Item Event*/
void* GetMenuItemEvent(HMENU subMenu, unsigned int pos){
	MENUITEMINFO menuInfo;
	menuInfo.cbSize = sizeof(MENUINFO);
	menuInfo.fMask = MIIM_DATA;
	if(!GetMenuItemInfo(subMenu, pos, EX_TRUE, &menuInfo)){
		ExDevWindowPrintc(EX_TEXT("Failed Get Menu Item"),EX_CONSOLE_RED);//failed;
	}
	return (void*)menuInfo.dwItemData;
}

HMENU ExCreateMainMenu(ExWin hWnd){
	MENUINFO info;
	HMENU hMenu = CreateMenu();
	if(!SetMenu(hWnd, hMenu))
		ExDevWindowPrint(EX_TEXT(""));
	info.cbSize = sizeof(MENUINFO);
	info.fMask = MIM_STYLE;
	info.dwStyle = MNS_NOTIFYBYPOS;
	if(!SetMenuInfo(hMenu,&info)){
		ExDevWindowPrint(EX_TEXT("failed to set menu info"));
	}
	DrawMenuBar(hWnd);
	return hMenu;
}

// string
HMENU ExCreatePopupMenu(HMENU hMenu,const ExChar* string){
	MENUINFO info;
    HMENU hSubMenu = CreatePopupMenu();
    if(!AppendMenu(hMenu, MF_STRING | MF_POPUP, (unsigned int)hSubMenu, string))
		ExDevWindowPrintc(EX_TEXT("Create Popup Menu Error"),EX_CONSOLE_RED);
	info.cbSize = sizeof(MENUINFO);
	info.fMask = MIM_STYLE;
	info.dwStyle = MNS_NOTIFYBYPOS;
	if(!SetMenuInfo(hSubMenu,&info)){
		ExDevWindowPrint(EX_TEXT("failed to set menu info"));
	}
	return hSubMenu;
}
// bitmap
HMENU ExCreatePopupMenuB(HMENU hmenu,HBITMAP bitmap){
	HMENU hSubMenu = CreatePopupMenu();
	if(!AppendMenu(hmenu, MF_BITMAP | MF_POPUP, (unsigned int)hSubMenu, (LPCWSTR)bitmap))
		ExDevWindowPrint(EX_TEXT("Create Popup Menu Error"));
	return hSubMenu;
}


HMENU  ExCreatePopUpMenuItem2(HMENU hpopupMenu,const ExChar* string, ExCallBack callback){
	MENUITEMINFO menuInfo;
	ExMenuEvent* event;
	menuInfo.cbSize = sizeof(MENUITEMINFO);

	event = (ExMenuEvent*)malloc(sizeof(ExMenuEvent));
	event->buttonPushed = callback;

	menuInfo.fMask = MIIM_STRING | MIIM_STATE | MIIM_DATA;
	menuInfo.dwItemData = (ULONG_PTR)event;
	menuInfo.fState = MFS_ENABLED;
	menuInfo.dwTypeData = (LPTSTR)string;
	if(!InsertMenuItem(hpopupMenu,GetMenuItemCount(hpopupMenu),EX_TRUE,&menuInfo)){
		//ExDevWindowPrintf(EX_TEXT("fail to insert Menu"));
	}
	return hpopupMenu;
}
 HMENU ExCreatePopUpMenuItem(HMENU hpopupMenu,const ExChar* string,unsigned int ID){
	ADDMENUITEM(hpopupMenu, ID, string);
	return hpopupMenu;
}

HMENU ExCreateMenuItemB(HMENU hpopupMenu, HBITMAP bitmap,  ExCallBack callback){
	MENUITEMINFO menuInfo;
	ExMenuEvent* event;
	menuInfo.cbSize = sizeof(MENUITEMINFO);

	event = (ExMenuEvent*)malloc(sizeof(ExMenuEvent));
	event->buttonPushed = callback;

	menuInfo.fMask = MIIM_BITMAP | MIIM_STATE | MIIM_DATA;
	menuInfo.dwItemData = (ULONG_PTR)event;
	menuInfo.fState = MFS_ENABLED;
	menuInfo.hbmpItem = bitmap;
	if(!InsertMenuItem(hpopupMenu,GetMenuItemCount(hpopupMenu),EX_TRUE,&menuInfo)){
		//ExDevWindowPrintf(EX_TEXT("fail to insert Menu"));
	}
	return hpopupMenu;
}

ExBoolean  ExCreateMenuSeparator(HMENU hMenu){
	MENUITEMINFO menuInfo;
	menuInfo.cbSize = sizeof(MENUITEMINFO);
	menuInfo.fMask = MIIM_FTYPE;
	menuInfo.fType = MFT_SEPARATOR;
	if(!InsertMenuItem(hMenu, GetMenuItemCount(hMenu), EX_TRUE, &menuInfo)){
		// error
		return EX_FALSE;
	}
	return EX_TRUE;
}
//=========================================
//		Status Bar		 //
ExWin ExCreateStatusBar(ExWin parenthWnd){
	// create status window
	RECT client_rect;
	HWND hwnd;
	INITCOMMONCONTROLSEX common_controls;
	common_controls.dwSize = sizeof(INITCOMMONCONTROLSEX);
	common_controls.dwICC = ICC_BAR_CLASSES;
	InitCommonControlsEx(&common_controls);

	GetClientRect(parenthWnd, &client_rect);

	if(!(hwnd = CreateWindowEx(0, STATUSCLASSNAME, NULL,
        WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP,0,
		client_rect.bottom-client_rect.top-20,
         client_rect.right-client_rect.left,20,
        parenthWnd, NULL, GetModuleHandle(NULL), NULL)))
		ExDevWindowPrintc(EX_TEXT("Failed to create Status Window"), EX_CONSOLE_RED);	// error check
	return hwnd;
}

void ExSetStatusBarText(ExWin statusHwnd,const  ExChar* string){
	WPARAM wparam = 0;
	EX_MAKEHIWORD(wparam,SBT_NOBORDERS);
	EX_MAKELOWORD(wparam,0);
	SendMessage(statusHwnd,SB_SETTEXT,wparam,(LPARAM)string);
}

void ExSetStatusBarTexti(ExWin statusHwnd,int index,const  ExChar* string){
	WPARAM wparam = 0;
	EX_MAKEHIWORD(wparam, SBT_NOBORDERS);
	EX_MAKELOWORD(wparam, index);
	SendMessage(statusHwnd, SB_SETTEXT, wparam, (LPARAM)string);
}

void ExSetStatusBarIcon(ExWin statusHwnd,HICON icon){
	SendMessage(statusHwnd,SB_SETICON,0,(LPARAM)icon);
}

void ExSetStatusBarParts(ExWin statusHwnd,int count){
	RECT client;
	int status_parts[128];
	int i;
	GetClientRect(statusHwnd,&client);
	for(i = 0; i < count; i++){
		status_parts[i] = ((client.right - client.left) / count) * (i +1);
		continue;
	}
	SendMessage(statusHwnd, SB_SETPARTS,count, (LPARAM)&status_parts);
}

//=========================================
//		Button		 //
ExWin ExCreateButton(ExWin parentHwnd, ExCallBack callback){
	HWND hwndButton;
	ExButtonEvent*  event = (ExButtonEvent*)malloc(sizeof(ExButtonEvent));
	memset(event, 0, sizeof(ExButtonEvent));
	event->buttonPushed = callback;
	hwndButton = CreateWindow(
    EX_TEXT("BUTTON"),  // Predefined class; Unicode assumed
    EX_TEXT(""),      // Button text
    WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON ,  // Styles
    20,					// x position
    20,					// y position
    100,				// Button width
    100,				// Button height
    parentHwnd,			// Parent window
    NULL,					// No menu.
    (HINSTANCE)GetWindowLong(parentHwnd, GWLP_HINSTANCE),
    0);			// Pointer not needed.
	SetWindowLongPtr(hwndButton, GWLP_USERDATA, (LONG_PTR)event);
	return hwndButton;
}

ExWin ExCreateComboBox(ExWin hWnd){
	HWND hWndCombo = CreateWindow(WC_COMBOBOX,EX_TEXT(""),
		CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED |  WS_VISIBLE | ES_NOHIDESEL,
		0,
		0,
		100,
		100,
		hWnd,
		NULL,
		GetModuleHandle(NULL),
		0);

	return hWndCombo;
}

ExWin ExCreateTrackBar(ExWin parenthWnd,unsigned int imin, unsigned int imax, unsigned int iselected){
	HWND  hwndTrack;
	InitCommonControls(); // loads common control's DLL
    hwndTrack = CreateWindowEx(
        0,                               // no extended styles
        TRACKBAR_CLASS,                  // class name
        EX_TEXT("Trackbar Control"),              // title (caption)
        WS_CHILD |
        WS_VISIBLE |
        TBS_AUTOTICKS |
        TBS_ENABLESELRANGE,              // style
        10, 10,                          // position
        200, 30,                         // size
        parenthWnd,                         // parent window
        0,								// control identifier
		GetModuleHandle(NULL),                         // instance
        NULL                             // no WM_CREATE parameter
        );

    SendMessage(hwndTrack, TBM_SETRANGE,
        (WPARAM) EX_TRUE,                   // redraw flag
        (LPARAM) MAKELONG(imin, imax));  // min. & max. positions

    SendMessage(hwndTrack, TBM_SETPAGESIZE,
        0, (LPARAM) 4);                  // new page size

/*    SendMessage(hwndTrack, TBM_SETSEL,
        (WPARAM) EX_FALSE,                  // redraw flag
        (LPARAM) MAKELONG(iSelMin, iSelMax)); */

    SendMessage(hwndTrack, TBM_SETPOS,
        (WPARAM) EX_TRUE,                   // redraw flag
        (LPARAM) iselected);

    SetFocus(hwndTrack);

    return hwndTrack;
}

ExWin ExCreateProgressBar(ExWin parentWnd){
	RECT rcClient;		// client area of the parent window
	ExWin hwndPB;		// progress bar window handle
	int cyVscroll;		// height of scroll bar arrow
	// initilize common controls
	InitCommonControls();

	GetClientRect(parentWnd, &rcClient);

	cyVscroll = GetSystemMetrics(SM_CYVSCROLL);

	hwndPB = CreateWindowEx(0,
		PROGRESS_CLASS, NULL,
		WS_CHILD | WS_VISIBLE,
		rcClient.left,
		rcClient.bottom - cyVscroll,
		rcClient.right,cyVscroll,
		parentWnd, NULL, GetModuleHandle(NULL),NULL);

	return hwndPB;
}

ExWin ExCreateListView(ExWin parenthWnd){
	INITCOMMONCONTROLSEX icex;           // Structure for control initialization.
	RECT rcClient;           // The parent window's client area.
    icex.dwICC = ICC_LISTVIEW_CLASSES;
    InitCommonControlsEx(&icex);

    GetClientRect (parenthWnd, &rcClient);

    // Create the list-view window in report view with label editing enabled.
    ExWin hWndListView = CreateWindow(WC_LISTVIEW,
                                     EX_TEXT(""),
                                     WS_CHILD | LVS_REPORT | LVS_EDITLABELS,
                                     0, 0,
                                     rcClient.right - rcClient.left,
                                     rcClient.bottom - rcClient.top,
                                     parenthWnd,
                                     NULL,
									 GetModuleHandle(NULL),
                                     NULL);
	HRESULT ok = SetWindowTheme(hWndListView, EX_TEXT("Explorer"), NULL);


	HICON hiconItem;     // Icon for list-view items.
	HIMAGELIST hLarge;   // Image list for icon view.
	HIMAGELIST hSmall;   // Image list for other views.

    // Create the full-sized icon image lists.
    hLarge = ImageList_Create(GetSystemMetrics(SM_CXICON),
                              GetSystemMetrics(SM_CYICON),
                              ILC_MASK, 1, 1);

    hSmall = ImageList_Create(GetSystemMetrics(SM_CXSMICON),
                              GetSystemMetrics(SM_CYSMICON),
                              ILC_MASK, 1, 1);

    // Add an icon to each image list.
    /*
	hiconItem = (HICON)LoadImage(GetModuleHandle(NULL),MAKEINTRESOURCE(IDI_ICON1),IMAGE_ICON,GetSystemMetrics(SM_CXICON),
		GetSystemMetrics(SM_CYICON),LR_DEFAULTCOLOR);
	*/
    ImageList_AddIcon(hLarge, hiconItem);
    ImageList_AddIcon(hSmall, hiconItem);

    DestroyIcon(hiconItem);

// When you are dealing with multiple icons, you can use the previous four lines of
// code inside a loop. The following code shows such a loop. The
// icons are defined in the application's header file as resources, which
// are numbered consecutively starting with IDS_FIRSTICON. The number of
// icons is defined in the header file as C_ICONS.

    // Assign the image lists to the list-view control.
    ListView_SetImageList(hWndListView, hLarge, LVSIL_NORMAL);
    ListView_SetImageList(hWndListView, hSmall, LVSIL_SMALL);

	ExChar szText[256] = {EX_TEXT("what wrong with this")};     // Temporary buffer.
    LVCOLUMN lvc;
    int iCol;
    int index;

    // Initialize the LVCOLUMN structure.
    // The mask specifies that the format, width, text,
    // and subitem members of the structure are valid.
    lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

    // Add the columns.
    for (iCol = 0; iCol < 2; iCol++)
    {
        lvc.iSubItem = iCol;
        lvc.pszText = szText;
        lvc.cx = 100;               // Width of column in pixels.

        if ( iCol < 2 )
            lvc.fmt = LVCFMT_LEFT;  // Left-aligned column.
        else
            lvc.fmt = LVCFMT_RIGHT; // Right-aligned column.

        // Insert the columns into the list view.
        if (ListView_InsertColumn(hWndListView, iCol, &lvc) == -1)
            return EX_FALSE;
    }

 LVITEM lvI;

    // Initialize LVITEM members that are common to all items.
    lvI.pszText   = EX_TEXT("Niga text"); // Sends an LVN_GETDISPINFO message.
    lvI.mask      = LVIF_TEXT | /*LVIF_IMAGE |*/LVIF_STATE;
    lvI.stateMask = 0;
    lvI.iSubItem  = 0;
    lvI.state     = LVIS_SELECTED;

    // Initialize LVITEM members that are different for each item.
    for (index = 0; index < 2; index++)
    {
        lvI.iItem  = index;
        lvI.iImage = index;

        // Insert items into the list.
        if (ListView_InsertItem(hWndListView, &lvI) == -1)
            return EX_FALSE;
    }

	SIZE size = { 100, 50 };
    LVTILEVIEWINFO tileViewInfo = {0};

    tileViewInfo.cbSize   = sizeof(tileViewInfo);
    tileViewInfo.dwFlags  = LVTVIF_FIXEDSIZE;
    tileViewInfo.dwMask   = LVTVIM_COLUMNS | LVTVIM_TILESIZE;
    tileViewInfo.cLines   = 2;
    tileViewInfo.sizeTile = size;

    ListView_SetTileViewInfo(hWndListView, &tileViewInfo);

	ExListViewEvent* listviewEvent = (ExListViewEvent*)malloc(sizeof(ExListViewEvent));
	ExSetControlEvent(hWndListView, listviewEvent);
	return hWndListView;
}

ExWin ExCreateHeader(ExWin hwndParent, int x, int y, int width, int height){
	HDLAYOUT hdl;
	WINDOWPOS wp;
	RECT rcParent;
	// the header control.
	INITCOMMONCONTROLSEX icex;  //declare an INITCOMMONCONTROLSEX Structure
	icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
	icex.dwICC = ICC_LISTVIEW_CLASSES;   //set dwICC member to ICC_LISTVIEW_CLASSES
												// this loads list-view and header control classes.
	InitCommonControlsEx(&icex);

	HWND hWndheader = CreateWindowEx(0, WC_HEADER, (LPCTSTR) NULL,
				WS_CHILD | WS_BORDER | HDS_BUTTONS | HDS_HORZ,
				0, 0, 0, 0, hwndParent, 0, GetModuleHandle(NULL),
				(LPVOID) NULL);


	GetClientRect(hwndParent, &rcParent);

	hdl.prc = &rcParent;
	hdl.pwpos = &wp;
	if (!SendMessage(hWndheader, HDM_LAYOUT, 0, (LPARAM) &hdl))
		return (HWND) NULL;

	SetWindowPos(hWndheader, wp.hwndInsertAfter, wp.x, wp.y,
			wp.cx, wp.cy,wp.flags |  SWP_SHOWWINDOW);
	return hWndheader;
}


ExWin ExCreateToolBar(ExWin parenthWnd){
    const int ImageListID    = 0;
    const int numButtons     = 3;
    const int bitmapSize     = 16;
	INITCOMMONCONTROLSEX icex = {0};
    HIMAGELIST g_hImageList;
	HWND hWndToolbar;
    const DWORD buttonStyles = BTNS_AUTOSIZE;

	icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
	icex.dwICC = ICC_BAR_CLASSES;
	InitCommonControlsEx(&icex);

    // Create the toolbar.
    if(!(hWndToolbar = CreateWindowEx(0, TOOLBARCLASSNAME, NULL,
                                      WS_CHILD | TBSTYLE_WRAPABLE | TBSTYLE_LIST | TBSTYLE_FLAT, 0, 0, 0, 0,
                                      parenthWnd, NULL, GetModuleHandle(NULL), NULL)))
        return NULL;

    // Create the image list.
   g_hImageList = ImageList_Create(bitmapSize, bitmapSize,   // Dimensions of individual bitmaps.
                                    ILC_COLOR16 | ILC_MASK,   // Ensures transparent background.
                                    numButtons, 16);
    // Set the image list.
    SendMessage(hWndToolbar, TB_SETIMAGELIST,
                (WPARAM)ImageListID,
                (LPARAM)g_hImageList);

    // Load the button images.
    SendMessage(hWndToolbar, TB_LOADIMAGES,
                (WPARAM)IDB_STD_SMALL_COLOR,
                (LPARAM)HINST_COMMCTRL);

    // Initialize button info.
    // IDM_NEW, IDM_OPEN, and IDM_SAVE are application-defined command constants.

   //TBBUTTON tbButtons[numButtons] =
   //{
   //    { MAKELONG(STD_FILENEW,  ImageListID), 0,  TBSTATE_ENABLED, buttonStyles, {0}, 0, (INT_PTR)L"New" },
   //    { MAKELONG(STD_FILEOPEN, ImageListID), 1, TBSTATE_ENABLED, buttonStyles, {0}, 0, (INT_PTR)L"Open"},
   //    { MAKELONG(STD_FILESAVE, ImageListID), 2, TBSTATE_ENABLED, buttonStyles, {0}, 0, (INT_PTR)L"Save"}
   //};

    // Add buttons.
    SendMessage(hWndToolbar, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);
    //SendMessage(hWndToolbar, TB_ADDBUTTONS,       (WPARAM)numButtons,       (LPARAM)&tbButtons);


    // Resize the toolbar, and then show it.
    SendMessage(hWndToolbar, TB_AUTOSIZE, 0, 0);
    ShowWindow(hWndToolbar,  EX_TRUE);

    return hWndToolbar;
}

ExBoolean ExAddToolBarTemplate(ExWin hWndToolbar, ExChar* text, unsigned int templates,ExButtonPushed buttoncallback){

    const int ImageListID    = 0;
    const int numButtons     = 1;
	HIMAGELIST g_hImageList;

    g_hImageList = (HIMAGELIST)SendMessage(hWndToolbar, TB_GETIMAGELIST,0,0);
    TBBUTTON tbButtons =  { MAKELONG(templates,  ImageListID), 0,  TBSTATE_ENABLED, BTNS_AUTOSIZE, {0}, 0, (INT_PTR)text };
    SendMessage(hWndToolbar, TB_ADDBUTTONS,       (WPARAM)numButtons,       (LPARAM)&tbButtons);
	return EX_TRUE;
}

void ExAddToolBarButton(ExWin hWndToolbar,ExChar* text,HBITMAP bitmap,unsigned int templates,ExButtonPushed buttoncallback){
    const int ImageListID    = 0;
    const int numButtons     = 1;
	HIMAGELIST g_hImageList;

    g_hImageList = (HIMAGELIST)SendMessage(hWndToolbar, TB_GETIMAGELIST,0,0);

	TBBUTTON button[] = {MAKELONG(STD_PROPERTIES,  ImageListID), 0,  TBSTATE_ENABLED, BTNS_AUTOSIZE, {0}, 0, (INT_PTR)EX_TEXT("New")};
	button->dwData = (DWORD_PTR)buttoncallback;
	SendMessage(hWndToolbar, TB_ADDBUTTONS,(WPARAM)1, (LPARAM)&button);

    ShowWindow(hWndToolbar,  EX_TRUE);
}

void ExAddToolBarButtonB(ExWin hWndToolbar,HBITMAP bitmap){
    int ImageListID    = 0;
    const int numButtons     = 1;
	HIMAGELIST g_hImageList;

    g_hImageList = (HIMAGELIST)SendMessage(hWndToolbar, TB_GETIMAGELIST,0,0);

	ImageListID = ImageList_Add(g_hImageList,bitmap,NULL);


	TBBUTTON button[] = {MAKELONG(STD_PROPERTIES,  ImageListID), 0,  TBSTATE_ENABLED, BTNS_AUTOSIZE, {0}, 0, (INT_PTR)0};
	SendMessage(hWndToolbar, TB_ADDBUTTONS,(WPARAM)1, (LPARAM)&button);

    ShowWindow(hWndToolbar,  EX_TRUE);
}

/*
	// tabcontrol
*/
ExWin ExCreateTabControl(ExWin parenthWnd){
	RECT rcClient;
	INITCOMMONCONTROLSEX icex;
	HWND hWndTab;
	TCITEM tie;
	ExChar* achTemp;
	int i;

	// initialize common controls
	icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
	icex.dwICC = ICC_TAB_CLASSES;
	InitCommonControlsEx(&icex);

	// Get the dimension of the parent window's client area.
	GetClientRect(parenthWnd,&rcClient);
	hWndTab = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW,
		WC_TABCONTROL,EX_TEXT(""),
		WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE,
		0,0,rcClient.right, rcClient.bottom,
		parenthWnd,NULL, GetModuleHandle(NULL),NULL);

// Add tabs for each day of the week.
    tie.mask = TCIF_TEXT | TCIF_IMAGE;
    tie.iImage = -1;
    tie.pszText =  EX_TEXT("random text");

    for (i = 0; i < 7; i++) {
		achTemp = EX_TEXT("random text");
        if (TabCtrl_InsertItem(hWndTab, i, &tie) == -1)
        {
            DestroyWindow(hWndTab);
            return NULL;
        }
    }
	return hWndTab;
}

ExWin ExCreateTab(ExWin tabhWnd){
/*    if (TabCtrl_InsertItem(hWndTab, i, &tie) == -1)

	}*/
	return 0;
}

ExWin ExCreateListBox(ExWin parentHwnd){
	ExListBoxEvent* listbox = (ExListBoxEvent*)malloc(sizeof(ExListBoxEvent));
	memset(listbox,0,sizeof(ExListBoxEvent));
	HWND hWndList = CreateWindowEx(WS_EX_CLIENTEDGE,
		EX_TEXT("listbox"),
		EX_TEXT(""),
		WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_AUTOVSCROLL | LBS_NOTIFY,
		240,
		40,
		150,
		100,
		parentHwnd,
		0,
		GetModuleHandle(NULL),
		NULL);
	ExSetControlEvent(hWndList,listbox);
	return hWndList;
}

ExWin ExCreateTextInput(ExWin parentHwnd){
	// create text input window.
	HWND hwnd;
	if(!(hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, EX_TEXT("edit"), EX_TEXT(""),
                              WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_LEFT,
                              CW_USEDEFAULT, CW_USEDEFAULT, 200, 24,	// x, y, w, h
                              parentHwnd,
							  NULL,
							  GetModuleHandle(NULL),
							  NULL))){
		ExDevWindowPrintc(EX_TEXT("Failed to Create TextInput"), EX_CONSOLE_RED);
	}
	 if(EX_TRUE){
		 ExTextInputEvent* event = (ExTextInputEvent*)malloc(sizeof(ExTextInputEvent));
		 ExSetControlEvent(hwnd,event);
	 }
	 return hwnd;
}

ExWin ExCreateStaticControl(ExWin parentHwnd, ExCallBack callback){

	HWND hWndstatic = CreateWindowEx(WS_EX_CLIENTEDGE,
		EX_TEXT("STATIC"),
		EX_TEXT(""),
		WS_CHILD | WS_VISIBLE | SS_NOTIFY | SS_BITMAP,
		0,
		0,
		256,
		256,
		parentHwnd,
		0,
		GetModuleHandle(NULL),
		NULL);
	if(callback){
		ExStaticControlEvent* staticControl = (ExStaticControlEvent*)malloc(sizeof(ExStaticControlEvent));
		memset(staticControl,0,sizeof(ExStaticControlEvent));
		staticControl->buttonPushed = callback;
		ExSetControlEvent(hWndstatic,staticControl);
	}
	return hWndstatic;
}

ExWin ExSetStaticControlBitMap(ExWin staticControl, HBITMAP hBitMap){

	// assign the texture
	SendMessage(staticControl,STM_SETIMAGE,IMAGE_BITMAP,(WPARAM)hBitMap);
	// set window woth a bitmap
	ExSetAddiWindowStyle(staticControl,SS_BITMAP | SS_REALSIZEIMAGE | SS_CENTERIMAGE );
	return staticControl;
}
