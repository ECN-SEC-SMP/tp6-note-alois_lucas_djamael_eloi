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

// Renvoie le pion de taille t (nullptr si vide).
bool Case::estVide() const
{
    return emplacements[0] == nullptr &&
           emplacements[1] == nullptr &&
           emplacements[2] == nullptr;
}

// True si la case contient un empilement complet (3 tailles) d’une même couleur.
bool Case::aEmpilement() const
{
    // Si un des emplacements est vide, pas d'empilement complet
    if (emplacements[PETIT] == nullptr ||
        emplacements[MOYEN] == nullptr ||
        emplacements[GRAND] == nullptr)
    {
        return false; // pas d'empilement
    }

    // Vérifier si les couleurs des trois pions sont identiques
    Couleur c = emplacements[PETIT]->getCouleur();
    return (emplacements[MOYEN]->getCouleur() == c) &&
           (emplacements[GRAND]->getCouleur() == c);
}
