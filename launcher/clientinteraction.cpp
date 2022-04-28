#include "clientinteraction.h"
#include "ui_clientinteraction.h"

clientInteraction::clientInteraction(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::clientInteraction)
{
    ui->setupUi(this);
    encryptioncesar = new cesar(2);
    ui->errorLabel->setText("en atenete de la connexion");
}

clientInteraction::~clientInteraction()
{
    delete ui;
    //on verifie l'existance du client
    if(clients!=nullptr){
        delete clients;
    }
}

void clientInteraction::createPacket(const QString message, const QString arg1, const QString arg2){
    QMap<QString, QVariant> packet;
    packet["type"]="laucher";
    packet["message"]=encryptioncesar->chiffre(message);
    packet["pseudo"]=encryptioncesar->chiffre("botLauncher");
    packet["arg"]=encryptioncesar->chiffre(arg1);
    packet["arg2"]=encryptioncesar->chiffre(arg2);
    packet["secondofsending"]=QDateTime::currentDateTime().toString("ss");
    packet["minuteofsending"]=QDateTime::currentDateTime().toString("mm");
    packet["sendingtime"]=QDateTime::currentDateTime().toString("hh");
    packet["sendingdate"]=QDateTime::currentDateTime().toString("d");
    packet["shippingday"]=QDateTime::currentDateTime().toString("dddd");
    packet["shippingmonth"]=QDateTime::currentDateTime().toString("MMMM");
    packet["shippingyears"]=QDateTime::currentDateTime().toString("yyyy");
    clients->senddatamap(packet);
}
void clientInteraction::connect(){
    ui->errorLabel->setText("connectée ! recuperation de la liste des serveur");
    ui->errorLabel->setVisible(false);
    ui->pushButton->setEnabled(false);
    createPacket("getListServer");
}
void clientInteraction::desconnect(){
    ui->errorLabel->setText(tr("erreur de connexion... le serveur est innacesible"));
    ui->serveurList->clear();
    ui->pushButton->setEnabled(false);
}
void clientInteraction::external(QMap<QString, QVariant> message){

    message["message"]=encryptioncesar->deChiffre(message["message"].toString());
//  /!\atention pas de dechifremment des arg  message["arg"]=encryptioncesar->deChiffre(message["arg"].toString());
//  /!\atention pas de dechifremment des arg    message["arg2"]=encryptioncesar->deChiffre(message["arg2"].toString());
    message["pseudo"]=encryptioncesar->deChiffre(message["pseudo"].toString());
    QMap<QString, QVariant> receved = message["arg"].toMap();
    if(message["type"].toString()=="laucher"){
        //on a recu un tableaux de serveur on afiche les clef (les valeur sont les port on les utilisera plus tard
        if(message["message"]=="listServer"){
            qDebug()<<"list of server recevied";
            if(message["arg"].toMap().isEmpty()){
                ui->errorLabel->setText("aucun serveur lancée, vous pouvez en lancée un depuis la precedente etape du launcher");
            }
            ui->pushButton->setEnabled(true);
            listeServer = QMap<QString, int>();


            QMapIterator<QString, QVariant> i(receved);
             i.toBack();
             while (i.hasPrevious()) {
                 i.previous();
                 qDebug() << i.key() << ": " << i.value().toInt();
                 ui->serveurList->addItem(i.key());
             }
        }

    }
}


void clientInteraction::on_pushButton_clicked()
{
    if(listeServer.contains(ui->serveurList->currentItem()->text())){
        //[nom,port]
        emit clientInteraction::serverSelected(m_ip,listeServer[ui->serveurList->currentItem()->text()]);
    }

}
void clientInteraction::connectto(const QString ip,const int port){
    clients = new client();
    m_ip=ip;
    clients->connectto(ip, port, "launcher");
    QObject::connect(clients,&client::isConnected, this, &clientInteraction::connect);
    QObject::connect(clients,&client::isDesconected, this, &clientInteraction::desconnect);
    QObject::connect(clients,&client::externalCommend, this, &clientInteraction::external);
    ui->errorLabel->setVisible(true);
    ui->errorLabel->setText(tr("la connexion a été lancée... passienter"));
    ui->pushButton->setEnabled(false);
}
