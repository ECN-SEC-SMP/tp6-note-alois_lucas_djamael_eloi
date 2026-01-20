#ifndef JOUEURHUMAIN_HPP
#define JOUEURHUMAIN_HPP
#include "joueur.hpp"


using namespace std;

class JoueurHumain : public Joueur
{
protected:
    string nom;
    Couleur couleur;
    vector<Pion*> main; 
    

public:
    // Constructeur et destructeur
    JoueurHumain(string nom, Couleur couleur);
    ~JoueurHumain();

    // Méthodes
    void jouerCoup(Plateau* plateau) override;

};

#endif // JOUEURHUMAIN_HPP