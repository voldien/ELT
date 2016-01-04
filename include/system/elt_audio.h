/**
    ELT (Engine Library Toolkit) is a multi platform engine toolkit
    Copyright (C) 2014  Valdemar Lindberg

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/
#ifndef _ELT_AUDIO_H_
#define _ELT_AUDIO_H_ 1
#include"./../EngineAssembly.h"

#ifdef  __cplusplus	/* C++ Environment */
extern "C"{
#endif

/*
 *
 */
extern DECLSPEC ExAudioContext ELTAPIENTRY ExAudioInit(const char* driverName);

/*
 *
 */
extern DECLSPEC ERESULT ELTAPIENTRY ExAudioQuit(void);

/*
 *
 */
extern DECLSPEC ERESULT ELTAPIENTRY ExAudioWrite(const void* data);

/*
 *
 */
extern DECLSPEC ERESULT ELTAPIENTRY ExAudioRead(void* data);

/**/
extern DECLSPEC const char* ELTAPIENTRY ExGetAudioDriver(Int32 index);

/**/
extern DECLSPEC void ELTAPIENTRY ExGetAudioStatus(void);

/**/
extern DECLSPEC const char* ELTAPIENTRY ExGetCurrentAudioDriver(void);

/**/
extern DECLSPEC int ELTAPIENTRY ExGetNumAudioDevices(void);

/**/
extern DECLSPEC int ELTAPIENTRY ExGetNumAudioDriver(void);


#ifdef  __cplusplus	/* C++ Environment */
}
#endif

#endif
