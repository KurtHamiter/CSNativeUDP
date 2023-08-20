# Introduction

This wrapper exists to be a replacement for C# UDP network sockets in high performance environments. Unlike C# sockets, sending and receiving data in this wrapper using pre-allocated buffers does not incur any new heap allocation penalties. All sockets created with this wrapper have dual stack IPv4 & IPv6 functionality by default.

# API Documentation

## Structs
### NetworkSocket 
Socket descriptor that references a created socket.

### NetworkAddress
Contains IP address and port information when sending and receiving packets over a network. Can store both IPv4 and IPv6 addresses.

## Methods
`int Initialize()` - 
Must be called once at the start of the application before any usage of the following API. Initializes the underlying winsock library. Do not call this again before de-initializing.
Returns response code 0 if successful.

`NetworkSocket CreateSocket(int bufferSize)` - 
Creates a new native socket and returns a handle for referencing it. bufferSize parameter is in bytes.

`int BindSocket(NetworkSocket networkSocket, string ipAddress, ushort port)` - 
Binds a socket to listen on an IP address and port. ::0 binds to any IP address and should be used by default. Port should be any value between 0 & 65535.
Returns response code 0 if successful.

`int SetBlocking(NetworkSocket networkSocket, bool option)` -
Sets a socket to either blocking or non blocking. Returns response code 0 if successful.

`int Receive(NetworkSocket networkSocket, byte[] writeBuffer, int writeBufferLength, ref NetworkAddress networkAddress)` - 
Receive available packets from the network queue. Writes packet payload to buffer and stores received address info in NetworkAddress struct. 
Returns bytes received. -1 means no packets are available.

`int Send(NetworkSocket networkSocket, byte[] writeBuffer, int writeBufferLength, ref NetworkAddress networkAddress)` -
Sends bytes inside writeBuffer to a NetworkAddress. Returns amount of bytes sent.

`void GetIP(ref NetworkAddress networkAddress, byte[] stringBytes, int stringBytesLength)` - Writes ASCII text representation of an IPv4 or IPv6 address into a byte array. This can be converted into a char array or string.

`void SetIP(ref NetworkAddress networkAddress, string ipString)` - Converts string representation of an IPv4 or IPv6 address into it's memory representation within a NetworkAddress struct.

`ushort GetPort(ref NetworkAddress networkAddress)` - Returns the port stored in a NetworkAddress. This should not be bypassed, as ports are stored internally using big endian format.

`void SetPort(ref NetworkAddress networkAddress, ushort port)` - Sets the port of a NetworkAddress struct. This should not be bypassed, as ports are stored internally using big endian format.

`bool IsIPv4(ref NetworkAddress networkAddress)` - Returns true if the NetworkAddress struct contains an IPv4 address. Returns false if IPv6.







