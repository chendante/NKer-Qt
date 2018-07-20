#include "weatherdialog.h"
#include "ui_weatherdialog.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkReply>
#include <QNetworkRequest>


WeatherDialog::WeatherDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WeatherDialog)
{
    ui->setupUi(this);

    m_weather=new QNetworkAccessManager(this);
    QObject::connect(m_weather, SIGNAL(finished(QNetworkReply*)), this, SLOT(finishedWeather(QNetworkReply*)));
}

WeatherDialog::~WeatherDialog()
{
    delete ui;
}

void WeatherDialog::on_pushButton_clicked()
{
    QNetworkRequest network_request;
    QString cityName = ui->lineEdit->text();

    /*设置发送数据*/
    network_request.setUrl(QUrl(QString("http://v.juhe.cn/weather/index?format=2&cityname=%1&key=5eeb0ec7f05f61c667cb814f9ac9c2a0")
                        .arg(cityName)));

    m_weather->get(network_request);
}

void WeatherDialog::finishedWeather(QNetworkReply* m_reply)
{
    QJsonObject data=QJsonDocument::fromJson(m_reply->readAll()).object();
    QJsonObject today=data.value("result").toObject().value("today").toObject();
    QString temperature=today.value("temperature").toString();
    QString weather=today.value("weather").toString();
    QString wind=today.value("wind").toString();
    QString dressing_advice=today.value("dressing_advice").toString();
    ui->label_3->setText("温度："+temperature+" 天气："+weather+" 风力："+wind+" 穿衣建议："+dressing_advice);
    ui->label_3->setText("<html>"+tr("温度：")+temperature+"</html>"
                         "<html>"+"<br>"+tr("天气：")+weather+"</html>"
                         "<html>"+"<br>"+tr("风力：")+wind+"</html>"
                         "<html>"+"<br>"+tr("穿衣建议：")+dressing_advice.left(15)+"</html>"
                         "<html>"+"<br>"+dressing_advice.mid(10,dressing_advice.length()-15)+"</html>");
}
