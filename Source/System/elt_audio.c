#include"elt_audio.h"
#ifdef EX_WINDOWS
#elif defined(EX_LINUX)
#   include<alsa/asoundlib.h>
#endif

DECLSPEC ERESULT ELTAPIENTRY ExAudioInit(const char* driver_name){
	ERESULT hr;
	if(!driver_name)return 0;
	if(!strcmp(driver_name, "")){
        #ifdef EX_WINDOWS
            ExLoadLibrary("libdl.so");
            snd_pcm_open(0,0,0,0);
        #elif defined(EX_LINUX)
        #endif // EX_WINDOWS
	}

	return hr;
}
