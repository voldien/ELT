#include"wnd_filedialog.h"
#ifdef EX_WINDOWS
DECLSPEC Boolean ELTAPIENTRY ExCreateOpenDialog(ExChar* path){
	// zero memory 
	OPENFILENAME openfile = {0};
	openfile.lStructSize = SIZEOF(OPENFILENAME);
	openfile.hwndOwner = EX_NULL;
	// file type
	openfile.lpstrFilter = TEXT("All\0*.*\0Text\0*.TXT\0");
	openfile.lpstrFile = path;
	openfile.lpstrFile[0] = '\0';
	openfile.nFilterIndex = 1;
	openfile.nMaxFile = MAX_PATH;
	openfile.nMaxFileTitle = 0;
	openfile.lpstrInitialDir = EX_NULL;
	openfile.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST |OFN_NOCHANGEDIR;
	return GetOpenFileName(&openfile);
}
DECLSPEC Boolean ELTAPIENTRY ExCreateOpenDialog2(ExFileDialog* exFileDialog){
	OPENFILENAME openfile = {0};
	openfile.lStructSize = SIZEOF(OPENFILENAME);
	openfile.hwndOwner = exFileDialog->hWnd;
	// file type
	openfile.lpstrFilter = exFileDialog->filefilter;
	openfile.lpstrFile = exFileDialog->filePath;
	openfile.lpstrFile[0] = '\0';
	openfile.nFilterIndex = 1;
	openfile.nMaxFile = MAX_PATH;
	openfile.nMaxFileTitle = 25;
	openfile.lpstrInitialDir = EX_NULL;
	openfile.lpstrTitle = exFileDialog->lpTitle;
	openfile.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST |OFN_NOCHANGEDIR | OFN_EXPLORER | OFN_ALLOWMULTISELECT;

	if(GetOpenFileName(&openfile)){
		// succed

		return TRUE;
	}
	else{
		wExDevPrintf(TEXT("Failed to Create Open Dialog : [Error] %s"), ExGetErrorMessage(CommDlgExtendedError()));
		return FALSE;
	}
}

DECLSPEC Boolean ELTAPIENTRY ExCreateSaveDialog(ExChar* path){
	OPENFILENAME savefile;
	memset(&savefile,0,SIZEOF(OPENFILENAME));
	savefile.lStructSize = SIZEOF(OPENFILENAME);
	savefile.hwndOwner = EX_NULL;
	savefile.hInstance = GetModuleHandle(EX_NULL);
	savefile.lpstrFilter = TEXT("All\0*.*\0Text\0*.TXT\0");
	savefile.lpstrFile = path;
	savefile.lpstrFile[0] = '\0';
	savefile.nFilterIndex = 1;
	savefile.nMaxFile = MAX_PATH;
	savefile.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST |OFN_NOCHANGEDIR;
	return GetSaveFileName(&savefile);
}

DECLSPEC Boolean ELTAPIENTRY ExCreateSaveDialog2(ExFileDialog* exFileDialog){
	OPENFILENAME savefile;
	memset(&savefile,0,SIZEOF(OPENFILENAME));
	savefile.lStructSize = SIZEOF(OPENFILENAME);
	savefile.hwndOwner = exFileDialog->hWnd;
	savefile.hInstance = GetModuleHandle(EX_NULL);
	savefile.lpstrFilter = exFileDialog->filefilter;
	savefile.lpstrFile = exFileDialog->filePath;
	savefile.lpstrFile[0] = '\0';
	savefile.nFilterIndex = 1;
	savefile.nMaxFile = MAX_PATH;
	savefile.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST |OFN_NOCHANGEDIR;
	return GetSaveFileName(&savefile);
}

DECLSPEC Boolean ELTAPIENTRY ExCreateFontDialog(Void){
	CHOOSEFONT fontdlg = {0};
	fontdlg.lStructSize = sizeof(fontdlg);
	return ChooseFont (&fontdlg);
}

DECLSPEC Boolean ELTAPIENTRY ExCreateColorDialog(ExWin owner,Uint8 colour[4]){
	COLORREF acrCustClr[16];
	CHOOSECOLOR chcolour = {0};
	chcolour.hwndOwner = owner;
	chcolour.lStructSize = sizeof(CHOOSECOLOR);
	chcolour.Flags = CC_ANYCOLOR | CC_FULLOPEN | CC_RGBINIT;
	chcolour.lpCustColors = acrCustClr;
	if(ChooseColor(&chcolour)){
		memcpy(colour,&chcolour.rgbResult, SIZEOF(colour));
		return TRUE;
	}else return FALSE;
}

#endif