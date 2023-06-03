#include "ampoulevue.h"
#include "ui_ampoulevue.h"
#include <QtWidgets>

AmpouleVue::AmpouleVue(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AmpouleVue)
{
    ui->setupUi(this);
    connect(ui->bAllumer,SIGNAL(clicked()),this,SLOT(demandeAllumer()));
    connect(ui->bEteindre,SIGNAL(clicked()),this,SLOT(demandeEteindre()));
}

AmpouleVue::~AmpouleVue()
{
    delete ui;

}

void AmpouleVue::demandeAllumer()
{
    qDebug() << "ca s'allume";
    _p->demandeAllumer();
}

void AmpouleVue::demandeEteindre()
{
    qDebug() << "ca s'eteint";
    _p->demandeEteindre();
}

void AmpouleVue::setPresentation(presentation* p)
{
    _p = p;
}

presentation * AmpouleVue::getPresentation()
{
    return _p;
}

void AmpouleVue::majInterface(Modele::UnEtat e)
{
    switch (e) {
        case Modele::allume :
            ui->lEtat->setPixmap(tr(":/td6/ampouleEteinte2.PNG"));
            ui->bAllumer->setEnabled(false);
            ui->bEteindre->setEnabled(true);
            break;
        case Modele::eteint :
            ui->lEtat->setPixmap(tr(":/td6/ampoulealluùe"));
            ui->bAllumer->setEnabled(true);
            ui->bEteindre->setEnabled(false);
            break;
        default:
            break;
}
}
