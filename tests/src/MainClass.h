#ifndef MAINCLASS_H
#define MAINCLASS_H

#include <WeaNet/Manager.h>

class MainClass : public Manager
{
    Q_OBJECT
public:
    explicit MainClass(QObject *parent = nullptr);

    void writeCsv(QString csvReadPath, QString csvWritePath, int rowToWrite);

private:
    QThread threadRecv;
    QThread threadSend;
    Manager *m_sender = nullptr;
    Manager *m_receiver = nullptr;
};

#endif // MAINCLASS_H
