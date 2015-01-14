/*
===========================================================================
Copyright (C) 2014 BroodCity Software, Inc. Voldemor2009@hotmail.com

*/
#ifndef WND_COMMON_H
#define WND_COMMON_H
#include"./../../EngineAssembly.h"
#include"./../../elt_console.h"

#ifdef EX_WINDOWS
	#include<Windows.h>
#ifdef __cplusplus // C++ environment
extern "C"{
#endif

/*	
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


#ifdef __cplusplus // C++ environment
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
//extern DECLSPEC FolderListA ELTAPIENTRY ExGetFolderFilePathA(const char* directoryPath);

//-------------------------------------------------------------------
/* Get All possiable File Name in  */
//extern DECLSPEC FolderListW ELTAPIENTRY ExGetFolderFilePathW(const WCHAR* directoryPath);



//extern DECLSPEC FolderListW ELTAPIENTRY ExGetFolderFileNameW(const WCHAR* directoryPath);

//extern DECLSPEC FolderListA ELTAPIENTRY ExGetFolderFileNameA(const char* directoryPath);

//-------------------------------------------------------------------
/* Get All possiable File Name in Specified Folder Location as a Relative Path. */
//extern DECLSPEC FolderListW ELTAPIENTRY ExGetFolderDirectoryPathW(const WCHAR* directoryPath);

//-------------------------------------------------------------------
/* Get All possiable File Name in Specified Folder Location as a Relative Path. */
//extern DECLSPEC FolderListA ELTAPIENTRY ExGetFolderDirectoryPathA(const char* directoryPath);

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
#endif