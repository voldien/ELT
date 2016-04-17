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

static int private_ip_exists(const char* ip){
	struct hostent* host;
	unsigned int iplen = strlen(ip);
	host = gethostbyname(ip);
	if(!host){
		host = gethostbyaddr(ip, iplen, iplen == 4 ? AF_INET : AF_INET6);
		if(host){
			return TRUE;
		}
		return FALSE;
	}
	return TRUE;
}

ExSocket ExOpenSocket(unsigned int protocol){
    unsigned int sockfd;
    unsigned int sock_domain,socket_protocol;
    struct sockaddr_in serv_addr, cli_addr;

    /*	*/
    if(protocol & EX_LOCAL){
        sock_domain = PF_UNIX;
        socket_protocol = 0;
    }
    else{
        socket_protocol = 0;
        sock_domain = AF_INET;
    }

    /*	create socket	*/
    if(protocol & EX_LOCAL){
        if((sockfd = socket(sock_domain, SOCK_STREAM, socket_protocol)) == -1)
            fprintf(stderr, strerror(errno));
        if(protocol & EX_CLIENT)
            return sockfd;
    }
    else if(protocol & EX_CLIENT){

        if((sockfd = socket(sock_domain, SOCK_STREAM, socket_protocol)) == -1)
            fprintf(stderr, strerror(errno));

        return sockfd;
    }
    else if(protocol & EX_TCP){
        socket_protocol = 0;
        if((sockfd = socket(sock_domain, SOCK_STREAM, 0)) == -1)
            fprintf(stderr, strerror(errno));
    }
    else if(protocol & EX_UDP){
        socket_protocol = 0;
        if((sockfd = socket(sock_domain, SOCK_DGRAM, socket_protocol)) == -1)
            fprintf(stderr, strerror(errno));
    }
    else{
        if((sockfd = socket(sock_domain, SOCK_STREAM, socket_protocol)) == -1)
            fprintf(stderr, strerror(errno));
    }

    return sockfd;
}

ExSocket ExCreateSocket(unsigned int domain, unsigned int style, unsigned int protocal){
	return (ExSocket)socket(domain, style, protocal);
}


inline unsigned int ExCloseSocket(ExSocket socket){
    return close(socket);
}

ExSocket ExBindSocket(const char* ip, unsigned int port, ExSocket socket){
    unsigned int sock_domain,socket_protocol;
    struct sockaddr_in serv_addr, cli_addr;
	struct hostent* host;
	unsigned int iplen = strlen(ip);

	host = gethostbyname(ip);	/*get host information by ip name or ip explicitly*/
    if(!host){
    	/**/
    	host = gethostbyaddr(ip, iplen, iplen == 4 ? AF_INET : AF_INET6);
    	if(!host){
    		ExLog("");
    		return (ExSocket)0;
    	}
    }

    bzero((char*)&serv_addr,sizeof(serv_addr));

    serv_addr.sin_family = host->h_addrtype;
	inet_pton(0,ip, &serv_addr.sin_addr);
    serv_addr.sin_port = htons(port);


    if(bind(socket, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0){
        fprintf(stderr, strerror(errno));
        return -1;
    }
    return socket;
}


ExSocket ExConnectSocket(const ExChar* ip, unsigned int port){
	/**/
    struct sockaddr_in serv_addr;
    struct hostent *server;
    ExSocket sockfd;
    unsigned int iplen = strlen(ip);

    server = gethostbyname(ip);	/*get host information by ip name or ip explicitly*/
    if(!server){
    	/**/
    	server = gethostbyaddr(ip, iplen, iplen == 4 ? AF_INET : AF_INET6);
    	if(!server){
    		ExLog("");
    		return (ExSocket)0;
    	}
    }

    /*	create soket	*/
    sockfd = ExOpenSocket(EX_CLIENT);
    //sockfd = ExCreateSocket(server->h_addrtype, server->h_)
    if(sockfd < 0){
    	ExLog("Failed to create socket.\n");
    	return (ExSocket)0;
    }

    /*	*/
    bzero((char*)&serv_addr, sizeof(serv_addr));


    /*	get namespace	*/
    serv_addr.sin_family = server->h_addrtype; /*AF_INET;*/

    /*	copy server addr data.	*/
    bcopy((char*)server->h_addr,
         (char*)&serv_addr.sin_addr.s_addr,
         server->h_length);

    serv_addr.sin_port = htons(port);

    /*	*/
    if(connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0){
    	ExLog("");
        fprintf(stderr, "%s\n", strerror(errno));
        return -1;
    }
    return sockfd;
}

const ExChar* ExGetHostName(const ExChar* hostname){
	unsigned int hostlen = strlen(hostname);
	struct hostent* host = gethostbyname(hostname);
	if(!host){
		ExLog("gethostname for %s failed.", hostname);
		return NULL;
	}

	if(host->h_length == 4)
		return host->h_addr_list[0];
	else if(host->h_length == 16)
		return host->h_addr_list[0];
	return NULL;
}


ExChar* ExGetInterfaceAddr(const ExChar* interface, ExChar* addr, Uint len){
    ExSocket fd;
    struct ifreq ifr;

    if(interface == NULL || addr == NULL)
    	return NULL;

	ifr.ifr_addr.sa_family = AF_INET;
	fd = ExCreateSocket(AF_INET, SOCK_DGRAM, 0);
	strncpy(ifr.ifr_name, interface, IFNAMSIZ-1);  /**/
	ioctl(fd, SIOCGIFADDR, &ifr);
	ExCloseSocket(fd);

	unsigned int inetlen = strlen(inet_ntoa(((struct sockaddr_in*)&ifr.ifr_addr)->sin_addr));
	memcpy(addr,
	           inet_ntoa(((struct sockaddr_in*)&ifr.ifr_addr)->sin_addr),
			   len < inetlen ? len  : inetlen);
	return addr;
}

