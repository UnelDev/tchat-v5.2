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
signals:
    void finish(QList<QString>usrRole);
private:
    Ui::userAction *ui;

private slots:
    void on_buttonBox_accepted();
};

#endif // USERACTION_H
