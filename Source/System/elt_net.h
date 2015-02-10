/*
========================================================================
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
#ifndef ELT_NET_H
#define ELT_NET_H
#include"./../EngineAssembly.h"

#define ELT_CLIENT 0x1  /*  Client socket*/
#define ELT_TCP 0x2     /*  reliable,  two-way  */
#define ELT_UDP 0x4     /*  UDP protocol */
#define ELT_LOCAL 0x8   /*  Local inter communication */

#ifdef __cplusplus  //  C++ Environment
extern "C" {
#endif
/**
    Open socket
    \
    \
    \
*/
extern DECLSPEC unsigned int ELTAPIENTRY ExOpenSocket(const char* ip, unsigned int port,unsigned int protocol);

/**
    Close socket
*/
extern DECLSPEC unsigned int ELTAPIENTRY ExCloseSocket(unsigned int socket);

/**

*/
extern DECLSPEC unsigned int ELTAPIENTRY ExBindSocket(const char* ip, unsigned int port,unsigned int socket);

/**
    Connect to socket
*/
extern DECLSPEC unsigned int ELTAPIENTRY ExConnectSocket(const char* ip, unsigned int port);

/**

*/
//extern DECLSPEC unsigned int ELTAPIENTRY ExNetListen(unsigned int socket,unsigned int blog);

/**
    Read Socket data
*/
extern DECLSPEC int ELTAPIENTRY ExReadSocket(unsigned int socket, unsigned char* data,unsigned size);
/**
    Write Socket data
*/
extern DECLSPEC int ELTAPIENTRY ExWriteSocket(unsigned int socket, unsigned char* data,unsigned size);

/**
*/
extern DECLSPEC int ELTAPIENTRY ExGetHostIp(char ip[15]);


#ifdef __cplusplus
}
#endif


#endif
