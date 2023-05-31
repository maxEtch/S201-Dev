#include "lecteur.h"

Lecteur::Lecteur()
{
    _numDiaporamaCourant = 0;   // =  le lecteur est vide
}

void Lecteur::avancer()
{
    _posImageCourante++;
    if (_posImageCourante > nbImages())
    {
        _posImageCourante = 1;
    }
}

void Lecteur::reculer()
{
    if (_posImageCourante == 1)
    {
        _posImageCourante = nbImages();
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


    imageACharger = new Image(3, "personne", "Blanche Neige", "C:\\cartesDisney\\carteDisney2.gif");
    _diaporama.push_back(imageACharger);
    imageACharger = new Image(2, "personne", "Cendrillon", "C:\\cartesDisney\\carteDisney4.gif");
    _diaporama.push_back(imageACharger);
    imageACharger = new Image(4, "animal", "Mickey", "C:\\cartesDisney\\carteDisney1.gif");
    _diaporama.push_back(imageACharger);
    imageACharger = new Image(1, "personne", "Grincheux", "C:\\cartesDisney\\carteDisney1.gif");
    _diaporama.push_back(imageACharger);



     // trier le contenu du diaporama par ordre croissant selon le rang de l'image dans le diaporama
	 // A FAIRE

     bool estTrie = true;
     while (estTrie)
     {
        estTrie = false;
        for (int var = 0; var < static_cast<int>(_diaporama.size()); var++)
        {
            if (_diaporama[var]->getRang() > _diaporama[var+1]->getRang())
            {
                Image val = *_diaporama[var];
                *_diaporama[var] = *_diaporama[var +1];
                *_diaporama[var+1] = val;
                estTrie = true;
            }
        }
     }

     _posImageCourante = 1;

     cout << "Diaporama num. " << numDiaporamaCourant() << " selectionne. " << endl;
     cout << nbImages() << " images chargees dans le diaporama" << endl;

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
