#ifndef PRESENTATION_H
#define PRESENTATION_H

#include <QObject>
#include "lecteur.h"

class LecteurVue;
class Presentation
{
public:
    Presentation();
    void setModele(Lecteur *m);
    void setVue(LecteurVue *v);
    void demandeAvancer();
    void demandeReculer();
    void demandeCharger();

private:
    Lecteur *_leModele;
    LecteurVue *_laVue;
};

#endif // PRESENTATION_H
