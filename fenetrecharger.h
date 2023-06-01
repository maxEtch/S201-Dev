#ifndef FENETRECHARGER_H
#define FENETRECHARGER_H

#include <QDialog>

namespace Ui {
class fenetreCharger;
}

class fenetreCharger : public QDialog
{
    Q_OBJECT

public:
    explicit fenetreCharger(QWidget *parent = nullptr);
    ~fenetreCharger();
    unsigned int getDiaporama();

public slots:
    void renvoieNbDiapo();

private:
    Ui::fenetreCharger *ui;
    unsigned int diapoDemande;

};

#endif // FENETRECHARGER_H
