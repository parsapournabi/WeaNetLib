// Importing module
#include <WeaNet/Tcp.h>

// Easy usage
using namespace WeaNet;

// Creating an object from TcpClient class.
TcpServer *server = new TcpServer();

class MainWindow : public QObject{
    Q_OBJECT
public:
    MainWindow() {

        // Signal connection
        /** Make Sure your connecting with  'Qt::DirectConnection' connectionType. **/
        QObject::connect(server, &TcpServer::errorOccured, this, &MainWindow::onErrorOccured, Qt::DirectConnection);
        QObject::connect(server, &TcpServer::stateUpdated, this, &MainWindow::onStateUpdated, Qt::DirectConnection);
        QObject::connect(server, &TcpServer::newConnection, this, &MainWindow::onNewConnection, Qt::DirectConnection);
        /** NOTE: Other signals like dataReceived, readyRead, bytesWritten and ... must be connect from acceptedClient. **/


        // Setting some options
        /** TcpClient class options & Properties **/
        server->isListening(); // Hover on function for hints.
        server->setMaxPendingConnections(20); // Hover on function for hints.
        server->maxPendingConnections(); // Hover on function for hints.
        server->pauseAccepting(); // Hover on function for hints.
        server->resumeAccepting(); // Hover on function for hints.
        server->hasPendingConnection(); // Hover on function for hints.
        server->nexPendingConnection(); // Hover on function for hints.
        /** Base options **/
        server->setBufferSize(1040); // Always set BufferSize for better & fast communication.
        server->setDebugMode(true); // If you setDebugMode(true) the traceback & loggers will print.
        server->socketType(); // Hover on function for hints.
        server->debugMode(); // Hover on function for hints.
        server->setBlockingMode(true); // Hover on function for hints.
        server->bufferSize(); // Hover on function for hints.
        server->readTimeout(); // Hover on function for hints.
        server->setReadTimeout(); // Hover on function for hints.
        server->writeTimeout(); // Hover on function for hints.
        server->setWriteTimeout(); // Hover on function for hints.
        server->latestError(); // Hover on function for hints.
        server->latestState(); // Hover on function for hints.
        server->localAddress(); // Hover on function for hints.
        server->localPort(); // Hover on function for hints.
        server->peerAddress(); // Hover on function for hints.
        server->peerPort(); // Hover on function for hints.
        server->socketDescriptor(); // Hover on function for hints.
        server->isValidIPv4Address("127.0.0.1"); // Hover on function for hints.
        server->isOpen(); // Hover on function for hints.
        server->isValid(); // Hover on function for hints.

    }

    // Gui Slot
    void onBindClicked() {
        // Object creation
        if (!server->isOpen()) {

            // Address validation
            std::string host = "127.0.0.1"; // For example txtHost.text()
            const int port = 1234; // For example txtPort.text()
            if (!server->isValidIPv4Address(host.c_str())) {
                std::cout << "Invalid host address!" << std::endl; // For example QMessageBox::critical(this, "Error", "errMessage")
                return;
            }

            // Listening
            if (!server->listen(host.c_str(), port)) {
                return;
            }
        }
        // Closing client session
        else {
            server->close();
        }
    }
    void onNewConnection() {
        // Safety condition
        if (!server->hasPendingConnection())
            return;
        // Object creation
        TcpClient* client = server->nexPendingConnection();
        // Saving client on cache
        m_acceptedClients.push_back(client);
        // Optional customizing (referer TcpClientExample.cpp)
        client->setAutoRead(true);
        client->setBufferSize(1040);
        // Signals
    //    QObject::connect(client, &TcpClient::readyRead, this, [client] () { client->read(); });
        QObject::connect(client, &TcpClient::errorOccured, this, &MainWindow::onErrorOccured, Qt::DirectConnection);
        QObject::connect(client, &TcpClient::stateUpdated, this, &MainWindow::onStateUpdated, Qt::DirectConnection);
        QObject::connect(client, &TcpClient::dataReceived, this, &MainWindow::onDataReceived, Qt::DirectConnection);
        QObject::connect(client, &TcpClient::bytesWritten, this, &MainWindow::onBytesWritten, Qt::DirectConnection);
        /** If you want to have flexible throughput customization, Connect your signal to
            client->setHighThroughputMode() slot.
            NOTE: Remember to disconnect signal by client closing state.**/
//		QMetaObject::Connection conn = connect(/**ui->cbHighThroughput**/, /**&QCheckBox::clicked**/, this, [this, client] () {
//            client->setHighThroughputMode(ui->cbHighThroughput->isChecked());});
        QObject::connect(client, &TcpClient::disconnected, this, [=] () {
            client->close();
            /** Referer conn QMetaObject::Connection object **/
//			disconnect(conn);
            m_acceptedClients.erase(std::remove(m_acceptedClients.begin(), m_acceptedClients.end(), client), m_acceptedClients.end());});
    }

    // GUI Slots
    void onSendClicked() {
        uint8_t buffer[5] = {0x00, 0x01, 0x02, 0x03, 0x4}; // Buffer data Example.
        // For example sending data to all of the connected clients
        for (auto &cli : m_acceptedClients) {
            cli->write((void *)&buffer);
        }
    }

    // Slot FROM WeaNet Signal
    void onReadyRead() {
        /** Only use onReadyRead when you connected readyRead signal.
         *  Also always setAutoRead(false) when you want to use readyRead signal.
         */
        std::cout << "Buffer is ready to read!" << std::endl;
        // Your code START FROM HERE

        // Your code END FROM HERE

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
        // "2020-01-01 14:00:00 [Server]: Socket isn't defined!."
    }

    // Slot FROM WeaNet Signal
    void onStateUpdated(int state, const char *state_message) {
        std::cout << "State updated: " << state_message << std::endl; // For example plainTxt.appendPlainText(QString::fromStdString(state_message))
        // Example of state_message:
        // "2020-01-01 14:00:00 [Server]: Socket bound to interface successfully."
    }
private:
    std::vector<TcpClient*> m_acceptedClients; // Need this vector on your code for client handling.
};

