#include "changeuserroom.h"
#include "ui_changeuserroom.h"

changeUserRoom::changeUserRoom(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::changeUserRoom)
{
    ui->setupUi(this);
}
changeUserRoom::~changeUserRoom()
{
    delete ui;
}
void changeUserRoom::addUser(QString name){
    ui->userList->addItem(name);
}
void changeUserRoom::on_buttonBox_accepted()
{
    QString room;
    if(ui->room->currentIndex()==0){
        room="talk";
    }else if(ui->room->currentIndex()==1){
        room="waiting";
    }
    emit changeUserRoom::finish(ui->userList->currentText(),room);
}

