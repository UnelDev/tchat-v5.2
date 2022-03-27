/*By Unel at 30/12/21
For Ananta Project*/
#include "client.h"
client::client()
{
    //lib externe
    QCoreApplication::setOrganizationName("ananta system");
    QCoreApplication::setOrganizationDomain("https://anantasystem.com/");
    QCoreApplication::setApplicationName("tchat");
    QCoreApplication::setApplicationVersion("5.2");
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
client::~client(){
    delete settings;
    delete socket;
    delete encryptioncesar;
}
//emeteur
void client::deleteclient(QString nameOfClient){ emit client::remouveClient(nameOfClient);}
void client::displayMessagelist(QString newMessage){ emit client::display(newMessage); }
void client::DisplayFile(const QString comment, const QString NameOfFile){ emit client::newFileAndComent(comment,NameOfFile);}
void client::changestateconnectbutton(bool state){ emit client::changestateconnect(state); }
void client::newclient(QString newClientName){ emit client::newuser(newClientName); }
void client::displayconnectlabel(QString newText){ emit client::changeTextConnect(newText);}
void client::externalCmd(const QString cmd){ emit client::externalOrder(cmd);}
//deccesseurs
void client::sendmessage(QString message){ senddatamap("msg",message); }

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
    emit client::isConnected();
    QString textmessage = generatemesage(tr("Connexion établie!"), tr("Tchat Bot"));
    senddatamap("connection");
    displayMessagelist(textmessage);
    changestateconnectbutton(true);
    displayconnectlabel("<font color=\"#70AD47\">"+tr("Connecté","lors de la connexion a un serveur")+"</font>");
}
void client::disconnect()
{
    emit client::isDesconected();
    QString textmessage = generatemesage(tr("Déconnecté du serveur"),tr("Tchat Bot"));
    displayconnectlabel("<font color=\"#ff0000\">"+tr("Déconnecté", "lors de la déconnexion a un serveur")+"</font>");
    displayMessagelist(textmessage);
    changestateconnectbutton(true);
}
void client::senddatamap(const QMap<QString,QVariant> sendmap)
{
    QByteArray paquet;
    QDataStream out(&paquet, QIODevice::WriteOnly);

    out << (int) 0;
    out << sendmap;
    out.device()->seek(0);
    out << (int) (paquet.size() - sizeof(int));
    int sentzise = socket->write(paquet); // On envoie le paquet
    if(sentzise == -1){
      QMessageBox::critical(nullptr, tr("Erreur d'envoie","quand un fichier est trop lourd"), tr("le packet n'a pas pue etre corectemment ecrit dans le socket, le fichier doit etre trop lourd","quand un fichier est trop lourd"));
    }
}
void client::senddatamap(const QString type){
    QMap<QString,QVariant> sendmap;
    sendmap["type"]=type;
    sendmap["pseudo"]=encryptioncesar->chiffre(psedo);
    sendmap["version"]=QCoreApplication::applicationVersion();
    sendmap["time"]=QDateTime::currentDateTime();
    senddatamap(sendmap);

}
void client::senddatamap(const QString type, QString message, QString pseudo, QDateTime seconde, QDateTime minute, QDateTime heures, QDateTime NoJour, QDate jour){
    QMap<QString,QVariant> sendmap;
    sendmap["type"]=type;
    sendmap["message"]=encryptioncesar->chiffre(message);
    sendmap["pseudo"]=encryptioncesar->chiffre(pseudo);
    sendmap["version"]=QCoreApplication::applicationVersion();
    sendmap["time"]=QDateTime::currentDateTime();
    senddatamap(sendmap);
}
void client::senddatamap(const QString type, QString message, QString pseudo){
    QMap<QString,QVariant> sendmap;
    sendmap["type"]=type;
    sendmap["message"]=encryptioncesar->chiffre(message);
    sendmap["pseudo"]=encryptioncesar->chiffre(pseudo);
    sendmap["version"]=QCoreApplication::applicationVersion();
    sendmap["time"]=QDateTime::currentDateTime();
    senddatamap(sendmap);
}
void client::senddatamap(const QString type, QString message){
    QMap<QString,QVariant> sendmap;
    sendmap["type"]=type;
    sendmap["message"]=encryptioncesar->chiffre(message);
    sendmap["pseudo"]=encryptioncesar->chiffre(psedo);
    sendmap["version"]=QCoreApplication::applicationVersion();
    sendmap["time"]=QDateTime::currentDateTime();
    senddatamap(sendmap);
}

