// Including C++ standard libraries

// Including self libraries
#include "WeaNet/Internal/network.h"
#include "WeaNet/Internal/error.h"

// Network class START
SocketType Network::socketType() const { return m_socketType; }

bool Network::debugMode() const { return m_debugMode; }

void Network::setDebugMode(const  bool mode) { m_debugMode = mode; }

void Network::setBlockingMode(const bool blocking) {
    // Update & err message
    const char *message;
    // Checking if is it possible to set flag
    if (m_sockfd < 0) {
        // Commit message
        message = "Failed to update socket flags, File descriptor access error.";
        // Raise exception & update state.
        occurError(m_sockfd, SocketError::SocketAccessError, message);
        updateState(SocketState::SocketFlags, message);
        return;
    }
    // Get socket flags.
#ifdef _WIN32
    u_long mode = blocking ? 0 : 1;
    int sock_flags = ioctlsocket(m_sockfd, FIONBIO, &mode);
#else
    int sock_flags = fcntl(m_sockfd, F_GETFL, 0);
    if (sock_flags < 0) {
        // Commit message
        message = "Failed to retrieve socket flags (fcntl F_GETFL).";
        // Raise exception & update state.
        updateState(SocketState::SocketFlags, message);
        occurError(m_sockfd, SocketError::SocketFlagError, message);
        return;
    }
    // Implementing non-blocking or blocking mode (depends on blocking arg).
    if (blocking)
        sock_flags &= ~O_NONBLOCK; // Earase O_NONBLOCK Mode.
    else
        sock_flags |= O_NONBLOCK; // Implementing non-blocking mode.
    // Set socket flags.
    if (fcntl(m_sockfd, F_SETFL, sock_flags) < 0) {
        // Commit message
        message = "Failed to update socket flags (fcntl F_SETFL).";
        // Raise exception & update state.
        updateState(SocketState::SocketFlags, message);
        occurError(m_sockfd, SocketError::SocketFlagError, message);
        return;
    }
#endif
    // Update state mode successfully set
    std::stringstream update_message;
    update_message << "Socket successfully set to " << (blocking ? "BLOCKING" : "NON-BLOCKING") << " Mode";
    updateState(SocketState::SocketFlags, update_message.str().c_str());

}

int Network::bufferSize() const { return m_bufferSize; }

void Network::setBufferSize(const int size) {
    m_bufferSize = size;
    m_buffer.resize(m_bufferSize);
}

int Network::socketOption(SocketOption option) {
    if (occurError(m_sockfd, SocketError::SocketAccessError, "Socket isn't defined!"))
        return -1;
    // opt var definition
    int opt;
#ifdef _WIN32
    int optlen = sizeof(opt);
    // get socket option
    int g = getsockopt(m_sockfd, SOL_SOCKET, option,(char *)&opt, &optlen);
#else
    socklen_t optlen = sizeof(opt);
    // get socket option
    int g = getsockopt(m_sockfd, SOL_SOCKET, option, &opt, &optlen);
#endif
    if (occurError(g, SocketError::SocketOptionError, "get socket option failed!"))
        return -1;
    // return opt var if getsockopt has no error
    return opt;

}

void Network::setServerReuseOption() {
    // Reuse Addr option...
    int opt_reuse = 1;
#ifdef _WIN32
    int opt_reuselen = sizeof(opt_reuse);
    int reuse_resp = setsockopt(m_sockfd, SOL_SOCKET, SO_REUSEADDR, (const char*)&opt_reuse, opt_reuselen);
#else
    socklen_t opt_reuselen = sizeof(opt_reuse);
    int reuse_resp = setsockopt(m_sockfd, SOL_SOCKET, SO_REUSEADDR, &opt_reuse, opt_reuselen);
#endif
    occurError(reuse_resp, SocketError::SocketOptionError, "Failed to set REUSEADDR option!");
}

void Network::setSocketOptions() {

    // Read Timeout option...
    timeval rcv_timeout;
    rcv_timeout.tv_sec = readTimeout();
    rcv_timeout.tv_usec = 0;
#ifdef _WIN32
    int rcv_timelen = sizeof(rcv_timeout);
    int rcv_resp = setsockopt(m_sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char *)&rcv_timeout, rcv_timelen);
