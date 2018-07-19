#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QRegExp>
#include <QValidator>
#include <QNetworkAccessManager>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();

private slots:
    void on_pushButton_clicked();

    void finishedLogin(QNetworkReply*);

private:
    Ui::LoginDialog *ui;

    QNetworkAccessManager *m_login;
    int status;  //当前网络状态，用于函数判断执行语句
};

#endif // LOGINDIALOG_H
