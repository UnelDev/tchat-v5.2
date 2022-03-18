#ifndef EXTERNALSERVER_H
#define EXTERNALSERVER_H

#include <QDialog>

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
private:
    Ui::externalServer *ui;
};

#endif // EXTERNALSERVER_H
