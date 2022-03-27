#ifndef SERVEUR_H
#define SERVEUR_H

#include <QObject>
#include <QTcpSocket>
#include <QDateTime>
#include <QDataStream>
#include <QTcpServer>
#include <QFile>
#include <QCoreApplication>
#include <QSettings>
#include <QDir>
#include <QNetworkInterface>
#include <future>
#include <math.h>
#include "utilisateur.h"
#include "cesar.h"

class serveur : public QObject
{
    Q_OBJECT
    public:
    serveur();
    int startserveur(const int port = 2048, const QString fileOfSave = "chat.dat");
    void recap();
    void sentcommande(const QString commande,const QString arg = "",const QString arg2 = "");
    void sentmessagetoall(const QString type, QString message, QString pseudo);
    void sentmessagetoall(const QMap<QString, QVariant> &message);
    void sentmessageto(const QMap<QString, QVariant> &message, int NoUtilisateur);
    private:
    void emitlog(const QString log);
    void messageBox(QString title, QString msg);
    void displayMessagelist(const QString message, const QString psedo);
    void sentmessageto(const QString &message,const int NoUtilisateur,QString pseudo="");
    void sentMessageToRole(const QString message,const  int role, QString psedoOfSent = tr("Serveur Tchat Bot"));
    void sendFileto(const QString path, const QString NameOfFile, const int NoUtilisateur);
    void sentcomandto(int usernaime,const QVariant &message,const QString arg="",const QString arg2="",const QString arg3="");

    void newconect();
    void outOfWating(int usernaime, const QString newpsedo);
    void connect(QMap<QString, QVariant> &connectpack, int usernaime);
    void datareceived();
    void disconnectclients();
    void writetofile(QMap<QString, QVariant> FluxFile);
    void recoverallfile();
    void processcomand(QMap<QString, QVariant> command, int noclient);
    int findIndex(QTcpSocket* socket);

    QList<utilisateur*> clientsList;
    cesar *encryptioncesar;
    QString psedo;
    QTcpServer* m_serveur;
    QList<QMap<QString,QVariant>> saveMessage;
    QSettings* settings;
    QString m_FileOfSave;
    int NbOfMessage;
    signals:
    void display(const QString message, const QString psedo);
    void error(QString title, QString msg);
    void log(const QString log);
    void noInternal(QMap<QString, QVariant> &message, const int user);
    void ActionOnUser(utilisateur*user, const bool living);
};

#endif // SERVEUR_H
