#include "lecteurvue.h"
#include "ui_lecteurvue.h"
#include "QtWidgets"

LecteurVue::LecteurVue(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LecteurVue)
{
    ui->setupUi(this);
    connect(ui->bSuivant,SIGNAL(clicked()),this, SLOT(avancer()));              //ok
    connect(ui->bPrecedent,SIGNAL(clicked()),this, SLOT(reculer()));            //ok
    connect(ui->bLancerDiapo,SIGNAL(clicked()),this,SLOT(lancer()));            //ok
    connect(ui->bArreterDiapo,SIGNAL(clicked()),this,SLOT(arreter()));          //ok
    connect(ui->actionCharger,SIGNAL(triggered()),this,SLOT(charger()));        //ok
    connect(ui->actionVitesse,SIGNAL(triggered()),this,SLOT(modifVitesse()));   //ok
    connect(ui->actionQuitter,SIGNAL(triggered()),this,SLOT(close()));          //ok
    connect(ui->actionPropos,SIGNAL(triggered()),this,SLOT(propos()));          //ok

    createStatusBar(true);
}

LecteurVue::~LecteurVue()
{
    delete ui;
}

void LecteurVue::creerBarStatus(bool estManuel)   //change l'état de la barre de status
{
    if (estManuel)
    {
        statusBar()->showMessage(tr("Statut : Manuel"));
    }
    else
    {
        statusBar()->showMessage(tr("Statut : Automatique"));
    }
}


void LecteurVue::avancer() //marche
{
    qDebug() << "La flèche droite marche";

}

void LecteurVue::reculer() //marche
{
    qDebug() << "La flèche gauche marche";
}

void LecteurVue::lancer() //marche
{
    qDebug() << "Le bouton lancer marche";
    ui->bArreterDiapo->setEnabled(true);    //active le bouton Arrèter diaporama
    this->creerBarStatus(false);           //Change la bar de status pour afficher le mode automatique
}

void LecteurVue::arreter() //marche
{
    qDebug() << "Le bouton arreter marche";
    ui->bArreterDiapo->setEnabled(false);   //Désactive le bouton Arreter le diaporama
    this->creerBarStatus(true);            //Change l'état de la bar de status pour afficher le mode manuel
}

void LecteurVue::charger() //marche
{
    qDebug() << "Le bouton charger le diaporam marche";
}

void LecteurVue::modifVitesse() //marche
{
    qDebug() << "Le bouton modifier la vitesse marche";
}

void LecteurVue::propos()
{
    QMessageBox::information(this, "À propos de", "Va dans Paramètre pour charger un diaporama , puis explore les images avec les flèches ou appuies sur lancer"); //description provisoir
     QDialog maDlg(nullptr);    //création de la boite de dialogue
     maDlg.show();              //affiche la boite de dialogue

     qDebug() << "Le bouton À propos de marche";
}
