/**
 * @file Case.cpp
 * @author
 * @brief
 * @version 0.1
 * @date 20-01-2026
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <stdexcept>

#include "Case.hpp"
#include "Pion.hpp" // pour enum Taille, Couleur

using namespace std;

// Constructeur par défaut
Case::Case() : emplacements{nullptr, nullptr, nullptr} {}

// Place un pion dans l’emplacement correspondant à sa taille.
// Retourne false si l’emplacement est déjà occupé ou si p == nullptr.
bool Case::placerPion(Pion *p)
{
    if (!p)
    {
        return false;
        throw invalid_argument("placerPion: pointeur Pion* null.");
    }

    const int i = static_cast<int>(p->getTaille()); // obtenir l'index basé sur la taille
    if (i < 0 || i > 2)
    {
        return false;
        throw invalid_argument("placerPion: taille de pion invalide.");
    }

    if (emplacements[i] != nullptr)
    { // emplacement déjà occupé
        return false;
        throw invalid_argument("placerPion: emplacement déjà occupé.");
    }

    emplacements[i] = p; // placer le pion
    return true;
}

// Retire et renvoie le pion de taille t (nullptr si vide).
Pion *Case::retirerPion(Taille t)
{
    const int i = static_cast<int>(t); // obtenir l'index basé sur la taille
    if (i < 0 || i > 2)
    { // taille invalide
        return nullptr;
        throw invalid_argument("retirerPion: taille de pion invalide.");
    }

    Pion *p = emplacements[i]; // obtenir le pion
    emplacements[i] = nullptr; // retirer le pion
    return p;                  // renvoyer le pion retiré (ou nullptr)
}

// Renvoie le pion de taille t (nullptr si vide).
Pion *Case::getPion(Taille t) const
{
    const int i = static_cast<int>(t); // obtenir l'index basé sur la taille
    if (i < 0 || i > 2)
    { // taille invalide
        return nullptr;
        throw invalid_argument("getPion: taille de pion invalide.");
    }

    return emplacements[i]; // renvoyer le pion (ou nullptr)
}

bool Case::estVide(Taille t) const {
    const int i = static_cast<int>(t);
    if (i < 0 || i > 2) {
        throw std::out_of_range("Taille invalide dans estVide(Taille)");
    }
    return emplacements[i] == nullptr;
}
