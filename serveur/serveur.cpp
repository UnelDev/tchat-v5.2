/*By Unel at 30/12/21
For Ananta Project*/
#include "serveur.h"

serveur::serveur()
{
    QCoreApplication::setOrganizationName("ananta system");
    QCoreApplication::setOrganizationDomain("https://anantasystem.com/");
    QCoreApplication::setApplicationName("tchat");
    QCoreApplication::setApplicationVersion("5.0");

    settings = new QSettings("settings.ini", QSettings::IniFormat);
    encryptioncesar = new cesar(2);
    m_serveur = new QTcpServer(this);
    psedo=tr("non rensengner","dans le constructeur du client a letape du psedo. c'est le psedo par defaut");
    NbOfMessage=0;
    recoverallfile();
}
void serveur::displayMessagelist(QString newMessage){ emit serveur::display(newMessage); }
int serveur::startserveur(int port)
{
    m_serveur = new QTcpServer(this);
    if (!m_serveur->listen(QHostAddress::Any, port)) // Démarrage du serveur sur toutes les IP disponibles et sur le port 2048
    {
        // Si le serveur n'a pas été démarré correctement
        if (!m_serveur->listen(QHostAddress::Any)) // Démarrage du serveur sur toutes les IP disponibles
        {
            // Si le serveur n'a pas été démarré correctement
            displayMessagelist(generatemesage(tr("Le serveur n'a pas pu être démarré. Raison :<br />") + m_serveur->errorString(),tr("Serveur Bot")));
            return 0;
        }
    }
    else
    {
        // Si le serveur a été démarré correctement
        displayMessagelist(generatemesage(tr("Le serveur a été démarré sur le port <strong>") + QString::number(m_serveur->serverPort()) + tr("</strong>.<br />Des clients peuvent maintenant se connecter."), tr("Chat Bot")));
        QObject::connect(m_serveur, &QTcpServer::newConnection, this, &serveur::newconect);
    }
    return m_serveur->serverPort();
}
//serveur
void serveur::sentmessagetoall(const QMap<QString, QVariant> &message)
{
    QByteArray pack;
    QDataStream out(&pack, QIODevice::WriteOnly);

    out << (quint16) 0; // On écrit 0 au début du paquet pour réserver la place pour écrire la taille
    out << message; // On ajoute le message à la suite
    out.device()->seek(0); // On se replace au début du paquet
    out << (quint16) (pack.size() - sizeof(quint16)); // On écrase le 0 qu'on avait réservé par la longueur du message
    //Sending
    for(int i = 0; i < clientsList.size(); i++)
    {
        clientsList[i]->getSocket()->write(pack);
    }
}
void serveur::sentmessageto(const QMap<QString, QVariant> &message, int NoUtilisateur)
{
    QByteArray pack;
    QDataStream out(&pack, QIODevice::WriteOnly);

    out << (quint16) 0; // On écrit 0 au début du paquet pour réserver la place pour écrire la taille
    out << message; // On ajoute le message à la suite
    out.device()->seek(0); // On se replace au début du paquet
    out << (quint16) (pack.size() - sizeof(quint16)); // On écrase le 0 qu'on avait réservé par la longueur du message
    //Sending
    clientsList[NoUtilisateur]->getSocket()->write(pack);
}
void serveur::sentmessagetoall(const QString type, QString message, QString pseudo){
    QMap<QString,QVariant> sendmap;
    sendmap["type"]=type;
    sendmap["message"]=encryptioncesar->chiffre(message);
    sendmap["pseudo"]=encryptioncesar->chiffre(pseudo);
    sendmap["secondofsending"]=QDateTime::currentDateTime().toString("ss");;
    sendmap["minuteofsending"]=QDateTime::currentDateTime().toString("mm");;
    sendmap["sendingtime"]=QDateTime::currentDateTime().toString("hh");
    sendmap["sendingdate"]=QDateTime::currentDateTime().toString("d");
    sendmap["shippingday"]=QDateTime::currentDateTime().toString("dddd");
    sendmap["shippingmonth"]=QDateTime::currentDateTime().toString("MMMM");
    sendmap["shippingyears"]=QDateTime::currentDateTime().toString("yyyy");
    sentmessagetoall(sendmap);
}
void serveur::sentmessageto(const QString &message, int NoUtilisateur)
{
    QMap<QString,QVariant> sendmap;
    sendmap["type"]="msg";
    sendmap["message"]=encryptioncesar->chiffre(message);
    sendmap["pseudo"]="serveur"+encryptioncesar->chiffre(psedo);
    sendmap["secondofsending"]=QDateTime::currentDateTime().toString("ss");;
    sendmap["minuteofsending"]=QDateTime::currentDateTime().toString("mm");;
    sendmap["sendingtime"]=QDateTime::currentDateTime().toString("hh");
    sendmap["sendingdate"]=QDateTime::currentDateTime().toString("d");
    sendmap["shippingday"]=QDateTime::currentDateTime().toString("dddd");
    sendmap["shippingmonth"]=QDateTime::currentDateTime().toString("MMMM");
    sendmap["shippingyears"]=QDateTime::currentDateTime().toString("yyyy");
    sentmessageto(sendmap,NoUtilisateur);
}
void serveur::sentmessageto(const QString &message,QString pseudo, int NoUtilisateur)
{
    QMap<QString,QVariant> sendmap;
    sendmap["type"]="msg";
    sendmap["message"]=encryptioncesar->chiffre(message);
    sendmap["pseudo"]=encryptioncesar->chiffre(pseudo);
    sendmap["secondofsending"]=QDateTime::currentDateTime().toString("ss");;
    sendmap["minuteofsending"]=QDateTime::currentDateTime().toString("mm");;
    sendmap["sendingtime"]=QDateTime::currentDateTime().toString("hh");
    sendmap["sendingdate"]=QDateTime::currentDateTime().toString("d");
    sendmap["shippingday"]=QDateTime::currentDateTime().toString("dddd");
    sendmap["shippingmonth"]=QDateTime::currentDateTime().toString("MMMM");
    sendmap["shippingyears"]=QDateTime::currentDateTime().toString("yyyy");
    sentmessageto(sendmap,NoUtilisateur);
}
void serveur::sentcomandto(const QVariant &message ,int usernaime)
{
    QMap<QString,QVariant> sendmap;
    sendmap["type"]="cmd";
    sendmap["message"]=message;
    sendmap["pseudo"]="serveur"+encryptioncesar->chiffre(psedo);
    sendmap["secondofsending"]=QDateTime::currentDateTime().toString("ss");;
    sendmap["minuteofsending"]=QDateTime::currentDateTime().toString("mm");;
    sendmap["sendingtime"]=QDateTime::currentDateTime().toString("hh");
    sendmap["sendingdate"]=QDateTime::currentDateTime().toString("d");
    sendmap["shippingday"]=QDateTime::currentDateTime().toString("dddd");
    sendmap["shippingmonth"]=QDateTime::currentDateTime().toString("MMMM");
    sendmap["shippingyears"]=QDateTime::currentDateTime().toString("yyyy");
    sentmessageto(sendmap,usernaime);

}
void serveur::sentcomandto(const QVariant &message,QString arg ,int usernaime)
{
    QMap<QString,QVariant> sendmap;
    sendmap["type"]="cmd";
    sendmap["message"]=message;
    sendmap["arg"]=encryptioncesar->chiffre(arg);
    sendmap["pseudo"]="serveur"+encryptioncesar->chiffre(psedo);
    sendmap["secondofsending"]=QDateTime::currentDateTime().toString("ss");;
    sendmap["minuteofsending"]=QDateTime::currentDateTime().toString("mm");;
    sendmap["sendingtime"]=QDateTime::currentDateTime().toString("hh");
    sendmap["sendingdate"]=QDateTime::currentDateTime().toString("d");
    sendmap["shippingday"]=QDateTime::currentDateTime().toString("dddd");
    sendmap["shippingmonth"]=QDateTime::currentDateTime().toString("MMMM");
    sendmap["shippingyears"]=QDateTime::currentDateTime().toString("yyyy");
    sentmessageto(sendmap,usernaime);

}
void serveur::sentcommande(const QString commande, QString arg){
    QMap<QString,QVariant> sendmap;
    sendmap["type"]="cmd";
    sendmap["message"]=commande;
    sendmap["arg"]=encryptioncesar->chiffre(arg);
    sendmap["pseudo"]="serveur"+encryptioncesar->chiffre(psedo);
    sendmap["secondofsending"]=QDateTime::currentDateTime().toString("ss");;
    sendmap["minuteofsending"]=QDateTime::currentDateTime().toString("mm");;
    sendmap["sendingtime"]=QDateTime::currentDateTime().toString("hh");
    sendmap["sendingdate"]=QDateTime::currentDateTime().toString("d");
    sendmap["shippingday"]=QDateTime::currentDateTime().toString("dddd");
    sendmap["shippingmonth"]=QDateTime::currentDateTime().toString("MMMM");
    sendmap["shippingyears"]=QDateTime::currentDateTime().toString("yyyy");
    sentmessagetoall(sendmap);
}
void serveur::newconect()
{
    utilisateur* newClient = new utilisateur(m_serveur->nextPendingConnection());
    clientsList.append(newClient);
    QObject::connect(clientsList.last()->getSocket(), &QTcpSocket::readyRead, this, &serveur::datareceived);
    QObject::connect(clientsList.last()->getSocket(), &QTcpSocket::disconnected, this ,&serveur::disconnectclients);
}
void serveur::connect(const QMap<QString, QVariant> &connectpack, int usernaime){
    QString username =encryptioncesar->deChiffre(connectpack["pseudo"].toString());
    clientsList[usernaime]->editpseudo(username);
    clientsList[usernaime]->editversion(connectpack["version"].toString());
    sentmessagetoall(connectpack);
    srand (time(NULL));
    int random = rand() % 4 + 1;
    if(random == 1){
        sentmessagetoall("msg",clientsList[usernaime]->getpseudo() + tr(" est connecté."),tr("Tchat Bot"));
    }else if(random == 2){
         sentmessagetoall("msg",clientsList[usernaime]->getpseudo() + tr(" vient d'arriver dans le salon."),tr("Tchat Bot"));
    }else if(random == 3){
        sentmessagetoall("msg",clientsList[usernaime]->getpseudo() + tr(" vient de nous rejoindre."),tr("Tchat Bot"));
    }else if(random == 4){
        sentmessagetoall("msg",tr("Il ne nous manquait plus que ")+clientsList[usernaime]->getpseudo()+ tr(" heureusement il nous a rejoint."),tr("Tchat Bot"));
    }
    for(int i = 0; i < saveMessage.size()-1; i++)
    {
        sentmessageto(saveMessage[i],usernaime);
    }
    for(int i = 0; i < clientsList.size()-1; i++){
        sentcomandto("isconnected",clientsList[i]->getpseudo(),usernaime);
    }

}
void serveur::datareceived()
{
    int index = findIndex(qobject_cast<QTcpSocket*>(sender()));
      utilisateur* sendingClient = clientsList[index];
      QTcpSocket* socket = sendingClient->getSocket();

      if(socket == nullptr) {
        displayMessagelist(generatemesage(tr("erreur lors de la recherche du client qui a envoyé le paquet (non il y a pas de jeux de mot pouris)"),tr("serveur bot")));
        return; //Error
      }
      QDataStream in(socket);
        while(1){
            if(sendingClient->getmessageSize() == 0) { //Try to catch
                if(socket->bytesAvailable() < static_cast<int>(sizeof(quint16))){
                    return;
                }
                quint16 messageSize;
                in >> messageSize;
                sendingClient->setmessageSize(messageSize);
            }
            if(socket->bytesAvailable() < sendingClient->getmessageSize()){ //Part of the message missing
            return;
            }
            QMap<QString, QVariant>message;
            in >> message;
            sendingClient->setmessageSize(static_cast<quint16>(0));
        if(message["type"]=="cmd"){//une commende
            message["arg"]=encryptioncesar->deChiffre(message["arg"].toString());
            message["pseudo"]=encryptioncesar->deChiffre(message["pseudo"].toString());
            processcomand(message,index);
        }else if(message["type"]=="msg"){
                sentmessagetoall(message);
                if(settings->value("settings/SaveMessage").toBool()){
                    writetofile(message);
                }
        }else if(message["type"]=="attachment"){
            //message["idOfFile"]=Listfile.size();
            /*QFile fileOut(message["nameOfFile"].toString());
            fileOut.open(QIODevice::WriteOnly);
            fileOut.write(message["attachment"].toByteArray().toStdString().data());
            qDebug() << message["attachment"].toByteArray().toStdString().data();*/
            sentmessagetoall(message);
            if(settings->value("settings/SaveMessage").toBool()){
                writetofile(message);
            }
        }else if(message["type"]=="connection"){
            connect(message, index);
        }else{
        QMessageBox::critical(nullptr, tr("erreur"), tr("un paquet de comande a été recu mais la l'idantificateur ")+ message["type"].toString() +tr("est incompri."));
        displayMessagelist(generatemesage(tr("un paquet de comande a été recu mais la l'idantificateur ")+ message["type"].toString() +tr("est incompri."),tr("serveur bot")));
    }
        sendingClient->setmessageSize(static_cast<quint16>(0));
    }
}
void serveur::disconnectclients()
{
    QTcpSocket* disconnectingClientSocket = qobject_cast<QTcpSocket*>(sender());

    if(disconnectingClientSocket == nullptr) //Error
    {
        displayMessagelist(generatemesage(tr("Erreur fatal: les clients ne peuvent pas être supprimés. fermeture!"),tr("Serveur Bot")));
        QMessageBox::critical(nullptr, tr("Erreur fatal"),tr("Les clients ne peuvent pas être supprimés. fermeture!"));
        qApp->quit();
        return;
    }

    int index = findIndex(disconnectingClientSocket);
    utilisateur* disconnectingClient = clientsList[index];
    sentcommande("disconnected",disconnectingClient->getpseudo());

    clientsList.removeOne(disconnectingClient);
    disconnectingClient->deleteLater();
}
int serveur::findIndex(QTcpSocket* socket)
{
    int index = 0;
    while(clientsList[index]->getSocket() != socket)
    {
        index++;
    }
    return index;
}
void serveur::writetofile(QMap<QString, QVariant> FluxFile)
{
    saveMessage.push_back(FluxFile);
    ++NbOfMessage;
    QFile file("chat.dat");
    if (!file.open(QIODevice::WriteOnly)){
            displayMessagelist(generatemesage(tr("Il est impossible d'écrire dans le fichier."),tr("Tchat Bot")));
            return;
        }
    QDataStream out(&file);
    out <<saveMessage;
}
void serveur::recoverallfile()
{
    QFile fichier("chat.dat");

   if(fichier.open(QIODevice::ReadOnly))
   {
       QByteArray paquet;
       paquet = fichier.readAll();// Lecture entier de notre fichier en octet
       QDataStream out(paquet);
       out>>saveMessage;

   }
   else
   {
       displayMessagelist(generatemesage(tr("Le fichier est inaxcessible"), tr("System Tchat Bot")));

   }
}
void serveur::processcomand(QMap<QString, QVariant> command, int noclient)
{
    if (command["message"]=="change_psedo") {// changer psedo
        for(int i = 1; i < clientsList.size(); i++)
        {
            if(clientsList[i]->getpseudo()==command["arg"] && i != noclient){//si c'est le meme on coupe et on envoie une erreur
                sentcomandto("pseudoalreadyuse",noclient);
                return;
            }else if(clientsList[i]->getpseudo().remove(" ")==command["arg"].toString().remove(" ") && i != noclient){//si c'est resembleaut on coupe et on envoie une erreur
                sentcomandto("pseudoresembling",noclient);
                return;
            }
        }
        sentmessagetoall("msg",clientsList[noclient]->getpseudo()+" a changer son psedo en "+ command["arg"].toString(),"Tchat Bot");
        clientsList[noclient]->editpseudo(command["arg"].toString());
    /*}else if(command["message"]=="file?") {
        sentcomandto(Listfile[command["arg"].toInt()],noclient);
    */}else{
        QMessageBox::critical(nullptr, tr("erreur"), tr("Un paquet de commande a été reçu mais la commande est incomprise."));
    }
}
QString serveur::generatedate()
{
    QString heures = QDateTime::currentDateTime().toString(" hh:mm:ss ");
    QString Date = QDateTime::currentDateTime().toString(" dd MM yyyy ");
    QDateTime::fromString(heures, " hh:mm:ss ");
    return(tr("<span style=\"font-size: 10px\"> Le ")+Date+tr("</span> <span style=\"font-size: 10px\">à ")+heures+tr(" </span><br/>"));
}
QString serveur::generatemesage(QString message, QString pseudo)
{
    return(tr("<span style=\"font-size: 12px; color:#000000; font-weight: bold;\">")+pseudo+tr("</span>")+generatedate()+tr("<span style=\"font-size: 14px; color:#2F2F2F\">")+message+tr("</span><br/><br/>"));
}
