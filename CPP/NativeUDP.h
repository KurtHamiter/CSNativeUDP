#define WIN32_LEAN_AND_MEAN
#include <Ws2tcpip.h>
#include <stdio.h>
#include <iostream>
#pragma comment(lib, "Ws2_32.lib")

struct NetworkAddress {
    union {
        struct in6_addr ipv6;
        struct {
                   uint8_t  zeros[10];
                   uint16_t ffff;
            struct in_addr  ip;
        } ipv4;
    };
    uint16_t port;
};

struct IPv4Map {
    uint64_t low  = 0;
    uint16_t mid  = 0;
    uint16_t high = 0xffff;
};

struct IPv4LocalHost {
    uint8_t low  = 127;
    uint8_t mid  = 0;
    uint8_t mid_ = 0;
    uint8_t high = 1;
};

struct IPv6LocalHost {
    uint64_t low  = 0;
    uint64_t high = 1;
};

extern "C" __declspec(dllexport) SOCKET   CreateSocket(int bufferSize);
extern "C" __declspec(dllexport) void     Initialize();
extern "C" __declspec(dllexport) void     SetIP(struct NetworkAddress* networkAddress, char* address);
extern "C" __declspec(dllexport) void     GetIP(struct NetworkAddress* networkAddress, char* stringBytes, int stringBytesLength);
extern "C" __declspec(dllexport) void     SetPort(struct NetworkAddress* networkAddress, uint16_t port);
extern "C" __declspec(dllexport) int      Send(SOCKET netSocket, char* sendBuffer, int sendBufferLength, struct NetworkAddress* networkAddress);
extern "C" __declspec(dllexport) int      BindSocket(SOCKET netSocket, char* stringAddress, unsigned short port);
extern "C" __declspec(dllexport) int      SetBlocking(SOCKET netSocket, bool option);
extern "C" __declspec(dllexport) int      Receive(SOCKET netSocket, char* writeBuffer, int writeBufferLength, struct NetworkAddress* networkAddress);
extern "C" __declspec(dllexport) bool     IsIPv4(struct NetworkAddress* networkAddress);
extern "C" __declspec(dllexport) bool     IsLocalHost(struct NetworkAddress* networkAddress);
extern "C" __declspec(dllexport) uint16_t GetPort(struct NetworkAddress* networkAddress);
