#pragma once

#include "Joueur.hpp"
#include <iostream>
#include <limits>

using namespace std;

class JoueurHumain : public Joueur
{
public:
    JoueurHumain(string nom, Couleur couleur);
    ~JoueurHumain();

    bool jouerCoup(Plateau* plateau) override;
};
