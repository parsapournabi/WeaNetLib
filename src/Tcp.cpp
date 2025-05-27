// Including C++ standard libraries
// Including self libraries
#include "WeaNet/Tcp.h"

using Clock = std::chrono::high_resolution_clock;
namespace WeaNet {
// TCP CLIENT CLASS START
TcpClient::TcpClient() {
#ifdef _WIN32
    WsaInitializer::ensureInitialized();
#endif

    // definition
    this->m_buffer.resize(m_bufferSize);
    this->m_socketType = SocketType::Client;

    this->m_isConnected = false;

    // threads & workers
    workerThread = new QThread();
    this->moveToThread(workerThread);

    // Signals & Events
    QObject::connect(workerThread, &QThread::started, this, &TcpClient::handlerPoll);
    QObject::connect(workerThread, &QThread::finished, workerThread, &QObject::deleteLater);

    // Monitor

    // Initialize
    workerThread->start();
}

#ifdef _WIN32
TcpClient::TcpClient(int sockfd, WSAPOLLFD fds) {

    // definition
    this->m_buffer.resize(m_bufferSize);
    this->m_socketType = SocketType::Client;

    this->m_pollLoop = false;
    this->m_isConnected = true;

    // workflow
    m_sockfd = sockfd;
    m_fds = fds;

    // SetOptions
    setSocketOptions();

    // Monitor

}
#else

TcpClient::TcpClient(int sockfd, struct pollfd fds) {

    // definition
    this->m_buffer.resize(m_bufferSize);
    this->m_socketType = SocketType::Client;

    this->m_pollLoop = false;
    this->m_isConnected = true;

    // workflow
    m_sockfd = sockfd;
    m_fds = fds;

    // SetOptions
    setSocketOptions();

    // Monitor

}
#endif

TcpClient::~TcpClient() {
    TcpClient::close();
}

bool TcpClient::connectToHost(const char* host, int port) {
    // Socket creation
    createSocket();

    // SetOptions
    setSocketOptions();

    // Update state (host lookup).
    updateState(SocketState::HostLookupState, "Scanning for host...");

    // Host address configuration
    m_servaddr.sin_family = m_socketFamily;
    m_servaddr.sin_addr.s_addr = inet_addr(host);
    m_servaddr.sin_port = htons(port);
    m_servlen = sizeof(m_servaddr);

    // Update state (Attempting connection)
    updateState(SocketState::ConnectingState, "Attempting secure connection...");

    // Trying to connect
    int c = ::connect(m_sockfd, (const struct sockaddr*)&m_servaddr, m_servlen);
    // Check connection response...
    if (!occurError(c, SocketError::ConnectionRefusedError, "Connectoin failed! Host unreachable.")) {
        // Locating local & peer address
        locateAddresses();

        // Update state (Server found)
            // Status message var
        std::stringstream update_message;
        update_message << "Found server at " << peerAddress() << ':' << peerPort();
        updateState(SocketState::ConnectingState, update_message.str().c_str());
        // Clearing update_message
        update_message.str("");
        update_message.clear();

    }


    // Assign true if response is not -1 else false
    m_isConnected = c < 0 ? false : true;


    // Set host & peer addresses & ports
    if (m_isConnected) {
        // Signal emit
        emit connected();
        // Updating status
        updateState(SocketState::ConnectedState, "Connection esablished successfully.");

        // Poll Config
        m_fds.fd = m_sockfd;
#ifdef _WIN32
        m_fds.events = POLLRDNORM;
#else
        m_fds.events = POLLIN;
#endif
    }
    else
        // Updating status
        updateState(SocketState::UnconnectedState, "Connection failed! Host unreachable.");

    // Definition
    m_peek = 0;

    return isConnected();
}

void TcpClient::disconnectFromHost() {
    emit disconnected();
}

bool TcpClient::isConnected() const { return m_isConnected; }

void TcpClient::read() {
    if (occurError(m_sockfd, SocketError::SocketAccessError, "Socket isn't defined!"))
        return;
    if (m_isConnected == false) {
        occurError(-1, SocketError::UnsupportedSocketOperationError, "Socket isn't connect!");
        return;
    }
#ifdef _WIN32
    int recv_bytes = ::recv(m_sockfd, (char *)m_buffer.data(), bufferSize(), MSG_WAITALL);
#else
    int recv_bytes = ::recv(m_sockfd, (void *)m_buffer.data(), bufferSize(), MSG_WAITALL);
#endif
    occurError(recv_bytes, SocketError::UnknownSocketError, "Socket read failed!", 1);

    // Data received
    if (recv_bytes > 0) {
        void *rawptr = static_cast<void*>(m_buffer.data());
        m_peek--;
        if (m_peek < 0)
            m_peek = 0;
        emit dataReceived(rawptr, recv_bytes);
    }
    // Means Server disconnected
    else if (recv_bytes == 0) {
        emit disconnected();
    }
    // Means we have an error on recv.
    else {
        // Checking if error number is equal to Disconnected client.
        if (errno != EWOULDBLOCK && errno != EAGAIN) {
            emit disconnected();
        }
    }
}

int TcpClient::write(void *buffer, int flags) {
    if (occurError(m_sockfd, SocketError::SocketAccessError, "Socket isn't defined!"))
        return -1;
    if (m_isConnected == false) {
        occurError(-1, SocketError::UnsupportedSocketOperationError, "Socket isn't connect!");
        return -1;
    }

#ifdef _WIN32
    int s = ::send(m_sockfd, (char *)buffer, bufferSize(), flags);
#else
    int s = ::send(m_sockfd, buffer, bufferSize(), flags);
#endif
    if(!occurError(s, SocketError::SocketTimeoutError, "No bytes sent!", 1))
        emit bytesWritten(s);
    return s;
}

void TcpClient::setAutoRead(bool auto_read) {
    if (auto_read == true) {
        QObject::connect(this, &TcpClient::readyRead, this, &TcpClient::read, Qt::DirectConnection);
    }
    else {
        QObject::disconnect(this, &TcpClient::readyRead, this, &TcpClient::read);
    }
}

void TcpClient::close() {
    setAutoRead(false);
    m_peek = 0;
    std::cout << "Tcp Close called: " << m_peek << std::endl;
    Network::close();
}

bool TcpClient::isHighThroughputMode() const { return m_highThroughputMode; }

void TcpClient::setHighThroughputMode(bool enabled) { m_highThroughputMode = enabled; }

void TcpClient::handlerPoll() {
    // Receiving loop...
    while (m_pollLoop) {
        if (!isConnected()) {
            QThread::msleep(100);
            continue;
        }
        handlerRead();
    }
}

void TcpClient::handlerRead() {
    if (isHighThroughputMode()) {
        if (m_peek <= 0) {
            m_peek++;
            read();
        }
    }
    else {
        // Poll timeout
        int timeout_ms = 200;
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
// TCP CLIENT CLASS END

// TCP SERVER CLASS START
TcpServer::TcpServer() {

#ifdef _WIN32
    WsaInitializer::ensureInitialized();
#endif

    // definition
    this->m_socketType = SocketType::Server;
    this->m_isListening = false;

    // threads & workers
    workerThread = new QThread();
    this->moveToThread(workerThread);

    // Signals & Events
    QObject::connect(workerThread, &QThread::started, this, &TcpServer::handlerPoll);
    QObject::connect(workerThread, &QThread::finished, workerThread, &QObject::deleteLater);

    // Monitor

    // Initializers
    workerThread->start();
}

TcpServer::~TcpServer() {
    TcpServer::close();
}

int TcpServer::maxPendingConnections() const { return m_maxPendingConnections; }

void TcpServer::setMaxPendingConnections(int numConnections) { m_maxPendingConnections = numConnections; }

void TcpServer::pauseAccepting() { m_resumeAccepting = false; }

void TcpServer::resumeAccepting() { m_resumeAccepting = true; }

bool TcpServer::listen(const char *host, int port) {

    // workflow
    createSocket();

    // SetOptions
    setServerReuseOption();

    // Server configuration
    memset(&m_servaddr, 0, sizeof(m_servaddr));
    m_servaddr.sin_family = m_socketFamily;
    m_servaddr.sin_port = htons(port);
    m_servaddr.sin_addr.s_addr = inet_addr(host);

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
    if (occurError(b, SocketError::SocketBindError, "Socket binding failed!"))
        return false;

    // Update State (Server bound).
    updateState(SocketState::BoundState, "Socket bound to interface successfully.");

    // Listen & check erros
    int l = ::listen(m_sockfd, maxPendingConnections());
    if (occurError(l, SocketError::SocketBindError, "Socket listen failed!"))
        return false;

    // Poll Cofigurations
#ifdef _WIN32
    WSAPOLLFD servPoll;
    servPoll.fd = m_sockfd;
    servPoll.events = POLLRDNORM;
#else
    pollfd servPoll;
    servPoll.fd = m_sockfd;
    servPoll.events = POLLIN;
#endif
    // Adding to list.
    m_polls.push_back(servPoll);

    // listening successfully
    m_isListening = true;

    // Update State (listening mode).
    updateState(SocketState::ListeningState, "Ready to accept incoming connections.");

    return isListening();

}

bool TcpServer::isListening() const { return m_isListening; }

TcpClient* TcpServer::nexPendingConnection() {
    if (m_pendingConnections.empty())
        return nullptr;
    // Dequeue & return
    auto first = m_pendingConnections.front();
    m_pendingConnections.erase(m_pendingConnections.begin());
    return first;
}

bool TcpServer::hasPendingConnection() const { return m_pendingConnections.empty() ? false : true; }

void TcpServer::close() {
    // Closing all of the connected sockets
    for (auto &client: m_clients) {
        client->disconnectFromHost();
    }
    // Closing current socket file descriptor.
    m_pendingConnections.clear();
    m_clients.clear();
    m_polls.clear();
    Network::close();

}

void TcpServer::handlerPoll() {
    // update message var
    std::stringstream update_message;
    constexpr int TIMEOUT = 100;
    constexpr int CLOCK_RATE = 10e8;
    auto st = Clock::now(); // A simple clock for raising error each 2 seconds

    // Event loop
    while (m_pollLoop) {
        if (!isListening() || !m_resumeAccepting || m_pendingConnections.size() >= maxPendingConnections()) {
            QThread::msleep(250);
            continue;
        }
#ifdef _WIN32
        int ret = WSAPoll(m_polls.data(), m_polls.size(), TIMEOUT);
#else
        int ret = poll(m_polls.data(), m_polls.size(), TIMEOUT);
#endif
        // Error handling
        if (ret < 0) {
            auto diff = std::chrono::duration_cast<std::chrono::nanoseconds>(Clock::now() - st).count();
            if (diff > CLOCK_RATE)
                occurError(ret, SocketError::UnknownSocketError, "Server poll response error!");
        }
        // New Client wants connect to the server
#ifdef _WIN32
        auto pollresult = (m_polls[0].revents & POLLRDNORM);
#else
        auto pollresult = (m_polls[0].revents & POLLIN);
#endif
        if (ret > 0 && pollresult) {
            struct sockaddr_in cliaddr;
            socklen_t clilen = sizeof(cliaddr);

            int cli_sockfd = accept(m_sockfd, (struct sockaddr*)&cliaddr, &clilen);
            if (occurError(cli_sockfd, SocketError::UnknownSocketError, "Server Accepting failed!"))
                continue;
            // If cli_sockfd is fine, must enqueue to m_pendingConnections
#ifdef _WIN32
            WSAPOLLFD cliPoll;
            cliPoll.fd = cli_sockfd;
            cliPoll.events = POLLRDNORM;
#else
            pollfd cliPoll;
            cliPoll.fd = cli_sockfd;
            cliPoll.events = POLLIN;
#endif
            auto* client = new TcpClient(cli_sockfd, cliPoll);

            m_polls.push_back(cliPoll);
            m_pendingConnections.push_back(client);
            m_clients.push_back(client);

            // Signal
            QObject::connect(client, &TcpClient::disconnected, this, [this, client] () {
                    // Index locating
                    auto it = std::find(m_clients.begin(), m_clients.end(), client);
                    if (it != m_clients.end()) {
                        int index = std::distance(m_clients.begin(), it);
                        // Erasing on m_clients & m_polls
                        m_clients.erase(m_clients.begin() + index);
                        m_polls.erase(m_polls.begin() + index + 1);
                    }
                    else {
                        std::cout << "No clients found on deleting state!" << std::endl;
                    }
                    // Erasing disconnected client socket
                    m_pendingConnections.erase(std::remove(m_pendingConnections.begin(), m_pendingConnections.end(), client), m_pendingConnections.end());
                    std::cout << "Client removed! Poll size: " << m_polls.size() << std::endl;
                }, Qt::DirectConnection);

            // Update State (new Client accepted)
            update_message << "Client connected from " << inet_ntoa(cliaddr.sin_addr) << ':' << ntohs(cliaddr.sin_port);
            updateState(SocketState::AcceptedState, update_message.str().c_str());
            // Clearing update_message
            update_message.str("");
            update_message.clear();

            // emit newConnection
            emit newConnection();

        }
        for (size_t i=1; i < m_polls.size(); i++) {
            m_clients[i - 1]->handlerRead();
        }

    }
}
// TCP SERVER CLASS END

}
