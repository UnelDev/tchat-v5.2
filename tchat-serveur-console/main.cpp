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
        QString sDate = QDateTime::currentDateTime().toString("hh:mm:ss");
        QString message = "server log at "+sDate+" :   " +log.toUtf8();
        std::cout <<message.toStdString()<<std::endl;
        save(message);

    }
    void save(QString msg){
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
    display.pinUp("-----------------generate-by-Ananta-System-5.2-on-"+QDateTime::currentDateTime().toString("-dddd-dd-MMMM-yyyy-hh:mm:ss")+"s----------------");
    display.save("-----------------generate-by-Ananta-System-5.2-on-"+QDateTime::currentDateTime().toString("-dddd-dd-MMMM-yyyy-hh:mm:ss")+"s----------------");
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


