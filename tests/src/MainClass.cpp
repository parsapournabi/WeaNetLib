#include <QFile>
#include <QEventLoop>

#include "MainClass.h"
#include "WeaNet/Internal/parserfile.h"


MainClass::MainClass(QObject *parent)
    : QObject(parent)
{
    m_receiver = new Manager();
    m_receiver->moveToThread(&threadRecv);    
    m_receiver->setConnectionType(SocketType::UdpSocket);
    m_receiver->setConnectionSetting(54321, 12345, "172.16.50.50");
    m_receiver->setConnectionTimeout(1, 10);
    m_receiver->setReadTimeout(1);
    m_receiver->setMaxReadRetries(10);
    m_receiver->setAutoReconnect(true);
    // m_receiver->onHighThroughput(true);
  //    QObject::connect(m_receiver->client, SIGNAL(connected()), this, SLOT([=]() {qDebug() << "CLIENT CONNECTED" ; }));
  //    QObject::connect(m_receiver->client, SIGNAL(disconnected()), this, SLOT([=]() {qDebug() << "CLIENT DISCONNECTED"<< m_receiver->client->autoReconnect();}));
    QObject::connect(m_receiver, SIGNAL(readyReads(QSharedPointer<QList<QSharedPointer<LogDataType>>> ,qreal,qreal)), this, SLOT(onReadyReads(QSharedPointer<QList<QSharedPointer<LogDataType>>> ,qreal,qreal)), Qt::DirectConnection);

    m_receiver->onConnect();

    monitor = new Monitor(m_receiver);
    monitor->moveToThread(&thMonitor);

    QObject::connect(monitor, &Monitor::signalDataUpdate, this, [=] (QSharedPointer<MonitorData> data) {
        qDebug() << data->csvReachedRow << data->csvLength << data->rxSpeed << data->txSpeed;
    });
    QObject::connect(&thMonitor, &QThread::started, monitor, [=]() { monitor->start(1000); });

    threadRecv.start();
    thMonitor.start();

    //    writeCsv("/home/Arvand/wearily/Log166Hub/docs/logData-slow.csv",
    //             "/home/Arvand/Desktop/logDataWearily.csv", 3000);

    // m_receiver->onSendLog("/home/Arvand/Desktop/logDataWearily.csv", -1, 3);
    QMetaObject::invokeMethod(m_receiver, "onSendLog", Q_ARG(QString, "/home/Arvand/Desktop/logData-slow.csv"),
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

void MainClass::readCsv(QString csvReadPath)
{

    QFile file(csvReadPath);
    if (file.open(QFile::ReadOnly)) {
        QTextStream stream(&file);
        QString line;
        double pre_time = 0.0;
        int row = -1;
        while (stream.readLineInto(&line)) {
            row++;
            bool ok;
            double time = line.split(',')[3].toDouble(&ok);
            if (!ok) {
                qDebug() << "Not Ok" << time << line;
                continue;
            }
            if (!pre_time) {
                qDebug() << "On First" << row << pre_time << time;
                pre_time = time;
                continue;
            }
            if ((time - pre_time) > 0.008)
                qDebug() << row << line.split(',').constFirst() << pre_time << time - pre_time;
            pre_time = time;
        }

        file.close();
//        qDebug() << stream.readLine();
//        qDebug() << stream.readLine();
//        qDebug() << stream.readLine();


    }
}
