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
#include <QDir>
#include "cesar.h"
class client : public QObject
{
    Q_OBJECT
public:
    client();
    ~client();
    void sendmessage(QString message);
    void sendcommande(QString commande, QString arg);
    void connectto(QString ip, int port, QString newpsedo);
    void sendcommande(const QString commande);
    void sendFile(const QString message, const QString path, const QString NameOfFile);
    QString getPsedo();
    void editPsedo(QString newpsedo);
protected:
    void senddatamap(const QString type);
    void senddatamap(const QMap<QString, QVariant> sendmap);
    void senddatamap(const QString type, QString message, QString pseudo, QDateTime seconde, QDateTime minute, QDateTime heurs, QDateTime NoJour, QDate jour);
    void senddatamap(const QString type, QString message, QString pseudo);
    void senddatamap(const QString type, QString message);
private:
    //emeteur
    void changestateconnectbutton(bool state);
    void displayMessagelist(QString newMessage);
    void displayconnectlabel(QString newText);
    void newclient(QString newClientName);
    void deleteclient(QString nameOfClient);
    void DisplayFile(const QString comment, const QString NameOfFile);
    //fonction
    void connected();
    void disconnect();
    void socketerror(QAbstractSocket::SocketError error);
    void datareceived();
    void processthemessage(QMap<QString, QVariant> message);
    void processcomand(QMap<QString, QVariant> commend);
    QString generatedate();
    QString generatedate(QMap<QString, QVariant> date);
    QString generatemesage(QString message, QString pseudo);
    QString generatemesage(QMap<QString, QVariant> message);

    QTcpSocket *socket;
    cesar *encryptioncesar;
    QSettings* settings;
    QString psedo;
    int messagesize;
    int nbuser;
signals:
    void newmessage();
    void display(QString message);
    void newFileAndComent(const QString Message, const QString NameOfFile);
    void changestateconnect(bool state);
    void changeTextConnect(QString newtext);
    void newuser(QString newClientName);
    void remouveClient(QString nameOfClient);
};

#endif // CLIENT_H
