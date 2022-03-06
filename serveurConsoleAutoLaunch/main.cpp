#include <QCoreApplication>
#include <iostream>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QSettings>
#include "serveur/serveur.h"
class Console: public QObject
{
public:
    QString m_name;
    int nbClient;
    Console(const QString name){
        m_name = name;
    }
    ~Console(){
        QFile::remove(m_name+"/"+m_name+".dat");
        const QString nameSave = QDir::currentPath()+"/"+m_name+"_"+QDateTime::currentDateTime().toString("-dddd-dd-MMMM-yyyy-hh:mm:ss");
        QFile::rename(m_name+"/"+m_name+".log",nameSave);

        QSettings room("room.ini", QSettings::IniFormat);
        room.setValue("NbOfRoom",room.value("NbOfRoom").toInt()-1);//on reduit le nombre de salle
    }
    void save(QString msg){
        const auto fichier = m_name+"/"+m_name+".log";
        QFile file(fichier);//on crée le fichier
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
                exit(0);
            }
        }
    }
};
bool createEnvironement(const QString name){
    QDir dir;
    dir.mkdir(name);
    QFile logFile(name+"/"+name+".log");//on crée le fichier
    if(!logFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)){
        return false;
    }else{
        QTextStream out(&logFile);//on initialise le fichier
        out<<"-----------------generate-by-Ananta-System-5.2-on-"+QDateTime::currentDateTime().toString("-dddd-dd-MMMM-yyyy-hh:mm:ss")+"s----------------"<<Qt::endl;
        return true;
    }
}
int main(int argc, char *argv[])//les argument : le port de lancement, lenom de la salle
{

    QCoreApplication a(argc, argv);
    const QString port = argv[0];
    const QString name = argv[1];
    if(port==""||name==""){
        std::cout << "error no argument inform"<<std::endl;
        exit(1);
    }
    Console console(name);
    /*if(!createEnvironement(name)){
        std::cout << "error in create environement"<<std::endl;
    }*/
    console.log("initialization..."); 
    serveur serv;
    QObject::connect(&serv, &serveur::display, &console, &Console::pinUp);//on connect
    QObject::connect(&serv, &serveur::log, &console, &Console::serverLog);
    QObject::connect(&serv, &serveur::error, &console, &Console::errorOnServer);
    QObject::connect(&serv, &serveur::ActionOnUser, &console, &Console::user);
    const int definitivePort = serv.startserveur(port.toInt(),name+"/"+name+".dat");//oncrée le serveur
    console.log("<<<<< the serveur of tchat has been create on port : "+QString::number(definitivePort)+">>>>>");
    return a.exec();
}
