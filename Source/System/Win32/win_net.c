#include"win_net.h"
#ifdef EX_WINDOWS
//#include<WinInet.h>
//#include<WinSock.h>
//#include<WS2tcpip.h>
//#include<IPHlpApi.h>
//#pragma comment(lib, "Ws2_32.lib")

WSADATA winsocket = {};

DECLSPEC ERESULT ELTAPIENTRY ExInitNet(Uint32 flag){
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2,2),&wsaData);


	return 0;
}
DECLSPEC ERESULT ELTAPIENTRY ExCreatServer(const char* ip, const char* port){
	//struct addrinfo* result = NULL, *ptr = NULL, hints;

	return 0;
}
DECLSPEC ExBoolean ELTAPIENTRY ExRelaseNet(void){
	if(!WSACleanup()){
		ExDevPrintf("error");
		return 0;
	}
	return TRUE;
}

#endif
