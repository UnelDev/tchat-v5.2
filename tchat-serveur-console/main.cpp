#include <QCoreApplication>
#include <serveur/serveur.h>
#include <iostream>
#include <QObject>
#include <QSettings>
#include "console.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("ananta system");
    QCoreApplication::setOrganizationDomain("https://anantasystem.com/");
    QCoreApplication::setApplicationName("tchat");
    QCoreApplication::setApplicationVersion("5.2");
    QCoreApplication a(argc, argv);

    std::cout << "initialization..." << std::endl;
    QSettings settings("settings.ini", QSettings::IniFormat);
    if(!settings.contains("settings/SaveMessage")){
        settings.setValue("settings/SaveMessage",true);
    }if(!settings.contains("settings/high")){
        settings.setValue("settings/level of secure","high");
    }if(!settings.contains("settings/log")){
        settings.setValue("settings/log",true);
    }if(!settings.contains("settings/logPaht")){
        settings.setValue("settings/logPaht","general.log");
    }if(!settings.contains("settings/port")){
        settings.setValue("settings/port",2048);
    }if(!settings.contains("settings/serverPath")){
        settings.setValue("settings/serverPath","serveur.exe");
    }if(!settings.contains("settings/port/NbOpenPort")){
        settings.setValue("settings/port/NbOpenPort",0);
    }
    std::cout << "-----------------generate-by-Ananta-System-5.2-on-"<< QDateTime::currentDateTime().toString("-dddd-dd-MMMM-yyyy-hh:mm:ss").toStdString() << "s----------------"<<std::endl;
    console display(settings.value("settings/port").toInt());
    display.save("-----------------generate-by-Ananta-System-5.2-on-"+QDateTime::currentDateTime().toString("-dddd-dd-MMMM-yyyy-hh:mm:ss")+"s----------------");
    return a.exec();
}
