/*By Unel at 30/12/21
For Ananta Project*/
#include "utilisateur.h"

utilisateur::utilisateur()
{
    pseudo = "anonymous";
    socket = new QTcpSocket;
    messageSize = 0;
    vertion = "0";
    m_grade = 0;
    room = "waiting";
}
utilisateur::utilisateur(QTcpSocket* socketToServer)
{
    pseudo = "anonymous";
    socket = socketToServer;
    messageSize = 0;
    vertion = "0";
    m_grade = 0;
    room = "waiting";
}
utilisateur::utilisateur(QString pseudo, QTcpSocket* socket)
{
    this->pseudo = pseudo;
    this->socket = socket;
    messageSize = 0;
    vertion = "0";
    m_grade = 0;
    room = "waiting";
}
utilisateur::~utilisateur(){
    delete socket;
}
QTcpSocket* utilisateur::getSocket()
{
    return socket;
}

void utilisateur::setmessageSize(int size)
{
    messageSize = size;
}
void utilisateur::promote(int grade){
    if(grade == 0|| grade ==1 || grade ==2){
      m_grade = grade;
    }
}
void utilisateur::changeRoom(QString newRoom){
    room = newRoom;
}
int utilisateur::getmessageSize()
{
    return messageSize;
}
int utilisateur::getGrade(){
    return m_grade;
}

QString utilisateur::getpseudo()
{
    return pseudo;
}
QString utilisateur::getversion()
{
    return vertion;
}
QString utilisateur::getRoom(){
    return room;
}
QString utilisateur::getGradeString(){
    if(m_grade==0){
        return tr("utilisateur", "dans les grade");
    }else if(m_grade==1){
        return tr("admin", "dans les grade");
    }else if(m_grade==2){
        return tr("host", "dans les grade");
    }else{
        return tr("erreur aucun grade touvée", "dans les grade");
    }
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
