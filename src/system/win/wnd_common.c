#include"system/win/wnd_common.h"
#include<windows.h>
#include<wininet.h>
#include<string.h>


 int  ExCreateProcess(const ExChar* applicationName){
	PROCESS_INFORMATION pi = {0};
	STARTUPINFO si = {0};
    si.cb = sizeof(si);
	if( !CreateProcess(
        applicationName,    // No module name (use command line)
        EX_TEXT(""),        // Command line
        NULL,               // Process handle not inheritable
        NULL,               // Thread handle not inheritable
        FALSE,              // Set handle inheritance to FALSE
        CREATE_NEW_PROCESS_GROUP,              // No creation flags
        NULL,               // Use parent's environment block
        NULL,               // Use parent's starting directory
        &si,                // Pointer to STARTUPINFO structure
        &pi )               // Pointer to PROCESS_INFORMATION structure
    ) {
		ExDevWindowPrint(EX_TEXT("CreateProcess failed (%d).\n"));
		return FALSE;
    }
	return TRUE;

}

 int  ExCreateProcessl(const ExChar* applicationName, ...){
	va_list argptr;
	ExChar argv[1024]= {0};
	ExChar* arg_temp;
	va_start(argptr,applicationName);

	PROCESS_INFORMATION pi = {0};
	STARTUPINFO si = {0};

#ifdef EX_UNICODE
	while(arg_temp = va_arg(argptr, ExChar*)){	// while arg isn't a null variable
		wcscat(argv,(const ExChar*)arg_temp);
		wcscat(argv,EX_TEXT(" "));
		continue;
	}
#else
	while((arg_temp = va_arg(argptr, ExChar*)) != NULL){
		strcat(argv,arg_temp);
		wcscat(argv,EX_TEXT(" "));
		continue;
	}

#endif
	va_end(argptr);
    si.cb = sizeof(si);
	if( !CreateProcess(applicationName,   	// No module name (use command line)
       argv,       	// Command line
        NULL,           // Process handle not inheritable
        NULL,           // Thread handle not inheritable
        FALSE,          // Set handle inheritance to FALSE
        CREATE_NEW_PROCESS_GROUP,// No creation flags
        NULL,           // Use parent's environment block
        NULL,           // Use parent's starting directory
        &si,            // Pointer to STARTUPINFO structure
        &pi )           // Pointer to PROCESS_INFORMATION structure
    ) {
		ExDevWindowPrint(EX_TEXT("CreateProcess failed"));
		return FALSE;
    }

	return TRUE;

}



 void  ExGetPrimaryScreenSize(ExSize* size){
	RECT rect;
	GetWindowRect(GetDesktopWindow(), &rect);
	size->width  = rect.right - rect.left;
	size->height = rect.bottom - rect.top;

}


 void  ExGetMonitorSize(unsigned int index, ExSize* size){
	//unsigned intDisplaySettings(

}


 int  ExGetMonitorSizes(unsigned int index, unsigned int* num, ExSize*sizes){

}

 void  ExGetPrimaryScreenRect(ExRect* rect){
	GetWindowRect(GetDesktopWindow(), (LPRECT)rect);
}

 void  ExGetMonitorRect(unsigned int index, ExRect* rect){

}

 int  ExGetMonitorHz(unsigned int index){
	DEVMODE mod;
	DISPLAY_DEVICE dev;
	//memcpy(&dev,&ExGetMonitor(index),sizeof(dev));
	unsigned intDisplaySettings(dev.DeviceName,unsigned int_CURRENT_SETTINGS, &mod);
	return mod.dmDisplayFrequency;
}


const char*  ExGetPlatform(void){

}

 unsigned int  ExGetPowerInfo(int* sec, int* pct){
	SYSTEM_POWER_STATUS spsPwr;
	if(!GetSystemPowerStatus(&spsPwr))
		ExIsWinError(EX_TEXT("Failed to Get Power Information"));
	if(sec)
		*sec = spsPwr.BatteryLifeTime;
	if(pct)
		*pct = spsPwr.BatteryLifePercent;
	return TRUE;
}

 void  ExGetExecutePath(ExChar* wChar, int length){
	ExIsError(GetModuleFileName(NULL,wChar,length));
}

 void  ExGetAppliationPath(ExChar* path, int length){
	ExIsError(GetCurrentDirectory(length,path));
}

