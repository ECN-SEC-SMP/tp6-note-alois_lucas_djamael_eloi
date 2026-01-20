#pragma once

#include "pion.h"   // doit définir Pion, Couleur, Taille
#include <cstddef>  // nullptr

class case {
private:
    // Tableau pour stocker les pions de différentes tailles sur la case
    Pion* emplacements[3]; // 0: petit, 1: moyen, 2: grand

    static int idx(Taille t);
public:

    // Constructeur par défaut
    Case();

    // Place un pion dans l’emplacement correspondant à sa taille.
    // Retourne false si l’emplacement est déjà occupé ou si p == nullptr.
    bool placerPion(Pion* pion);

    // Retire et renvoie le pion de taille t (nullptr si vide).
    bool retirerPion(Taille taille);

    // Renvoie le pion de taille t (nullptr si vide).
    Pion* getPion(Taille taille) const;

    // True si l’emplacement t est vide.
    bool estVide() const;

    // True si la case contient un empilement complet (3 tailles) d’une même couleur.
    bool aEmpilement() const;

};