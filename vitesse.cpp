#include "vitesse.h"
#include "ui_vitesse.h"


Vitesse::Vitesse(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Vitesse)
{
    ui->setupUi(this);

    connect(ui->horizontalSlider,SIGNAL(valueChanged(int)),this, SLOT(changerText(int)));
}

Vitesse::~Vitesse()
{
    delete ui;
}

void Vitesse::changerText(int valeur)
{
    ui->valeurVitesse->setNum(valeur); //change la valeur du texte

}

int Vitesse::getVitesse()
{
    return ui->horizontalSlider->value();
}
