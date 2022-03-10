#ifndef CONSOLE_H
#define CONSOLE_H

#include <QObject>
#include <QSettings>
#include <QIODevice>
#include <QTextStream>
#include <QFile>
#include <QDateTime>
#include <iostream>
#include <QDir>
#include <QProcess>

//#include <QDesktopServices>
#include <QUrl>
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
    void createPacket(const int index, const QString message, const QString arg1 = "", const QString arg2 = "");
private:
    void errorOnServer(QString title, QString msg);
    void exernalCommende(QMap<QString, QVariant> &message,const int user);
    void serverLog(const QString logs);
    bool copyFile(const QString name);
    int createFile(const QString name, const int index);
    QSettings *settings;
    bool write;
    serveur* serv;

    cesar* encryptioncesar;
    QList<QString> servName;
};

#endif // CONSOLE_H
