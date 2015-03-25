#include"uiCommand.h"
#include<Cmd/stringlib.h>

HANDLE uiConsoleThread = EX_NULL;
UI_COMMAND_DATA* uiConsoleData = EX_NULL;


Void ELTAPIENTRY ExSetConsoleSize(ExWin hWndParent,ExWin hWndConsole,Enum uiflag){
	RECT clientrect;
	ExGetWindowRect(hWndParent,(rect_t*)&clientrect);
	if (EXUI_VIEW_TOP & uiflag)
		SetWindowPos(hWndConsole,EX_NULL,0,0,(clientrect.right - clientrect.left),(clientrect.bottom - clientrect.top) * 0.35,SWP_SHOWWINDOW);
	if( EXUI_VIEW_BOTTOM & uiflag)
		SetWindowPos(hWndConsole,EX_NULL,0,0,(clientrect.right - clientrect.left),(clientrect.bottom - clientrect.top) * 0.35,SWP_SHOWWINDOW);
	if( EXUI_VIEW_LEFT & uiflag)
		SetWindowPos(hWndConsole,EX_NULL,0,0,(clientrect.right - clientrect.left),(clientrect.bottom - clientrect.top) * 0.35,SWP_SHOWWINDOW);
	if( EXUI_VIEW_RIGHT & uiflag)
		SetWindowPos(hWndConsole,EX_NULL,0,0,(clientrect.right - clientrect.left),(clientrect.bottom - clientrect.top) * 0.35,SWP_SHOWWINDOW);

}

DECLSPEC ExWin ELTAPIENTRY ExInitUICommand(ExWin hWndrender, ExWin hWndConsole,ExUICommandProc proc, Enum uiFlag){
	ExWin parenthwnd;
	RECT theRect;
	RECT rect;
	SIZE renderSIZE, consoleSize;
	if(!hWndConsole || !hWndrender)return FALSE;
	// set hwnd render window size

	GetClientRect(hWndrender,&rect);
	// create a parent window
	if(uiFlag & EXUI_CONSOLE_CHILD)
		parenthwnd = hWndrender;
	else{
		parenthwnd = ExCreateNativWindow(
			rect.left,rect.top,
			rect.right - rect.left,rect.bottom - rect.top);
		SetParent(hWndrender,parenthwnd);
	}
	// render hwnd parent 

	SetWindowLong(hWndrender,GWL_STYLE,GetWindowLong(hWndrender, GWL_STYLE) | WS_VISIBLE);

	SetParent(hWndConsole,parenthwnd);
	SetWindowLong(hWndConsole,GWL_STYLE,GetWindowLong(hWndConsole, GWL_STYLE) | WS_VISIBLE | WS_CHILD);

	// set size



	//FlushConsoleInputBuffer(GetStdHandle(STD_OUTPUT_HANDLE));

	// set position of console window

	//Coord fontSize = ExGetConsoleFontSize(0);
	//Coord coord = {(rect.right - rect.left) / (fontSize.X) + 4,fontSize.Y };
	//CONSOLE_SCREEN_BUFFER_INFO coninfo;
	//if(SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE),coord)){
	//	int failurehere = 0;
	//}
	ExSetConsoleSize(parenthwnd,hWndConsole,uiFlag);

	if(uiFlag & EXUI_TRANSPARENT){
		SetWindowLong(hWndConsole, GWL_EXSTYLE, GetWindowLong(hWndConsole, GWL_EXSTYLE) | WS_EX_TRANSPARENT | WS_EX_LAYERED);
		SetLayeredWindowAttributes(hWndConsole, RGB(0xF0,0xF0,0xf0), 128, LWA_COLORKEY | LWA_ALPHA );
	}

	//FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), ' ', coord.X * coord.Y,coord, 0);

	//SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), ENABLE_ECHO_INPUT | ENABLE_EXTENDED_FLAGS);
	uiConsoleData = (UI_COMMAND_DATA*)ExMalloc(SIZEOF(UI_COMMAND_DATA));
	// zero memory
	memset(uiConsoleData, 0, SIZEOF(UI_COMMAND_DATA));

	// use of internal command promt functionallity
	if(uiFlag & EXUI_INTERNAL_PROC){
		uiConsoleData->commandProc = (ExUICommandProc*)ExMalloc(SIZEOF(ExUICommandProc) * 2);
		ExHookUICommandProc(ExUICommandInternalProc);
		ExHookUICommandProc(proc);
		EX_MAKEHIDWORD(uiConsoleData->renderingFlag,2);
	}
	else{
		uiConsoleData->commandProc = (ExUICommandProc*)ExMalloc(SIZEOF(ExUICommandProc));
		ExHookUICommandProc(proc);
		EX_MAKEHIDWORD(uiConsoleData->renderingFlag,1);
	}
	// assign
	uiConsoleData->renderHwnd = hWndrender;
	uiConsoleData->hWndConsole = hWndConsole;
	uiConsoleData->renderingFlag |= uiFlag | EXUI_ENABLE;
	uiConsoleData->parentHwnd = parenthwnd;

	if(!uiConsoleThread)
		uiConsoleThread = CreateThread(EX_NULL, 128, (LPTHREAD_START_ROUTINE)ExUICommandThread,uiConsoleData,EX_NULL,EX_NULL);
	else
		return FALSE;
	ResumeThread(uiConsoleThread);

	ValidateRect(parenthwnd,&theRect);
	UpdateWindow(parenthwnd);

	return parenthwnd;
}

