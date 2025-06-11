#ifndef NETWORK_H
#define NETWORK_H

#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <bits/stdc++.h>
#include <sys/types.h>
#include <unistd.h>
#ifdef _WIN32
//    #include <winsock2.h>
    #include <ws2tcpip.h>
    #include <windows.h>
    #include <mswsock.h>
    #include "WeaNet/Internal/WsaInitializer.h"
//    typedef SOCKET SockType
#else
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <poll.h>
    #include <fcntl.h>
//    typedef int SockType
#endif
#include <unordered_map>

#include <QObject>
#include <QDebug>
#include <QThread>
#include <QtCore/Qt>

#include "WeaNet/Internal/common.h"
#include "WeaNet/Internal/net_enums.h"

/// Abstract Network Class
/// @details Base functions & variables declared into this class..
class Network : public QObject, public INetwork {
    Q_OBJECT
public:
    // Public methods

    //// @return SocketType: TcpClient.
    //// @return SocketType: TcpServer.
    //// @return SocketType: UdpSocket.
    SocketType socketType() const;

    /// @return bool: true -> if debug mode is enabled.
    /// @return bool: false -> if debug mode is disabled.
    bool debugMode() const;

    /// @details On debug mode the logs & qDebug & perror will print if you enable it.
    /// @param bool: mode -> true == enabled debug mode, false == disable debug mode.
    void setDebugMode(const bool mode);

    /// @details Socket non-blocking/blocking mode. helps to read buffer faster on non-blocking mode.
    /// @param const bool: mode -> true == blocking mode, false == non-blocking mode.
    void setBlockingMode(const bool blocking);

    /// @details Size of the buffer (referer read&write functions).
    /// @return int: size of the buffer -> default 1024.
    int bufferSize() const;

    /// @details Note: This must be call before send(write) or recv(read) functions.
    /// @param int: size-> Usually 1024(also default value).
    void setBufferSize(const int size);

    /// @details BSD getsockopt: see SocketOption on enum_sock.h .
    /// @param SocketOption: option see enum value.
    /// @return int: optval (for example on timeout option the value is an integer timeout value with milliseconds unit)
    int socketOption(SocketOption option);

    /// @returns bool: true if the socket_fd (File Descriptor) is created, else false.
    bool isOpen() const;

    /// @return bool: true @if socket file descriptor is valid. @else false.
    bool isValid() const;

    /// @details Host address validation conditions.
    /// @param const char *: host -> Host address.
    /// @return bool: true @if host arg is valid @else false. @example -> "192.168.1.1" is Valid!, "192.0.0.0.0" is not Valid!.
    bool isValidIPv4Address(const char *host) const;

    /// @details Socket getsockopt(socketOption). SO_RCVTIMEO.
    /// @return int: timeout value (units = seconds).
    int readTimeout() const;

    /// @details Socket setsockopt (setOption). SO_RCVTIMEO
    /// @param int: sec -> timeout value (seconds).
    void setReadTimeout(int sec = 30);

    /// @details Socket getsockopt(socketOption). SO_SNDTIMEO.
    /// @return int: timeout value (units = seconds).
    int writeTimeout() const;

    /// @details Socket setsockopt (setOption). SO_SNDTIMEO
    /// @param int: sec -> timeout value (seconds).
    void setWriteTimeout(int sec = 30);

    /// @return SocketError: referer enum_sock.h SocketError enum.
    /// In @class usage: the private getter variable is latest_error_.
    SocketError latestError() const;

    /// @details SocketState: referer enum_sock.h, return values is:
    /// @return SocketState::UnconnectedState,
    /// @return SocketState::HostLookupState,
    /// @return SocketState::ConnectingState,
    /// @return SocketState::ConnectedState,
    /// @return SocketState::BoundState,
    /// @return SocketState::ListeningState,
    /// @return SocketState::ClosingState
    /// In @class usage: the private getter variable is latest_state_.
    SocketState latestState() const;

    /// @return local IP Address: for example 192.168.1.86.
    const char* localAddress() const;

    /// @return local Port value: for example on server side it returns bound port value, on client side returns current port number.
    int localPort() const;

    /// @return peer IP Address: for example on server side it returns connected client ip_address, on client side returns server ip address.
    const char* peerAddress() const;

    /// @return peer Port value: for example on server side it returns connected client port number, on client side returns server port number.
    int peerPort() const;

    /// @return int: socket file descriptor(m_sockfd).
    int socketDescriptor() const;

    /// Closing the socket. If protocol = TCP -> closes all clients file descriptor & server fd.
    /// If protocol = UDP -> closes instance socket.
    virtual void close();

signals:
    // Signals

    /// @details If any error occurred this signal will emit.
    /// @param SocketError: socketError -> Referer enum_sock.h SocketError.
    /// @param const char*: err_message -> error message summary.
    void errorOccured(SocketError socketError, const char *err_mesasge);

