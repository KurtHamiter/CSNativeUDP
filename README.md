# Introduction

This wrapper exists to be a replacement for C# UDP network sockets. Unlike C# sockets, sending and receiving data in this wrapper using pre-allocated buffers does not incur any new heap allocation penalties. All sockets created with this wrapper have dual stack IPV4 & IPV6 functionality by default.

# API Documentation

## Structs
### NetworkSocket 
Socket descriptor that references a created socket.

### NetworkAddress
Contains IP address and port information when sending and receiving packets over a network. Can store both IPV4 and IPV6 addresses.

## Methods
### Initialize()
Must be called once at the very start of the application. Initializes the underlying winsock library.

### NetworkSocket CreateSocket(int bufferSize)
Creates a new native socket and returns a handle for referencing it. bufferSize parameter is in bytes.

### int BindSocket(NetworkSocket networkSocket, string ipAddress, ushort port)
Binds a socket to listen on an IP address and port. ::0 binds to any IP address and should be used by default. Port should be any value between 0 & 65535.