//function manually
 ExChar*  ExGetApplicationName(ExChar* name,int length){
	ExChar path[MAX_PATH];
	ExIsError(GetModuleFileName(NULL,path,sizeof(path)));
	_wsplitpath(path,0,0,name,0);
	return name;

}

 ExChar*  ExGetCurrentDirectory(void){
	ExChar path[1024];
	DWORD a = GetCurrentDirectory(MAX_PATH,path);
	return path;

}

 int  ExSetCurrentDirectory (const ExChar* cdirectory){
	return SetCurrentDirectory(cdirectory);
}

 unsigned int64  ExGetTotalSystemMemory(void){
	MEMORYSTATUSEX status;
	status.dwLength = sizeof(status);
	GlobalMemoryStatusEx(&status);
	return status.ullTotalPhys;

}

 unsigned int64  ExGetTotalVirtualMemory(void){
	MEMORYSTATUSEX status;
	status.dwLength = sizeof(status);
	GlobalMemoryStatusEx(&status);
	return status.ullTotalVirtual;

}



 const ExChar*  ExGetOSName(void){
	OSVERSIONINFO pOSVI;
	pOSVI.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	if(!GetVersionEx(&pOSVI)){
		wExDevPrintf(TEXT("Failed to Get Operting System Version | %s |"),ExGetErrorMessage(GetLastError()));
	}
	// check what version this computer is running.
	if ((pOSVI.dwMajorVersion ==6)&&(pOSVI.dwMinorVersion==4))
		return EX_TEXT("Windows 10");
	else if ((pOSVI.dwMajorVersion ==6)&&(pOSVI.dwMinorVersion==3))
		return EX_TEXT("Windows 8.1");
	else if ((pOSVI.dwMajorVersion ==6)&&(pOSVI.dwMinorVersion==2))
		return EX_TEXT("Windows 8");
	else if ((pOSVI.dwMajorVersion ==6)&&(pOSVI.dwMinorVersion==1))
		return EX_TEXT("Windows 7");
	else if ((pOSVI.dwMajorVersion ==6)&&(pOSVI.dwMinorVersion==0))
		return EX_TEXT("Windows Vista");
	else if ((pOSVI.dwMajorVersion ==5)&&(pOSVI.dwMinorVersion==1))
		return EX_TEXT("Windows XP");
	else if ((pOSVI.dwMajorVersion ==5)&&(pOSVI.dwMinorVersion==0))
		return EX_TEXT("Windows 2000");
	else if ((pOSVI.dwMajorVersion ==4)&&(pOSVI.dwMinorVersion==0))
		return EX_TEXT("Windows NT 4.0");
	else if ((pOSVI.dwMajorVersion ==3)&&(pOSVI.dwMinorVersion==51))
		return EX_TEXT("Windows NT 3.51");
	else if ((pOSVI.dwMajorVersion ==4)&&(pOSVI.dwMinorVersion==90))
		return EX_TEXT("Windows ME");
	else if ((pOSVI.dwMajorVersion ==4)&&(pOSVI.dwMinorVersion==10))
		return EX_TEXT("Windows 98");
	else if((pOSVI.dwMajorVersion ==4)&&(pOSVI.dwMinorVersion==0))
		return TEXT("Windows 95");
	else
		return TEXT("Windows OS Unknown");

}

 const ExChar*  ExGetCurrentUser(void){
	ExChar user[MAX_PATH];
	unsigned long csize;
	ExIsError(GetUserName(user,&csize));
	return user;
}



 int  ExSetClipboardText(const ExChar* text){

	HANDLE handle;
	void* data;
	OpenClipboard(NULL);
	// create a buffer of data
	handle = GlobalAlloc(GMEM_MOVEABLE,
		sizeof(ExChar) * EX_STR_LEN(text) + sizeof(ExChar));
	data = GlobalLock(handle );
	memcpy(data,text, sizeof(ExChar) * EX_STR_LEN(text)+sizeof(ExChar));
	GlobalUnlock(handle);
#ifdef EX_UNICODE
	SetClipboardData(CF_UNICODETEXT,handle);
#else
	SetClipboardData(CF_TEXT,handle);
#endif
	CloseClipboard();
	return (data != NULL);

}


