/*By Unel at 30/12/21
For Ananta Project*/
#ifndef QFTPCLIENT_H
#define QFTPCLIENT_H

#include <QObject>
#include <QFtp>

class QftpClient : public QObject
{
    Q_OBJECT
public:
    explicit QftpClient(QObject *parent = nullptr);

signals:

};

#endif // QFTPCLIENT_H
