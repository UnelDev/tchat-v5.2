#ifndef USERACTION_H
#define USERACTION_H

#include <QDialog>

namespace Ui {
class userAction;
}

class userAction : public QDialog
{
    Q_OBJECT

public:
    void addUser(QString name);
    explicit userAction(QWidget *parent = nullptr);
    ~userAction();    
private:
    Ui::userAction *ui;
signals:
    void finish(QList<QString>usrRole);
private slots:
    void on_buttonBox_accepted();
};

#endif // USERACTION_H
