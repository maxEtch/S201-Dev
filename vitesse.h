#ifndef VITESSE_H
#define VITESSE_H

#include <QDialog>
#include "lecteurvue.h"

namespace Ui {
class Vitesse;
}

class Vitesse : public QDialog
{
    Q_OBJECT

public:
    explicit Vitesse(QWidget *parent = nullptr);
    ~Vitesse();

public slots:
    void changerText(int);
    int getVitesse();

private:
    Ui::Vitesse *ui;
};

#endif // VITESSE_H
