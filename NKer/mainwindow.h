#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QStackedWidget;

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

signals:
    void sendScore(QStringList,QStringList,std::vector<double>,std::vector<double>);


private slots:
    void on_action_B_triggered();

private:
    Ui::MainWindow *ui;

    QStackedWidget *m_stackedWidget;

    //对成绩进行分析计算
    void calculateScore();

    //正则表达式，用于选取页面中的有用信息
    QString rul_id=(">""([0123456789]{7})""<");//学号
    QString rul_name=("18%\">""([^2016:]{2,20})""</td>");//姓名
    QString rul_socre=("</td>\r\n\t\t\t \t<td>([^刘子晨]{1,50})</td>\r\n\t\t\t \t<td align=\"center\">([0123456789. ]{0,10})</td>\r\n\t\t\t \t<td align=\"center\">([0123456789. ]{0,10})</td>\r\n\t\t\t \t<td align=\"center\">([0123456789. ]{0,10}) </td>\r\n\t\t\t");
    QString rul_type1=("院系公共必修课");
    QString rul_type2=("专业必修课");
    QString rul_type3=("专业选修课");
    QString rul_type4=("任选课");

    double ave_a_score;
    double ave_b_score;
    double ave_c_score;
    double ave_d_score;
    double ave_e_score;
    double ave_abcd_score;
    double ave_abcde_score;

    //课程名称
    QStringList class_names;

    //课程类型（A\B\C\D\E）
    QStringList class_types;

    //学分
    std::vector<double> credits;

    //成绩
    std::vector<double> scores;
};

#endif // MAINWINDOW_H
