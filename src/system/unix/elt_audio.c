#include"system/elt_audio.h"
#include<AL/al.h>
#include<AL/alc.h>

#ifdef EX_WINDOWS
#elif defined(EX_LINUX)
#	include <alsa/asoundlib.h>
#	include <stdio.h>
#endif

#define PCM_DEVICE "default"

ALCcontext *alContext;
ALCdevice *alDevice;

DECLSPEC ExAudioContext ELTAPIENTRY ExAudioInit(const char* cDriverName){
	ERESULT hr;

	alDevice = alcOpenDevice(cDriverName);

	if(alDevice){



		ALfloat listenerPos[]={0.0,0.0,0.0};
		ALfloat listenerVel[]={0.0,0.0,0.0};
		ALfloat	listenerOri[]={0.0,0.0,-1.0, 0.0,1.0,0.0};	// Listener facing into the screen



		alContext = alcCreateContext(alDevice, NULL);

		if(alContext){
			alcMakeContextCurrent(alContext);

			alListenerfv(AL_POSITION,listenerPos); 	// Position ...
			alListenerfv(AL_VELOCITY,listenerVel); 	// Velocity ...
			alListenerfv(AL_ORIENTATION,listenerOri); 	// Orientation ...
			alListenerf(AL_GAIN, 1.0f * 0.01f);
		}
	}

	/*
	if(!strcmp(cDriverName, "asound")){


        HANDLE handle;
		unsigned int pcm;
		int rate, channels, seconds;
#ifdef EX_LINUX
		snd_pcm_t *pcm_handle;
		snd_pcm_hw_params_t *params;
		snd_pcm_uframes_t frames;

        if(!ExIsModuleLoaded("libasound.so"))
        	ExLoadLibrary("libasound.so");



        if( ( audiodriver = snd_pcm_open(&pcm_handle,PCM_DEVICE,SND_PCM_STREAM_PLAYBACK,0) ) < 0){

        }
        audiodriver = pcm_handle;


        rate = 44100;
        channels = 1;

        snd_pcm_hw_params_alloca(&params);

        snd_pcm_hw_params_any(pcm_handle,params);

        if(pcm = snd_pcm_hw_params_set_access(pcm_handle, params,SND_PCM_ACCESS_RW_INTERLEAVED) < 0){
        }
        if (pcm = snd_pcm_hw_params_set_format(pcm_handle, params,
        						SND_PCM_FORMAT_S16_LE) < 0)
        		printf("ERROR: Can't set format. %s\n", snd_strerror(pcm));

		if (pcm = snd_pcm_hw_params_set_channels(pcm_handle, params, channels) < 0)
			printf("ERROR: Can't set channels number. %s\n", snd_strerror(pcm));

		if (pcm = snd_pcm_hw_params_set_rate_near(pcm_handle, params, &rate, 0) < 0)
			printf("ERROR: Can't set rate. %s\n", snd_strerror(pcm));

		if (pcm = snd_pcm_hw_params(pcm_handle, params) < 0)
			printf("ERROR: Can't set harware parameters. %s\n", snd_strerror(pcm));

#endif
		return audiodriver;
	}
    else if(!strcmp(cDriverName,"pulseaudio")){

    }
    */
	return alContext;
}

DECLSPEC ERESULT ELTAPIENTRY ExAudioQuit(void){

	alcMakeContextCurrent(NULL);
	alcDestroyContext(alContext);
	//Close device
	alcCloseDevice(alDevice);
}


DECLSPEC int ELTAPIENTRY ExGetNumAudioDevices(void){
	const ALCchar *devices  = alcGetString(NULL, ALC_DEVICE_SPECIFIER);

}
DECLSPEC int ELTAPIENTRY ExGetNumAudioDriver(void){

}



