/*By Unel at 30/12/21
For Ananta Project*/
#include "client.h"
client::client()
{
    //lib externe
    QCoreApplication::setOrganizationName("ananta system");
    QCoreApplication::setOrganizationDomain("https://anantasystem.com/");
    QCoreApplication::setApplicationName("tchat");
    QCoreApplication::setApplicationVersion("5.2.2");
    //variable global
    //variable complex
    cesar(1);
    encryptioncesar = new cesar(2);
    settings = new QSettings("settings.ini", QSettings::IniFormat);
    socket = new QTcpSocket(this);
    //variable simple
    messagesize=0;
    nbuser=0;
    psedo=tr("non rensengner","dans le constructeur du client a letape du psedo. c'est le psedo par defaut");
    //connexion
    connect(socket, &QTcpSocket::readyRead, this ,&client::datareceived);
    connect(socket, &QTcpSocket::connected,this, &client::connected);
    connect(socket, &QTcpSocket::disconnected,this, &client::disconnect);
    connect(socket, &QTcpSocket::errorOccurred, this, &client::socketerror);

}
//emeteur
void client::deleteclient(QString nameOfClient){ emit client::remouveClient(nameOfClient);}
void client::displayMessagelist(QString newMessage){ emit client::display(newMessage); }
void client::changestateconnectbutton(bool state){ emit client::changestateconnect(state); }
void client::newclient(QString newClientName){ emit client::newuser(newClientName); }
void client::displayconnectlabel(QString newText){ emit client::changeTextConnect(newText);}
//deccesseurs
void client::sendmessage(QString message){ sentdatamap("msg",message); }//a faire

