#ifndef CHANGEUSERROOM_H
#define CHANGEUSERROOM_H

#include <QDialog>

namespace Ui {
class changeUserRoom;
}

class changeUserRoom : public QDialog
{
    Q_OBJECT

public:
    void addUser(QString name);
    explicit changeUserRoom(QWidget *parent = nullptr);
    ~changeUserRoom();

signals:
    void finish(const QString username, const QString room);


private:
    Ui::changeUserRoom *ui;
private slots:
    void on_buttonBox_accepted();

};

#endif // CHANGEUSERROOM_H
