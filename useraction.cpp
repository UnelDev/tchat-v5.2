#include "useraction.h"
#include "ui_useraction.h"

useraction::useraction(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::userAction)
{
    ui->setupUi(this);
}
useraction::~useraction()
{
    delete ui;
}
void useraction::addUser(QString name){
    ui->userList->addItem(name);
}
void useraction::on_buttonBox_accepted()
{
    emit useraction::finish(ui->userList->currentText(),ui->roleList->currentIndex());
}

