#ifndef LECTEURVUE_H
#define LECTEURVUE_H

#include <QMainWindow>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class LecteurVue; }
QT_END_NAMESPACE

class LecteurVue : public QMainWindow
{
    Q_OBJECT

public:
    LecteurVue(QWidget *parent = nullptr);
    ~LecteurVue();
    void createStatusBar(bool);

private:
    Ui::LecteurVue *ui;

private slots: //il en faut 6
    void avancer();
    void reculer();
    void lancer();
    void charger();
    void modifVitesse();
    void arreter();
    void propos();


};
#endif // LECTEURVUE_H
