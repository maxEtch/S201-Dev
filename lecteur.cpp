#include "lecteur.h"
#include "QDebug"
#include "lecteurvue.h"

Lecteur::Lecteur()
{
    _numDiaporamaCourant = 0;   // =  le lecteur est vide
}

void Lecteur::avancer()
{
    _posImageCourante++;
    if (_posImageCourante == nbImages())
    {
        _posImageCourante = 0;
    }
}

void Lecteur::reculer()
{
    if (_posImageCourante == 0)
    {
        _posImageCourante = nbImages()-1;
    }
    else
    {
        _posImageCourante--;
    }
}

void Lecteur::changerDiaporama(unsigned int pNumDiaporama)
{
    // s'il y a un diaporama courant, le vider, puis charger le nouveau Diaporama
    if (numDiaporamaCourant() > 0)
    {
        viderDiaporama();
    }
    _numDiaporamaCourant = pNumDiaporama;
    if (numDiaporamaCourant() > 0)
    {
        chargerDiaporama(); // charge le diaporama courant
    }

}

void Lecteur::chargerDiaporama()
{
    /* Chargement des images associées au diaporama courant
       Dans une version ultérieure, ces données proviendront d'une base de données,
       et correspondront au diaporama choisi */
    Image* imageACharger;

    viderDiaporama();

    qDebug() << "juste avant le vecteur";

    imageACharger = new Image(3, "personne", "Blanche Neige", ":/lecteurDiapoV7_MVP/Disney_2.gif");
    _diaporama.push_back(imageACharger);
    imageACharger = new Image(2, "personne", "Cendrillon", ":/lecteurDiapoV7_MVP/Disney_4.gif");
    _diaporama.push_back(imageACharger);
    imageACharger = new Image(4, "animal", "Dalmatien", ":/lecteurDiapoV7_MVP/Disney_1.gif");
    _diaporama.push_back(imageACharger);
    imageACharger = new Image(1, "animal", "Bambi", ":/lecteurDiapoV7_MVP/Disney_3.gif");
    _diaporama.push_back(imageACharger);

    qDebug() << "juste après le débug";

     // trier le contenu du diaporama par ordre croissant selon le rang de l'image dans le diaporama
	 // A FAIRE

     triBulle(this->_diaporama);

     qDebug() << "juste après le tri";

     _posImageCourante = 0;

     cout << "Diaporama num. " << numDiaporamaCourant() << " selectionne. " << endl;
     cout << nbImages() << " images chargees dans le diaporama" << endl;

}

void Lecteur::triBulle(Diaporama &unDiapo)
{
    bool estTrie = false;
    while (!estTrie)
    {
       estTrie = true;
       for (int var = 0; var < static_cast<int>(unDiapo.size()-1); var++)
       {
           if (_diaporama[var]->getRang() > unDiapo[var+1]->getRang())
           {
               Image val = *unDiapo[var];
               *unDiapo[var] = *unDiapo[var +1];
               *unDiapo[var+1] = val;
               estTrie = false;
           }
        }
     }
}


void Lecteur::viderDiaporama()
{
    if (nbImages () > 0)
    {
        unsigned int taille = nbImages();
        for (unsigned int i = 0; i < taille ; i++)
        {
            _diaporama.pop_back(); /* Removes the last element in the vector,
                                      effectively reducing the container size by one.
                                      AND deletes the removed element */
        }
     _posImageCourante = 0;
    }
    cout << nbImages() << " images restantes dans le diaporama." << endl;

}

void Lecteur::afficher()
{
    /* affiche les information sur le lecteur :
     * 1) vide (si num. de diaporama = 0) OU BIEN  numéro de diaporama affiché
     * 2) Si un diaporama courant est chargé (num. de diaporama > 0), affiche l'image courante OU BIEN 'diaporama vide'
     *     si ce diaporama n'a aucun image */
    if (_numDiaporamaCourant == 0)
    {
        cout << "diapo vide" << endl;
    }
    else
    {
        cout << "On lance le diapo num " << _numDiaporamaCourant << endl;
        if (nbImages() > 0)
        {
            cout << "on affiche une image !" << endl;
            imageCourante()->afficher();
        }
        else
        {
            cout << "pas d'images dans diapo" << endl;
        }
    }


}

unsigned int Lecteur::nbImages()
{
    return _diaporama.size();
}

Image *Lecteur::imageCourante()
{
    return _diaporama[_posImageCourante];
}

unsigned int Lecteur::numDiaporamaCourant()
{
    return _numDiaporamaCourant;
}
