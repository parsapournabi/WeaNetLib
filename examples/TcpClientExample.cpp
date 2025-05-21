#ifdef EXAMPLE_MODE
// Importing module
#include <WeaNet/Tcp.h>

// Easy usage
using namespace WeaNet;

// Creating an object from TcpClient class.
TcpClient *client = new TcpClient();

class MainWindow {

    MainWindow () {
        // Signal connection
        /** Make Sure your connecting with  'Qt::DirectConnection' connectionType. **/
        QObject::connect(client, &TcpClient::errorOccured, this, &MainWindow::onErrorOccured, Qt::DirectConnection);
        QObject::connect(client, &TcpClient::stateUpdated, this, &MainWindow::onStateUpdated, Qt::DirectConnection);
        /** Recommendation: Don't use readyRead if you need High reading rate. Just setAutoRead(true). **/
        // QObject::connect(client, &TcpClient::readyRead, this, &MainWindow::onReadyRead, Qt::DirectConnection);
        QObject::connect(client, &TcpClient::dataReceived, this, &MainWindow::onDataReceived, Qt::DirectConnection);
        QObject::connect(client, &TcpClient::bytesWritten, this, &MainWindow::onBytesWritten, Qt::DirectConnection);
        QObject::connect(client, &TcpClient::connected, this, &MainWindow::onConnected, Qt::DirectConnection);
        QObject::connect(client, &TcpClient::disconnected, this, &MainWindow::onDisconnected, Qt::DirectConnection);

        /** TcpClient class options & Properties **/
        client->setAutoRead(true); // setAutoRead(false) if you connected readyRead signal.
        client->isConnected(); // Hover on function for hints.
        client->isHighThroughputMode(); // Hover on function for hints.
        client->setHighThroughputMode(true); // Hover on function for hints.
        /** Base options **/
        client->setBufferSize(1040); // Always set BufferSize for better & fast communication.
        client->setDebugMode(true); // If you setDebugMode(true) the traceback & loggers will print.
        client->socketType(); // Hover on function for hints.
        client->debugMode(); // Hover on function for hints.
        client->setBlockingMode(false); // Hover on function for hints.
        client->bufferSize(); // Hover on function for hints.
        client->readTimeout(); // Hover on function for hints.
        client->setReadTimeout(); // Hover on function for hints.
        client->writeTimeout(); // Hover on function for hints.
        client->setWriteTimeout(); // Hover on function for hints.
        client->latestError(); // Hover on function for hints.
        client->latestState(); // Hover on function for hints.
        client->localAddress(); // Hover on function for hints.
        client->localPort(); // Hover on function for hints.
        client->peerAddress(); // Hover on function for hints.
        client->peerPort(); // Hover on function for hints.
        client->socketDescriptor(); // Hover on function for hints.
        client->isValidIPv4Address("127.0.0.1"); // Hover on function for hints.
        client->isOpen(); // Hover on function for hints.
        client->isValid(); // Hover on function for hints.

    }


    // Gui Slot
    void onConnectClicked() {
        // Object creation
        if (!client->isOpen()) {

            // Address validation
            std::string host = "127.0.0.1"; // For example txtHost.text()
            const int port = 1234; // For example txtPort.text()
            if (!client->isValidIPv4Address(host.c_str())) {
                std::cout << "Invalid server address!" << std::endl; // For example QMessageBox::critical(this, "Error", "errMessage")
                return;
            }

            // Connecting to server
            if (!client->connectToHost(host.c_str(), port)) {
                return;
            }
        }
        // Closing client session
        else {
            client->close();
        }
    }
    // GUI Slots
    void onSendClicked() {
        uint8_t buffer[5] = {0x00, 0x01, 0x02, 0x03, 0x4}; // Buffer data Example.
        if (client->isConnected()) // Safety condition
            client->write((void *)&buffer); // Writing from client to server

    }

    // Slot FROM WeaNet Signal
    void onReadyRead() {
        /** Only use onReadyRead when you connected readyRead signal.
         *  Also always setAutoRead(false) when you want to use readyRead signal.
         */
        std::cout << "Buffer is ready to read!" << std::endl;
        // Your code START FROM HERE

        // Your code END FROM HERE
        client->read(); // Result will connect to onDataReceived
        // Your code START FROM HERE

        // Your code END FROM HERE
    }

    // Slot FROM WeaNet Signal
    void onDataReceived(void *p_buffer, int buf_len) {

        uint8_t *raw = static_cast<uint8_t*>(p_buffer); // Passing address to an array.
        // YOUR PARSE CODE START FROM HERE

        // YOUR PARSE CODE END FROM HERE

        // Just example for plaining data...
        std::stringstream ss;
        for (int i; i < buf_len; i++) {
            ss << std::hex << std::setw(2) << std::setfill('0') << (int)raw[i] << ' ';
        }
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
        // "2020-01-01 14:00:00 [Client]: Socket isn't connect!."
    }

    // Slot FROM WeaNet Signal
    void onStateUpdated(int state, const char *state_message) {
        std::cout << "State updated: " << state_message << std::endl; // For example plainTxt.appendPlainText(QString::fromStdString(state_message))
        // Example of state_message:
        // "2020-01-01 14:00:00 [Client]: Connection esablished successfully."
    }

    // Slot FROM WeaNet Signal
    void onConnected() {
        // YOUR CODE START FROM HERE
            // You can write Gui updating on this slot

        // YOUR CODE END HERE
    }

    // Slot FROM WeaNet Signal
    void onDisconnected() {
        // YOUR CODE START FROM HERE
            // You can write Gui updating on this slot

        // YOUR CODE END HERE
    }
};

#endif
