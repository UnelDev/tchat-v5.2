/*By Unel at 30/12/21
For Ananta Project*/
#ifndef SUCCEES_H
#define SUCCEES_H

#include <QDialog>
#include <QSettings>
#include <QMessageBox>
namespace Ui {
class sucees;
}

class sucees : public QDialog
{
    Q_OBJECT

public:
    explicit sucees(QWidget *parent = nullptr);
    ~sucees();

private slots:
    //void scan();

    void on_message10_clicked();

    void on_message100_clicked();

    void on_message1000_clicked();

    void on_messagemaxint_clicked();

    void on_saveNbMessage_toggled(bool checked);

    void on_pushButton_2_clicked();

    void on_userdifferent10_clicked();

    void on_userdifferent30_clicked();

    void on_userdifferent100_clicked();

    void on_server20_clicked();

private:
    QSettings* settings;
    Ui::sucees *ui;
};

#endif // SUCCEES_H
