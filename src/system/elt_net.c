#include"system/elt_net.h"
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

#if defined(EX_PNACL)
#   include<sys/types.h>
#   include<sys/socket.h>
#   include<netinet/in.h>
//#   include<sys/un.h>       /*  sockaddr_un   */
#   include<arpa/inet.h>
#   include<sys/ioctl.h>
#   include<errno.h>
#   include<netdb.h>
#   include<unistd.h>
#elif defined(EX_UNIX)   /*  Linux network and android*/
#   include<sys/types.h>
#   include<sys/socket.h>
#   include<netinet/in.h>
#   include<sys/un.h>       /*  sockaddr_un   */
#   include<arpa/inet.h>
#   include<sys/ioctl.h>
#   include<errno.h>
#   include<netdb.h>
#   include<unistd.h>
#   include<net/if.h>
#elif defined(EX_WINDOWS)   /*  Windows network*/
#	pragma comment(lib,"Ws2_32.lib")
#	pragma comment(lib,"wininet")
#	include<windows.h>
#	include<wininet.h>
#	include<winsock.h>

WSADATA wsadata = {0};
#define EX_WSA_VERSION MAKEWORD(2,2)
static int inline init_wsa(void){  /*  initialize was*/
	if(wsadata.wVersion != EX_WSA_VERSION){
		if(!WSAStartup(EX_WSA_VERSION, &wsadata))return -1;
	}
}


#endif // EX_WINDOWS



#if defined(EX_UNIX)   /*  Linux network and android*/
#   include<errno.h>
#   include<unistd.h>
#endif





// http://www.linuxhowtos.org/data/6/server.c


/*
	create ip address on current machine
*/
static int inline create_ip_address(const char* ip, unsigned int port){
#ifdef EX_WINDOWS

	return 1;
#elif defined(EX_UNIX)
	/*	todo resolver later!*/
    //struct ifreq ifr = {0};

	/*
	strncpy(ifr.ifr_name, "eth1", IFNAMSIZ);
    ifr.ifr_addr.sa_family = AF_INET;
    inet_pton(AF_INET, ip, ifr.ifr_addr.sa_data + 2);
    ioctl(sockfd, SIOCSIFADDR, &ifr);

    inet_pton(AF_INET, "255.255.0.0", ifr.ifr_addr.sa_data + 2);
    ioctl(sockfd, SIOCSIFNETMASK, &ifr);

    ioctl(sockfd, SIOCGIFFLAGS, &ifr);

    ifr.ifr_flags |= (IFF_UP | IFF_RUNNING);

    ioctl(sockfd, SIOCSIFFLAGS, &ifr);
*/
	return 1;
#endif

}

static int ip_exists(const char* ip){
	struct hostent* host;
	host = gethostbyname(ip);
	if(!host)
		return FALSE;
	return TRUE;
}


