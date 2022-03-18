#ifndef USERACTION_H
#define USERACTION_H

#include <QDialog>

namespace Ui {
class userAction;
}

class useraction : public QDialog
{
    Q_OBJECT

public:
    void addUser(QString name);
    explicit useraction(QWidget *parent = nullptr);
    ~useraction();
signals:
    void finish(QString name, int grade);
private:
    Ui::userAction *ui;

private slots:
    void on_buttonBox_accepted();
};

#endif // USERACTION_H
