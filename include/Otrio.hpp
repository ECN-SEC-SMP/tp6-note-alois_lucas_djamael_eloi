#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <memory>             

#include "Joueur.hpp"
#include "Joueurhumain.hpp"
#include "JoueurIA.hpp"
#include "Plateau.hpp"

using namespace std;

class Otrio
{
protected:
    Plateau plateau;

    // Stockage polymorphe pour mélanger JoueurHumain et JoueurIA
    vector<unique_ptr<Joueur>> joueurs;

    int joueurCourantIndex;
    int mode; // mode de jeu (0 = standard, 1 = 2 joueurs, 3 = avec IA)

public:
    Otrio(void);
    ~Otrio();

    void initialiserPartie(int mode = 0);
    void lancerBoucleJeu();
    void afficherEtatJeu() const;
    bool passerAuJoueurSuivant();
    bool estFini() const;

    // Getters pour l'affichage graphique
    const Plateau& getPlateau() const { return plateau; }

    // On renvoie la liste de Joueur* (lisible par Affichage sans ownership)
    const vector<unique_ptr<Joueur>>& getJoueurs() const { return joueurs; }

    int getJoueurCourantIndex() const { return joueurCourantIndex; }
    int getMode() const { return mode; }
};