DECLSPEC unsigned int ELTAPIENTRY ExOpenSocket(unsigned int protocol){
    #ifdef EX_WINDOWS
    unsigned int sockfd,newsockdf;
    unsigned int sock_domain,socket_protocol;
    SOCKADDR_IN serv_addr, cli_addr;

	if(wsadata.wVersion != EX_WSA_VERSION){
		if(WSAStartup(EX_WSA_VERSION, &wsadata))return -1;
	}

	if(!ip_exists(ip)){
		create_ip_address(ip,port);
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	serv_addr.sin_addr.S_un.S_addr = inet_addr(ip);

	sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(protocol & ELT_CLIENT)
		return sockfd;

	return sockfd;

#elif defined(EX_UNIX)

    unsigned int sockfd;
    unsigned int sock_domain,socket_protocol;
    struct sockaddr_in serv_addr, cli_addr;

    if(protocol & ELT_LOCAL){
        sock_domain = PF_LOCAL;
        socket_protocol = 0;
    }
    else{
        socket_protocol = 0;
        sock_domain = PF_INET;
    }


    /*	create socket	*/
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
        if((sockfd = socket(sock_domain, SOCK_STREAM, 0)) == -1)
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

    return sockfd;
    #endif
}

DECLSPEC unsigned int ELTAPIENTRY ExCloseSocket(unsigned int socket){
    #ifdef EX_WINDOWS
	return closesocket((SOCKET)socket);
#elif defined(EX_UNIX)
    return close(socket);
    #endif

}

DECLSPEC unsigned int ELTAPIENTRY ExBindSocket(const char* ip, unsigned int port,unsigned int socket){
#ifdef EX_WINDOWS
    SOCKADDR_IN serv_addr, cli_addr;

	if(bind(socket,(SOCKADDR *)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR){
		wprintf(EX_TEXT("connect function failed with error: %ld\n"), WSAGetLastError());
	}

#elif defined(EX_UNIX)
    unsigned int sock_domain,socket_protocol;
    struct sockaddr_in serv_addr, cli_addr;

	struct hostent* host;
	host = gethostbyname(ip);

    bzero((char*)&serv_addr,sizeof(serv_addr));

    serv_addr.sin_family = host->h_addrtype;
	inet_pton(0,ip, &serv_addr.sin_addr);
    serv_addr.sin_port = htons(port);

    /**
        TODO solve how to create a ip address
    */
    if(bind(socket, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0){
        fprintf(stderr,strerror(errno));
        return -1;
    }
    return socket;
#endif // EX_WINDOWS

}

DECLSPEC unsigned int ELTAPIENTRY ExConnectSocket(const char* ip, unsigned int port){
    #ifdef EX_WINDOWS
    SOCKADDR_IN serv_addr;
    struct hostent *server;
    int sockfd;/**TODO check if sockfd should be input parameter*/

	if(wsadata.wVersion != EX_WSA_VERSION)
		WSAStartup(EX_WSA_VERSION, &wsadata);

    sockfd = ExOpenSocket(ip,port,ELT_CLIENT);

	server = gethostbyname(ip);/*   Get information of the ip address */


	serv_addr.sin_port = htons(port);
	serv_addr.sin_family = server->h_addrtype; /*AF_INET;*/
	serv_addr.sin_addr.S_un.S_addr = inet_addr(ip);

    if(connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))  == SOCKET_ERROR){
		wprintf(EX_TEXT("connect function failed with error: %ld\n"), WSAGetLastError());
	}
        fprintf(stderr,strerror(errno));

	return sockfd ;
#elif defined(EX_UNIX)
    struct sockaddr_in serv_addr;
    struct hostent *server;
    int sockfd;/**TODO check if sockdf should be input parameter*/
    /**/
    sockfd = ExOpenSocket(ELT_CLIENT);


    bzero((char*)&serv_addr, sizeof(serv_addr));
    server = gethostbyname(ip);/*get host information by ip name or ip explicitly*/

    serv_addr.sin_family = server->h_addrtype; /*AF_INET;*/

    bcopy((char*)server->h_addr,
         (char*)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(port);

    if(connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0){
        fprintf(stderr,strerror(errno));
        return 0;
    }
    return sockfd;
    #endif
}

DECLSPEC inline int ELTAPIENTRY ExGetHostIp(char ip[16]){
#ifdef EX_WINDOWS
	SOCKET fd;
	char name[256];
	struct in_addr addr;
	struct hostent* host;
	int len;

	init_wsa();

	if((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
		return -1;

	gethostname(name,sizeof(name));

	host = gethostbyname(name);

	memcpy(&addr,host->h_addr_list[0],sizeof(struct in_addr));

	memcpy(ip, inet_ntoa(addr), strlen(inet_ntoa(addr)));

    ip[strlen(strlen(inet_ntoa(addr)))] = '\0';   /*end the string*/

	ExCloseSocket(fd);

	return TRUE;
#elif defined(EX_LINUX)
    int fd;
    struct ifreq ifr;

    if((fd = socket(AF_INET, SOCK_DGRAM,0)) < 0){   /**/
        fprintf(stderr,strerror(errno));
        return -1;
    }

    ifr.ifr_addr.sa_family = AF_INET;

    strncpy(ifr.ifr_name, "eth0", IFNAMSIZ-1);  /**/

    ioctl(fd, SIOCGIFADDR, &ifr);

    close(fd);

    memcpy(ip,
           inet_ntoa(((struct sockaddr_in*)&ifr.ifr_addr)->sin_addr),
           strlen(inet_ntoa(((struct sockaddr_in*)&ifr.ifr_addr)->sin_addr)));

    ip[strlen(inet_ntoa(((struct sockaddr_in*)&ifr.ifr_addr)->sin_addr))] = '\0';   /*end the string*/
    return TRUE;
#endif

}
