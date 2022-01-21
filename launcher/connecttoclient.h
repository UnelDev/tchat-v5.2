#ifndef CONNECTTOCLIENT_H
#define CONNECTTOCLIENT_H

#include <QWidget>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>
#include <QFile>
#include <QTextStream>
#include <string>
#include <QSettings>

namespace Ui {
class connecttoclient;
}

class connecttoclient : public QWidget
{
    Q_OBJECT

public:
    explicit connecttoclient(QWidget *parent = nullptr);
    ~connecttoclient();

private slots:

    void on_checkBox_toggled(bool checked);
    void on_pushButton_clicked();

private:
    QSettings* settings;
    Ui::connecttoclient *ui;
};

#endif // CONNECTTOCLIENT_H
