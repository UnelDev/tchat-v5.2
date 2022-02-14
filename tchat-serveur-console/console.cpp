#include "console.h"
console::console(int Preferedport)
{
    encryptioncesar = new cesar(2);
    QCoreApplication::setOrganizationName("ananta system");
    QCoreApplication::setOrganizationDomain("https://anantasystem.com/");
    QCoreApplication::setApplicationName("tchat");
    QCoreApplication::setApplicationVersion("5.2");
    serv = new serveur();
    settings= new QSettings("settings.ini", QSettings::IniFormat);
    QObject::connect(serv, &serveur::display, this, &console::pinUp);
    QObject::connect(serv, &serveur::error, this, &console::errorOnServer);
    if(settings->value("settings/log").toBool()){
        QObject::connect(serv, &serveur::log, this, &console::log);
    }

    connect(serv, &serveur::noInternal, this, &console::exernalCommende);

    int port =serv->startserveur(Preferedport);
    pinUp("the server has been start of port "+QString::number(port));
    pinUp("initialization down !");
    pinUp("");

}
console::~console(){
    delete serv;
    delete settings;
    delete encryptioncesar;
}
void console::pinUp(const QString message,const QString pseudo){
    if(pseudo==""){
        std::cout << message.toStdString() << std::endl;
    }else{
       std::cout <<"\""<<pseudo.toStdString()<<" \" sent the message : " <<message.toStdString() << std::endl;
    }
}
void console::log(const QString log){
    QString sDate = QDateTime::currentDateTime().toString("hh:mm:ss");
    QString message = "server log at "+sDate+" :   " +log.toUtf8();
    std::cout <<message.toStdString()<<std::endl;
    save(message);

}
void console::save(QString msg){
    if(settings->value("settings/logPaht").toString()!=""){
        const auto fichier = settings->value("settings/logPaht").toString();
        QFile file(fichier);//on crée le fichier
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)){
            return;
        }
        QTextStream out(&file);
        out<<msg.toUtf8()<<Qt::endl;
    }
}
void console::errorOnServer(QString title, QString msg){
    std::cout <<title.toStdString() <<" : " <<msg.toStdString()<<std::endl;
}
void console::exernalCommende(QMap<QString, QVariant> &message){
    cesar chiffremment(2);
    message["message"]=chiffremment.deChiffre(message["message"].toString());
    message["arg"]=chiffremment.deChiffre(message["arg"].toString());
    message["arg2"]=chiffremment.deChiffre(message["arg2"].toString());
    message["pseudo"]=chiffremment.deChiffre(message["pseudo"].toString());
    log("an external order has been received");
    if(message["type"].toString()!="laucher"){
        return;
    }
    if(message["message"].toString()=="launchControl"){
        createPacket("versionServer", QCoreApplication::applicationVersion());
        if(servlist.empty()){
            for(int i=0; i>servlist.size();){
                createPacket("newSerrveur",servName[i]);
            }
        }else{
             createPacket("newSerrveur","noServerLauch");
        }
    }else if(message["message"].toString()=="startNew"){
        if(servName.indexOf(message["arg"].toString())!=-1){//si le nom existe deja
            createPacket("errorName");
            return;
        }
        serveur newServ;
        servlist.append(&newServ);
        const QString name = message["arg"].toString();
        servName.append(name);
        createPacket("createServer");
    }else if(message["message"].toString() == "init"){
        const int index {servName.indexOf(message["arg"].toString())};
        if(index>=0){
            createPacket("starting", QString::number(servlist[index]->startserveur()));
        }
    }
}
void console::createPacket(const QString message, const QString arg1, const QString arg2){
    QMap<QString, QVariant> packet;
    packet["type"]="laucher";
    packet["message"]=encryptioncesar->chiffre(message);
    packet["pseudo"]=encryptioncesar->chiffre("botLauncher");
    packet["arg"]=encryptioncesar->chiffre(arg1);
    packet["arg1"]=encryptioncesar->chiffre(arg2);
    packet["secondofsending"]=QDateTime::currentDateTime().toString("ss");;
    packet["minuteofsending"]=QDateTime::currentDateTime().toString("mm");;
    packet["sendingtime"]=QDateTime::currentDateTime().toString("hh");
    packet["sendingdate"]=QDateTime::currentDateTime().toString("d");
    packet["shippingday"]=QDateTime::currentDateTime().toString("dddd");
    packet["shippingmonth"]=QDateTime::currentDateTime().toString("MMMM");
    packet["shippingyears"]=QDateTime::currentDateTime().toString("yyyy");
    serv->sentmessagetoall(packet);
}
