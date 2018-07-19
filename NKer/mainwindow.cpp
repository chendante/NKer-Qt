#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tabledialog.h"
#include <QDebug>
#include<QStackedWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ave_a_score=0;
    ave_b_score=0;
    ave_c_score=0;
    ave_d_score=0;
    ave_e_score=0;
    ave_abcd_score=0;
    ave_abcde_score=0;

    m_stackedWidget=new QStackedWidget(this);
    TableDialog *tableDlg=new TableDialog(this);
    m_stackedWidget->addWidget(tableDlg);
    m_stackedWidget->move(0,30);
    m_stackedWidget->resize(600,600);
    m_stackedWidget->hide();

    QObject::connect(this, SIGNAL(sendScore(QStringList,QStringList,std::vector<double>,std::vector<double>)),
                     tableDlg,SLOT(showScore(QStringList,QStringList,std::vector<double>,std::vector<double>)));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::dealScore(QString score_data)
{
    //设置正则表达式获取姓名
    QString name,id;

    QRegExp rx(rul_name);
    int pos1 =score_data.indexOf(rx);
   if( pos1!=-1){name=rx.cap(1);
   }
   else{
    qDebug()<<"get_name fail";
   }
    //设置正则表达式获取学号
    QRegExp rx2(rul_id);
    int pos2 = score_data.indexOf(rx2);

    if( pos2!=-1){id=rx2.cap(1);
    }

    else{ qDebug()<<"get_name fail";}
    //改变窗体标题
    this->setWindowTitle("欢迎:"+name+" 学号:"+id);
    //设置正则表达式获取成绩
    QRegExp rx3(rul_socre);
    QRegExp rxt1(rul_type1);
    QRegExp rxt2(rul_type2);
    QRegExp rxt3(rul_type3);
    QRegExp rxt4(rul_type4);

    int type1=score_data.indexOf(rxt1);
    int type2=score_data.indexOf(rxt2);
    int type3=score_data.indexOf(rxt3);
    int type4=score_data.indexOf(rxt4);

    int pos3= score_data.indexOf(rx3);
     while ((pos3 = rx3.indexIn(score_data, pos3)) != -1 ) {
         QString class_name = rx3.cap(1);  //该条记录中的课程名称
         QString credit = rx3.cap(2);      //该条记录中的要求学分
         QString credit_get=rx3.cap(3);    //该条记录中的实修学分
         QString score=rx3.cap(4);        //该条记录中的成绩
         if(credit_get!=""){
             class_names.append(class_name);

             if(type1>pos3){
                class_types.append(tr("A"));
             }
             else if (type2>pos3) {
                class_types.append(tr("B"));
             }
             else if(type3>pos3){
                class_types.append(tr("C"));
             }
             else if(type4>pos3){
                class_types.append(tr("D"));
             }
             else{
                class_types.append(tr("E"));
             }

             credits.push_back(credit.toDouble());
             scores.push_back(score.toDouble());
         }

         //将位置移至下一条成绩记录的开始
       pos3 += rx3.matchedLength();
    }
    this->calculateScore();
}

void MainWindow::calculateScore()
{
    double sumOFcreditA=0;
    double sumOFcreditB=0;
    double sumOFcreditC=0;
    double sumOFcreditD=0;
    double sumOFcreditE=0;

    for(int i=0;i<scores.size();i++)
    {
        if(class_types[i]==tr("A"))
        {
            sumOFcreditA+=credits[i];
            ave_a_score+=scores[i]*credits[i];
            ave_abcd_score+=scores[i]*credits[i];
            ave_abcde_score+=scores[i]*credits[i];
        }
        else if (class_types[i]==tr("B")) {
            sumOFcreditB+=credits[i];
            ave_b_score+=scores[i]*credits[i];
            ave_abcd_score+=scores[i]*credits[i];
            ave_abcde_score+=scores[i]*credits[i];
        }
        else if (class_types[i]==tr("C")) {
            sumOFcreditC+=credits[i];
            ave_c_score+=scores[i]*credits[i];
            ave_abcd_score+=scores[i]*credits[i];
            ave_abcde_score+=scores[i]*credits[i];
        }
        else if (class_types[i]==tr("D")) {
            sumOFcreditD+=credits[i];
            ave_d_score+=scores[i]*credits[i];
            ave_abcd_score+=scores[i]*credits[i];
            ave_abcde_score+=scores[i]*credits[i];
        }
        else if (class_types[i]==tr("E")) {
            sumOFcreditE+=credits[i];
            ave_e_score+=scores[i]*credits[i];
            ave_abcde_score+=scores[i]*credits[i];
        }
    }
    ave_abcde_score/=sumOFcreditA+sumOFcreditB+sumOFcreditC+sumOFcreditD+sumOFcreditE;
    ave_abcd_score/=sumOFcreditA+sumOFcreditB+sumOFcreditC+sumOFcreditD;
    ave_a_score/=sumOFcreditA;
    ave_b_score/=sumOFcreditB;
    ave_c_score/=sumOFcreditC;
    ave_d_score/=sumOFcreditD;
    ave_e_score/=sumOFcreditE;

    qDebug()<<ave_a_score;
    //设置颜色，如果成绩低于某一成绩就会变红
    QPalette pa;
    double red=90;
    pa.setColor(QPalette::WindowText,Qt::red);
    if(ave_a_score<red)
    {
        ui->label_2->setPalette(pa);
    }
    if(ave_b_score<red)
    {
        ui->label_4->setPalette(pa);
    }
    if(ave_c_score<red)
    {
        ui->label_6->setPalette(pa);
    }
    if(ave_d_score<red)
    {
        ui->label_8->setPalette(pa);
    }
    if(ave_e_score<red)
    {
        ui->label_10->setPalette(pa);
    }
    if(ave_abcd_score<red)
    {
        ui->label_11->setPalette(pa);
    }
    if(ave_abcde_score<red)
    {
        ui->label_13->setPalette(pa);
    }
    ui->label_2->setText(QString::number(ave_a_score));
    ui->label_4->setText(QString::number(ave_b_score));
    ui->label_6->setText(QString::number(ave_c_score));
    ui->label_8->setText(QString::number(ave_d_score));
    ui->label_10->setText(QString::number(ave_e_score));
    ui->label_11->setText(QString::number(ave_abcd_score));
    ui->label_13->setText(QString::number(ave_abcde_score));

    emit sendScore(class_types,class_names,scores,credits);
}

void MainWindow::on_action_B_triggered()
{
    int index=0;
    m_stackedWidget->show();
    m_stackedWidget->setCurrentIndex(index);
}
