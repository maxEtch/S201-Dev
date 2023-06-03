#ifndef AMPOULEVUE_H
#define AMPOULEVUE_H

#include <QMainWindow>
#include "presentation.h"

QT_BEGIN_NAMESPACE
namespace Ui { class AmpouleVue; }
QT_END_NAMESPACE

class presentation;
class AmpouleVue : public QMainWindow
{
    Q_OBJECT

public:
    AmpouleVue(QWidget *parent = nullptr);
    ~AmpouleVue();
    void setPresentation(presentation *p);
    presentation* getPresentation();
    void majInterface (Modele::UnEtat e);


public slots:
    void demandeAllumer();
    void demandeEteindre();

private:
    Ui::AmpouleVue *ui;
    presentation* _p;
};
#endif // AMPOULEVUE_H
