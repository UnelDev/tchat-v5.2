#include "externalserver.h"
#include "ui_externalserver.h"

externalServer::externalServer(int *valueProgress, QString Adresse, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::externalServer)
{
    ui->setupUi(this);
    ui->ip->setText(Adresse);
    ui->progressBar->setValue(*valueProgress);
    this->adjustSize();
    ui->aide->setVisible(false);
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
void externalServer::setState(const QString newState){
    ui->state->setText(newState);
    this->adjustSize();
}
void externalServer::interactionFinish(const int port, const QString username){
    m_port = port;
    m_uername = username;
    ui->state->setText(tr("initialisation terminée sur le port : ","luncher")+QString::number(port));
    this->adjustSize();
}
void externalServer::startClient(const QString userName, const QString ip, const int port){
    QSettings settings("settings.ini", QSettings::IniFormat);
    QFile file(settings.value("launcher/AutoConectClientPosition").toString());
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        QMessageBox::information(nullptr,tr("erreur a louverture du registre"),tr("la clef de registre n'est pas presente faite nous un signalement"));
    QTextStream out(&file);
    out << ip +"\n";
    out <<QString::number(port)+"\n";
    out << userName;
    QUrl client(settings.value("launcher/clientPosition").toString());
    if(!QDesktopServices::openUrl(client)){
        QMessageBox::information(nullptr,tr("erreur a louverture du lien"),tr("le lien ne veut pas souvrir la clef du registre a du etre modifier reinstaler le tchat"));
    }
    qApp->quit();
}

void externalServer::on_pushButton_clicked()
{
    startClient(m_uername,ui->ip->text(),m_port);
}
