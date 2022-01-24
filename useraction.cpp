#include "useraction.h"
#include "ui_useraction.h"

userAction::userAction(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::userAction)
{
    ui->setupUi(this);
}
userAction::~userAction()
{
    delete ui;
}
void userAction::addUser(QString name){
    ui->userList->addItem(name);
}
void userAction::on_buttonBox_accepted()
{
    QList<QString>usrRole;
    usrRole.append(ui->userList->currentText());
    usrRole.append(QString::number(ui->roleList->currentIndex()));
    emit userAction::finish(usrRole);
}

