#ifndef WIDGET_H
#define WIDGET_H

#include <QSystemTrayIcon>
#include <QTcpSocket>
#include <QWidget>
#include <QSettings>
#include <QMenu>
#include <QTextDocumentFragment>
#include <QNetworkInterface>
#include <QScrollBar>
#include <QDateTime>
#include "parametre.h"
#include "serveur.h"
#include "client.h"
#include <QCoreApplication>
#include <qtconcurrentrun.h>
#include <QThread>

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
    QList<QString> listeClient;
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
    QString m_path;
    QList<QString> listeOfpPath;


    QFuture<void> multiprocess;
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
    void openfile();
    //asseseur
    void displayMessagelist(QString message);
    void displayFileOnMessageList(const QString comment, const QString NameOfFile);
    void deletClient(QString nameOfClient);
    void newuser(QString name);
    void recap();
    void executeCmd(const QString cmd);
    //les auto generer
    void on_sentbutton_clicked();
    void on_parametrebutton_clicked();
    void on_pieceJointe_clicked();

};
#endif // WIDGET_H
