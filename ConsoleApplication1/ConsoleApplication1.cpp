#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <stdlib.h>

#pragma comment(lib, "Ws2_32.lib")

int main(int argc,char** argv)
{
    WSADATA wsaData;
    SOCKET ConnectSocket = INVALID_SOCKET;
    const char* sendbuf = "this is a test";
    struct sockaddr_in hints;
    int iResult;

    // Validate the parameters
    if (argc != 3) {
        printf("usage: %s ip port\n", argv[0]);
        return 1;
    }

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.sin_family = AF_INET;
    //hints.sin_port = htons(22); //ssh WSAECONNREFUSED // 10061
    //hints.sin_port = htons(3389); //rdp 3389
    hints.sin_port = htons(atoi(argv[2]));

    //Result = inet_pton(AF_INET, "127.0.0.1", &hints.sin_addr);
    //Result = inet_pton(AF_INET, "0.0.0.0", &hints.sin_addr); // WSAEADDRNOTAVAIL 10049
    iResult = inet_pton(AF_INET, argv[1], &hints.sin_addr);
    if (iResult != 1) {
        printf("inet_pton failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    // Create a SOCKET for connecting to server
    ConnectSocket = socket(hints.sin_family, SOCK_STREAM, 0);
    if (ConnectSocket == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    // Connect to server.
    iResult = connect(ConnectSocket, (struct sockaddr*)&hints, (int)sizeof(hints));
    if (iResult == SOCKET_ERROR) {
        printf("connect failed with error: %ld\n", WSAGetLastError());
        closesocket(ConnectSocket);
        return 1;
    }

    if (ConnectSocket == INVALID_SOCKET) {
        printf("Unable to connect to server!\n");
        WSACleanup();
        return 1;
    }
    printf("connect: OK");
    return 0;
}

