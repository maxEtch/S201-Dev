#ifndef MODELE_H
#define MODELE_H

#include <QObject>

class presentation;
class Modele : public QObject
{
    Q_OBJECT
public:
    enum UnEtat {eteint, allume};
    explicit Modele(UnEtat e=eteint, QObject *parent = nullptr);
    void allumer();
		// modifie etat à valeur: allumer
    void eteindre();
		// modifie etat à valeur :eteindre
    UnEtat getEtat();
		// getter : retourne valeur de etat
private:
    UnEtat _etat; 
};

#endif // MODELE_H
