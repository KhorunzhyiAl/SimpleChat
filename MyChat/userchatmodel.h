#ifndef CHATMODEL_H
#define CHATMODEL_H

#include <QAbstractListModel>
#include <QLinkedList>
#include <QDebug>

#include "message.h"

class UserChatModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum MessageRoles
    {
        isMyRole = Qt::UserRole + 1,
        nameRole,
        textRole
    };

    explicit UserChatModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

//    // Add data:
//    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    // Remove data:
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    QHash<int, QByteArray> roleNames() const override;

    void addMessage(Message &message);
    void addMessage(Message &&message);

private:
    QList<Message> messages;

};

#endif // CHATMODEL_H
