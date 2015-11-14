#include"system/elt_net.h"

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

#   include<errno.h>
#   include<unistd.h>

static int ip_exists(const char* ip){
	struct hostent* host;
	host = gethostbyname(ip);
	if(!host)
		return FALSE;
	return TRUE;
}

DECLSPEC ExSocket ELTAPIENTRY ExOpenSocket(unsigned int protocol){
    unsigned int sockfd;
    unsigned int sock_domain,socket_protocol;
    struct sockaddr_in serv_addr, cli_addr;

    if(protocol & ELT_LOCAL){
        sock_domain = PF_LOCAL;
        socket_protocol = 0;
    }
    else{
        socket_protocol = 0;
        sock_domain = AF_INET;
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
}



inline
DECLSPEC unsigned int ELTAPIENTRY ExCloseSocket(ExSocket socket){
    return close(socket);
}



DECLSPEC ExSocket ELTAPIENTRY ExBindSocket(const char* ip, unsigned int port, ExSocket socket){
    unsigned int sock_domain,socket_protocol;
    struct sockaddr_in serv_addr, cli_addr;

	struct hostent* host;

	host = gethostbyname(ip);

    bzero((char*)&serv_addr,sizeof(serv_addr));

    serv_addr.sin_family = host->h_addrtype;
	inet_pton(0,ip, &serv_addr.sin_addr);
    serv_addr.sin_port = htons(port);

    /*	TODO solve how to create a ip address	*/
    if(bind(socket, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0){
        fprintf(stderr,strerror(errno));
        return -1;
    }
    return socket;
}


DECLSPEC ExSocket ELTAPIENTRY ExConnectSocket(const char* ip, unsigned int port){

    struct sockaddr_in serv_addr;
    struct hostent *server;
    ExSocket sockfd;
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
        return -1;
    }
    return sockfd;
}


int ExGetHostIp(char* ip){
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
}


