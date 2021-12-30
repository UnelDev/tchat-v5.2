/*By Unel at 30/12/21
For Ananta Project*/
#ifndef CLIENT_H
#define CLIENT_H
#include <QObject>
#include <QString>
#include <QAbstractSocket>
#include <QTcpSocket>
#include <QCoreApplication>
#include <QDateTime>
#include <QMessageBox>
#include <QSettings>
#include "cesar.h"
class client : public QObject
{
    Q_OBJECT
public:
    client();
    void sendmessage(QString message);
    void sentcommande(QString commande, QString arg);
    void connectto(QString ip, int port, QString newpsedo);
    void sentcommande(const QString commande);
protected:
    void sentdatamap(const QString type);
    void sentdatamap(const QMap<QString,QString> sendmap);
    void sentdatamap(const QString type, QString message, QString pseudo, QDateTime seconde, QDateTime minute, QDateTime heurs, QDateTime NoJour, QDate jour);
    void sentdatamap(const QString type, QString message, QString pseudo);
    void sentdatamap(const QString type, QString message);
    //void sentcommande(const QString commande, QString arg);
private:
    //emeteur
    void changestateconnectbutton(bool state);
    void displayMessagelist(QString newMessage);
    void displayconnectlabel(QString newText);
    void newclient(QString newClientName);
    void deleteclient(QString nameOfClient);
    //fonction
    void connected();
    void disconnect();
    void socketerror(QAbstractSocket::SocketError error);
    void datareceived();
    void processthemessage(QMap<QString,QString> message);
    void processcomand(QMap<QString, QString> commend);
    QString generatedate();
    QString generatedate(QMap<QString, QString> date);
    QString generatemesage(QString message, QString pseudo);
    QString generatemesage(QMap<QString, QString> message);

    QTcpSocket *socket;
    cesar *encryptioncesar;
    QSettings* settings;
    QString psedo;

    quint16 messagesize;
    int nbuser;
signals:
    void newmessage();
    void display(QString message);
    void changestateconnect(bool state);
    void changeTextConnect(QString newtext);
    void newuser(QString newClientName);
    void remouveClient(QString nameOfClient);
};

#endif // CLIENT_H