#else
    socklen_t rcv_timelen = sizeof(rcv_timeout);
    int rcv_resp = setsockopt(m_sockfd, SOL_SOCKET, SO_RCVTIMEO, &rcv_timeout, rcv_timelen);
#endif
    occurError(rcv_resp, SocketError::SocketOptionError, "Failed to set SO_RCVTIMEO option!");

    // Write Timeout option...
    timeval snd_timeout;
    snd_timeout.tv_sec = writeTimeout();
    snd_timeout.tv_usec = 0;
#ifdef _WIN32
    int snd_timelen = sizeof(snd_timeout);
    int snd_resp = setsockopt(m_sockfd, SOL_SOCKET, SO_SNDTIMEO, (const char *)&snd_timeout, snd_timelen);
#else
    socklen_t snd_timelen = sizeof(snd_timeout);
    int snd_resp = setsockopt(m_sockfd, SOL_SOCKET, SO_SNDTIMEO, &snd_timeout, snd_timelen);
#endif
    occurError(snd_resp, SocketError::SocketOptionError, "Failed to set SO_SNDTIMEO option!");
}

bool Network::isOpen() const { return m_isConnected || m_isListening || m_isBind; }

bool Network::isValid() const { return !(m_sockfd < 0); }

bool Network::isValidIPv4Address(const char *host) const {
    // Craeting streaming string
    std::istringstream ss(host);
    std::string token;
    int segment = 0;

    while (std::getline(ss, token, '.')) {
        if (++segment > 4)
            return false;
        if (token.empty())
            return false;
        for (char c : token) {
            if (!std::isdigit(c))
                return false;
        }
        if (token.size() > 1 && token[0] == '0')
            return false;
        int value = std::stoi(token);
        if (value < 0 || value > 255)
            return false;

    }
    return segment == 4;

}

int Network::readTimeout() const { return m_rcvTimeout; }

void Network::setReadTimeout(int sec) { m_rcvTimeout = sec; }

int Network::writeTimeout() const { return m_sndTimeout; }

void Network::setWriteTimeout(int sec) { m_sndTimeout = sec; }

SocketError Network::latestError() const { return m_latestError; }

SocketState Network::latestState() const { return m_latestState; }

const char* Network::localAddress() const { return m_localAddress;}

int Network::localPort() const { return m_localPort;}

const char* Network::peerAddress() const{ return m_peerAddress;}

int Network::peerPort() const { return m_peerPort;}

int Network::socketDescriptor() const { return m_sockfd; }

void Network::close() {

    // Updating state.
    updateState(SocketState::ClosingState, "Socket Closed!");

    // Clearing memories
    cleanUp();

    // Closing socket.
#ifdef _WIN32
    ::closesocket(m_sockfd);
#else
    ::close(m_sockfd);
#endif
    m_sockfd = -1;

}
void Network::createSocket() {
    // Updating state
    updateState(SocketState::SocketCreation, "Creating socket...");


    // Config servaddr
    int socket_type;
    switch (socketType()) {
    case SocketType::Client:
        socket_type = SOCK_STREAM;
        break;
    case SocketType::Server:
        socket_type = SOCK_STREAM;
        break;
    case SocketType::UdpSocket:
        socket_type = SOCK_DGRAM;
        break;
    }
    m_sockfd = socket(Network::m_socketFamily, socket_type, 0);
    // Raise exception if we have an error.
    occurError(m_sockfd, SocketError::SocketAccessError, "Socket creation failed!");
    // Updating state
    if (latestError() == SocketError::NoError)
        updateState(SocketState::SocketCreated, "Socket created successfully.");
    else
        updateState(SocketState::NoSocketState, "Failed to create socket.");
}

void Network::setLocalAddress(const char *address) { m_localAddress = address; }

void Network::setLocalPort(int port_num) { m_localPort = port_num; }

void Network::setPeerAddress(const char *address) { m_peerAddress = address; }

void Network::setPeerPort(int port_num) { m_peerPort = port_num; }

