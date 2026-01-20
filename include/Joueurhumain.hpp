#pragma once

#include "Joueur.hpp"

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
    bool jouerCoup(Plateau* plateau) override;

};