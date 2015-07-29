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
#ifndef _ELT_NET_H_
#define _ELT_NET_H_ 1
#include"./../EngineAssembly.h"

#define ELT_CLIENT 0x1  	/*  Client socket*/
#define ELT_TCP 0x2     	/*  reliable,  two-way  */
#define ELT_UDP 0x4     	/*  UDP protocol */
#define ELT_LOCAL 0x8   	/*  Local internal communication */
#define ELT_STREAM 0x10
#define ELT_S 0x20

#ifdef __cplusplus  //  C++ Environment
extern "C" {
#endif


/**
    Open socket
    \ip
    \port
    \protocol
*/
extern DECLSPEC unsigned int ELTAPIENTRY ExOpenSocket(unsigned int protocol);

/**
	Close socket
	\socket
	@return
*/
extern DECLSPEC unsigned int ELTAPIENTRY ExCloseSocket(unsigned int socket);

/**
	Bind socket to ip and port address
	\ip
	\port
	\socket
	@return
*/
extern DECLSPEC unsigned int ELTAPIENTRY ExBindSocket(const char* ip, unsigned int port,unsigned int socket);

/**
	Connect to socket
	\ip
	\port
	@return socket
*/
extern DECLSPEC unsigned int ELTAPIENTRY ExConnectSocket(const char* ip, unsigned int port);

/**
    Listen
*/
#define ExListen    listen
/**
	Read Socket data
	\socket
	\buffer
	\size
	@return
*/
extern DECLSPEC int ELTAPIENTRY ExReadSocket(unsigned int socket, unsigned char* buffer,unsigned size);
//#define ExReadSocket read
/**
	Write Socket data
	\socket
	\buffer
	\size
	@return
*/
extern DECLSPEC int ELTAPIENTRY ExWriteSocket(unsigned int socket, unsigned char* data,unsigned size);
//#define ExWriteSocket write

/*
	Get host ip adress.
*/
extern DECLSPEC int ELTAPIENTRY ExGetHostIp(char ip[16]);


#ifdef __cplusplus
}
#endif


#endif
