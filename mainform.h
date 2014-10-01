#ifndef MAINFORM_H
#define MAINFORM_H

#include <QMainWindow>
#include <QtNetwork>
#include <QSystemTrayIcon>
#include <QCloseEvent>

#include "Class/smtp.h"
#include "Class/smtps.h"

namespace Ui {
class MainForm;
}

class MainForm : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainForm(QWidget *parent = 0);
    ~MainForm();
    void GetIP(QString url);

protected:
    //bool eventFilter(QObject* obj, QEvent* event);
    void closeEvent(QCloseEvent* event);
private slots:
    void ReadyIP();
    void FinishReadyIP();
    void UpdateIP();

    void on_pushButton_ok_clicked();
    void on_pushButton_cancel_clicked();
    void trayIconActivated(QSystemTrayIcon::ActivationReason);
    void on_action_exit_triggered();
    void on_action_setting_triggered();

private:
    Ui::MainForm *ui;
    QSystemTrayIcon* sys_tray;
    QTimer* timer;
    QSettings* settings;
    QNetworkAccessManager man;
    QNetworkReply* reply;
    QByteArray result_ip;
    QString smtp_server;
    QString login;
    QString password;
    QString url;
    QString time_out;
};

#endif // MAINFORM_H
