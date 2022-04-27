#include "console.h"

console::console(int Preferedport)
{
    encryptioncesar = new cesar(2);
    QCoreApplication::setOrganizationName("ananta system");
    QCoreApplication::setOrganizationDomain("https://anantasystem.com/");
    QCoreApplication::setApplicationName("tchat");
    QCoreApplication::setApplicationVersion("5.2");
    settings = new QSettings("settings.ini", QSettings::IniFormat);


    serv = new serveur();
    QObject::connect(serv, &serveur::display, this, &console::pinUp);
    QObject::connect(serv, &serveur::log, this, &console::serverLog);
    QObject::connect(serv, &serveur::error, this, &console::errorOnServer);
    QObject::connect(serv, &serveur::noInternal, this, &console::exernalCommende);

    int port =serv->startserveur(Preferedport);
    pinUp("the server has been start of port "+QString::number(port));
    listeServer = QMap<QString,QVariant>();
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
void console::exernalCommende(QMap<QString, QVariant> &message,const int user){
    cesar chiffremment(2);
    message["message"]=chiffremment.deChiffre(message["message"].toString());
    message["arg"]=chiffremment.deChiffre(message["arg"].toString());
    message["arg2"]=chiffremment.deChiffre(message["arg2"].toString());
    message["pseudo"]=chiffremment.deChiffre(message["pseudo"].toString());
    if(message["type"].toString()!="laucher"){
        return;
    }
    if(message["message"].toString()=="launchControl"){
        createPacket(user,"versionServer", QCoreApplication::applicationVersion());
    }else if(message["message"].toString()=="startNew"){
        createPacket(user,"createServer");
        createFile(message["arg"].toString(),user);
    }else if(message["message"].toString()=="getListServer"){
        //nous allon listée les serveur
        sentMap(user,"listServer",listeServer);
    }
}
void console::createPacket(const int index, const QString message, const QString arg1, const QString arg2){
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
    serv->sentmessageto(packet,index);
}
void console::sentMap(const int index, const QString message,QMap<QString,QVariant>mymap){
    // Create a map and insert some values
    QMap<QString, QVariant> packet;
    packet["type"]="laucher";
    packet["message"]=encryptioncesar->chiffre(message);
    packet["pseudo"]=encryptioncesar->chiffre("botLauncher");
    packet["arg"]=mymap;
    packet["secondofsending"]=QDateTime::currentDateTime().toString("ss");;
    packet["minuteofsending"]=QDateTime::currentDateTime().toString("mm");;
    packet["sendingtime"]=QDateTime::currentDateTime().toString("hh");
    packet["sendingdate"]=QDateTime::currentDateTime().toString("d");
    packet["shippingday"]=QDateTime::currentDateTime().toString("dddd");
    packet["shippingmonth"]=QDateTime::currentDateTime().toString("MMMM");
    packet["shippingyears"]=QDateTime::currentDateTime().toString("yyyy");
    serv->sentmessageto(packet,index);
}
void console::serverLog(const QString logs){
    log("the serveur general sent :"+logs);
}
int console::createFile(const QString name, const int index){
    QSettings room("room.ini", QSettings::IniFormat);
    if(!room.contains("NbOpenPort")){room.setValue("NbOpenPort",1);}
    if(!room.contains("NbOfRoom")){room.setValue("NbOfRoom",0);}
    if(!room.contains("1")){room.setValue("1",2049);}
    if(room.value("NbOpenPort").toInt()<=room.value("NbOfRoom").toInt()){
        log("error all port is taken");
        return(0);
    }
    room.setValue("NbOfRoom",room.value("NbOfRoom").toInt()+1);//on augmente le nombre de salle

    QProcess* starter = new QProcess();
    QStringList arg;
    const int portPrefered = room.value(room.value("NbOfRoom").toString()).toInt();
    arg.push_back(QString::number(portPrefered));//on met le port
    arg.push_back(name);
    starter->setArguments(arg);
    starter->setProgram(settings->value("settings/serverPath").toString());
    starter->start(settings->value("settings/serverPath").toString(),arg);
    connect(starter, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
        [=](int exitCode, QProcess::ExitStatus exitStatus){ console::finished(exitCode,exitStatus);});
    if(0){
        log("error on start server");
    }else{
        listeServer[name]=portPrefered;
        log("the demarage is down");
        createPacket(index, "starting",QString::number(portPrefered));
    }
    return room.value(room.value("NbOfRoom").toString()).toInt();//on donne le port
}


void console::finished(int exitCode, QProcess::ExitStatus exitStatus){
    //une erreur avec le serveur est survenus
    if(exitCode!=0){
        log("error on server: exit code "+QString::number(exitCode));
    }
    if(exitStatus==QProcess::CrashExit){
        log("error on server: exit status crash");
    }
}
