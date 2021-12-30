/*By Unel at 30/12/21
For Ananta Project*/
#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent),
    parametres(this),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    QCoreApplication::setOrganizationName("ananta system");
    QCoreApplication::setOrganizationDomain("https://anantasystem.com/");
    QCoreApplication::setApplicationName("tchat");
    QCoreApplication::setApplicationVersion("5.0");

    settings = new QSettings("settings.ini", QSettings::IniFormat);
    if(!settings->contains("succes/succes")){
        settings->setValue("succes/succes",true);
    }if(!settings->contains("succes/nbmessage")){
        settings->setValue("succes/nbmessage",0);
    }if(!settings->contains("settings/SaveMessage")){
        settings->setValue("settings/SaveMessage",true);
    }if(!settings->contains("settings/visualNotification")){
        settings->setValue("settings/visualNotification",true);
    }if(!settings->contains("settings/SoundNotification")){
        settings->setValue("settings/SoundNotification",true);
    }if(!settings->contains("settings/color")){
        settings->setValue("settings/color","white");
    }if(!settings->contains("settings/path")){
        settings->setValue("settings/path",":/sound/notifdefault.wav");
    }if(!settings->contains("settings/transparency")){
        settings->setValue("settings/transparency",0.5);
    }if(!settings->contains("settings/server/activeTransparnece")){
        settings->setValue("settings/server/activeTransparnece",true);
    }if(!settings->contains("succes/10userSimultaneously")){
        settings->setValue("succes/10userSimultaneously", false);
    }if(!settings->contains("succes/30userSimultaneously")){
        settings->setValue("succes/30userSimultaneously", false);
    }if(!settings->contains("succes/100userSimultaneously")){
        settings->setValue("succes/100userSimultaneously", false);
    }if(!settings->contains("succes/server/nbserveur")){
        settings->setValue("succes/server/nbserveur", 0);
    }if(!settings->contains("succes/10server")){
        settings->setValue("succes/20server", false);
    }if(!settings->contains("settings/high")){
        settings->setValue("settings/level of secure","high");
    }if(!settings->contains("settings/localHost")){
        settings->setValue("settings/level of secure","high");
    }
    //variable complex
    parametre parametres(this);
    encryptioncesar = new cesar(2);
    //fonction pour condenser le constructeur
    autoconnect();//il faut que la focntion se fasse avant le lancement du serveur mais il doit se lancer apres le registre
    startTrayIcon();
    qApp->setPalette(parametres.starttheme());//Sélection de la couleur du theme
    //variable simple
    levelOfSecure=settings->value("settings/level of secure").toString();
    condenser = false;
    //remplissage des information
    QString ip;
    foreach (const QHostAddress &address, QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost))
             ip = (address.toString());
    }
    qDebug() <<ip;
    ui->serveurip->setText(ip);
    //serveur
    server = new serveur();//initialisation du serveur
    //connexion
    connect(server, &serveur::display, this, &Widget::displayMessagelist);
    int port = server->startserveur(ui->serveurport->value());//demarage du serveur
    if (port!=0){
        if (port != ui->serveurport->value()){
            ui->serveurport->setValue(port);
            QMessageBox::information(nullptr,tr("erreur au lancement", "lancemment du serveur"),tr(&"le serveur n'a pa pue etre lancer sur le port demadée il a donc été lancer sur le port : "[port],"lancemment du serveur"));
        }
    }else{
        QMessageBox::information(nullptr,tr("erreur au lancement", "lancemment du serveur"),tr("imposible de lancer le serveur","lancemment du serveur"));
    }

    //client
    clients = new client();
    QObject::connect(clients, &client::display, this, &Widget::displayMessagelist);
    QObject::connect(clients, &client::remouveClient, this, &Widget::deletClient);
    QObject::connect(clients, &client::newuser, this, &Widget::newuser);
    clients->connectto("localhost",ui->serveurport->value(),ui->pseudo->text());

    QPushButton test;

}
Widget::~Widget()
{
    delete ui;
    delete sticon;
    delete stmenu;
    delete server;
    delete settings;
    delete clients;
}
void Widget::autoconnect(){
    QFile fichier(settings->value("launcher/AutoConectServeurPosition").toString()); //on ouvre le fichier de preconexion
    if(fichier.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream flux(&fichier);
        flux.readLine();// sert a sauter une ligne caron ne repli pas lip dans le serveur
        ui->serveurport->setValue(flux.readLine().toInt());
        ui->pseudo->setText(flux.readLine());
    }
    else
    {
        ui->serveurport->setValue(2048);
        QString name = qgetenv("USER");
        if (name.isEmpty())
            name = qgetenv("USERNAME");
        ui->pseudo->setText(name);
    }
}
void Widget::startTrayIcon(){
    sticon = new QSystemTrayIcon(this); // On construit notre icône de notification
    // Création du menu contextuel de notre icône
    stmenu = new QMenu(this);
    QAction* actTexte1 = new QAction(tr("Quitter"),this);
    QAction* condense = new QAction(tr("Condenser la fenêtre"), this);
    connect(qApp, &QGuiApplication::applicationStateChanged, this,  &Widget::changetransparency);
    stmenu->addAction(actTexte1);
    stmenu->addAction(condense);
    condense->setCheckable(true);
    sticon->setContextMenu(stmenu); // On assigne le menu contextuel à l'icône de notification
    QIcon icon(":/image/Ananta.png");
    sticon->setIcon(icon); // On assigne une image à notre icône
    sticon->show(); // On affiche l'icône
    connect(actTexte1, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(condense,&QAction::triggered,this, &Widget::condesed);
}
void Widget::connectClient()
{
    if(ui->pseudo->text()==""||ui->pseudo->text()==" "||ui->pseudo->text()=="anonymous"){
        QMessageBox::critical(this,tr("pseudo invalid"),tr("Vous devez posseder un pseudo (anonymous est interdit)."));
        return;
    }
    clients->connectto(ui->serveurip->text(), ui->serveurport->value(),ui->pseudo->text());
    ui->clientlist->clear();
}
void Widget::newuser(QString name){
    ui->clientlist->addItem(name);
}
void Widget::deletClient(QString nameOfClient){
    if(ui->clientlist->findItems(nameOfClient,Qt::MatchCaseSensitive).isEmpty()){
        ui->clientlist->removeItemWidget(ui->clientlist->findItems(nameOfClient,Qt::MatchCaseSensitive)[1]); //on suprime le nom specifier
        QMessageBox::critical(nullptr, tr("Suppression de client"), tr("Le client vient d'être supprimé."));
    }
}
void Widget::changetransparency(Qt::ApplicationState state){
    if(state == Qt::ApplicationInactive&&condenser==true&&settings->value("settings/client/activeTransparnece").toBool()){
        this->setWindowOpacity(settings->value("settings/transparency").toFloat());
    }else if(state == Qt::ApplicationActive){
        this->setWindowOpacity(1);
    }
}
void Widget::condesed(){
    if (socket->state()){
        if (condenser == false)
        {
            ui->serveurip->setVisible(false);
            ui->pseudo->setVisible(false);
            ui->label_4->setVisible(false);
            ui->label_5->setVisible(false);
            ui->serveurport->setVisible(false);
            ui->clientlist->setVisible(false);
            if(settings->value("settings/client/activeTransparnece").toBool()){
                this->setWindowFlags(Qt::WindowStaysOnTopHint);
            }
            this->show();
            condenser = true;
            resize(610,89);
        }else if (condenser == true){
            //ui->label->setVisible(true);
            ui->serveurip->setVisible(true);
            ui->pseudo->setVisible(true);
            ui->label_4->setVisible(true);
            ui->label_5->setVisible(true);
            ui->serveurport->setVisible(true);
            ui->clientlist->setVisible(true);
            this->setWindowFlags(Qt::Window);
            condenser = false;
            this->show();
        }else{
            QMessageBox::critical(this,tr("bool condesed"),tr("erreur un bool ne pet pas avoir tois etat signalez le dans: parametre  puis discord"));
        }
    }else{
        QMessageBox::information(this,tr("passage en mode condensée"),tr("vous ne pouvez passer l'app en mode condensée que une fois connecter"));

    }
}
void helpcondesed(){
     QMessageBox::information(nullptr,QObject::tr("passage en mode condensée"),QObject::tr("vous ne pouvez passer l'app en mode condensée que une fois connecter"));
}
void Widget::displayMessagelist(QString message)
{
    if(settings->value("settings/SoundNotification").toBool())
    {
        if(!QApplication::activeWindow()){
            QApplication::beep();
        }
        /*QMediaPlayer player;
        connect(&player, QOverload<QMediaPlayer::Error>::of(&QMediaPlayer::error),
            [=](QMediaPlayer::Error error){ errorNotif(error); });
        player.setMedia(QUrl("C:\\Users\\eneep\\Desktop\\VEHCar_Voiture demarrage et depart (ID 0189)_LS.wav"));
        player.setVolume(100);
        player.play();*/
    }
    if(settings->value("settings/visualNotification").toBool())
    {
        if(!QApplication::activeWindow()){
            auto text = QTextDocumentFragment::fromHtml(message);
            sticon->showMessage("",text.toPlainText(),QSystemTrayIcon::Information,2000);
        }
        QApplication::alert(this);
    }
    ui->messagelist->append(message);
}
QString Widget::returnpseudo()
{
    return ui->pseudo->text();
}
void Widget::processechatbot(QString command)
{
    srand (time(NULL));
   //reponse pré faite
   if (command==tr("bonjour")||command==tr("salut")||command==tr("hello")){//posibilier de question
       int random = rand() % 5 + 1;//on fait l'aleatoire
       if(random == 1){
           ui->messagelist->append(generatemesage(tr("Bonjour") + ui->pseudo->text()+".",tr("Tchat Bot")));
       }else if(random == 2){
           ui->messagelist->append(generatemesage(tr("Salut") + ui->pseudo->text()+".",tr("Tchat Bot")));
       }else if(random == 3){
           ui->messagelist->append(generatemesage(tr("Salut🖖") + ui->pseudo->text()+".",tr("Tchat Bot")));
       }else if(random == 4){
           ui->messagelist->append(generatemesage(tr("Hello") + ui->pseudo->text()+".",tr("Tchat Bot")));
       }else if(random == 5){
           ui->messagelist->append(generatemesage(tr("Hello👋") + ui->pseudo->text()+".",tr("Tchat Bot")));
       }
   }else if (command==tr("comment t'apelle tu")||command==tr("quel est ton nom")){
       int random = rand() % 2 + 1;
       if(random == 1){
           ui->messagelist->append(generatemesage(tr("Tu peux m'appeller Tchat Bot."),tr("Tchat Bot")));
       }else if(random == 2){
           ui->messagelist->append(generatemesage(tr("Tu peux m'appeller Tchat Bot 😊."),tr("Tchat Bot")));
       }
   }else if (command==tr("qui est tu")){
       ui->messagelist->append(generatemesage(tr("Je suis le Tchat Bot crée par les développeurs de Ananta System, je suis encore très inachevé."),tr("Tchat Bot")));
   }else if (command=="clear"){
       ui->messagelist->clear();
   }else if (command=="actualise"||command=="update"){
        clients->sentcommande("updating");
   }else if (command==tr("merci")){
       int random = rand() % 7 + 1;
       if(random == 1){
           ui->messagelist->append(generatemesage(tr("De rien 😀"),tr("Tchat Bot")));
       }else if(random == 2){
           ui->messagelist->append(generatemesage(tr("Tout le plaisir est pour moi 😀"),tr("Tchat Bot")));
       }else if(random == 3){
           ui->messagelist->append(generatemesage(tr("Tout le plaisir est pour moi!"),tr("Tchat Bot")));
       }else if(random == 3){
           ui->messagelist->append(generatemesage(tr("De rien !"),tr("Tchat Bot")));
       }else if(random == 4){
           ui->messagelist->append(generatemesage(tr("Mais je suis là pour ça bien sûr 😀"),tr("Tchat Bot")));
       }else if(random == 5){
           ui->messagelist->append(generatemesage(tr("Mais je suis là pour ça bien sûr !"),tr("Tchat Bot")));
       }else if (random == 6){
            ui->messagelist->append(generatemesage(tr("Quand tu ne me parle pas je fais que des actions répétitives, recevoir des messages et les afficher😥..."),tr("Tchat Bot")));
       }else if (random == 7){
            ui->messagelist->append(generatemesage(tr("Quand tu ne me parle pas je m'ennuie 😥"),tr("Tchat Bot")));
   }else if (command==tr("condenses")||command==tr("condense")||command==tr("condense menu")){
       condesed();
    }else if (command==tr("comment condenser la fenetre")||command==tr("comment condenser le menu")||command==tr("compacter la fenetre")){
       int random = rand() % 2 + 1;
       if(random == 1){
           displayMessagelist(generatemesage(tr("Il suffit de taper la commande /condense", "Attention bien taper la même commande!"),tr("Tchat Bot")));
       }else if(random == 2){
           ui->messagelist->append(generatemesage(tr("Tu peux faire clique droit sur l'icône en bas à droite dans ta barre des tâches -> Condenser la fenêtre"),tr("Tchat Bot")));
       }
   }
   }else{
      displayMessagelist(generatemesage(tr("Je suis desolé, mais je n'ai pas compris votre demande, vérifiez l'orthographe."),tr("Tchat Bot")));
  }
}
void Widget::on_pseudo_editingFinished()
{
    clients->sentcommande("change_psedo",ui->pseudo->text());
}
QString Widget::generatemesage(QString message, QString pseudo)
{
    if(pseudo == "" ||pseudo == " "){
        pseudo = "anonymous";
    }
    return(tr("<span style=\"font-size: 12px; font-weight: bold;\">")+pseudo+tr("</span>")+generatedate()+tr("<span style=\"font-size: 14px; \">")+message+tr("</span><br/><br/>"));
}
QString Widget::generatedate()
{
    QString heures = QDateTime::currentDateTime().toString("hh:mm:ss");
    QString Date = QDateTime::currentDateTime().toString("ddd dd MMMM yyyy");
    QDateTime::fromString(heures, "hh:mm:ss");
    return ("<span style=\"font-size: 10px\">"  +   tr("le ")    +   Date    +"</span> <span style=\"font-size: 10px\">"+   tr("à") +   heures +"</span><br/>");
}
void Widget::on_sentbutton_clicked()
{
    QString message = ui->mesage->text(); // si le if prend trop de temps l'utilisateur ne pouras pas modifier son message
    QString msg = message;
    if(message==""){
        QMessageBox::information(this,tr("Erreur passive: Securitée anti-DDOS"),tr("Vous ne pouvez pas envoyer un message vide."));
        return;
    }
    if(settings->value("succes/succes").toBool()==true){
        settings->setValue("succes/nbmessage",settings->value("succes/nbmessage").toInt()+1);
    }
    //suppression des formule de politesse des point et des majuscule
    message = message.toLower();
    if (message.contains(tr("stp","diminutif de s'il te plait")))
        message = message.remove(tr("stp","diminutif de s'il te plait"));
    if (message.contains(tr("s'il te plait")))
        message = message.remove(tr("s'il te plait"));
    if (message.contains("?"))
        message = message.remove("?");
    if (message.contains("."))
        message = message.remove(".");
    if (message.contains("!"))
        message = message.remove("!");
    if (message.contains("@"))
    message = message.remove("@");
    if(message.startsWith("/")){
        message = message.remove("/");
        processechatbot(message);
    }else if(message.startsWith(tr("tchat bot"))){
        message.remove(tr("tchat bot"));
        processechatbot(message);
    }else if(message.startsWith(tr("ananta system"))){
        message.remove(tr("ananta system"));
        processechatbot(message);
    }else if(message.startsWith(tr("ananta system"))){
        message.remove(tr("ananta system"));
       processechatbot(message);
    }else{
        clients->sendmessage(msg);
    }
    ui->mesage->clear();
}
void Widget::on_parametrebutton_clicked()
{
    parametres.show();
}

