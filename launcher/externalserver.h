#ifndef EXTERNALSERVER_H
#define EXTERNALSERVER_H

#include <QDialog>
#include <QSettings>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QDesktopServices>
#include <QStringList>

namespace Ui {
class externalServer;
}

class externalServer : public QDialog
{
    Q_OBJECT

public:
    explicit externalServer(int* valueProgress,QString Adresse, QWidget *parent = nullptr);
    ~externalServer();
    void changeProgress(const int newValue);
    void setState(const QString newState);
    void interactionFinish(const int port, const QString username);
    void startClient(const QString userName, const QString ip, const int port);
private slots:
    void on_pushButton_clicked();

private:
    int m_port;
    QString m_uername;
    Ui::externalServer *ui;
};

#endif // EXTERNALSERVER_H
