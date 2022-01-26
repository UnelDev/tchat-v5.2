#include <QCoreApplication>
#include <serveur/serveur.h>
#include <iostream>
#include <QObject>
#include <QSettings>
class console : public QObject
{
public:
    QSettings *settings;
    bool write;
    console(){
         settings= new QSettings("settings.ini", QSettings::IniFormat);
    }
    void pinUp(const QString message,const QString pseudo = ""){
        if(pseudo==""){
            std::cout << message.toStdString() << std::endl;
        }else{
           std::cout <<"\""<<pseudo.toStdString()<<" \" sent the message : " <<message.toStdString() << std::endl;
        }

    }
    void errorOnServer(QString title, QString msg){
        std::cout <<title.toStdString() <<" : " <<msg.toStdString()<<std::endl;
    }
    void log(const QString log){
        std::cout <<"server log :   " <<log.toUtf8().toStdString()<<std::endl;
        if(settings->value("settings/logPaht")!=""){
            QFile file("out.txt");
            if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
                return;
            QTextStream out(&file);
            out<<log;
        }
    }

};

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("ananta system");
    QCoreApplication::setOrganizationDomain("https://anantasystem.com/");
    QCoreApplication::setApplicationName("tchat");
    QCoreApplication::setApplicationVersion("5.2");
    QCoreApplication a(argc, argv);
    console display;
    display.pinUp("initialization...");
    QSettings settings("settings.ini", QSettings::IniFormat);
    if(!settings.contains("settings/SaveMessage")){
        settings.setValue("settings/SaveMessage",true);
    }if(!settings.contains("settings/high")){
        settings.setValue("settings/level of secure","high");
    }if(!settings.contains("settings/log")){
        settings.setValue("settings/log",true);
    }if(!settings.contains("settings/logPaht")){
        settings.setValue("settings/logPaht","");
    }
    serveur serv;
    QObject::connect(&serv, &serveur::display, &display, &console::pinUp);
    QObject::connect(&serv, &serveur::error, &display, &console::errorOnServer);
    if(settings.value("settings/log").toBool()){
        QObject::connect(&serv, &serveur::log, &display, &console::log);
    }
    int port =serv.startserveur(2048);
    display.pinUp("the server has been start of port "+QString::number(port));
    display.pinUp("initialization down !");
    display.pinUp("");
    return a.exec();
}


