/*By Unel at 30/12/21
For Ananta Project*/
#include "utilisateur.h"

utilisateur::utilisateur()
{
    pseudo = "anonymous";
    socket = new QTcpSocket;
    messageSize = 0;
    vertion = "0";
}
utilisateur::utilisateur(QTcpSocket* socketToServer)
{
    pseudo = "anonymous";
    socket = socketToServer;
    messageSize = 0;
    vertion = "0";
}
utilisateur::utilisateur(QString pseudo, QTcpSocket* socket)
{
    this->pseudo = pseudo;
    this->socket = socket;
    messageSize = 0;
    vertion = "0";
}
utilisateur::~utilisateur(){
    delete socket;
}
QTcpSocket* utilisateur::getSocket()
{
    return socket;
}

void utilisateur::setmessageSize(quint16 size)
{
    messageSize = size;
}
quint16 utilisateur::getmessageSize()
{
    return messageSize;
}
QString utilisateur::getpseudo()
{
    return pseudo;
}
QString utilisateur::getversion()
{
    return vertion;
}
void utilisateur::editversion(QString newvertion){
    vertion = newvertion;
}
void utilisateur::editpseudo(QString newpsedo)
{
    pseudo = newpsedo;
}
bool utilisateur::isconnecteed()
{
    if(getpseudo()=="Anonymous"&&vertion!=0){
        return false;
    }else{
        return true;
    }
}
QString utilisateur::safe(){
    if((pseudo!="anonymous"&&pseudo!="")&&(vertion=="5.0")){
        if(pseudo==pseudo&&vertion==vertion){
            return "high";
        }else{
            return "medium";
        }
    }else{
        return "low";
    }
}
bool utilisateur::highSafe(){
    if(safe()=="high"){
        return true;
    }else{
        return false;
    }
}
bool utilisateur::medumSafeOrSuperior(){
    if(safe()=="medium"||safe()=="high"){
        return true;
    }else{
        return false;
    }
}
bool utilisateur::lowSafeOrSuperior(){
    if(safe()=="low"||safe()=="medium"||safe()=="high"){
        return true;
    }else{
        return false;
    }
}
