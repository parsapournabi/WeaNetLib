#ifndef MONITOR_H
#define MONITOR_H

#include <QObject>
#include <QTimerEvent>
#include <QBasicTimer>

#include "WeaNet/Manager.h"

struct MonitorData {
    double txSpeed;
    double rxSpeed;
    double csvReachedRow;
    double csvLength;
};

class Monitor : public QObject
{
    Q_OBJECT
public:
    typedef QSharedPointer<MonitorData> monitorPtr;

    explicit Monitor(Manager *mng, QObject *parent = nullptr);
    ~Monitor();
    void start(int interval = 1000);
    void stop();

signals:
    void signalDataUpdate(monitorPtr data);

protected:
    void timerEvent(QTimerEvent *e) override;

private:
    void doUpdate();

    int m_timerId = -1;
    Manager *m_mng = nullptr;
    QBasicTimer timer;

};

#endif // MONITOR_H