void client::connectto(QString ip, int port, QString newpsedo)
{
    psedo = newpsedo;
    displayMessagelist(generatemesage(tr("Tentative de connexion en cours..."),tr("Tchat Bot")));
    changestateconnectbutton(false);
    socket->abort();
    socket->connectToHost(ip, port);
    displayconnectlabel("<font color=\"#894B23\">"+tr("Connexion lancée", "dans les tentative de connexion dans le client")+"</font>");
}
void client::connected()
{
    QString textmessage = generatemesage(tr("Connexion établie!"), tr("Tchat Bot"));
    sentdatamap("connection");
    displayMessagelist(textmessage);
    changestateconnectbutton(true);
    displayconnectlabel(tr("<font color=\"#70AD47\">Connecté</font>"));
}
void client::disconnect()
{
    QString textmessage = generatemesage(tr("Déconnecté du serveur"),tr("Tchat Bot"));
    displayconnectlabel(tr("<font color=\"#ff0000\">Déconnecté</font>"));
    displayMessagelist(textmessage);
    changestateconnectbutton(true);
}
void client::socketerror(QAbstractSocket::SocketError erreur)
{
    displayconnectlabel(tr("<font color=\"#ff0000\">Déconnecté</font>"));
    switch(erreur) // On affiche un message diff?rent selon l'erreur qu'on nous indique
    {
        case QAbstractSocket::HostNotFoundError:
            displayMessagelist(generatemesage(QObject::tr("Erreur: Le serveur n'a pas pu être trouvé. Vérifiez l'adresse et le pin."),tr("System Tchat Bot")));
            changestateconnectbutton(true);
        break;

        case QAbstractSocket::ConnectionRefusedError:
            displayMessagelist(generatemesage(QObject::tr("Erreur: Le serveur a refusé la connexion. Vérifiez si le programme \"serveur\" a bien été lancé. Vérifiez aussi l'adresse et le pin."),tr("System Tchat Bot")));
            changestateconnectbutton(true);
        break;

        case QAbstractSocket::RemoteHostClosedError:
            displayMessagelist(generatemesage(QObject::tr("Erreur: Le serveur a coupé la connexion."),tr("System Tchat Bot")));
            changestateconnectbutton(true);
        break;

        case QAbstractSocket::SocketAccessError:
            displayMessagelist(generatemesage(QObject::tr("Erreur: L'opération a échoué car l'application ne dispose pas des privilèges requis."),tr("System Tchat Bot")));
            changestateconnectbutton(true);
        break;
        case QAbstractSocket::SocketResourceError:
            displayMessagelist(generatemesage(QObject::tr("Erreur: Le système local a manqué de ressources."),tr("System Tchat Bot")));
            changestateconnectbutton(true);
        break;

        case QAbstractSocket::SocketTimeoutError:
            displayMessagelist(generatemesage(QObject::tr("Erreur: L'opération a expirée."),tr("System Tchat Bot")));
            changestateconnectbutton(true);
        break;

        case QAbstractSocket::DatagramTooLargeError:
            displayMessagelist(generatemesage(QObject::tr("Erreur: Le datagramme était plus grand que la limite du système d'exploitation (qui peut être aussi basse que 8192 octets)."),tr("System Tchat Bot")));
            changestateconnectbutton(true);
        break;
        case QAbstractSocket::NetworkError:
            displayMessagelist(generatemesage(QObject::tr("Erreur: Une erreur s'est produite avec le réseau ."),tr("System Tchat Bot")));
            changestateconnectbutton(true);
        break;

        case QAbstractSocket::UnsupportedSocketOperationError:
            displayMessagelist(generatemesage(QObject::tr("Erreur: L'opération de socket demandée n'est pas prise en charge par le système d'exploitation."),tr("System Tchat Bot")));
            changestateconnectbutton(true);
        break;

        case QAbstractSocket::ProxyAuthenticationRequiredError:
            displayMessagelist(generatemesage(QObject::tr("Erreur: Le proxy requiert une authentification."),tr("System Tchat Bot")));
            changestateconnectbutton(true);
        break;

        case QAbstractSocket::ProxyConnectionRefusedError:
            displayMessagelist(generatemesage(QObject::tr("Erreur: Impossible de contacter le serveur proxy car la connexion à celui-ci a été refusée."),tr("System Tchat Bot")));
            changestateconnectbutton(true);
        break;

        case QAbstractSocket::ProxyConnectionClosedError:
            displayMessagelist(generatemesage(QObject::tr("Erreur: La connexion au serveur proxy a été fermée de manière inattendue."),tr("System Tchat Bot")));
            changestateconnectbutton(true);
        break;

        case QAbstractSocket::ProxyConnectionTimeoutError:
            displayMessagelist(generatemesage(QObject::tr("Erreur: La connexion au serveur proxy a expiré ou le serveur proxy a cessé de répondre lors de la phase d'authentification."),tr("System Tchat Bot")));
            changestateconnectbutton(true);
        break;

        case QAbstractSocket::ProxyNotFoundError:
            displayMessagelist(generatemesage(QObject::tr("Erreur: Le proxy est introuvable."),tr("System Tchat Bot")));
            changestateconnectbutton(true);
        break;

        case QAbstractSocket::ProxyProtocolError:
            displayMessagelist(generatemesage(QObject::tr("Erreur: La connexion avec le serveur proxy a échouée, car la réponse de celui-ci n'a pas pu être comprise."),tr("System Tchat Bot")));
            changestateconnectbutton(true);
        break;

        case QAbstractSocket::OperationError:
            displayMessagelist(generatemesage(QObject::tr("Erreur: Une opération a été tentée alors que le socket était dans un état qui ne l'autorisait pas."),tr("System Tchat Bot")));
            changestateconnectbutton(true);
        break;

        case QAbstractSocket::TemporaryError:
            displayMessagelist(generatemesage(QObject::tr("Erreur: Une erreur temporaire s'est produite (Réssayer dans un moment.)."),tr("System Tchat Bot")));
            changestateconnectbutton(true);
        break;

        case QAbstractSocket::UnknownSocketError:
            displayMessagelist(generatemesage(QObject::tr("Erreur: Une erreur non identifiée s'est produite."),tr("System Tchat Bot")));
            changestateconnectbutton(true);
        break;

    default:
            displayMessagelist(generatemesage(QObject::tr("Erreur : ") + socket->errorString(),tr("System Tchat Bot")));
            changestateconnectbutton(true);
        break;
    }
}
// optionelle
void client::sentdatamap(const QMap<QString,QString> sendmap)
{
    QByteArray paquet;
    QDataStream out(&paquet, QIODevice::WriteOnly);

    out << (quint16) 0;
    out << sendmap;
    out.device()->seek(0);
    out << (quint16) (paquet.size() - sizeof(quint16));
    socket->write(paquet); // On envoie le paquet
}
void client::sentdatamap(const QString type){
    QMap<QString,QString> sendmap;
    sendmap["type"]=type;
    sendmap["pseudo"]=encryptioncesar->chiffre(psedo);
    sendmap["version"]=QCoreApplication::applicationVersion();
    sendmap["secondofsending"]=QDateTime::currentDateTime().toString("ss");;
    sendmap["minuteofsending"]=QDateTime::currentDateTime().toString("mm");;
    sendmap["sendingtime"]=QDateTime::currentDateTime().toString("hh");
    sendmap["sendingdate"]=QDateTime::currentDateTime().toString("d");
    sendmap["shippingday"]=QDateTime::currentDateTime().toString("dddd");
    sendmap["shippingmonth"]=QDateTime::currentDateTime().toString("MMMM");
    sendmap["shippingyears"]=QDateTime::currentDateTime().toString("yyyy");
    sentdatamap(sendmap);

}
void client::sentdatamap(const QString type, QString message, QString pseudo, QDateTime seconde, QDateTime minute, QDateTime heures, QDateTime NoJour, QDate jour){
    QMap<QString,QString> sendmap;
    sendmap["type"]=type;
    sendmap["message"]=encryptioncesar->chiffre(message);
    sendmap["pseudo"]=encryptioncesar->chiffre(pseudo);
    sendmap["version"]=QCoreApplication::applicationVersion();;
    sendmap["secondofsending"]=seconde.toString();
    sendmap["minuteofsending"]=minute.toString();
    sendmap["sendingtime"]=heures.toString();
    sendmap["sendingdate"]=NoJour.toString();
    sendmap["shippingday"]=jour.toString();
    sentdatamap(sendmap);
}
void client::sentdatamap(const QString type, QString message, QString pseudo){
    QMap<QString,QString> sendmap;
    sendmap["type"]=type;
    sendmap["message"]=encryptioncesar->chiffre(message);
    sendmap["pseudo"]=encryptioncesar->chiffre(pseudo);
    sendmap["version"]=QCoreApplication::applicationVersion();;
    sendmap["secondofsending"]=QDateTime::currentDateTime().toString("ss");;
    sendmap["minuteofsending"]=QDateTime::currentDateTime().toString("mm");;
    sendmap["sendingtime"]=QDateTime::currentDateTime().toString("hh");
    sendmap["sendingdate"]=QDateTime::currentDateTime().toString("d");
    sendmap["shippingday"]=QDateTime::currentDateTime().toString("dddd");
    sendmap["shippingmonth"]=QDateTime::currentDateTime().toString("MMMM");
    sendmap["shippingyears"]=QDateTime::currentDateTime().toString("yyyy");
    sentdatamap(sendmap);
}
void client::sentdatamap(const QString type, QString message){
    QMap<QString,QString> sendmap;
    sendmap["type"]=type;
    sendmap["message"]=encryptioncesar->chiffre(message);
    sendmap["pseudo"]=encryptioncesar->chiffre(psedo);
    sendmap["version"]=QCoreApplication::applicationVersion();;
    sendmap["secondofsending"]=QDateTime::currentDateTime().toString("ss");;
    sendmap["minuteofsending"]=QDateTime::currentDateTime().toString("mm");;
    sendmap["sendingtime"]=QDateTime::currentDateTime().toString("hh");
    sendmap["sendingdate"]=QDateTime::currentDateTime().toString("d");
    sendmap["shippingday"]=QDateTime::currentDateTime().toString("dddd");
    sendmap["shippingmonth"]=QDateTime::currentDateTime().toString("MMMM");
    sendmap["shippingyears"]=QDateTime::currentDateTime().toString("yyyy");
    sentdatamap(sendmap);
}
void client::sentcommande(const QString commande){
    QMap<QString,QString> sendmap;
    sendmap["type"]="cmd";
    sendmap["message"]=commande;
    sendmap["pseudo"]=encryptioncesar->chiffre(psedo);
    sendmap["version"]=QCoreApplication::applicationVersion();;
    sendmap["secondofsending"]=QDateTime::currentDateTime().toString("ss");;
    sendmap["minuteofsending"]=QDateTime::currentDateTime().toString("mm");;
    sendmap["sendingtime"]=QDateTime::currentDateTime().toString("hh");
    sendmap["sendingdate"]=QDateTime::currentDateTime().toString("d");
    sendmap["shippingday"]=QDateTime::currentDateTime().toString("dddd");
    sendmap["shippingmonth"]=QDateTime::currentDateTime().toString("MMMM");
    sendmap["shippingyears"]=QDateTime::currentDateTime().toString("yyyy");
    sentdatamap(sendmap);
}
void client::sentcommande(const QString commande, QString arg){
    QMap<QString,QString> sendmap;
    sendmap["type"]="cmd";
    sendmap["message"]=commande;
    sendmap["arg"]=encryptioncesar->chiffre(arg);
    sendmap["pseudo"]=encryptioncesar->chiffre(psedo);
    sendmap["version"]=QCoreApplication::applicationVersion();;
    sendmap["secondofsending"]=QDateTime::currentDateTime().toString("ss");;
    sendmap["minuteofsending"]=QDateTime::currentDateTime().toString("m");;
    sendmap["sendingtime"]=QDateTime::currentDateTime().toString("hh");
    sendmap["sendingdate"]=QDateTime::currentDateTime().toString("d");
    sendmap["shippingday"]=QDateTime::currentDateTime().toString("ddd");
    sendmap["shippingmonth"]=QDateTime::currentDateTime().toString("MMMM");
    sendmap["shippingyears"]=QDateTime::currentDateTime().toString("yyyy");;
    sentdatamap(sendmap);
}
void client::datareceived()
{
    QDataStream in(socket);
    while (1) {
        if (messagesize == 0)
        {
            if (socket->bytesAvailable() < (int)sizeof(quint16))
                 return;
            in >> messagesize;
        }
        if (socket->bytesAvailable() < messagesize)
            return;
        // Si on arrive jusqu'? cette ligne, on peut récupérer le message entier
        QMap<QString,QString> messageRecu;
        in >> messageRecu;
        processthemessage(messageRecu);
        // On remet la taille du message ? 0 pour pouvoir recevoir de futurs messages
        messagesize = 0;
    }
}
void client::processthemessage(QMap<QString,QString> message)
{
    if(message["type"]=="cmd"){
        message["pseudo"]=encryptioncesar->deChiffre(message["pseudo"]);
        message["arg"]=encryptioncesar->deChiffre(message["arg"]);
        processcomand(message);
    }else if(message["type"]=="msg"){
        message["pseudo"]=encryptioncesar->deChiffre(message["pseudo"]);
        message["message"]=encryptioncesar->deChiffre(message["message"]);
        displayMessagelist(generatemesage(message));
    }else if(message["type"]=="connection"){
        newclient(encryptioncesar->deChiffre(message["pseudo"]));
        ++nbuser;
        if(nbuser==10){
            settings->setValue("succes/10userSimultaneously", true);
        }else if(nbuser==30){
            settings->setValue("succes/30userSimultaneously", true);
        }else if(nbuser==100){
            settings->setValue("succes/100userSimultaneously", true);
        }
    }else{
        QMessageBox::critical(nullptr,tr("Erreur"), tr("Un paquet a été recu mais l'indentificateur : ") + message["type"] + tr(" est inconnu."));
    }

}
void client::processcomand(QMap<QString, QString> commend)
{
    if (commend["message"] == "pseudo?"){
        sentcommande("pseudo_", psedo);
    }else if (commend["message"]=="version?"){
        sentcommande("version",QCoreApplication::applicationVersion());
    }else if (commend["message"]=="pseudoanonymousinvalid"){
        QMessageBox::critical(nullptr, tr("Erreur"), tr("Il vous faut un pseudo pour vous connecter (Anonymous est interdit)."));
    }else if(commend["message"]=="pseudoalreadyuse"){
        QMessageBox::critical(nullptr, tr("Erreur"), tr("Un autre client porte déjà ce pseudo. Veuillez changer de pseudo pour vous connecter."));
    }else if(commend["message"]=="pseudoresembling"){
        QMessageBox::critical(nullptr, tr("Erreur"), tr("Un autre client porte déjà un pseudo ressemblant. Veuillez changer de pseudo pour vous connecter."));
    }else if (commend["message"]=="update_") {
        displayMessagelist(commend["arg"]);
    }else if (commend["message"]=="isconnected"){
        newclient(commend["arg"]);
        ++nbuser;
        if(nbuser==10){
            settings->setValue("succes/10userSimultaneously", true);
        }else if(nbuser==30){
            settings->setValue("succes/30userSimultaneously", true);
        }else if(nbuser==100){
            settings->setValue("succes/100userSimultaneously", true);
        }
    }else if(commend["message"]=="disconnected"){
        deleteclient(commend["arg"]);
        --nbuser;
    }else{
        QMessageBox::critical(nullptr, tr("Erreur"), tr("Un paquet de comande a été reçu mais la commande est incomprise. ")+commend["message"]);
    }
}
QString client::generatedate()
{
    QString heures = QDateTime::currentDateTime().toString("hh:mm:ss");
    QString Date = QDateTime::currentDateTime().toString("ddd dd MMMM yyyy");
    QDateTime::fromString(heures, "hh:mm:ss");
    return ("<span style=\"font-size: 10px\">"  +   tr("le ")    +   Date    +"</span> <span style=\"font-size: 10px\">"+   tr("à") +   heures +"</span><br/>");
}
QString client::generatedate(QMap<QString, QString> date)
{
        return("<span style=\"font-size: 10px\">"+ tr(" Le ","dans la generationde message")+date["shippingday"]+" "+date["sendingdate"]+" "+date["shippingmonth"]+" "+date["shippingyears"] +"</span> <span style=\"font-size: 10px\">"+tr( " à ","dans la generationde message")+date["sendingtime"]+" : "+date["minuteofsending"]+tr(" </span><br/>"));
}
QString client::generatemesage(QString message, QString pseudo)
{
    if(pseudo == "" ||pseudo == " "){
        pseudo = "anonymous";
    }
    return(tr("<span style=\"font-size: 12px; font-weight: bold;\">")+pseudo+tr("</span>")+generatedate()+tr("<span style=\"font-size: 14px; \">")+message+tr("</span><br/><br/>"));
}
QString client::generatemesage(QMap<QString, QString> message){
    if(message["pseudo"] == "" ||message["pseudo"] == " "){
        message["pseudo"] = "anonymous";
    }
    return(tr("<span style=\"font-size: 12px; font-weight: bold;\">")+message["pseudo"]+tr("</span>")+generatedate(message)+tr("<span style=\"font-size: 14px; \">")+message["message"]+tr("</span><br/><br/>"));
}

