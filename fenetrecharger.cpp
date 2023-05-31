#include "fenetrecharger.h"
#include "qsqlquery.h"
#include "ui_fenetrecharger.h"
#include "database.h"

fenetreCharger::fenetreCharger(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::fenetreCharger)
{
    ui->setupUi(this);

    //ui->tableWidget->insertColumn(0);
    //ui->tableWidget->insertColumn(1);

    QSqlQuery query;
    query.exec("SELECT `Diaporamas`.`titre Diaporama` FROM `Diaporamas` JOIN DiaposDansDiaporama ON `Diaporamas`.`idDiaporama` = DiaposDansDiaporama.`idDiaporama` GROUP BY `titre Diaporama`;");
    for(int i = 0; query.next(); i++)
    {
        ui->tableWidget->insertRow(i);

        QTableWidgetItem *nomDiapo = new QTableWidgetItem(query.value(0).toString());
        QTableWidgetItem *nbImage = new QTableWidgetItem(query.value(1).toInt());
        ui->tableWidget->setItem(i,0,nomDiapo);
        ui->tableWidget->setItem(i,1,nbImage);
    }

    connect(ui->bAnnuler,SIGNAL(clicked()),this, SLOT(close()));
}

fenetreCharger::~fenetreCharger()
{
    delete ui;
}
