#include "launcher.h"
#include "ui_launcher.h"

launcher::launcher(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::launcher)
{
    ui->setupUi(this);
}

launcher::~launcher()
{
    delete ui;
}


void launcher::on_pushButton_clicked()
{
    startserver.show();
}

void launcher::on_pushButton_2_clicked()
{
    connectclient.show();
}
