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
#include "utilisateur.h"
#include "cesar.h"

class serveur : public QObject
{
    Q_OBJECT
    public:
    serveur();
    int startserveur(int port);
    void recap();
    private:
    void messageBox(QString title, QString msg);
    void displayMessagelist(const QString message, const QString psedo);
    void sentmessagetoall(const QMap<QString, QVariant> &message);
    void sentmessageto(const QMap<QString, QVariant> &message, int NoUtilisateur);
    void sentmessagetoall(const QString type, QString message, QString pseudo);
    void sentmessageto(const QString &message, int NoUtilisateur);
    void sentmessageto(const QString &message,QString pseudo, int NoUtilisateur);
    void sendFileto(const QString path, const QString NameOfFile, const int NoUtilisateur);
    void sentcomandto(const QVariant &message ,int usernaime);
    void sentcomandto(const QVariant &message,QString arg ,int usernaime);
    void sentcommande(const QString commande,const QString arg = "",const QString arg2 = "");
    void newconect();
    void connect(const QMap<QString, QVariant> &connectpack, int usernaime);
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
    int NbOfMessage;
    signals:
    void display(const QString message, const QString psedo);
    void error(QString title, QString msg);
};

#endif // SERVEUR_H
