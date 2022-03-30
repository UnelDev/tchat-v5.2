#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent),
    parametres(this),
    ui(new Ui::Widget)
{
    //lib externe
    ui->setupUi(this);
    this->setWindowIcon(QIcon(QPixmap(":/image/resource/image/Ananta.png").scaled(QSize(128, 128), Qt::KeepAspectRatio, Qt::SmoothTransformation)));//sinon sur linux ca carsh
    ui->erorLabel->setVisible(false);
    QCoreApplication::setOrganizationName("ananta system");
    QCoreApplication::setOrganizationDomain("https://anantasystem.com/");
    QCoreApplication::setApplicationName("tchat");
    QCoreApplication::setApplicationVersion("5.2");
    //registre et verification
    settings = new QSettings("settings.ini", QSettings::IniFormat);
    if(!settings->contains("succes/nbmessage")){
        settings->setValue("succes/nbmessage",0);
    }if(!settings->contains("settings/SaveMessage")){
        settings->setValue("settings/SaveMessage",true);
    }if(!settings->contains("settings/visualNotification")){
        settings->setValue("settings/visualNotification",true);
    }if(!settings->contains("settings/SoundNotification")){
        settings->setValue("settings/SoundNotification",true);
    }if(!settings->contains("settings/transparencyIsActived")){
        settings->setValue("settings/transparencyIsActived", false);
    }if(!settings->contains("settings/color")){
        settings->setValue("settings/color","white");
    }if(!settings->contains("sound/path")){
        settings->setValue("sound/path","qrc:/sound/notifdefault.wav");
    }if(!settings->contains("settings/transparency")){
        settings->setValue("settings/transparency",0.5);
    }if(!settings->contains("settings/transparencyIsActived")){
        settings->setValue("settings/transparencyIsActived",true);
    }if(!settings->contains("succes/10userSimultaneously")){
        settings->setValue("succes/10userSimultaneously", false);
    }if(!settings->contains("succes/30userSimultaneously")){
        settings->setValue("succes/30userSimultaneously", false);
    }if(!settings->contains("succes/100userSimultaneously")){
        settings->setValue("succes/100userSimultaneously", false);
    }if(!settings->contains("succes/server/nbserveur")){
        settings->setValue("succes/server/nbserveur", 0);
    }if(!settings->contains("succes/server/nbserveur")){
        settings->setValue("succes/server/nbserveur", 0);
    }if(!settings->contains("launcher/AutoConectserveurPosition")){
        settings->setValue("launcher/AutoConectserveurPosition","start.temp");
    }if(!settings->contains("settings/encryption")){
        settings->setValue("settings/encryption","low");
    }if(!settings->contains("settings/client/activeTransparnece")){
        settings->setValue("settings/client/activeTransparnece",true);
    }
    //variable complex
   clients = new client();
   parametre parametres(this);
   condenser = false;
   //variable
   encryption = settings->value("settings/encryption").toString();
   lastMessageIsText=false;
   lastText=0;
   //apel fonction pour racourcire le constructeur
   startTrayIcon();
   {
       QString name = qgetenv("USER");
       if (name.isEmpty())
           name = qgetenv("USERNAME");
       ui->pseudo->setText(name);
   }
   autoconnect();
   //connexion
   QObject::connect(clients, &client::display, this, &Widget::displayMessagelist);
   QObject::connect(clients, &client::changestateconnect, this, &Widget::changestateconnectbutton);
   QObject::connect(clients, &client::changeTextConnect, this, &Widget::displayconnectlabel);
   QObject::connect(clients, &client::remouveClient, this, &Widget::deletClient);
   QObject::connect(clients, &client::newuser, this, &Widget::newuser);
   QObject::connect(clients, &client::externalOrder, this , &Widget::executeCmd);
   QObject::connect(clients, &client::newFileAndComent, this , &Widget::displayFileOnMessageList);
   QObject::connect(clients, &client::newEmbed, this, &Widget::displayEmbed);
   //conexion
   auto *areaScrollBar = ui->scrollArea->verticalScrollBar();  // Je recupère un pointeur sur la ScrollBar
   QObject::connect(areaScrollBar,&QAbstractSlider::rangeChanged, [this]() {//fo nction lambda
          ui->scrollArea->verticalScrollBar()->setValue(ui->scrollArea->verticalScrollBar()->maximum());
       });
}

