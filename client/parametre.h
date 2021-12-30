#ifndef PARAMETRE_H
#define PARAMETRE_H

#include <QDialog>
#include <QList>
#include <QFile>
#include <QStyleFactory>
#include <QMessageBox>
#include <QFileDialog>
#include <QDesktopServices>
#include <QSettings>
#include <QtDebug>
#include "succees.h"
#include "moreinformation.h"

namespace Ui {
class parametre;
}

class parametre : public QDialog
{
    sucees *succes;
    moreinformation *moreinformations;
    Q_OBJECT
public:
    QSettings* settings;
    explicit parametre(QWidget *parent = nullptr);
    ~parametre();
public slots:
    QPalette starttheme();
private slots:
    void checklanguage();

    void on_checkBox_toggled(bool checked);

    void on_checkBox_2_toggled(bool checked);

    void on_pushButton_3_clicked();

    void on_site_clicked();

    void on_discord_clicked();

    void on_tweter_clicked();

    void on_don_clicked();

    void on_pushButton_4_clicked();

    void on_checkboxmodecondensee_toggled(bool checked);

    void on_setcollor_activated(const QString &arg1);

    void on_comboBox_2_activated(const QString &arg1);

    //void on_comboBox_activated(const QString &arg1);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_5_clicked();

    void on_levelofsecure_currentIndexChanged(const QString &arg1);

private:
    Ui::parametre *ui;
private:
    QPalette whitehultra();
    QPalette darkmode();
    QPalette whitemode();
    QPalette darkmodeUltra();
};

#endif // PARAMETRE_H
