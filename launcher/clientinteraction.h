#ifndef CLIENTINTERACTION_H
#define CLIENTINTERACTION_H

#include <QDialog>
#include <QListWidgetItem>
#include "client.h"

namespace Ui {
class clientInteraction;
}

class clientInteraction : public QDialog
{
    Q_OBJECT

public:
    clientInteraction(QWidget *parent = nullptr)/*(const QString ip, const int port, QWidget *parent = nullptr)*/;
    ~clientInteraction();

    //gestion du client
    void connectto(const QString ip,const int port);
    void connect();
    void desconnect();
    void external(QMap<QString, QVariant> message);
    void createPacket(const QString message, const QString arg1="", const QString arg2="");
private slots:
    void on_pushButton_clicked();

    void on_serveurList_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::clientInteraction *ui;
    client* clients;
    cesar* encryptioncesar;
    QMap<QString, int> listeServer;
    QString m_ip;

signals:
    void serverSelected(const QString ip, const int port);
};

#endif // CLIENTINTERACTION_H
