#ifndef SMTPS_H
#define SMTPS_H

#include <QSslSocket>
#include <QDebug>

class Smtps
{
public:
    Smtps();
    Smtps(QString server,QString login,QString password);
    ~Smtps();
    void SetSmtpsServer(QString server);
    void SetLogin(QString login);
    void SetPassword(QString password);
    void SendMessage(QString to,QString message);
private:
    QSslSocket* sock;
    QByteArray server;
    QByteArray login;
    QByteArray password;
};

#endif // SMTPS_H
