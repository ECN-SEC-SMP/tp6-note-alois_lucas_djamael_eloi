/**
 * @file Plateau.hpp
 * @author Eloi Tourangin (Eloi.Tourangin@eleves.ec-nantes.fr)
 * @brief
 * @version 0.1
 * @date 20-01-2026
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

#include <vector>
#include <stdexcept>
#include "Case.hpp"
#include "Pion.hpp"
//#include "Joueur.hpp"
class Joueur;

using namespace std;

class Plateau
{
private:
    vector<vector<Case>> grille;

    bool verifierLignes(Joueur* joueur);

    bool verifierColonnes(Joueur* joueur);

    bool verifierDiagonales(Joueur* joueur);

    bool verifierEmpilements(Joueur* joueur);

public:
    Plateau();
    ~Plateau() = default;

    bool placerPion(int x, int y, Pion *p);

    Case *getCase(int x, int y);

    bool verifierVictoire(Joueur* joueur);
};