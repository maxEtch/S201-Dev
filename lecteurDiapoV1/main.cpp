#include "lecteurvue.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LecteurVue w;
    w.show();
    w.createStatusBar(false);

    w.createStatusBar(true);
    return a.exec();
}
