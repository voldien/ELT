#include"system/elt_net.h"


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


#ifdef EX_WINDOWS
DECLSPEC ExSocket ELTAPIENTRY ExOpenSocket(unsigned int protocol){

    unsigned int sockfd,newsockdf;
    unsigned int sock_domain,socket_protocol;

	if(wsadata.wVersion != EX_WSA_VERSION){
		if(WSAStartup(EX_WSA_VERSION, &wsadata))return -1;
	}


	sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(protocol & ELT_CLIENT)
		return sockfd;

	return sockfd;

}
#endif

#ifdef EX_WINDOWS
DECLSPEC unsigned int ELTAPIENTRY ExCloseSocket(ExSocket socket){
	return closesocket((SOCKET)socket);
}
#endif

#ifdef EX_WINDOWS
DECLSPEC ExSocket ELTAPIENTRY ExBindSocket(const char* ip, unsigned int port, ExSocket socket){

    SOCKADDR_IN serv_addr, cli_addr;

	if(bind(socket,(SOCKADDR *)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR){
		wprintf(EX_TEXT("connect function failed with error: %ld\n"), WSAGetLastError());
	}

}
#endif


#ifdef EX_WINDOWS
DECLSPEC ExSocket ELTAPIENTRY ExConnectSocket(const char* ip, unsigned int port){

    SOCKADDR_IN serv_addr;
    struct hostent *server;
    int sockfd;/**TODO check if sockfd should be input parameter*/

	if(wsadata.wVersion != EX_WSA_VERSION)
		WSAStartup(EX_WSA_VERSION, &wsadata);

    sockfd = ExOpenSocket(ELT_CLIENT);

	server = gethostbyname(ip);/*   Get information of the ip address */


	serv_addr.sin_port = htons(port);
	serv_addr.sin_family = server->h_addrtype; /*AF_INET;*/
	serv_addr.sin_addr.S_un.S_addr = inet_addr(ip);

    if(connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))  == SOCKET_ERROR){
		wprintf(EX_TEXT("connect function failed with error: %ld\n"), WSAGetLastError());
	}
        fprintf(stderr,strerror(errno));

	return sockfd ;


}
#endif


#ifdef EX_WINDOWS
DECLSPEC inline int ELTAPIENTRY ExGetHostIp(char ip[16]){

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

}
#endif

