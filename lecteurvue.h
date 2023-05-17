#ifndef LECTEURVUE_H
#define LECTEURVUE_H

#include <QMainWindow>
#include <QWidget>
#include "image.h"

QT_BEGIN_NAMESPACE
namespace Ui { class LecteurVue; }
QT_END_NAMESPACE

typedef vector<Image*> Diaporama;

class LecteurVue : public QMainWindow
{
    Q_OBJECT

public:
    LecteurVue(QWidget *parent = nullptr);  //constructeur (variable à initialiser dedans si besoin)
    ~LecteurVue();  //destructeur
    void creerBarStatus(bool);  //permet de changer l'affichage dans la bar de status

    Image* imageCourante();     // retourne le pointeur vers l'image courante
    unsigned int numDiaporamaCourant(); //retourne le numero de l'image
    void afficher(); //affiche les informations sur lecteur-diaporama et image courante
    unsigned int nbImages();    //affiche la taille de _diaporama
    void changerDiaporama(unsigned int pNumDiaporama);    //a faire    permet de choisir un diaporama, 0 si aucun diaporama souhaité





private:
    Ui::LecteurVue *ui;
    unsigned _numDiaporamaCourant;   // numéro du diaporama courant, par défaut 0
    Diaporama _diaporama;            // pointeurs vers les images du diaporama
    unsigned int _posImageCourante;

public slots:
    void avancer(); //fait défiler le diaporama vers l'image suivante
    void reculer(); //fait défiler le diaporama vers l'image suivante
    void lancer();  //change le mode en automatique
    void charger(); //permet de sélectionner un diaporama à afficher
    void modifVitesse();    //interface pour modifier la vitesse de défilement des images
    void arreter(); //change le mode de défilement en manuel
    void propos();  //affiche une boîte de dialogue pour aider l'utilisateur
    void viderDiaporama();      //a faire       vide _diaporama de tous ses objets image et les delete

    void triBulle(Diaporama &);

};
#endif // LECTEURVUE_H
