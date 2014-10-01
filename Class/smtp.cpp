#include "smtp.h"

Smtp::Smtp()
{
    sock=new QTcpSocket();
}

Smtp::Smtp(QString server,QString login,QString password)
{
    sock=new QTcpSocket();
    SetSmtpServer(server);
    SetLogin(login);
    SetPassword(password);
}

Smtp::~Smtp()
{
    if (sock->isOpen())
        sock->close();
    delete sock;
}

void Smtp::SetSmtpServer(QString server)
{
    this->server.clear();
    this->server.append(server);
}

void Smtp::SetLogin(QString login)
{
    this->login.clear();
    this->login.append(login);
}

void Smtp::SetPassword(QString password)
{
    this->password.clear();
    this->password.append(password);
}

void Smtp::SendMessage(QString to,QString message)
{
    QByteArray tmp;
    sock->connectToHost(server,25);
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
        sock->waitForReadyRead();
        qDebug()<<sock->readAll();
        sock->close();
    }
}
