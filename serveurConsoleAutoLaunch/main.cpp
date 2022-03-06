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
    void save(QString msg){
        const auto fichier = "settings.ini";
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
        log(QDir::currentPath().split("/").last() +" send : "+logs);//on emet avec lo nom du repertoir courant
    }
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Console console;
    console.log("initialization...");
    serveur serv;
    QSettings settings("settings.ini", QSettings::IniFormat);
    QObject::connect(&serv, &serveur::display, &console, &Console::pinUp);
    QObject::connect(&serv, &serveur::log, &console, &Console::serverLog);
    QObject::connect(&serv, &serveur::error, &console, &Console::errorOnServer);
    const int port  = serv.startserveur(2048);
    console.log("<<<<< the serveur of tchat has been create on port : "+QString::number(port)+">>>>>");
    return a.exec();
}
