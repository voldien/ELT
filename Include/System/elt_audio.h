/*
===========================================================================
Copyright (C) 2014 BroodCity Software, Inc. Voldemor2009@hotmail.com

*/
#ifndef ELT_AUDIO_H
#define ELT_AUDIO_H
#include"./../EngineAssembly.h"
#ifdef __cplusplus	// C++ Environment
extern "C"{
#endif

extern DECLSPEC ERESULT ELTAPIENTRY ExAudioInit(const char* driver_name);

extern DECLSPEC ERESULT ELTAPIENTRY ExAudioQuit(void);

extern DECLSPEC const char* ELTAPIENTRY ExGetAudioDriver(Int32 index);

extern DECLSPEC void ELTAPIENTRY ExGetAudioStatus(void);
extern DECLSPEC const char* ELTAPIENTRY ExGetCurrentAudioDriver(void);
extern DECLSPEC void ELTAPIENTRY EXGetNumAudioDevices(void);
extern DECLSPEC void ELTAPIENTRY EXGetNumAudioDriver(void);


#ifdef __cplusplus	// C++ Environment
}
#endif
#endif