// get clipboard text
 ExChar*  ExGetClipboardText(void){
	HANDLE hData;
	ExChar* pszText;
	OpenClipboard(NULL);
#ifdef EX_UNICODE
	hData = GetClipboardData(CF_UNICODETEXT);
	pszText = (ExChar*)GlobalLock(hData);
#else
	hData = GetClipboardData(CF_TEXT);
	pszText = (char*)GlobalLock(hData);
#endif
	GlobalUnlock( hData );
	CloseClipboard();

	return (ExChar*)pszText;

}


//internetOpenUrl
 void*  ExDownloadURL(const ExChar* url){

	HINTERNET hOpen = NULL;
	HINTERNET hFile = NULL;
	HANDLE hOut = NULL;
	char* lpBuffer = NULL;
	DWORD dwBytesRead = 0;
	DWORD dwBytesWritten = 0;
	hOpen = internetOpen(L"MyAgent", NULL, NULL, NULL, NULL);
	hFile = internetOpenUrl(hOpen,url,0,0,INTERNET_FLAG_RELOAD | INTERNET_FLAG_DONT_CACHE,NULL);

	//internetReadFile(hFile,0,0,&dwBytesRead);
	lpBuffer = (char*)malloc(1024);
	internetReadFile(hFile,(LPVOID*)lpBuffer,1024,&dwBytesRead);
	internetCloseHandle(hFile);
	internetCloseHandle(hOpen);
	return lpBuffer;

}




 DISPLAY_DEVICE  ExGetMonitor(unsigned int index){
	DISPLAY_DEVICE dd;
	dd.cb = sizeof(DISPLAY_DEVICE);
	if(unsigned intDisplayDevices(NULL, index, &dd, 0))
		return dd;
	else{
		ExDevPrintf("Failed to Find monitor at Index %i\n",index);
		return dd;
	}
}

 DISPLAY_DEVICE  ExGetSafeMonitor(unsigned int index){
	DISPLAY_DEVICE dd;
	dd.cb = sizeof(DISPLAY_DEVICE);
	if(unsigned intDisplayDevices(NULL, index, &dd, 0))
		return dd;
	else{
		ExDevPrintf("Failed to Find monitor at Index %i\n",index);
		return dd;
	}
}

 DISPLAY_DEVICE  ExGetPrimaryMontior(void){
	DISPLAY_DEVICE dd;
	dd.cb = sizeof(DISPLAY_DEVICE);
	int index = 0;
	while(unsigned intDisplayDevices(NULL, index++, &dd,0)){
		if(dd.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE) return dd;
		// check the iteration count for preventing infinity loop here.
		if(index > sizeof(ExBoolean) * 256){// check how many monitor is attached. 
			ExDevPrintf("Failed to Find Primary Monitor Device");
			break;
		}
		continue;
	}
	return dd;
}



BOOL CALLBACK unsigned intWindowsProc(_In_  ExWin hwnd,_In_  LPARAM lParam){
	ALTTABINFO i = {0};
	i.cbSize = sizeof(ALTTABINFO);
	if(GetAltTabInfo (hwnd,-1,&i,0,0))
		*((unsigned int*)lParam) += 1;
	//ExBoolean isVis = IsWindowVisible(hwnd);
	//*(unsigned int*)lParam+= isVis;
	return TRUE; 
}


 unsigned int  ExGetWindowChildCount(ExWin hwnd){
	unsigned int icount = 0;
	unsigned intWindows(unsigned intWindowsProc,(LPARAM)&icount);
	return icount;
}

