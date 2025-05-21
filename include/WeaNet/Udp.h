#ifndef UDP_H
#define UDP_H

#include "WeaNet/Internal/network.h"

namespace WeaNet {
class Udp : public Network {
    Q_OBJECT
public:
    // Public methods

    /// Manually Udp creation
    explicit Udp();

    /// Destructure on TcpClient class.
    /// closes sockets earase cache
    ~Udp();

    /// @details binding server
    /// @param const char *: host -> SERVER IP_ADDRESS
    /// @param int: port -> SERVER PORT_ADDRESS
    /// @return bool: true if it was successful.
    bool bind(const char *host, int port);

    /// @return bool: true @if socket is bound @else false.
    bool isBound() const;

    /// @details Receiver configuration.
    /// @details The configs will store on protected recvaddr variable.
    void receiverConfig(const char *host, int port);

    /// @return bool: true -> senderConfig has been called successfully @else false.
    /// @note getter variable is m_hasSender
    bool hasReceiver() const;

    /// @details using BSD recvfrom().
    /// @details data will emit on dataReceived() signal. (you must parse the buffer with address arg).
    /// @note Function can be call externally & internally (to use internally without any call just setAutoRead(true);
    /// @note the dataGramReceived signal will emit buffer address & buffer size & host & port.
    void receiveDatagram();

    /// @details This method uses socket sendto() but simpler
    /// @param buffer: The size of buffer must be same as buffer_size.
    /// @param const char *: host -> Receiver IP_ADDRESS
    /// @param int: port -> Receiver PORT_ADDRESS
    /// @param flags: sendto() UDP flags.
    /// @return int: sent Bytes.
    int writeDatagram(void *buffer, const char *host, int port, int flags = 0);

    /// @details This method will send buffer to only one host.
    /// @note Remember before you call this function make sure that you called ConfigReceiver.
    /// @param buffer: The size of buffer must be same as buffer_size.
    /// @param flags: sendto() UDP flags.
    /// @return int: sent Bytes.
    int writeDatagram(void *buffer, int flags = 0);

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

    /// @details Like Qt readyRead() signal.
    /// In @class usage: connect this signal to recvfrom/recvDatagram function.
    void readyRead();

    /// @details When the receiveDatagram() call the byte (buffer) address & the size of the bytes(B) will emit on this signal.
    /// @param void *: bytes_addr -> Buffer pointer address.
    /// @param size_t: bytes_size -> bytes_addr.size(), for example 1024 bytes.
    /// @param const char*: host -> Sender IP_ADDRESS.
    /// @param int: port -> Sender PORT_ADDRESS.
    void dataReceived(void *bytes_addr, size_t bytes_size, const char* host, int port);

    /// @details like Qt bytesWritter signal.
    void bytesWritten(int numSentBytes);

protected:
    // Protected methods

    void handlerPoll() override;

private:
    // Private methods

    /// @details reading handler when mode is setted on HighThroughput or not.
    void handlerRead();

private:
    // Private variables

    // Receiver static address
    struct sockaddr_in m_recvaddr;
    socklen_t m_recvlen = sizeof(m_recvaddr);

    /// Poll peek counter needs on readyRead signal.
    /// peek will avoid race_condition between read & readyRead.
    long long m_peek = 0;

    /// Getter & Setter on receiverConfig
    bool m_hasReceiver = false;

    /// isHighThroughputMode property
    bool m_highThroughputMode = false;

    /// Needs on handlerPoll
    struct pollfd m_fds;

};
}


#endif // UDP_H
