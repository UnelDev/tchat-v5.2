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
    QList<QString>usrRole;
    usrRole.append(ui->userList->currentText());
    usrRole.append(QString::number(ui->roleList->currentIndex()));
    emit useraction::finish(usrRole);
}

