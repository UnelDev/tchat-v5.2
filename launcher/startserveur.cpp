#include "startserveur.h"
#include "ui_startserveur.h"

startserveur::startserveur(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::startserveur)
{
    //ui
    ui->setupUi(this);
    ui->port->setVisible(false);
    ui->label_idantufiant->setVisible(false);
    ui->labelUsername->setVisible((false));
    ui->username->setVisible(false);
    ui->erorLabel->setVisible(false);
    //this->setFixedSize(317,119);
    //parametre
    QCoreApplication::setOrganizationName("ananta system");
    QCoreApplication::setOrganizationDomain("https://anantasystem.com/");
    QCoreApplication::setApplicationName("tchat");
    settings = new QSettings("settings.ini", QSettings::IniFormat);
    if(!settings->contains("launcher/serveurPosition")){
        settings->setValue("launcher/serveurPosition","serveur.exe");
    }if(!settings->contains("launcher/AutoConectServeurPosition")){
        settings->setValue("launcher/AutoConectServeurPosition","start.temp");
    }
    //remplissage de l'ip
    QString ip;
    foreach (const QHostAddress &address, QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost))
             ip = (address.toString());
    }
    ui->ip->setText(ip);
    //chargement du fichier
    QFile fichier(settings->value("launcher/AutoConectPosition").toString()); //on ouvre le fichier de preconexion
    if(fichier.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream flux(&fichier);
        flux.readLine();// sert a sauter une ligne caron ne repli pas lip dans le serveur
        ui->port->setValue(flux.readLine().toInt());
        ui->username->setText(flux.readLine());
    }
    else
    {
        QString name = qgetenv("USER");
        if (name.isEmpty())
            name = qgetenv("USERNAME");
        ui->username->setText(name);
    }
    verify();

}

startserveur::~startserveur()
{
    delete ui;
}
void startserveur::on_checkBox_toggled(bool checked)
{
    ui->label_idantufiant->setVisible(!checked);
    ui->port->setVisible(!checked);
    ui->labelUsername->setVisible(!checked);
    ui->username->setVisible(!checked);
    this->adjustSize();
}
void startserveur::on_pushButton_clicked()
{
    QString name = settings->value("launcher/AutoConectServeurPosition").toString();
    QFile file(name);
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
        QMessageBox::information(this,tr("erreur a louverture du registre"),tr("la clef de registre n'est pas presente faite nous un signalement"));
    QTextStream out(&file);
    out << ui->ip->text()+"\n";
    out <<QString::number(ui->port->value())+"\n";
    out << ui->username->text();
    if(!QDesktopServices::openUrl(QUrl(settings->value("launcher/serveurPosition").toString()))){
        QMessageBox::information(this,tr("erreur a louverture du lien"),tr("le lien ne veut pas souvrir la clef du registre a du etre modifier reinstaler le tchat"));
    }
    qApp->quit();
}
bool startserveur::verify(){
    QTcpServer serveurTest;
    if (!serveurTest.listen(QHostAddress::Any, ui->port->value())){//demarage sur le port choisi pour tester louverture
        ui->erorLabel->setVisible(true);
        ui->erorLabel->setText(tr("erreur le pin ","avec le n° deriere ")+QString::number(ui->port->value())+ tr(" est deja utiliser choisiser en un autre","dans l'alete du port"));
        this->adjustSize();
        serveurTest.close();
        serveurTest.deleteLater();
        return false;
    }else {
        ui->erorLabel->setVisible(false);
        this->adjustSize();
        serveurTest.close();
        serveurTest.deleteLater();
        return true;
    }
}
void startserveur::autocomplete(){
    QTcpServer serveurTest;
    if (!serveurTest.listen(QHostAddress::Any)) // Démarrage du serveur sur toutes les IP disponibles
    {
        // Si le serveur n'a pas été démarré correctement
        ui->erorLabel->setText(tr("Le serveur n'a pas pu être démarré. Raison :")+"<br/> " + serveurTest.errorString()+" <br/>");
    }else{
        ui->erorLabel->setText(tr("atention le port a éte changer automatiquemment"));
    }
    ui->port->setValue(serveurTest.serverPort());
    this->adjustSize();
    serveurTest.close();
    serveurTest.deleteLater();
}
void startserveur::on_port_valueChanged(int arg1)
{
    verify();
}

