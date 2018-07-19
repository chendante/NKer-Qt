#include "mainwindow.h"
#include "logindialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    LoginDialog dlg;

    //关联网页获取与主窗口输出
    a.connect(&dlg,LoginDialog::getScore,&w,MainWindow::dealScore);

    if(dlg.exec()==QDialog::Accepted)
    {
        w.show();
    }
    else {
       exit(0);
    }

    return a.exec();
}
