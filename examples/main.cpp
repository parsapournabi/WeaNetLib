#include <iostream>
#include <QByteArray>
#include <QDataStream>
#include <WeaNet/Manager.h>

using namespace WeaNet;

int main() {

    QThread* threadRecv = new QThread();
    Manager* receiver = new Manager();
    receiver->moveToThread(threadRecv);
    receiver->setConnectionType(2);
    receiver->setConnectionSetting(54321, 12345, "127.0.0.1");
    receiver->onBind();
    receiver->onConnect();

    QThread* threadSend = new QThread();
    Manager* sender = new Manager();
    sender->moveToThread(threadSend);

    sender->setConnectionType(2); // Udp (0 = TcpClient, 1 = TcpServer, 2 = UdpSocket)
    sender->setConnectionSetting(12345, 54321, "127.0.0.1"); // Replace with your own ip & ports
    sender->onBind();
    sender->onConnect(); // Assigning the peer port & address

    threadRecv->start();
    threadSend->start();

    //    std::vector<double> buff(1040, 0x00);
//    double raw[7] = { 1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.7};
//    size_t len = sizeof(raw);
    //    QByteArray bytes(reinterpret_cast<const char*>(raw), len);

    sender->onSendLog("/home/Arvand/wearily/Log166Hub/docs/logData-slow.csv", 3); // Edit the path
    QThread::sleep(1);

    QObject::connect(receiver, &Manager::readyRead, receiver, [=] () {
        qDebug() << "Azimuth" << receiver->azimuth();
        qDebug() << "Elv" << receiver->elevation();
        qDebug() << "Range" << receiver->range();
    //    qDebug() << "Time" <<
        qDebug() << "Power" << receiver->power();
    //    qDebug() << "ctime" << recvPackets.ctime;

        QByteArray byte = receiver->rawData();
        qDebug() << "RawData: " << byte.toHex();
        QDataStream ds(&byte,QIODevice::ReadOnly);
        ds.setByteOrder(QDataStream::LittleEndian);
        double header;
        ds >> header;
        qDebug() << "header: " << header;
        ds >> header;
        qDebug() << "header: " << header;
        }, Qt::DirectConnection);

    return 0;
}
