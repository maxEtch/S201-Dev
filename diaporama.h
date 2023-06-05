#ifndef DIAPORAMA_H
#define DIAPORAMA_H

#include <QDialog>

namespace Ui {
class Diaporama;
}

class Diaporama : public QDialog
{
    Q_OBJECT

public:
    explicit Diaporama(QWidget *parent = nullptr);
    ~Diaporama();
    unsigned int getDiaporama();

public slots:
    void renvoieNbDiapo();

private:
    Ui::Diaporama *ui;
    unsigned int diapoDemande;

};

#endif // DIAPORAMA_H