void client::sendcommande(const QString commande, const QString arg, const QString arg2){
    QMap<QString,QVariant> sendmap;
    sendmap["type"]="cmd";
    sendmap["message"]=commande;
    sendmap["arg"]=encryptioncesar->chiffre(arg);
    sendmap["arg2"]=encryptioncesar->chiffre(arg2);
    sendmap["pseudo"]=encryptioncesar->chiffre(psedo);
    sendmap["version"]=QCoreApplication::applicationVersion();
    sendmap["time"]=QDateTime::currentDateTime();
    senddatamap(sendmap);
}
void client::sendFile(const QString message, const QString path, const QString NameOfFile){
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly)){ return; }//on test louverture du ficher
    QByteArray ba = file.readAll();
    QMap<QString,QVariant> sendmap;//creation du descritif
    sendmap["type"]="attachment";
    sendmap["message"]=encryptioncesar->chiffre(message);
    sendmap["nameOfFile"]=encryptioncesar->chiffre(NameOfFile);
    sendmap["pseudo"]=encryptioncesar->chiffre(psedo);
    sendmap["version"]=QCoreApplication::applicationVersion();;
    sendmap["time"]=QDateTime::currentDateTime();
    sendmap["attachment"]=ba;
    //senddatamap(sendmap);
    QByteArray paquet;
    QDataStream out(&paquet, QIODevice::WriteOnly);

    out << (int) 0;
    out << sendmap;
    out.device()->seek(0);
    out << (int) (paquet.size() - sizeof(int));
    int sentzise = socket->write(paquet); // On envoie le paquet
    if(sentzise == -1){
      QMessageBox::critical(nullptr, tr("Erreur d'envoie","quand un fichier est trop lourd"), tr("le packet n'a pas pue etre corectemment ecrit dans le socket, le fichier doit etre trop lourd","quand un fichier est trop lourd"));
    }
}
QString client::getPsedo(){
    return psedo;
}
void client::editPsedo(QString newpsedo){
    psedo=newpsedo;
}
void client::datareceived()
{
    QDataStream in(socket);
    while (1) {
        if (messagesize == 0)
        {
            if (socket->bytesAvailable() < (int)sizeof(int))
                 return;
            in >> messagesize;
        }
        if (socket->bytesAvailable() < messagesize)
            return;
        // Si on arrive jusqu'? cette ligne, on peut récupérer le message entier
        QMap<QString,QVariant> messageRecu;
        in >> messageRecu;
        processthemessage(messageRecu);
        // On remet la taille du message ? 0 pour pouvoir recevoir de futurs messages
        messagesize = 0;
    }
}
void client::processthemessage(QMap<QString,QVariant> message)
{
    if(message["type"]=="cmd"){
        message["pseudo"]=encryptioncesar->deChiffre(message["pseudo"].toString());
        message["arg"]=encryptioncesar->deChiffre(message["arg"].toString());
        message["arg2"]=encryptioncesar->deChiffre(message["arg2"].toString());
        processcomand(message);
    }else if(message["type"]=="msg"){
        message["pseudo"]=encryptioncesar->deChiffre(message["pseudo"].toString());
        message["message"]=encryptioncesar->deChiffre(message["message"].toString());
        displayMessagelist(generatemesage(message));
    }else if(message["type"]=="connection"){
        newclient(encryptioncesar->deChiffre(message["pseudo"].toString()));
        ++nbuser;
        if(nbuser==10){
            settings->setValue("succes/10userSimultaneously", true);
        }else if(nbuser==30){
            settings->setValue("succes/30userSimultaneously", true);
        }else if(nbuser==100){
            settings->setValue("succes/100userSimultaneously", true);
        }
    }else if(message["type"]=="attachment"){
        message["pseudo"]=encryptioncesar->deChiffre(message["pseudo"].toString());
        message["message"]=encryptioncesar->deChiffre(message["message"].toString());
        message["nameOfFile"]=encryptioncesar->deChiffre(message["nameOfFile"].toString());

        QDir dir;
        dir.mkpath("temp");//on crée le repertoir
        QFile file("temp/"+message["nameOfFile"].toString());
        if (!file.fileName().isEmpty()) {// Check that the path is valid
            file.open(QIODevice::WriteOnly);
            QByteArray ba = message["attachment"].toByteArray();//on crée le flux
           file.write(ba);
           qDebug()<<file;
           file.close();// Close the file
        }

        DisplayFile(generatemesage(message),message["nameOfFile"].toString());
        sendcommande("file?",message["nameOfFile"].toString());
    }else if(message["type"]=="attachmentFile"){
         message["pseudo"]=encryptioncesar->deChiffre(message["pseudo"].toString());
        message["message"]=encryptioncesar->deChiffre(message["message"].toString());
        message["nameOfFile"]=encryptioncesar->deChiffre(message["nameOfFile"].toString());
        // Ask the user where he/she wants to save the file
        QDir dir;
        dir.mkpath("temp");//on crée le repertoir
        QFile file("temp/"+message["nameOfFile"].toString());
        if (!file.fileName().isEmpty()) {// Check that the path is valid
            file.open(QIODevice::WriteOnly);
            QByteArray ba = message["attachment"].toByteArray();//on crée le flux
           file.write(ba);
           qDebug()<<file;
           file.close();// Close the file
        }
    }else{
        emit externalCommend(message);
    }

}
void client::processcomand(QMap<QString, QVariant> commend)
{
    if (commend["message"] == "pseudo?"){
        sendcommande("pseudo_", psedo);
    }else if (commend["message"]=="version?"){
        sendcommande("version",QCoreApplication::applicationVersion());
    }else if (commend["message"]=="pseudoanonymousinvalid"){
        QMessageBox::critical(nullptr, tr("Erreur"), tr("Il vous faut un pseudo pour vous connecter (Anonymous est interdit)."));
    }else if(commend["message"]=="pseudoalreadyuse"){
        QMessageBox::critical(nullptr, tr("Erreur"), tr("Un autre client porte déjà ce pseudo. Veuillez changer de pseudo pour vous connecter."));
    }else if(commend["message"]=="pseudoresembling"){
        QMessageBox::critical(nullptr, tr("Erreur"), tr("Un autre client porte déjà un pseudo ressemblant. Veuillez changer de pseudo pour vous connecter."));
    }else if (commend["message"]=="update_") {
        displayMessagelist(commend["arg"].toString());
    }else if (commend["message"]=="isconnected"){
        newclient(commend["arg"].toString());
        ++nbuser;
        if(nbuser==10){
            settings->setValue("succes/10userSimultaneously", true);
        }else if(nbuser==30){
            settings->setValue("succes/30userSimultaneously", true);
        }else if(nbuser==100){
            settings->setValue("succes/100userSimultaneously", true);
        }
    }else if (commend["message"]=="clear"){
        externalCmd("clear");
    }else if(commend["message"]=="disconnected"){
        deleteclient(commend["arg"].toString());
        --nbuser;
    }else if(commend["message"]=="changePsedo"){
        displayMessagelist(commend["arg"].toString()+ tr(" à changer son pseudo en : ","lors d'un changement de nom utilisateur")+commend["arg2"].toString());
        deleteclient(commend["arg"].toString());
        newclient(commend["arg2"].toString());
    }else if(commend["message"]=="silentNameChange"){
        deleteclient(commend["arg"].toString());
        newclient(commend["arg2"].toString());
    }else if(commend["message"]=="pong"){
        QTime actualTime = QTime::currentTime();
        const int time = commend["time"].toDateTime().time().msecsTo(actualTime);
        QList< QList<QString>>liste;
        const QList<QString>one{tr("ascendant 🔼"),commend["arg"].toString()+" ms"};
        liste.push_back(one);
        const QList<QString>two{tr("descendant 🔽"),QString::number(time)+" ms"};
        liste.push_back(two);

        emit client::newEmbed(tr("latence"),tr("affiche la latence avec le serveur"),liste);
    }else if(commend["message"]=="ReInfo"){
        QTime actualTime = QTime::currentTime();
        const int time = commend["time"].toDateTime().time().msecsTo(actualTime);
        QList< QList<QString>>liste;
        const QList<QString>one{tr("ascendant 🔼"),commend["arg"].toString()+" ms"};
        liste.push_back(one);
        const QList<QString>two{tr("traitement serveur 🔁"),commend["arg2"].toString()+" ms"};
        liste.push_back(two);
        const QList<QString>three{tr("descendant 🔽"),QString::number(time)+" ms"};
        liste.push_back(three);
        const int totalTime{commend["arg"].toInt()+commend["arg2"].toInt()+time};//total des ping
        const QList<QString>four{tr("total ⏱️"),QString::number(totalTime)+" ms"};
        liste.push_back(four);
        const QList<QString>five{tr("nombre de clients 😏"),commend["arg3"].toString()};
        liste.push_back(five);
        emit client::newEmbed(tr("information de connexion"),tr("affiche les informationde connexion de serveur"),liste);
    }else{
        QMessageBox::critical(nullptr, tr("Erreur"), tr("Un paquet de commande a été reçu mais la commande est incomprise. ")+commend["message"].toString());
    }
}
QString client::generatedate()
{
    QString heures = QDateTime::currentDateTime().toString("hh:mm:ss");
    QString Date = QDateTime::currentDateTime().toString("ddd dd MMMM yyyy");
    QDateTime::fromString(heures, "hh:mm:ss");
    return ("<span style=\"font-size: 12px\">"  +   tr(" le ")    +   Date    +"</span> <span style=\"font-size: 10px\">"+   tr("à") +   heures +"</span><br/>");
}
QString client::generatedate(QMap<QString, QVariant> message)
{
    auto date = message["time"].toDateTime().date();
    return("<span style=\"font-size: 12px\">"+ tr(" Le ","dans la generationde message")+ date.toString("dddd") +" "+date.toString("d")+" "+date.toString("MMMM")+" "+date.toString("yyyy") +"</span> <span style=\"font-size: 10px\">"+tr( " à ","dans la generationde message")+date.toString("hh")+" : "+date.toString("mm")+tr(" </span><br/>"));
}
QString client::generatemesage(QString message, QString pseudo)
{
    if(pseudo == "" ||pseudo == " "){
        pseudo = "anonymous";
    }
    return(tr("<span style=\"font-size: 12px; font-weight: bold;\">")+pseudo+tr("</span>")+generatedate()+tr("<span style=\"font-size: 14px; \">")+message+tr("</span>"));
}
QString client::generatemesage(QMap<QString, QVariant> message){
    if(message["pseudo"] == "" ||message["pseudo"] == " "){
        message["pseudo"] = "anonymous";
    }
    return(tr("<span style=\"font-size: 12px; font-weight: bold;\">")+message["pseudo"].toString()+tr("</span>")+generatedate(message)+tr("<span style=\"font-size: 14px; \">")+message["message"].toString()+tr("</span>"));
}
void client::socketerror(QAbstractSocket::SocketError erreur)
{
    emit client::isConnected();
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
