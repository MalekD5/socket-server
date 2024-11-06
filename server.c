#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#define PORT "3030"
#define BACKLOG 10

void *get_address_family(struct sockaddr *sa) {
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in *) sa)->sin_addr);
    }

    return &(((struct sockaddr_in6 *) sa)->sin6_addr);
}

int main(void) {
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

    if ((status = getaddrinfo(NULL, PORT, &hints, &serverInfo)) != 0) {
        fprintf(stderr, "getaddrinfo failed (%s).\n", gai_strerror(status));
        exit(1);
    }

    printf("IP Address:\n");

    bool isPv4;

    for (const struct addrinfo *p = serverInfo; p != NULL; p = p->ai_next) {
        isPv4 =  p->ai_family == AF_INET;
        char ip[isPv4 ? INET_ADDRSTRLEN : INET6_ADDRSTRLEN];
        inet_ntop(AF_INET, p->ai_addr, ip, isPv4 ? INET_ADDRSTRLEN : INET6_ADDRSTRLEN);
        printf("IP: %s\ntype: %s\n", ip, isPv4 ? "IPv4" : "IPv6");
    }

    int s = socket(serverInfo->ai_family, serverInfo->ai_socktype, serverInfo->ai_protocol);
    bind(s, serverInfo->ai_addr, serverInfo->ai_addrlen);

    listen(s, BACKLOG);

    printf("Waiting for connections..\n");

    struct sockaddr_storage s_client;
    socklen_t sin_size;

    while (1) {
        sin_size = sizeof(s_client);
        SOCKET new_fd = accept(s, (struct sockaddr *) &s_client, &sin_size);
        if (new_fd == INVALID_SOCKET) {
            fprintf(stderr, "accept failed (%s).\n", WSAGetLastError());
            continue;
        }
        char ip[isPv4 ? INET_ADDRSTRLEN : INET6_ADDRSTRLEN];
        inet_ntop(s_client.ss_family,  get_address_family((struct sockaddr *) &s_client), ip, isPv4 ? INET_ADDRSTRLEN : INET6_ADDRSTRLEN);
        printf("Connection established with %s.\n", ip);

        send(new_fd, "Hello world!", 12, 0);
        closesocket(new_fd);
        shutdown(new_fd, SD_BOTH);
        break;
    }

    freeaddrinfo(serverInfo);
}
