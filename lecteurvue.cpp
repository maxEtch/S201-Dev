#include "lecteurvue.h"
#include "qmessagebox.h"
#include "ui_lecteurvue.h"
#include "QString"

LecteurVue::LecteurVue(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LecteurVue)
{
    timer = new QTimer(this);

    ui->setupUi(this);

    connect(ui->bSuivant,SIGNAL(clicked()),this, SLOT(avancer()));  //ok
    connect(ui->bSuivant,SIGNAL(clicked()),this, SLOT(arreter()));  //essaye d'avancer dans le diapo et arrète le mode auto

    connect(ui->bPrecedent,SIGNAL(clicked()),this, SLOT(reculer()));    //ok
    connect(ui->bPrecedent,SIGNAL(clicked()),this, SLOT(arreter()));    //essaye d'avancer dans le diapo et arrète le mode auto

    connect(ui->bLancerDiapo,SIGNAL(clicked()),this,SLOT(lancer()));            //ok
    connect(ui->bArreterDiapo,SIGNAL(clicked()),this,SLOT(arreter()));          //ok
    connect(ui->actionCharger,SIGNAL(triggered()),this,SLOT(charger()));        //ok
    connect(ui->actionVitesse,SIGNAL(triggered()),this,SLOT(modifVitesse()));   //ok
    connect(ui->actionQuitter,SIGNAL(triggered()),this,SLOT(close()));          //ok
    connect(ui->actionPropos,SIGNAL(triggered()),this,SLOT(propos()));          //ok
    connect(ui->actionEnlever,SIGNAL(triggered()),this,SLOT(viderDiaporama())); //ok
    connect(timer, SIGNAL(timeout()),this,SLOT(avancerAuto()));

    creerBarStatus();

    //initialisation des variables
    _numDiaporamaCourant = 0;
    _posImageCourante = 0;


}

LecteurVue::~LecteurVue()
{
    delete ui;
    _diaporama.clear();
}

void LecteurVue::creerBarStatus()   //change l'état de la barre de status
{
    if (getEtat())
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
    if(getEtat())
    {
        _posImageCourante++;
        if (_posImageCourante == nbImages())
        {
            _posImageCourante = 0;
        }
        afficher();
    }
}


void LecteurVue::reculer() //marche
{
    qDebug() << "La flèche gauche marche";
    if(getEtat())
    {
        if (_posImageCourante == 0)
        {
            _posImageCourante = nbImages()-1;
        }
        else
        {
            _posImageCourante--;
        }
        afficher();
    }
}

void LecteurVue::lancer() //marche
{
    _posImageCourante = 0;
    afficher();

    ui->bArreterDiapo->setEnabled(true);    //active le bouton Arrèter diaporama
    setEtat(false);         //Met l'état en automatique
    creerBarStatus();       //Change la bar de status pour afficher le mode automatique

    timer->start(2000); //on lance le chronomètre
}

void LecteurVue::arreter() //marche
{
    qDebug() << "Le bouton arreter marche";
    ui->bArreterDiapo->setEnabled(false);   //Désactive le bouton Arreter le diaporama
    setEtat(true);         //Met l'état en manuel
    creerBarStatus();       //Change la bar de status pour afficher le mode automatique

    timer->stop();
}

void LecteurVue::charger() //marche
{
    qDebug() << "Le bouton charger le diaporama marche";

    Image* imageACharger;

    viderDiaporama();

    imageACharger = new Image(3, "Personne", "Blanche Neige", ":/lecteurDiapoV2/Disney_4.gif");
    _diaporama.push_back(imageACharger);
    imageACharger = new Image(2, "Personne", "Cendrillon", ":/lecteurDiapoV2/Disney_45.gif");
    _diaporama.push_back(imageACharger);
    imageACharger = new Image(4, "Animal", "Mickey", ":/lecteurDiapoV2/Disney_19.gif");
    _diaporama.push_back(imageACharger);
    imageACharger = new Image(1, "Animal", "Bambi", ":/lecteurDiapoV2/Disney_3.gif");
    _diaporama.push_back(imageACharger);

    triBulle(this->_diaporama);

    ui->lImageMax->setNum(static_cast<int>(_diaporama.size()));

    ui->bLancerDiapo->setDisabled(false);
    ui->bSuivant->setDisabled(false);
    ui->bPrecedent->setDisabled(false);

    afficher();
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

    qDebug()<<"affichage démarre";

    if (!_diaporama.empty())
    {

        QString categorie = QString::fromStdString(imageCourante()->getCategorie());
        ui->lCategorie->setText(categorie);

        QString text = QString::fromStdString(imageCourante()->getTitre());
        ui->lTitreImage->setText(text);

        int nombre = imageCourante()->getRang();
        ui->lImageActuel->setNum(nombre);

        QString chemin = QString::fromStdString(imageCourante()->getChemin());
        QImage cheminImage (chemin);
        ui->image->setPixmap(QPixmap::fromImage(cheminImage));
        ui->image->show();
    }
    else
    {
        ui->lCategorie->setText(tr("catégorie"));
        ui->lTitreImage->setText(tr("titre"));
        ui->lImageActuel->setText(tr("nbImageActuelle"));
        ui->lImageMax->setText(tr("nbImageTotal"));
        ui->image->setText(tr("image"));
    }


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

    arreter();
    _diaporama.clear();
    afficher();

    _posImageCourante = 0;

    ui->bLancerDiapo->setDisabled(true);
    ui->bSuivant->setDisabled(true);
    ui->bPrecedent->setDisabled(true);
}


void LecteurVue::triBulle(Diaporama &unDiaporama)
{
    bool estTrie = false;
    while (!estTrie)
    {
       estTrie = true;
       for (int var = 0; var < static_cast<int>(unDiaporama.size()-1); var++)
       {
           if (_diaporama[var]->getRang() > unDiaporama[var+1]->getRang())
           {
               Image val = *unDiaporama[var];
               *unDiaporama[var] = *unDiaporama[var +1];
               *unDiaporama[var+1] = val;
               estTrie = false;
           }
        }
    }
}

bool LecteurVue::getEtat()
{
    return _estManuel;
}

void LecteurVue::setEtat(bool estManuel)
{
    _estManuel = estManuel;
}

void LecteurVue::avancerAuto()
{
    qDebug() << "la fonction se lance";
    _posImageCourante++;
    if (_posImageCourante == nbImages())
    {
        _posImageCourante = 0;
    }
    afficher();
}
