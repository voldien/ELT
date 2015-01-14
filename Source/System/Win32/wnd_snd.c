#include"wnd_snd.h"
#ifdef EX_WINDOWS
	#include<BaseTsd.h>
	#include<dinput.h>
	#include<dinputd.h>
	#include<Xinput.h>
	#include<Dbt.h>
	#include<oleauto.h>
	#include<shellapi.h>
	#pragma warning( disable : 4996 ) // disable deprecated warning 
	#pragma comment(lib, "dinput8.lib")
LPDIRECTSOUND8 pDS = EX_NULL;
	
DECLSPEC ERESULT ELTAPIENTRY ExInitDirectSound(ExWin hWnd, Uint32 flag){
	ERESULT hr;

	CoInitializeEx(NULL,COINIT_MULTITHREADED);
	/*
	if(FAILED(hr = DirectSoundCreate8(EX_NULL, &pDS,EX_NULL))){
		ExDevPrintf("Failed to Create DirectSound %s", ExGetHResultErrorMessage(hr));
	}
	if(FAILED( hr = pDS->SetCooperativeLevel(hWnd, DSSCL_PRIORITY))){
		ExDevPrintf("Failed to Set Cooperative Level on DirectSound %s", ExGetHResultErrorMessage(hr));
	}
	*/
	return hr;
}


DECLSPEC void ELTAPIENTRY ExReleaseDirectSound(void){
/*	ERESULT hr;
	if(pDS)
		if(FAILED(hr = pDS->Release()))
			wExDevPrintf(EX_TEXT("Failed to Release DirectSound"), ExGetHResultErrorMessage(hr));*/
}
#endif
