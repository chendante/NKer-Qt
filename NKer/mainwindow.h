#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //处理从登录界面得到的分数数据
    void dealScore(QString score_data);


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
