/**
 * @file Pion.cpp
 * @author Aloïs GUILLON (alois.guillon@eleves.ec-nantes.fr)
 * @brief
 * @version 0.1
 * @date 2026-01-20
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "Pion.hpp"

Pion::Pion(Couleur c, Taille t)
{
    this->couleur = c;
    this->taille = t;
}

Couleur Pion::getCouleur() const
{
    return this->couleur;
}

Taille Pion::getTaille() const
{
    return this->taille;
}

string Pion::getTailleStr() const
{
    switch (taille)
    {
        case PETIT:  return "PETIT";
        case MOYEN:  return "MOYEN";
        case GRAND:  return "GRAND";
        default:     return "INCONNU";
    }
}

string Pion::getCouleurStr() const
{
    switch (couleur)
    {
        case ROUGE:  return "ROUGE";
        case VERT:   return "VERT";
        case BLEU:   return "BLEU";
        case JAUNE: return "JAUNE";
        default:     return "INCONNUE";
    }
}
