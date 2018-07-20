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

    //登录成功后，执行该槽函数
    void finishedLogin(QNetworkReply*);

signals :
    //获取分数的信号，获取到后传递到主窗口
    void getScore(QString Score);

private:
    Ui::LoginDialog *ui;

    //使用通用协议执行网络操作的类

    //用于登录南开大学教学信息管理系统
    QNetworkAccessManager *m_login;


    int status;  //当前网络状态，用于函数判断执行语句
};

#endif // LOGINDIALOG_H
