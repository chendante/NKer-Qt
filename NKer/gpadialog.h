#ifndef GPADIALOG_H
#define GPADIALOG_H

#include <QDialog>

namespace Ui {
class GPADialog;
}

class GPADialog : public QDialog
{
    Q_OBJECT

public:
    explicit GPADialog(QWidget *parent = 0);
    ~GPADialog();

private:
    Ui::GPADialog *ui;

private slots:
    //用于获取mainwindow传递过来的数据，并进行处理
    void showScore2(QStringList,QStringList,std::vector<double>,std::vector<double>);
};

#endif // GPADIALOG_H
