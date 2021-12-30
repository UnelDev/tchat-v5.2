/*By Unel at 30/12/21
For Ananta Project*/
#include "succees.h"
#include "ui_succees.h"

sucees::sucees(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sucees)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    QCoreApplication::setOrganizationName("ananta system");
    QCoreApplication::setOrganizationDomain("https://anantasystem.com/");
    QCoreApplication::setApplicationName("tchat");
    QCoreApplication::setApplicationVersion("5.0");
    settings = new QSettings("settings.ini", QSettings::IniFormat);
    if(settings->contains("succes/succes")){
        settings->setValue("succes/succes",true);
    }
    ui->saveNbMessage->setChecked(settings->value("succes/succes").toBool());
    ui->nbmessage->setText("le monbre de tes message :"+QString::number(settings->value("succes/nbmessage").toInt()));
    if(settings->value("succes/nbmessage").toInt()<0&&settings->value("succes/succes").toBool()){
        QMessageBox::critical(this,tr("tchit detecter"),tr("alors comme ca on veut avoir des sucée gratuis ? c'est mal de tricher"));
        ui->message10->setToolTip("imposible de l'avoir vous avez tricher");
        ui->message100->setToolTip("imposible de l'avoir vous avez tricher");
        ui->message1000->setToolTip("imposible de l'avoir vous avez tricher");
        ui->messagemaxint->setToolTip("imposible de l'avoir vous avez tricher");
        ui->userdifferent10->setToolTip("imposible de l'avoir vous avez tricher");
        ui->userdifferent30->setToolTip("imposible de l'avoir vous avez tricher");
        ui->userdifferent100->setToolTip("imposible de l'avoir vous avez tricher");
        ui->server20->setToolTip("imposible de l'avoir vous avez tricher");
        ui->message10->setText("");
        ui->message100->setText("");
        ui->message1000->setText("");
        ui->messagemaxint->setText("");
        ui->userdifferent10->setText("");
        ui->userdifferent30->setText("");
        ui->userdifferent100->setText("");
        ui->server20->setText("");
        ui->message10->setIcon(QIcon(":/image/suprimer.png"));
        ui->message100->setIcon(QIcon(":/image/suprimer.png"));
        ui->message1000->setIcon(QIcon(":/image/suprimer.png"));
        ui->messagemaxint->setIcon(QIcon(":/image/suprimer.png"));
        ui->userdifferent10->setIcon(QIcon(":/image/suprimer.png"));
        ui->userdifferent30->setIcon(QIcon(":/image/suprimer.png"));
        ui->userdifferent100->setIcon(QIcon(":/image/suprimer.png"));
        ui->server20->setIcon(QIcon(":/image/suprimer.png"));
    }if(settings->value("succes/nbmessage").toInt()<0&&settings->value("succes/succes").toBool()==false){
        ui->message10->setToolTip("imposible de l'avoir vous avez desactiver les succés");
        ui->message100->setToolTip("imposible de l'avoir vous avez desactiver les succés");
        ui->message1000->setToolTip("imposible de l'avoir vous avez desactiver les succés");
        ui->messagemaxint->setToolTip("imposible de l'avoir vous avez desactiver les succés");
        ui->userdifferent10->setToolTip("imposible de l'avoir vous avez desactiver les succés");
        ui->userdifferent30->setToolTip("imposible de l'avoir vous avez desactiver les succés");
        ui->userdifferent100->setToolTip("imposible de l'avoir vous avez desactiver les succés");
        ui->server20->setToolTip("imposible de l'avoir vous avez desactiver les succés");
        ui->message10->setText("");
        ui->message100->setText("");
        ui->message1000->setText("");
        ui->messagemaxint->setText("");
        ui->userdifferent10->setText("");
        ui->userdifferent30->setText("");
        ui->userdifferent100->setText("");
        ui->server20->setText("");
        ui->message10->setIcon(QIcon(":/image/suprimer.png"));
        ui->message100->setIcon(QIcon(":/image/suprimer.png"));
        ui->message1000->setIcon(QIcon(":/image/suprimer.png"));
        ui->messagemaxint->setIcon(QIcon(":/image/suprimer.png"));
        ui->userdifferent10->setIcon(QIcon(":/image/suprimer.png"));
        ui->userdifferent30->setIcon(QIcon(":/image/suprimer.png"));
        ui->userdifferent100->setIcon(QIcon(":/image/suprimer.png"));
        ui->server20->setIcon(QIcon(":/image/suprimer.png"));
    }if(settings->value("succes/nbmessage").toInt()>=10){
        ui->message10->setToolTip("obtenus");
        ui->message10->setText("");
        ui->message10->setIcon(QIcon(":/image/Check_green.png"));
    }if(settings->value("succes/nbmessage").toInt()>=100){
        ui->message100->setToolTip("obtenus");
        ui->message100->setText("");
        ui->message100->setIcon(QIcon(":/image/Check_green.png"));
    } if(settings->value("succes/nbmessage").toInt()>=1000){
        ui->message1000->setToolTip("obtenus");
        ui->message1000->setText("");
        ui->message1000->setIcon(QIcon(":/image/Check_green.png"));
    } if(settings->value("succes/nbmessage").toInt()>=2147483647){
        ui->messagemaxint->setToolTip("obtenus");
        ui->messagemaxint->setText("");
        ui->messagemaxint->setIcon(QIcon(":/image/Check_green.png"));
    }if(settings->value("succes/10userSimultaneously").toBool()){
        ui->userdifferent10->setToolTip("obtenus");
        ui->userdifferent10->setText("");
        ui->userdifferent10->setIcon(QIcon(":/image/Check_green.png"));
    }if(settings->value("succes/30userSimultaneously").toBool()){
        ui->userdifferent30->setToolTip("obtenus");
        ui->userdifferent30->setText("");
        ui->userdifferent30->setIcon(QIcon(":/image/Check_green.png"));
    }if(settings->value("succes/100userSimultaneously").toBool()){
        ui->userdifferent100->setToolTip("obtenus");
        ui->userdifferent100->setText("");
        ui->userdifferent100->setIcon(QIcon(":/image/Check_green.png"));
    }if(settings->value("succes/20server").toBool()){
        ui->server20->setToolTip("obtenus");
        ui->server20->setText("");
        ui->server20->setIcon(QIcon(":/image/Check_green.png"));
    }

}
sucees::~sucees()
{
    delete ui;
}
void sucees::on_message10_clicked()
{
    if(settings->value("succes/nbmessage").toInt()<=10&&settings->value("succes/nbmessage").toInt()>=0&&settings->value("succes/succes").toBool()){
        QMessageBox::information(this,tr("info"),tr("pour avoir ce succé il faux avoir envoyer 10 message"));
    }else if(settings->value("succes/nbmessage").toInt()>=10){
        QMessageBox::information(this,tr("info"),tr("vous avez reusis a avoir ce succée"));
    }else if(!settings->value("succes/succes").toBool()){
        QMessageBox::information(this,tr("info"),tr("pour avor ce succes il faut avoir 10 message mais vous avez desactiver l'option"));
    }
}
void sucees::on_message100_clicked()
{
    if(settings->value("succes/nbmessage").toInt()<=100&&settings->value("succes/nbmessage").toInt()>=0&&settings->value("succes/succes").toBool()){
        QMessageBox::information(this,tr("info"),tr("pour avoir ce succé il faux avoir envoyer 100 message"));
    }else if(settings->value("succes/nbmessage").toInt()>=100){
        QMessageBox::information(this,tr("info"),tr("vous avez reusis a avoir ce succée"));
    }else if(!settings->value("succes/succes").toBool()){
        QMessageBox::information(this,tr("info"),tr("pour avor ce succes il faut avoir 100 message mais vous avez desactiver l'option"));
    }
}
void sucees::on_message1000_clicked()
{
    if(settings->value("succes/nbmessage").toInt()<=1000&&settings->value("succes/nbmessage").toInt()>=0&&settings->value("succes/succes").toBool()){
        QMessageBox::information(this,tr("info"),tr("pour avoir ce succé il faux avoir envoyer 1000 message"));
    }else if(settings->value("succes/nbmessage").toInt()>=1000){
        QMessageBox::information(this,tr("info"),tr("vous avez reusis a avoir ce succée"));
    }else if(!settings->value("succes/succes").toBool()){
        QMessageBox::information(this,tr("info"),tr("pour avor ce succes il faut avoir 1000 message mais vous avez desactiver l'option"));
    }
}
void sucees::on_messagemaxint_clicked()
{
    if(settings->value("succes/nbmessage").toInt()<=2147483647 &&settings->value("succes/nbmessage").toInt()>=0&&settings->value("succes/succes").toBool()){
        QMessageBox::information(this,tr("info"),tr("pour avoir ce succé il faux avoir envoyer 2 147 483 647 message"));
    }else if(settings->value("succes/nbmessage").toInt()>=2147483647){
        QMessageBox::information(this,tr("info"),tr("vous avez reusis a avoir ce succée"));
    }else if(!settings->value("succes/succes").toBool()){
        QMessageBox::information(this,tr("info"),tr("pour avor ce succes il faut avoir 2147483647 message mais vous avez desactiver l'option"));
    }
}
void sucees::on_saveNbMessage_toggled(bool checked)
{
    settings->setValue("succes/succes",checked);
}
void sucees::on_pushButton_2_clicked()
{
    settings->setValue("succes/nbmessage",0);
    int reponse = QMessageBox::question(this, tr("confirmation"), tr("le nombre de vos message va etre supimer et uniquemment le nombre atention cette option ne suprimeras pas vos message ecrit. voulez vous continuer ?"), QMessageBox ::Yes | QMessageBox::No);
    if (reponse == QMessageBox::Yes)
    {
        QMessageBox::critical(this,tr("supression prise en compte"),tr("la supression du nombre de message a bien fonctionée vous avez actuellement 0 message enregistrer"));
            ui->nbmessage->setText("le monbre de tes message :"+QString::number(settings->value("succes/nbmessage").toInt()));
    }
}
void sucees::on_userdifferent10_clicked()
{
    if(!settings->value("succes/10userSimultaneously").toBool()&&settings->value("succes/succes").toBool()){
        QMessageBox::information(this,tr("info"),tr("pour avoir ce suces il faut etre conecter en meme temps que 10 utilisateur"));
    }else if(settings->value("succes/10userSimultaneously").toBool()){
        QMessageBox::information(this,tr("info"),tr("vous avez reusis a avoir ce succée"));
    }else if(!settings->value("succes/succes").toBool()){
        QMessageBox::information(this,tr("info"),tr("pour avoir ce suces il faut etre conecter en meme temps que 10 utilisateur mais vous avez desactiver l'option"));
    }}

