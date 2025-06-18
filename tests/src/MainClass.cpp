#include <QFile>

#include "MainClass.h"
#include "WeaNet/Internal/parserfile.h"


MainClass::MainClass(QObject *parent)
    : QObject(parent)
{

    //    m_sender = new Manager();
    //    m_sender->moveToThread(&threadSend);
    //    m_sender->setConnectionType(SocketType::Server);
    //    m_sender->setConnectionSetting(12345, 54321, "172.16.50.50");
    //    sender->onConnect();

    m_receiver = new Manager();
    m_receiver->moveToThread(&threadRecv);
    m_receiver->setConnectionType(SocketType::Server);
    m_receiver->setConnectionSetting(12347, 54321, "127.0.0.1");
    m_receiver->setConnectionTimeout(1, 10);
    m_receiver->setReadTimeout(1);
    m_receiver->setMaxReadRetries(10);
    m_receiver->setAutoReconnect(true);
    // m_receiver->onHighThroughput(true);
    //    QObject::connect(m_receiver->client, SIGNAL(connected()), this, SLOT([=]() {qDebug() << "CLIENT CONNECTED" ; }));
    //    QObject::connect(m_receiver->client, SIGNAL(disconnected()), this, SLOT([=]() {qDebug() << "CLIENT DISCONNECTED"<< m_receiver->client->autoReconnect();}));
    QObject::connect(m_receiver, SIGNAL(readyReads(QSharedPointer<QList<QSharedPointer<LogDataType>>> ,qreal,qreal)), this, SLOT(onReadyReads(QSharedPointer<QList<QSharedPointer<LogDataType>>> ,qreal,qreal)), Qt::DirectConnection);

    m_receiver->onConnect();

    //    threadSend.start();
    threadRecv.start();

    //    writeCsv("/home/Arvand/wearily/Log166Hub/docs/logData-slow.csv",
    //             "/home/Arvand/Desktop/logDataWearily.csv", 3000);

    // m_receiver->onSendLog("/home/Arvand/Desktop/logDataWearily.csv", -1, 3);
    // m_receiver->onSendLog("C:/Users/PARSA/Desktop/logger.csv", -1, 3);
    QMetaObject::invokeMethod(m_receiver, "onSendLog", Q_ARG(QString, "C:/Users/PARSA/Desktop/logger.csv"),
                              Q_ARG(int, -1),
                              Q_ARG(int, 3));
}


void MainClass::onReadyReads(QSharedPointer<QList<QSharedPointer<LogDataType>>> logs, qreal az, qreal time) {

    qDebug() << logs->constLast()->recvPackets.ctime << ' ' << logs->size() << ' ' << az << ' ' << time;
}

void MainClass::writeCsv(QString csvReadPath, QString csvWritePath, int rowToWrite) {
    std::vector<std::vector<double>> matrix = ParserFile::loadSlowData(csvReadPath);
    QFile file = QFile(csvWritePath);
    file.open(QFile::WriteOnly);
    for (int i = 0; i < rowToWrite && i < matrix.size(); ++i) {
        auto row = matrix[i];
        for (auto &col : row) {
            file.write(std::to_string(col).c_str());
            file.write(",");
        }
        file.write("\n");
    }
    file.close();
    qDebug() << "File wrote.";
}
