/**
 * @file Case.hpp
 * @author
 * @brief
 * @version 0.1
 * @date 20-01-2026
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

#include "Pion.hpp" // doit définir Pion, Couleur, Taille
#include "Joueur.hpp"
#include <cstddef>  // nullptr

using namespace std;

class Case
{
private:
    // Tableau pour stocker les pions de différentes tailles sur la case
    Pion *emplacements[3]; // 0: petit, 1: moyen, 2: grand

public:
    // Constructeur par défaut
    Case();

    // Place un pion dans l’emplacement correspondant à sa taille.
    // Retourne false si l’emplacement est déjà occupé ou si p == nullptr.
    bool placerPion(Pion *pion);

    // Retire et renvoie le pion de taille t (nullptr si vide).
    Pion *retirerPion(Taille taille);

    // Renvoie le pion de taille t (nullptr si vide).
    Pion *getPion(Taille taille) const;

    // True si l’emplacement t est vide.
    bool estVide(Taille taille) const;
};