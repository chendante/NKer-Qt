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
    for(int j=0;j<scores.size();j++){
        ui->tableWidget->setItem(j,0,new QTableWidgetItem(class_types[j]));
        ui->tableWidget->setItem(j,1,new QTableWidgetItem(class_names[j]));
        ui->tableWidget->setItem(j,2,new QTableWidgetItem(QString::number(scores[j])));
        ui->tableWidget->setItem(j,3,new QTableWidgetItem(QString::number(credits[j])));
    }
}
