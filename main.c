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

    struct sockaddr_in6 sa6; // IPv6
    inet_pton(AF_INET6, "2001:db8:63b3:1::3490", &(sa6.sin6_addr)); // IPv6

    struct sockaddr_in sa; // pretend this is loaded with something
    inet_pton(AF_INET, "10.12.110.57", &(sa.sin_addr)); // IPv4

    char ip4[INET_ADDRSTRLEN]; // space to hold the IPv4 string
    inet_ntop(AF_INET, &(sa.sin_addr), ip4, INET_ADDRSTRLEN);
    printf("The IPv4 address is: %s\n", ip4);

    char ip6[INET6_ADDRSTRLEN];
    inet_ntop(AF_INET6, &(sa6.sin6_addr), ip6, INET6_ADDRSTRLEN);
    printf("The IPv6 address is: %s\n", ip6);

    return 0;
}
