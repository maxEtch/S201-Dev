#include "presentation.h"
#include "lecteurvue.h"
#include <iostream>

Presentation::Presentation()
{

}

void Presentation::setModele(Lecteur *m)
{
    _leModele = m;
}

void Presentation::setVue(LecteurVue *v)
{
    _laVue = v;
}

void Presentation::demandeAvancer()
{
    _leModele->avancer();

    string categorie = _leModele->imageCourante()->getCategorie();
    string chemin = _leModele->imageCourante()->getChemin();
    int rang = _leModele->imageCourante()->getRang();
    string titre = _leModele->imageCourante()->getTitre();

    _laVue->afficherImage(titre, categorie, rang, chemin);
}

void Presentation::demandeReculer()
{
    _leModele->reculer();

    string categorie = _leModele->imageCourante()->getCategorie();
    string chemin = _leModele->imageCourante()->getChemin();
    int rang = _leModele->imageCourante()->getRang();
    string titre = _leModele->imageCourante()->getTitre();

    _laVue->afficherImage(titre, categorie, rang, chemin);
}

void Presentation::demandeCharger()
{
    _leModele->chargerDiaporama();
    int nbImage  = _leModele->nbImages();

    _laVue->afficherDiapo(nbImage);

    string categorie = _leModele->imageCourante()->getCategorie();
    string chemin = _leModele->imageCourante()->getChemin();
    int rang = _leModele->imageCourante()->getRang();
    string titre = _leModele->imageCourante()->getTitre();

    _laVue->afficherImage(titre, categorie,  rang, chemin);
}