Widget::~Widget()
{
    delete ui;
    delete sticon;
}
void Widget::displayconnectlabel(QString text)
{
    ui->conectstatelabel->setText(text);
}
void Widget::autoconnect(){
    QFile fichier(settings->value("launcher/AutoConectClientPosition").toString()); //on ouvre le fichier de preconexion
    if(fichier.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream flux(&fichier);
        ui->serveurip->setText(flux.readLine());
        ui->serveurport->setValue(flux.readLine().toInt());
        ui->pseudo->setText(flux.readLine());
        ui->conectbuton->click();
    }else if(!settings->value("settings/erorFileConect").toBool()){
        QMessageBox msgBox;
        msgBox.setText(tr("erreur imposible de lire le fichier de conexion... il faut rentrer les info manullement !"));
        msgBox.setStandardButtons(QMessageBox::Ok |QMessageBox::Help);
        msgBox.setDefaultButton(QMessageBox::Ok);
        QCheckBox *checkBox = new QCheckBox(tr("ne plus aficher"));
        msgBox.setCheckBox(checkBox);
        int ret = msgBox.exec();
        auto check_box_status = checkBox->isChecked();
        settings->setValue("settings/erorFileConect", check_box_status);
        switch (ret) {
          case QMessageBox::Ok:
              //on fait rien
              break;
          case QMessageBox::Help:
            QMessageBox::warning(this,tr("information"),tr("le fichier d'auto conexion a pas été trouvée. vous avez sans doute pas lancée le launcher"));
          default:
              break;//ne rien faire
        }
        ui->serveurport->setValue(2048);
        QString name = qgetenv("USER");
        if (name.isEmpty())
            name = qgetenv("USERNAME");
        ui->pseudo->setText(name);
    }
}
void Widget::startTrayIcon(){
    sticon = new QSystemTrayIcon(this); // on construit notre icône de notification
    // Création du menu contextuel de notre icône
    QMenu* stmenu = new QMenu(this);
    QAction* actTexte1 = new QAction(tr("quiter"),this);
    QAction* condense = new QAction(tr("condenser la fenetre"), this);
    connect(qApp, &QGuiApplication::applicationStateChanged, this,  &Widget::changetransparency);
    stmenu->addAction(actTexte1);
    stmenu->addAction(condense);
    condense->setCheckable(true);
    sticon->setContextMenu(stmenu); // On assigne le menu contextuel à l'icône de notification
    QIcon icon(":/image/resource/image/Ananta.png");
    sticon->setIcon(icon); // On assigne une image à notre icône
    sticon->show(); // On affiche l'icône
    connect(actTexte1, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(condense,&QAction::triggered,this, &Widget::condesed);
}
void Widget::executeCmd(const QString cmd){
    if(cmd=="clear"){
        QLayoutItem* child;
        while((child = ui->messageliste->takeAt(0)) != 0)
        {
           if(child->widget() != 0)
           {
            delete child->widget();
           }
           delete child;
        }
    }
    lastMessageIsText =false;
}
void Widget::changeUserRole(QList<QString>usrRole){
    clients->sendcommande("changeUsrRole",usrRole[0]/*le nom d'utilisateur*/,usrRole[1]/*le role en int*/);
    useraction *usraction = qobject_cast<useraction*>(sender());
    usraction->deleteLater();
}
void Widget::changeUsersaloon(const QString username, const QString room){
    clients->sendcommande("changeUsrRoom",username/*le nom d'utilisateur*/,room/*la salle*/);
    class changeUserRoom *usrRoom = qobject_cast<class changeUserRoom*>(sender());
    usrRoom->deleteLater();
}
void Widget::newuser(QString name){
    listeClient.append(name);
    ui->clientlist->addItem(name);
}
void Widget::deletClient(QString nameOfClient){
    listeClient.removeOne(nameOfClient);
    ui->clientlist->clear();
    ui->clientlist->addItems(listeClient);
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
            ui->label_6->setVisible(false);
            ui->conectstatelabel->setVisible(false);
            ui->conectbuton->setVisible(false);
            ui->serveurport->setVisible(false);
            ui->parametrebuton_2->setVisible(false);
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
            ui->label_6->setVisible(false);
            ui->conectbuton->setVisible(true);
            ui->conectstatelabel->setVisible(false);
            ui->serveurport->setVisible(true);
            ui->parametrebuton_2->setVisible(true);
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
    }
    if(settings->value("settings/visualNotification").toBool())
    {
        if(!QApplication::activeWindow()){
            auto text = QTextDocumentFragment::fromHtml(message);
            sticon->showMessage("",text.toPlainText(),QSystemTrayIcon::Information,2000);
        }
        QApplication::alert(this);
    }
    addmessage(message);
}
void Widget::displayFileOnMessageList(const QString comment, const QString NameOfFile){
    int i = listeOfpPath.indexOf(NameOfFile);
    if (i != -1){
        listeOfpPath.removeAt(i);
        ui->erorLabel->setVisible(false);
    }
    if(settings->value("settings/SoundNotification").toBool())
    {
        if(!QApplication::activeWindow()){
            QApplication::beep();
        }
    }
    if(settings->value("settings/visualNotification").toBool())
    {
        if(!QApplication::activeWindow()){
            auto text = QTextDocumentFragment::fromHtml(comment);
            sticon->showMessage("",text.toPlainText(),QSystemTrayIcon::Information,2000);
        }
        QApplication::alert(this);
    }
    QLabel *label = new QLabel(this);//creation du label pour le message
    label->setText(comment);
    label->setTextInteractionFlags(Qt::TextSelectableByMouse|Qt::TextSelectableByKeyboard|Qt::LinksAccessibleByMouse|Qt::LinksAccessibleByKeyboard);
    ui->messageliste->addWidget(label);

    QPushButton *PushButton = new QPushButton(this);//creation du bouton pour le telechargement
    PushButton->setText(tr("telecharger: ","dans le bouton de telechargement")+NameOfFile);
    connect(PushButton,&QPushButton::clicked,this, &Widget::openfile);

    QVBoxLayout *vlayout = new QVBoxLayout(this);//creation du layout pour metre en forme tout
    vlayout->addWidget(label);
    vlayout->addWidget(PushButton);
    vlayout->setSpacing(2);
    ui->messageliste->addLayout(vlayout);//on lajoute a l'ui

    if(chatBotInteraction::ImageSupported(NameOfFile)){
        QLabel  *label  = new QLabel(this);
        QPixmap *pixmap_img = new QPixmap(QPixmap("temp/"+NameOfFile).scaledToWidth(ui->scrollArea->size().width()-50,Qt::SmoothTransformation));//on redimentionne a la taille de l'afichage
        ui->scrollArea->setMinimumWidth(ui->scrollArea->size().width());
        PushButton->setMaximumWidth(ui->scrollArea->size().width()-50);
        label->setPixmap(*pixmap_img);
        vlayout->addWidget(label);
    }
    else if(chatBotInteraction::textSuported(NameOfFile)){
        const QString file = chatBotInteraction::exctractText("temp/"+NameOfFile,10);
        if(file!=QString::number(-1)){
            QTextBrowser *TextBrowser = new QTextBrowser(this);
            TextBrowser->append(file);
            const int number_of_lines = file.split("<br>").size();
            // Get the height of the font being used
            QFontMetrics font_metrics(TextBrowser->font());
            int font_height = font_metrics.height();// Get the height by multiplying number of lines by font height, Maybe add to this a bit for a slight margin?
            int height = font_height * number_of_lines;// Set the height to the text broswer
            TextBrowser->setMinimumHeight(height);
            TextBrowser->setMaximumHeight(height);
            TextBrowser->setTextInteractionFlags(Qt::TextSelectableByMouse|Qt::TextSelectableByKeyboard|Qt::LinksAccessibleByMouse|Qt::LinksAccessibleByKeyboard);
            TextBrowser->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//on cache la scrollBar
            vlayout->addWidget(TextBrowser);
        }


    }
    lastMessageIsText=false;
    lastText=0;

}
void Widget::displayEmbed(const QString name, const QString information,const QList<QList<QString >>liste){
    QFrame* line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    ui->messageliste->addWidget(line);
    if(settings->value("settings/SoundNotification").toBool())
    {
        if(!QApplication::activeWindow()){
            QApplication::beep();
        }
    }
    QGridLayout  *GLayout = new QGridLayout();
    ui->messageliste->addSpacing(10);
    QLabel *labelName = new QLabel("<span style=\"font-size: 18px\">     "+name+"</p></span>");
    labelName->setWordWrap(true);
    QLabel *labelInformation = new QLabel("<span style=\"font-size: 10px\">     "+information+"</p></span>");
    labelInformation->setWordWrap(true);
    GLayout->addWidget(labelName, 0, 0, 1, 2);
    GLayout->addWidget(labelInformation,1,0,1,2);

    for (int i = 0; i < liste.size(); ++i) {
        if(liste[i][0]!=""&&liste[i][1]!=""){
            QLabel * LabelText = new QLabel(liste[i][0]);
            labelName->setWordWrap(true);
            QLabel * describle = new QLabel(liste[i][1]);
            describle->setWordWrap(true);
            GLayout->addWidget(LabelText,i+2,0);
            GLayout->addWidget(describle,i+2,1);
        }

    }

    GLayout->setHorizontalSpacing(10);
    ui->messageliste->addLayout(GLayout);

    QFrame* lineEnd = new QFrame();
    lineEnd->setFrameShape(QFrame::HLine);
    lineEnd->setFrameShadow(QFrame::Sunken);
    ui->messageliste->addWidget(lineEnd);

    lastMessageIsText=false;
    lastText=0;

}
void Widget::openfile(){
    QPushButton *PushButton = qobject_cast<QPushButton*>(sender());
    PushButton->setText(PushButton->text().remove(tr("telecharger: ","dans le bouton de telechargement")));
    QString extention{PushButton->text().split(".").last()};
    QString path = QFileDialog::getSaveFileName(nullptr,tr("choisir le nom du fichier"))+"."+extention;
    if(!path.isEmpty()){
        QFile file("temp/"+PushButton->text());
        file.copy(path);
    }
    qDebug()<<PushButton->text();
}
void Widget::addmessage(QString message){
    if(!lastMessageIsText){//le dernier message n'est pas du texte
        QLabel *label = new QLabel(this);
        label->setText(message);
        label->setTextInteractionFlags(Qt::TextSelectableByMouse|Qt::TextSelectableByKeyboard|Qt::LinksAccessibleByMouse|Qt::LinksAccessibleByKeyboard);
        label->setWordWrap(true);
        ui->messageliste->addWidget(label);
        lastText=label;
        lastMessageIsText=true;
    }else{//le dernier message est du texte
        //QString text =lastText->text()
        lastText->setText(lastText->text()+"<br><br>"+message);
        ui->messageliste->addWidget(lastText);
    }
}
void Widget::changestateconnectbutton(bool state)
{
    ui->conectbuton->setEnabled(state);
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
            addmessage(generatemesage(tr("Bonjour") + ui->pseudo->text()+".",tr("Tchat Bot")));
        }else if(random == 2){
            addmessage(generatemesage(tr("Salut") + ui->pseudo->text()+".",tr("Tchat Bot")));
        }else if(random == 3){
            addmessage(generatemesage(tr("Salut🖖") + ui->pseudo->text()+".",tr("Tchat Bot")));
        }else if(random == 4){
            addmessage(generatemesage(tr("Hello") + ui->pseudo->text()+".",tr("Tchat Bot")));
        }else if(random == 5){
            addmessage(generatemesage(tr("Hello👋") + ui->pseudo->text()+".",tr("Tchat Bot")));
        }
    }else if (command==tr("comment t'apelle tu")||command==tr("quel est ton nom")){
        int random = rand() % 2 + 1;
        if(random == 1){
            addmessage(generatemesage(tr("Tu peux m'appeller Tchat Bot."),tr("Tchat Bot")));
        }else if(random == 2){
            addmessage(generatemesage(tr("Tu peux m'appeller Tchat Bot 😊."),tr("Tchat Bot")));
        }
    }else if (command==tr("qui est tu")){
        addmessage(generatemesage(tr("Je suis le Tchat Bot crée par les développeurs de Ananta System, je suis encore très inachevé."),tr("Tchat Bot")));
    }else if (command=="clear"){
        executeCmd("clear");
    }else if (command=="clearall"){
        clients->sendcommande("clearForAll");
    }else if(command.startsWith("promot")){
        useraction *usrAction = new useraction;
        usrAction->show();
        for(int i=0;i<ui->clientlist->count();i++){
            usrAction->addUser(ui->clientlist->item(i)->text());
        }
        QObject::connect(usrAction, &useraction::finish, this, &Widget::changeUserRole);
    }else if (command=="actualise"||command=="update"){
        clients->sendcommande("updating");
    }else if(command.startsWith("acept")){
        changeUserRoom *usrRoom = new changeUserRoom;
        usrRoom->show();
        for(int i=0;i<ui->clientlist->count();i++){
            usrRoom->addUser(ui->clientlist->item(i)->text());
        }
        QObject::connect(usrRoom, &changeUserRoom::finish, this, &Widget::changeUsersaloon);
    }else if (command==tr("merci")){
        int random = rand() % 7 + 1;
        if(random == 1){
            addmessage(generatemesage(tr("De rien 😀"),tr("Tchat Bot")));
        }else if(random == 2){
            addmessage(generatemesage(tr("Tout le plaisir est pour moi 😀"),tr("Tchat Bot")));
        }else if(random == 3){
            addmessage(generatemesage(tr("Tout le plaisir est pour moi!"),tr("Tchat Bot")));
        }else if(random == 3){
            addmessage(generatemesage(tr("De rien !"),tr("Tchat Bot")));
        }else if(random == 4){
            addmessage(generatemesage(tr("Mais je suis là pour ça bien sûr 😀"),tr("Tchat Bot")));
        }else if(random == 5){
            addmessage(generatemesage(tr("Mais je suis là pour ça bien sûr !"),tr("Tchat Bot")));
        }else if (random == 6){
            addmessage(generatemesage(tr("Quand tu ne me parle pas je fais que des actions répétitives, recevoir des messages et les afficher😥..."),tr("Tchat Bot")));
        }else if (random == 7){
            addmessage(generatemesage(tr("Quand tu ne me parle pas je m'ennuie 😥"),tr("Tchat Bot")));
        }else if (command==tr("condenses")||command==tr("condense")||command==tr("condense menu")){
            condesed();
        }else if (command==tr("comment condenser la fenetre")||command==tr("comment condenser le menu")||command==tr("compacter la fenetre")){
            int random = rand() % 2 + 1;
            if(random == 1){
                displayMessagelist(generatemesage(tr("Il suffit de taper la commande /condense", "Attention bien taper la même commande!"),tr("Tchat Bot")));
            }else if(random == 2){
                addmessage(generatemesage(tr("Tu peux faire clique droit sur l'icône en bas à droite dans ta barre des tâches -> Condenser la fenêtre"),tr("Tchat Bot")));
            }
        }
    }else if(command==tr("ping")){
        clients->sendcommande("ping");
    }else{
        displayMessagelist(generatemesage(tr("Je suis desolé, mais je n'ai pas compris votre demande, vérifiez l'orthographe."),tr("Tchat Bot")));
    }
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

