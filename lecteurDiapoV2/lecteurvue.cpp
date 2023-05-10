#include "lecteurvue.h"
#include "qmessagebox.h"
#include "ui_lecteurvue.h"
#include "image.h"

LecteurVue::LecteurVue(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LecteurVue)
{
    _diaporama.clear();
    ui->setupUi(this);
    connect(ui->bSuivant,SIGNAL(clicked()),this, SLOT(avancer()));              //ok
    connect(ui->bPrecedent,SIGNAL(clicked()),this, SLOT(reculer()));            //ok
    connect(ui->bLancerDiapo,SIGNAL(clicked()),this,SLOT(lancer()));            //ok
    connect(ui->bArreterDiapo,SIGNAL(clicked()),this,SLOT(arreter()));          //ok
    connect(ui->actionCharger,SIGNAL(triggered()),this,SLOT(charger()));        //ok
    connect(ui->actionVitesse,SIGNAL(triggered()),this,SLOT(modifVitesse()));   //ok
    connect(ui->actionQuitter,SIGNAL(triggered()),this,SLOT(close()));          //ok
    connect(ui->actionPropos,SIGNAL(triggered()),this,SLOT(propos()));          //ok

    creerBarStatus(true);

    _numDiaporamaCourant = 0;


}

LecteurVue::~LecteurVue()
{
    delete ui;
    _diaporama.clear();
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
    _posImageCourante++;
    if (_posImageCourante > nbImages())
    {
        _posImageCourante = 1;
    }
    afficher();
}

void LecteurVue::reculer() //marche
{
    qDebug() << "La flèche gauche marche";
    if (_posImageCourante == 1)
    {
        _posImageCourante = nbImages();
    }
    else
    {
        _posImageCourante--;
    }
    afficher();
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
    qDebug() << "Le bouton charger le diaporama marche";

    Image* imageACharger;


    imageACharger = new Image(3, "personne", "Blanche Neige", "C:\\cartesDisney\\carteDisney2.gif");
    _diaporama.push_back(imageACharger);
    imageACharger = new Image(2, "personne", "Cendrillon", "C:\\cartesDisney\\carteDisney4.gif");
    _diaporama.push_back(imageACharger);
    imageACharger = new Image(4, "animal", "Mickey", "C:\\cartesDisney\\carteDisney1.gif");
    _diaporama.push_back(imageACharger);
    imageACharger = new Image(1, "personne", "Grincheux", "C:\\cartesDisney\\carteDisney1.gif");
    _diaporama.push_back(imageACharger);

     bool estTrie = true;
     while (estTrie)
     {
        estTrie = false;
        for (int var = 0; var < static_cast<int>(_diaporama.size()); var++)
        {
            if (_diaporama[var]->getRang() > _diaporama[var+1]->getRang())
            {
                Image val = *_diaporama[var];
                *_diaporama[var] = *_diaporama[var +1];
                *_diaporama[var+1] = val;
                estTrie = true;
            }
        }
     }
     ui->lImageMax->setNum(static_cast<int>(_diaporama.size()));
}

void LecteurVue::modifVitesse() //marche
{
    qDebug() << "Le bouton modifier la vitesse marche";
}

void LecteurVue::propos()
{
    QMessageBox::information(this, "À propos de", "Version : Version 2.0\n Date création : 5/05/2023\n Auteurs : Maxime Etchecopar, Axel Marrier, Lucas Marrot"); //description provisoir
     QDialog maDlg(nullptr);    //création de la boite de dialogue
     maDlg.show();              //affiche la boite de dialogue

     qDebug() << "Le bouton À propos de marche";
}

void LecteurVue::afficher()
{
    qDebug() << "afficher() ce lance";
    QString text = QString::fromStdString(imageCourante()->getCategorie());
    ui->lCategorie->setText(text);

    text = QString::fromStdString(imageCourante()->getTitre());
    ui->lTitreImage->setText(text);

    int nombre = imageCourante()->getRang();
    ui->lImageActuel->setNum(nombre);
}

unsigned int LecteurVue::nbImages()
{
    return _diaporama.size();
}

Image *LecteurVue::imageCourante()
{
    return _diaporama[_posImageCourante];
}

void LecteurVue::changerDiaporama(unsigned int pNumDiaporama)
{
    if (numDiaporamaCourant() > 0)
    {
        viderDiaporama();
    }
    _numDiaporamaCourant = pNumDiaporama;
    if (numDiaporamaCourant() > 0)
    {
        charger();
    }
}

unsigned int LecteurVue::numDiaporamaCourant()
{
    return _numDiaporamaCourant;
}

void LecteurVue::viderDiaporama()
{
    if (nbImages() > 0)
    {
        unsigned int taille = nbImages();
        for (unsigned int i = 0; i < taille; i++)
        {
            _diaporama.pop_back();
        }
    }
}
