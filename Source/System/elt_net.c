#include"elt_net.h"
#if defined(EX_LINUX)
#   include<sys/types.h>
#   include<sys/socket.h>
#   include<netinet/in.h>
#   include<errno.h>
#   include<netdb.h>
#elif defined(EX_WINDOWS)
#pragma comment(lib,"Ws2_32.lib")
#	include<WinSock.h>
WSADATA wsadata = {0};
#endif // EX_WINDOWS

// http://www.linuxhowtos.org/data/6/server.c

DECLSPEC unsigned int ELTAPIENTRY ExOpenSocket(const char* ip, unsigned int port,unsigned int protocol){
    #ifdef EX_WINDOWS
    unsigned int sockfd,newsockdf;
    unsigned int sock_domain,socket_protocol;
    SOCKADDR_IN serv_addr, cli_addr;

	if(wsadata.wVersion != 0x0202)
		WSAStartup(0x0202, &wsadata);


	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	serv_addr.sin_addr.S_un.S_addr = inet_addr(ip);

	sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if(bind(0,(struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0){
		fprintf(stderr,strerror(errno));
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

    bzero(&serv_addr,sizeof(serv_addr));

    serv_addr.sin_family = sock_domain;
    serv_addr.sin_addr.s_addr = inet_addr(ip);
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
	gethostbyname(ip);

	return 0 ;
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

