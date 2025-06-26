#include "monitor.h"

Monitor::Monitor(Manager *mng, QObject *parent) :
    m_mng(mng), QObject{parent}
{
}

Monitor::~Monitor()
{
}

void Monitor::start(int interval)
{
    if (m_timerId == -1) {
        m_timerId = startTimer(interval);
    }
}

void Monitor::stop()
{
    if (m_timerId == -1)
        return;
    killTimer(m_timerId);
    m_timerId = -1;
}

void Monitor::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == m_timerId)
        doUpdate();
}

void Monitor::doUpdate()
{
    monitorPtr data = monitorPtr::create();
    data->txSpeed = m_mng->sendSpeed();
    data->rxSpeed = m_mng->receiveSpeed();
    data->csvReachedRow = m_mng->csvReachedIndex();
    data->csvLength = m_mng->csvLength();
    emit signalDataUpdate(data);
}
