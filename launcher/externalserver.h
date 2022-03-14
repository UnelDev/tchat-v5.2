#ifndef EXTERNALSERVER_H
#define EXTERNALSERVER_H

#include <QDialog>
#include <QFile>
#include <QSettings>
#include <QMessageBox>
#include <QTextStream>
#include <QDesktopServices>

namespace Ui {
class externalServer;
}

class externalServer : public QDialog
{
    Q_OBJECT

public:
    explicit externalServer(int* valueProgress, const QString Adresse, QWidget *parent = nullptr);
    ~externalServer();
    void changeProgress(const int newValue);
    void setState(const QString newState);
    void setInformation(const int port,const QString username);
private slots:
    void on_start_clicked();

private:
    Ui::externalServer *ui;
    int m_port;
    QString m_userName;
};

#endif // EXTERNALSERVER_H
