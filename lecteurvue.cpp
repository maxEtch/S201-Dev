#include "lecteurvue.h"
#include "qmessagebox.h"
#include "ui_lecteurvue.h"
#include "QString"
#include "vitesse.h"

LecteurVue::LecteurVue(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LecteurVue)
{
    timer = new QTimer(this);  //créer un timer

    ui->setupUi(this);

    connect(ui->bSuivant,SIGNAL(clicked()),this, SLOT(avancer()));  //essaye d'avancer dans le diapo
    connect(ui->bSuivant,SIGNAL(clicked()),this, SLOT(arreter()));  //arrète le mode auto

    connect(ui->bPrecedent,SIGNAL(clicked()),this, SLOT(reculer()));    //essaye de reculer dans le diapo e
    connect(ui->bPrecedent,SIGNAL(clicked()),this, SLOT(arreter()));    //arrète le mode auto

    connect(ui->bLancerDiapo,SIGNAL(clicked()),this,SLOT(lancer()));            //active le mode automatique
    connect(ui->bArreterDiapo,SIGNAL(clicked()),this,SLOT(arreter()));          //arrète le mode automatique
    connect(ui->actionCharger,SIGNAL(triggered()),this,SLOT(charger()));        //charge les des images dans le lecteur
    connect(ui->actionVitesse,SIGNAL(triggered()),this,SLOT(modifVitesse()));   //ok
    connect(ui->actionQuitter,SIGNAL(triggered()),this,SLOT(close()));          //ferme la fenêtre
    connect(ui->actionPropos,SIGNAL(triggered()),this,SLOT(propos()));          //affiche une fenêtre avec les informations
    connect(ui->actionEnlever,SIGNAL(triggered()),this,SLOT(viderDiaporama())); //décharge les images du lecteur
    connect(timer, SIGNAL(timeout()),this,SLOT(avancerAuto()));                 //fais avancer le diapo en mode automatique quand le timer atteint une certaine valeur

    creerBarStatus(); //affiche la bar de staus indiquant le mode actuel

    //initialisation des variables
    _numDiaporamaCourant = 0;
    _posImageCourante = 0;


}

LecteurVue::~LecteurVue()
{
    delete ui;
    _diaporama.clear();
}

void LecteurVue::creerBarStatus()   //change l'état de la barre de status en fonction de la valeur estManuel
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


void LecteurVue::avancer()
{
    if(getEtat())  //si le diaporama est en mode manuel
    {
        _posImageCourante++;    //on augmente la position de l'image courante
        if (_posImageCourante == nbImages())
        {
            _posImageCourante = 0;      //si la position dépasse le nombre d'image en 'boucle' et on revient à la première image
        }
        afficher(); //on affiche la nouvelle image
    }
}


void LecteurVue::reculer()
{
    if(getEtat())   //si le diaporama est en mode manuel
    {
        if (_posImageCourante == 0) //si la position est à la première place
        {
            _posImageCourante = nbImages()-1;   //on revient à la dernière position du diaporama
        }
        else
        {
            _posImageCourante--;    //sinon on diminue la position de l'image courant
        }
        afficher(); //on affiche la nouvelle image
    }
}

void LecteurVue::lancer()
{
    _posImageCourante = 0;  //on se place à la première image du diaporama
    afficher(); //on affiche la première image

    ui->bArreterDiapo->setEnabled(true);    //active le bouton Arrèter diaporama
    setEtat(false);         //Met l'état en automatique
    creerBarStatus();       //Change la bar de status pour afficher le mode automatique

    timer->start(vitesseDefilement); //on lance le chronomètre
}

void LecteurVue::arreter()
{
    qDebug() << "Le bouton arreter marche";
    ui->bArreterDiapo->setEnabled(false);   //Désactive le bouton Arreter le diaporama
    setEtat(true);         //Met l'état en manuel
    creerBarStatus();       //Change la bar de status pour afficher le mode automatique

    timer->stop();  //on coupe le chronomètre
}

