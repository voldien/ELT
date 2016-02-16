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
#ifndef _ELT_WND_COMMON_H_
#define _ELT_WND_COMMON_H_ 1
#include"./../../EngineAssembly.h"
#include<windows.h>

#ifdef __cplusplus /* C++ environment */
extern "C"{
#endif

/**
	//Set Monitor Sleep
*/
//extern ELTDECLSPEC void ELTAPIENTRY ExSleepMonitor(void){SendMessage(HWND_BROADCAST, WM_SYSCOMMAND,SC_SCREENSAVE, (LPARAM)2);}



/*
 *	Get Monitor Display Device
 */
extern ELTDECLSPEC DISPLAY_DEVICE ELTAPIENTRY ExGetMonitor(Uint32 index);

/*
 *	Get Monitor Display Device. if index isn't value. then it will decriment intill a valid monitor Index
 */
extern ELTDECLSPEC DISPLAY_DEVICE ELTAPIENTRY ExGetSafeMonitor(Uint32 index);

/* Get Primary Montior Display Device.*/
extern ELTDECLSPEC DISPLAY_DEVICE ELTAPIENTRY ExGetPrimaryMontior(void);

/*	Get Count of Children Window */
extern ELTDECLSPEC Uint32 ELTAPIENTRY ExGetWindowChildCount(ExWin hwnd);

/*		*/
extern ELTDECLSPEC ExWin ELTAPIENTRY ExShellDef(void);
/*		*/
extern ELTDECLSPEC ExWin ELTAPIENTRY ExhShell(void);
/*		*/
extern ELTDECLSPEC ExWin ELTAPIENTRY ExprograMan(void);
/*	Parent of	*/
extern ELTDECLSPEC ExWin ELTAPIENTRY ExListView(void);
/*	Lowest Child	*/
extern ELTDECLSPEC ExWin ELTAPIENTRY ExSysHeader32(void);

/*
	// Convert Ascii Character into Wide-character
*/
extern ELTDECLSPEC void ELTAPIENTRY ExAsciiToUnicode(const char* cchar, WCHAR** wchar);
extern ELTDECLSPEC WCHAR* ELTAPIENTRY ExConvertToUnicode(const char* cchar);
/*
	// Convert Wide-character Character into Ascii
	// remark: if char pointer is null. then it will malloc its size. otherwise
	// the function will use char* current size
*/
extern ELTDECLSPEC void ELTAPIENTRY ExUnicodeToAscii(const WCHAR* wchar, char** cchar);
extern ELTDECLSPEC char* ELTAPIENTRY ExConvertAscii(const WCHAR* wwchar);

/*
	// registry window
*/
/*
	// exist
*/
extern ELTDECLSPEC ExBoolean ELTAPIENTRY ExExistRegKey(HKEY hKey, const ExChar* directory);
// get value
extern ELTDECLSPEC Uint32 ELTAPIENTRY ExGetRegValuei(HKEY hKey, const ExChar* directory, const ExChar* cregname);
extern ELTDECLSPEC Uint64 ELTAPIENTRY ExGetRegValuel(HKEY hKey, const ExChar* directory, const ExChar* cregname);
extern ELTDECLSPEC Uint32 ELTAPIENTRY ExGetRegValuec(HKEY hKey, const ExChar* directory, const ExChar* cregname, WCHAR* character_string);
extern ELTDECLSPEC Uint32 ELTAPIENTRY ExGetRegValuecv(HKEY hKey, const ExChar* directory, const ExChar* cregname, WCHAR* character_string);
// get registry value
extern ELTDECLSPEC Uint32 ELTAPIENTRY ExGetRegValueType(HKEY hKey, const ExChar* directory, const ExChar* cregname);

extern ELTDECLSPEC void ELTAPIENTRY ExSetRegValuei(HKEY hKey, const ExChar* directory, const ExChar* cregname,Int32 iint);
extern ELTDECLSPEC void ELTAPIENTRY ExSetRegValuel(HKEY hKey, const ExChar* directory, const ExChar* cregname,Long ilong);
extern ELTDECLSPEC void ELTAPIENTRY ExSetRegValuec(HKEY hKey, const ExChar* directory, const ExChar* cregname,LPCWSTR character);
extern ELTDECLSPEC Uint32 ELTAPIENTRY ExSetRegValuecv(HKEY hKey, const ExChar* directory, const ExChar* cregname, WCHAR* character_string);

extern ELTDECLSPEC void ELTAPIENTRY ExCreateRegKey(HKEY hKey, const ExChar* directory);

/*
	// file exts for desktop
	http://msdn.microsoft.com/en-us/library/windows/desktop/cc144148(v=vs.85).aspx
*/
extern ELTDECLSPEC void ELTAPIENTRY ExCreateFileExts(const ExChar* filetype);
extern ELTDECLSPEC void ELTAPIENTRY ExCreateFileExtsDesc(const ExChar* filetype,const ExChar* description);
extern ELTDECLSPEC ExBoolean ELTAPIENTRY ExRemoveFileExts(const ExChar* filetype);

#ifdef __cplusplus	/*	C++ environment	*/
}
#endif

#endif
