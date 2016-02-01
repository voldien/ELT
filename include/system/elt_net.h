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
#include <stdio.h>
#include <stdlib.h>
#include"./../EngineAssembly.h"

typedef signed int ExSocket;


/*TODO rename ELT to EX.	*/
#define ELT_CLIENT 0x1  	/*  Client socket*/
#define ELT_TCP 0x2     	/*  reliable,  two-way  */
#define ELT_UDP 0x4     	/*  UDP protocol */
#define ELT_LOCAL 0x8   	/*  Local internal communication */
#define ELT_STREAM 0x10		/**/
#define ELT_DGRAM 0x20		/**/

#ifdef  __cplusplus	/*	C++ Environment	*/
extern "C" {
#endif


/*
 *	Open socket
 *	\ip
 *	\port
 *	\protocol
 *	@return
*/
extern DECLSPEC ExSocket ELTAPIENTRY ExOpenSocket(unsigned int protocol);

/*
 *	Close socket
 *	\socket
 *	@return
*/
extern DECLSPEC unsigned int ELTAPIENTRY ExCloseSocket(ExSocket socket);

/*
 *	Bind socket to ip and port address
 *	\ip
 *	\port
 *	\socket
 *	@return
*/
extern DECLSPEC ExSocket ELTAPIENTRY ExBindSocket(const char* ip, unsigned int port, ExSocket socket);

/*
 *	Connect to socket
 *	\ip
 *	\port
 *	@return socket
*/
extern DECLSPEC ExSocket ELTAPIENTRY ExConnectSocket(const char* ip, unsigned int port);

/*
 *    Listen
*/
#define ExListen    listen

/*
 *	Read Socket data
 *	\socket
 *	\buffer
 *	\size
 *	@return
 */
#ifdef EX_LINUX
	#define ExReadSocket read
#elif defined(EX_WINDOWS)
	#define ExReadSocket recive
#endif

/*
 *	Write Socket data
 *	\socket
 *	\buffer
 *	\size
 *	@return
 */
#ifdef EX_LINUX
	#define ExWriteSocket read
#elif defined(EX_WINDOWS)
	#define ExWriteSocket send
#endif

/*
 *	Get host name to ip adress.
 *	@return
 */
extern DECLSPEC int ELTAPIENTRY ExGetHostIp(char* host);


#ifdef  __cplusplus	/* C++ Environment */
}
#endif


#endif
