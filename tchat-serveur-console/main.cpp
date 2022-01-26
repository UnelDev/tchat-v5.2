#include <QCoreApplication>
#include <serveur/serveur.h>
#include <iostream>
#include <QObject>
class console : public QObject
{
public:
    void pinUp(QString message){
        std::cout <<message.toStdString() << std::endl;
    }
    void errorOnServer(QString title, QString msg){
        std::cout <<title.toStdString() <<" : " <<msg.toStdString()<<std::endl;
    }
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    console display;
    display.pinUp("initialization...");
    serveur serv;
    QObject::connect(&serv, &serveur::display, &display, &console::pinUp);
    QObject::connect(&serv, &serveur::error, &display, &console::errorOnServer);
    int port =serv.startserveur(2048);
    display.pinUp("the server has been start of port "+QString::number(port));
    display.pinUp("initialization down !");
    return a.exec();
}


