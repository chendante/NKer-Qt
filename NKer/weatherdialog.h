#ifndef WEATHERDIALOG_H
#define WEATHERDIALOG_H

#include <QDialog>
#include <QNetworkAccessManager>

namespace Ui {
class WeatherDialog;
}

class WeatherDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WeatherDialog(QWidget *parent = 0);
    ~WeatherDialog();

private slots:
    void finishedWeather(QNetworkReply*);

    void on_pushButton_clicked();

private:
    Ui::WeatherDialog *ui;

    //用于获取天气情况
    QNetworkAccessManager *m_weather;
};

#endif // WEATHERDIALOG_H
