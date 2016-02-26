#include"system/elt_net.h"

#	pragma comment(lib,"Ws2_32.lib")
#	pragma comment(lib,"wininet")
#	include<windows.h>
#	include<wininet.h>
#	include<winsock.h>

WSADATA wsadata = {0};
#define EX_WSA_VERSION MAKEWORD(2,2)

static inline  int init_wsa(void){  /*  initialize was*/
	if(wsadata.wVersion != EX_WSA_VERSION){
		if(!WSAStartup(EX_WSA_VERSION, &wsadata))return -1;
	}
}


ELTDECLSPEC ExSocket ELTAPIENTRY ExOpenSocket(unsigned int protocol){

    unsigned int sockfd,newsockdf;
    unsigned int sock_domain,socket_protocol;

	if(wsadata.wVersion != EX_WSA_VERSION){
		if(WSAStartup(EX_WSA_VERSION, &wsadata))return -1;
	}


	sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(protocol & EX_CLIENT)
		return sockfd;

	return sockfd;

}

ELTDECLSPEC unsigned int ELTAPIENTRY ExCloseSocket(ExSocket socket){
	return closesocket((SOCKET)socket);
}


ELTDECLSPEC ExSocket ELTAPIENTRY ExBindSocket(const char* ip, unsigned int port, ExSocket socket){

    SOCKADDR_IN serv_addr, cli_addr;

	if(bind(socket,(SOCKADDR *)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR){
		wprintf(EX_TEXT("connect function failed with error: %ld\n"), WSAGetLastError());
	}

}


ELTDECLSPEC ExSocket ELTAPIENTRY ExConnectSocket(const char* ip, unsigned int port){

    SOCKADDR_IN serv_addr;
    struct hostent *server;
    int sockfd;/**TODO check if sockfd should be input parameter*/

	if(wsadata.wVersion != EX_WSA_VERSION)
		WSAStartup(EX_WSA_VERSION, &wsadata);

    sockfd = ExOpenSocket(EX_CLIENT);

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



ELTDECLSPEC inline int ELTAPIENTRY ExGetHostIp(char ip[16]){

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
