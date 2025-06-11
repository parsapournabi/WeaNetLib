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
    m_receiver->setConnectionSetting(12345, 12345, "172.16.50.50");
//    m_receiver->client->setReadTimeout(10);
    m_receiver->client->setConnectionTimeout(1, -1);
    QObject::connect(m_receiver, &Manager::readyReads, this, [=] (QSharedPointer<QList<QSharedPointer<LogDataType>>> logs,
                                                                 qreal az,
                                                                 qreal time) {
        qDebug() << logs->size() << az << time;
    });

    //    m_receiver->onBind();
    m_receiver->onConnect();

//    threadSend.start();
    threadRecv.start();

//    writeCsv("/home/Arvand/wearily/Log166Hub/docs/logData-slow.csv",
//             "/home/Arvand/Desktop/logDataWearily.csv", 3000);

//    m_sender->onSendLog("/home/Arvand/Desktop/logData-slow1.csv", 1, 3);

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
