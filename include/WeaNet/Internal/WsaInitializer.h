#ifndef WSAINITIALIZER_H
#define WSAINITIALIZER_H

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <iostream>
#include <exception>

#pragma comment(lib, "ws2_32.lib")

class WsaInitializer {
public:
    static void ensureInitialized() {
        static WsaInitializer instance;
    }
    ~WsaInitializer() {
        WSACleanup();
    }
private:
    WsaInitializer() {
        WSADATA wsaData;
        int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
        if (result < 0)
            throw std::runtime_error("WSAStartup failed!");
    }
    WsaInitializer(const WsaInitializer&) = delete;
    WsaInitializer& operator=(const WsaInitializer&) = delete;

};
#endif

#endif // WSAINITIALIZER_H
