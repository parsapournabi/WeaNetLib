#ifndef NET_ENUMS_H
#define NET_ENUMS_H

enum SocketType {
    Client = 0, // TcpClient
    Server = 1, // TcpServer
    UdpSocket = 2
};

enum NetworkLayerProtocol {
    AnyIPProtocol,
    IPv6Protocol = 10, // AF_INET6
    IPv4Protocol = 2, // AF_INET
    UnknownNetworkLayerProtocol = -1
};

enum SocketError {
    ConnectionRefusedError,
    RemoteHostClosedError,
    HostNotFoundError,
    SocketAccessError,
    SocketResourceError,
    SocketTimeoutError,                     /* 5 */
    DatagramTooLargeError,
    NetworkError,
    AddressInUseError,
    SocketAddressNotAvailableError,
    UnsupportedSocketOperationError,        /* 10 */
    UnfinishedSocketOperationError,
    TemporaryError,
    SocketOptionError,
    SocketBindError,
    UnknownSocketError = -1,
    SocketFlagError,
    NoError
};

enum SocketState {
    UnconnectedState,
    HostLookupState,
    ConnectingState,
    ConnectedState,
    BindingState,
    BoundState,
    ListeningState,
    AcceptedState,
    ClosingState,
    SocketCreation,
    NoSocketState,
    SocketFlags,
    SocketCreated
};

enum SocketOption {
//    LowDelayOption, // TCP_NODELAY
    TypeOfServiceOption = 1, // IP_TOS
    ReuseAddressOption = 2, // SO_REUSEADDR
    KeepAliveOption = 9, // SO_KEEPALIVE
    MulticastTtlOption = 33, // IP_MULTICAST_TTL
    SendBufferSizeSocketOption = 7,    //SO_SNDBUF
    ReceiveBufferSizeSocketOption = 8,  //SO_RCVBUF
    PathMtuSocketOption = 14, // IP_MTU
    ReceiveTimeoutOption = 20, // SO_RCVTIMEO
    SendTimeoutOption = 21 // SO_SNDTIMEO
};

#endif // NET_ENUMS_H
