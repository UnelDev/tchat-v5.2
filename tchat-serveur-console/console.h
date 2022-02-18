#ifndef CONSOLE_H
#define CONSOLE_H

#include <QObject>
#include <QSettings>
#include <QIODevice>
#include <QTextStream>
#include <QFile>
#include <QDateTime>
#include <iostream>
#include "serveur/serveur.h"
#include "serveur/utilisateur.h"
#include "cesar.h"
class console: public QObject
{
    Q_OBJECT
public:
    console(int Preferedport);
    ~console();
    void pinUp(const QString message,const QString pseudo = "");
    void log(const QString log);
    void save(QString msg);
    void createPacket(const QString message, const QString arg1 = "", const QString arg2 = "");
private:
    void errorOnServer(QString title, QString msg);
    void exernalCommende(QMap<QString, QVariant> &message);
    void newServeur(QString name);
    void serverLog(const QString logs);
    void newUser(utilisateur*user, const bool living);
    QSettings *settings;
    bool write;
    serveur* serv;

    cesar* encryptioncesar;
    QList<serveur*> servlist;
    QList<QString> servName;
    QMap<serveur*, QList<utilisateur*>> userlist;
};

#endif // CONSOLE_H
