// Including C++ standard libraries

// Including self libraries
#include "WeaNet/Udp.h"

namespace WeaNet {
// UDP CLIENT CLASS START
Udp::Udp() {

#ifdef _WIN32
    WsaInitializer::ensureInitialized();
#endif

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
    }
    // SetOptions
    setServerReuseOption();
    setSocketOptions();

    // Server configuration
    memset(&m_servaddr, 0, sizeof(m_servaddr));
    m_servaddr.sin_family = m_socketFamily;
    m_servaddr.sin_addr.s_addr = inet_addr(host);
    m_servaddr.sin_port = htons(port);
    m_servlen = sizeof(m_servaddr);

    // Update State (attempting to bind).
        // State update var
    std::stringstream update_message;
    update_message << "Binding socket...";
    updateState(SocketState::BindingState, update_message.str().c_str());
    update_message.str("");
    update_message.clear();


    // Bind & check errors
    int b = ::bind(m_sockfd, (const struct sockaddr*)&m_servaddr, m_servlen);
    if (occurError(b, SocketError::SocketBindError, "Socket binding failed!"))
        return false;
    else {
        // Locating local & peer address
        locateAddresses();

        // Update State (Server bound).
        update_message << "Socket bound to interface" << localAddress() << ':' << localPort() << " successfully. ";
        updateState(SocketState::BindingState, update_message.str().c_str());
        // clearing update state
        update_message.str("");
        update_message.clear();

    }
    // Socket bound.
    m_isBind = true;


    // Poll Config
    m_fds.fd = m_sockfd;
#ifdef _WIN32
    m_fds.events = POLLRDNORM;
#else
    m_fds.events = POLLIN;
#endif

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
    struct sockaddr_in cliaddr;

#ifdef _WIN32
    socklen_t clilen = sizeof(cliaddr);
    int recv_bytes = ::recvfrom(m_sockfd, (char *)m_buffer.data(), bufferSize(), 0, (sockaddr *)&cliaddr, &clilen);
    // Avoid race condition
    m_peek--;
    if (m_peek < 0)
        m_peek = 0;

#else
    socklen_t clilen = sizeof(clilen);
    int recv_bytes = ::recvfrom(m_sockfd, (void *)m_buffer.data(), bufferSize(), MSG_WAITALL, (sockaddr *)&cliaddr, &clilen);
#endif
    occurError(recv_bytes, SocketError::UnknownSocketError, "Socket read failed!", 1);
    qDebug() << "Recv Bytes: " << recv_bytes << m_peek;
    if (recv_bytes > 0) {
        void *rawptr = static_cast<void*>(m_buffer.data());
#ifndef  _WIN32
        m_peek--;
        if (m_peek < 0)
            m_peek = 0;

#endif
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
        if (ret_fd > 0 && (m_fds.revents & POLLRDNORM)) {
            if (m_peek <= 0) {
                m_peek++;
                emit readyRead();
            }
        }
#else
        int ret_fd = poll(&m_fds, 1, timeout_ms);
        if (ret_fd > 0 && (m_fds.revents & POLLIN)) {
            if (m_peek <= 0) {
                m_peek++;
                emit readyRead();
            }
        }
#endif
    }

}

}
// UDP CLIENT CLASS END
