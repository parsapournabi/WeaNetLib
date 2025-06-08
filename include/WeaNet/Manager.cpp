//#include "parser.h"
#include <bits/stdc++.h>
#include <QThread>
#include <QVector>
#include <QStandardPaths>
#include <QDebug>
#include <QDataStream>
#include <cmath>

#include "Manager.h"
#include "WeaNet/Internal/parserfile.h"

//#define USE_UNION

namespace WeaNet {
const int BUFFER_SIZE = 64000;
const int TCP_BUFFER_SIZE = 1040;
const int BUFFER_LENGTH = 6;

QString FILE_PATH = QStandardPaths::writableLocation(QStandardPaths::HomeLocation) +"/Desktop/logData-166Recv.csv";
Manager::Manager(QObject *parent)
    : QObject(parent)
{
    qputenv("QT_ASSUME_STDERR_HAS_CONSOLE", "1");
    qDebug() << "Initialized!";

    // events & signal connection
//    QObject::connect(ui->rbTcpServer, &QRadioButton::clicked, this, &Manager::onSocketType);
//    QObject::connect(ui->rbTcpClient, &QRadioButton::clicked, this, &Manager::onSocketType);
//    QObject::connect(ui->rbUdp, &QRadioButton::clicked, this, &Manager::onSocketType);
//    QObject::connect(ui->cbHighThroughput, &QCheckBox::clicked, this, &Manager::onHighThroughput);
//    QObject::connect(ui->btnBind, &QPushButton::clicked, this, &Manager::onBindBtn);
//    QObject::connect(ui->btnConnect, &QPushButton::clicked, this, &Manager::onConnectBtn);
//    QObject::connect(ui->btnSend, &QPushButton::clicked, this, &Manager::onSendBtn);

    workerThread = new QThread();
    QObject::connect(workerThread, &QThread::started, this, &Manager::sendingCsvProcess);
    QObject::connect(this, &QObject::destroyed, workerThread, &QThread::quit);

    // Signal connection Tcp Client
    QObject::connect(client, SIGNAL(errorOccured(SocketError, const char*)), this, SLOT(onErrorOccured(SocketError, const char*)), Qt::DirectConnection);
    QObject::connect(client, SIGNAL(stateUpdated(SocketState, const char*)), this, SLOT(onStateUpdated(SocketState, const char*)), Qt::DirectConnection);
    QObject::connect(client, SIGNAL(dataReceived(void *, size_t)), this, SLOT(onDataReceived(void *, size_t)), Qt::DirectConnection);
    QObject::connect(client, SIGNAL(bytesWritten(int)), this, SLOT(onBytesWritten(int)), Qt::DirectConnection);

    // Signal connection Tcp Server
    QObject::connect(server, SIGNAL(errorOccured(SocketError, const char*)), this, SLOT(onErrorOccured(SocketError, const char*)), Qt::DirectConnection);
    QObject::connect(server, SIGNAL(stateUpdated(SocketState, const char*)), this, SLOT(onStateUpdated(SocketState, const char*)), Qt::DirectConnection);
    QObject::connect(server, SIGNAL(newConnection()), this, SLOT(onNewConnection()), Qt::DirectConnection);

    // Signal connection Udp
    QObject::connect(udp, SIGNAL(errorOccured(SocketError, const char*)), this, SLOT(onErrorOccured(SocketError, const char*)), Qt::DirectConnection);
    QObject::connect(udp, SIGNAL(stateUpdated(SocketState, const char*)), this, SLOT(onStateUpdated(SocketState, const char*)), Qt::DirectConnection);
    QObject::connect(udp, SIGNAL(dataReceived(void *, size_t, const char *, int)), this, SLOT(onDataReceivedUdp(void *, size_t, const char *, int)), Qt::DirectConnection);
    QObject::connect(udp, SIGNAL(bytesWritten(int)), this, SLOT(onBytesWritten(int)), Qt::DirectConnection);

    QObject::connect(this, SIGNAL(signalData(QByteArray*)), this, SLOT(onParseData(QByteArray*)), Qt::DirectConnection);


    // First view
    buffer.resize(BUFFER_SIZE);

    server->setDebugMode(true);
    client->setDebugMode(true);
    udp->setDebugMode(true);

    client->setAutoRead(true);
    //    client->setReadTimeout(30);
    //    client->setWriteTimeout(10);

    udp->setBufferSize(BUFFER_SIZE);
    udp->setAutoRead(true);

    //    client->setBlockingMode(false);
}

void Manager::setConnectionType(int type) {
    switch (type) {
    case SocketType::Client:
        m_socketType = SocketType::Client;
        break;

    case SocketType::Server:
        m_socketType = SocketType::Server;
        break;

    case SocketType::UdpSocket:
        m_socketType = SocketType::UdpSocket;
        break;
    default:
        qCritical() << "Invalid Socket Type!";
        break;
    }

}

int Manager::connectionType() const { return m_socketType; }
void Manager::setConnectionSetting(int sender_port, int receiver_port, const char* address) {
    m_senderPort = sender_port;
    m_receiverPort = receiver_port;
    m_host = address;
}

int Manager::receiverPort() const { return m_receiverPort; }
void Manager::setReceiverPort(int port) { m_receiverPort = port; }

int Manager::senderPort() const { return m_senderPort; }
void Manager::setSenderPort(int port) { m_senderPort = port; }

void Manager::onHighThroughput(bool enable) {
    client->setHighThroughputMode(enable);
    udp->setHighThroughputMode(enable);
}



int Manager::bufferSize() const {
    if (m_socketType == SocketType::Client) {
        return client->bufferSize();

    } else if (m_socketType == SocketType::Server) {
        for (auto &cli: m_acceptedClients)
            return cli->bufferSize();

    } else if (m_socketType == SocketType::UdpSocket) {
        return udp->bufferSize();
    }
    return -1;
}

double Manager::receiveSpeed() const { return RX_MB_S; }
double Manager::sendSpeed() const { return TX_MB_S; }

void Manager::setPauseSending(bool pause) { m_pauseSending = pause; }
bool Manager::pauseSending() const { return m_pauseSending; }

void Manager::onBind() {
    // If socketType is Tcp.
    if (m_socketType == SocketType::Server) {
        // If Object is nullptr or closed.
        if (!server->isOpen()) {

            // Setting some options
            server->setBufferSize(TCP_BUFFER_SIZE);
            // Address validation
            if (!server->isValidIPv4Address(m_host)){
                qCritical() << "Error" << "Invalid Local IP address!";
                return;
            }
            // Listening
            if (!server->listen(m_host, m_senderPort)) {
                return;
            }
        }

    }
    // else if socketType is Udp
    else if (m_socketType == SocketType::UdpSocket) {
        if (!udp->isOpen()) {
            // Setting some options
            udp->setBufferSize(64000);
            udp->setAutoRead(true);

            // Address validation
            if (!udp->isValidIPv4Address(m_host)){
                qCritical() << "Error" << "Invalid Local IP address!";
                return;
            }
            // Binding
            if (!udp->bind(m_host, m_senderPort)) {
                return;
            }
        }
    }
}

void Manager::onUnBound() {
    // If socketType is Tcp.
    if (m_socketType == SocketType::Server) {
        server->close();
        std::cout << "Server object deleted" << std::endl;
    }
    // else if socketType is Udp
    else if (m_socketType == SocketType::UdpSocket) {
        udp->close();
    }

}

void Manager::onConnect() {
    // If socketType is Tcp Client
    if (m_socketType == SocketType::Client) {
        if (!client->isOpen()){
            // Setting some options
            client->setAutoRead(true);
            client->setBufferSize(TCP_BUFFER_SIZE);
            // Address validation
            if (!client->isValidIPv4Address(m_host)){
                qCritical() << "Error" << "Invalid Local IP address!" << m_host;
                return;
            }
            // Connecting to server
            if (!client->connectToHost(m_host, m_senderPort)) {
                return;
            }
        }

        // else If socketType is Udp
    } else if (m_socketType == SocketType::UdpSocket) {
        // Validation
        if (!udp->isValid()){
            qCritical() <<  "Error" << "Socket isn't define!";
            return;

        }
        // Address validation
        if (!server->isValidIPv4Address(m_host)){
            qCritical() << "Error" << "Invalid Local IP address!";
            return;
        }
        udp->receiverConfig(m_host, m_receiverPort);

    }

}

void Manager::onDisconnect() {
    // If socketType is Tcp Client
    if (m_socketType == SocketType::Client) {
        // Closing client session
        client->close();

        // else If socketType is Udp
    } else if (m_socketType == SocketType::UdpSocket) {

    }

}
void Manager::onSend(QByteArray bytes) {
    std::vector<uint8_t> sendBuffer(bytes.begin(), bytes.end());

    if (m_socketType == SocketType::Client) {
        client->write((void *)sendBuffer.data());

    } else if (m_socketType == SocketType::Server) {
        for (auto &cli : m_acceptedClients) {
            cli->write((void *)sendBuffer.data());
        }

    } else if (m_socketType == SocketType::UdpSocket) {

        if (!udp->hasReceiver()) {
            qCritical() << "Error" << "No peer socket found!";
            return;
        }
        udp->writeDatagram((void *)sendBuffer.data());

    }

}

void Manager::onSendLog(QString csv_path, int interval_index) {
    if (workerThread->isRunning()) {
        qWarning() << "Warning" << "SendLog process is already running!";
        return;
    }
    // Reading csv data
    m_readCsvPath = csv_path;
    m_csvData = ParserFile::loadSlowData(m_readCsvPath);
    m_csvDataLen = m_csvData.size();
    m_interValIndex = interval_index;
    if (m_readCsvPath.isEmpty()) {
        qCritical() << "Error" << "Please upload yor smaple.csv file.";
        return;
    }

    // If Ready to send
    if (!workerThread) {
        qCritical() << "Error" << "Thread isn't created!";
        return;
    }
    setPauseSending(false);
    workerThread->start();
}

void Manager::sendingCsvProcess() {
    m_startTime = clock::now();
    m_elapsedTime = 0.0;
    m_csvReachedIndex = 0;
    while (!pauseSending() && m_csvReachedIndex < m_csvDataLen) {
        m_elapsedTime = std::chrono::duration_cast<std::chrono::nanoseconds>(clock::now() - m_startTime).count() / 10e8;
        LogPacket packet;
        for (int i = 0; i < m_csvData[m_csvReachedIndex].size(); ++i)
            packet.raw[i] = m_csvData[m_csvReachedIndex][i];
        packet.ctime = m_elapsedTime;
        int len = sizeof(packet.raw);
        std::fill(buffer.begin(), buffer.end(), 0x00);
        memcpy(buffer.data(), &packet.raw, len);
        onSend(QByteArray(reinterpret_cast<const char*>(buffer.data()), static_cast<int>(buffer.size())));
        m_startTime = clock::now();
        if (m_csvReachedIndex < m_csvDataLen) {
            int timeIndex = m_interValIndex;
            busyWait(m_csvData[m_csvReachedIndex + 1][timeIndex] - m_csvData[m_csvReachedIndex][timeIndex]);
        }
        m_csvReachedIndex++;

    }

}

void Manager::onNewConnection() {
    if (!server->hasPendingConnection())
        return;
    std::cout << "New Client Connected!" << std::endl;
    TcpClient* client = server->nexPendingConnection();
    m_acceptedClients.push_back(client);
    client->setAutoRead(true);
    client->setBufferSize(1040);
    //    QObject::connect(client, &TcpClient::readyRead, this, [client] () { client->read(); });
    QObject::connect(client, &TcpClient::errorOccured, this, &Manager::onErrorOccured, Qt::DirectConnection);
    QObject::connect(client, &TcpClient::stateUpdated, this, &Manager::onStateUpdated, Qt::DirectConnection);
    QObject::connect(client, &TcpClient::dataReceived, this, &Manager::onDataReceived, Qt::DirectConnection);
    QObject::connect(client, &TcpClient::bytesWritten, this, &Manager::onBytesWritten, Qt::DirectConnection);
//    QMetaObject::Connection conn = connect(ui->cbHighThroughput, &QCheckBox::clicked, this, [this, client] () {
//        client->setHighThroughputMode(ui->cbHighThroughput->isChecked());
//        std::cout << "Client set throughmode: " << client << " Also List size: " << m_clientSockets.size() << std::endl;});
    QObject::connect(client, &TcpClient::disconnected, this, [this, client] () {
        client->close();
//        disconnect(conn);
        m_acceptedClients.erase(std::remove(m_acceptedClients.begin(), m_acceptedClients.end(), client), m_acceptedClients.end());});
    std::cout << "Current thread on NewConnection(): " << QThread::currentThread() << std::endl;

}

void Manager::onReadyRead() {
    std::cout << "Data received on readyRead()" << std::endl;
}

void Manager::onDataReceived(void *p_buffer, size_t buf_len) {
    //    std::cout << "Data received on dataReceived()" << std::endl;
    std::string buf_str = std::to_string(buf_len);
#ifdef USE_UNION
    LogDataType *logDataType = new LogDataType();
    const char *raw = static_cast<const char*>(p_buffer);
    memcpy(logDataType->recvPackets.raw, &raw, sizeof(logDataType->recvPackets.raw));
    emit readyRead(logDataType);
#else

    const char *raw = static_cast<const char*>(p_buffer);
    QByteArray bytes(raw, buf_len);
    emit signalData(&bytes);
#endif

    if (std::chrono::duration_cast<std::chrono::nanoseconds>(clock::now() - m_rxStartTime).count() > 10e8) {
        // Speed calculating
        RX_MB_S = std::round((RX_bytes / 10e5) * 100.0) / 100.0;
        emit signalRecvSpeed(RX_MB_S);
        RX_bytes = 0.0;
        RX_MB_S = 0.0;
        m_rxStartTime = clock::now();
    }
    else RX_bytes += buf_len;
}

void Manager::onDataReceivedUdp(void *p_buffer, size_t buf_len, const char *host, int port) {
    std::string buf_str = std::to_string(buf_len);
#ifdef USE_UNION
    LogDataType *logDataType = new LogDataType();
    const char *raw = static_cast<const char*>(p_buffer);
    memcpy(logDataType->recvPackets.raw, &raw, sizeof(logDataType->recvPackets.raw));
    emit readyRead(logDataType);
#else
    const char *raw = static_cast<const char*>(p_buffer);
    QByteArray bytes(raw, buf_len);
    emit signalData(&bytes);
#endif
    if (std::chrono::duration_cast<std::chrono::nanoseconds>(clock::now() - m_rxStartTime).count() > 10e8) {
        RX_MB_S = std::round((RX_bytes / 10e5) * 100.0) / 100.0;
        emit signalRecvSpeed(RX_MB_S);

        RX_bytes = 0.0;
        RX_MB_S = 0.0;
        m_rxStartTime = clock::now();
    }
    else RX_bytes += buf_len;
}

void Manager::onParseData(QByteArray *bytes) {
//    qDebug() << "Bytes" << bytes->toHex();
//    qDebug() << "ByteSize: " << bytes->count();
//    qDebug() << "ServoPacket Before assign";
//    for (auto &r: recvPackets.raw)
//        qDebug() << r;
    LogDataType *logDataType = new LogDataType();
    memcpy(logDataType->recvPackets.raw, bytes->constData(), sizeof(logDataType->recvPackets.raw));

    emit readyRead(logDataType);
//    for (auto &r: recvPackets.raw)
//        qDebug() << r;
//    qDebug() << "Azimuth" << recvPackets.azimuth;
//    qDebug() << "Elv" << recvPackets.elevation;
//    qDebug() << "Range" << recvPackets.rangeCell;
//    qDebug() << "Time" << recvPackets.time;
//    qDebug() << "Power" << recvPackets.power;
//    qDebug() << "ctime" << recvPackets.ctime;
}

void Manager::onBytesWritten(int numSentBytes) {
    //    std::cout << "Bytes sent" << numSentBytes << std::endl;
    if (std::chrono::duration_cast<std::chrono::nanoseconds>(clock::now() - m_txStartTime).count() > 10e8) {
        TX_MB_S = std::round((TX_bytes / 10e5) * 100.0) / 100.0;
        emit signalSendSpeed(TX_MB_S);
//        std::ostringstream rounded;
//        rounded << std::fixed << std::setprecision(2) << TX_MB_S;
//        std::string throughput = rounded.str() + " MB/s";
//        std::cout << "Tx Speed (MB/s): " << TX_MB_S << std::endl;
        TX_bytes = 0.0;
        TX_MB_S = 0.0;
        m_txStartTime = clock::now();
    }
    else TX_bytes += numSentBytes;
}

void Manager::onErrorOccured(SocketError err_code, const char *err_message) {
}

void Manager::onStateUpdated(SocketState state, const char *state_message) {

}


void Manager::busyWait(double seconds) {
    auto st = clock::now();
    auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::duration<double>(seconds)).count();
    while (std::chrono::duration_cast<std::chrono::nanoseconds>(clock::now() - st).count() <= nanoseconds) {

    }

}
}
