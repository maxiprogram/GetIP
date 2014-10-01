#include "mainform.h"
#include "ui_mainform.h"

MainForm::MainForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainForm)
{
    ui->setupUi(this);

    settings=new QSettings("settings.ini",QSettings::IniFormat,this);
    smtp_server=settings->value("smtp_server").toByteArray();
    login=settings->value("login").toByteArray();
    password=settings->value("password").toByteArray();
    url=settings->value("url").toByteArray();
    time_out=settings->value("time_out").toByteArray();

    ui->lineEdit_url->setText(url);
    ui->lineEdit_smtp->setText(smtp_server);
    ui->lineEdit_login->setText(login);
    ui->lineEdit_password->setText(password);
    ui->lineEdit_time_out->setText(time_out);

    timer=new QTimer(this);
    if (time_out!=0)
    {
        connect(timer,SIGNAL(timeout()),this,SLOT(UpdateIP()));
        timer->setInterval(time_out.toInt()*60*60*1000);
        timer->start();
    }

    sys_tray=new QSystemTrayIcon(this);
    sys_tray->setContextMenu(ui->menu);
    sys_tray->setIcon(QIcon("://tray_icon.png"));
    connect(sys_tray,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(trayIconActivated(QSystemTrayIcon::ActivationReason)));
    sys_tray->show();

    GetIP(url);
    //settings->setValue("password","1234");
}

MainForm::~MainForm()
{
    delete ui;
}

void MainForm::GetIP(QString url)
{
    result_ip.clear();
    reply=man.get(QNetworkRequest(QUrl(url)));
    connect(reply,SIGNAL(readyRead()),this,SLOT(ReadyIP()));
    connect(reply,SIGNAL(finished()),this,SLOT(FinishReadyIP()));
}

void MainForm::ReadyIP()
{
    result_ip.append(reply->readAll());
}

void MainForm::FinishReadyIP()
{
    QFile file("last_ip.log");
    file.open(QIODevice::WriteOnly);
    file.write(result_ip);
    file.close();
    /*Smtp без SSL
    Smtp s(smtp_server,login,password);
    //s.SetSmtpServer(smtp_server);
    //s.SetLogin(login);
    //s.SetPassword(password);
    QString str_date="";
    str_date+=QString::number(QDate::currentDate().day())+"."+
              QString::number(QDate::currentDate().month())+"."+
              QString::number(QDate::currentDate().year());
    str_date+=" "+QTime::currentTime().toString();
    s.SendMessage(login,"IP-adress on "+str_date+" = "+result_ip);
    */
    ///*Smtp с SSL
    Smtps s(smtp_server,login,password);
    //s.SetSmtpServer(smtp_server);
    //s.SetLogin(login);
    //s.SetPassword(password);
    QString str_date="";
    str_date+=QString::number(QDate::currentDate().day())+"."+
              QString::number(QDate::currentDate().month())+"."+
              QString::number(QDate::currentDate().year());
    str_date+=" "+QTime::currentTime().toString();
    s.SendMessage(login,"IP-adress on "+str_date+" = "+result_ip);
    //*/
}

void MainForm::UpdateIP()
{
    timer->setInterval(time_out.toInt()*60*60*1000);
    if (time_out!=0)
        GetIP(url);
}

void MainForm::on_pushButton_ok_clicked()
{
    url=ui->lineEdit_url->text();
    smtp_server=ui->lineEdit_smtp->text();
    login=ui->lineEdit_login->text();
    password=ui->lineEdit_password->text();
    time_out=ui->lineEdit_time_out->text();

    settings->setValue("url",url);
    settings->setValue("smtp_server",smtp_server);
    settings->setValue("login",login);
    settings->setValue("password",password);
    settings->setValue("time_out",time_out);

    this->hide();
}

void MainForm::on_pushButton_cancel_clicked()
{
    this->hide();
}

void MainForm::trayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
        case QSystemTrayIcon::Trigger:
        case QSystemTrayIcon::DoubleClick:
            this->show();
            break;
        default:
            break;
    }
}

void MainForm::closeEvent(QCloseEvent* event)
{
    this->hide();
    event->ignore();
}

void MainForm::on_action_exit_triggered()
{
    QApplication::exit();
}

void MainForm::on_action_setting_triggered()
{
    this->show();
}
