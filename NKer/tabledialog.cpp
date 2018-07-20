#include "tabledialog.h"
#include "ui_tabledialog.h"

TableDialog::TableDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TableDialog)
{
    ui->setupUi(this);
}

TableDialog::~TableDialog()
{
    delete ui;
}

void TableDialog::showScore(QStringList class_types,QStringList class_names,std::vector<double> scores,std::vector<double> credits)
{
    ui->tableWidget->setRowCount(scores.size());
    for(int i=0;i<scores.size();i++){
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(class_types[i]));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(class_names[i]));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(QString::number(scores[i])));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(QString::number(credits[i])));

        //当成绩高于90时，将其显示为绿色
        if(scores[i]>=90)
        {
            ui->tableWidget->item(i,2)->setTextColor(QColor(0,255,0));
        }
        //当成绩低于85时，将其显示为红色
        else if (scores[i]<85) {
            ui->tableWidget->item(i,2)->setTextColor(QColor(255,0,0));
        }

        //当学分大于3且不是E类课时，将学分显示为蓝色
        if(credits[i]>3&&class_types[i]!=tr("E"))
        {
            ui->tableWidget->item(i,3)->setTextColor(QColor(0,0,255));
        }
    }
}
