#include <QFile>

#include "MainClass.h"
#include "WeaNet/Internal/parserfile.h"


MainClass::MainClass(QObject *parent)
    : Manager{parent}
{

//    m_sender = new Manager();
//    m_sender->moveToThread(&threadSend);
//    m_sender->setConnectionType(SocketType::Server);
//    m_sender->setConnectionSetting(12345, 54321, "172.16.50.50");
//    m_sender->onBind();
    //    sender->onConnect();

    m_receiver = new Manager();
    m_receiver->moveToThread(&threadRecv);
    m_receiver->setConnectionType(SocketType::Client);
    m_receiver->setConnectionSetting(54321, 54321, "127.0.0.1");
//    m_receiver->client->setConnectionTimeout(1, 10);
//    m_receiver->client->setReadTimeout(1);
//    m_receiver->client->setMaxReadRetries(10);
//    m_receiver->client->setAutoReconnect(true);
//    QObject::connect(m_receiver->client, SIGNAL(connected()), this, SLOT([=]() {qDebug() << "CLIENT CONNECTED" ; }));
//    QObject::connect(m_receiver->client, SIGNAL(disconnected()), this, SLOT([=]() {qDebug() << "CLIENT DISCONNECTED"<< m_receiver->client->autoReconnect();}));
    QObject::connect(m_receiver, &Manager::readyReads, this, [=] (QSharedPointer<QList<QSharedPointer<LogDataType>>> logs,
                                                                 qreal az,
                                                                 qreal time) {
            qDebug() << logs->constLast()->recvPackets.ctime << az << time;
                     });

//    m_receiver->onBind();
    m_receiver->onConnect();

//    threadSend.start();
    threadRecv.start();

//    writeCsv("/home/Arvand/wearily/Log166Hub/docs/logData-slow.csv",
//             "/home/Arvand/Desktop/logDataWearily.csv", 3000);

    m_receiver->onSendLog("/home/Arvand/Desktop/logDataWearily.csv", -1, 3);

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
