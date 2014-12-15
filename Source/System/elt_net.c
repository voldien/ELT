#include"elt_net.h"
#ifdef EX_WINDOWS

#elif defined(EX_LINUX)
#   include<sys/types.h>
#   include<sys/socket.h>
#   include<netinet/in.h>
#   include<errno.h>
#endif // EX_WINDOWS

// http://www.linuxhowtos.org/data/6/server.c

DECLSPEC unsigned int ELTAPIENTRY ExOpenSocket(const char* ip, unsigned int port,unsigned int protocol){
    unsigned int sockfd,newsockdf;
    struct sockaddr_in serv_addr, cli_addr;
    /**
        create socket
    */
    switch(protocol){
        case ELT_CLIENT:
            if((sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
                fprintf(stderr,strerror(errno));
            return sockfd;
        case ELT_TCP:
            if((sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
                fprintf(stderr,strerror(errno));
            break;
        case ELT_UDP:
            if((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
                fprintf(stderr,strerror(errno));
            break;
        default:return E_INVALID_ENUM;
    }

    bzero(&serv_addr,sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(ip);
    serv_addr.sin_port = htons(port);
    if(bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0){
        fprintf(stderr,strerror(errno));
        return -1;
    }

    return sockfd;
}

DECLSPEC unsigned int ELTAPIENTRY ExCloseSocket(unsigned int socket){
    return close(socket);
}

DECLSPEC unsigned int ELTAPIENTRY ExConnectSocket(const char* ip, unsigned int port){
    struct sockaddr_in serv_addr;
    struct hostent *server;
    int sockfd;/**TODO check if sockdf should be input parameter*/
    /**/
    sockfd = ExOpenSocket(ip,port,ELT_CLIENT);

    bzero((char*)&serv_addr, sizeof(serv_addr));
    server = gethostbyname(ip);

    serv_addr.sin_family = AF_INET;

    serv_addr.sin_addr.s_addr = inet_addr(ip);
    /*bcopy((char*)server->h_addr,
         (char*)&serv_addr.sin_addr.s_addr,
         server->h_length);
*/
    serv_addr.sin_port = htons(port);

    if(connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
        fprintf(stderr,strerror(errno));

    return sockfd;
}

