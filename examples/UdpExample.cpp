#ifdef EXAMPLE_MODE
// Importing module
#include <WeaNet/Udp.h>

// Easy usage
using namespace WeaNet;

// Creating an object from TcpClient class.
Udp *udp = new Udp();

class MainWindow {

public:
    MainWindow() {
        // Signal connection
        /** Make Sure your connecting with  'Qt::DirectConnection' connectionType. **/
        QObject::connect(udp, &Udp::errorOccured, this, &MainWindow::onErrorOccured, Qt::DirectConnection);
        QObject::connect(udp, &Udp::stateUpdated, this, &MainWindow::onStateUpdated, Qt::DirectConnection);
        /** Recommendation: Don't use readyRead if you need High reading rate. Just setAutoRead(true). **/
        //QObject::connect(udp, &Udp::readyRead, this, &MainWindow::onReadyRead, Qt::DirectConnection);
        QObject::connect(udp, &Udp::dataReceived, this, &MainWindow::onDataReceivedUdp, Qt::DirectConnection);
        QObject::connect(udp, &Udp::bytesWritten, this, &MainWindow::onBytesWritten, Qt::DirectConnection);
        /** NOTE: Other signals like dataReceived, readyRead, bytesWritten and ... must be connect from acceptedClient. **/


        // Setting some options
        /** TcpClient class options & Properties **/
        udp->setAutoRead(true); // Hover on function for hints.
        udp->isHighThroughputMode(); // Hover on function for hints.
        udp->setHighThroughputMode(true); // Hover on function for hints.
        udp->receiverConfig("127.0.0.1", 1234); // Hover on function for hints.
        udp->hasReceiver(); // Hover on function for hints.
        /** Base options **/
        udp->setBufferSize(64000); // Always set BufferSize for better & fast communication.
        udp->setDebugMode(true); // If you setDebugMode(true) the traceback & loggers will print.
        udp->socketType(); // Hover on function for hints.
        udp->debugMode(); // Hover on function for hints.
        udp->setBlockingMode(true); // Hover on function for hints.
        udp->bufferSize(); // Hover on function for hints.
        udp->readTimeout(); // Hover on function for hints.
        udp->setReadTimeout(); // Hover on function for hints.
        udp->writeTimeout(); // Hover on function for hints.
        udp->setWriteTimeout(); // Hover on function for hints.
        udp->latestError(); // Hover on function for hints.
        udp->latestState(); // Hover on function for hints.
        udp->localAddress(); // Hover on function for hints.
        udp->localPort(); // Hover on function for hints.
        udp->peerAddress(); // Hover on function for hints.
        udp->peerPort(); // Hover on function for hints.
        udp->socketDescriptor(); // Hover on function for hints.
        udp->isValidIPv4Address("127.0.0.1"); // Hover on function for hints.
        udp->isOpen(); // Hover on function for hints.
        udp->isValid(); // Hover on function for hints.

    }
    // Gui Slot
    void onBindClicked() {
        // Object creation
        if (!udp->isOpen()) {
            // Address validation
            std::string host = "127.0.0.1"; // For example txtHost.text()
            const int port = 1234; // For example txtPort.text()
            if (!udp->isValidIPv4Address(host.c_str())) {
                std::cout << "Invalid host address!" << std::endl; // For example QMessageBox::critical(this, "Error", "errMessage")
                return;
            }

            // Binding
            if (!udp->bind(host.c_str(), port)) {
                return;
            }
        }
        // Closing client session
        else {
            udp->close();
        }
    }

    // GUI Slot
    void onConnectedClicked() {
        /** Connecting on Udp class means set Receiver IP for writeDatagram method **/
        // Safety condition
        if (!udp->isValid()) {
            std::cerr << "Socket isn't define!" << std::endl; // For example QMessageBox::critical(this, "Error", "Socket isn't define");
            return;

        }
        // Receiver Address validation
        std::string host = "127.0.0.1"; // For example txtHost.text()
        const int port = 1234; // For example txtPort.text()
        if (!udp->isValidIPv4Address(host.c_str())) {
            std::cout << "Invalid host address!" << std::endl; // For example QMessageBox::critical(this, "Error", "errMessage")
            return;
        }
        udp->receiverConfig(host.c_str(), port); // Then you can just call writeDatagram without inserting host & port args.
        //QMessageBox::information(this, "Info", "Peer address configured successfully.");
    }

    // GUI Slots
    void onSendClicked() {
        uint8_t buffer[5] = {0x00, 0x01, 0x02, 0x03, 0x4}; // Buffer data Example.
        /** There is two different types on writeDatagram function **/
            // Type A: If you set udp->receiverConfig() earlier & you have single receiver.
        udp->writeDatagram((void *)&buffer);
            // Type B: If you didn't set udp->receiverConfig() before & you have multiple receivers.
        udp->writeDatagram((void *)&buffer, "127.0.0.1", 1234);
    }

    // Slot FROM WeaNet Signal
    void onReadyRead() {
        /** Only use onReadyRead when you connected readyRead signal.
         *  Also always setAutoRead(false) when you want to use readyRead signal.
         */
        std::cout << "Buffer is ready to read!" << std::endl;
        // Your code START FROM HERE

        // Your code END FROM HERE
        udp->receiveDatagram(); // Result will connect to onDataReceivedUdp
        // Your code START FROM HERE

        // Your code END FROM HERE
    }

    // Slot FROM WeaNet Signal
    void onDataReceivedUdp(void *p_buffer, int buf_len, const char *host, int port) {
        uint8_t *raw = static_cast<uint8_t*>(p_buffer); // Passing address to an array.
        // YOUR PARSE CODE START FROM HERE

        // YOUR PARSE CODE END FROM HERE

        // Just example for plaining data...
        std::stringstream ss;
        for (int i; i < buf_len; i++) {
            ss << std::hex << std::setw(2) << std::setfill('0') << (int)raw[i] << ' ';
        }
        std::cout << "Data Received from address: " << host << ':' << port;
        std::cout << "Received data: " << ss.str() << std::endl; // For example plainTxt.appendPlainText(QString::fromStdString(ss.str());
    }

    // Slot FROM WeaNet Signal
    void onBytesWritten(int numSentBytes) {
        std::cout << numSentBytes << std::endl; // You can configure buffer sent with client->bufferSize() to make sure data is already sent or not.
        /** Also you can calculate Throughput using numSentBytes value **/
    }

    // Slot FROM WeaNet Signal
    void onErrorOccured(int err_code, const char *err_message) {
        std::cout << "An error occured: " << err_message << std::endl; // For example plainTxt.appendPlainText(QString::fromStdString(err_message))
        // Example of err_message:
        // "2020-01-01 14:00:00 [Server]: Socket isn't defined!."
    }

    // Slot FROM WeaNet Signal
    void onStateUpdated(int state, const char *state_message) {
        std::cout << "State updated: " << state_message << std::endl; // For example plainTxt.appendPlainText(QString::fromStdString(state_message))
        // Example of state_message:
        // "2020-01-01 14:00:00 [Server]: Socket bound to interface successfully."
    }
};

#endif
