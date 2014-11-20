/*
===========================================================================
Copyright (C) 2014 BroodCity Software, Inc. Voldemor2009@hotmail.com

*/
#ifndef WND_FILE_DIALOG_H
#define WND_FILE_DIALOG_H
#include"./../../ExPreProcessor.h"
#include"win_win32.h"
#ifdef EX_CPP
extern "C"{
#endif
typedef struct ex_file_dialog{
	// owner hwnd.
	ExWin hWnd;
	ExChar* filefilter;
	ExChar* filePath;
	ExChar* lpTitle;
}ExFileDialog;

/*		Create Default Open Dialog	*/
extern DECLSPEC Boolean ELTAPIENTRY ExCreateOpenDialog(ExChar* path);
/*		Create Custum Open Dialog	*/
extern DECLSPEC Boolean ELTAPIENTRY ExCreateOpenDialog2(ExFileDialog* exFileDialog);

extern DECLSPEC Boolean ELTAPIENTRY ExCreateMultiOpenDialog(ExChar* path);

extern DECLSPEC Boolean ELTAPIENTRY ExCreateSaveDialog(ExChar* path);
extern DECLSPEC Boolean ELTAPIENTRY ExCreateSaveDialog2(ExFileDialog* exFileDialog);

extern DECLSPEC Boolean ELTAPIENTRY ExCreateMultiSaveDialog(ExChar* path);





#ifdef EX_CPP
}
#endif
#endif