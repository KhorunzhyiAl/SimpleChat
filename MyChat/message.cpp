#include "message.h"

Message::Message()
    : from(""),
      text("")
{
    this->isMy = false;
}

Message::Message(const Message &other)
    : from(other.getName()),
      text(other.getText())
{
    this->isMy = other.isMy;
}

Message::Message(bool my, QString &from, QString &text)
    : from(from),
      text(text)
{
    this->isMy = my;
}

Message::Message(bool my, QString &&from, QString &&text)
    : from(from),
      text(text)
{
    this->isMy = my;
}

bool Message::getIsMy() const
{
    return this->isMy;
}

const QString &Message::getName() const
{
    return this->from;
}

const QString &Message::getText() const
{
    return this->text;
}
