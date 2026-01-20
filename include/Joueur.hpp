#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include "Pion.hpp"
#include "Plateau.hpp"


#define NB_PIONS_PAR_TAILLE 3
#define NB_GROUPES_PIONS    3

using namespace std;

class Joueur
{
protected:
    string nom;
    Couleur couleur;
    vector<Pion*> main; 
    

public:
    // Constructeur et destructeur
    Joueur(string nom, Couleur couleur);
    ~Joueur();

    // Getters
    string getNom() const;
    Couleur getCouleur() const;
    vector<Pion*> getPionRestants() const;
    
    // Méthodes
    void retirerPionDeMain(Pion* p);
    virtual bool jouerCoup(Plateau* plateau) = 0;

};