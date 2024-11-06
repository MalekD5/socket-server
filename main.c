#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>


int main(void)
{
    WSADATA wsaData;


    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        fprintf(stderr, "WSAStartup failed.\n");
        exit(1);
    }

    if (LOBYTE(wsaData.wVersion) != 2 ||
        HIBYTE(wsaData.wVersion) != 2)
    {
        fprintf(stderr,"Version 2.2 of Winsock is not available.\n");
        WSACleanup();
        exit(2);
    }

    int status;
    struct addrinfo hints = {0};

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    struct addrinfo *serverInfo = {0};

    if ((status = getaddrinfo(NULL, "3940", &hints, &serverInfo)) != 0) {
        fprintf(stderr, "getaddrinfo failed (%d).\n", status);
        exit(1);
    }

    printf("IP Address:\n");

    for (const struct addrinfo *p = serverInfo; p != NULL; p = p->ai_next) {

        const boolean isPv4 =  p->ai_family == AF_INET;
        char ip[isPv4 ? INET_ADDRSTRLEN : INET6_ADDRSTRLEN];
        inet_ntop(AF_INET, p->ai_addr, ip, isPv4 ? INET_ADDRSTRLEN : INET6_ADDRSTRLEN);
        printf("IP: %s\ntype: %s\n", ip, isPv4 ? "IPv4" : "IPv6");
    }


    freeaddrinfo(serverInfo);
    return 0;
}
