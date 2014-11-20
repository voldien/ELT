/*
===========================================================================
Copyright (C) 2014 BroodCity Software, Inc. Voldemor2009@hotmail.com

*/
#ifndef WIN_NET_H
#define WIN_NET_H
#include"./../../EngineAssembly.h"
#ifdef EX_WINDOWS
#ifdef INTERNAL_ENGINEX
	#include<WinInet.h>
	#include<WinSock.h>
	//#include<WS2tcpip.h>
	//#include<IPHlpApi.h>
	#pragma comment(lib, "Ws2_32.lib")
	#pragma comment(lib,"wininet")
#endif
#define EX_DEFAULT_PORT "27015"
#ifdef EX_CPP
extern "C"{
#endif
extern WSADATA winsocket;

DECLSPEC ERESULT ELTAPIENTRY ExInitNet(Uint32 flag);

DECLSPEC ERESULT ELTAPIENTRY ExCreatServer(const char* ip, const char* port);

DECLSPEC Boolean ELTAPIENTRY ExRelaseNet(Void);


#ifdef EX_CPP
}
#endif

#endif
#endif