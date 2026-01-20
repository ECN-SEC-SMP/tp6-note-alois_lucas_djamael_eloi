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

#include "plateau.hpp"

Plateau::Plateau()
{
}

bool Plateau::placerPion(int x, int y, Pion *p)
{
}

Case *Plateau::getCase(int x, int y)
{
    return &grille[y][x];
}

bool Plateau::verifierVictoire()
{
    return verifierLignes() || verifierColonnes() || verifierDiagonales() || verifierEmpilements();
}