void sucees::on_userdifferent30_clicked()
{
    if(!settings->value("succes/30userSimultaneously").toBool()&&settings->value("succes/succes").toBool()){
        QMessageBox::information(this,tr("info"),tr("pour avoir ce suces il faut etre conecter en meme temps que 30 utilisateur"));
    }else if(settings->value("succes/30userSimultaneously").toBool()){
        QMessageBox::information(this,tr("info"),tr("vous avez reusis a avoir ce succée"));
    }else if(!settings->value("succes/succes").toBool()){
        QMessageBox::information(this,tr("info"),tr("pour avoir ce suces il faut etre conecter en meme temps que 30 utilisateur mais vous avez desactiver l'option"));
    }
}
void sucees::on_userdifferent100_clicked()
{
    if(!settings->value("succes/100userSimultaneously").toBool()&&settings->value("succes/succes").toBool()){
        QMessageBox::information(this,tr("info"),tr("pour avoir ce suces il faut etre conecter en meme temps que 100 utilisateur"));
    }else if(settings->value("succes/100userSimultaneously").toBool()){
        QMessageBox::information(this,tr("info"),tr("vous avez reusis a avoir ce succée"));
    }else if(!settings->value("succes/succes").toBool()){
        QMessageBox::information(this,tr("info"),tr("pour avoir ce suces il faut etre conecter en meme temps que 100 utilisateur mais vous avez desactiver l'option"));
    }
}
void sucees::on_server20_clicked()
{
    if(!settings->value("succes/20server").toBool()&&settings->value("succes/succes").toBool()){
        QMessageBox::information(this,tr("info"),tr("pour avoir ce suces il faut s'etre conecter a 20 serveur"));
    }else if(settings->value("succes/20server").toBool()){
        QMessageBox::information(this,tr("info"),tr("vous avez reusis a avoir ce succée"));
    }else if(!settings->value("succes/succes").toBool()){
        QMessageBox::information(this,tr("info"),tr("pour avoir ce suces il faut s'etre conecter a 20 serveur mais vous avez desactiver l'option"));
    }
}