void Widget::on_conectbuton_clicked()
{
    if(ui->pseudo->text()==""||ui->pseudo->text()==" "||ui->pseudo->text()=="anonymous"){
        QMessageBox::critical(this,tr("pseudo invalid"),tr("Vous devez posseder un pseudo (anonymous est interdit)."));
        return;
    }
    clients->connectto(ui->serveurip->text(), ui->serveurport->value(),ui->pseudo->text());
    ui->clientlist->clear();
    displayconnectlabel("<font color=\"#ff0000\">"+tr("Déconnecté")+"</font>");
}


void Widget::on_sentbuton_clicked()
{
    QString message = ui->mesage->text(); // si le if prend trop de temps l'utilisateur ne pouras pas modifier son message
    QString msg = message;
    if(message==""){
        QMessageBox::information(this,tr("Securitée anti-DDOS"),tr("Vous ne pouvez pas envoyer un message vide."));
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
    }else if (m_path!=""){
        ui->erorLabel->setVisible(true);
        ui->erorLabel->setText("<font color=#DAA520>"+tr("uplaud du fichier en cours...","quand on envoi un fichier")+"</font>");
        QString m_pathSplit=m_path.split("/").last();
        clients->sendFile(msg,m_path,m_pathSplit);
        ui->pieceJointe->setIcon(QIcon(":/image/resource/image/paper-clip.png"));
        m_path="";
        listeOfpPath.append(m_pathSplit);
    }else if(m_path==""){
        clients->sendmessage(msg);
        ui->pieceJointe->setEnabled(true);
    }
    ui->mesage->clear();
}

