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
#include <QScrollBar>
#include <QCheckBox>
#include "parametre.h"
#include "cesar.h"
#include "client.h"
#include "useraction.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE
class Widget :public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    parametre parametres;

private slots:
    void on_conectbuton_clicked();
    void on_sentbuton_clicked();
    void on_parametrebuton_2_clicked();
    void addmessage(QString message);
    void openfile();
    void on_pieceJointe_clicked();
    void on_pseudo_editingFinished();

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
    void processechatbot(QString command);
    void client_processechatbot(QString command);
    void client_generatemesage();
    //asseseur
    void displayMessagelist(QString message);
    void displayFileOnMessageList(const QString comment, const QString NameOfFile);
    void changestateconnectbutton(bool state);
    void displayconnectlabel(QString text);
    void deletClient(QString nameOfClient);
    void newuser(QString name);
    void executeCmd(const QString cmd);
    void changeUserRole(QList<QString>usrRole);
    //variable
    QString m_path;
    QString encryption;
    client *clients;
    QSettings* settings;
    Ui::Widget *ui;
    bool condenser;
    bool lastMessageIsText;
    QSystemTrayIcon* sticon;
    QLabel *text;
    QLabel *lastText;
    QMenu *stmenu;
    QTcpSocket *socket;
    QList<QMap<QString,QString>> saveMessage;
    QList<QString> listeClient;
    QList<QString> listeOfpPath;
};
#endif // WIDGET_H
