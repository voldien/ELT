/*
===========================================================================
Copyright (C) 2014 BroodCity Software, Inc. Voldemor2009@hotmail.com

*/
#ifndef WND_FILE_DIALOG_H
#define WND_FILE_DIALOG_H
#include"./../../ExPreProcessor.h"
#include"win_win32.h"
#ifdef __cplusplus // C++ environment
extern "C"{
#endif
typedef struct ex_file_dialog{
	// owner hwnd.
	ExWin hWnd;
	const ExChar* filefilter;
	ExChar* filePath;
	const ExChar* lpTitle;
}ExFileDialog;

/*
	//	Create Default Open Dialog
*/
extern DECLSPEC ExBoolean ELTAPIENTRY ExCreateOpenDialog(ExChar* path);
/*
	//	Create Custum Open Dialog
*/
extern DECLSPEC ExBoolean ELTAPIENTRY ExCreateOpenDialog2(ExFileDialog* exFileDialog);

extern DECLSPEC ExBoolean ELTAPIENTRY ExCreateMultiOpenDialog(ExChar* path);

extern DECLSPEC ExBoolean ELTAPIENTRY ExCreateSaveDialog(ExChar* path);
extern DECLSPEC ExBoolean ELTAPIENTRY ExCreateSaveDialog2(ExFileDialog* exFileDialog);
/*
	//	Choose Font
*/
extern DECLSPEC ExBoolean ELTAPIENTRY ExCreateFontDialog(void);



extern DECLSPEC ExBoolean ELTAPIENTRY ExCreateMultiSaveDialog(ExChar* path);
/*
	
*/
extern DECLSPEC ExBoolean ELTAPIENTRY ExCreateColorDialog(ExWin owner,Uint8 colour[4]);



#ifdef __cplusplus // C++ environment
}
#endif
#endif