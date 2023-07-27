#include "NativeUDP.h";

void Initialize() {
    WSADATA wsaData;
    int     returnValue = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (returnValue != 0) { printf("Socket Initialization Error"); }
}

SOCKET CreateSocket(int bufferSize) {
    SOCKET newSocket  = socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP);
    int    sockOption = 0;
    setsockopt(newSocket, SOL_SOCKET, SO_RCVBUF, (const char*)&bufferSize, sizeof(bufferSize));
    setsockopt(newSocket, IPPROTO_IPV6, IPV6_V6ONLY, (const char*)&sockOption, sizeof(sockOption));
    return newSocket;
}

int BindSocket(SOCKET netSocket, char* stringAddress, unsigned short port) {
    struct sockaddr_in6   ipAddress      = {0};
    struct NetworkAddress networkAddress = {0};

    SetIP(&networkAddress, stringAddress);

    ipAddress.sin6_family = AF_INET6;
    ipAddress.sin6_addr   = networkAddress.ipv6;
    ipAddress.sin6_port   = htons(port);
    return bind(netSocket, (sockaddr*)&ipAddress, sizeof(ipAddress));
}

bool IsLocalHost(struct NetworkAddress* networkAddress) {
    switch (IsIPv4(networkAddress)) {
        case true: {
            struct IPv4LocalHost ipv4LocalHost;
            return !memcmp(&networkAddress->ipv4.ip, &ipv4LocalHost, 4);
        }
        case false: {
            struct IPv6LocalHost ipv6LocalHost;
            return !memcmp(&networkAddress->ipv6, &ipv6LocalHost, 16);
        }
    }
}

bool IsStringIPv4(char* address) {
    bool returnValue = false;
    if (strchr(address, ':') == NULL) { returnValue = true; }
    return returnValue;
}

bool IsIPv4(struct NetworkAddress* networkAddress) {
    struct IPv4Map ipv4Map;
    return !memcmp(networkAddress, &ipv4Map, 12);
}

int Send(SOCKET netSocket, char* sendBuffer, int sendBufferLength, struct NetworkAddress* networkAddress) {
    struct sockaddr_in6 ipAddress = {};
    int                 ipAddressSize = sizeof(ipAddress);

    ipAddress.sin6_family = AF_INET6;
    ipAddress.sin6_addr   = networkAddress->ipv6;
    ipAddress.sin6_port   = networkAddress->port;
    return sendto(netSocket, sendBuffer, sendBufferLength, 0, (struct sockaddr*)&ipAddress, ipAddressSize);
}

int Receive(SOCKET netSocket, char* receiveBuffer, int receiveBufferLength, struct NetworkAddress* networkAddress) {
    struct sockaddr_storage ipAddress = {};
    int                     ipAddressSize = sizeof(ipAddress);

    int byteCount = recvfrom(netSocket, receiveBuffer, receiveBufferLength, 0, (struct sockaddr*)&ipAddress, &ipAddressSize);
    networkAddress->ipv6 = ((struct sockaddr_in6*)&ipAddress)->sin6_addr;
    networkAddress->port = ((struct sockaddr_in6*)&ipAddress)->sin6_port;
    return byteCount;
}

int SetBlocking(SOCKET netSocket, bool option) {
    u_long mode;
    if (option)  { mode = 0; }
    if (!option) { mode = 1; }
    return ioctlsocket(netSocket, FIONBIO, &mode);
}

void GetIP(struct NetworkAddress* networkAddress, char* stringBytes, int stringBytesLength) {
    switch (IsIPv4(networkAddress)) {
        case true: {
            inet_ntop(AF_INET, &networkAddress->ipv4.ip, stringBytes, stringBytesLength);
            break;
        }
        case false: {
            inet_ntop(AF_INET6, &networkAddress->ipv6, stringBytes, stringBytesLength);
            break;
        }
    }
}

void SetIP(struct NetworkAddress* networkAddress, char* address) {
    switch (IsStringIPv4(address)) {
        case true: {
            struct IPv4Map ipv4Map;
            memcpy(networkAddress, &ipv4Map, 12);
            inet_pton(AF_INET, address, &networkAddress->ipv4.ip);
            break;
        }
        case false: {
            inet_pton(AF_INET6, address, &networkAddress->ipv6);
            break;
        }
    }
}

void SetPort(struct NetworkAddress* networkAddress, uint16_t port) {
    networkAddress->port = htons(port);
}

uint16_t GetPort(struct NetworkAddress* networkAddress) {
    return ntohs(networkAddress->port);
}
