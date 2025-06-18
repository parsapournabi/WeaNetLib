#ifndef MAINCLASS_H
#define MAINCLASS_H

#include <WeaNet/Manager.h>

class MainClass : public QObject
{
    Q_OBJECT
public:
    explicit MainClass(QObject *parent = nullptr);

    void writeCsv(QString csvReadPath, QString csvWritePath, int rowToWrite);
public slots:
    void onReadyReads(QSharedPointer<QList<QSharedPointer<LogDataType>>> logs, qreal az, qreal time);
private:
    QThread threadRecv;
    QThread threadSend;
    Manager *m_sender = nullptr;
    Manager *m_receiver = nullptr;
};

#endif // MAINCLASS_H
