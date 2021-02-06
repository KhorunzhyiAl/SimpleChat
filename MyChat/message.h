#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>

class Message
{
public:
    Message();
    Message(const Message & other);
    Message(bool my, QString  &from, QString  &text);
    Message(bool my, QString &&from, QString &&text);

    bool getIsMy() const;
    const QString & getName() const;
    const QString & getText() const;

private:
    bool isMy;
    QString from;
    QString text;
};

#endif // MESSAGE_H
