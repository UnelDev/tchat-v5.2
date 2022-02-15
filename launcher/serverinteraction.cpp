#include "serverinteraction.h"

serverInteraction::serverInteraction()
{
    progresse=0;
    name="";
}
void serverInteraction::connectTo(int port){
    QCoreApplication::setApplicationVersion("5.2");
    encryptioncesar = new cesar(2);
    externalServ = new externalServer(&progresse,"192.168.0.1");
    externalServ->show();
    clients = new client();
    clients->connectto("127.0.0.1", 2048, "launcher");
    QObject::connect(clients,&client::isConnected, this, &serverInteraction::connect);
    QObject::connect(clients,&client::isDesconected, this, &serverInteraction::desconnect);
    QObject::connect(clients,&client::externalCommend, this, &serverInteraction::external);

}
serverInteraction::~serverInteraction(){
    if(clients!=nullptr){
        delete clients;
    }

}
void serverInteraction::connect(){
    emit serverInteraction::connected();
    createPacket("launchControl");
    progresse=progresse+1;
    externalServ->changeProgress(progresse);
    externalServ->setState(tr("connecter au serveur verification de la version","luncher"));
}
void serverInteraction::desconnect(){emit serverInteraction::desconnected();}
void serverInteraction::external(QMap<QString, QVariant> message){
    message["message"]=encryptioncesar->deChiffre(message["message"].toString());
    message["arg"]=encryptioncesar->deChiffre(message["arg"].toString());
    message["arg2"]=encryptioncesar->deChiffre(message["arg2"].toString());
    message["pseudo"]=encryptioncesar->deChiffre(message["pseudo"].toString());
    if(message["type"].toString()=="laucher"){
        if(message["message"]=="versionServer"){
            QString version{QCoreApplication::applicationVersion()};
            if(message["arg"].toString()!=version){
                int rep {QMessageBox::question(nullptr,tr("mise a jour dispolible"),tr("une nouvelle version est disponible voulez vous la telecharger ?"))};
                switch (rep) {
                  case QMessageBox::Yes:
                    if(!QDesktopServices::openUrl(QUrl("https://anantasystem.com/downloads"))){
                        QMessageBox::information(nullptr,tr("erreur a louverture du lien","luncher mise a jour"),tr("le lien ne veut pas souvrir le probleme vien de votre navigateur par default taper anantasystem.com dans votre navigateur et faite nous un raport de bug sur le discord","luncher mise a jour"));
                    }
                    break;
                  case QMessageBox::Abort:
                    return;//on arete toutdefault:
                }
            }else{
                progresse=progresse+1;
                externalServ->changeProgress(progresse);
                externalServ->setState(tr("bonne version creation du serveur","luncher"));
                createServeur();
            }
        }else if(message["message"].toString()=="errorName"){
            progresse=progresse-1;
            externalServ->changeProgress(progresse);
            externalServ->setState(tr("erreur de nom réessayer","luncher nom"));
            QMessageBox::information(nullptr,tr("erreur de nom","luncher nom"),tr("le nom doit deja etre utiliser chnager le !"));
            createServeur();
        }else if(message["message"].toString()=="createServer"){
            progresse=progresse+1;
            externalServ->changeProgress(progresse);
            externalServ->setState(tr("initialisation du serveur","luncher"));
            createPacket("init",name
                         );
        }else if(message["message"].toString()=="starting"){
            progresse=progresse+1;
            externalServ->changeProgress(progresse);
            externalServ->setState(tr("initialisation terminée sur le port : ","luncher")+message["arg"].toString());
        }
    }
}

void serverInteraction::createPacket(const QString message, const QString arg1, const QString arg2){

    QMap<QString, QVariant> packet;
    packet["type"]="laucher";
    packet["message"]=encryptioncesar->chiffre(message);
    packet["pseudo"]=encryptioncesar->chiffre("botLauncher");
    packet["arg"]=encryptioncesar->chiffre(arg1);
    packet["arg2"]=encryptioncesar->chiffre(arg2);
    packet["secondofsending"]=QDateTime::currentDateTime().toString("ss");;
    packet["minuteofsending"]=QDateTime::currentDateTime().toString("mm");;
    packet["sendingtime"]=QDateTime::currentDateTime().toString("hh");
    packet["sendingdate"]=QDateTime::currentDateTime().toString("d");
    packet["shippingday"]=QDateTime::currentDateTime().toString("dddd");
    packet["shippingmonth"]=QDateTime::currentDateTime().toString("MMMM");
    packet["shippingyears"]=QDateTime::currentDateTime().toString("yyyy");
    clients->senddatamap(packet);
}
void serverInteraction::createServeur(){
    name = QInputDialog::getText(nullptr,tr("nom du serveur"), tr("quelle est le nom du serveur ? atention cella sera public"));
    createPacket("startNew",name);
    progresse=progresse+1;
    externalServ->changeProgress(progresse);
    externalServ->setState(tr("interogation du serveur sur le nom","dans la creation de serveur"));
}
