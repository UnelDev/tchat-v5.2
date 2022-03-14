#include "externalserver.h"
#include "ui_externalserver.h"

externalServer::externalServer(int *valueProgress, const QString Adresse, QWidget *parent):
    QDialog(parent),
    ui(new Ui::externalServer)
{
    m_port = 0;
    ui->setupUi(this);
    ui->ip->setText(Adresse);
    ui->progressBar->setValue(*valueProgress);
    this->adjustSize();
    ui->aide->setVisible(false);
    ui->start->setVisible(false);
}

externalServer::~externalServer()
{
    delete ui;
}

void externalServer::changeProgress(const int newValue){
    ui->progressBar->setValue(newValue);
    this->adjustSize();
    if(newValue==ui->progressBar->maximum()){
        ui->progressBar->hide();
        ui->label_2->setText(tr("sur le port"));
        ui->aide->setVisible(true);
    }
}
void externalServer::setInformation(const int port,const QString username)
{
    m_port = port;
    m_userName = username;
}
void externalServer::setState(const QString newState){
    ui->state->setText(newState);
    this->adjustSize();
}

void externalServer::on_start_clicked()
{
    QSettings settings("settings.ini", QSettings::IniFormat);
    if(!settings.contains("launcher/clientPosition")){
        settings.setValue("launcher/clientPosition","chat.exe");
    }if(!settings.contains("launcher/AutoConectClientPosition")){
        settings.setValue("launcher/AutoConectClientPosition","start.temp");
    }
    QFile file(settings.value("launcher/AutoConectClientPosition").toString());
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        QMessageBox::information(this,tr("erreur a louverture du registre"),tr("la clef de registre n'est pas presente faite nous un signalement"));
    QTextStream out(&file);
    out << ui->ip->text()+"\n";
    out <<QString::number(m_port)+"\n";
    out << m_userName;
    QUrl client(settings.value("launcher/clientPosition").toString());
    if(!QDesktopServices::openUrl(client)){
        QMessageBox::information(this,tr("erreur a louverture du lien"),tr("le lien ne veut pas souvrir la clef du registre a du etre modifier reinstaler le tchat"));
    }
    qApp->quit();
}