/*

*/
 ExWin  ExprograMan(void){
	ExWin desktop = GetDesktopWindow();
	ExWin handle =  FindWindowEx(desktop,0,EX_TEXT("Progman"),EX_TEXT("Program Manager"));
	return handle;
}

 ExWin  ExShellDef (void){
	HWND desktop = GetDesktopWindow();
	HWND _programHandle = ExprograMan();

	HWND defView = FindWindowEx(_programHandle, NULL, EX_TEXT("SHELLDLL_DefView"), NULL);
	unsigned int ChildAfter = 0;
	while(!defView){
		HWND worker = FindWindowEx(desktop, (HWND)ChildAfter, EX_TEXT("WorkerW"), 0);
		if(worker){
			defView = FindWindowEx(worker, 0, EX_TEXT("SHELLDLL_DefView"),0);
		}
		ChildAfter++;

	}
	return defView;
}

 ExWin  ExhShell(void){
	HWND handle = FindWindowEx(ExprograMan(), 0, EX_TEXT("DeskFolder"), NULL);
	return handle;
}

 ExWin  ExListView(void){
	HWND hwnd;
	unsigned int i = 0;
	HWND listHWND;
	HWND defHWND;
	HWND desktop = GetDesktopWindow();
	hwnd = FindWindowEx(desktop, 0, EX_TEXT("Progman"), EX_TEXT("Program Manager"));
	if(hwnd == NULL)return hwnd;
	defHWND = FindWindowEx(hwnd, 0, EX_TEXT("SHELLDLL_DefView"), 0);
	while(!defHWND){
		HWND worker = FindWindowEx(desktop, (HWND)i, EX_TEXT("WorkerW"), 0);
		if(worker){
			defHWND  = FindWindowEx(worker, 0, EX_TEXT("SHELLDLL_DefView"),0);
		}
		i++;
	}
	listHWND = FindWindowEx(defHWND, NULL, EX_TEXT("SysListView32"), EX_TEXT("FolderView"));

	return listHWND;
}
 ExWin  ExSysHeader32(void){
	return FindWindowEx(ExListView(), 0, EX_TEXT("SysHeader32"), 0);
}


 void  ExAsciiToUnicode(const char* cchar, WCHAR** wchar){
	int length;
	if(!cchar)
		return;

	length = strlen(cchar);
	if(!wchar[0])
		wchar[0] = (WCHAR*)malloc(sizeof(WCHAR) * length + 2);
	if(MultiByteToWideChar(CP_OEMCP,0,cchar,-1,wchar[0], length + 2)){
		wExDevPrintf(EX_TEXT("Failed to Convert to Unicode | %s"), ExGetErrorMessage(GetLastError()));
	}
}

 WCHAR*  ExConvertToUnicode(const char* cchar){
	WCHAR* wconvert;ExAsciiToUnicode(cchar,&wconvert);return wconvert;
}

 void  ExUnicodeToAscii(const WCHAR* wchar, char** cchar){
	int length = wcslen(wchar);
	if(!wchar)return;
	if(!*cchar)
		cchar[0] = (char*)malloc(sizeof(char) * length + 1);
	if(WideCharToMultiByte(CP_OEMCP,0,wchar, -1, cchar[0],sizeof(char) * length + sizeof(char), 0,0) <= 0){
		wExDevPrintf(EX_TEXT("Failed to Convert to Asci | %s"), ExGetErrorMessage(GetLastError()));
	}
}

 char*  ExConvertAscii(const WCHAR* wwchar){
	char* cconvert;ExUnicodeToAscii(wwchar,&cconvert);return cconvert;
}


