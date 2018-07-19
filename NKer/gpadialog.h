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
    void showScore2(QStringList,QStringList,std::vector<double>,std::vector<double>);
};

#endif // GPADIALOG_H
