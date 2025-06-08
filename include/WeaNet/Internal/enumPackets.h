#ifndef ENUMPACKETS_H
#define ENUMPACKETS_H

#include <iostream>
#include <cstring>
#include <vector>

enum PacketKind {
    TypeA = 0,
    TypeB = 1
};

// Packets
#pragma pack(push, 1)
union LogPacket {
    struct {
        double azimuth;
        double elevation;
        double rangeCell;
        double time;
        double power;
        double ctime;
    };
    double raw[6];

    LogPacket() {}

};
#pragma pack(pop)

#pragma pack(push, 1)
union PacketA {
    struct {
        uint8_t byte0 = 0x4e;
        uint8_t byte1 = 0x53;
        uint8_t byte2 = 0x52;
        uint8_t byte3 = 0x2a;
        uint8_t byte4 = 0x00;
        uint8_t byte5 = 0x00;
        uint8_t byte6 = 0x00;
        uint8_t byte7 = 0x01;
        uint8_t byte8 = 0x17;
        uint8_t byte9 = 0x00;
        uint8_t byte10 = 0x00;
        uint8_t byte11 = 0x00;
        uint8_t byte12 = 0x01;
        uint8_t byte13 = 0x00;
        uint8_t byte14 = 0x00;
        uint8_t byte15 = 0x00;
        uint8_t byte16 = 0x00;
        uint8_t byte17 = 0x00;
        uint8_t byte18 = 0x4a;
        uint8_t byte19 = 0xff;
    };
    uint8_t raw[20];

    PacketA() {}
};
#pragma pack(pop)

#pragma pack(push, 1)
union PacketB {
    struct {
        uint8_t byte0 = 0x4e;
        uint8_t byte1 = 0x53;
        uint8_t byte2 = 0x52;
        uint8_t byte3 = 0x2a;
        uint8_t byte4 = 0x00;
        uint8_t byte5 = 0x00;
        uint8_t byte6 = 0x00;
        uint8_t byte7 = 0x00;
        uint8_t byte8 = 0x17;
        uint8_t byte9 = 0x00;
        uint8_t byte10 = 0x00;
        uint8_t byte11 = 0x00;
        uint8_t byte12 = 0x01;
        uint8_t byte13 = 0x00;
        uint8_t byte14 = 0x00;
        uint8_t byte15 = 0x00;
        uint8_t byte16 = 0x00;
        uint8_t byte17 = 0x00;
        uint8_t byte18 = 0x4a;
        uint8_t byte19 = 0xff;
    };
    uint8_t raw[20];
    PacketB() {}
};
#pragma pack(pop)

#pragma pack(push, 1)
struct Packets {
    PacketA packetA;
    PacketB packetB;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct PacketManager {
    Packets packets;

    void getRaw(const int index, int &length, std::vector<uint8_t> &buffer) {
        // Clearing buffer
        std::fill(buffer.begin(), buffer.end(), 0x00);
        switch (index) {
        case PacketKind::TypeA:
            length = sizeof(packets.packetA.raw);
            mempcpy(buffer.data(), &packets.packetA.raw, length);
            break;
        case PacketKind::TypeB:
            length = sizeof(packets.packetB.raw);
            mempcpy(buffer.data(), &packets.packetB.raw, length);
            break;
        default:
            length = 0;
            break;

        }
    }
};
#pragma pack(pop)


#endif // ENUMPACKETS_H
