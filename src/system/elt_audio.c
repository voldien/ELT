#include"system/elt_audio.h"
#ifdef EX_WINDOWS
#elif defined(EX_LINUX)
#   include<alsa/asoundlib.h>
#endif

HANDLE audiodriver;

DECLSPEC ERESULT ELTAPIENTRY ExAudioInit(const char* driver_name){
	ERESULT hr;
	if(!driver_name)return 0;

	if(!strcmp(driver_name, "asound")){
        HANDLE handle;

        if(!ExIsModuleLoaded("libasound.so"))
        	ExLoadLibrary("libasound.so");



        //snd_pcm_open(0,0,0,0);

	}
    else if(!strcmp(driver_name,"pulseaudio")){

    }
	return hr;
}
