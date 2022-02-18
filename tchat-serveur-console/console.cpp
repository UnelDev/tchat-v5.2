#include "console.h"
console::console(int Preferedport)
{
    encryptioncesar = new cesar(2);
    QCoreApplication::setOrganizationName("ananta system");
    QCoreApplication::setOrganizationDomain("https://anantasystem.com/");
    QCoreApplication::setApplicationName("tchat");
    QCoreApplication::setApplicationVersion("5.2");
    settings= new QSettings("settings.ini", QSettings::IniFormat);


    serv = new serveur();
    servlist.append(serv);
    servName.append("general");
    QObject::connect(serv, &serveur::display, this, &console::pinUp);
    QObject::connect(serv, &serveur::log, this, &console::serverLog);
    QObject::connect(serv, &serveur::error, this, &console::errorOnServer);
    QObject::connect(serv, &serveur::ActionOnUser, this, &console::newUser);
    QObject::connect(serv, &serveur::noInternal, this, &console::exernalCommende);
    servlist.append(serv);

    int port =serv->startserveur(Preferedport);
    pinUp("the server has been start of port "+QString::number(port));
    pinUp("initialization down !");
    pinUp("");
}
console::~console(){
    delete serv;
    delete settings;
    delete encryptioncesar;
    for (int i=0; i<servlist.size();i++ ) {
        servlist[i]->deleteLater();
    }
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
        newServeur(message["arg"].toString());
    }else if(message["message"].toString() == "init"){
        const int index {servName.indexOf(message["arg"].toString())};
        if(index>=0){
            const int portOfServeur = servlist[index]->startserveur();
            createPacket("starting", QString::number(portOfServeur));
            log("the server : "+message["arg"].toString()+" has been initialized on port "+QString::number(portOfServeur));
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
void console::serverLog(const QString logs){
    serveur* servSend = qobject_cast<serveur*>(sender());//on retrouve le serveur qui a emis
    const QString name  = servName[servlist.indexOf(servSend)];
    log("the serveur "+name+" sent :"+logs);

}
void console::newServeur(QString name){
    if(name.remove(" ")==""){//si le nom est vide
        createPacket("errorName");
        return;
    }else if(servName.indexOf(name)!=-1){//si le nom existe deja
        createPacket("errorName");
        return;
    }//verification terminée
    serveur* newServ;
    newServ = new serveur();
    QObject::connect(newServ, &serveur::log, this, &console::serverLog);
    QObject::connect(newServ, &serveur::error, this, &console::errorOnServer);
    QObject::connect(newServ, &serveur::ActionOnUser, this, &console::newUser);
    servlist.append(newServ);
    servName.append(name);
    createPacket("createServer");
    log("a new server has been created : "+ name);
}
void console::newUser(utilisateur *user, const bool living){
    serveur* servSend = qobject_cast<serveur*>(sender());//on retrouve le serveur qui a emis
    if(living){//si l'utilisateur est encore actif
        userlist[servSend].append(user);//on l'ajoute a la liste des utilisateur au serveur servsend
    }else{// si il vien d'etre suprimée
        userlist[servSend].removeOne(user); //on le suprime de la liste des utilisateur au serveur servsend
        if(userlist[servSend].empty()){//si il n'y a plus personne
            const QString name = servName[servlist.indexOf(servSend)];
            log("-->the serveur "+name+"has been deleted because no client is connected");
            servSend->deleteLater();
        }
    }

}
