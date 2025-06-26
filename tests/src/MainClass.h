#ifndef MAINCLASS_H
#define MAINCLASS_H

#include <WeaNet/Manager.h>
#include "monitor.h"

class MainClass : public QObject
{
    Q_OBJECT
public:
    explicit MainClass(QObject *parent = nullptr);

    void writeCsv(QString csvReadPath, QString csvWritePath, int rowToWrite);
    void readCsv(QString csvReadPath);
public slots:
    void onReadyReads(QSharedPointer<QList<QSharedPointer<LogDataType>>> logs, qreal az, qreal time);
private:
    QThread threadRecv;
    QThread thMonitor;
    Manager *m_receiver = nullptr;
    Monitor *monitor = nullptr;
};

#endif // MAINCLASS_H
