#ifndef TCP_H
#define TCP_H

#include "WeaNet/Internal/network.h"

namespace WeaNet {
class TcpClient : public Network {
    Q_OBJECT

    friend class TcpServer;

public:
    // Public methods

    /// Manually TcpClient creation
    explicit TcpClient();

    /// Uses on TcpServer accept file descriptor response.
    /// @note By using this constructure the workerThread will not create.
    /// @param int: sockfd-> file descriptor the response of the accept method.
    /// @param pollfd: fds-> Poll File descriptor handler.
    explicit TcpClient(int sockfd, struct pollfd fds);

    /// Destructure on TcpClient class.
    /// closes sockets earase cache
    ~TcpClient();

    /// @details connect to the server.
    /// @param const char *: host -> SERVER_IP_ADDRESS
    /// @param int: port -> SERVER_PORT_ADDRESS
    bool connectToHost(const char* host, int port);

    /// @return bool: true @if socket is connected to server @else false.
    bool isConnected() const;

    /// @details using BSD recv().
    /// @details data will emit on dataReceived() signal. (you must parse the buffer with address arg).
    /// @note Function can be call externally & internally (to use internally without any call just setAutoRead(true);
    void read();

    /// This method uses socket send() but simpler
    /// @param buffer: The size of buffer must be same as buffer_size.
    /// @param flags: send() TCP flags.
    /// @return int: sent Bytes.
    int write(void *buffer, int flags = 0);

    /// @details By enabling this function the readyRead signal will connect internally to read();
    /// @param bool: mode -> true == enable, false == disable
    void setAutoRead(bool auto_read);

    /// @return bool: true -> @if you setHighThroughputMode(true); @else false.
    bool isHighThroughputMode() const;

    /// @details Before you set this attribute to true. make sure that you setAutoRead(true);
    /// @details By enabling this property the poll() will ignore.
    void setHighThroughputMode(bool enabled);

    /// Override from Network class.
    void close() override;

signals:
    // Signals

    /// @details If socket goes connectTohost() this signal will emit.
    void connected();

    /// @details @if socket disconnect form server the disconnected signal will emit.
    /// @note **Make sure you'll delete socket file descriptor from heap after closing.
    /// @note Use lambda function for Best Practice of signal/slot connection.
    void disconnected();

    /// @details Like Qt readyRead() signal.
    /// In @class usage: connect this signal to recv/read function.
    void readyRead();

    /// @details When the read() call the byte (buffer) address & the size of the bytes(B) will emit on this signal.
    /// @param void *: bytes_addr -> Buffer pointer address.
    /// @param size_t: bytes_size -> bytes_addr.size(), for example 1024 bytes.
    void dataReceived(void *bytes_addr, size_t bytes_size);

    /// @details like Qt bytesWritter signal.
    void bytesWritten(int numSentBytes);

protected:
    // Protected methods

    void handlerPoll() override;

private:
    // Private methods

    /// @details By using this function you should connect disconnected signal to your disconnect handler slot.
    /// @note The disconnectFromHost method will not close the socket! you should close it manually when you want to use this funciton.
    void disconnectFromHost();

    /// @details reading handler when mode is setted on HighThroughput or not.
    void handlerRead();

private:
    // Private variables

    /// Poll peek counter needs on readyRead signal.
    /// peek will avoid race_condition between read & readyRead.
    long long m_peek = 0;

    /// isHighThroughputMode property
    bool m_highThroughputMode = false;

    /// Needs on handlerPoll
    struct pollfd m_fds;
};

class TcpServer : public Network {
    Q_OBJECT

public:
    // Public methods

    /// Socket creation.
    explicit TcpServer();

    /// Socket closing.
    ~TcpServer();

    /// @details Getter / private var = max_penfing_connections_
    /// @default = 10
    /// @return int: number of the maximum pending connections.
    int maxPendingConnections() const;

    /// @details setter / private var = max_penfing_connections_
    /// @default = 10
    void setMaxPendingConnections(int numConnections);

    /// @details Pause handler Accepting loop
    /// @details private var = resume_accepting_.
    void pauseAccepting();

    /// @details Resume handler Accepting loop
    /// @details private var = resume_accepting_.
    void resumeAccepting();

    /// @details Bind & listen on to specify host & port.
    /// @param const char *: host -> server IP_ADDRESS
    /// @param int: port -> server PORT_ADDRESS
    /// @return bool: true if listen is fine.
    bool listen(const char *host, int port);

    /// @return bool: true If server is on the accept event loop with no error, else false.
    bool isListening() const;

    /// @return TcpClient: accept method returning
    /// @return nullptr: If failed or there is no pendingConnection
    TcpClient* nexPendingConnection();

    /// @return bool: true if any pendingConnection isn't empty(), else false.
    bool hasPendingConnection() const;

    /// Override from Network class.
    void close() override;

signals:
    // Signals

    /// @details emit by any new accepting.
    void newConnection();

protected:
    // Protected methods

    void handlerPoll() override;

private:
    // Private variables

    /// all clients will store here.
    /// @note This variable is just like the queue!
    /// @note by each newConnection emit & nexPendingConnection, one client will dequeue from this var.
    std::vector<TcpClient*> m_pendingConnections;

    /// all clients will store here.
    std::vector<TcpClient*> m_clients;

    /// All Poll files will store here.
    std::vector<pollfd> m_polls;

    /// @details getter & setter variable of maxPendingConnections()
    /// @default = 10;
    int m_maxPendingConnections = 10;

    /// @details referer handlerAcceptLoop (while event loop continue condition).
    /// @details to pause or resume the loop, check pauseAccepting() & resumeAccepting() functions.
    /// @details true == resume, false == pause
    bool m_resumeAccepting = true;
};
}

#endif // TCP_H
