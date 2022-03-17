#ifndef CHATBOT_H
#define CHATBOT_H

#include <QObject>
#include <QDateTime>
#include <future>
#include <QVariant>
#include "useraction.h"
#include "changeuserroom.h"

class chatBot : public QObject
{
    Q_OBJECT
public:
    chatBot();
    void proccess(const QString command, const QString psedo);
private:
    QString generatemesage(QString message, QString pseudo);
    QString generatedate();
    void emitMessage(const QString message);
    void emitCommende(const QString commende);
    void finishChangeUserRoom(const QString username, const QString room);
    void finishUseraction(QString name, int grade);
    void startUserAction(const QList<QString> userlist);
    void startChangeUserRoom(const QList<QString> userlist);

signals:
    void sendInternalCommend(const QString commende,QVariant arg1 = "", QVariant arg2="");
};

#endif // CHATBOT_H
