#include"system/win/wnd_snd.h"
#ifdef EX_WINDOWS
	#include<basetsd.h>
	#include<dinput.h>
	//#include<dinputd.h>
	#include<xinput.h>
	#include<dbt.h>
	#include<oleauto.h>
	#include<shellapi.h>
	#pragma warning( disable : 4996 ) // disable deprecated warning 
	#pragma comment(lib, "dinput8.lib")
LPDIRECTSOUND8 pDS = NULL;
	
DECLSPEC ERESULT ELTAPIENTRY ExInitDirectSound(ExWin hWnd, Uint32 flag){
	ERESULT hr;

	CoInitializeEx(NULL,COINIT_MULTITHREADED);
	/*
	if(FAILED(hr = DirectSoundCreate8(NULL, &pDS,NULL))){
		ExDevPrintf("Failed to Create DirectSound %s", ExGetHResultErrorMessage(hr));
	}
	if(FAILED( hr = pDS->SetCooperativeLevel(hWnd, DSSCL_PRIORITY))){
		ExDevPrintf("Failed to Set Cooperative Level on DirectSound %s", ExGetHResultErrorMessage(hr));
	}
	*/
	return hr;
}

#endif
