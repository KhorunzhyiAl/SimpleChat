#include "myserver.h"

MyServer::MyServer()
    : server(this)
{
    connect(&server, &QTcpServer::newConnection, this, &MyServer::acceptConnection);


    if (!server.listen(QHostAddress::LocalHost, 5050)) {
        std::cout << "listen() failed" << std::endl;
        std::cout << server.errorString().toStdString() << std::endl;
        return;
    }

    std::cout << "server port: " << server.serverPort() << std::endl;
    std::cout << "server address: " << server.serverAddress().toString().toStdString() << std::endl;

    std::cout << "waiting for a connection..." << std::endl;
}

void MyServer::acceptConnection()
{
    QTcpSocket * socket = server.nextPendingConnection();

    if (!socket->isValid()) {
        std::cout << server.errorString().toStdString() << std::endl;
        return;
    }

    int newSocketID = ++lastSocketID;
    connections.insert(newSocketID, socket);

    connect(socket, &QTcpSocket::disconnected, socket, &QObject::deleteLater);
    connect(socket, &QTcpSocket::disconnected,
            this, [this, newSocketID](){ this->onClientDisconnected(newSocketID); });
    connect(socket, &QTcpSocket::readyRead,
            this, [this, socket](){ this->readFromSocket(socket); });

    std::cout << "connection received. number of connections: " << connections.size()
              << "\tconnection id: " << newSocketID << std::endl;
}

void MyServer::onClientDisconnected(int socketID)
{
    connections.remove(socketID);
    std::cout << "disconnected. number of connections: " << connections.size() << std::endl;
}

void MyServer::readFromSocket(QTcpSocket *socket)
{
    std::cout << "reading a message..." << std::endl;

    QByteArray byte = socket->readAll();

    // Send the message to everyone else
    for (QTcpSocket * client : connections) {
        if (client != socket) {
            client->write(byte);
        }
    }
}
