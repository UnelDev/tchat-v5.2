#include "connecttoclient.h"
#include "ui_connecttoclient.h"

connecttoclient::connecttoclient(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::connecttoclient)
{
    ui->setupUi(this);
    ui->port->setVisible(false);
    ui->label_idantufiant->setVisible(false);
    ui->labelUsername->setVisible((false));
    ui->username->setVisible(false);
    QCoreApplication::setOrganizationName("ananta system");
    QCoreApplication::setOrganizationDomain("https://anantasystem.com/");
    QCoreApplication::setApplicationName("tchat");
    settings = new QSettings("settings.ini", QSettings::IniFormat);
    if(!settings->contains("launcher/clientPosition")){
        settings->setValue("launcher/clientPosition","chat.exe");
    }if(!settings->contains("launcher/AutoConectClientPosition")){
        settings->setValue("launcher/AutoConectClientPosition","start.temp");
    }
    //chargement du fichier
    QFile fichier(settings->value("launcher/AutoConectClientPosition").toString()); //on ouvre le fichier de preconexion
    if(fichier.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream flux(&fichier);
        ui->ip->setText(flux.readLine());// sert a sauter une ligne caron ne repli pas lip dans le serveur
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
}

connecttoclient::~connecttoclient()
{
    delete ui;
}
void connecttoclient::on_pushButton_clicked()
{
    QFile file(settings->value("launcher/AutoConectClientPosition").toString());
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        QMessageBox::information(this,tr("erreur a louverture du registre"),tr("la clef de registre n'est pas presente faite nous un signalement"));
    QTextStream out(&file);
    out << ui->ip->text()+"\n";
    out <<QString::number(ui->port->value())+"\n";
    out << ui->username->text();
    QUrl client(settings->value("launcher/clientPosition").toString());
    if(!QDesktopServices::openUrl(client)){
        QMessageBox::information(this,tr("erreur a louverture du lien"),tr("le lien ne veut pas souvrir la clef du registre a du etre modifier reinstaler le tchat"));
    }
    qApp->quit();
}
void connecttoclient::on_checkBox_toggled(bool checked)
{
    ui->label_idantufiant->setVisible(!checked);
    ui->port->setVisible(!checked);
    ui->labelUsername->setVisible(!checked);
    ui->username->setVisible(!checked);
    this->adjustSize();
}
