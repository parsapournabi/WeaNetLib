#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include <iostream>
#include <chrono>

#include "WeaNet/Tcp.h"
#include "WeaNet/Udp.h"
#include "WeaNet/Internal/net_enums.h"
#include "WeaNet/Internal/enumPackets.h"
#include "WeaNet/Internal/logdatatype.h"

using namespace WeaNet;
namespace WeaNet {
class Manager : public QObject
{
    Q_OBJECT
    using clock = std::chrono::high_resolution_clock;
    using TimePoint = std::chrono::time_point<clock>;
public:
    explicit Manager(QObject *parent = nullptr);

    /// @return int: 0 == ClientTcp
    /// @return int: 1 == ServerTcp
    /// @return int: 2 == Udp
    int connectionType() const;

    int receiverPort() const;

    int senderPort() const;

    int bufferSize() const;

    double receiveSpeed() const;
    double sendSpeed() const;

    void setPauseSending(bool pause);
    bool pauseSending() const;


signals:
    void signalData(QByteArray *);
    /// @details Speed MB/s
    void signalRecvSpeed(double speed);
    /// @details Speed MB/s
    void signalSendSpeed(double speed);

    void readyRead(LogDataType *);

    void readyReads(QSharedPointer<QList<QSharedPointer<LogDataType>>> logs, qreal az, qreal time);

public slots:

    /// @param int: 0 == ClientTcp
    /// @param int: 1 == ServerTcp
    /// @param int: 2 == Udp
    void setConnectionType(int type);

    void setConnectionSetting(int sender_port, int receiver_port, const char* address);

    void setReceiverPort(int port);

    void setSenderPort(int port);

    void onHighThroughput(bool enable);

    void onBind();

    void onUnBound();

    void onConnect();

    void onDisconnect();

    void onSend(QByteArray bytes);

    void onSendLog(QString csv_path, int interval_index = 3);

    void sendingCsvProcess();

    void onNewConnection();

    void onReadyRead();

    void onDataReceived(void *p_buffer, size_t buf_len);

    void onDataReceivedUdp(void *p_buffer, size_t buf_len, const char *host, int port);

    void onParseData(QByteArray *bytes);

    void onBytesWritten(int numSentBytes);

    void onErrorOccured(SocketError err_code, const char *err_message);

    void onStateUpdated(SocketState state, const char *state_message);

private:

    void busyWait(double seconds);

public:
    // Public variables

    TcpClient *client = new TcpClient();public:
    TcpServer *server = new TcpServer();
    Udp *udp = new Udp();

private:
    QThread *workerThread = nullptr;
    TimePoint m_rxStartTime = clock::now();
    TimePoint m_rxStartTimeGui = clock::now();
    TimePoint m_rxUdpStartTimeGui = clock::now();
    TimePoint m_txStartTime = clock::now();
    std::vector<TcpClient*> m_acceptedClients;
    std::vector<uint8_t> buffer;

    PacketManager m_packetManager;
    double RX_MB_S = 0.0;
    double RX_bytes = 0.0;
    double TX_MB_S = 0.0;
    double TX_bytes = 0.0;

    SocketType m_socketType;
    const char *m_host = "";
    int m_senderPort = 12345;
    int m_receiverPort = 12346;

    std::vector<std::vector<double>> m_csvArray;
    QString m_readCsvPath;
    std::vector<std::vector<double>> m_csvData;
    size_t m_csvDataLen;
    std::ofstream file;
    bool m_writeCsv = false;
    bool m_pauseSending = false;
    long m_csvReachedIndex = 0;
    TimePoint m_startTime = clock::now();
    double m_elapsedTime = 0.0;
    int m_interValIndex = 3;
    int m_azimuthIndex = 0;
};
}

#endif // MANAGER_H
