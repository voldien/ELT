/*
===========================================================================
Copyright (C) 2014 BroodCity Software, Inc. Voldemor2009@hotmail.com

*/
#ifndef WIN_NET_H
#define WIN_NET_H
#include"./../../EngineAssembly.h"
#ifdef EX_WINDOWS
#ifdef INTERNAL_ENGINEX

#endif
#define EX_DEFAULT_PORT "27015"
#ifdef __cplusplus // C++ environment
extern "C"{
#endif
extern WSADATA winsocket;

extern DECLSPEC ERESULT ELTAPIENTRY ExInitNet(Uint32 flag);

extern DECLSPEC ERESULT ELTAPIENTRY ExCreatServer(const char* ip, const char* port);

extern DECLSPEC ExBoolean ELTAPIENTRY ExRelaseNet(void);


#ifdef EX_CPP
}
#endif

#endif
#endif
