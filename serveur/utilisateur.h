#ifndef UTILISATEUR_H
#define UTILISATEUR_H

#include <QObject>
#include <QTcpSocket>


class utilisateur: public QObject
{
public:
    utilisateur();
    ~utilisateur();
    utilisateur(QString pseudo, QTcpSocket* socket);
    utilisateur(QTcpSocket* socket);
    void editpseudo(QString newpseudo);
    void editversion(QString newvertion);
    void setmessageSize(int size);
    void promote(int grade);
    void demote(int grande = 0);
    QTcpSocket* getSocket();
    int getmessageSize();
    int getGrade();
    QString getpseudo();
    QString getversion();
    QString safe();
    QString getGradeString();
    bool isconnecteed();
    bool highSafe();
    bool medumSafeOrSuperior();
    bool lowSafeOrSuperior();
private:
    QString vertion;
    QString pseudo;
    int m_grade;// peut etre 0 : utilisateur, 1 admin, 2host
    QTcpSocket* socket;
    int messageSize;
};
#endif // UTILISATEUR_H
