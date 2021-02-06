#ifndef MYSERVER_H
#define MYSERVER_H

#include <iostream>

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDataStream>
#include <QHash>

class MyServer : public QObject
{
    Q_OBJECT

public:
    MyServer();

private slots:
    void acceptConnection();
    void onClientDisconnected(int socketID);
    void readFromSocket(QTcpSocket * socket);

private:
    QTcpServer server;
    QHash<int, QTcpSocket*> connections;

    int lastSocketID = -1;
};

#endif // MYSERVER_H
