# WeaNet

## Description
### BSD-Based Network Library
This library porivdes there lightweight,
Qt-inspired C++ classes for handling netowrk communication using BSD sockets.
The design focuses on simplicity, performance, and clean object-oriented structure, making it ideal for use in high-performance, low-level systems while maintaining a familiar Qt-style API.
#### Classes Overview:
1. TcpServer
A non-blocking TCP server class built on top of poll(). It listens for incoming connections and creates new instances of TcpClient upon each accepted connection. Designed for scalability and easy intergration in event-driven applications.
2. TcpClient
A wrapper around a TCP socket, providing methods to connect to a remote host, sned and receive data, and monitor disconnection or errors.
Internally uses poll() to watch the socket file descriptor, Inspired by QTcpSocket, this class includes customizable callbacks to simulate signal sucha as connected(), disconnected(), and dataReceived().
3. Udp
A simple, flexible class for sending and receiving datagrams using UDP.
Supports both unicast and broadcast modes. Like QUdpSocket, it provides asynchronous-style event handling without depending on an external event loop.
### Key Features:
- Fully asynchronous, event-driven architecture (poll-based)
- Qt-style API with custom signal/slot-like mechanism (via std::function)
- Minimal dependencies (pure C++17 and POSIX)
- Design with CPU efficiency and thread-safety in mind
- Easy to integrate into non-Qt systems or embedded environments


## Contents

1. [Installation](#installation)
        - [Dependencies](#dependencies)
        - [Library Installation](#library-installation)
2. [Usage](#Usage)
        - [TcpClient](#tcpclient)
        - [TcpServer](#tcpserver)
        - [Udp](#udp)
        - [CMake Usage] (#cmake-usage)
3. [Platforms](#platforms)

## Installation
### Dependencies
        1- Qt5 Core lib.
        2- C++ 17 POSIX

### Library Installation
#### Linux
    1- chmod +x install.sh
    2- ./install.sh
    3- Or if you want to install on specific path do this: ./install.sh /your/path/WeaNet
#### Windows
    1- Build the Project.
    2- cd /to/build/path/
    3- cmake --install .
## Usage
### TcpClient
1- Referer to example/TcpClientExample.cpp

### TcpServer
1- Referer to example/TcpServerExample.cpp

### Udp
1- Referer to example/UdpExample.cpp

### CMake Usage
- You must include these lines to you Project CMakeLists.txt:
```CMakeLists
find_package(WeaNet REQUIRED)
# or you can Do by custom Prefix if the package isn't install to "/usr/local/WeaNet" or "C:\Program Files (x86)\WeaNet"
find_package(WeaNet REQUIRED PATHS "/to/your/installed/path/")

target_link_libraries(yourProjectName PRIVATE WeaNet::WeaNet)

# ONLY REQUIRED on Windows
if (_WIN32)
        target_compile_definitions(WeaNetExamples PRIVATE _WIN32_WINNT=0x0A00)
endif()
```
>[!WARNING]
> Remember to always implement this line of code at below to your project CMakeLists.txt (If you are using Windows).
```CMakeLists
target_compile_definitions(WeaNetExamples PRIVATE _WIN32_WINNT=0x0A00)
```

## Platforms
1- Linux
2- Windows




