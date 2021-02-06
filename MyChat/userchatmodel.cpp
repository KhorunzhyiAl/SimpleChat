#include "userchatmodel.h"

UserChatModel::UserChatModel(QObject *parent)
    : QAbstractListModel(parent)
{
    addMessage(Message(false, "Help", "Write a message in the box below and press \"send\""));
}

int UserChatModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    // FIXME: Implement me!
    return messages.size();
}

QVariant UserChatModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    if (role == MessageRoles::isMyRole) {
        return messages[index.row()].getIsMy();
    }
    if (role == MessageRoles::nameRole) {
        return messages[index.row()].getName();
    }
    if (role == MessageRoles::textRole) {
        return messages[index.row()].getText();
    }

    return QVariant();
}

bool UserChatModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (row + count > messages.size() || row < 0) {
        return false;
    }

    beginRemoveRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    auto a = messages.begin();
    a += row;
    messages.erase(a, a + count);

    endRemoveRows();

    return true;
}

QHash<int, QByteArray> UserChatModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[MessageRoles::isMyRole] = "isMyRole";
    roles[MessageRoles::nameRole] = "nameRole";
    roles[MessageRoles::textRole] = "textRole";
    return roles;
}

void UserChatModel::addMessage(Message &message)
{
    beginInsertRows(QModelIndex(), messages.size(), messages.size() + 1);
    messages.push_back(message);
    endInsertRows();
}

void UserChatModel::addMessage(Message &&message)
{
    beginInsertRows(QModelIndex(), 0, 0);
    messages.push_front(message);
    endInsertRows();
}
