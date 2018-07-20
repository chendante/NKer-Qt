#include "logindialog.h"
#include "ui_logindialog.h"
#include <QDebug>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QMessageBox>
#include <QTextCodec>
#include <QFile>
#include <QFileDialog>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    //设置学号密码的输入设置
    QRegExp regx("[0-9]*");//正则表达式,学号的输入只能有数字
    QValidator *validator = new QRegExpValidator(regx, this );
    ui->lineEdit->setValidator( validator );//设置学号的输入验证
    QRegExp regxPW("^[\\S]*$");//设置不允许密码中间输入空格
    QValidator *pwvalidator = new QRegExpValidator(regxPW, this );
    ui->lineEdit_2->setValidator( pwvalidator );//设置密码验证器

    status=1;
    m_login=new QNetworkAccessManager(this);

    QObject::connect(m_login, SIGNAL(finished(QNetworkReply*)), this, SLOT(finishedLogin(QNetworkReply*)));

    //读取已经保存的账号密码信息，并将其置于登录框中
    QFile file("/login.txt");
    file.open(QIODevice::ReadOnly| QIODevice::Text);

     QTextStream txtInput(&file);
     QString str1=txtInput.readLine();
     ui->lineEdit->setText(str1);
     QString str2=txtInput.readLine();
     ui->lineEdit_2->setText(str2);
     file.close();
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_pushButton_clicked()
{
    QString id=ui->lineEdit->text();
    QString password=ui->lineEdit_2->text();

    //当保存按钮被选中后，将账号密码保存在txt中
    if(ui->checkBox->isChecked())
    {
        QFile f1("/login.txt");
        //将文件以只写形式打开
        f1.open(QIODevice::WriteOnly|QIODevice::Text);

        QTextStream str(&f1);

        str<<id<<endl<<password;
        f1.close();
    }

    //设置 request headers
    QNetworkRequest m_req(QUrl("http://eamis.nankai.edu.cn/eams/login.action"));  //该网址为教学管理系统登陆网址
    m_req.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

    //设置 Form Data
    QString content=tr("username=%1&password=%2&encodedPassword=&session_locale=zh_CN").arg(id).arg(password);

    m_login->post(m_req,content.toUtf8());

}

//得到登陆结束信号后，执行该函数
void LoginDialog::finishedLogin(QNetworkReply *m_reply)
{
    if(status==1)
    {
       if(m_reply->error()!=0){
       QMessageBox::critical(this, tr("错误"),tr("网络连接错误"));
       return;
    }

    m_reply->deleteLater();

    //访问计划完成情况页面
    QNetworkRequest m_req(QUrl("http://eamis.nankai.edu.cn/eams/myPlanCompl.action"));
    m_req.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

    m_login->get(m_req);

    status=2;
    }
    else if(status==2){
        QTextCodec *codec = QTextCodec::codecForName("UTF-8");
        QString score_data= codec->toUnicode(m_reply->readAll());
        if(score_data!=""){
            this->accept();
            emit getScore(score_data);
        }
        else {
            QMessageBox::critical(this, tr("错误"),tr("登录失败，请检查输入学号密码"));
        }
        //qDebug()<<'s'<<score_data.toStdString().data();
        m_reply->deleteLater();
    }
}
