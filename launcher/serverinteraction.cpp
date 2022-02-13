#include "serverinteraction.h"

serverInteraction::serverInteraction()
{
    progresse=0;
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
    delete clients;
}
void serverInteraction::connect(){
    emit serverInteraction::connected();
    createPacket("launchControl");
    progresse=progresse+1;
    externalServ->changeProgress(progresse);
}
void serverInteraction::desconnect(){emit serverInteraction::desconnected();}
void serverInteraction::external(QMap<QString, QVariant> message){
    message["message"]=encryptioncesar->deChiffre(message["message"].toString());
    message["arg"]=encryptioncesar->deChiffre(message["arg"].toString());
    message["arg2"]=encryptioncesar->deChiffre(message["arg2"].toString());
    message["pseudo"]=encryptioncesar->deChiffre(message["pseudo"].toString());
    if(message["type"]=="laucher"){
        if(message["message"]=="versionServer"){
            if(message["versionServer"].toString()!=QCoreApplication::applicationVersion()){
                int rep {QMessageBox::question(nullptr,tr("mise a jour dispolible"),tr("une nouvelle version est disponible voulez vous la telecharger ?"))};
                switch (rep) {
                  case QMessageBox::Ok:
                    if(!QDesktopServices::openUrl(QUrl("https://anantasystem.com/"))){
                        QMessageBox::information(nullptr,tr("erreur a louverture du lien","guit hub pour les theme"),tr("le lien ne veut pas souvrir le probleme vien de votre navigateur par default taper anantasystem.com dans votre navigateur et faite nous un raport de bug sur le discord","guit hub pour les theme"));
                    }
                    break;
                  case QMessageBox::Abort:
                    return;//on arete toutdefault:
                }
            }else{
                progresse=progresse+1;
                externalServ->changeProgress(progresse);
            }
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
