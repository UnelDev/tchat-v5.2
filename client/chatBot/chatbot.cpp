#include "chatbot.h"

chatBot::chatBot(){}
void chatBot::emitMessage(const QString message){
    emit chatBot::sendInternalCommend("message",message);
}
void chatBot::emitCommende(const QString command){
    emit chatBot::sendInternalCommend("cmd",command);
}
void chatBot::proccess(const QString command, const QString psedo){
    srand (time(NULL));
    //reponse pré faite
    if (command==tr("bonjour")||command==tr("salut")||command==tr("hello")){//posibilier de question
        int random = rand() % 5 + 1;//on fait l'aleatoire
        if(random == 1){
            emitMessage(generatemesage(tr("Bonjour") + psedo+".",tr("Tchat Bot")));
        }else if(random == 2){
            emitMessage(generatemesage(tr("Salut") + psedo+".",tr("Tchat Bot")));
        }else if(random == 3){
            emitMessage(generatemesage(tr("Salut🖖") + psedo+".",tr("Tchat Bot")));
        }else if(random == 4){
            emitMessage(generatemesage(tr("Hello") + psedo+".",tr("Tchat Bot")));
        }else if(random == 5){
            emitMessage(generatemesage(tr("Hello👋") + psedo+".",tr("Tchat Bot")));
        }
    }else if (command==tr("comment t'apelle tu")||command==tr("quel est ton nom")){
        int random = rand() % 2 + 1;
        if(random == 1){
            emitMessage(generatemesage(tr("Tu peux m'appeller Tchat Bot."),tr("Tchat Bot")));
        }else if(random == 2){
            emitMessage(generatemesage(tr("Tu peux m'appeller Tchat Bot 😊."),tr("Tchat Bot")));
        }
    }else if (command==tr("qui est tu")){
        emitMessage(generatemesage(tr("Je suis le Tchat Bot crée par les développeurs de Ananta System, je suis encore très inachevé."),tr("Tchat Bot")));
    }else if (command=="clear"){
        emitCommende("clear");
    }else if (command=="clearall"){
           emitCommende("clearForAll");
    }else if(command.startsWith("userAction")){
        emit chatBot::sendInternalCommend("promot");
    }else if(command.startsWith("acept")){
        emit chatBot::sendInternalCommend("userRoom");
    }else if (command=="actualise"||command=="update"){
         emitCommende("updating");
    }else if (command==tr("merci")){
        int random = rand() % 7 + 1;
        if(random == 1){
            emitMessage(generatemesage(tr("De rien 😀"),tr("Tchat Bot")));
        }else if(random == 2){
            emitMessage(generatemesage(tr("Tout le plaisir est pour moi 😀"),tr("Tchat Bot")));
        }else if(random == 3){
            emitMessage(generatemesage(tr("Tout le plaisir est pour moi!"),tr("Tchat Bot")));
        }else if(random == 3){
            emitMessage(generatemesage(tr("De rien !"),tr("Tchat Bot")));
        }else if(random == 4){
            emitMessage(generatemesage(tr("Mais je suis là pour ça bien sûr 😀"),tr("Tchat Bot")));
        }else if(random == 5){
            emitMessage(generatemesage(tr("Mais je suis là pour ça bien sûr !"),tr("Tchat Bot")));
        }else if (random == 6){
             emitMessage(generatemesage(tr("Quand tu ne me parle pas je fais que des actions répétitives, recevoir des messages et les afficher😥..."),tr("Tchat Bot")));
        }else if (random == 7){
             emitMessage(generatemesage(tr("Quand tu ne me parle pas je m'ennuie 😥"),tr("Tchat Bot")));
    }else if (command==tr("condenses")||command==tr("condense")||command==tr("condense menu")){
        emit sendInternalCommend("condensed");
     }else if (command==tr("comment condenser la fenetre")||command==tr("comment condenser le menu")||command==tr("compacter la fenetre")){
        int random = rand() % 2 + 1;
        if(random == 1){
            emitMessage(generatemesage(tr("Il suffit de taper la commande /condense", "Attention bien taper la même commande!"),tr("Tchat Bot")));
        }else if(random == 2){
            emitMessage(generatemesage(tr("Tu peux faire clique droit sur l'icône en bas à droite dans ta barre des tâches -> Condenser la fenêtre"),tr("Tchat Bot")));
        }
    }
    }else{
       emitMessage(generatemesage(tr("Je suis desolé, mais je n'ai pas compris votre demande, vérifiez l'orthographe."),tr("Tchat Bot")));
   }
}
QString chatBot::generatemesage(QString message, QString pseudo)
{
   if(pseudo == "" ||pseudo == " "){
       pseudo = "anonymous";
   }
   return(tr("<span style=\"font-size: 12px; font-weight: bold;\">")+pseudo+tr("</span>")+generatedate()+tr("<span style=\"font-size: 14px; \">")+message+tr("</span><br/><br/>"));
}
QString chatBot::generatedate()
{
    QString heures = QDateTime::currentDateTime().toString("hh:mm:ss");
    QString Date = QDateTime::currentDateTime().toString("ddd dd MMMM yyyy");
    QDateTime::fromString(heures, "hh:mm:ss");
    return ("<span style=\"font-size: 10px\">"  +   tr("le ")    +   Date    +"</span> <span style=\"font-size: 10px\">"+   tr("à") +   heures +"</span><br/>");
}
void chatBot::startUserAction(const QList<QString> userlist){
    useraction *usrAction = new useraction;
    usrAction->show();
        for(int i=0;i<userlist.size();i++){
            usrAction->addUser(userlist[i]);
        }
    QObject::connect(usrAction,&useraction::finish,this, &chatBot::finishUseraction);
}
void chatBot::startChangeUserRoom(const QList<QString> userlist){
    changeUserRoom *usrRoom;
    std::async(std::launch::deferred, [&](){usrRoom = new changeUserRoom;});//on crée l'object de maniere asycronne ( a tester)
    usrRoom->show();
    for(int i=0;i<userlist.size();i++){
        usrRoom->addUser(userlist[i]);
    }
    QObject::connect(usrRoom,&changeUserRoom::finish,this , &chatBot::finishChangeUserRoom);
}
void chatBot::finishChangeUserRoom(const QString username, const QString room){
    emit chatBot::sendInternalCommend("ChangeUserRoom",username,room);
    useraction *usraction = qobject_cast<useraction*>(sender());
    usraction->deleteLater();
}
void chatBot::finishUseraction(QString name, int grade){
    emit chatBot::sendInternalCommend("Useraction",name,grade);
    changeUserRoom *usrRoom = qobject_cast<changeUserRoom*>(sender());
    usrRoom->deleteLater();
}
