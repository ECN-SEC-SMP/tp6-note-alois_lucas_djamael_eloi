/**
 * @file Plateau.cpp
 * @author Eloi Tourangin (Eloi.Tourangin@eleves.ec-nantes.fr)
 * @brief
 * @version 0.1
 * @date 20-01-2026
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "Plateau.hpp"

Plateau::Plateau()
{
}

bool Plateau::placerPion(int x, int y, Pion *p)
{
    // verifier si la case est valide et placer le pion
    if (x < 0 || x >= this->grille.size() || y < 0 || y >= this->grille.size())
    {
        return false;
        throw invalid_argument("placerPion: coordonnées de case invalides.");
    }
    
    bool placed = this->grille[y][x].placerPion(p);
    return placed;
}

Case *Plateau::getCase(int x, int y)
{
    return &grille[y][x];
}

bool Plateau::verifierVictoire()
{
    return verifierLignes() || verifierColonnes() || verifierDiagonales() || verifierEmpilements();
}

bool Plateau::verifierLignes()
{   
    
}

bool Plateau::verifierColonnes()
{
    return true;
}

bool Plateau::verifierDiagonales()
{
    return true;
}

bool Plateau::verifierEmpilements()
{
    return true;
}