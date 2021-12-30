/* ce projet est en test il a été consu comme si il y avait deux classe
 je voulais faire de la foward declaration mais je ne savais pas faire... donc en atendant...
ANANTA SYSTEME  tchat 4.0.-1
*/

#ifndef WIDGET_H
#define WIDGET_H
#include <QMediaPlayer>
#include <QWidget>
#include <QTcpSocket>
#include <QDateTime>
#include <QMessageBox>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QTextDocumentFragment>
#include <QFileDialog>
#include <QSettings>
#include <QStyleFactory>
#include <QNetworkInterface>
#include "parametre.h"
#include "cesar.h"
#include "client.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE
class Widget :public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    QList<QMap<QString,QString>> saveMessage;
    parametre parametres;
private slots:
    void on_conectbuton_clicked();

    void on_sentbuton_clicked();

private:
    QString returnpseudo();
    QString generatemesage(QString message, QString pseudo);
    QString generatemesage(QMap<QString, QString> message);
    QString generatedate();
    void client_sentdatamap(const QString type);
    void startTrayIcon();
    void changetransparency(Qt::ApplicationState state);
    void condesed();
    void helpcondesed();
    void autoconnect();
    void on_parametrebutton_clicked();
    void processechatbot(QString command);
    void on_parametrebuton_2_clicked();
    void on_pseudo_editingFinished();
    void client_processechatbot(QString command);
    void client_generatemesage();
    //asseseur
    void displayMessagelist(QString message);
    void changestateconnectbutton(bool state);
    void displayconnectlabel(QString text);
    void deletClient(QString nameOfClient);
    void newuser(QString name);

    QString encryption;
    client *clients;
    QSettings* settings;
    Ui::Widget *ui;
    bool condenser;
    QSystemTrayIcon* sticon;
    QLabel *text;
    QMenu *stmenu;
    QTcpSocket *socket;
};
#endif // WIDGET_H
