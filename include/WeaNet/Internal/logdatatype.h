#ifndef LOGDATATYPE_H
#define LOGDATATYPE_H

#include <QObject>
#include "WeaNet/Internal/enumPackets.h"

class LogDataType : public QObject
{
    Q_OBJECT
public:
    explicit LogDataType(QObject *parent = nullptr);

    double azimuth() const;
    double elevation() const;
    double range() const;
    double time() const;
    double power() const;
    QVector<double> rawVec();
    QByteArray rawData() const;

public:
    LogPacket recvPackets;

};

#endif // LOGDATATYPE_H
