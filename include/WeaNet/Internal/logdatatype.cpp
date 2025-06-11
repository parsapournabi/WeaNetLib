#include "logdatatype.h"

LogDataType::LogDataType(QObject *parent)
    : QObject{parent}
{

}

double LogDataType::azimuth() const { return recvPackets.azimuth; }
double LogDataType::elevation() const { return recvPackets.elevation; }
double LogDataType::range() const { return recvPackets.rangeCell; }
double LogDataType::time() const { return recvPackets.time; }
double LogDataType::power() const { return recvPackets.power; }
QByteArray LogDataType::rawData() const {
    return QByteArray(reinterpret_cast<const char*>(recvPackets.raw),
                      sizeof(recvPackets.raw));
}
