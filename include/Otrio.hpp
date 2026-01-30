#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include "Joueur.hpp"
#include "Joueurhumain.hpp"
#include "Plateau.hpp"

using namespace std;

class Otrio
{
protected:
    Plateau plateau;
    vector<JoueurHumain> joueurs;
    int joueurCourantIndex;

public:

    Otrio(void);
    ~Otrio();

    void initialiserPartie();
    void lancerBoucleJeu();
    void afficherEtatJeu() const; // en + affichage du plateau et des joueurs dans le terminal
    bool passerAuJoueurSuivant();
    bool estFini() const;
    
    // Getters pour l'affichage graphique
    const Plateau& getPlateau() const { return plateau; }
    const vector<JoueurHumain>& getJoueurs() const { return joueurs; }
    int getJoueurCourantIndex() const { return joueurCourantIndex; }
};