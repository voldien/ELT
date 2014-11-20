/*
===========================================================================
Copyright (C) 2014 BroodCity Software, Inc. Voldemor2009@hotmail.com

*/
#ifndef WND_COMMON_H
#define WND_COMMON_H
#include"./../../EngineAssembly.h"
#include"./../../elt_console.h"
#include<Cmd/mathlib.h>
#ifdef EX_WINDOWS
	#include<Windows.h>
#ifdef EX_CPP
extern "C"{
#endif

/*	
	//Set Monitor Sleep
*/
extern DECLSPEC INLINE Void ELTAPIENTRY ExSleepMonitor(Void){SendMessage(HWND_BROADCAST, WM_SYSCOMMAND,SC_SCREENSAVE, (LPARAM)2);}



/* Get Monitor Display Device*/
extern DECLSPEC DISPLAY_DEVICE ELTAPIENTRY ExGetMonitor(Uint32 index);
/* Get Monitor Display Device. if index isn't value. then it will decriment intill a valid monitor Index*/
extern DECLSPEC DISPLAY_DEVICE ELTAPIENTRY ExGetSafeMonitor(Uint32 index);
/* Get Primary Montior Display Device.*/
extern DECLSPEC DISPLAY_DEVICE ELTAPIENTRY ExGetPrimaryMontior(Void);

/*	Get Count of Children Window */
extern DECLSPEC Uint32 ELTAPIENTRY ExGetWindowChildCount(ExWin hwnd);

/*		*/
extern DECLSPEC ExWin ELTAPIENTRY ExShellDef(Void);
/*		*/
extern DECLSPEC ExWin ELTAPIENTRY ExhShell(Void);
/*		*/
extern DECLSPEC ExWin ELTAPIENTRY ExprograMan(Void);
/*	Parent of	*/
extern DECLSPEC ExWin ELTAPIENTRY ExListView(Void);
/*	Lowest Child	*/
extern DECLSPEC ExWin ELTAPIENTRY ExSysHeader32(Void);

/*
	// Convert Ascii Character into Wide-character
*/
extern DECLSPEC Void ELTAPIENTRY ExAsciiToUnicode(const char* cchar, WCHAR** wchar);
DECLSPEC INLINE WCHAR* ELTAPIENTRY ExConvertToUnicode(const char* cchar){
	WCHAR* wconvert;ExAsciiToUnicode(cchar,&wconvert);return wconvert;
}
/*
	// Convert Wide-character Character into Ascii
	// remark: if char pointer is null. then it will malloc its size. otherwise 
	// the function will use char* current size
*/
extern DECLSPEC Void ELTAPIENTRY ExUnicodeToAscii(const WCHAR* wchar, char** cchar);
DECLSPEC INLINE char* ELTAPIENTRY ExConvertAscii(const WCHAR* wwchar){
	char* cconvert;ExUnicodeToAscii(wwchar,&cconvert);return cconvert;
}

/*
	// registry window
*/
/*
	// exist
*/
extern DECLSPEC Boolean ELTAPIENTRY ExExistRegKey(HKEY hKey, const ExChar* directory);
// get value
extern DECLSPEC Uint32 ELTAPIENTRY ExGetRegValuei(HKEY hKey, const ExChar* directory, const ExChar* cregname);
extern DECLSPEC Uint64 ELTAPIENTRY ExGetRegValuel(HKEY hKey, const ExChar* directory, const ExChar* cregname);
extern DECLSPEC Uint32 ELTAPIENTRY ExGetRegValuec(HKEY hKey, const ExChar* directory, const ExChar* cregname, WCHAR* character_string);
extern DECLSPEC Uint32 ELTAPIENTRY ExGetRegValuecv(HKEY hKey, const ExChar* directory, const ExChar* cregname, WCHAR* character_string);
// get registry value
extern DECLSPEC Uint32 ELTAPIENTRY ExGetRegValueType(HKEY hKey, const ExChar* directory, const ExChar* cregname);

extern DECLSPEC Void ELTAPIENTRY ExSetRegValuei(HKEY hKey, const ExChar* directory, const ExChar* cregname,Int32 iint);
extern DECLSPEC Void ELTAPIENTRY ExSetRegValuel(HKEY hKey, const ExChar* directory, const ExChar* cregname,Long ilong);
extern DECLSPEC Void ELTAPIENTRY ExSetRegValuec(HKEY hKey, const ExChar* directory, const ExChar* cregname,LPCWSTR character);
extern DECLSPEC Uint32 ELTAPIENTRY ExSetRegValuecv(HKEY hKey, const ExChar* directory, const ExChar* cregname, WCHAR* character_string);

extern DECLSPEC Void ELTAPIENTRY ExCreateRegKey(HKEY hKey, const ExChar* directory);

/*
	// file exts for desktop
	http://msdn.microsoft.com/en-us/library/windows/desktop/cc144148(v=vs.85).aspx
*/
extern DECLSPEC Void ELTAPIENTRY ExCreateFileExts(const ExChar* filetype);
extern DECLSPEC Void ELTAPIENTRY ExCreateFileExtsDesc(const ExChar* filetype,const ExChar* description);
extern DECLSPEC Boolean ELTAPIENTRY ExRemoveFileExts(const ExChar* filetype);

#ifdef EX_CPP
}
#endif


#ifdef EX_CPP
#include<vector>
#include<string>
// vector list container of strings 
typedef std::vector<std::string> FolderListA;
// vector list container of wide-strings 
typedef std::vector<std::wstring> FolderListW;
#else
typedef struct filefolderA{
	char** file;
	unsigned int filecount;
}FILE_FOLDER_A;
typedef struct filefolderW{
	wchar_t** file;
	unsigned int filecount;
}FILE_FOLDER_W;
#endif



//-------------------------------------------------------------------
/* Get All possiable File Name in Specified Folder Location. */
DECLSPEC FolderListA ELTAPIENTRY ExGetFolderFilePathA(const char* directoryPath);

//-------------------------------------------------------------------
/* Get All possiable File Name in  */
DECLSPEC FolderListW ELTAPIENTRY ExGetFolderFilePathW(const WCHAR* directoryPath);



DECLSPEC FolderListW ELTAPIENTRY ExGetFolderFileNameW(const WCHAR* directoryPath);

DECLSPEC FolderListA ELTAPIENTRY ExGetFolderFileNameA(const char* directoryPath);

//-------------------------------------------------------------------
/* Get All possiable File Name in Specified Folder Location as a Relative Path. */
DECLSPEC FolderListW ELTAPIENTRY ExGetFolderDirectoryPathW(const WCHAR* directoryPath);

//-------------------------------------------------------------------
/* Get All possiable File Name in Specified Folder Location as a Relative Path. */
DECLSPEC FolderListA ELTAPIENTRY ExGetFolderDirectoryPathA(const char* directoryPath);

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
	typedef FolderListA FolderList;
#endif



#endif
#endif