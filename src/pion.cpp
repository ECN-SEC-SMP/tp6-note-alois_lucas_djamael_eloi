/**
 * @file pion.cpp
 * @author Aloïs GUILLON (alois.guillon@eleves.ec-nantes.fr)
 * @brief
 * @version 0.1
 * @date 2026-01-20
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "pion.hpp"

Pion::Pion(Couleur c, Taille t)
{
    this->couleur = c;
    this->taille = t;
}

Couleur Pion::getCouleur()
{
    return this->couleur;
}

Taille Pion::getTaille()
{
    return this->taille;
}