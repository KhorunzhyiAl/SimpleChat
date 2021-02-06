#include "user.h"

User::User()
{
    m_username = "user" + QString::number(qrand() % 1000);
    connect(&mySocket, &QTcpSocket::readyRead, this, &User::onReadyRead);

    // change the host address to what the one server app prints
    mySocket.connectToHost("127.0.0.1", 5050);
}

void User::setUsername(QString &userame)
{
    this->m_username = userame;
}

QString &User::username()
{
    return this->m_username;
}

void User::sendMessage(QString message)
{
    chatModel.addMessage(Message(true, m_username, message));

    QDataStream out(&mySocket);
    out << QStringList { m_username, message };
}

void User::onReadyRead()
{
    // must be: ["name", "message text"]
    QByteArray byte = mySocket.readAll();
    QStringList receivedMessage;

    QDataStream in(byte);
    in >> receivedMessage;
    if (receivedMessage.size() != 2) {
        qDebug() << "error receiving message";
        return;
    }

    qDebug() << "message received successfully.";
    chatModel.addMessage(Message(false, receivedMessage[0], receivedMessage[1]));
}


