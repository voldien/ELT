#include"wnd_common.h"
#ifdef EX_WINDOWS

#include<string.h>
#ifdef EX_CPP
	using namespace std;
#endif

DECLSPEC DISPLAY_DEVICE ELTAPIENTRY ExGetMonitor(Uint32 index){
	DISPLAY_DEVICE dd;
	dd.cb = sizeof(DISPLAY_DEVICE);
	if(EnumDisplayDevices(NULL, index, &dd, 0))
		return dd;
	else{
		ExDevPrintf("Failed to Find monitor at Index %i\n",index);
		return dd;
	}
}
DECLSPEC DISPLAY_DEVICE ELTAPIENTRY ExGetSafeMonitor(Uint32 index){
	DISPLAY_DEVICE dd;
	dd.cb = sizeof(DISPLAY_DEVICE);
	if(EnumDisplayDevices(NULL, index, &dd, 0))
		return dd;
	else{
		ExDevPrintf("Failed to Find monitor at Index %i\n",index);
		return dd;
	}
}
DECLSPEC DISPLAY_DEVICE ELTAPIENTRY ExGetPrimaryMontior(void){
	DISPLAY_DEVICE dd;
	dd.cb = sizeof(DISPLAY_DEVICE);
	Int32 index = 0;
	while(EnumDisplayDevices(NULL, index++, &dd,0)){
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



BOOL CALLBACK EnumWindowsProc(_In_  ExWin hwnd,_In_  LPARAM lParam){
	ALTTABINFO i = {0};
	i.cbSize = sizeof(ALTTABINFO);
	if(GetAltTabInfo (hwnd,-1,&i,0,0))
		*((Uint32*)lParam) += 1;
	//ExBoolean isVis = IsWindowVisible(hwnd);
	//*(Uint*)lParam+= isVis;
	return TRUE; 
}

DECLSPEC Uint32 ELTAPIENTRY ExGetWindowChildCount(ExWin hwnd){
	Uint32 icount = 0;
	EnumWindows(EnumWindowsProc,(LPARAM)&icount);
	return icount;
}

/*

*/
DECLSPEC ExWin ELTAPIENTRY ExprograMan(void){
	ExWin desktop = GetDesktopWindow();
	ExWin handle =  FindWindowEx(desktop,0,EX_TEXT("Progman"),EX_TEXT("Program Manager"));
	return handle;
}
DECLSPEC ExWin ELTAPIENTRY ExShellDef (void){
	HWND desktop = GetDesktopWindow();
	HWND _programHandle = ExprograMan();

	HWND defView = FindWindowEx(_programHandle, NULL, EX_TEXT("SHELLDLL_DefView"), NULL);
	Uint ChildAfter = 0;
	while(!defView){
		HWND worker = FindWindowEx(desktop, (HWND)ChildAfter, EX_TEXT("WorkerW"), 0);
		if(worker){
			defView = FindWindowEx(worker, 0, EX_TEXT("SHELLDLL_DefView"),0);
		}
		ChildAfter++;
		continue;
	}
	return defView;
}
DECLSPEC ExWin ELTAPIENTRY ExhShell(void){
	HWND handle = FindWindowEx(ExprograMan(), 0, EX_TEXT("DeskFolder"), NULL);
	return handle;
}
DECLSPEC ExWin ELTAPIENTRY ExListView(void){
	HWND hwnd;
	Uint32 i = 0;
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
DECLSPEC ExWin ELTAPIENTRY ExSysHeader32(void){
	return FindWindowEx(ExListView(), 0, EX_TEXT("SysHeader32"), 0);
}


DECLSPEC void ELTAPIENTRY ExAsciiToUnicode(const char* cchar, WCHAR** wchar){
	Int32 length;
	if(!cchar)return;
	length = strlen(cchar);
	if(!wchar[0])
		wchar[0] = (WCHAR*)ExMalloc(sizeof(WCHAR) * length + 2);
	if(MultiByteToWideChar(CP_OEMCP,0,cchar,-1,wchar[0], length + 2)){
		wExDevPrintf(EX_TEXT("Failed to Convert to Unicode | %s"), ExGetErrorMessage(GetLastError()));
	}
}
DECLSPEC WCHAR* ELTAPIENTRY ExConvertToUnicode(const char* cchar){
	WCHAR* wconvert;ExAsciiToUnicode(cchar,&wconvert);return wconvert;
}

DECLSPEC void ELTAPIENTRY ExUnicodeToAscii(const WCHAR* wchar, char** cchar){
	Int32 length = wcslen(wchar);
	if(!wchar)return;
	if(!*cchar)
		cchar[0] = (char*)ExMalloc(sizeof(char) * length + 1);
	if(WideCharToMultiByte(CP_OEMCP,0,wchar, -1, cchar[0],sizeof(char) * length + sizeof(char), 0,0) <= 0){
		wExDevPrintf(EX_TEXT("Failed to Convert to Asci | %s"), ExGetErrorMessage(GetLastError()));
	}
}
DECLSPEC char* ELTAPIENTRY ExConvertAscii(const WCHAR* wwchar){
	char* cconvert;ExUnicodeToAscii(wwchar,&cconvert);return cconvert;
}


// http://forum.codecall.net/topic/63205-registry-operations-using-win32-part-1/
#define ExOpenRegKey(hKey,directory,phKey) RegOpenKeyEx(hKey,directory,0, KEY_ALL_ACCESS, phKey)

DECLSPEC ExBoolean ELTAPIENTRY ExExistRegKey(HKEY hKey, const ExChar* directory){
	return (ExBoolean)ExOpenRegKey(hKey,directory,NULL) == ERROR_SUCCESS ? TRUE : FALSE;
}

DECLSPEC Uint32 ELTAPIENTRY ExGetRegValuei(HKEY hKey, const ExChar* directory, const ExChar* cregname){
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
DECLSPEC Uint64 ELTAPIENTRY ExGetRegValuel(HKEY hKey, const ExChar* directory, const ExChar* cregname){
	DWORD res;
	DWORD type =REG_DWORD;
	DWORD cbData =1024;
	Uint64 val;
	ExOpenRegKey(hKey,directory,&hKey);
	res = RegQueryValueEx(hKey, cregname,NULL,&type,(LPBYTE)&val,&cbData);
	if(res != ERROR_SUCCESS)
		wExDevPrint(L"Error reading value");
	RegCloseKey(hKey);
	return val;
}
DECLSPEC Uint32 ELTAPIENTRY ExGetRegValuec(HKEY hKey, const ExChar* directory, const ExChar* cregname, ExChar* character_string){
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

DECLSPEC void ExSetRegValuei(HKEY hKey, const ExChar* directory, const ExChar* cregname,Int32 iint){

}
DECLSPEC void ExSetRegValuel(HKEY hKey, const ExChar* directory, const ExChar* cregname,Long ilong){
	DWORD res;
	DWORD type =REG_DWORD;
	DWORD cbData =1024;
	DWORD val;
	ExOpenRegKey(hKey,directory,&hKey);

	RegSetValueEx(hKey,cregname,NULL,REG_DWORD,(Uint8*)&ilong,sizeof(Long));
	RegCloseKey(hKey);
}
DECLSPEC void ExSetRegValuec(HKEY hKey, LPCWSTR directory, LPCWSTR cregname,LPCWSTR character){
	DWORD res;
	DWORD type =REG_DWORD;
	DWORD cbData =1024;
	DWORD val;
	ExOpenRegKey(hKey,directory,&hKey);

	RegSetValueEx(hKey,cregname,NULL,REG_SZ,(Uint8*)character,2 * wcslen(character)+2);
	RegCloseKey(hKey);
}

DECLSPEC void ExCreateRegKey(HKEY hKey,const ExChar* directory){
	DWORD dwDisposition;
	RegCreateKeyEx(hKey, directory, 0, NULL, 0,0,NULL, &hKey,&dwDisposition);
	if(dwDisposition != REG_CREATED_NEW_KEY && dwDisposition != REG_OPENED_EXISTING_KEY)
		wExDevPrint(L"Error reading value");
}

DECLSPEC void ExCreateFileExts(LPCWSTR filetype){
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
DECLSPEC void ExCreateFileExtsDesc(LPCWSTR filetype,LPCWSTR description){
	ExSetRegValuec(HKEY_CLASSES_ROOT,filetype,EX_TEXT(""),description);
}


#ifdef EX_CPP
/*
	folder file paths
*/
DECLSPEC FolderListA ELTAPIENTRY ExGetFolderFilePathA(const char* directoryPath){
	if(strlen(directoryPath) == 0)return FolderListA();// directory null

	FolderListA fileList;
	WIN32_FIND_DATA ffd;
	LARGE_INTEGER fileSize;
	TCHAR szDir[MAX_PATH];
	HANDLE hFind = INVALID_HANDLE_VALUE;
	DWORD wdError = 0;
	string path = directoryPath;
	wstring thePath;
	thePath = wstring(path.begin(), path.end());
	if(directoryPath[path.size() - 1] != '\\')
		thePath += TEXT("\\");
	thePath += TEXT("/*");
	hFind  = FindFirstFile(thePath.c_str(), &ffd);

	if (INVALID_HANDLE_VALUE == hFind){
		thePath.pop_back();	thePath.pop_back();
		wExDevPrintf(TEXT("Failed to Get Folder Files | Path %s : Error Code %s"),thePath.data(),ExGetErrorMessage(GetLastError()));
		return fileList;
	}
	do{
      if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){
		  printf("FileName : %s \n",ffd.cFileName);
      }
      else{
         fileSize.LowPart = ffd.nFileSizeLow;
         fileSize.HighPart = ffd.nFileSizeHigh;

		 const wstring fileName = ffd.cFileName;
		 fileList.push_back(string(path.begin(),path.end()) + "\\" + string(fileName.begin(), fileName.end()));
      }
   }
   while (FindNextFile(hFind, &ffd) != 0);
   wdError = GetLastError();
   if(wdError != ERROR_NO_MORE_FILES) {
	   // a error acured under the process.
		wExDevPrintf(TEXT("Error Accuted during the GetFolderPath | Path %s : Error Code %s"),thePath.data(),ExGetErrorMessage(wdError));
   }
	FindClose(hFind);
	return fileList;
}	
DECLSPEC FolderListW ELTAPIENTRY ExGetFolderFilePathW(const WCHAR* directoryPath){
	if(!wcslen(directoryPath))return FolderListW();
	FolderListW fileList;
	WIN32_FIND_DATA ffd;
	LARGE_INTEGER fileSize;
	TCHAR szDir[MAX_PATH];
	HANDLE hFind = INVALID_HANDLE_VALUE;
	DWORD wdError = 0;
	wstring path = directoryPath;
	wstring thePath(path.size() - 1, EX_TEXT('#'));
	thePath = directoryPath;

	if(thePath[thePath.size() - 1] != EX_TEXT('\\'))
		thePath += EX_TEXT("\\");
	thePath += EX_TEXT("/*");
	hFind  = FindFirstFile(thePath.c_str(), &ffd);

	// if handler was found
	if (INVALID_HANDLE_VALUE == hFind){
		thePath.pop_back();	thePath.pop_back();
		wExDevPrintf(EX_TEXT("Failed to Get Folder Files | Path %s | Error Code %s"),thePath.data(),ExGetErrorMessage(GetLastError()));
		return fileList;
	}
	do{
		if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){
#ifdef EX_DEBUG
			wprintf(EX_TEXT("FileName %s\n"), ffd.cFileName);
#endif
		}
		else{
			fileSize.LowPart = ffd.nFileSizeLow;
			fileSize.HighPart = ffd.nFileSizeHigh;

			const wstring fileName = ffd.cFileName;
			fileList.push_back(wstring(path.begin(),path.end()));
			fileList[fileList.size() - 1] = wstring(fileList[fileList.size() - 1] + fileName );
		}
	}
	while (FindNextFile(hFind, &ffd) != 0);
	wdError = GetLastError();
	if (wdError != ERROR_NO_MORE_FILES) {
		// a error accured during the process.
		wExDevPrintf(EX_TEXT("Error Accuted during the GetFolderPath | Path %s : Error Code %s"),thePath.data(),ExGetErrorMessage(wdError));
	}
	FindClose(hFind);
	return fileList;
}

DECLSPEC FolderListW ELTAPIENTRY ExGetFolderDirectoryPathW(const WCHAR* directoryPath){
	if(wcslen(directoryPath) == 0)return FolderListW();
	FolderListW fileList;
	WIN32_FIND_DATA ffd;
	LARGE_INTEGER fileSize;
	TCHAR szDir[MAX_PATH];
	HANDLE hFind = INVALID_HANDLE_VALUE;
	DWORD wdError = 0;
	wstring path = directoryPath;
	wstring thePath(path.size() - 1, EX_TEXT('#'));
	thePath = directoryPath;

	if(thePath[thePath.size() - 1] != EX_TEXT('\\'))
		thePath += EX_TEXT("\\");
	thePath += EX_TEXT("/*");
	hFind  = FindFirstFile(thePath.c_str(), &ffd);
	// if handler was found
	if (INVALID_HANDLE_VALUE == hFind){
		thePath.pop_back();	thePath.pop_back();
		wExDevPrintf(EX_TEXT("Failed to Get Folder Files | Path %s | Error Code %s"),thePath.data(),ExGetErrorMessage(GetLastError()));
		return fileList;
	}
	do{
		if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){
			fileSize.LowPart = ffd.nFileSizeLow;
			fileSize.HighPart = ffd.nFileSizeHigh;

			const wstring fileName = ffd.cFileName;
			fileList.push_back(path);
			fileList[fileList.size() - 1] = wstring(fileList[fileList.size() - 1] + fileName + EX_TEXT("\\"));
		}
	}
	while (FindNextFile(hFind, &ffd) != 0);
	wdError = GetLastError();
	if (wdError != ERROR_NO_MORE_FILES) {
		// a error accured during the process.
		wExDevPrintf(EX_TEXT("Error Accuted during the GetFolderPath | Path %s : Error Code %s"),thePath.data(),ExGetErrorMessage(wdError));
	}
	FindClose(hFind);
	return fileList;
}
DECLSPEC FolderListA ELTAPIENTRY ExGetFolderDirectoryPathA(const char* directoryPath){
	if(strlen(directoryPath) == 0)return FolderListA();
	FolderListA filelist;

	return filelist;
}

#endif // C++


#endif // Windows