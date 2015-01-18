#include"elt_net.h"
#if defined(EX_LINUX)   /*  Linux network*/
#   include<sys/types.h>
#   include<sys/socket.h>
#   include<netinet/in.h>
#   include<errno.h>
#   include<netdb.h>
#elif defined(EX_WINDOWS)   /*  Windows network*/
#	pragma comment(lib,"Ws2_32.lib")
#	pragma comment(lib,"wininet")
#	include<WinInet.h>
#	include<WinSock.h>
//#	include<WS2tcpip.h>

WSADATA wsadata = {0};
#define EX_WSA_VERSION MAKEWORD(2,2)
static int init_wsa(void){
	if(wsadata.wVersion != EX_WSA_VERSION){
		if(!WSAStartup(EX_WSA_VERSION, &wsadata))return -1;
	}
}
#elif defined(EX_ANDROID)

#endif // EX_WINDOWS

// http://www.linuxhowtos.org/data/6/server.c

DECLSPEC unsigned int ELTAPIENTRY ExOpenSocket(const char* ip, unsigned int port,unsigned int protocol){
    #ifdef EX_WINDOWS
    unsigned int sockfd,newsockdf;
    unsigned int sock_domain,socket_protocol;
    SOCKADDR_IN serv_addr, cli_addr;

	if(wsadata.wVersion != EX_WSA_VERSION){
		if(WSAStartup(EX_WSA_VERSION, &wsadata))return -1;
	}


	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	serv_addr.sin_addr.S_un.S_addr = inet_addr(ip);

	sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(protocol & ELT_CLIENT)
		return sockfd;

	if(bind(sockfd,(SOCKADDR *)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR){
		wprintf(EX_TEXT("connect function failed with error: %ld\n"), WSAGetLastError());
	}
	return sockfd;

    #elif defined(EX_LINUX)

    unsigned int sockfd,newsockdf;
    unsigned int sock_domain,socket_protocol;
    struct sockaddr_in serv_addr, cli_addr;
    //struct sockaddr_un name;

    if(protocol & ELT_LOCAL){
        sock_domain = PF_LOCAL;
        socket_protocol = 0;
    }
    else{
        socket_protocol = 0;
        sock_domain = AF_INET;
    }
    /**
        create socket
    */
    if(protocol & ELT_LOCAL){
        if((sockfd = socket(sock_domain, SOCK_STREAM, socket_protocol)) == -1)
            fprintf(stderr,strerror(errno));
        if(protocol & ELT_CLIENT)
            return sockfd;
    }
    else if(protocol & ELT_CLIENT){

        if((sockfd = socket(sock_domain, SOCK_STREAM, socket_protocol)) == -1)
            fprintf(stderr,strerror(errno));
        return sockfd;
    }
    else if(protocol & ELT_TCP){
        socket_protocol = 0;
        if((sockfd = socket(sock_domain, SOCK_STREAM, socket_protocol)) == -1)
            fprintf(stderr,strerror(errno));
    }
    else if(protocol & ELT_UDP){
        socket_protocol = 0;
        if((sockfd = socket(sock_domain, SOCK_DGRAM, socket_protocol)) == -1)
            fprintf(stderr,strerror(errno));
    }
    else{
        if((sockfd = socket(sock_domain, SOCK_STREAM, socket_protocol)) == -1)
            fprintf(stderr,strerror(errno));
    }

    bzero((char*)&serv_addr,sizeof(serv_addr));
	
    serv_addr.sin_family = sock_domain;
    serv_addr.sin_addr.s_addr = inet_addr(ip);
	inet_pton(sock_domain,ip, &serv_serv.sin_addr);
    //serv_addr.sin_addr.s_addr = INADDR_ANY;

    serv_addr.sin_port = htons(port);
    if(bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0){
        fprintf(stderr,strerror(errno));
        //return -1;
    }

    return sockfd;
    #endif
}

DECLSPEC unsigned int ELTAPIENTRY ExCloseSocket(unsigned int socket){
    #ifdef EX_WINDOWS
	return closesocket((SOCKET)socket);
    #elif defined(EX_LINUX)
    return close(socket);
    #endif

}

DECLSPEC unsigned int ELTAPIENTRY ExConnectSocket(const char* ip, unsigned int port){
    #ifdef EX_WINDOWS
    SOCKADDR_IN serv_addr;
    struct hostent *server;
    int sockfd;/**TODO check if sockdf should be input parameter*/

	if(wsadata.wVersion != EX_WSA_VERSION)
		WSAStartup(EX_WSA_VERSION, &wsadata);

    sockfd = ExOpenSocket(ip,port,ELT_CLIENT);
	server = gethostbyname(ip);


	serv_addr.sin_port = htons(port);
	serv_addr.sin_family = server->h_addrtype; /*AF_INET;*/
	serv_addr.sin_addr.S_un.S_addr = inet_addr(ip);

    if(connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))  == SOCKET_ERROR){
		wprintf(EX_TEXT("connect function failed with error: %ld\n"), WSAGetLastError());
	}
        fprintf(stderr,strerror(errno));

	return sockfd ;
    #elif defined(EX_LINUX)
    struct sockaddr_in serv_addr;
    struct hostent *server;
    int sockfd;/**TODO check if sockdf should be input parameter*/
    /**/
    sockfd = ExOpenSocket(ip,port,ELT_CLIENT);
    //sockfd = socket(AF_INET, SOCK_STREAM, 0);


    bzero((char*)&serv_addr, sizeof(serv_addr));
    server = gethostbyname(ip);/*get host information by ip name or ip explicitly*/

    serv_addr.sin_family = server->h_addrtype; /*AF_INET;*/

    bcopy((char*)server->h_addr,
         (char*)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(port);

    if(connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
        fprintf(stderr,strerror(errno));

    return sockfd;
    #endif
}

