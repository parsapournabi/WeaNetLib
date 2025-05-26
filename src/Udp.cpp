// Including C++ standard libraries

// Including self libraries
#include "WeaNet/Udp.h"

namespace WeaNet {
// UDP CLIENT CLASS START
Udp::Udp() {

//#ifdef _WIN32
    WsaInitializer::ensureInitialized();
//#endif

    // threads & workers
    workerThread = new QThread();
    this->moveToThread(workerThread);

    // Signals & Events
    QObject::connect(workerThread, &QThread::started, this, &Udp::handlerPoll);
    QObject::connect(workerThread, &QThread::finished, workerThread, &QObject::deleteLater);


    // definition
    this->m_buffer.resize(m_bufferSize);
    this->m_socketType = SocketType::UdpSocket;
    this->m_isBind = false;

    // workflow
    createSocket();

    // SetOptions
    setServerReuseOption();

    // Initializers
    workerThread->start();
}

Udp::~Udp() {
    Udp::close();
}

bool Udp::bind(const char *host, int port) {
    // Creating Socket if its already closed.
    if (m_sockfd < 0) {
        createSocket();
        // SetOptions
        setServerReuseOption();
    }

    // Server configuration
    memset(&m_servaddr, 0, sizeof(m_servaddr));
    m_servaddr.sin_family = m_socketFamily;
    m_servaddr.sin_addr.s_addr = inet_addr(host);
    m_servaddr.sin_port = htons(port);
    m_servlen = sizeof(m_servaddr);

    // Locating local & peer address
    locateAddresses();

    // Update State (attempting to bind).
        // State update var
    std::stringstream update_message;
    update_message << "Binding socket to " << localAddress() << ':' << localPort();
    updateState(SocketState::BindingState, update_message.str().c_str());
    // clearing update state
    update_message.str("");
    update_message.clear();

    // Bind & check errors
    int b = ::bind(m_sockfd, (const struct sockaddr*)&m_servaddr, m_servlen);
    std::cout << "Bind result: " << b << " Socket FD: " << m_sockfd << std::endl;
    if (occurError(b, SocketError::SocketBindError, "Socket binding failed!"))
        return false;
    // Socket bound.
    m_isBind = true;

    // Update State (Server bound).
    updateState(SocketState::BoundState, "Socket bound to interface successfully.");

    // Poll Config
    m_fds.fd = m_sockfd;
    m_fds.events = POLLIN;

    // Definition
    m_peek = 0;

    // Server bound successfully
    return isBound();
}

bool Udp::isBound() const { return m_isBind; }

void Udp::receiverConfig(const char *host, int port) {
    // Config receiver
    m_recvaddr.sin_family = m_socketFamily;
    m_recvaddr.sin_addr.s_addr = inet_addr(host);
    m_recvaddr.sin_port = htons(port);
    m_hasReceiver = true;
}

bool Udp::hasReceiver() const { return m_hasReceiver; }

void Udp::receiveDatagram() {
    if (occurError(m_sockfd, SocketError::SocketAccessError, "Socket isn't defined!"))
        return;
    if (m_isBind == false) {
        occurError(-1, SocketError::UnsupportedSocketOperationError, "Socket isn't connect!");
        return;
    }
    sockaddr_in cliaddr;
    socklen_t clilen = sizeof(clilen);

    int recv_bytes = ::recvfrom(m_sockfd, (char *)m_buffer.data(), bufferSize(), MSG_WAITALL, (sockaddr *)&cliaddr, &clilen);
    occurError(recv_bytes, SocketError::UnknownSocketError, "Socket read failed!", 1);

    if (recv_bytes > 0) {
        void *rawptr = static_cast<void*>(m_buffer.data());
        m_peek--;
        if (m_peek < 0)
            m_peek = 0;
        emit dataReceived(rawptr, recv_bytes, inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));
    }
}

int Udp::writeDatagram(void *buffer, int flags) {
    if (occurError(m_sockfd, SocketError::SocketAccessError, "Socket isn't defined!"))
        return -1;
    if (!hasReceiver()) {
        occurError(-1, SocketError::SocketAccessError, "Receiver not found!");
        return -1;
    }

#ifdef _WIN32
    int s = ::sendto(m_sockfd, (char *)buffer, bufferSize(), 0, (sockaddr *)&m_recvaddr, m_recvlen);
#else
    int s = ::sendto(m_sockfd, buffer, bufferSize(), MSG_CONFIRM, (sockaddr *)&m_recvaddr, m_recvlen);
#endif
    if(!occurError(s, SocketError::SocketTimeoutError, "No bytes sent!", 1))
        emit bytesWritten(s);
    return s;
}

int Udp::writeDatagram(void *buffer, const char *host, int port, int flags) {
    if (occurError(m_sockfd, SocketError::SocketAccessError, "Socket isn't defined!"))
        return -1;

    // receiver addr configuration
    struct sockaddr_in addr;
    socklen_t addrlen = sizeof(addr);
    addr.sin_family = m_socketFamily;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(host);


#ifdef _WIN32
    int s = ::sendto(m_sockfd, (char *)buffer, bufferSize(), 0, (sockaddr *)&addr, addrlen);
#else
    int s = ::sendto(m_sockfd, buffer, bufferSize(), MSG_CONFIRM, (sockaddr *)&addr, addrlen);
#endif
    if(!occurError(s, SocketError::SocketTimeoutError, "No bytes sent!", 1))
        emit bytesWritten(s);
    return s;
}

void Udp::setAutoRead(bool auto_read) {
    if (auto_read == true) {
        QObject::connect(this, &Udp::readyRead, this, &Udp::receiveDatagram, Qt::DirectConnection);
    }
    else {
        QObject::disconnect(this, &Udp::readyRead, this, &Udp::receiveDatagram);
    }
}

bool Udp::isHighThroughputMode() const { return m_highThroughputMode; }

void Udp::setHighThroughputMode(bool enabled) { m_highThroughputMode = enabled; }

void Udp::close() {
    setAutoRead(false);
    m_hasReceiver = false;
    m_peek = 0;
    Network::close();
}

void Udp::handlerPoll() {
    while (m_pollLoop) {
        if (!isBound()) {
            QThread::msleep(200);
            continue;
        }
        handlerRead();
    }
}
void Udp::handlerRead() {
    if (isHighThroughputMode()) {
        if (m_peek <= 0) {
            m_peek++;
            receiveDatagram();
        }
    }
    else {
        // Poll timeout
        int timeout_ms = 100;
        // Poll workflow
#ifdef _WIN32
        int ret_fd = WSAPoll(&m_fds, 1, timeout_ms);
#else
        int ret_fd = poll(&m_fds, 1, timeout_ms);
#endif
        if (ret_fd > 0 && (m_fds.revents & POLLIN)) {
            if (m_peek <= 0) {
                m_peek++;
                emit readyRead();
            }
        }
    }

}

}
// UDP CLIENT CLASS END