DECLSPEC Uint16 ELTAPIENTRY ExHookUICommandProc(ExUICommandProc commandProc){
	if(!commandProc)return 0;
	uiConsoleData->commandProc = (ExUICommandProc*)realloc(uiConsoleData->commandProc,(EX_HIWORD(uiConsoleData->renderingFlag) + 1) * sizeof(ExUICommandProc));
	int s = EX_HIWORD(uiConsoleData->renderingFlag);
	uiConsoleData->commandProc[EX_HIWORD(uiConsoleData->renderingFlag)] = commandProc;
	EX_MAKEHIDWORD(uiConsoleData->renderingFlag,EX_HIWORD(uiConsoleData->renderingFlag) + 1);
	return 1;
}
DECLSPEC Uint16 ELTAPIENTRY ExRemoveUICommandProc(ExUICommandProc commandProc){
	return 0;
}
DECLSPEC Uint16 ELTAPIENTRY ExRemoveUICommandProci(Uint32 index){
	uiConsoleData->commandProc[index] = EX_NULL;
	return 0;
}

DECLSPEC Uint32 ELTAPIENTRY ExReleaseUICommand(Void){
	if(uiConsoleThread){
		if(uiConsoleData){
			// free the children from command window
			SetParent(uiConsoleData->hWndConsole,0);
			SetParent(uiConsoleData->renderHwnd,0);

			// free information 
			free(uiConsoleData->message);
			free(uiConsoleData);

		}
		return TerminateThread(uiConsoleThread,0);
	}
	return 0;
}

