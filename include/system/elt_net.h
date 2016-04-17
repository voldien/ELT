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

/*
 *
 */
typedef signed int ExSocket;

/*
 *
 */
#define EX_CLIENT 	0x1  		/*  Client socket*/
#define EX_TCP 		0x2     	/*  Reliable,  two-way  */
#define EX_UDP 		0x4     	/*  UDP protocol */
#define EX_LOCAL 	0x8   		/*  Local internal communication */
#define EX_STREAM 	0x10		/*		*/
#define EX_DGRAM 	0x20		/*		*/
#define EX_INET4
#define EX_INET6

#ifdef  __cplusplus	/*	C++ Environment	*/
extern "C" {
#endif


/*
 *	Open socket
 *	\ip
 *	\port
 *	\protocol
 *	@Return
*/
extern ELTDECLSPEC ExSocket ELTAPIENTRY ExOpenSocket(unsigned int protocol);

/*
 *
 * 	@Return
 */
extern ELTDECLSPEC ExSocket ELTAPIENTRY ExCreateSocket(unsigned int domain, unsigned int style, unsigned int protocal);

/*
 *	Close socket
 *	\socket
 *	@Return
*/
extern ELTDECLSPEC unsigned int ELTAPIFASTENTRY ExCloseSocket(ExSocket socket);

/*
 *	Bind socket to ip and port address
 *	\ip
 *	\port
 *	\socket
 *	@Return
*/
extern ELTDECLSPEC ExSocket ELTAPIENTRY ExBindSocket(const ExChar* ip, unsigned int port, ExSocket socket);

/*
 *	Connect to socket
 *	\ip
 *	\port
 *	@Return socket
*/
extern ELTDECLSPEC ExSocket ELTAPIENTRY ExConnectSocket(const ExChar* ip, unsigned int port);




/*
 *    Listen
 *    @Return
 */
#define ExListen    listen

/*
 *	Read Socket data
 *	\socket
 *	\buffer
 *	\size
 *	@Return
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
 *	@Return
 */
#ifdef EX_LINUX
	#define ExWriteSocket send
#elif defined(EX_WINDOWS)
	#define ExWriteSocket send
#endif

/*
 *
 * @Return
 */
extern ELTDECLSPEC const ExChar* ELTAPIENTRY ExGetHostName(const ExChar* hostname);


/*
 *
 */
extern ELTDECLSPEC ExChar* ELTAPIENTRY ExGetInterfaceAddr(const ExChar* interface, ExChar* addr, Uint len);

#ifdef  __cplusplus	/* C++ Environment */
}
#endif


#endif
