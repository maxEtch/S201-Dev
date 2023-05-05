#ifndef LECTEURVUE_H
#define LECTEURVUE_H

#include <QMainWindow>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class LecteurVue; }
QT_END_NAMESPACE

class LecteurVue : public QMainWindow
{
    Q_OBJECT

public:
    LecteurVue(QWidget *parent = nullptr);  //constructeur (variable à initialiser dedans si besoin)
    ~LecteurVue();  //destructeur
    void creerBarStatus(bool);  //permet de changer l'affichage dans la bar de status



private:
    Ui::LecteurVue *ui;

private slots:
    void avancer(); //fait défiler le diaporama vers l'image suivante
    void reculer(); //fait défiler le diaporama vers l'image suivante
    void lancer();  //change le mode en automatique
    void charger(); //permet de sélectionner un diaporama à afficher
    void modifVitesse();    //interface pour modifier la vitesse de défilement des images
    void arreter(); //change le mode de défilement en manuel
    void propos();  //affiche une boîte de dialogue pour aider l'utilisateur


};
#endif // LECTEURVUE_H
