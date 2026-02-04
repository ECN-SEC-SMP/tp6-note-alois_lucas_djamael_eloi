/**
 * @file Plateau.hpp
 * @author Eloi Tourangin
 * @brief
 * @version 0.1
 * @date 20-01-2026
 */

#pragma once

#include <vector>
#include <iostream>
#include "Case.hpp"
#include "Pion.hpp"
#include "Joueur.hpp"

using namespace std;
class Joueur;
class Plateau
{
private:
    vector<vector<Case>> grille;

    bool verifierLignes(Couleur couleur) const;
    bool verifierColonnes(Couleur couleur) const;
    bool verifierDiagonales(Couleur couleur) const;
    bool verifierEmpilements(Couleur couleur) const;

public:
    Plateau();
    ~Plateau() = default;
    bool estPlein() const;

    bool placerPion(int x, int y, Pion *p);
    Case *getCase(int x, int y);
    const Case* getCase(int x, int y) const;
    bool verifierVictoire(Couleur couleur) const;
    bool peutPlacer(int x, int y, const Pion* p) const;
    bool joueurPeutJouer(const Joueur& j) const;


    void afficher() const;
};
