/*By Unel at 30/12/21
For Ananta Project*/
#ifndef MOREINFORMATION_H
#define MOREINFORMATION_H

#include <QDialog>
#include <QDesktopServices>
#include <QUrl>
#include <QMessageBox>

namespace Ui {
class moreinformation;
}

class moreinformation : public QDialog
{
    Q_OBJECT

public:
    explicit moreinformation(QWidget *parent = nullptr);
    ~moreinformation();

private slots:
    void on_pushButton_clicked();

private:
    Ui::moreinformation *ui;
};

#endif // MOREINFORMATION_H
