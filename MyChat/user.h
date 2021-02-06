#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QDataStream>

#include "message.h"
#include "userchatmodel.h"

class User : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString username READ username WRITE setUsername NOTIFY usernameChanged)
public:
    // general
    QString m_username;
    UserChatModel chatModel;

    User();

    void setUsername(QString & userame);
    QString & username();

public slots:
    Q_INVOKABLE void sendMessage(QString message);
    void onReadyRead();

signals:
    void usernameChanged();

private:
    // networking
    QTcpSocket mySocket;
};

#endif // CLIENT_H
