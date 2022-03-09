#include <QCoreApplication>
#include <iostream>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QSettings>
#include "serveur/serveur.h"
bool removeDir(QString dir) //par Keisuke
{
    QDir dossier(dir);
    QFileInfoList listElem = dossier.entryInfoList(QDir::AllEntries);// On parcours la liste des élèments
    for(int i=2; i<listElem.size(); i++)
    {
        QFileInfo fi(listElem.at(i));// Si c'est un fichier
        if(fi.isFile())
        {
            if(!QFile::remove(fi.filePath()))// On supprime le fichier
            {
                return false;
            }
        }
        // Si c'est un dossier
        else if(fi.isDir())
        {// On supprime les fichiers par récursivité
            removeDir(fi.filePath());
        }
    }
    if(!dossier.rmdir(dossier.path()))
    {
        return false;
    }
    return true;
}
void clearEnvironement(const QString name){
    if(!removeDir(name)){
        std::cout << "error in remouve dir" << std::endl;
    }
    QSettings room("room.ini", QSettings::IniFormat);
    room.setValue("NbOfRoom",room.value("NbOfRoom").toInt()-1);//on reduit le nombre de salle
    std::cout << "remouve dir success" << std::endl;
}
class Console: public QObject
{
public:
    QString m_name;
    int nbClient;
    Console(const QString name){
        m_name = name;
    }
    /*~Console(){
        clearEnvironement(m_name);
    }*/
    void save(QString msg){
        const auto fichier = "log/"+m_name+".log";
        QFile file(fichier);//m_name crée le fichier
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)){
            return;
        }
        QTextStream out(&file);
        out<<msg.toUtf8()<<Qt::endl;
    }

    void pinUp(const QString message,const QString pseudo=""){
        if(pseudo==""){
            std::cout << message.toStdString() << std::endl;
        }else{
           std::cout <<"\""<<pseudo.toStdString()<<" \" sent the message : " <<message.toStdString() << std::endl;
        }
    }

    void log(const QString log){
        QString sDate = QDateTime::currentDateTime().toString("hh:mm:ss");
        QString message = "server log at "+sDate+" :   " +log.toUtf8();
        std::cout <<message.toStdString()<<std::endl;
        save(message);
    }

    void errorOnServer(QString title, QString msg){
        std::cout <<title.toStdString() <<" : " <<msg.toStdString()<<std::endl;
    }
    void serverLog(const QString logs){
        log(m_name +" send : "+logs);//on emet avec lo nom du repertoir courant
    }
    void user(utilisateur*user, const bool living){
        if(living){
            ++nbClient;
        }else{
            --nbClient;
            if(nbClient<=0){
                log("the last client has been desconect");
                log("<<<<end of this room>>>>");
                clearEnvironement(m_name);
                exit(0);
            }
        }
    }
};
bool createEnvironement(const QString name){
    bool notError = true;
    QDir dir;
    dir.mkdir("log");
    dir.mkdir(name);
    const QString time = QDateTime::currentDateTime().toString("dd-MM-yy-hh-mm-ss");
    QFile logFile("log/"+name+time+".log");//on crée le fichier
    if(!logFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)){
        notError = false;
    }else{
        QTextStream out(&logFile);//on initialise le fichier
        out<<"-----------------generate-by-Ananta-System-5.2-on-"+QDateTime::currentDateTime().toString("dd-MM-yy-hh:mm:ss")+"s----------------"<<Qt::endl;
    }
    QFile dataFile(name+"/"+name+".dat");
    if(!logFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)){
        notError =  false;
    }
    return notError;
}
int main(int argc, char *argv[])//les argument : le port de lancement, lenom de la salle
{

    QCoreApplication a(argc, argv);/*
    const QString port = argv[0];
    const QString name = argv[1];*/
    const QString port = "2048";
    const QString name = "test";
    if(port==""||name==""){
        std::cout << "error no argument inform"<<std::endl;
        exit(1);
    }
    Console console(name);
    if(!createEnvironement(name)){
        std::cout << "error in create environement"<<std::endl;
    }
    console.log("initialization...");
    serveur serv;
    QObject::connect(&serv, &serveur::display, &console, &Console::pinUp);//on connect
    QObject::connect(&serv, &serveur::log, &console, &Console::serverLog);
    QObject::connect(&serv, &serveur::error, &console, &Console::errorOnServer);
    QObject::connect(&serv, &serveur::ActionOnUser, &console, &Console::user);
    const int definitivePort = serv.startserveur(port.toInt(),name+"/"+name+".dat");//oncrée le serveur
    console.log("<<<<< the serveur of tchat has been create on port : "+QString::number(definitivePort)+">>>>>");
    //clearEnvironement(name);
    return a.exec();
}
