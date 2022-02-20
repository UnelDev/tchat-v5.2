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
    servName.append("general");
    QObject::connect(serv, &serveur::display, this, &console::pinUp);
    QObject::connect(serv, &serveur::log, this, &console::serverLog);
    QObject::connect(serv, &serveur::error, this, &console::errorOnServer);
    QObject::connect(serv, &serveur::noInternal, this, &console::exernalCommende);

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
    if(message["type"].toString()!="laucher"){
        return;
    }
    if(message["message"].toString()=="launchControl"){
        createPacket("versionServer", QCoreApplication::applicationVersion());
    }else if(message["message"].toString()=="startNew"){
        createFile(message["arg"].toString());
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
    log("the serveur general sent :"+logs);
}
int console::createFile(const QString name){
    QSettings room("room.ini", QSettings::IniFormat);
    if(settings->value("settings/port/NbOpenPort").toInt()>=room.value("NbOfRoom").toInt()){
        //tout les port sont pris
    }
    QDir folder;
    folder.mkpath(name);
    QFile log(name+"/"+name+".log");//on crée le fichier
    if(!log.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)){
        return 0;
    }
    QTextStream out(&log);//on initialise le fichier
    out<<"-----------------generate-by-Ananta-System-5.2-on-"+QDateTime::currentDateTime().toString("-dddd-dd-MMMM-yyyy-hh:mm:ss")+"s----------------"<<Qt::endl;
    const bool copy = QFile::copy(settings->value("settings/serverPath").toString(),
                                  name+"/"+settings->value("settings/serverPath").toString());//on crée un nouveaux serveur dans le dossier
    if(!copy){
        //il est imposible de copier le fichier
    }
    room.setValue("NbOfRoom",room.value("NbOfRoom").toInt()+1);//on augmente le nombre de salle
    QFile tmp(name+"/sart.tmp");
    if(!tmp.open(QIODevice::WriteOnly | QIODevice::Text)){
        return 0;
    }
    QTextStream outTmp(&tmp);//on initialise le fichier
    outTmp<<room.value(QString::number(room.value("NbOfRoom").toInt())).toInt();//on ecrit le port dans le fichier
    return room.value(QString::number(room.value("NbOfRoom").toInt())).toInt();//on donne le port
    //ouvrir le serveur
}
