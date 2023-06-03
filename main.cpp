#include "ampoulevue.h"
#include "modele.h"
#include "presentation.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    AmpouleVue w;
    Modele *m = new Modele();
    // créer la présentation
    presentation *p = new presentation();
    // faire pointer la présentation vers la vue et le modèle
    p->setVue(&w);
    p->setModele(m);
    // faire pointer la vue vers la présentation
    w.setPresentation(p);
    // initialiser la vue en conformité avec l'état initial du modèle
    w.majInterface(m->getEtat());
    w.show();

    return a.exec();
}