void Network::locateAddresses() {
    // Configuring address
    struct sockaddr_in addr;
    socklen_t addrlen = sizeof(addr);
    int gsn = getsockname(m_sockfd, (sockaddr*)&addr, &addrlen);

    // Raise exception if we have an error while getsockname().
    occurError(gsn, SocketError::HostNotFoundError, "Get local address failed!");

    // If SocketType is TcpClient
    switch (socketType()) {
        case SocketType::Client:
            // Set server Address
            setPeerAddress(inet_ntoa(m_servaddr.sin_addr));
            // Set server Port
            setPeerPort(ntohs(m_servaddr.sin_port));

            // Set local Address
            setLocalAddress(inet_ntoa(addr.sin_addr));
            // Set local Port
            setLocalPort(ntohs(addr.sin_port));
            break;
        case SocketType::Server:
            // Set server Address
            setPeerAddress(inet_ntoa(addr.sin_addr));
            // Set server Port
            setPeerPort(ntohs(addr.sin_port));

            // Set local Address
            setLocalAddress(inet_ntoa(m_servaddr.sin_addr));
            // Set local Port
            setLocalPort(ntohs(m_servaddr.sin_port));
            break;
        case SocketType::UdpSocket:
            // Set server Address
            setPeerAddress(inet_ntoa(addr.sin_addr));
            // Set server Port
            setPeerPort(ntohs(addr.sin_port));

            // Set local Address
            setLocalAddress(inet_ntoa(m_servaddr.sin_addr));
            // Set local Port
            setLocalPort(ntohs(m_servaddr.sin_port));
            break;
    }

}

bool Network::occurError(int target, SocketError socketError, const char *err_message, int condition) {
    // Check if we have any error
    if (target < condition) {
        // getter of latestError()
        m_latestError = socketError;
        // Converting err_message
        std::string message = std::string(err_message);
        // Now time
        std::time_t now = std::time(nullptr);
        std::tm *local_time = std::localtime(&now);
        // Formating time
        std::ostringstream time_stream;
        time_stream << std::put_time(local_time, "%Y-%m-%d %H:%M:%S");

        switch (socketType()) {
        case SocketType::Client:
            message = time_stream.str() + " [Client] " + message;
            break;
        case SocketType::Server:
            message = time_stream.str() + " [Server] " + message;
            break;
        case SocketType::UdpSocket:
            message = time_stream.str() + " [UDP] " + message;
            break;
        }
#ifdef _WIN32
        int err = WSAGetLastError();
        char *msg = nullptr;
        FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                       NULL, err, 0, (LPSTR)&msg, 0, NULL);
        message = message + " Error details: " + msg;
        LocalFree(msg);
#else
        message = message + " Error details: " + strerror(errno);
#endif
        if (debugMode()) {
            std::cerr << message.c_str() << std::endl;
//            print_stacktrace();
        }
        emit errorOccured(socketError, message.c_str());
        return true;
    }
    else {
        // Clearing latest_error_
        m_latestError = SocketError::NoError;
        return false;
    }
}

void Network::updateState(SocketState socketState, const char *state_message) {
    m_latestState = socketState;
    std::string message = std::string(state_message);
    // Now time
    std::time_t now = std::time(nullptr);
    std::tm *local_time = std::localtime(&now);
    // Formating time
    std::ostringstream time_stream;
    time_stream << std::put_time(local_time, "%Y-%m-%d %H:%M:%S");

    switch (socketType()) {
    case SocketType::Client:
        message = time_stream.str() + " [Client] " + message;
        break;
    case SocketType::Server:
        message = time_stream.str() + " [Server] " + message;
        break;
    case SocketType::UdpSocket:
        message = time_stream.str() + " [UDP] " + message;
        break;
    }
    if (debugMode())
        std::cout << message.c_str() << std::endl;

    emit stateUpdated(socketState, message.c_str());

}

void Network::cleanUp() { // is not finished already
    // clearing varaibles to default. sock_fd_ = -1; is_bind = false; is_connected = false;
    m_isConnected = false;
    m_isListening = false;
    m_isBind = false;
//    m_pollLoop = false;
    // Clearing state & options variable to default.
    m_latestError = SocketError::NoError;
    m_latestState = SocketState::NoSocketState;
    m_localAddress = "";
    m_localPort = -1;
    m_peerAddress = "";
    m_peerPort = -1;
}
