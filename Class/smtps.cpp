#include "smtps.h"

Smtps::Smtps()
{
    sock=new QSslSocket();
}

Smtps::Smtps(QString server,QString login,QString password)
{
    sock=new QSslSocket();
    SetSmtpsServer(server);
    SetLogin(login);
    SetPassword(password);
}

Smtps::~Smtps()
{
    if (sock->isOpen())
        sock->close();
    delete sock;
}

void Smtps::SetSmtpsServer(QString server)
{
    this->server.clear();
    this->server.append(server);
}

void Smtps::SetLogin(QString login)
{
    this->login.clear();
    this->login.append(login);
}

void Smtps::SetPassword(QString password)
{
    this->password.clear();
    this->password.append(password);
}

void Smtps::SendMessage(QString to,QString message)
{
    QByteArray tmp;
    qDebug()<<"Connect...";
    sock->connectToHostEncrypted(server,465);
    if (!sock->waitForConnected())
        qDebug()<<sock->errorString();
    if (sock->isOpen())
    {
        sock->write("ehlo "+server+"\r\n");
        sock->waitForReadyRead();
        qDebug()<<sock->readAll();
        sock->write("auth login\r\n");
        sock->waitForReadyRead();
        qDebug()<<sock->readAll();
        sock->write(login.toBase64()+"\r\n");
        sock->waitForReadyRead();
        qDebug()<<sock->readAll();
        sock->write(password.toBase64()+"\r\n");
        sock->waitForReadyRead();
        qDebug()<<sock->readAll();
        sock->write("mail from: "+login+"\r\n");
        sock->waitForReadyRead();
        qDebug()<<sock->readAll();
        tmp.clear();
        tmp.append(to);
        sock->write("rcpt to: "+tmp+"\r\n");
        sock->waitForReadyRead();
        qDebug()<<sock->readAll();
        sock->write("data\n");
        sock->waitForReadyRead();
        qDebug()<<sock->readAll();
        tmp.clear();
        tmp.append(message);
        sock->write(tmp+"\r\n");
        sock->waitForReadyRead();
        qDebug()<<sock->readAll();
        sock->write(".\r\n");
        sock->waitForReadyRead();
        qDebug()<<sock->readAll();
        sock->write("quit");
        //sock->waitForReadyRead();
        //qDebug()<<sock->readAll();
        sock->close();
    }
}
