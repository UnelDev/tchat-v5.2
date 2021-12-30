#ifndef WIDGET_H
#define WIDGET_H

#include <QSystemTrayIcon>
#include <QTcpSocket>
#include <QWidget>
#include <QSettings>
#include <QMenu>
#include <QTextDocumentFragment>
#include <QNetworkInterface>
#include <QSound>
#include "serveur.h"
#include "client.h"

#include <QAbstractSocket>
#include <QTcpSocket>
#include <QDateTime>
#include "parametre.h"
#include "cesar.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    parametre parametres;
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
private:
    QList<QMap<QString,QString>> saveMessage;
    client *clients;
    cesar *encryptioncesar;
    QString levelOfSecure;
    QSettings* settings;
    Ui::Widget *ui;
    bool condenser;
    QSystemTrayIcon* sticon;
    QLabel *text;
    QMenu *stmenu;
    QTcpSocket *socket;
    serveur *server;
    quint16 messagesize;
    QList<QWidget*>test;
private slots:
    QString returnpseudo();
    QString generatemesage(QString message, QString pseudo);
    QString generatedate();
    void addmessage(QString message);
    void startTrayIcon();
    void changetransparency(Qt::ApplicationState state);
    void condesed();
    void autoconnect();
    void processechatbot(QString command);
    void on_pseudo_editingFinished();
    void connectClient();
    //asseseur
    void displayMessagelist(QString message);
    void deletClient(QString nameOfClient);
    void newuser(QString name);
    //les auto generer
    void on_sentbutton_clicked();
    void on_parametrebutton_clicked();
};
#endif // WIDGET_H
