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
