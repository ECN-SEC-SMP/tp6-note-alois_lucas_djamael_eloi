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
    int mode; // mode de jeu (0 = standard, 1= 2 joueurs, 3= avec IA)

public:

    Otrio(void);
    ~Otrio();

    void initialiserPartie(int mode=0);
    void lancerBoucleJeu();
    void afficherEtatJeu() const; // en + affichage du plateau et des joueurs dans le terminal
    bool passerAuJoueurSuivant();
    bool estFini() const;
    
    // Getters pour l'affichage graphique
    const Plateau& getPlateau() const { return plateau; }
    const vector<JoueurHumain>& getJoueurs() const { return joueurs; }
    int getJoueurCourantIndex() const { return joueurCourantIndex; }
};