DECLSPEC Boolean ELTAPIENTRY ExSetUIFlag(Enum renderingFlag){
	if(!uiConsoleData)return 0;
	
	if(renderingFlag & EXUI_DISABLE){
		ShowWindow(uiConsoleData->renderHwnd,SW_SHOWMAXIMIZED);
		ShowWindow(uiConsoleData->hWndConsole,SW_HIDE);
	}
	if(renderingFlag & EXUI_ENABLE){
		//ShowWindow(uiConsoleData->renderHwnd,SW_MAXIMIZE);
		ShowWindow(uiConsoleData->hWndConsole,SW_SHOW);
		SetActiveWindow(uiConsoleData->hWndConsole);
		SetFocus(uiConsoleData->hWndConsole);
	}


	uiConsoleData->renderingFlag ^= renderingFlag;
	return TRUE;
}
DECLSPEC Void ELTAPIENTRY ExSetUIRect(RECT* rect){
	SetWindowPos(uiConsoleData->hWndConsole,EX_NULL,
		rect->right - rect->left,0,
		0,0,
		SWP_SHOWWINDOW);
}
DECLSPEC Boolean ELTAPIENTRY ExUpdateUIWindow(Void){
	if(uiConsoleData == EX_NULL)return FALSE;
//RECT clientRect;
//GetClientRect(uiConsoleData->parentHwnd, &clientRect);
//if(uiConsoleData->renderingFlag & EXUI_VIEW_BOTTOM){
//	SetWindowPos(uiConsoleData->renderHwnd,
//		0,
//		0,
//		0,
//		clientRect.right - clientRect.left,
//		clientRect.bottom - clientRect.top - (clientRect.bottom - clientRect.top) / 6,
//		SWP_SHOWWINDOW);
//}
//
	return TRUE;
}

DECLSPEC Uint32 ELTAPISTDENTRY ExUICommandThread(LPVOID data){
	// data 
	//char message[1024];
	UiCommandData* uiData = (UiCommandData*)data;
	uiConsoleData = uiData;
	uiData->message = (char*)ExMalloc(1024);
	DWORD status = 1;
	do{
		if(!status)break;
		if(uiData->renderingFlag & EXUI_ROLLDOWN){
			if(uiData->renderingFlag & EXUI_VIEW_BOTTOM){}
		}
		gets(uiData->message);
		uiData->renderingFlag |= EXUI_MESSAGE;
		printf("\n");

	}while(GetExitCodeThread(uiConsoleThread,&status));
	free(uiData->message);
	return 1;
}

DECLSPEC Uint16 ELTAPIENTRY ExGetUIMessage(Void){
	// is there a uiConsoleThread
	if(!uiConsoleThread)return 0;
	if(uiConsoleData->renderingFlag & EXUI_MESSAGE){
		if(uiConsoleData->commandProc){
			// iterate through all function pointer
			for(Int32 x = 0; x < EX_HIWORD(uiConsoleData->renderingFlag); x++){
				uiConsoleData->commandProc[x](uiConsoleData->renderHwnd,uiConsoleData->message);
			}
		}
		// mark as readed
		uiConsoleData->renderingFlag = (~EXUI_MESSAGE & uiConsoleData->renderingFlag);
	}
	return 1;
}

DECLSPEC ERESULT ELTAPIENTRY ExUICommandInternalProc(ExWin hWnd, char* cCmd){
	char* tempCmd = cCmd;
	if(strstrsafe(cCmd, "exit",&tempCmd))exit(EXIT_SUCCESS);
	else if(strstr(cCmd,"help"))
		printf("help");
	else if(strstrsafe(tempCmd, "elt",&tempCmd)){
		/*if(strstrsafe(tempCmd, "version",tempCmd))
			printf("ELT version : %f\n",EX_ENGINEEXVERSION);
		else if(strstrsafe(tempCmd, "bulid",tempCmd))
			printf("");*/
	}
	else if(strstrsafe(cCmd, "compiler",&tempCmd)){
		if(strstrsafe(tempCmd, "version",&tempCmd))
			printf(EX_COMPILER_NAME);
		if(strstrsafe(tempCmd, "name",&tempCmd))
			printf(EX_COMPILER_NAME);
	}
	else if(strstr(cCmd,"memoryuse"))printf("");
	else if(strstrsafe(cCmd, "system",&tempCmd)){
		if(strstrsafe(cCmd, "totalmemory",&tempCmd))
			printf("System Total memory : %u MB\n",((ExGetTotalSystemMemory() / 1024)/1024));
	}
	else if(strstr(cCmd,""))printf("");
	else if(strstr(cCmd,""))printf("");

	return 1;
}