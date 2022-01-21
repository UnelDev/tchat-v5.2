#ifndef STARTSERVEUR_H
#define STARTSERVEUR_H

#include <QWidget>
#include <QDesktopServices>
#include <QMessageBox>
#include <QUrl>
#include <QTcpSocket>
#include <QSettings>
#include <QFile>
#include <QNetworkInterface>
#include <QTcpServer>

namespace Ui {
class startserveur;
}

class startserveur : public QWidget
{
    Q_OBJECT

public:
    explicit startserveur(QWidget *parent = nullptr);
    ~startserveur();

private slots:
    void on_checkBox_toggled(bool checked);
    bool verify();
    void on_pushButton_clicked();
    void on_port_valueChanged(int arg1);

private:
    QSettings* settings;
    Ui::startserveur *ui;
};

#endif // STARTSERVEUR_H
