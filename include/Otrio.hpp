#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include "Joueur.hpp"
#include "Plateau.hpp"

using namespace std;

class Otrio
{
protected:
    Plateau plateau;
    vector<Joueur> joueurs;
    int joueurCourantIndex;

public:

    Otrio(const vector<Joueur>& joueurs);
    ~Otrio() = default;

    void initialiserPartie();
    void lancerBoucleJeu();
    void afficherEtatJeu() const; // en + affichage du plateau et des joueurs dans le terminal
    bool passerAuJoueurSuivant();
    bool estFini() const;
};