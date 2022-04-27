#include "clientinteraction.h"
#include "ui_clientinteraction.h"

clientInteraction::clientInteraction(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::clientInteraction)
{
    ui->setupUi(this);
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
qDebug()<<"create in progress";
    QMap<QString, QVariant> packet;
    qDebug()<<"create -1";
    packet["type"]="laucher";
    qDebug()<<"create 0";
    packet["message"]=encryptioncesar->chiffre(message);
    qDebug()<<"create 1";
    packet["pseudo"]=encryptioncesar->chiffre("botLauncher");
    packet["arg"]=encryptioncesar->chiffre(arg1);
    packet["arg2"]=encryptioncesar->chiffre(arg2);
    qDebug()<<"create 2";
    packet["secondofsending"]=QDateTime::currentDateTime().toString("ss");
    packet["minuteofsending"]=QDateTime::currentDateTime().toString("mm");
    packet["sendingtime"]=QDateTime::currentDateTime().toString("hh");
    packet["sendingdate"]=QDateTime::currentDateTime().toString("d");
    packet["shippingday"]=QDateTime::currentDateTime().toString("dddd");
    packet["shippingmonth"]=QDateTime::currentDateTime().toString("MMMM");
    packet["shippingyears"]=QDateTime::currentDateTime().toString("yyyy");
    qDebug()<<"create 3";
    clients->senddatamap(packet);
    qDebug()<<"create down";
}
void clientInteraction::connect(){
    ui->errorLabel->setText("");
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
    qDebug()<<"external recevied";
    message["message"]=encryptioncesar->deChiffre(message["message"].toString());
    message["arg"]=encryptioncesar->deChiffre(message["arg"].toString());
    message["arg2"]=encryptioncesar->deChiffre(message["arg2"].toString());
    message["pseudo"]=encryptioncesar->deChiffre(message["pseudo"].toString());
    if(message["type"].toString()=="laucher"){
        //on a recu un tableaux de serveur on afiche les clef (les valeur sont les port on les utilisera plus tard
        if(message["message"]=="listServer"){
            if(!message["arg"].toMap().isEmpty()){
                ui->errorLabel->setText("aucun serveur lancée, vous pouvez en lancée un depuis la precedente etape du launcher");
            }
            ui->pushButton->setEnabled(true);
            listeServer = QMap<QString, int>();
           for(int i=0;i<message["arg"].toMap().size();i++){
               ui->serveurList->addItem(message["arg"].toMap().key(i));
               listeServer[message["arg"].toMap().key(i)] = message[message["arg"].toMap().key(i)].toInt();
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
    qDebug()<<"connect lauch";
    clients = new client();
    m_ip=ip;
    clients->connectto(ip, port, "launcher");
    QObject::connect(clients,&client::isConnected, this, &clientInteraction::connect);
    QObject::connect(clients,&client::isDesconected, this, &clientInteraction::desconnect);
    QObject::connect(clients,&client::externalCommend, this, &clientInteraction::external);
    ui->errorLabel->setVisible(true);
    ui->errorLabel->setText(tr("la connexion a été lancée... passienter"));
    ui->pushButton->setEnabled(false);
    qDebug()<<"connect lauch2";
}