// http://forum.codecall.net/topic/63205-registry-operations-using-win32-part-1/
#define ExOpenRegKey(hKey,directory,phKey) RegOpenKeyEx(hKey,directory,0, KEY_ALL_ACCESS, phKey)

 ExBoolean  ExExistRegKey(HKEY hKey, const ExChar* directory){
	return (ExBoolean)ExOpenRegKey(hKey,directory,NULL) == ERROR_SUCCESS ? TRUE : FALSE;
}

 unsigned int  ExGetRegValuei(HKEY hKey, const ExChar* directory, const ExChar* cregname){
	DWORD res;
	DWORD type =REG_DWORD;
	DWORD cbData =1024;
	DWORD val;
	ExOpenRegKey(hKey,directory,&hKey);
	res = RegQueryValueEx(hKey, cregname,NULL,&type,(LPBYTE)&val,&cbData);
	if(res != ERROR_SUCCESS)
		wExDevPrint(L"Error reading value");
	RegCloseKey(hKey);
	return val;
}

 unsigned int64  ExGetRegValuel(HKEY hKey, const ExChar* directory, const ExChar* cregname){
	DWORD res;
	DWORD type =REG_DWORD;
	DWORD cbData =1024;
	unsigned int64 val;
	ExOpenRegKey(hKey,directory,&hKey);
	res = RegQueryValueEx(hKey, cregname,NULL,&type,(LPBYTE)&val,&cbData);
	if(res != ERROR_SUCCESS)
		wExDevPrint(L"Error reading value");
	RegCloseKey(hKey);
	return val;
}
/*
 unsigned int  ExGetRegValuec(HKEY hKey, const ExChar* directory, const ExChar* cregname, ExChar* character_string){
	DWORD res;
	DWORD type =REG_DWORD;
	DWORD cbData =1024;
	ExOpenRegKey(hKey,directory,&hKey);
	res = RegQueryValueEx(hKey, cregname,NULL,&type,(LPBYTE)character_string,&cbData);
	if(res != ERROR_SUCCESS)
		wExDevPrint(L"Error reading value");
	RegCloseKey(hKey);
	return res;
}

 void ExSetRegValuei(HKEY hKey, const ExChar* directory, const ExChar* cregname,int iint){

}

 void ExSetRegValuel(HKEY hKey, const ExChar* directory, const ExChar* cregname,Long ilong){
	DWORD res;
	DWORD type =REG_DWORD;
	DWORD cbData =1024;
	DWORD val;
	ExOpenRegKey(hKey,directory,&hKey);

	RegSetValueEx(hKey,cregname,NULL,REG_DWORD,(unsigned char*)&ilong,sizeof(Long));
	RegCloseKey(hKey);
}

 void ExSetRegValuec(HKEY hKey, LPCWSTR directory, LPCWSTR cregname,LPCWSTR character){
	DWORD res;
	DWORD type =REG_DWORD;
	DWORD cbData =1024;
	DWORD val;
	ExOpenRegKey(hKey,directory,&hKey);

	RegSetValueEx(hKey,cregname,NULL,REG_SZ,(unsigned char*)character,2 * wcslen(character)+2);
	RegCloseKey(hKey);
}

 void ExCreateRegKey(HKEY hKey,const ExChar* directory){
	DWORD dwDisposition;
	RegCreateKeyEx(hKey, directory, 0, NULL, 0,0,NULL, &hKey,&dwDisposition);
	if(dwDisposition != REG_CREATED_NEW_KEY && dwDisposition != REG_OPENED_EXISTING_KEY)
		wExDevPrint(L"Error reading value");
}

 void ExCreateFileExts(LPCWSTR filetype){
	WCHAR path[MAX_PATH];
	HKEY hKey;
	WORD res;
	res = ExOpenRegKey(HKEY_CURRENT_USER, EX_TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\FileExts\\"),&hKey);
	ExCreateRegKey(hKey,filetype);
	RegCloseKey(hKey);

	memcpy(path, EX_TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\FileExts\\"), wcslen( EX_TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\FileExts\\")) * 2 + 2);
	memcpy(&path[wcslen( EX_TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\FileExts\\"))],filetype, wcslen(filetype) * 2 + 2);
	ExCreateRegKey(HKEY_CURRENT_USER,path);

	// class root 
	ExCreateRegKey(HKEY_CLASSES_ROOT,filetype);
	res = ExOpenRegKey(HKEY_CLASSES_ROOT,filetype,&hKey);
	ExCreateRegKey(hKey,EX_TEXT("OpenWithList"));
	ExCreateRegKey(hKey,EX_TEXT("OpenWithProgids"));
	RegCloseKey(hKey);


}


 void ExCreateFileExtsDesc(LPCWSTR filetype,LPCWSTR description){
	ExSetRegValuec(HKEY_CLASSES_ROOT,filetype,EX_TEXT(""),description);
}

*/