void Widget::on_parametrebuton_2_clicked()
{
    parametres.show();
}
void Widget::on_pieceJointe_clicked()
{
    if(m_path==""){
        const auto fichier = QFileDialog::getOpenFileName(nullptr, tr("Ouvrir un fichier","dans les upload de fichier"), QString());
        QFile file(fichier);//on crée le fichier
        if(!file.open(QIODevice::ReadOnly)){
            QMessageBox::critical(nullptr,tr("erreur de permision","dans les ouverture de fichier"),tr("le fichier ne peut pas etre lu sans doute une erreur d'autorisation","dans les ouverture de fichier"));
            return;
        }//on test louverture du ficher
        if(file.size()>256901120){//si c'est superieur a 250mb
            QMessageBox::critical(nullptr,tr("fichier trop lourd","dans les upload de fichier"),tr("le fichier est trop gros il faut qu'il fasse moin que 250mB","dans les upload de fichier"));
            return;
        }
        ui->pieceJointe->setIcon(QIcon(":/image/resource/image/supression.png"));
        m_path = fichier;
    }else{
        m_path="";
        ui->pieceJointe->setIcon(QIcon(":/image/resource/image/paper-clip.png"));
    }
}

void Widget::on_pseudo_editingFinished()
{
    if(clients->getPsedo()!=ui->pseudo->text()){//eviter d'envoyer un message qui sert a rien
        clients->sendcommande("change_psedo",ui->pseudo->text());
        clients->editPsedo(ui->pseudo->text());
    }
}
