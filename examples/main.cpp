#include <iostream>
#include <WeaNet/Tcp.h>

using namespace WeaNet;

int main() {
    std::cout << "Process started.." << std::endl;

    TcpServer *server = new TcpServer();
    server->listen("127.0.0.1", 12345);

    return 0;
}
