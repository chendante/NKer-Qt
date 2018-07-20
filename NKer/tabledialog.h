#ifndef TABLEDIALOG_H
#define TABLEDIALOG_H

#include <QDialog>

namespace Ui {
class TableDialog;
}

class TableDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TableDialog(QWidget *parent = 0);
    ~TableDialog();

private:
    Ui::TableDialog *ui;

private slots:
    //用于获取mainwindow传递过来的数据，并进行处理
    void showScore(QStringList,QStringList,std::vector<double>,std::vector<double>);
};

#endif // TABLEDIALOG_H
