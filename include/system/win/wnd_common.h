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
#ifndef _WND_COMMON_H_
#define _WND_COMMON_H_ 1
#include"./../../EngineAssembly.h"
#include"./../../elt_console.h"
#include<Windows.h>

#ifdef __cplusplus /* C++ environment */
extern "C"{
#endif

/**
	//Set Monitor Sleep
*/
//extern DECLSPEC void ELTAPIENTRY ExSleepMonitor(void){SendMessage(HWND_BROADCAST, WM_SYSCOMMAND,SC_SCREENSAVE, (LPARAM)2);}



/* Get Monitor Display Device*/
extern DECLSPEC DISPLAY_DEVICE ELTAPIENTRY ExGetMonitor(Uint32 index);
/* Get Monitor Display Device. if index isn't value. then it will decriment intill a valid monitor Index*/
extern DECLSPEC DISPLAY_DEVICE ELTAPIENTRY ExGetSafeMonitor(Uint32 index);
/* Get Primary Montior Display Device.*/
extern DECLSPEC DISPLAY_DEVICE ELTAPIENTRY ExGetPrimaryMontior(void);

/*	Get Count of Children Window */
extern DECLSPEC Uint32 ELTAPIENTRY ExGetWindowChildCount(ExWin hwnd);

/*		*/
extern DECLSPEC ExWin ELTAPIENTRY ExShellDef(void);
/*		*/
extern DECLSPEC ExWin ELTAPIENTRY ExhShell(void);
/*		*/
extern DECLSPEC ExWin ELTAPIENTRY ExprograMan(void);
/*	Parent of	*/
extern DECLSPEC ExWin ELTAPIENTRY ExListView(void);
/*	Lowest Child	*/
extern DECLSPEC ExWin ELTAPIENTRY ExSysHeader32(void);

/*
	// Convert Ascii Character into Wide-character
*/
extern DECLSPEC void ELTAPIENTRY ExAsciiToUnicode(const char* cchar, WCHAR** wchar);
extern DECLSPEC WCHAR* ELTAPIENTRY ExConvertToUnicode(const char* cchar);
/*
	// Convert Wide-character Character into Ascii
	// remark: if char pointer is null. then it will malloc its size. otherwise
	// the function will use char* current size
*/
extern DECLSPEC void ELTAPIENTRY ExUnicodeToAscii(const WCHAR* wchar, char** cchar);
extern DECLSPEC char* ELTAPIENTRY ExConvertAscii(const WCHAR* wwchar);

/*
	// registry window
*/
/*
	// exist
*/
extern DECLSPEC ExBoolean ELTAPIENTRY ExExistRegKey(HKEY hKey, const ExChar* directory);
// get value
extern DECLSPEC Uint32 ELTAPIENTRY ExGetRegValuei(HKEY hKey, const ExChar* directory, const ExChar* cregname);
extern DECLSPEC Uint64 ELTAPIENTRY ExGetRegValuel(HKEY hKey, const ExChar* directory, const ExChar* cregname);
extern DECLSPEC Uint32 ELTAPIENTRY ExGetRegValuec(HKEY hKey, const ExChar* directory, const ExChar* cregname, WCHAR* character_string);
extern DECLSPEC Uint32 ELTAPIENTRY ExGetRegValuecv(HKEY hKey, const ExChar* directory, const ExChar* cregname, WCHAR* character_string);
// get registry value
extern DECLSPEC Uint32 ELTAPIENTRY ExGetRegValueType(HKEY hKey, const ExChar* directory, const ExChar* cregname);

extern DECLSPEC void ELTAPIENTRY ExSetRegValuei(HKEY hKey, const ExChar* directory, const ExChar* cregname,Int32 iint);
extern DECLSPEC void ELTAPIENTRY ExSetRegValuel(HKEY hKey, const ExChar* directory, const ExChar* cregname,Long ilong);
extern DECLSPEC void ELTAPIENTRY ExSetRegValuec(HKEY hKey, const ExChar* directory, const ExChar* cregname,LPCWSTR character);
extern DECLSPEC Uint32 ELTAPIENTRY ExSetRegValuecv(HKEY hKey, const ExChar* directory, const ExChar* cregname, WCHAR* character_string);

extern DECLSPEC void ELTAPIENTRY ExCreateRegKey(HKEY hKey, const ExChar* directory);

/*
	// file exts for desktop
	http://msdn.microsoft.com/en-us/library/windows/desktop/cc144148(v=vs.85).aspx
*/
extern DECLSPEC void ELTAPIENTRY ExCreateFileExts(const ExChar* filetype);
extern DECLSPEC void ELTAPIENTRY ExCreateFileExtsDesc(const ExChar* filetype,const ExChar* description);
extern DECLSPEC ExBoolean ELTAPIENTRY ExRemoveFileExts(const ExChar* filetype);

#ifdef __cplusplus // C++ environment
}
#endif

typedef struct filefolderA{
	char** file;
	unsigned int filecount;
}FILE_FOLDER_A;
typedef struct filefolderW{
	wchar_t** file;
	unsigned int filecount;
}FILE_FOLDER_W;

// UNICODE
#ifdef EX_UNCIODE
	#define ExGetFolderFilePath ExGetFolderFilePathW
	#define ExGetFolderDirectoryPath ExGetFolderDirectoryPathW
	#define ExGetFolderFileName ExGetFolderFileNameW
	typedef FolderListW FolderList;
#else
	#define ExGetFolderFilePath ExGetFolderFilePathA
	#define ExGetFolderDirectoryPath ExGetFolderDirectoryPathA
	#define ExGetFolderFileName ExGetFolderFileNameA
	//typedef FolderListA FolderList;
#endif

#endif
