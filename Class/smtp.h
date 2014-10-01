#ifndef SMTP_H
#define SMTP_H

#include <QTcpSocket>
#include <QDebug>

class Smtp
{
public:
    Smtp();
    Smtp(QString server,QString login,QString password);
    ~Smtp();
    void SetSmtpServer(QString server);
    void SetLogin(QString login);
    void SetPassword(QString password);
    void SendMessage(QString to,QString message);
private:
    QTcpSocket* sock;
    QByteArray server;
    QByteArray login;
    QByteArray password;
};

#endif // SMTP_H
