/*
===========================================================================
Copyright (C) 2014 BroodCity Software, Inc. Voldemor2009@hotmail.com

*/
#ifndef ELT_NET_H
#define ELT_NET_H
#include"./../EngineAssembly.h"

#define ELT_TCP 0x1 /*  reliable,  two-way  */
#define ELT_UDP 0x2 /**/
/*
*/
extern DECLSPEC unsigned int ELTAPIENTRY ExOpenSocket(const char* ip, unsigned int port,unsigned int protocol);

/*
*/
extern DECLSPEC unsigned int ELTAPIENTRY ExCloseSocket(unsigned int socket);
/**
    Connect to socket
*/
extern DECLSPEC unsigned int ELTAPIENTRY ExConnectSocket(const char* ip, unsigned int port);

/**
*/

/*

*/
extern DECLSPEC int ELTAPIENTRY ExReadSocket(unsigned int socket, unsigned int* data,unsigned size);
/*

*/
extern DECLSPEC int ELTAPIENTRY ExWriteSocket(unsigned int socket, unsigned int* data,unsigned size);



#endif
