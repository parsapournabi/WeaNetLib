#include <iostream>
#include <QByteArray>
#include <QDataStream>
#include <WeaNet/Manager.h>

using namespace WeaNet;

int main() {
    /** Receiver Config **/
    QThread* threadRecv = new QThread();
    Manager* receiver = new Manager();
    receiver->moveToThread(threadRecv);
    receiver->setConnectionType(SocketType::Client);
    receiver->setConnectionSetting(54321, 12345, "127.0.0.1");
    // Client options
    receiver->client->setConnectionTimeout(1, 10);
    receiver->client->setReadTimeout(1);
    receiver->client->setMaxReadRetries(10);
    receiver->client->setAutoReconnect(true);
//    receiver->onBind(); /** Only on UDP & Server **/
    receiver->onConnect(); /** Only on UDP & Client**/

    QObject::connect(receiver, &Manager::readyReads, receiver, [=] (QSharedPointer<QList<QSharedPointer<LogDataType>>> logDatas,
                                                      qreal az,
                                                      qreal time) {
            qDebug() << "Azimuth" << logDatas->constFirst()->azimuth();
            qDebug() << "Elv" << logDatas->constFirst()->elevation();
            qDebug() << "Range" << logDatas->constFirst()->range();
            //    qDebug() << "Time" <<
            qDebug() << "Power" << logDatas->constFirst()->power();
            //    qDebug() << "ctime" << recvPackets.ctime;

            QByteArray byte = logDatas->constFirst()->rawData();
            qDebug() << "RawData: " << byte.toHex();
            QDataStream ds(&byte,QIODevice::ReadOnly);
            ds.setByteOrder(QDataStream::LittleEndian);
            double header;
            ds >> header;
            qDebug() << "header: " << header;
            ds >> header;
            qDebug() << "header: " << header;
        }, Qt::DirectConnection);
    threadRecv->start();

    /** Sender Config **/
    QThread* threadSend = new QThread();
    Manager* sender = new Manager();
    sender->moveToThread(threadSend);

    sender->setConnectionType(2); // Udp (0 = TcpClient, 1 = TcpServer, 2 = UdpSocket)
    sender->setConnectionSetting(12345, 54321, "127.0.0.1"); // Replace with your own ip & ports
    sender->onBind();
    sender->onConnect(); // Assigning the peer port & address
    threadSend->start();

    sender->onSendLog("/home/Arvand/wearily/Log166Hub/docs/logData-slow.csv", 3); // Edit the path
    QThread::sleep(1);


    return 0;
}
