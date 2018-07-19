#include "gpadialog.h"
#include "ui_gpadialog.h"

GPADialog::GPADialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GPADialog)
{
    ui->setupUi(this);
}

GPADialog::~GPADialog()
{
    delete ui;
}

void GPADialog::showScore2(QStringList class_types,QStringList class_names,std::vector<double> scores,std::vector<double> credits)
{

    //标准4.0GPA
    double gpa=0;

    //改进4.0(1)
    double gpa1=0;

    //改进4.0(2)
    double gpa2=0;

    double sumOFcredit=0;

    for(int i=0;i<scores.size();i++)
    {
        double tem=0;
        double tem1=0;
        double tem2=0;
        if(scores[i]>=90)
        {
            tem=4.0;
            tem1=4.0;
            tem2=4.0;
        }
        else if (scores[i]>=85) {
            tem=3.0;
            tem1=4.0;
            tem2=4.0;
        }
        else if (scores[i]>=80) {
            tem=3.0;
            tem1=3.0;
            tem2=3.0;
        }
        else if (scores[i]>=75) {
            tem=2.0;
            tem1=3.0;
            tem2=3.0;
        }
        else if (scores[i]>=70) {
            tem=2.0;
            tem1=3.0;
            tem2=2.0;
        }
        else if (scores[i]>=60) {
            tem=1.0;
            tem1=2.0;
            tem2=2.0;
        }

        sumOFcredit+=credits[i];
        gpa+=tem*credits[i];
        gpa1+=tem1*credits[i];
        gpa2+=tem2*credits[i];
    }

    gpa/=sumOFcredit;
    gpa1/=sumOFcredit;
    gpa2/=sumOFcredit;

    ui->label_4->setText(QString::number(gpa));
    ui->label_5->setText(QString::number(gpa1));
    ui->label_6->setText(QString::number(gpa2));
}
