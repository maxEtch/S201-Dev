#include "lecteurvue.h"
#include "presentation.h"
#include "lecteur.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Lecteur *m = new Lecteur();
    Presentation *p = new Presentation();
    LecteurVue w;

    p->setModele(m);
    p->setVue(&w);

    w.setPresentation(p);

    w.show();
    return a.exec();
}
