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

private:
    Ui::fenetreCharger *ui;
};

#endif // FENETRECHARGER_H
