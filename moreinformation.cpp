/*By Unel at 30/12/21
For Ananta Project*/
#include "moreinformation.h"
#include "ui_moreinformation.h"

moreinformation::moreinformation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::moreinformation)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

moreinformation::~moreinformation()
{
    delete ui;
}

void moreinformation::on_pushButton_clicked()
{
    if(!QDesktopServices::openUrl(QUrl("https://gist.github.com/QuantumCD/6245215"))){
        QMessageBox::information(this,tr("erreur a louverture du lien","guit hub pour les theme"),tr("le lien ne veut pas souvrir le probleme vien de votre navigateur par default taper https://gist.github.com/QuantumCD/6245215 dans votre navigateur et faite nous un raport de bug sur le discord","guit hub pour les theme"));
    }
}

