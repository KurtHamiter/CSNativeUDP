using System;
using System.Net;
using System.Runtime.InteropServices;
using System.Text;

namespace NativeUDP
{

    public struct NetworkSocket
    {
        private ulong handle;
    }

    public struct NetworkAddress
    {
        private uint   low;
        private uint   low_;
        private uint   high;
        private uint   high_;
        private ushort port;
    }

    static class Program
    {

        public const string dllPath = "NativeUDP.dll";

        [DllImport(dllPath, EntryPoint = "Initialize", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Initialize();

        [DllImport(dllPath, EntryPoint = "CreateSocket", CallingConvention = CallingConvention.Cdecl)]
        public static extern NetworkSocket CreateSocket(int bufferSize);

        [DllImport(dllPath, EntryPoint = "BindSocket", CallingConvention = CallingConvention.Cdecl)]
        public static extern int BindSocket(NetworkSocket networkSocket, string ipAddress, ushort port);

        [DllImport(dllPath, EntryPoint = "SetBlocking", CallingConvention = CallingConvention.Cdecl)]
        public static extern int SetBlocking(NetworkSocket networkSocket, bool option);

        [DllImport(dllPath, EntryPoint = "Receive", CallingConvention = CallingConvention.Cdecl)]
        public static extern int Receive(NetworkSocket networkSocket, byte[] writeBuffer, int writeBufferLength, ref NetworkAddress senderAddress);

        [DllImport(dllPath, EntryPoint = "Send", CallingConvention = CallingConvention.Cdecl)]
        public static extern int Send(NetworkSocket networkSocket, byte[] writeBuffer, int writeBufferLength, ref NetworkAddress senderAddress);

        [DllImport(dllPath, EntryPoint = "GetIP", CallingConvention = CallingConvention.Cdecl)]
        public static extern void GetIP(ref NetworkAddress networkAddress, byte[] stringBytes, int stringBytesLength);

        [DllImport(dllPath, EntryPoint = "SetIP", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetIP(ref NetworkAddress networkAddress, string ipString);

        [DllImport(dllPath, EntryPoint = "GetPort", CallingConvention = CallingConvention.Cdecl)]
        public static extern ushort GetPort(ref NetworkAddress networkAddress);

        [DllImport(dllPath, EntryPoint = "SetPort", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetPort(ref NetworkAddress networkAddress, ushort port);

        [DllImport(dllPath, EntryPoint = "IsIPv4", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool IsIPv4(ref NetworkAddress networkAddress);

    }
}
