#ifndef PRESENTATION_H
#define PRESENTATION_H

#include <QObject>
#include "modele.h"

class AmpouleVue;
class Modele;
class presentation : public QObject
{
    Q_OBJECT
public:
    explicit presentation(QObject *parent = nullptr); //constructeur

public:
    AmpouleVue* getVue();
    Modele* getModele();
    void setModele(Modele *m);
    void setVue(AmpouleVue *v);

public :
    void demandeAllumer();
    void demandeEteindre();

private:
    Modele *_leModele;
    AmpouleVue *_laVue;
};

#endif // PRESENTATION_H
