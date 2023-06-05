#include "diaporama.h"
#include "qsqlquery.h"
#include "ui_diaporama.h"
#include "database.h"


Diaporama::Diaporama(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Diaporama)
{
    ui->setupUi(this);

    QSqlQuery query;
    query.exec("SELECT `Diaporamas`.`titre Diaporama` FROM `Diaporamas` ORDER BY `idDiaporama`;");
    for(int i = 0; query.next(); i++)
    {
        ui->tableWidget->insertRow(i);

        QTableWidgetItem *nomDiapo = new QTableWidgetItem(query.value(0).toString());
        ui->tableWidget->setItem(i,0,nomDiapo);

    }

    connect(ui->bAnnuler,SIGNAL(clicked()),this, SLOT(close()));
    connect(ui->bValider,SIGNAL(clicked()),this,SLOT(renvoieNbDiapo()));

}

Diaporama::~Diaporama()
{
    delete ui;
}

unsigned int Diaporama::getDiaporama()
{
    return diapoDemande;
}

void Diaporama::renvoieNbDiapo()
{
   diapoDemande = ui->tableWidget->currentRow() + 1;
   qDebug() << ui->tableWidget->currentRow() + 1;
   this->close();
}