void LecteurVue::charger()
{


    Image* imageACharger; //on créer un pointeur pour stocker temporairement les images

    viderDiaporama();

    imageACharger = new Image(3, "Personne", "Blanche Neige", ":/lecteurDiapoV2/Disney_4.gif"); //on met les infos d'une image dans imageACharger
    _diaporama.push_back(imageACharger);    //on met imageACharger à la dernière place du diaporama
    imageACharger = new Image(2, "Personne", "Cendrillon", ":/lecteurDiapoV2/Disney_45.gif");   //on met les infos d'une image dans imageACharger
    _diaporama.push_back(imageACharger);    //on met imageACharger à la dernière place du diaporama
    imageACharger = new Image(4, "Animal", "Mickey", ":/lecteurDiapoV2/Disney_19.gif"); //on met les infos d'une image dans imageACharger
    _diaporama.push_back(imageACharger);    //on met imageACharger à la dernière place du diaporama
    imageACharger = new Image(1, "Animal", "Bambi", ":/lecteurDiapoV2/Disney_3.gif"); //on met les infos d'une image dans imageACharger
    _diaporama.push_back(imageACharger);    //on met imageACharger à la dernière place du diaporama

    triBulle(this->_diaporama); //on trie le diaporama

    ui->lImageMax->setNum(static_cast<int>(_diaporama.size())); //on affiche le nombre d'image total dans le diaporama

    ui->bLancerDiapo->setDisabled(false);  //on active le bouton lancer
    ui->bSuivant->setDisabled(false);      //on active le bouton suivant
    ui->bPrecedent->setDisabled(false);    //on active le bouton précédent

    afficher(); //on affiche l'image
}

void LecteurVue::modifVitesse()
{
    Vitesse v;
    // trouver comment mettre le slider à l'ancienne vitesse plus tard
    v.exec();
    vitesseDefilement = v.getVitesse();
}

void LecteurVue::propos()
{
    QMessageBox::information(this, "À propos de", "Version : Version 2.0\n Date création : 5/05/2023\n Auteurs : Maxime Etchecopar, Axel Marrier, Lucas Marrot"); //description provisoir
    QDialog maDlg(nullptr);    //création de la boite de dialogue
    maDlg.show();              //affiche la boite de dialogue
}

void LecteurVue::afficher()
{
    if (!_diaporama.empty())  //si le diaporama est vide on met un texte par défaut
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
    else    //si le diaporama n'est pas vide on affiche les infos de l'image
    {
        ui->lCategorie->setText(tr("catégorie"));
        ui->lTitreImage->setText(tr("titre"));
        ui->lImageActuel->setText(tr("nbImageActuelle"));
        ui->lImageMax->setText(tr("nbImageTotal"));
        ui->image->setText(tr("image"));
    }


}

unsigned int LecteurVue::nbImages() //retourne le nombre d'image dans le diaporam
{
    return _diaporama.size();
}

Image *LecteurVue::imageCourante() //retourne le pointeur de l'image actuel
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

void LecteurVue::setVitesse(int nouvelleVitesse)
{
    vitesseDefilement = nouvelleVitesse;
}

unsigned int LecteurVue::numDiaporamaCourant() //retourne le numéro du diaporama
{
    return _numDiaporamaCourant;
}

void LecteurVue::viderDiaporama()
{

    arreter();  //coupe le mode automatique
    _diaporama.clear(); //vide le diaporama
    afficher(); //affiche le texte de base

    _posImageCourante = 0;  //met l'image courante en première position

    ui->bLancerDiapo->setDisabled(true);    //désactive le bouton lancer
    ui->bSuivant->setDisabled(true);        //désactive le bouton suivant
    ui->bPrecedent->setDisabled(true);      //désactive le bouton précédent
}


void LecteurVue::triBulle(Diaporama &unDiaporama)
{
    bool estTrie = false;
    while (!estTrie)    //on continue le tri tant que le diaporama n'est pas trier
    {
       estTrie = true;  //si le tri ne s'exécute pas alors le diaporama est trié
       for (int var = 0; var < static_cast<int>(unDiaporama.size()-1); var++) //on parcour tout le diaporama
       {
           if (_diaporama[var]->getRang() > unDiaporama[var+1]->getRang()) //si le rang de 2 images n'est pas dans l'ordre
           {
               Image val = *unDiaporama[var];               //échange les positions des deux images
               *unDiaporama[var] = *unDiaporama[var +1];
               *unDiaporama[var+1] = val;
               estTrie = false; //le tri n'est pas finit et doit continuer
           }
        }
    }
}

bool LecteurVue::getEtat()
{
    return _estManuel;  //retourne true si le lecteur est en manuel
}

void LecteurVue::setEtat(bool estManuel)  //change l'état du diaporama
{
    _estManuel = estManuel;
}

void LecteurVue::avancerAuto()
{
    _posImageCourante++;    //on augmente la position de l'image courante
    if (_posImageCourante == nbImages())
    {                                       //si on est à la fin du diaporama on revient au début
        _posImageCourante = 0;
    }
    afficher(); //on affiche la nouvelle image
}
