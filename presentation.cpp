#include "presentation.h"
#include "ampoulevue.h"

presentation::presentation(QObject *parent)
    : QObject{parent}
{

}

void presentation::setModele(Modele *m)
{
    this->_leModele = m;
}

void presentation::setVue(AmpouleVue *v)
{
    this->_laVue = v;
}

AmpouleVue* presentation::getVue()
{
    return _laVue;
}
Modele* presentation::getModele()
{
    return _leModele;
}

void presentation::demandeAllumer()
{
    _leModele->allumer();
    _laVue->majInterface(_leModele->getEtat());
}
void presentation::demandeEteindre()
{
    _leModele->eteindre();
    _laVue->majInterface(_leModele->getEtat());
}