    /// @details Referer enum_sock.h
    /// @param SocketState: socketState -> Referer enum_sock.h SocketState.
    /// @param const char*: state_message -> You can use it on GUI socket state panel.
    void stateUpdated(SocketState socketState, const char *state_message);

protected:
    // Protected methods
    Network() = default; // Cannot create any instance on this class.

    /// @details Socket creation: Depends on socketType. (TCP = SOCK_STREAM, UDP = SOCK_DGRAM).
    void createSocket();

    /// @details Using server SO_REUSEADDR option.
    void setServerReuseOption();

    /// @details Configuring Timeout options & ...
    void setSocketOptions();

    /// @details setter of localAddress. (variable = local_addrss_)
    /// @param const char *: address -> IP_ADDRESS
    void setLocalAddress(const char *address);

    /// @details setter of localPort. (variable = local_port_)
    /// @param int: port -> PORT number
    void setLocalPort(int port_num);

    /// @details setter of peerAddress. (variable = peer_addrss_)
    /// @param const char *: address -> IP_ADDRESS
    void setPeerAddress(const char *address);

    /// @details setter of peerPort. (variable = peer_port_)
    /// @param int: port -> PORT number
    void setPeerPort(int port_num);

    /// @details locating localIpAddress, localPortNumber, peerIpAddress, peerIpPort.
    /// @details This method will set setLocalAddress and ... properties.
    void locateAddresses();

    /// @details error_handling with if (targer < condition) == we have an error on socket. Then the errorOccured signal will emit.
    /// @note : If you setDebugMode(true) the error messages will print with traceback.
    /// @note: setter of latestError().
    /// @param int: target-> can be sock_fd_ (file descriptor) or any response on socket BSD methods.
    /// @param SocketError: socketError-> referer enum_sock.h SocketError.
    /// @param const char*: err_message -> ^^Optional^^ the error_message that will append to base errror message.
    /// @param int: condition -> The condition value for example (target < condition).
    /// @return bool: true if any error occured. else false. (usage is on the internal method conditions which helps to break the funcitons if we had any error).
    /// In @class usage: after the process written, then the latest_error_ must be set with socketError.
    bool occurError(int target, SocketError socketError, const char *err_message = "An error occured: ", int condition = 0);

    /// @details This method will emit stateUpdated signal.
    /// @note : If you setDebugMode(true) the state messages goes printable.
    /// @note: setter of latestState().
    /// @param SocketState: socketState -> referer enum_sock.h SocketState.
    /// @param const char *: state_message -> The state message value.
    /// In @class usage: after the process written, then the latest_state_ must be set with socketState.
    void updateState(SocketState socketState, const char *state_message = "");

    /// @details Client Poll handler: pollfd will check new data receiving from the buffer.
    /// @details Server Poll handler: pollfd will check new client request from the buffer.
    /// @note some signals will emit from this method, for example (readyRead, newConnection).
    virtual void handlerPoll() = 0;

private:
    // Private methods

    /// @details After calling the this->close(), must clear some for memory optimization.
    /// @note The variables that must be clear are marked with $$ sign.
    /// In @class usage: Also the threads and safe Quit (signal connection quit) must be declare at the end of the method
    void cleanUp();

protected:

    // Threads
    /// workerMethod is poll function for checking readyRead(on TcpClient) & AcceptLoop(on TcpServer).
    QThread *workerThread = new QThread();

    // Socket required attributes
    /// @note $$ = -1;
    int m_sockfd = -1;
    struct sockaddr_in m_servaddr;
    socklen_t m_servlen = sizeof(m_servaddr);

    // Socket config parameters
    SocketType m_socketType;
    NetworkLayerProtocol m_socketFamily = NetworkLayerProtocol::IPv4Protocol;

    /// @details TCP Server.
    /// @note $$.
    bool m_isListening = false;
    /// @details TCP Client.
    /// @note $$.
    bool m_isConnected = false;
    /// @details UDP.
    /// @note $$.
    bool m_isBind = false;

    // class options
    bool m_debugMode = false;
    /// handlerPoll() while loop condition
    /// @note $$.
    bool m_pollLoop = true;

    // Properties private variable.
    /// getter & setter for latestErrror();
    /// @note $$.
    SocketError m_latestError = SocketError::NoError;
    /// getter & setter for state();
    /// @note $$.
    SocketState m_latestState = SocketState::NoSocketState;
    /// getter & setter for localAddress();
    /// @note $$.
    const char* m_localAddress;
    /// getter & setter for localPort();
    /// @note $$.
    int m_localPort;
    /// getter & setter for peerAddress();
    /// @note $$.
    const char* m_peerAddress;
    /// getter & setter for peerAddress();
    /// @note $$.
    int m_peerPort;

    // Socket vars
    /// getter & setter for bufferSize();
    int m_bufferSize = 1024;

    /// Getter & Setter setReadTimeout property
    int m_rcvTimeout = 2;

    /// Getter & Setter setWriteTimeout property
    int m_sndTimeout = 10;

    /// All data receive will store on this variable.
    std::vector<uint8_t> m_buffer;

};

#endif // NETWORK_H
