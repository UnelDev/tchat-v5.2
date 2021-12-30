#include "remouvefile.h"
#include "ui_remouvefile.h"

remouveFile::remouveFile(QList<QMap<QString, QString>> &ref, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::remouveFile)
{
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    ui->setupUi(this);
    listeOfMessage =new QList<QMap<QString, QString>>;
    listeOfMessage = &ref;
    ui->TextLabeldisplayingNumberDessage->setText("<html><head/><body><p align=\"center\"><span style=\" font-size:14pt;\">Il y a "+QString::number(listeOfMessage->size())+" message(s)</span></p></body></html>");
    ui->deleteNMessage->setMaximum(listeOfMessage->size());
 //   on_deleteAllMessage_clicked();//Les autres fonctionnalités sont en test
}
remouveFile::~remouveFile()
{
    delete ui;
}

void remouveFile::on_delete10message_clicked()
{
    remouveOnFile(10);
    ui->TextLabeldisplayingNumberDessage->setText("<html><head/><body><p align=\"center\"><span style=\" font-size:14pt;\">Il y a "+QString::number(listeOfMessage->size())+" message(s)</span></p></body></html>");
    ui->deleteNMessage->setMaximum(listeOfMessage->size());
}


void remouveFile::on_deleteAllMessage_clicked()
{
    remouveOnFile(listeOfMessage->size());
    ui->TextLabeldisplayingNumberDessage->setText("<html><head/><body><p align=\"center\"><span style=\" font-size:14pt;\">Il y a "+QString::number(listeOfMessage->size())+" message(s)</span></p></body></html>");
    ui->deleteNMessage->setMaximum(listeOfMessage->size());
}
void remouveFile::on_deleteNMessage_editingFinished()
{
    remouveOnFile(ui->deleteNMessage->value());
    ui->TextLabeldisplayingNumberDessage->setText("<html><head/><body><p align=\"center\"><span style=\" font-size:14pt;\">Il y a "+QString::number(listeOfMessage->size())+" message(s)</span></p></body></html>");
    ui->deleteNMessage->setMaximum(listeOfMessage->size());
}
void remouveFile::remouveOnFile(int NumberOfRemouve){
    {
        QFile file("chat.dat");
        file.remove();
        file.close();
    }
    for (int compteur {NumberOfRemouve}; compteur > 0; --compteur)
    {
       if(listeOfMessage->isEmpty()){listeOfMessage->removeFirst();}
    }
    QFile file("chat.dat");
    if (!file.open(QIODevice::WriteOnly)){
            QMessageBox::critical(this, tr("Erreur passive"),tr("Le fichier ne peut pas être ouvert merci de réssayer plus tard."));
            return;
        }
    QDataStream out(&file);
    out << *listeOfMessage;
    QMessageBox::critical(this, tr("Erreur Fatal"),tr("Les clients ne peuvent pas être supprimés. Nouvelle tentative puis fermeture!"));
}
void remouveFile::on_pushButton_clicked()
{
    ui->TextLabeldisplayingNumberDessage->setText("<html><head/><body><p align=\"center\"><span style=\" font-size:14pt;\">Il y a "+QString::number(listeOfMessage->size())+" message(s)</span></p></body></html>");
    ui->deleteNMessage->setMaximum(listeOfMessage->size());
}

